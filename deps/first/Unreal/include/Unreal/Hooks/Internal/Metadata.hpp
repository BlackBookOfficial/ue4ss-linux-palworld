#pragma once
#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <concepts>
#include <type_traits>

#include <Unreal/Hooks/Internal/Common.hpp>
#include <Unreal/Hooks/Hooks.hpp>
#include <Unreal/Hooks/Internal/Constants.hpp>
#include <Unreal/Hooks/Internal/DetourTraits.hpp>

#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UnrealInitializer.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/UGameViewportClient.hpp>
#include <Unreal/Searcher/ObjectSearcher.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/UEngine.hpp>
#include <Unreal/AGameModeBase.hpp>
#include <Unreal/ULocalPlayer.hpp>


namespace RC::Unreal::Hook::Internal
{
    #ifdef UE_HOOK_TEST
    class FTestVoidDetourHolder;
    class FTestNonVoidDetourHolder;
    #endif

    // Metadata for registered callbacks, simple, untemplated structure that gets passed into ICallbackIterationData for metadata access. 
    struct RC_UE_API FCallbackMetadata  {
        GlobalCallbackId Id{};
        StringType OwnerModName;
        StringType HookName;
        // Packed state for executor-count + invalidation flag.
        // High bit: invalid (1 = invalid/removed)
        // Low 63 bits: number of threads currently executing this callback
        static constexpr uint64_t INVALID_BIT = 1ull << 63;
        static constexpr uint64_t EXECUTOR_MASK = ~INVALID_BIT;

        std::atomic<uint64_t> State{0};

        [[nodiscard]] bool IsInvalid(const std::memory_order order = std::memory_order_acquire) const noexcept
        {
            return (State.load(order) & INVALID_BIT) != 0;
        }

        [[nodiscard]] uint64_t GetExecutorCount(const std::memory_order order = std::memory_order_acquire) const noexcept
        {
            return State.load(order) & EXECUTOR_MASK;
        }

        // Attempts to begin executing this callback.
        // If bOnce is true, this also atomically claims the callback (sets invalid) so exactly one thread executes it.
        // Returns true iff the caller should proceed to execute the callback.
        [[nodiscard]] bool TryBeginExecution(const bool bOnce, bool& out_invalidated_by_once) noexcept
        {
            out_invalidated_by_once = false;

            uint64_t cur = State.load(std::memory_order_acquire);
            for (;;)
            {
                if (cur & INVALID_BIT) return false;

                const uint64_t exec = (cur & EXECUTOR_MASK);
                if (exec == EXECUTOR_MASK) [[unlikely]] return false; // would overflow into INVALID_BIT

                uint64_t desired = cur + 1;
                if (bOnce) desired |= INVALID_BIT;

                if (State.compare_exchange_weak(cur, desired, std::memory_order_acq_rel, std::memory_order_acquire))
                {
                    out_invalidated_by_once = bOnce;
                    return true;
                }
            }
        }

        // Marks this callback as invalid. Returns true iff this call transitioned it from valid -> invalid.
        bool Invalidate() noexcept
        {
            return (State.fetch_or(INVALID_BIT, std::memory_order_acq_rel) & INVALID_BIT) == 0;
        }

        // Ends an execution region started by TryBeginExecution().
        void EndExecution() noexcept
        {
            const uint64_t prev = State.fetch_sub(1, std::memory_order_acq_rel);
            if ((prev & EXECUTOR_MASK) == 1)
            {
                State.notify_all();
            }
        }

        // Waits until all in-flight executions are finished.
        void WaitForExecutorsToFinish() noexcept
        {
            uint64_t cur = State.load(std::memory_order_acquire);
            while ((cur & EXECUTOR_MASK) != 0)
            {
                State.wait(cur, std::memory_order_acquire);
                cur = State.load(std::memory_order_acquire);
            }
        }
        FCallbackMetadata() = delete;
        FCallbackMetadata(GlobalCallbackId Id, StringType OwnerModName, StringType HookName)
          : Id(Id), OwnerModName(std::move(OwnerModName)), HookName(std::move(HookName)) {}
        virtual ~FCallbackMetadata() = default;
    };

    // Metadata for registered callbacks + the actual typed callback
    template<typename CallbackType>
    struct TCallbackData : public FCallbackMetadata {
        CallbackType Callback;

        TCallbackData() = delete;
        TCallbackData(GlobalCallbackId id, const FCallbackOptions& opts, CallbackType cb)
            : FCallbackMetadata(id, opts.OwnerModName, opts.HookName), Callback(std::move(cb)) {}
        ~TCallbackData() override = default;
    };

    template<EDetourTarget Detour>
    struct TDetourMetadata {
        using FTargetFunction = typename TSignatureTraits<typename TDetourTraits<Detour>::Signature>::rc_function_type;

        FTargetFunction* TargetFunction;
        const bool* bShouldHook;
    };

    inline static constexpr bool ALWAYS_TRUE = true;

    template<EDetourTarget Detour>
    inline TDetourMetadata<Detour> GetDetourMetadata() 
    {
        if constexpr(Detour == EDetourTarget::StaticConstructObject) 
        {
            return 
            {
                &UObjectGlobals::GlobalState::StaticConstructObjectInternal, //may or may not be used depending on version
                &ALWAYS_TRUE // always hooked according to lack of option in UnrealInitializer::Config
            };
        }
        else if constexpr(Detour == EDetourTarget::ProcessEvent) 
        {  
            return 
            {
                &UObject::ProcessEventInternal,
                &ALWAYS_TRUE // always hooked according to lack of option in UnrealInitializer::Config
            };
        }
        else if constexpr(Detour == EDetourTarget::ProcessConsoleExec) 
        {
            return 
            {
                &UObject::ProcessConsoleExecInternal,
                &ALWAYS_TRUE // always hooked since the old RegisterProcessConsoleExecCallback/Pre/Post didn't respect UnrealInitializer::Config
            };
        }
        else if constexpr(Detour == EDetourTarget::UStructLink) 
        {
            return 
            {
                &UStruct::LinkInternal,
                &ALWAYS_TRUE // always hooked since its an internal hook
            };
        }
        else if constexpr(Detour == EDetourTarget::ProcessInternal) 
        {
            return 
            {
                &UObject::ProcessInternalInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookProcessInternal // should we somehow use atomics?
            };
        }
        else if constexpr(Detour == EDetourTarget::ProcessLocalScriptFunction) 
        {
            return 
            {
                &UObject::ProcessLocalScriptFunctionInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookProcessLocalScriptFunction
            };
        }
        else if constexpr(Detour == EDetourTarget::LoadMap) 
        {
            return 
            {
                &UEngine::LoadMapInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookLoadMap
            };
        }
        else if constexpr(Detour == EDetourTarget::EngineTick) 
        {
            return 
            {
                &UEngine::TickInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookEngineTick
            };
        }
        else if constexpr(Detour == EDetourTarget::InitGameState) 
        {
            return 
            {
                &AGameModeBase::InitGameStateInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookInitGameState
            };
        }
        else if constexpr(Detour == EDetourTarget::BeginPlay) 
        {
            return 
            {
                &AActor::BeginPlayInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookBeginPlay
            };
        }
        else if constexpr(Detour == EDetourTarget::EndPlay) 
        {
            return 
            {
                &AActor::EndPlayInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookEndPlay
            };
        }
        else if constexpr(Detour == EDetourTarget::AActorTick) 
        {
            return 
            {
                &AActor::TickInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookAActorTick
            };
        }
        else if constexpr(Detour == EDetourTarget::GameViewportClientTick) 
        {
            return 
            {
                &UGameViewportClient::TickInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookGameViewportClientTick
            };
        }
        else if constexpr(Detour == EDetourTarget::CallFunctionByNameWithArguments) 
        {
            return 
            {
                &UObject::CallFunctionByNameWithArgumentsInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookCallFunctionByNameWithArguments
            };
        }
        else if constexpr(Detour == EDetourTarget::ULocalPlayerExec) 
        {
            return 
            {
                &ULocalPlayer::ExecInternal,
                &UnrealInitializer::StaticStorage::GlobalConfig.bHookLocalPlayerExec
            };
        }
        else if constexpr(Detour == EDetourTarget::FNameConstructor)
        {
            return
            {
                &FName::ConstructorInternal,
                &ALWAYS_TRUE
            };
        }
        #ifdef UE_HOOK_TEST
        else if constexpr(Detour == EDetourTarget::VoidTest) 
        {
            static RC::Function<void(FTestVoidDetourHolder*, int)> func; // test class will handle assigning the pointer
            return 
            {
                &func,
                &ALWAYS_TRUE
            };
        }
        else if constexpr(Detour == EDetourTarget::NonVoidTest) 
        {
            static RC::Function<bool(FTestNonVoidDetourHolder*, int)> func; // test class will handle assigning the pointer
            return 
            {
                &func,
                &ALWAYS_TRUE
            };
        }
        #endif
        else {
            static_assert(false, "Unhandled EDetourTarget passed into GetDetourMetadata()!");
        }
    }
}
