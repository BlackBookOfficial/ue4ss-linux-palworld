# Custom Game Configs

> [!IMPORTANT]
> Some of these files may be out of date as the games/UE4SS updates. If you find that a game's custom game config is out of date, please open an issue on the [ue4ss-linux repository](https://github.com/XarminaEu/ue4ss-linux/issues). Make sure that you first test if the game works without the custom game config, as it may have been fixed in the latest version of UE4SS.

These settings are for games that have altered the engine in ways that make UE4SS not work out of the box.  

You need to download the files from each folder for your game and place them in the same folder in your UE4SS installation. For example, downloading the configs for Kingdom Hearts 3 should result in your files being in the following structure:

```
Binaries/Linux/
├── CustomGameConfigs/
│   └── Kingdom Hearts 3/
│       ├── UE4SS_Signatures/
│       │   ├── FName_Constructor.lua
│       │   ├── FName_ToString.lua
│       │   ├── StaticConstructObject.lua
│       ├── MemberVariableLayout.ini
│       ├── UE4SS-settings.ini
│       ├── VTableLayout.ini
```

... but obviously the file structure will change depending on the game's configs.