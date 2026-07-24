#pragma once
#include <concepts>
#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

#include <Unreal/AActor.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/FFrame.hpp>
#include <Unreal/FURL.hpp>
#include <Unreal/UFunctionStructs.hpp>
#include <Unreal/Hooks/Internal/Common.hpp>
#include <Unreal/Hooks/CallbackIterationData.hpp>
#include <Unreal/Hooks/Internal/Constants.hpp>
#include <Unreal/Hooks/GlobalCallbackId.hpp>

#include <Helpers/String.hpp>
#include <String/StringType.hpp>
#pragma push_macro("ensure")
#undef ensure

//NOTE would be nice in the future to make abstract rcu container
//NOTE dumping all metadata on crashes would also be nice
//NOTE another possible 'nice' thing: using TDetourTraits to define a StaticInvoker struct that holds the static function
//      that gets detoured to, then making DetourInstance inherit from it so that its template argument can just be EDetourTarget
//      rather than the whole signature/type deduction combo

#define DEPRECATED_HOOK_CALLBACK [[deprecated("Metadata-less hooks are deprecated and less efficient, use the 'WithData' callback overload instead!")]]

namespace PLH
{
    class x64Detour;
}

namespace RC::LuaMadeSimple
{
    class Lua;
}

namespace RC::Unreal::Hook::Internal
{
    struct FCallbackMetadata;
}

namespace RC::Unreal
{
    class UClass;
    class UFunction;
    class AGameModeBase;
    class AActor;
    class ULocalPlayer;
    class UWorld;
    class UEngine;
    class UPendingNetGame;
    class UGameViewportClient;
    struct FWorldContext;
    struct FStaticConstructObjectParameters;

    namespace Hook
    {
        template<typename ReturnType>
        concept CVoidReturnType = std::is_void_v<ReturnType>;

        template<typename ReturnType>
        concept CNonVoidReturnType = !CVoidReturnType<ReturnType>;

        #pragma region Interfaces and Structs

        // Options for registering callbacks. Default constructible, but highly recommended to set at least
        // OwnerModName and HookName for debugging and logging; this will make finding issues
        // and conflicts much easier, especially if an end user can supply a log.
        struct RC_UE_API FCallbackOptions
        {
            // Set to true to only execute this callback once, then automatically remove it.
            bool bOnce = false;

            // Set to true to ensure that this callback executes after all other callbacks of the same type
            // (meaning that if it's a posthook, it executes after all other posthook callbacks, and if it's
            // a prehook, it executes after all other prehook callbacks) and that it won't modify the return
            // value or try to prevent the original function call, or otherwise call any non-const function
            // of ICallbackIterationData
            bool bReadonly = false;

            // Set to the name of the registering mod for logging/debugging
            StringType OwnerModName;

            // Set the name of this particular callback for logging/debugging
            StringType HookName;
        };

        #pragma endregion

        #pragma region Hook Signatures
        using ProcessEventSignature = std::function<void(UObject* Context, UFunction* Function, void* Parms)>;
        using StaticConstructObjectSignature = std::function<UObject*(const FStaticConstructObjectParameters& Params)>;
        using StaticConstructObjectDeprecatedSignature = std::function<UObject*(StaticConstructObject_Internal_Params_Deprecated)>;
        using ProcessConsoleExecGlobalSignature = std::function<bool(UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)>;
        using ProcessConsoleExecSignature = std::function<bool(UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)>;
        using ProcessInternalSignature = std::function<void(UObject* Context, FFrame& Stack, void* RESULT_DECL)>;
        using ProcessLocalScriptFunctionSignature = std::function<void(UObject* Context, FFrame& Stack, void* RESULT_DECL)>;
        using InitGameStateSignature = std::function<void(AGameModeBase* Context)>;
        using LoadMapSignature = std::function<bool(UEngine*, FWorldContext& WorldContext, FURL URL, UPendingNetGame* PendingGame, FString& Error)>;
        using EngineTickSignature = std::function<void(UEngine* Context, float DeltaSeconds, bool bIdleMode)>;
        using BeginPlaySignature = std::function<void(AActor* Context)>;
        using EndPlaySignature = std::function<void(AActor* Context, EEndPlayReason EndPlayReason)>;
        using AActorTickSignature = std::function<void(AActor* Context, float DeltaSeconds)>;
        using GameViewportClientTickSignature = std::function<void(UGameViewportClient* Context, float DeltaSeconds)>;
        using CallFunctionByNameWithArgumentsSignature = std::function<bool(UObject* Context, const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec)>;
        using ULocalPlayerExecSignature = std::function<bool(ULocalPlayer* Context, UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)>;
        using FNameConstructorSignature = std::function<FName(const CharType*, EFindName)>;
        #pragma endregion

        #pragma region Callback Signatures

        template<typename Signature>
        struct sig_to_callback_t;

        template<typename ReturnType, typename ...Args>
        struct sig_to_callback_t<std::function<ReturnType(Args...)>>
        {
            using value = std::function<void(TCallbackIterationData<ReturnType>&, Args...)>;
        };

        template<typename Signature>
        using sig_to_callback_v = sig_to_callback_t<Signature>::value;

        using ProcessEventCallbackWithData = sig_to_callback_v<ProcessEventSignature>;
        using StaticConstructObjectCallbackWithData = sig_to_callback_v<StaticConstructObjectSignature>;
        using StaticConstructObjectDeprecatedCallbackWithData = sig_to_callback_v<StaticConstructObjectDeprecatedSignature>;
        using ProcessConsoleExecCallbackWithData = sig_to_callback_v<ProcessConsoleExecSignature>;
        using ProcessInternalCallbackWithData = sig_to_callback_v<ProcessInternalSignature>;
        using ProcessLocalScriptFunctionCallbackWithData = sig_to_callback_v<ProcessLocalScriptFunctionSignature>;
        using InitGameStateCallbackWithData = sig_to_callback_v<InitGameStateSignature>;
        using LoadMapCallbackWithData = sig_to_callback_v<LoadMapSignature>;
        using EngineTickCallbackWithData = sig_to_callback_v<EngineTickSignature>;
        using BeginPlayCallbackWithData = sig_to_callback_v<BeginPlaySignature>;
        using EndPlayCallbackWithData = sig_to_callback_v<EndPlaySignature>;
        using AActorTickCallbackWithData = sig_to_callback_v<AActorTickSignature>;
        using GameViewportClientTickCallbackWithData = sig_to_callback_v<GameViewportClientTickSignature>;
        using CallFunctionByNameWithArgumentsCallbackWithData = sig_to_callback_v<CallFunctionByNameWithArgumentsSignature>;
        using ULocalPlayerExecCallbackWithData = sig_to_callback_v<ULocalPlayerExecSignature>;
        using FNameConstructorCallbackWithData = sig_to_callback_v<FNameConstructorSignature>;

        #pragma endregion

        #pragma region Deprecated Callback Signatures
        using ProcessEventCallback = std::function<void(UObject* Context, UFunction* Function, void* Parms)>;
        using StaticConstructObjectPreCallback = std::function<UObject*(const FStaticConstructObjectParameters& Params)>;
        using StaticConstructObjectPostCallback = std::function<UObject*(const FStaticConstructObjectParameters& Params, UObject* ConstructedObject)>;
        using ProcessConsoleExecGlobalCallback = std::function<std::pair<bool, bool>(UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)>;
        using ProcessConsoleExecCallback = std::function<bool(UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)>;
        using ProcessInternalCallback = std::function<void(UObject* Context, FFrame& Stack, void* RESULT_DECL)>;
        using ProcessLocalScriptFunctionCallback = std::function<void(UObject* Context, FFrame& Stack, void* RESULT_DECL)>;
        using InitGameStateCallback = std::function<void(AGameModeBase* Context)>;
        using LoadMapCallback = std::function<std::pair<bool, bool>(UEngine*, FWorldContext& WorldContext, FURL URL, UPendingNetGame* PendingGame, FString& Error)>;
        using EngineTickCallback = std::function<void(UEngine* Context, float DeltaSeconds)>;
        using BeginPlayCallback = std::function<void(AActor* Context)>;
        using EndPlayCallback = std::function<void(AActor* Context, EEndPlayReason EndPlayReason)>;
        using AActorTickCallback = std::function<void(AActor* Context, float DeltaSeconds)>;
        using GameViewportClientTickCallback = std::function<void(UGameViewportClient* Context, float DeltaSeconds)>;
        using CallFunctionByNameWithArgumentsCallback = std::function<std::pair<bool, bool>(UObject* Context, const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec)>;
        struct ULocalPlayerExecCallbackReturnValue { bool UseOriginalReturnValue{true}; bool NewReturnValue{}; bool ExecuteOriginalFunction{true}; };
        using ULocalPlayerExecCallback = std::function<ULocalPlayerExecCallbackReturnValue(ULocalPlayer* Context, UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)>;
        #pragma endregion

        #pragma region API

        struct RC_UE_API StaticStorage
        {
            struct RequiredObject
            {
                std::vector<FName> ObjectNameParts{};
                bool ObjectConstructed{false};
            };

            static std::vector<RequiredObject> RequiredObjectsForInit;
            static int32_t NumRequiredObjectsConstructed;
            static bool bAllRequiredObjectsConstructed;
        };

        auto RC_UE_API AddRequiredObject(const std::vector<StringViewType>& ObjectFullTypelessName) -> void;
        auto RC_UE_API AllRequiredObjectsConstructed() -> bool;

        // Registers a callback to be called whenever 'StaticConstructObject' is called
        // Callbacks may alter the return value of 'StaticConstructObject', and the last one to alter it is the one that takes effect
        // Alterations to parameters in the 'pre' callback are applied prior to object construction
        // Alterations to parameters in the 'post' callback have no effect
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterStaticConstructObjectPreCallback(StaticConstructObjectPreCallback) -> void;
        auto RC_UE_API RegisterStaticConstructObjectPreCallback(StaticConstructObjectCallbackWithData, FCallbackOptions) -> GlobalCallbackId;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterStaticConstructObjectPostCallback(StaticConstructObjectPostCallback) -> void;
        auto RC_UE_API RegisterStaticConstructObjectPostCallback(StaticConstructObjectCallbackWithData, FCallbackOptions) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'ProcessEvent' is called
        // Callbacks may not alter the return value 'ProcessEvent', because there is no return value
        // Alterations to parameters in the 'pre' callback are applied prior to object construction
        // Alterations to parameters in the 'post' callback have no effect
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessEventPreCallback(ProcessEventCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessEventPostCallback(ProcessEventCallback Callback) -> void;
        auto RC_UE_API RegisterProcessEventPreCallback(ProcessEventCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterProcessEventPostCallback(ProcessEventCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'UGameViewportClient::ProcessConsoleExec' is executed
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessConsoleExecCallback(ProcessConsoleExecCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessConsoleExecGlobalPreCallback(ProcessConsoleExecGlobalCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessConsoleExecGlobalPostCallback(ProcessConsoleExecGlobalCallback Callback) -> void;
        auto RC_UE_API RegisterProcessConsoleExecCallback(ProcessConsoleExecCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterProcessConsoleExecGlobalPreCallback(ProcessConsoleExecCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterProcessConsoleExecGlobalPostCallback(ProcessConsoleExecCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'ProcessInternal' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessInternalPreCallback(ProcessInternalCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessInternalPostCallback(ProcessInternalCallback Callback) -> void;
        auto RC_UE_API RegisterProcessInternalPreCallback(ProcessInternalCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterProcessInternalPostCallback(ProcessInternalCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'ProcessLocalScriptFunction' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessLocalScriptFunctionPreCallback(ProcessLocalScriptFunctionCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterProcessLocalScriptFunctionPostCallback(ProcessLocalScriptFunctionCallback Callback) -> void;
        auto RC_UE_API RegisterProcessLocalScriptFunctionPreCallback(ProcessLocalScriptFunctionCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterProcessLocalScriptFunctionPostCallback(ProcessLocalScriptFunctionCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'InitGameState' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterInitGameStatePreCallback(InitGameStateCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterInitGameStatePostCallback(InitGameStateCallback Callback) -> void;
        auto RC_UE_API RegisterInitGameStatePreCallback(InitGameStateCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterInitGameStatePostCallback(InitGameStateCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'LoadMap' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterLoadMapPreCallback(LoadMapCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterLoadMapPostCallback(LoadMapCallback Callback) -> void;
        auto RC_UE_API RegisterLoadMapPreCallback(LoadMapCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterLoadMapPostCallback(LoadMapCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'UEngine::Tick' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterEngineTickPreCallback(EngineTickCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterEngineTickPostCallback(EngineTickCallback Callback) -> void;
        auto RC_UE_API RegisterEngineTickPreCallback(EngineTickCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterEngineTickPostCallback(EngineTickCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'BeginPlay' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterBeginPlayPreCallback(BeginPlayCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterBeginPlayPostCallback(BeginPlayCallback Callback) -> void;
        auto RC_UE_API RegisterBeginPlayPreCallback(BeginPlayCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterBeginPlayPostCallback(BeginPlayCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'EndPlay' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterEndPlayPreCallback(EndPlayCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterEndPlayPostCallback(EndPlayCallback Callback) -> void;
        auto RC_UE_API RegisterEndPlayPreCallback(EndPlayCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterEndPlayPostCallback(EndPlayCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'AActor::Tick' is called
        // WARNING! Be careful when hooking any 'Tick' functions because they are extremely performance sensitive.
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterAActorTickPreCallback(AActorTickCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterAActorTickPostCallback(AActorTickCallback Callback) -> void;
        auto RC_UE_API RegisterAActorTickPreCallback(AActorTickCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterAActorTickPostCallback(AActorTickCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'GameViewportClient::Tick' is called
        // WARNING! Be careful when hooking any 'Tick' functions because they are extremely performance sensitive.
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterGameViewportClientTickPreCallback(GameViewportClientTickCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterGameViewportClientTickPostCallback(GameViewportClientTickCallback Callback) -> void;
        auto RC_UE_API RegisterGameViewportClientTickPreCallback(GameViewportClientTickCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterGameViewportClientTickPostCallback(GameViewportClientTickCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'CallFunctionByNameWithArguments' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterCallFunctionByNameWithArgumentsPreCallback(CallFunctionByNameWithArgumentsCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterCallFunctionByNameWithArgumentsPostCallback(CallFunctionByNameWithArgumentsCallback Callback) -> void;
        auto RC_UE_API RegisterCallFunctionByNameWithArgumentsPreCallback(CallFunctionByNameWithArgumentsCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterCallFunctionByNameWithArgumentsPostCallback(CallFunctionByNameWithArgumentsCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Registers a callback to be called whenever 'CallFunctionByNameWithArguments' is called
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterULocalPlayerExecPreCallback(ULocalPlayerExecCallback Callback) -> void;
        DEPRECATED_HOOK_CALLBACK auto RC_UE_API RegisterULocalPlayerExecPostCallback(ULocalPlayerExecCallback Callback) -> void;
        auto RC_UE_API RegisterULocalPlayerExecPreCallback(ULocalPlayerExecCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterULocalPlayerExecPostCallback(ULocalPlayerExecCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        auto RC_UE_API RegisterFNameConstructorPreCallback(FNameConstructorCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;
        auto RC_UE_API RegisterFNameConstructorPostCallback(FNameConstructorCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId;

        // Attempts to unregister a callback with the given GlobalCallbackId
        // NEVER CALL THIS FROM WITHIN A CALLBACK - IT WILL DEADLOCK!!!
        // Use the function RemoveSelf in the FCallbackIterationData that gets passed into your callback.
        auto RC_UE_API UnregisterCallback(GlobalCallbackId Id) -> bool;

        auto RC_UE_API StartCallbackGarbageCollector() -> bool;
        auto RC_UE_API StopCallbackGarbageCollector() -> bool;
    }

    // For some reason these are exported, forward to new objects for compatibility
    auto RC_UE_API HookStaticConstructObject() -> void;
    auto RC_UE_API HookProcessEvent() -> void;
    auto RC_UE_API HookProcessConsoleExec() -> void;
    auto RC_UE_API HookUStructLink() -> void;
    auto RC_UE_API HookProcessInternal() -> void;
    auto RC_UE_API HookProcessLocalScriptFunction() -> void;
    auto RC_UE_API HookLoadMap() -> void;
    auto RC_UE_API HookEngineTick() -> void;
    auto RC_UE_API HookInitGameState() -> void;
    auto RC_UE_API HookBeginPlay() -> void;
    auto RC_UE_API HookEndPlay() -> void;
    auto RC_UE_API HookAActorTick() -> void;
    auto RC_UE_API HookGameViewportClientTick() -> void;
    auto RC_UE_API HookCallFunctionByNameWithArguments() -> void;
    auto RC_UE_API HookULocalPlayerExec() -> void;
    auto RC_UE_API HookFNameConstructor() -> void;

    #pragma endregion

#ifdef UE_HOOK_TEST
    auto RC_UE_API StartTests() -> bool;
#endif
}

#undef DEPRECATED_HOOK_CALLBACK
#pragma pop_macro("ensure")
