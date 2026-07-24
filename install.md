# UE4SS Linux Installation Guide

## Requirements

- Linux x86_64 (Ubuntu 22.04+, Debian 12+, or similar)
- The game server must be an Unreal Engine 4 game running on Linux

## Quick Start

### 1. Extract the build

```bash
unzip UE4SS-Linux-build.zip -d /opt/ue4ss
```

This will give you:

```
/opt/ue4ss/
├── libUE4SS.so          # The main UE4SS library
├── CHANGELOG.md         # Changelog
└── install.md           # This file
```

### 2. Set up the UE4SS directory in your game folder

Create a `UE4SS` folder inside your game server's directory:

```bash
mkdir -p /path/to/game/UE4SS/Mods
```

Create a minimal `UE4SS-settings.ini`:

```bash
cat > /path/to/game/UE4SS/UE4SS-settings.ini << 'EOF'
[Debug]
DebugConsoleEnabled=false
SimpleConsoleEnabled=true

[Overrides]
ModsFolderPath=./UE4SS/Mods
EOF
```

### 3. Start the game server with LD_PRELOAD

```bash
LD_PRELOAD=/opt/ue4ss/libUE4SS.so /path/to/game/GameServer-Linux-Shipping
```

Or set it as an environment variable:

```bash
export LD_PRELOAD=/opt/ue4ss/libUE4SS.so
/path/to/game/GameServer-Linux-Shipping
```

### 4. Verify it loaded

Check the log file:

```bash
cat /path/to/game/UE4SS/UE4SS.log
```

You should see UE4SS initialization messages.

## Installing Mods

### Lua Mods

Place Lua mods in the `Mods` directory:

```
/path/to/game/UE4SS/Mods/
├── MyLuaMod/
│   └── scripts/
│       └── main.lua
```

### C++ Mods

C++ mods must be compiled as `.so` files (not `.dll`):

```
/path/to/game/UE4SS/Mods/
├── MyCppMod/
│   └── dlls/
│       └── MyCppMod.so
```

## Integration with Server Managers

### AMP (CubeCoders)

**Method 1: Wrapper Script**

Create a wrapper script:

```bash
#!/bin/bash
export LD_PRELOAD=/opt/ue4ss/libUE4SS.so
exec "$@"
```

Save as `/opt/ue4ss/ue4ss-wrapper.sh` and make it executable:

```bash
chmod +x /opt/ue4ss/ue4ss-wrapper.sh
```

In AMP: Configuration -> Server -> Start-up Command, set it to:

```
/opt/ue4ss/ue4ss-wrapper.sh ./OriginalServerBinary
```

**Method 2: Environment Variable**

In AMP: Configuration -> Server -> Environment Variables, add:

```
LD_PRELOAD=/opt/ue4ss/libUE4SS.so
```

**Method 3: systemd Override**

```bash
systemctl edit amp@<instancename>.service
```

Add:

```ini
[Service]
Environment="LD_PRELOAD=/opt/ue4ss/libUE4SS.so"
```

Then:

```bash
systemctl daemon-reload
systemctl restart amp@<instancename>
```

### Pterodactyl Panel

Add the `LD_PRELOAD` environment variable in the server's startup settings:

```
LD_PRELOAD=/opt/ue4ss/libUE4SS.so
```

Or modify the startup command to include it.

### Docker

In your Dockerfile or docker-compose.yml:

```yaml
environment:
  - LD_PRELOAD=/opt/ue4ss/libUE4SS.so
```

Or with `docker run`:

```bash
docker run -e LD_PRELOAD=/opt/ue4ss/libUE4SS.so my-gameserver
```

### systemd Service

Create or edit a systemd service file:

```ini
[Unit]
Description=Game Server with UE4SS
After=network.target

[Service]
Environment="LD_PRELOAD=/opt/ue4ss/libUE4SS.so"
ExecStart=/path/to/game/GameServer-Linux-Shipping
WorkingDirectory=/path/to/game
Restart=on-failure

[Install]
WantedBy=multi-user.target
```

## Troubleshooting

### UE4SS doesn't load

- Verify the path to `libUE4SS.so` is absolute
- Check file permissions: `chmod 755 /opt/ue4ss/libUE4SS.so`
- Check if the game server process can read the file
- Look for error messages in the server console output

### No log file created

- Ensure the `UE4SS/` directory exists in the game server's working directory
- Check write permissions on the `UE4SS/` directory

### Mods not loading

- Verify the `Mods` folder path in `UE4SS-settings.ini`
- Check that mod folder structure is correct (`scripts/main.lua` for Lua mods)
- Check the UE4SS log for error messages

### Segfault on startup

- Ensure you are using the correct architecture (x86_64)
- Verify the game server is an Unreal Engine 4 game
- Check `dmesg` or `journalctl` for crash details

## Building from Source

### Prerequisites

- GCC 13+ or Clang 15+
- CMake 3.22+
- Ninja build system
- Lua 5.4 development headers
- fmt library
- Git

### Build Steps

```bash
git clone --recursive https://github.com/XarminaEu/ue4ss-linux.git
cd ue4ss-linux
git checkout linux-native
git submodule update --init --recursive

# Configure
cmake -B build_linux -G Ninja \
  -DCMAKE_BUILD_TYPE=Shipping \
  -DUE4SS_GUI_ENABLED=OFF \
  -DUE4SS_INPUT_ENABLED=OFF

# Build
cmake --build build_linux --target UE4SS
```

The built library will be at:

```
build_linux/Game__Shipping__Linux64/lib/libUE4SS.so
```

### Note on UEPseudo Submodule

The `deps/first/Unreal` submodule (UEPseudo) requires access to the Epic Games GitHub organization. You must join the Epic Games GitHub organization and clone the submodule separately.
