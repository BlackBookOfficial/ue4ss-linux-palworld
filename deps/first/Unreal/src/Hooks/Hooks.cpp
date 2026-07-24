/*
 *  Adding and removing detours:
 *  To add a detour:    1. Add its name in Constants.hpp to the list under RC_UE_HOOK_DETOUR_TARGETS
 *                          - This generates its EDetourTarget entry and its switch case in UnregisterCallback
 *                          - Similarly to UnregisterCallback, if you wanted to get rid of the 30+ functions for registering each
 *                              individual hook and type of hook and just use a single RegisterHook function that also uses a
 *                              generated switch statement and TDetourTraits, that's an option for the future.
 *                      2. If needed, define a subclass of TDetourInstance in DetourSubclass.hpp, like with the others. If it's not needed, skip this step.
 *                          - It's best to keep the constructor protected and friend GetDetourInstance, see all of the existing
 *                              subclasses for an example. This enforces singleton behavior.
 *                          - Overrides need to follow the contract of the functions they're overriding (accomplish the same things)
 *                      3. Define the detour's metadata in Metadata.hpp as an 'if constexpr' statement in GetDetourMetadata, this is where the target
 *                          RC::Function* and bShouldHook* are supplied
 *                      4. Define the detour's TDetourTraits in DetourTraits.hpp. The Signature should be the same as UE's signature wrapped
 *                          in an std::function, the Base should be the TDetourInstance with the appropriate EDetourTarget and the
 *                          Signature, and the Impl should be Base if you skipped step 2, or the name of the subclass if you didn't. Note that
 *                          if you didn't skip step 2, you'll need to forward declare the class at the top of the file next to the other forward
 *                          declarations.
 *                      5. If the detour returns a value other than bool, UObject*, or void, then extern its explicit template instantiation for
 *                          FCallbackIterationData in the header, and export it in CallbackIterationData.cpp (as the current ones do) so that mods that link against
 *                          UE4SS use the dll's template instantiation rather than making their own. This helps ABI compatibility and reduces compile
 *                          times for mods.
 * To remove a detour, remove its entry from RC_UE_HOOK_DETOUR_TARGETS, any subclasses, its metadata, and its TDetourTraits/forward declaration.
 */


#include <Unreal/Hooks/Hooks.hpp>
#include <Unreal/Hooks/Internal/DetourSubclasses.hpp>
#include <Unreal/Hooks/Internal/Metadata.hpp>

#pragma push_macro("ensure")
#undef ensure

namespace RC::Unreal::Hook
{

#ifndef __cpp_lib_atomic_shared_ptr
#error UEPseudo hooks require std::atomic<std::shared_ptr<T>> specialization for thread safety!
#endif

    std::vector<StaticStorage::RequiredObject> StaticStorage::RequiredObjectsForInit{};
    int32_t StaticStorage::NumRequiredObjectsConstructed{};
    bool StaticStorage::bAllRequiredObjectsConstructed{false};

    namespace I = RC::Unreal::Hook::Internal;

    using I::EHookType;
    using I::EDetourTarget;
    using I::EGlobalCallbackAttributeFlags;


    #pragma region StaticConstructObject

    auto RegisterStaticConstructObjectPreCallback(StaticConstructObjectPreCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::StaticConstructObject>()->AddCallback([callback](auto& info, const FStaticConstructObjectParameters& params){
            auto rval = callback(params);
            if(rval) info.TrySetReturnValue(rval);
        }, EHookType::Pre, {});
    }

    auto RegisterStaticConstructObjectPreCallback(StaticConstructObjectCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::StaticConstructObject>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterStaticConstructObjectPostCallback(StaticConstructObjectPostCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::StaticConstructObject>()->AddCallback([callback](auto& info, const FStaticConstructObjectParameters& params){
            auto rval = callback(params, info.GetOriginalFunctionCallResult());
            if(rval) info.TrySetReturnValue(rval);
        }, EHookType::Post, {});
    }

    auto RegisterStaticConstructObjectPostCallback(StaticConstructObjectCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::StaticConstructObject>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region ProcessEvent

    auto RegisterProcessEventPreCallback(ProcessEventCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessEvent>()->AddCallback([callback](auto& info, UObject* context, UFunction* function, void* args){
            callback(context, function, args);
        }, EHookType::Pre, {});
    }

    auto RegisterProcessEventPostCallback(ProcessEventCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessEvent>()->AddCallback([callback](auto& info, UObject* context, UFunction* function, void* args){
            callback(context, function, args);
        }, EHookType::Post, {});
    }

    auto RegisterProcessEventPreCallback(ProcessEventCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessEvent>()->AddCallback(std::move(Callback), EHookType::Pre, std::move(Options));
    }

    auto RegisterProcessEventPostCallback(ProcessEventCallbackWithData Callback, FCallbackOptions Options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessEvent>()->AddCallback(std::move(Callback), EHookType::Post, std::move(Options));
    }

    #pragma endregion

    #pragma region ProcessInternal

    auto RegisterProcessInternalPreCallback(ProcessInternalCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessInternal>()->AddCallback([callback](auto& info, UObject* context, FFrame& stack, void* result){
            callback(context, stack, result);
        }, EHookType::Pre, {});
    }

    auto RegisterProcessInternalPostCallback(ProcessInternalCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessInternal>()->AddCallback([callback](auto& info, UObject* context, FFrame& stack, void* result){
            callback(context, stack, result);
        }, EHookType::Post, {});
    }

    auto RegisterProcessInternalPreCallback(ProcessInternalCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessInternal>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterProcessInternalPostCallback(ProcessInternalCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessInternal>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region ProcessLocalScriptFunction

    auto RegisterProcessLocalScriptFunctionPreCallback(ProcessLocalScriptFunctionCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessLocalScriptFunction>()->AddCallback([callback](auto& info, UObject* context, FFrame& stack, void* result){
            callback(context, stack, result);
        }, EHookType::Pre, {});
    }

    auto RegisterProcessLocalScriptFunctionPostCallback(ProcessLocalScriptFunctionCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessLocalScriptFunction>()->AddCallback([callback](auto& info, UObject* context, FFrame& stack, void* result){
            callback(context, stack, result);
        }, EHookType::Post, {});
    }

    auto RegisterProcessLocalScriptFunctionPreCallback(ProcessLocalScriptFunctionCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessLocalScriptFunction>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterProcessLocalScriptFunctionPostCallback(ProcessLocalScriptFunctionCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessLocalScriptFunction>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region InitGameState

    auto RegisterInitGameStatePreCallback(InitGameStateCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::InitGameState>()->AddCallback([callback](auto& info, AGameModeBase* context){
            callback(context);
        }, EHookType::Pre, {});
    }

    auto RegisterInitGameStatePostCallback(InitGameStateCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::InitGameState>()->AddCallback([callback](auto& info, AGameModeBase* context){
            callback(context);
        }, EHookType::Post, {});
    }

    auto RegisterInitGameStatePreCallback(InitGameStateCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::InitGameState>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterInitGameStatePostCallback(InitGameStateCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::InitGameState>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region LoadMap

    auto RegisterLoadMapPreCallback(LoadMapCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::LoadMap>()->AddCallback([callback](auto& info, UEngine* context, FWorldContext& world, FURL url, UPendingNetGame* game, FString& error){
            auto rval = callback(context, world, url, game, error);
            if(rval.first) info.TrySetReturnValue(rval.second);
        }, EHookType::Pre, {});
    }

    auto RegisterLoadMapPostCallback(LoadMapCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::LoadMap>()->AddCallback([callback](auto& info, UEngine* context, FWorldContext& world, FURL url, UPendingNetGame* game, FString& error){
            auto rval = callback(context, world, url, game, error);
            if(rval.first) info.TrySetReturnValue(rval.second);
        }, EHookType::Post, {});
    }

    auto RegisterLoadMapPreCallback(LoadMapCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::LoadMap>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterLoadMapPostCallback(LoadMapCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::LoadMap>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region EngineTick

    auto RegisterEngineTickPreCallback(EngineTickCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::EngineTick>()->AddCallback([callback](auto& info, UEngine* context, float delta, bool idle){
            callback(context, delta);
        }, EHookType::Pre, {});
    }

    auto RegisterEngineTickPostCallback(EngineTickCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::EngineTick>()->AddCallback([callback](auto& info, UEngine* context, float delta, bool idle){
            callback(context, delta);
        }, EHookType::Post, {});
    }

    auto RegisterEngineTickPreCallback(EngineTickCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::EngineTick>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterEngineTickPostCallback(EngineTickCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::EngineTick>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region BeginPlay

    auto RegisterBeginPlayPreCallback(BeginPlayCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::BeginPlay>()->AddCallback([callback](auto& info, AActor* context){
            callback(context);
        }, EHookType::Pre, {});
    }

    auto RegisterBeginPlayPostCallback(BeginPlayCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::BeginPlay>()->AddCallback([callback](auto& info, AActor* context){
            callback(context);
        }, EHookType::Post, {});
    }

    auto RegisterBeginPlayPreCallback(BeginPlayCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::BeginPlay>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterBeginPlayPostCallback(BeginPlayCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::BeginPlay>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region EndPlay

    auto RegisterEndPlayPreCallback(EndPlayCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::EndPlay>()->AddCallback([callback](auto& info, AActor* actor, EEndPlayReason reason){
            callback(actor, reason);
        }, EHookType::Pre, {});
    }

    auto RegisterEndPlayPostCallback(EndPlayCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::EndPlay>()->AddCallback([callback](auto& info, AActor* actor, EEndPlayReason reason){
            callback(actor, reason);
        }, EHookType::Post, {});
    }

    auto RegisterEndPlayPreCallback(EndPlayCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::EndPlay>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterEndPlayPostCallback(EndPlayCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::EndPlay>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region AActorTick

    auto RegisterAActorTickPreCallback(AActorTickCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::AActorTick>()->AddCallback([callback](auto& info, AActor* context, float delta){
            callback(context, delta);
        }, EHookType::Pre, {});
    }

    auto RegisterAActorTickPostCallback(AActorTickCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::AActorTick>()->AddCallback([callback](auto& info, AActor* context, float delta){
            callback(context, delta);
        }, EHookType::Post, {});
    }

    auto RegisterAActorTickPreCallback(AActorTickCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::AActorTick>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterAActorTickPostCallback(AActorTickCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::AActorTick>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region GameViewportClientTick

    auto RegisterGameViewportClientTickPreCallback(GameViewportClientTickCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::GameViewportClientTick>()->AddCallback([callback](auto& info, UGameViewportClient* context, float delta){
            callback(context, delta);
        }, EHookType::Pre, {});
    }

    auto RegisterGameViewportClientTickPostCallback(GameViewportClientTickCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::GameViewportClientTick>()->AddCallback([callback](auto& info, UGameViewportClient* context, float delta){
            callback(context, delta);
        }, EHookType::Post, {});
    }

    auto RegisterGameViewportClientTickPreCallback(GameViewportClientTickCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::GameViewportClientTick>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterGameViewportClientTickPostCallback(GameViewportClientTickCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::GameViewportClientTick>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region CallFunctionByNameWithArguments

    auto RegisterCallFunctionByNameWithArgumentsPreCallback(CallFunctionByNameWithArgumentsCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::CallFunctionByNameWithArguments>()->AddCallback([callback](auto& info, UObject* Context, const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec){
            auto rval = callback(Context, Str, Ar, Executor, bForceCallWithNonExec);
            if(rval.first) info.TrySetReturnValue(rval.second);
        }, EHookType::Pre, {});
    }

    auto RegisterCallFunctionByNameWithArgumentsPostCallback(CallFunctionByNameWithArgumentsCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::CallFunctionByNameWithArguments>()->AddCallback([callback](auto& info, UObject* Context, const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec){
            auto rval = callback(Context, Str, Ar, Executor, bForceCallWithNonExec);
            if(rval.first) info.TrySetReturnValue(rval.second);
        }, EHookType::Post, {});
    }

    auto RegisterCallFunctionByNameWithArgumentsPreCallback(CallFunctionByNameWithArgumentsCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::CallFunctionByNameWithArguments>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterCallFunctionByNameWithArgumentsPostCallback(CallFunctionByNameWithArgumentsCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::CallFunctionByNameWithArguments>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region ULocalPlayerExec

    auto RegisterULocalPlayerExecPreCallback(ULocalPlayerExecCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ULocalPlayerExec>()->AddCallback([callback](auto& info, ULocalPlayer* Context, UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar){
            auto rval = callback(Context, InWorld, Cmd, Ar);
            if(!rval.ExecuteOriginalFunction) info.PreventOriginalFunctionCall();
            if(!rval.UseOriginalReturnValue) info.TrySetReturnValue(rval.NewReturnValue);
        }, EHookType::Pre, {});
    }

    auto RegisterULocalPlayerExecPostCallback(ULocalPlayerExecCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ULocalPlayerExec>()->AddCallback([callback](auto& info, ULocalPlayer* Context, UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar){
            auto rval = callback(Context, InWorld, Cmd, Ar);
            if(!rval.ExecuteOriginalFunction) info.PreventOriginalFunctionCall();
            if(!rval.UseOriginalReturnValue) info.TrySetReturnValue(rval.NewReturnValue);
        }, EHookType::Post, {});
    }

    auto RegisterULocalPlayerExecPreCallback(ULocalPlayerExecCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ULocalPlayerExec>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterULocalPlayerExecPostCallback(ULocalPlayerExecCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ULocalPlayerExec>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    auto RegisterFNameConstructorPreCallback(FNameConstructorCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::FNameConstructor>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterFNameConstructorPostCallback(FNameConstructorCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::FNameConstructor>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    #pragma region ProcessConsoleExec

    // Note - not the exact same semantically, non-globals aren't executed after globals and any may be the first when setting the return value,
    // but just like with all other detours, all registered callbacks are guaranteed to be called.

    auto RegisterProcessConsoleExecCallback(ProcessConsoleExecCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessConsoleExec>()->AddCallback([callback](auto& info, UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor){
            if(!Unreal::Cast<UGameViewportClient>(Context)) return;
            if(callback(Context, Cmd, Ar, Executor)) info.TrySetReturnValue(true);
        }, EHookType::Post, {});
    }

    auto RegisterProcessConsoleExecGlobalPreCallback(ProcessConsoleExecGlobalCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessConsoleExec>()->AddCallback([callback](auto& info, UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor){
            auto rval = callback(Context, Cmd, Ar, Executor);
            if(rval.first) info.TrySetReturnValue(rval.second);
        }, EHookType::Pre, {});
    }

    auto RegisterProcessConsoleExecGlobalPostCallback(ProcessConsoleExecGlobalCallback callback) -> void
    {
        I::GetDetourInstance<EDetourTarget::ProcessConsoleExec>()->AddCallback([callback](auto& info, UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor){
            auto rval = callback(Context, Cmd, Ar, Executor);
            if(rval.first) info.TrySetReturnValue(rval.second);
        }, EHookType::Post, {});
    }

    auto RegisterProcessConsoleExecCallback(ProcessConsoleExecCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessConsoleExec>()->AddCallback([callback](auto& info, UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor){
            if(!Unreal::Cast<UGameViewportClient>(Context)) return;
            callback(info, Context, Cmd, Ar, Executor);
        }, EHookType::Post, std::move(options));
    }

    auto RegisterProcessConsoleExecGlobalPreCallback(ProcessConsoleExecCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessConsoleExec>()->AddCallback(std::move(callback), EHookType::Pre, std::move(options));
    }

    auto RegisterProcessConsoleExecGlobalPostCallback(ProcessConsoleExecCallbackWithData callback, FCallbackOptions options) -> GlobalCallbackId
    {
        return I::GetDetourInstance<EDetourTarget::ProcessConsoleExec>()->AddCallback(std::move(callback), EHookType::Post, std::move(options));
    }

    #pragma endregion

    auto UnregisterCallback(const GlobalCallbackId Id) -> bool
    {
        switch(static_cast<EDetourTarget>(Id & I::DETOUR_MASK)) {
        #define RC_UNREGISTER_CASE(name, value) \
            case EDetourTarget::name: return I::GetDetourInstance<EDetourTarget::name>()->RemoveCallback(Id);
            RC_UE_HOOK_DETOUR_TARGETS(RC_UNREGISTER_CASE)
        #undef RC_UNREGISTER_CASE
        #ifdef UE_HOOK_TEST
            case EDetourTarget::NonVoidTest: return I::GetDetourInstance<EDetourTarget::NonVoidTest>()->RemoveCallback(Id);
            case EDetourTarget::VoidTest: return I::GetDetourInstance<EDetourTarget::VoidTest>()->RemoveCallback(Id);
        #endif
            default: {
                Output::send<LogLevel::Error>(STR("[UnregisterCallback] Failed to unregister hook with Id = {:#X}, detour = {:#X}, mask = {:#X} because the detour doesn't exist!\n"), Id, Id & I::DETOUR_MASK, I::DETOUR_MASK);
                return false;
            }
        }
    }

    auto StartCallbackGarbageCollector() -> bool
    {
        return I::FCallbackGarbageCollector::GetInstance()->StartGCThread();
    }

    auto StopCallbackGarbageCollector() -> bool
    {
        return I::FCallbackGarbageCollector::GetInstance()->StopGCThread();
    }

    auto AddRequiredObject(const std::vector<StringViewType>& ObjectFullTypelessName) -> void
    {
        std::vector<FName> NameParts{};
        for (const auto& NamePart : ObjectFullTypelessName)
        {
            // Try find first, and only add a new name if an existing name wasn't found.
            // This is because of a bug with FNAME_Add (perhaps wrong constructor found) that causes a new name to be created with a number instead of retrieving the existing one.
            auto NamePartName = FName(NamePart, FNAME_Find);
            if (NamePartName == NAME_None)
            {
                NamePartName = FName(NamePart, FNAME_Add);
            }
            NameParts.push_back(NamePartName);
        }
        if (!UObjectGlobals::StaticFindObject_InternalNoToStringFromNames(NameParts))
        {
            Output::send(STR("Need to construct: {}\n"), ObjectFullTypelessName);
            StaticStorage::RequiredObjectsForInit.emplace_back(Hook::StaticStorage::RequiredObject{NameParts});
            StaticStorage::bAllRequiredObjectsConstructed = false;
        }
        else
        {
            Output::send(STR("Already constructed: {}\n"), ObjectFullTypelessName);
            if (StaticStorage::RequiredObjectsForInit.size() == 0)
            {
                StaticStorage::bAllRequiredObjectsConstructed = true;
            }
        }
    }

    auto AllRequiredObjectsConstructed() -> bool
    {
        std::erase_if(StaticStorage::RequiredObjectsForInit, [&](StaticStorage::RequiredObject& RequiredObject) -> bool {
            return UObjectGlobals::StaticFindObject_InternalNoToStringFromNames(RequiredObject.ObjectNameParts);
        });

        StaticStorage::bAllRequiredObjectsConstructed = StaticStorage::RequiredObjectsForInit.size() == 0;
        return StaticStorage::bAllRequiredObjectsConstructed;
    }
}

auto RC::Unreal::HookStaticConstructObject() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::StaticConstructObject>::Impl::EnsureHooked();
}

auto RC::Unreal::HookProcessEvent() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::ProcessEvent>::Impl::EnsureHooked();
}

auto RC::Unreal::HookProcessConsoleExec() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::ProcessConsoleExec>::Impl::EnsureHooked();
}

auto RC::Unreal::HookUStructLink() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::UStructLink>::Impl::EnsureHooked();
}

auto RC::Unreal::HookProcessInternal() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::ProcessInternal>::Impl::EnsureHooked();
}

auto RC::Unreal::HookProcessLocalScriptFunction() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::ProcessLocalScriptFunction>::Impl::EnsureHooked();
}

auto RC::Unreal::HookLoadMap() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::LoadMap>::Impl::EnsureHooked();
}

auto RC::Unreal::HookEngineTick() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::EngineTick>::Impl::EnsureHooked();
}

auto RC::Unreal::HookInitGameState() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::InitGameState>::Impl::EnsureHooked();
}

auto RC::Unreal::HookBeginPlay() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::BeginPlay>::Impl::EnsureHooked();
}

auto RC::Unreal::HookEndPlay() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::EndPlay>::Impl::EnsureHooked();
}

auto RC::Unreal::HookAActorTick() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::AActorTick>::Impl::EnsureHooked();
}

auto RC::Unreal::HookGameViewportClientTick() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::GameViewportClientTick>::Impl::EnsureHooked();
}

auto RC::Unreal::HookCallFunctionByNameWithArguments() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::CallFunctionByNameWithArguments>::Impl::EnsureHooked();
}

auto RC::Unreal::HookULocalPlayerExec() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::ULocalPlayerExec>::Impl::EnsureHooked();
}

auto RC::Unreal::HookFNameConstructor() -> void
{
    Hook::Internal::TDetourTraits<Hook::EDetourTarget::FNameConstructor>::Impl::EnsureHooked();
}

#include <Unreal/Hooks/Internal/Testing.hpp>

#pragma pop_macro("ensure")