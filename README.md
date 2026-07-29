# UE4SS Linux Native Port


>
> Based on [RE-UE4SS](https://github.com/UE4SS-RE/RE-UE4SS) by [UE4SS-RE](https://github.com/UE4SS-RE).
> Linux port originally by [calebm02](https://github.com/calebm02/RE-UE4SS-Linux).
>
> Licensed under the MIT License. See [LICENSE](LICENSE) and [NOTICE](NOTICE) for details.

A native Linux build of UE4SS (Unreal Engine 4/5 Scripting System) for dedicated game servers running on Linux. This port enables Lua mod loading and scripting on Linux dedicated servers without requiring Windows.

> ## ⚠️ IMPORTANT: Plugin File Format on Linux
>
> **This is a Linux build. It CANNOT load Windows `.dll` files.** Any mod or plugin
> you install must be provided in the **native Linux formats** listed below. If a mod
> author only ships `.dll` files, that mod **will not work** on this Linux build —
> there is no `.dll`-to-`.so` compatibility layer, emulation, or shim of any kind.
>
> | Mod Type | Windows Format | **Required Linux Format** |
> |----------|-----------------|----------------------------|
> | Lua mods | `scripts/main.lua` | `scripts/main.lua` — **identical, no changes needed** (Lua is script-based and platform-independent) |
> | C++ mods | `dlls/main.dll` | `libs/main.so` — **must be a natively compiled Linux shared object (`.so`), not a `.dll`** |
>
> **Key points to remember:**
> - The mod folder for C++ mods on Linux is called **`libs/`**, not `dlls/` (this is different from Windows!).
> - A C++ mod must be **recompiled from source specifically for Linux** (e.g. with GCC or Clang, producing an ELF `.so` file). Simply renaming a `.dll` to `.so` will **not** work — the internal binary format is completely different.
> - Directory names inside a mod folder are **case-sensitive** on Linux (`scripts`, `libs` — always lowercase), unlike Windows where case does not matter.
> - If your mod only provides a `dlls/` folder with a `.dll` inside, UE4SS will **not detect or load it at all** on Linux — you will need the mod author (or yourself, if you have the source) to produce a Linux `.so` build.
>
> **In short: Lua mods just work as-is. C++ mods must be a Linux-native `.so` file inside a `libs/` folder — never a `.dll`.**

## Features

- **Lua Mod Loading**: Load and run Lua-based mods on Linux dedicated servers
- **LD_PRELOAD Injection**: Loaded via `LD_PRELOAD` — no proxy DLL needed
- **Per-Mod Crash Recovery**: If one mod crashes (SIGSEGV), other mods continue to load
- **Headless Mode**: GUI and input systems disabled for server environments
- **POSIX File System**: Full Linux file system support
- **Native Linux Crash Dumper**: Signal-based crash handling with backtrace

## Palworld (UE 5.1) Status

Fully working on the native Linux dedicated server — all major hooks verified
in-game: BeginPlay, EndPlay, LoadMap, InitGameState, ProcessConsoleExec,
ULocalPlayerExec, EngineTick, ProcessLocalScriptFunction,
CallFunctionByNameWithArguments, UObjectProcessEvent, StaticConstructObject.

Game updates are handled by three resilience layers, so a Palworld update
either just works or fails loudly — never a silent mid-session crash:

1. **AOB scans** resolve ProcessEvent, FName, GUObjectArray, etc. across
   recompiles.
2. **Self-healing vtable sweep** re-derives AActor BeginPlay/EndPlay slot
   offsets by consensus over all in-binary vtables at boot.
3. **Hook-target validation gate** disassembles each hook target before
   detouring and refuses proven-crash classes with a named log line.

See [UE4SS-PALWORLD-LINUX-STATUS.md](UE4SS-PALWORLD-LINUX-STATUS.md) for the
full hook table, verified offsets, and what to check in the log after an
update (`REFUSED` / `NOTE` lines).

## Building From Source

Linux (GCC or Clang) — the same recipe CI uses:

```bash
sudo apt-get install -y cmake ninja-build pkg-config gcc g++ \
  libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev \
  libgl-dev libegl-dev libgles-dev
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh   # Rust toolchain

git clone --recursive https://github.com/BlackBookOfficial/ue4ss-linux-palworld.git
cd ue4ss-linux-palworld
cmake -B build_linux_Dev_gcc -G Ninja \
  -DCMAKE_BUILD_TYPE=Game__Dev__Linux64 \
  -DUE4SS_GUI_ENABLED=ON -DUE4SS_INPUT_ENABLED=OFF
cmake --build build_linux_Dev_gcc --target UE4SS
# result: build_linux_Dev_gcc/Game__Dev__Linux64/lib/libUE4SS.so
```

CI (`Linux & Cross-Compile CI` workflow) builds GCC+Clang, Debug+Dev on every
push and PR to `linux-native`; the `Linux Release Publisher` workflow tags a
release with ready-to-deploy artifacts. No local build required.

## Installation

### Prerequisites

- A Linux dedicated server for a UE4/5 game (e.g., Palworld, Ark, etc.)
- Root or sudo access to the server

### Steps

1. **Download the latest release**

   Download `UE4SS-Linux-build.zip` from the [Releases page](https://github.com/BlackBookOfficial/ue4ss-linux-palworld/releases/latest).

2. **Extract the archive**

   ```bash
   unzip UE4SS-Linux-build.zip
   ```

   This will extract `libUE4SS.so`.

3. **Copy `libUE4SS.so` to your game's binary directory**

   Place `libUE4SS.so` in the same directory as your game server executable.

   Example for Palworld:
   ```bash
   cp libUE4SS.so /path/to/PalServer/Binaries/Linux/
   ```

4. **Set up the Mods directory**

   Create a `Mods` folder in the game's binary directory:
   ```bash
   mkdir -p /path/to/PalServer/Binaries/Linux/Mods
   ```

   Create a `mods.txt` file inside the `Mods` folder to specify which mods to load:
   ```bash
   echo "UE4SSStatus : 1" > /path/to/PalServer/Binaries/Linux/Mods/mods.txt
   ```

   Each line follows the format `ModName : 1` (enabled) or `ModName : 0` (disabled).

5. **Set up Lua mods**

   Each mod goes in its own folder under `Mods/`:
   ```
   Mods/
   ├── mods.txt
   └── MyMod/
       └── scripts/
           └── main.lua
   ```

   Note: On Linux, the scripts directory is lowercase `scripts` (case-sensitive).

6. **Launch the server with LD_PRELOAD**

   Set the `LD_PRELOAD` environment variable to load UE4SS:
   ```bash
   LD_PRELOAD=/path/to/libUE4SS.so ./PalServer-Linux-Shipping
   ```

   Or set it in your server startup script / systemd service:
   ```bash
   export LD_PRELOAD=/path/to/libUE4SS.so
   ```

### Optional: UE4SS Settings

Create a `UE4SS-settings.ini` file in the game's binary directory to configure UE4SS:

```ini
[General]
EnableHotReloadSystem=true
EnableAutoReloadingLuaMods=true
UseCache=true
InvalidateCacheIfDLLDiffers=true
EnableDebugKeyBindings=false
```

On Linux, `UE4SS-settings.ini` is fully parsed using a narrow-string parser (the wide-string INI parser crashes due to memory allocator conflicts). If no settings file is found, sensible defaults are used.

To use a different game/engine version, add an `[EngineVersionOverride]` section:
```ini
[EngineVersionOverride]
MajorVersion=5
MinorVersion=1
DebugBuild=false
```

## Verified Games

- **Palworld** (UE5.1) — Dedicated server on Linux

## Known Limitations

- **Work in Progress**: The entire codebase is being ported from Windows to Linux. Since this is an ongoing process, bugs may still occur. Not all Windows-specific code paths have been fully tested — please [report issues](https://github.com/BlackBookOfficial/ue4ss-linux-palworld/issues) if you encounter problems.
- **Function Resolution**: UE function addresses are resolved automatically on unstripped binaries via `dlsym`. On stripped binaries, use `UE4SS_Addresses.ini` to provide addresses manually. Without resolved addresses, mod functionality is limited to Lua scripting and basic operations.
- **Engine Version**: The engine version defaults to UE 5.1 (Palworld). For other games, set `[EngineVersionOverride]` in `UE4SS-settings.ini` with the correct `MajorVersion` and `MinorVersion`.
- **AOB/Signature Scanning**: patternsleuth (Rust) is built on Linux via Corrosion with ELF support. Pattern-based address discovery works for ELF binaries. On unstripped binaries, `dlsym` is used as the primary resolution method; patternsleuth provides fallback AOB scanning. On stripped binaries, manual entries in `UE4SS_Addresses.ini` may still be needed if AOB patterns don't match.
- **Mod Lifecycle**: `LuaMod::on_program_start()` and C++ mods' `on_program_start()` now run on Linux **when `GUObjectArray` is resolved** (via `dlsym` or `UE4SS_Addresses.ini`). On stripped binaries with no resolved addresses, only Lua mod top-level script code runs; C++ mods only get their constructor called.
- **Keybinds**: `RegisterKeyBind`/`RegisterKeyBindAsync` (Lua) and the hot-reload key now work on Linux when a real TTY is attached (reads raw keypresses via `termios`). They do **not** work when there's no controlling terminal (e.g. under systemd/Docker without a pty allocated).
- **GUI (Linux)**: The GUI is now enabled on Linux using the GLFW3/OpenGL3 backend. On headless servers (no `DISPLAY` environment variable), it automatically uses EGL with a hidden window for off-screen rendering. For interactive GUI access on a headless server, use `xvfb-run -a` or set up a virtual framebuffer (Xvfb). GUI settings can be configured in `UE4SS-settings.ini` under `[Debug]` with `GraphicsAPI` (0=DX11 Windows-only, 1=GLFW3/OpenGL3) and `RenderMode` (0=ExternalThread, 1=EngineTick, 2=GameViewportClientTick). To disable GUI entirely, build with `-DUE4SS_GUI_ENABLED=OFF`.
- **No UVTD**: The VTable Dumper tool is not built on Linux (depends on the Windows-only `raw_pdb` library).
- **UE Console Commands**: `RegisterConsoleCommandHandler`/`RegisterConsoleCommandGlobalHandler` (Lua) go through the `ProcessConsoleExec` hook, which is disabled by default (`HookProcessConsoleExec=false`) and requires a real caller of `UObject::ProcessConsoleExec` (e.g. RCON/admin commands the game already processes) — there is no interactive "type a command into stdin" console on Linux.
- **Blueprint Mod Loader**: Blueprint mod loading is supported. On unstripped binaries, UE function addresses are resolved automatically via `dlsym`. On stripped binaries, addresses can be provided manually via `UE4SS_Addresses.ini`. See [Blueprint Modloader docs](docs/feature-overview/blueprint-modloader.md) for details.
- **C++ Mods**: C++ mods must be compiled as `.so` files (not `.dll`).
- **Case Sensitivity**: Linux filesystems are case-sensitive — mod directories must use lowercase `scripts`.

## Troubleshooting

### Server won't start

Check that `LD_PRELOAD` points to the correct absolute path of `libUE4SS.so`.

### Mods not loading

- Verify `mods.txt` exists in the `Mods/` directory
- Verify each mod has a `scripts/main.lua` file (lowercase `scripts`)
- Check the server console output for `[UE4SS]` log messages

### Mod crashes

UE4SS has per-mod crash recovery. If a mod crashes, you will see:
```
[UE4SS] Caught signal 11 during mod execution, recovering...
[UE4SS] Recovered from signal 11 during mod execution, continuing to next mod.
[UE4SS] Mod 'ModName' crashed during startup, continuing to next mod.
```
Other mods will continue to load normally.

## AMP Server Setup

If you run your dedicated server through an AMP control panel, AMP overwrites the
server binary on every game update, which breaks the `LD_PRELOAD` setup. See
[docs/AMP-Setup.md](docs/AMP-Setup.md) for a wrapper-script + cronjob solution
that survives AMP updates.

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for the full changelog.

## Downloads

Download the latest build from the [Releases page](https://github.com/BlackBookOfficial/ue4ss-linux-palworld/releases/latest). Old releases are replaced with each new build.

