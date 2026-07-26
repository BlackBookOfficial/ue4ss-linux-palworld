# Itanium ABI: PMF Bug and Palworld Vtable Shift

## Technical Note for Upstreaming

This document explains two bugs that only manifested on Linux (Itanium C++ ABI)
and were the root causes preventing `ProcessEvent` from being resolved on the
Palworld dedicated server.

---

## 1. The `bit_cast_mfp` Uninitialized Adjustment Field

### Background: Pointer-to-Member-Function (PMF) Representation

On the Itanium C++ ABI (used by GCC and Clang on Linux), a
pointer-to-member-function (PMF) is **16 bytes**, not 8:

| Bytes 0–7 | Bytes 8–15 |
|-----------|-------------|
| Function pointer (or vtable offset if bit 0 is set) | `this` adjustment offset |

The low bit of the first word determines the dispatch mode:
- **Bit 0 = 0**: Direct call. The first word is the function address.
- **Bit 0 = 1**: Virtual dispatch. The first word is `(vtable_offset + 1)`,
  and the function is looked up in the vtable using that offset.

On the MSVC ABI (Windows), a PMF is also variable-sized, but the compiler
handles the representation transparently, and `std::bit_cast` works correctly
because MSVC's `bit_cast` implementation is designed for this.

### The Bug

UE4SS uses a `bit_cast_mfp` helper to convert a raw `void*` (read from a
vtable entry) into a PMF, because GCC/Clang's `std::bit_cast` does not support
PMFs (they are not trivially copyable).

The original implementation used a union:

```cpp
template <typename MemberFuncPtr>
static MemberFuncPtr bit_cast_mfp(void* ptr) {
    union { void* in; MemberFuncPtr out; } u;
    u.in = ptr;
    return u.out;
}
```

**The union only writes 8 bytes** (the size of `void*`), but the PMF is
**16 bytes**. The `this` adjustment field (bytes 8–15) is left
**uninitialized** — it contains whatever garbage was on the stack.

When the PMF is invoked, the Itanium ABI runtime applies the `this`
adjustment to the object pointer before calling the function. With garbage
in the adjustment field, the `this` pointer is corrupted, causing a SIGSEGV
in the called function (typically at the very first instruction that
dereferences `this`).

### Why It Only Manifested on Linux

On Windows (MSVC ABI), `std::bit_cast<MemberFuncPtr>` is used instead of
`bit_cast_mfp`. MSVC's `bit_cast` correctly zero-initializes the entire PMF
before copying, so the adjustment field is always 0. The union-based helper
was never compiled on Windows.

On Linux, every `IMPLEMENT_UNREAL_VIRTUAL_WRAPPER` macro call flows through
`bit_cast_mfp`, meaning **every virtual function call made through the
vtable wrapper was affected**. The most visible symptom was `ProcessEvent`
crashing, but the bug affected all vtable-dispatched virtuals.

### The Fix

Zero-initialize the full PMF before copying the function pointer:

```cpp
template <typename MemberFuncPtr>
static MemberFuncPtr bit_cast_mfp(void* ptr) {
    MemberFuncPtr out{};  // zero-initialize (both fields = 0)
    std::memcpy(&out, &ptr, sizeof(void*));
    return out;
}
```

This ensures the `this` adjustment is always 0, which is correct for
single-inheritance classes like `UObject` (where the vtable entry IS the
actual function address with no adjustment needed).

---

## 2. Palworld UObject Vtable Offset Shift (+8)

### Background: UE4SS Vtable Offsets

UE4SS maintains a `VTableLayoutMap` for each engine class, mapping function
names to byte offsets within the vtable. These offsets are generated from
the Unreal Engine source for each engine version (e.g., UE5.1).

For `UObject` on UE5.1, the generated offsets include:

| Function | Standard UE5.1 Offset |
|----------|----------------------|
| `OverridePerObjectConfigSection` | 0x258 |
| `ProcessEvent` | 0x260 |
| `GetFunctionCallspace` | 0x268 |
| `CallRemoteFunction` | 0x270 |
| `ProcessConsoleExec` | 0x278 |

### The Bug

Palworld's UE5.1 build (Pocketpair's modified engine) has an **extra
virtual function slot** in the `UObject` vtable, inserted between
`OverridePerObjectConfigSection` and `ProcessEvent`. This shifts all four
subsequent functions by +8 bytes:

| Function | Palworld Actual Offset | Shift |
|----------|------------------------|------|
| `OverridePerObjectConfigSection` | 0x258 (unchanged) | 0 |
| *(extra slot — empty stub)* | 0x260 | — |
| `ProcessEvent` | 0x268 | +8 |
| `GetFunctionCallspace` | 0x270 | +8 |
| `CallRemoteFunction` | 0x278 | +8 |
| `ProcessConsoleExec` | 0x280 | +8 |

The extra slot at 0x260 contains a no-op stub (`ret; int3`), suggesting
Pocketpair added a virtual function declaration to `UObject` that returns
void and does nothing.

### Evidence

Runtime verification via GDB confirmed:
- `vtable[0x260]` = `ret; int3; int3; int3` (empty stub) — NOT ProcessEvent
- `vtable[0x268]` = `push rbp; mov rsp,rbp` (real function) — IS ProcessEvent
- Calling `vtable[0x268]` via the KSL CDO correctly converts `FName(0x1f8)`
  to the string `"Actor"`, confirming it is `UObject::ProcessEvent`
- Other UObject virtuals (`PostLoad` at 0xA0, `BeginDestroy` at 0xB0,
  `FinishDestroy` at 0xC0) are at their **standard offsets** — the shift
  is local to the ProcessEvent region, not a global ABI difference

### Why It Is Palworld-Specific, Not Engine-Wide

The shift affects only the `ProcessEvent` region of the vtable. If it were
an engine-wide Itanium ABI difference, ALL virtual functions would be
shifted (e.g., `PostLoad` would be at 0xA8 instead of 0xA0). The fact that
only ProcessEvent and its neighbors are shifted proves that Pocketpair added
a virtual function to `UObject` in their custom engine build.

### Why It Only Manifested on Linux

On Windows, the standard UE4SS offsets work because:
1. The Windows binary is built from the same modified engine source
2. The MSVC compiler generates the vtable with the same extra slot
3. BUT: the VTableLayoutMap was empirically validated on Windows by reading
   the actual vtable, so the Windows offsets already account for the extra
   slot

On Linux, the VTableLayoutMap was never validated against the actual binary
because `ProcessEvent` resolution was blocked by the `bit_cast_mfp` bug
(which prevented `Conv_NameToString` from working, which prevented
`GetFullName()` from returning correct strings, which prevented
`Default__Object` from being found).

Once the `bit_cast_mfp` bug was fixed, `Conv_NameToString` worked, but it
called `ProcessEvent` via the wrong vtable offset (0x260 instead of 0x268),
hitting the no-op stub and returning empty strings. This cascade of failures
made the vtable offset bug invisible until the PMF bug was fixed first.

### The Fix

Override the vtable offsets at runtime, gated to the Palworld binary:

```cpp
char exe_path[4096];
ssize_t exe_len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
bool is_palworld = (exe_len > 0 && 
    std::string(exe_path).find("PalServer") != std::string::npos);
if (is_palworld)
{
    UObject::VTableLayoutMap[STR("ProcessEvent")] = 0x268;
    UObject::VTableLayoutMap[STR("GetFunctionCallspace")] = 0x270;
    UObject::VTableLayoutMap[STR("CallRemoteFunction")] = 0x278;
    UObject::VTableLayoutMap[STR("ProcessConsoleExec")] = 0x280;
}
```

The `VTableLayoutMap` is an `unordered_map` that supports runtime updates.
The override is applied after `set_virtual_offsets()` populates the standard
offsets and before any code that calls virtual functions through the wrapper.

---

## Summary of the Failure Cascade

```
bit_cast_mfp bug (uninitialized this_adjustment)
    │
    ├── ProcessEvent called via vtable → SIGSEGV (corrupted this)
    │
    └── Conv_NameToString returns empty strings (ProcessEvent crashes
        are caught by SIGSEGV recovery, returning nothing)
            │
            └── GetFullName() returns " ." (empty class + empty path)
                │
                └── StaticFindObject_InternalSlow("...Default__Object")
                    never matches → Object = nullptr
                    │
                    └── ProcessEvent hook never installed
                        │
                        └── All hooks fail: "function is unavailable"

After fixing bit_cast_mfp:
    ProcessEvent no longer crashes, but calls the no-op stub at 0x260
    (vtable offset shift) → Conv_NameToString still returns empty strings
    → same cascade continues

After ALSO fixing vtable offset (0x260 → 0x268):
    Conv_NameToString returns correct strings
    → GetFullName() works
    → Default__Object found
    → ProcessEvent address resolved
    → All hooks installed
```

Both bugs had to be fixed together. Fixing only one would have left
`Conv_NameToString` returning empty strings (either crashing or hitting the
no-op stub), preventing the entire initialization chain from completing.
