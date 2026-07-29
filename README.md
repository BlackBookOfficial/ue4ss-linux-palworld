# UE4SS Linux — Palworld

A native Linux build of [UE4SS](https://github.com/UE4SS-RE/RE-UE4SS) (Unreal
Engine 4/5 Scripting System) that runs Lua mods on a **Linux dedicated
Palworld server** — no Windows, no Proton, no Wine. Loaded with `LD_PRELOAD`.

> Based on [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS) by UE4SS-RE
> (MIT License), with Linux groundwork by
> [calebm02](https://github.com/calebm02/RE-UE4SS-Linux).

## Status

Palworld (UE 5.1) dedicated server: **all major UE4SS hooks verified working
in-game** — BeginPlay, EndPlay, LoadMap, InitGameState, ProcessConsoleExec,
ULocalPlayerExec, EngineTick, ProcessLocalScriptFunction,
CallFunctionByNameWithArguments, UObjectProcessEvent, StaticConstructObject.
`RegisterHook` and Lua mods (e.g. AdminCommands) work as upstream.
Full hook table: [UE4SS-PALWORLD-LINUX-STATUS.md](UE4SS-PALWORLD-LINUX-STATUS.md).

Game updates are handled by three resilience layers — an update either just
works or fails loudly, never silently corrupts the server:

1. **AOB scans** resolve ProcessEvent, FName, GUObjectArray, GMalloc, etc.
   across recompiles.
2. **Self-healing vtable sweep** re-derives AActor BeginPlay/EndPlay slot
   offsets by consensus over all vtables in the binary at boot.
3. **Validation gate** disassembles every vtable hook target before detouring
   and refuses proven-crash signatures with a named log line.

After a server update, boot once and check `UE4SS.log` for `vtable sweep` and
`REFUSED`/`NOTE` lines before anyone joins — details in the status doc.

---

## For Server Owners

### Requirements
- Native Linux Palworld dedicated server (`PalServer-Linux-Shipping`), x86_64
- glibc-based distro (tested on Ubuntu; WSL works)

### Install
Get `libUE4SS.so` — from the [Releases page](../../releases) or a CI artifact
([Actions](../../actions) → latest `Linux & Cross-Compile CI` run), or build
it yourself (below). Then, next to `PalServer.sh`:

```
your-server/
├── PalServer.sh
├── libUE4SS.so              ← the engine hook library
├── UE4SS-settings.ini       ← hook & logging config
├── MemberVariableLayout.ini ← struct offsets (Palworld-specific)
└── Mods/
    ├── mods.txt             ← "ModName : 1" enables a mod
    └── YourMod/
        └── scripts/main.lua
```

Launch with the library preloaded:

```bash
LD_PRELOAD="$PWD/libUE4SS.so" ./PalServer.sh -port=8211 ...your flags...
```

If you use a server manager (AMP, Pterodactyl, a custom script), point its
startup at a wrapper that sets `LD_PRELOAD` and re-creates the symlink after
game updates (managers overwrite the binary).

Verify: `UE4SS.log` appears beside the binary and mods print their load
messages.

### Palworld updates
Just restart. The port re-resolves everything automatically. If a hook ever
fails validation after an update, the server still boots — the hook is
disabled and `UE4SS.log` names it (`Palworld hook validation REFUSED ...`).

---

## For Mod Developers

- **Lua mods**: identical to upstream UE4SS — `Mods/<ModName>/scripts/main.lua`,
  enabled via `Mods/mods.txt`. API docs: upstream
  [UE4SS docs](https://docs.ue4ss.com/). Nothing to port.
- **C++ mods**: must be built as Linux `.so` in `<Mod>/libs/` (not `dlls/`).
  Windows DLLs can never load here.
- Palworld-specifics that differ from upstream:
  - `RegisterKeyBind` needs a real TTY (no stdin console on dedicated servers).
  - GUI runs headless (EGL, hidden window) — no visible window on a server.
  - Console-command mods rely on the `ProcessConsoleExec` hook (works, fires
    on RCON/chat commands).
  - One mod crashing does not kill the server — per-mod crash recovery logs
    and continues.

---

## For Contributors (working on ue4ss-linux)

### How the port works
- **Injection**: `LD_PRELOAD` → `UE4SS/src/main_linux.cpp` bootstraps inside
  the game process (no proxy DLL).
- **Function resolution** (`ScanOverrides`): `dlsym` against the process, then
  port-specific AOB/pattern scans for ProcessEvent, PLSF, CFBNWA, FName,
  StaticConstructObject; heuristics for GUObjectArray/GMalloc — all update-
  robust.
- **JMP thunks**: `RESOLVE_JMP` is thunk-aware (follows mid-function jmp
  stubs) — detouring a stub instead of the real function previously broke
  player joins.
- **Vtable handling** (`deps/first/Unreal/src/UnrealInitializer.cpp`):
  - Palworld's vtables diverge from upstream UE5.1 — per-entry verified
    overrides in the `is_palworld` block (NOT a uniform shift — do not
    blanket-shift, UEngine::Tick proves it).
  - The **vtable sweep** re-derives AActor BeginPlay/EndPlay offsets at boot
    by anchoring on the tick-prerequisite adapter thunk and voting across
    ~500 vtables.
  - The **validation gate** (`validate_hook_target`) prologue-checks every
    vtable hook before install: refuses junk targets and float/int register
    truncation (loud `REFUSED` log), notes shape drift (`NOTE` log) and
    installs anyway — extra pointer args pass through the trampoline safely.
- **Docs to read before changing anything**:
  [UE4SS-PALWORLD-LINUX-STATUS.md](UE4SS-PALWORLD-LINUX-STATUS.md) — hook table,
  verified offsets, crash-signature reading guide, landmines
  (e.g. `VTableLayout.ini` cannot override baked offsets; deploy the `.so`
  atomically). [docs/LINUX_PORT_AUDIT.md](docs/LINUX_PORT_AUDIT.md) —
  classification of all port changes.

### Build
Same recipe CI uses:

```bash
sudo apt-get install -y cmake ninja-build pkg-config gcc g++ \
  libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
  libgl-dev libegl-dev libgles-dev
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

git clone <your-fork-url> && cd ue4ss-linux-palworld
cmake -B build_linux_Dev_gcc -G Ninja \
  -DCMAKE_BUILD_TYPE=Game__Dev__Linux64 \
  -DUE4SS_GUI_ENABLED=ON -DUE4SS_INPUT_ENABLED=OFF
cmake --build build_linux_Dev_gcc --target UE4SS
# -> build_linux_Dev_gcc/Game__Dev__Linux64/lib/libUE4SS.so
```

### CI
- **Linux & Cross-Compile CI** — every push/PR to `linux-native`:
  Debug + Dev × gcc + clang. (`Debug`/`Dev` are UE4SS build configurations,
  not "debug vs release" in the classic sense; the shippable config is `Dev`.)
- **Linux Release Publisher** — manual trigger with a tag: builds the `Dev`
  config and publishes a GitHub Release with ready-to-deploy artifacts.

### After a Palworld update
1. Boot once, read `UE4SS.log`: `vtable sweep` lines confirm self-correction,
   `REFUSED` names a disabled hook, `NOTE` flags shape drift.
2. If a slot needs re-derivation, the binary method is in the status doc
   (anchor sweep + caller argument analysis).
3. PRs welcome — keep the per-entry-verification discipline: no blanket
   vtable shifts, verify against the shipping binary.

## License

MIT — see [LICENSE](LICENSE) and [NOTICE](NOTICE). Palworld is a trademark of
Pocketpair, Inc.; this project is not affiliated with or endorsed by them.
