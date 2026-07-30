# Installation

> **This is a Linux-native build.** It uses `LD_PRELOAD` instead of proxy DLLs.
> Windows-specific instructions (`.dll`, `dwmapi.dll`, proxy injection) do not apply.

## Core structure concept

There are four concepts you need to know about.

1. The `root directory`.
    - This directory contains the `libUE4SS.so` file.
2. The `working directory`.
    - This directory contains configuration and mod files and is located inside the `root directory`.
3. The `game directory`.
    - This directory usually contains a small executable with the name of your game and a folder with the same name.
    - Example of a `game directory`: `/home/user/GameServer/`
4. The `game executable directory`.
    - This directory contains the real executable file for your game server.
    - Example of a `game executable directory`:
    `/home/user/GameServer/Binaries/Linux/`

## Installation

### Step 1: Download the latest release

Download `UE4SS-Linux-build.zip` from the [Releases page](https://github.com/BlackBookOfficial/ue4ss-linux-palworld/releases/latest).

### Step 2: Extract the archive

```bash
unzip UE4SS-Linux-build.zip
```

This will extract `libUE4SS.so`.

### Step 3: Copy `libUE4SS.so` to your game's binary directory

Place `libUE4SS.so` in the same directory as your game server executable.

Example for Palworld:
```bash
cp libUE4SS.so /path/to/PalServer/Binaries/Linux/
```

### Step 4: Set up the Mods directory

Create a `Mods` folder in the game's binary directory:
```bash
mkdir -p /path/to/PalServer/Binaries/Linux/Mods
```

Create a `mods.txt` file inside the `Mods` folder to specify which mods to load:
```bash
echo "UE4SSStatus : 1" > /path/to/PalServer/Binaries/Linux/Mods/mods.txt
```

Each line follows the format `ModName : 1` (enabled) or `ModName : 0` (disabled).

### Step 5: Set up Lua mods

Each mod goes in its own folder under `Mods/`:
```
Mods/
├── mods.txt
└── MyMod/
    └── scripts/
        └── main.lua
```

> **Note:** On Linux, directory names are **case-sensitive** — always use lowercase `scripts`.

### Step 6: Launch the server with LD_PRELOAD

Set the `LD_PRELOAD` environment variable to load UE4SS:
```bash
LD_PRELOAD=/path/to/libUE4SS.so ./PalServer-Linux-Shipping
```

Or set it in your server startup script / systemd service:
```bash
export LD_PRELOAD=/path/to/libUE4SS.so
```

### Optional: AMP Server Setup

If you run your dedicated server through an AMP control panel, see [AMP-Setup.md](./AMP-Setup.md) for a wrapper-script + cronjob solution that survives AMP updates.

## How to verify that UE4SS is running successfully?

Try any of the following:
* Check the server console output for `[UE4SS]` log messages.
* Check that the log file `UE4SS.log` is created in the same folder as `libUE4SS.so`, and that the log file contains fresh timestamps and no errors.
* Verify that `libUE4SS.so` is loaded in the process:
  ```bash
  PID=$(pgrep -f 'PalServer-Linux-Shipping' | head -1)
  cat /proc/$PID/maps | grep -i ue4ss
  ```

## Configuration

After installation, you can configure UE4SS through the `UE4SS-settings.ini` file.

### Multiple Mods Directories

You can load mods from multiple directories using the `UE4SS-settings.ini` file:

```ini
[Overrides]
; Add additional mods directories with + prefix, remove with - prefix
+ModsFolderPaths = ../SharedMods
+ModsFolderPaths = /home/user/MyMods
-ModsFolderPaths = ../SharedMods
```

INI paths are processed in the order they appear (last entry has highest priority).

Alternatively, use the `UE4SS_MODS_PATHS` environment variable with colon-separated paths on Linux:
```bash
export UE4SS_MODS_PATHS=/home/user/SharedMods:/home/user/GameMods
```

Environment variable paths are processed in reverse order (first entry has highest priority). Both INI and environment variable paths support relative and absolute paths, including symlinks.

### Controlling Mods List

By default, UE4SS parses the `mods.txt` file from each mods directory. You can override this to use a single controlling `mods.txt` file:

```ini
[Overrides]
; Path to a specific mods.txt file to use as the controlling mod list.
; If set, ONLY this mods.txt will be parsed instead of mods.txt from all mod directories.
; Can be relative to working directory or an absolute path.
ControllingModsTxt = ../MyModsList/mods.txt
```

This is useful when:
- Managing mod load order centrally across multiple mod directories
- Using a shared configuration for multiple game installations
- Keeping mod lists in version control separate from mod files

When `ControllingModsTxt` is empty (default), UE4SS will parse `mods.txt` from all configured mod directories.