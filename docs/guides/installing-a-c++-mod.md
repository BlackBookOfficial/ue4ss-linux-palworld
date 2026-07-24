# Installing a C++ Mod

1. This part assumes you have UE4SS installed and working for your game already. If not, refer to the [installation guide](../installation-guide.md). 

2. After building, you will have the following file:
    - `libMyAwesomeMod.so` in `MyMods/build/MyAwesomeMod/`
    
3. Navigate over to your game's executable folder and open the `Mods` folder. Here we'll do a couple things:  
    - Create a folder structure in `Mods` that looks like `MyAwesomeMod/libs`. 
    - Move `libMyAwesomeMod.so` inside the `libs` folder and rename it to `main.so`.

> NOTE: `libMyAwesomeMod.so` will also work and UE4SS will use `libMyAwesomeMod.so` if `main.so` isn't present.

The result should look like:
```
Mods/
    MyAwesomeMod/
        libs/
            main.so
```    

4. To enable loading of your mod in-game you will have to edit the `mods.txt` located in the `Mods` folder. By default it looks something like this:
```
CheatManagerEnablerMod : 1
ActorDumperMod : 0
ConsoleCommandsMod : 1
ConsoleEnablerMod : 1
SplitScreenMod : 0
LineTraceMod : 1
BPModLoaderMod : 1
jsbLuaProfilerMod : 0



; Built-in keybinds, do not move up!
Keybinds : 1
```

Here you will want to add the line: 
```
MyAwesomeMod : 1
```
**above** the keybinds to enable `MyAwesomeMod`.

Alternatively, place an empty text file named `enabled.txt` inside of the MyAwesomeMod folder.  This method is not recommended because it does not allow load ordering  
and bypasses mods.txt, but may allow for easier installation by end users.

5. Launch your game server with `LD_PRELOAD` set to `libUE4SS.so` and if everything was done correctly, you should see the text "MyAwesomeMod says hello" in the server console output (before all the scanning occurs), and if you used the `on_unreal_init` function, you should see "Object Name: /Script/CoreUObject.Object" as well (right after the scanning finishes).

## Automation

Now that you understand how the process works, you can use the [UE4SS CPP Template](https://github.com/UE4SS-RE/UE4SSCPPTemplate) repository that automates the process of creating a mod, building it, and installing it. Be aware that the setup script will checkout the commit at the latest release so that you can be sure that your mod is being built with the correct ABI as latest release. 

> NOTE: On Linux, C++ mods must be compiled as `.so` files (not `.dll`). The mod folder uses `libs/` instead of `dlls/`.