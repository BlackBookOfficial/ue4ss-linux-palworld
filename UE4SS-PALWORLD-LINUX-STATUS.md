# UE4SS Native Linux Port — Palworld Server

## Status: WORKING — all major hooks verified in-game (2026-07-28)

Lua mods load, `RegisterHook` works, admin commands work, players join and play
with the full hook set enabled. Server stable at 118–119 FPS.

## Hook Status (config: `~/palworld-server/UE4SS-settings.ini`)

| Hook | Setting | Verified address | Status |
|---|---|---|---|
| BeginPlay | `HookBeginPlay=true` | `0x9f778f0` (vtable slot `0x388`) | Working, soak-tested in-game |
| EndPlay | `HookEndPlay=true` | `0x9f64320` (slot `0x390`) | Working |
| LoadMap | `HookLoadMap=true` | `0xaa43800` (slot `0x4C0`) | Working (fires at startup) |
| InitGameState | `HookInitGameState=true` | `0xa3b5000` (slot `0x740`) | Working |
| ProcessConsoleExec | `HookProcessConsoleExec=true` | `0x7b4b5e0` (slot `0x2B8`) | Working |
| ULocalPlayerExec | `HookLocalPlayerExec=true` | via `FExecVTableOffsetInLocalPlayer` | Working |
| EngineTick | `HookEngineTick=true` (default) | `0xaa39580` (slot `0x2F0`) | Working — 30h-stable |
| ProcessLocalScriptFunction | `HookProcessLocalScriptFunction=true` | AOB scan | Working — survived player join (fixed by thunk-aware JMP resolution) |
| StaticConstructObject | always on | AOB scan | Working |
| CallFunctionByNameWithArguments | `HookCallFunctionByNameWithArguments=false` | — | **Untested since thunk fix** — retest pending |
| UObjectProcessEvent | `HookUObjectProcessEvent=false` | — | **Untested since thunk fix** — retest pending |

## Verified Palworld vtable offsets (differ from upstream 5.1 dump)

Palworld's vtables do **not** follow a uniform shift — verify per entry, never
blanket-shift. Overrides live in `deps/first/Unreal/src/UnrealInitializer.cpp`
(gated `is_palworld` block).

| Class::Function | Upstream 5.1 (baked) | Palworld-Linux | Evidence |
|---|---|---|---|
| UObject::ProcessEvent | 0x260 | **0x268** | GDB call test (audit) |
| UObject::GetFunctionCallspace | 0x268 | **0x270** | audit |
| UObject::CallRemoteFunction | 0x270 | **0x278** | audit |
| UObject::ProcessConsoleExec | 0x278 | **0x2B8** real impl (via thunk at slot) | thunk-aware resolution; fired hooks work |
| AActor::BeginPlay | 0x380 | **0x388** | 261 vtables share `0x9f778f0` at 0x388; caller `mov %rdi,%rbx; call` (1-arg) |
| AActor::EndPlay | 0x388 | **0x390** | same sweep; wrapper callers pass `rsi` through (EndPlayReason) |
| AGameModeBase::InitGameState | 0x738 | **0x740** | six GameMode vtables hold `0xa3b5000` at 0x740; override wrapper chains into it with rdi only |
| UEngine::Tick | 0x2F0 | **0x2F0 (unshifted)** | 30h-stable hook; slot 0x2F8's fn is `(ptr, i64, ptr)` and crashes if detoured as Tick |
| UEngine::LoadMap | 0x4C0 | **0x4C0 (baked)** | fires cleanly at startup; consistent across 3 UEngine vtables |

Model: AActor's own region has an extra slot before the tick-prerequisite
adapters (0x378/0x380 = RemoveTickPrerequisiteActor/Component adapters, note
`+0x28` vs `+0x30` variants). UEngine's region is NOT shifted. UObject's
ProcessEvent-and-later slots are +8. Do not generalize.

## Root Causes Found and Fixed (newest first)

### Thunk-aware JMP resolution (ASMHelper) — fixed PLSF join freeze
**File:** `deps/first/ASMHelper/src/ASMHelper.cpp`
`RESOLVE_JMP` previously stopped at the first instruction; a 2-instruction stub
(`xor %r8d,%r8d; jmp <real>`) was returned as the hook target. Now follows jmp
thunks (including mid-function ones) to the real implementation. ProcessConsoleExec
`0x44d0020 → 0x7b4b5e0`, and ProcessLocalScriptFunction now detours the real
function — the old behavior (detour on a stub) is the likely cause of the
deterministic join freeze at ~90% (2026-07-28 09:24 boot). PLSF re-verified
working after the fix.

### Palworld vtable slot verification & overrides
**File:** `deps/first/Unreal/src/UnrealInitializer.cpp`
AActor BeginPlay/EndPlay, AGameModeBase InitGameState overrides (table above).
Verification method (reusable after updates): anchor vtables in the binary via
the shared tick-adapter thunk (`0x9f5cc80`, slot 0x380) or a known function,
read candidate slots, disassemble targets, and check caller argument setup
(`rdi`-only vs `rdi+rsi`).

### FName `_N` suffix Number parsing
**Files:** `deps/first/Unreal/src/NameTypes.cpp`, `UE4SS/src/LuaType/LuaFName.cpp`
The engine's find-or-add parses `Name_N` suffixes and returns the BASE name's
ComparisonIndex; we must replicate the parse and set `FName.Number = N` (default
was 0 — wrong for e.g. `BountyProof_1`). New Lua overload
`FName(string, integer Number, EFindName)`.

### Lua SIGABRT on mod errors
**Commit:** `c1b0bd5` — use `longjmp` instead of C++ exceptions across Lua.

### Limited-mode crashes
**Commit:** `f9f18e7`; Default__Object lookup + ProcessEvent hook init: `0e2a3f4`.

### Earlier fixes (kept from previous revision)
1. `Function::reset_address()` missing `m_is_ready=false` — stale ready flag.
2. `FName(StringViewType)` now null-terminates before find-or-add.
3. GMalloc heuristic: main-exe writable segments + BSS only, vtable[2] must be `31 C0 C3`.
4. FMalloc vtable +8 shift (extra no-op slot) — Malloc 0x18, TryMalloc 0x20, Realloc 0x28, TryRealloc 0x30, Free 0x38.
5. `FMemory::Malloc/Realloc/Free` use system allocator on Linux (FMallocBinned2 TLS cache unsafe from UE4SS init context).
6. GUObjectArray chunked access (6 chunks × 65536 × 24-byte items) + SIGSEGV recovery on stale pointers.
7. PalworldNameProvider::FindName wired to engine find-or-add `0x7941c10` (AOB).

## Landmines / What To Watch Out For

- **`VTableLayout.ini` (server dir) CANNOT fix wrong offsets.** The loader uses
  `emplace()` — insert-only, existing keys win. Baked/generated offsets always
  beat the ini. Correct place: the `is_palworld` block in
  `UnrealInitializer.cpp`.
- **Deploy atomically:** `cp libUE4SS.so libUE4SS.so.new && mv libUE4SS.so.new libUE4SS.so`.
  A plain `cp` over the live `.so` while the server runs corrupts the mapping.
- **Crash signature reading:**
  - SIGSEGV inside GUObjectArray accessor with a garbage index → a hook registry/
    index corrupted earlier by a wrong detour (six-hook boot symptom).
  - Detour receives denormal float (~9e-39) + bool=64 → wrong slot: real fn is
    `(ptr, i64, ptr)`-shaped; the truncation kills a pointer → crash deep in callee.
  - SIGSEGV `[rsi+8]` inside libUE4SS after a vtable hook → detour signature
    mismatch; Lua callback marshaled a garbage `this`/param.
  - `rip` in `0x7f...` range = inside libUE4SS/trampolines; low `0x0...` = game binary.
- **After any Palworld update:** re-verify every offset in the table above
  against the new binary BEFORE enabling hooks (method: vtable anchor sweep +
  caller arg-setup check). Boot and confirm the `... address 0x...` lines in
  `UE4SS.log` match expectations; `PalworldNameProvider` errors or
  `ScanGame: ... failed` lines mean re-derivation is needed.
- **The port hooks PLSF/CFBNWA-relevant script dispatch via the standard
  TDetourInstance path; mods using `RegisterHook` on UFunctions rely on it.**
  If joins freeze at ~90% again, suspect these first — but do NOT blanket-disable;
  capture the stalled game thread with `gdb -p <pid> -batch -ex "thread apply all bt 8"`.
- **Stripped binary:** no symbols; every address in this doc is for the current
  `PalServer-Linux-Shipping` build and WILL move on update.

## Key Addresses (runtime, process-specific)
- GUObjectArray: `0xc11e878` (BSS, patternsleuth)
- Engine find-or-add: `0x7941c10` (text, AOB)
- FMallocBinned2 vtable: `0x1a1eef0` (rodata); instance on heap
- Text region: `0x043b3000-0x0bc8e000`; BSS: `0xbd34000-0xc2e5000`

## Build & Deploy
```bash
cd ~/ue4ss-linux-src && source ~/.cargo/env
cmake --build build_linux_Dev_gcc --target UE4SS
cp build_linux_Dev_gcc/Game__Dev__Linux64/lib/libUE4SS.so ~/palworld-server/libUE4SS.so.new
mv ~/palworld-server/libUE4SS.so.new ~/palworld-server/libUE4SS.so   # atomic
~/palctl.sh restart
```

## Config
- `~/palworld-server.conf`: `ENABLE_UE4SS=1`
- `~/palworld-server/Mods/mods.txt`: mod load order
- `~/palworld-server/MemberVariableLayout.ini`: member offsets (NOT vtable overrides)
- `~/palworld-server/UE4SS-settings.ini`: hook toggles per table above
