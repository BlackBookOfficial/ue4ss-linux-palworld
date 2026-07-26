# UE4SS Native Linux Port — Palworld Server

## Status: WORKING — Lua mods execute successfully

### What Works
- ✅ UE4SS loads via LD_PRELOAD on native Linux Palworld server
- ✅ GUObjectArray found (patternsleuth Linux patterns, `0xc11e878`)
- ✅ FName constructor wired to engine's find-or-add (`0x7941c10`)
- ✅ FName(StringViewType) correctly null-terminates string_view data
- ✅ KismetStringLibrary CDO found, Conv_NameToString available
- ✅ `store_all_object_types()` succeeds (22/24 core objects found)
- ✅ `find_all_property_types()` succeeds (FFieldClass map populated)
- ✅ ProcessLocalScriptFunction hook installed
- ✅ CallFunctionByNameWithArguments hook installed
- ✅ StaticConstructObject hook installed
- ✅ Lua mod loading works — UE4SSStatus mod executes `main.lua`
- ✅ Server stable at 118-119 FPS

### What Doesn't Work Yet
- ❌ AdminCommands mod crashes the server (Signal 6/SIGABRT during Lua require())
- ❌ ProcessEvent hook unavailable (Default__Object CDO not found)
- ❌ Many hooks fail ("function is unavailable") — detour installation fails
- ❌ BeginPlay/EndPlay hooks not available

## Root Causes Found and Fixed

### 1. Function::reset_address() missing m_is_ready=false
**File:** `deps/first/Function/include/Function/Function.hpp`
**Fix:** Added `m_is_ready = false;` to `reset_address()`.
Without this, `is_ready()` returns true after a reset, causing calls to stale/wrong addresses.

### 2. FName(StringViewType) passing non-null-terminated data
**File:** `deps/first/Unreal/include/Unreal/NameTypes.hpp`
**Fix:** `FName(StringViewType, ...)` now creates a null-terminated copy (`StringType null_terminated(str_name)`) before passing to `construct_with_string()`.
**Root cause:** `string_view::data()` is NOT null-terminated. The engine's FName constructor (`0x7941c10`) scans for a null terminator to determine string length. Non-null-terminated data caused it to read past the view boundary, producing wrong ComparisonIndex values (e.g., reading "/Script/CoreUObject.Object" instead of "/Script/CoreUObject").

### 3. GMalloc heuristic finding wrong pointer
**File:** `UE4SS/src/UE4SSProgram.cpp` (ScanOverrides.fmemory_free)
**Fixes:**
- Restricted scan to main executable's writable segments only (not heap/shared libs)
- Added BSS anonymous region from `/proc/self/maps` (where GMalloc lives)
- Required vtable[2] to be the no-op pattern `31 C0 C3` (xor eax,eax; ret)
- This filters false positives from other vtables

### 4. FMalloc vtable offset mismatch (Itanium ABI extra slot)
**File:** `UE4SS/src/UE4SSProgram.cpp` (after GMalloc found)
**Fix:** On Linux, FMallocBinned2's vtable has an extra virtual slot (vtable[2] = no-op), shifting all function offsets by +8 bytes:
- Malloc: 0x10 → 0x18
- TryMalloc: 0x18 → 0x20
- Realloc: 0x20 → 0x28
- TryRealloc: 0x28 → 0x30
- Free: 0x30 → 0x38
**Detection:** Check if vtable[2] is `31 C0 C3` (xor eax,eax; ret). If so, shift all offsets.

### 5. FMemory::Malloc/Realloc/Free crash on Linux
**File:** `deps/first/Unreal/src/Core/HAL/UnrealMemory.cpp`
**Fix:** On Linux, `FMemory::Malloc/Realloc/Free` use `SystemMalloc`/`realloc`/`SystemFree` instead of `(*GMalloc)->Malloc/Realloc/Free`.
**Root cause:** The engine's FMallocBinned2 uses thread-local caches (`pthread_getspecific`). When UE4SS calls `Malloc` from its init context, the TLS cache may not be set up correctly, causing a crash in the allocator internals. UE4SS's containers (TMap, TSparseArray) are internal and don't interact with the engine's GC, so using the system allocator is safe.

### 6. GUObjectArray chunked layout
**File:** `deps/first/Unreal/src/UObjectArray.cpp`, `UObjectGlobals.cpp`
**Fix:** Implemented chunked FChunkedFixedUObjectArray access (6 chunks, 65536 items per chunk, 24-byte FUObjectItem). Per-iteration SIGSEGV recovery for stale UObject pointers.

### 7. PalworldNameProvider::FindName
**File:** `deps/first/Unreal/src/NameTypes.cpp`
**Fix:** Wired FName constructor to engine's find-or-add name lookup at `0x7941c10` (located via AOB signature scan). Returns correct ComparisonIndex matching UObject NamePrivate values.

## Key Addresses (runtime, process-specific)
- GUObjectArray: `0xc11e878` (BSS, found via patternsleuth)
- Engine find-or-add: `0x7941c10` (text, found via AOB)
- GMalloc: BSS (found via heuristic with vtable validation)
- FMallocBinned2 vtable: `0x1a1eef0` (rodata)
- FMalloc instance: heap (varies per run)
- Text region: `0x043b3000-0x0bc8e000`
- BSS region: `0xbd34000-0xc2e5000`

## Build & Deploy
```bash
cd ~/ue4ss-linux-src && source ~/.cargo/env
cmake --build build_linux_Dev_gcc --target UE4SS
cp build_linux_Dev_gcc/Game__Dev__Linux64/lib/libUE4SS.so ~/palworld-server/libUE4SS.so
```

## Config
- `~/palworld-server.conf`: `ENABLE_UE4SS=1` to enable
- `~/palworld-server/Mods/mods.txt`: mod load order
- `~/palworld-server/MemberVariableLayout.ini`: UObject/struct offsets
- `~/palworld-server/UE4SS-settings.ini`: UE4SS settings
