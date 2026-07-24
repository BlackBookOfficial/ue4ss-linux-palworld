# Blueprint Modloader

> **Linux Status:** Blueprint mod loading is fully supported in the Linux build, with two modes:
>
> ### Automatic mode (unstripped binaries)
> On unstripped Linux binaries, UE4SS automatically resolves all required function addresses via `dlsym`:
> - `GUObjectArray`, `FName::ToString`, `FName::FName`, `StaticConstructObject`, `GMalloc`, `GNatives`
> - `ProcessInternal`, `ProcessLocalScriptFunction`, `CallFunctionByNameWithArguments`
> - `UGameEngine::Tick`
>
> ### Manual mode (stripped binaries)
> On stripped binaries (most dedicated server builds), `dlsym` cannot find symbols. You can provide addresses manually via a `UE4SS_Addresses.ini` file in the UE4SS working directory:
>
> ```ini
> [Addresses]
> GUObjectArray = 0x7f1234567890
> FNameToString = 0x7f12345678a0
> FNameConstructor = 0x7f12345678b0
> StaticConstructObject = 0x7f12345678c0
> GMalloc = 0x7f12345678d0
> GNatives = 0x7f12345678e0
> UGameEngineTick = 0x7f12345678f0
> ProcessInternal = 0x7f1234567900
> ProcessLocalScriptFunction = 0x7f1234567910
> CallFunctionByNameWithArguments = 0x7f1234567920
> ```
>
> You can find these addresses using tools like `objdump`, `nm`, or a debugger (GDB) on the game binary.
>
> ### Required hooks
> The following hooks must be enabled in `UE4SS-settings.ini`:
> - `HookLoadMap=true`
> - `HookBeginPlay=true`
> - `HookProcessInternal=true`
>
> ### Blueprint mod installation
> Blueprint `.pak` files must be placed in `Content/Paks/LogicMods/` relative to the game's content directory.

As our BP system is based on RussellJ's, this tutorial video is applicable for creating a blueprint mod for UE4SS:

<iframe width="560" height="315" src="https://www.youtube.com/embed/fB3yT85XhVA?si=Hvu0wHmcFxFT2MA_" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>