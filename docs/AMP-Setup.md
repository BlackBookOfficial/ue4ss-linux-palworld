# UE4SS Linux (.so) Integration for Palworld AMP Servers

## Problem
AMP overwrites the server binary `PalServer-Linux-Shipping` on every Palworld update.
This destroys the wrapper, and `libUE4SS.so` no longer gets loaded.
AMP does not provide a post-update hook to automatically repair this.

## Solution: Binary Wrapper + Cronjob Auto-Repair

---

### Step 1: Place libUE4SS.so

The `.so` must be located in the same directory as the server binary:

```
<AMP-Instance>/palworld/2394010/Pal/Binaries/Linux/libUE4SS.so
```

Example for an instance named `MyServer01`:
```
/home/amp/.ampdata/instances/MyServer01/palworld/2394010/Pal/Binaries/Linux/libUE4SS.so
```

### Step 2: Create UE4SS-settings.ini

UE4SS looks for the config in multiple locations. Create it here:

```
<Path>/Pal/Binaries/Linux/UE4SS-settings.ini
<Path>/Pal/Binaries/Linux/ue4ss/UE4SS-settings.ini
```

Example content (hooks disabled for initial testing):
```ini
[Overrides]
; ModsFolderPath=./Mods

[General]
EnableHotReloadSystem=false
EnableAutoReloadingLuaMods=false
UseCache=true
InvalidateCacheIfDLLDiffers=true
EnableDebugKeyBindings=false
SecondsToScanBeforeGivingUp=30
bUseUObjectArrayCache=false
DoEarlyScan=false
bEnableSeachByMemoryAddress=false
DefaultExecuteInGameThreadMethod=GameThread

[Debug]
DebugConsoleEnabled=false
SimpleConsoleEnabled=true

[Threads]
SigScannerNumThreads=-1
SigScannerMultithreadingModuleSizeThreshold=104857600

[Hooks]
HookProcessInternal=false
HookProcessLocalScriptFunction=false
HookLoadMap=false
HookInitGameState=false
HookCallFunctionByNameWithArguments=false
HookBeginPlay=false
HookEndPlay=false
```

> Once the server is running stably, hooks can be enabled one by one by setting them to `true`.

### Step 3: Wrap the Server Binary

The original binary is renamed and replaced with a wrapper script:

```bash
cd /home/amp/.ampdata/instances/<YourInstanceName>/palworld/2394010/Pal/Binaries/Linux

# Rename the original binary (only if it's still an ELF, not already a script)
file PalServer-Linux-Shipping | grep -q ELF && mv PalServer-Linux-Shipping PalServer-Linux-Shipping.real

# Create the wrapper script
cat > PalServer-Linux-Shipping << 'WRAPPER'
#!/bin/bash
SCRIPT_DIR="/AMP/palworld/2394010/Pal/Binaries/Linux"
if [ ! -e "$SCRIPT_DIR/PalServer-Linux-Shipping.real" ]; then
    SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
fi
export LC_ALL=C.UTF-8
export LANG=C.UTF-8
export LD_PRELOAD="$SCRIPT_DIR/libUE4SS.so"
export LD_LIBRARY_PATH="$SCRIPT_DIR:$LD_LIBRARY_PATH"
exec -a "PalServer-Linux-Shipping" "$SCRIPT_DIR/PalServer-Linux-Shipping.real" "$@"
WRAPPER

chmod +x PalServer-Linux-Shipping
chown amp:amp PalServer-Linux-Shipping PalServer-Linux-Shipping.real
```

### Step 4: Cronjob for Auto-Repair After Updates

Since AMP overwrites the binary on updates, you need a cronjob that
checks whether the wrapper is still in place and recreates it if needed.

#### 4a: Create the Repair Script

```bash
cat > /opt/ue4ss/repair-wrapper.sh << 'REPAIR'
#!/bin/bash
# Checks all AMP Palworld instances for a missing UE4SS wrapper
# and restores it if necessary.

INSTANCES_DIR="/home/amp/.ampdata/instances"

for INSTANCE in "$INSTANCES_DIR"/*/; do
    BIN_DIR="${INSTANCE}palworld/2394010/Pal/Binaries/Linux"

    # Skip if not a Palworld server
    [ ! -d "$BIN_DIR" ] && continue

    # Skip if no libUE4SS.so is present
    [ ! -f "$BIN_DIR/libUE4SS.so" ] && continue

    BIN="$BIN_DIR/PalServer-Linux-Shipping"

    # If PalServer-Linux-Shipping is an ELF binary (not a script),
    # it was overwritten by an update -> recreate the wrapper
    if file "$BIN" 2>/dev/null | grep -q 'ELF'; then
        echo "[$(date)] Wrapper missing in $BIN_DIR -> repairing..."
        mv "$BIN" "$BIN_DIR/PalServer-Linux-Shipping.real"
        cat > "$BIN" << 'WRAPPER'
#!/bin/bash
SCRIPT_DIR="/AMP/palworld/2394010/Pal/Binaries/Linux"
if [ ! -e "$SCRIPT_DIR/PalServer-Linux-Shipping.real" ]; then
    SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
fi
export LC_ALL=C.UTF-8
export LANG=C.UTF-8
export LD_PRELOAD="$SCRIPT_DIR/libUE4SS.so"
export LD_LIBRARY_PATH="$SCRIPT_DIR:$LD_LIBRARY_PATH"
exec -a "PalServer-Linux-Shipping" "$SCRIPT_DIR/PalServer-Linux-Shipping.real" "$@"
WRAPPER
        chmod +x "$BIN"
        chown amp:amp "$BIN" "$BIN_DIR/PalServer-Linux-Shipping.real"
        echo "[$(date)] Wrapper restored in $BIN_DIR"
    fi
done
REPAIR

chmod +x /opt/ue4ss/repair-wrapper.sh
```

#### 4b: Set Up the Cronjob (as root)

```bash
# Open the crontab
crontab -e

# Add this line (checks every 5 minutes):
*/5 * * * * /opt/ue4ss/repair-wrapper.sh >> /var/log/ue4ss-repair.log 2>&1
```

#### 4c: Check the Log

```bash
tail -f /var/log/ue4ss-repair.log
```

---

### Step 5: Start the Server and Verify

1. In AMP: Start the instance.
2. Check whether the `.so` was loaded:

```bash
# Find the PID of the server process
PID=$(pgrep -f 'PalServer-Linux-Shipping' | head -1)

# Check LD_PRELOAD in the process environment
cat /proc/$PID/environ | tr '\0' '\n' | grep LD_PRELOAD

# Check whether libUE4SS.so is in the memory maps
cat /proc/$PID/maps | grep -i ue4ss

# Alternatively: lsof
lsof -p $PID | grep -i ue4ss
```

3. Check the AMP console for:
```
[UE4SS] Library loaded via LD_PRELOAD, starting initialization thread...
[UE4SS] Detected game executable: /AMP/palworld/2394010/Pal/Binaries/Linux/PalServer-Linux-Shipping.real
```

---

### Troubleshooting

| Symptom | Cause | Solution |
|---------|-------|----------|
| Server doesn't start at all (Unable to run) | `libUE4SS.so` crashes on load | `.so` version incompatible, try an older/newer version |
| Exit Code 139 (Segfault) | UE4SS hooks incompatible with the Palworld build | Set all hooks to `false` in `UE4SS-settings.ini` |
| `GLIBC_2.38 not found` | System glibc is too old | Use a newer Linux distribution or a more compatible `.so` version |
| Wrapper gone after update | AMP overwrote the binary | Set up the cronjob from Step 4 |
| `[UE4SS]` doesn't appear in the log | `LD_PRELOAD` is not being set | Check whether `PalServer-Linux-Shipping` is a script (`file` command) |

---

### How It Works (Summary)

```
AMP starts -> PalServer-Linux-Shipping (wrapper script)
                       |
                       v
            sets LD_PRELOAD=libUE4SS.so
                       |
                       v
            exec PalServer-Linux-Shipping.real (original binary)
                       |
                       v
            Linux loads libUE4SS.so BEFORE the server
                       |
                       v
            UE4SS hooks into the Unreal Engine
```

`LD_PRELOAD` ensures that `libUE4SS.so` is loaded as the very first
library, before the server itself starts. This allows UE4SS to hook
into the process and register mods/hooks.
