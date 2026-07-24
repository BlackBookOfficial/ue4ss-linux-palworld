#pragma once
#include <type_traits>
#include <Unreal/Hooks/Hooks.hpp>
#include <Unreal/Hooks/Internal/Constants.hpp>
#include <Function/Function.hpp>

namespace RC::Unreal::Hook::Internal
{
    // Forward declare any subclasses of TDetourInstance here.
#ifdef UE4SS_PROFILERS
    class FProcessEventDetour;
#endif
    class FProcessConsoleExecDetour;
    class FStaticConstructObjectDetour;
    class FULocalPlayerExecDetour;
    class FUStructLinkDetour;
    class FCallFunctionByNameWithArgumentsDetour;
    class FInitGameStateDetour;

    template<EDetourTarget DetourTarget, typename HookSig>
    class TDetourInstance;

    // Used to simplify various getters that respond differently to different TDetourInstances 
    // (currently GetDetourMetadata and GetDetourInstance), mainly to make maintainability easier.
    // Any new detours should declare their TDetourTraits in this file. Signature should be an std::function version
    // of the actual UE function, Base should be the TDetourInstance with the enum value and Signature, and Impl
    // should be either Base (if the default behavior of the template works) or the subclass for that detour.
    template<EDetourTarget Target>
    struct TDetourTraits;

    template<>
    struct TDetourTraits<EDetourTarget::AActorTick> 
    {
        using Signature = AActorTickSignature;
        using Base = TDetourInstance<EDetourTarget::AActorTick, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::BeginPlay> 
    {
        using Signature = BeginPlaySignature;
        using Base = TDetourInstance<EDetourTarget::BeginPlay, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::CallFunctionByNameWithArguments> 
    {
        using Signature = CallFunctionByNameWithArgumentsSignature;
        using Base = TDetourInstance<EDetourTarget::CallFunctionByNameWithArguments, Signature>;
        using Impl = FCallFunctionByNameWithArgumentsDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::EndPlay> 
    {
        using Signature = EndPlaySignature;
        using Base = TDetourInstance<EDetourTarget::EndPlay, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::EngineTick> 
    {
        using Signature = EngineTickSignature;
        using Base = TDetourInstance<EDetourTarget::EngineTick, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::GameViewportClientTick> 
    {
        using Signature = GameViewportClientTickSignature;
        using Base = TDetourInstance<EDetourTarget::GameViewportClientTick, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::InitGameState> 
    {
        using Signature = InitGameStateSignature;
        using Base = TDetourInstance<EDetourTarget::InitGameState, Signature>;
        using Impl = FInitGameStateDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::LoadMap> 
    {
        using Signature = LoadMapSignature;
        using Base = TDetourInstance<EDetourTarget::LoadMap, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::ProcessConsoleExec> 
    {
        using Signature = ProcessConsoleExecSignature;
        using Base = TDetourInstance<EDetourTarget::ProcessConsoleExec, Signature>;
        using Impl = FProcessConsoleExecDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::ProcessEvent>
    {
        using Signature = ProcessEventSignature;
        using Base = TDetourInstance<EDetourTarget::ProcessEvent, Signature>;
#ifdef UE4SS_PROFILERS
        using Impl = FProcessEventDetour;
#else
        using Impl = Base;
#endif
    };

    template<>
    struct TDetourTraits<EDetourTarget::ProcessInternal> 
    {
        using Signature = ProcessInternalSignature;
        using Base = TDetourInstance<EDetourTarget::ProcessInternal, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::ProcessLocalScriptFunction> 
    {
        using Signature = ProcessLocalScriptFunctionSignature;
        using Base = TDetourInstance<EDetourTarget::ProcessLocalScriptFunction, Signature>;
        using Impl = Base;
    };

    template<>
    struct TDetourTraits<EDetourTarget::StaticConstructObject> 
    {
        using Signature = StaticConstructObjectSignature;
        using Base = TDetourInstance<EDetourTarget::StaticConstructObject, Signature>;
        using Impl = FStaticConstructObjectDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::ULocalPlayerExec> 
    {
        using Signature = ULocalPlayerExecSignature;
        using Base = TDetourInstance<EDetourTarget::ULocalPlayerExec, Signature>;
        using Impl = FULocalPlayerExecDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::UStructLink> 
    {
        using Signature = std::function<void(UStruct*, FArchive&, bool)>;
        using Base = TDetourInstance<EDetourTarget::UStructLink, Signature>;
        using Impl = FUStructLinkDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::FNameConstructor>
    {
        using Signature = FNameConstructorSignature;
        using Base = TDetourInstance<EDetourTarget::FNameConstructor, Signature>;
        using Impl = Base;
    };

#ifdef UE_HOOK_TEST

    class TestVoidDetour;
    class TestNonVoidDetour;
    class FTestNonVoidDetourHolder;
    class FTestVoidDetourHolder;
        
    template<>
    struct TDetourTraits<EDetourTarget::NonVoidTest> 
    {
        using Signature = std::function<bool(FTestNonVoidDetourHolder*, int)>;
        using Base = TDetourInstance<EDetourTarget::NonVoidTest, Signature>;
        using Impl = TestNonVoidDetour;
    };

    template<>
    struct TDetourTraits<EDetourTarget::VoidTest> 
    {
        using Signature = std::function<void(FTestVoidDetourHolder*, int)>;
        using Base = TDetourInstance<EDetourTarget::VoidTest, Signature>;
        using Impl = TestVoidDetour;
    };

#endif

    template<typename Signature>
    struct TSignatureTraits;

    // Helper trait to get various useful signatures from the main std::function-ified UE signature.
    template<typename ReturnType, typename ...Args>
    struct TSignatureTraits<std::function<ReturnType(Args...)>> 
    {
        using rc_function_type = RC::Function<ReturnType(Args...)>;
        using callback_type = sig_to_callback_v<std::function<ReturnType(Args...)>>;
        using return_type = ReturnType;
    };
}