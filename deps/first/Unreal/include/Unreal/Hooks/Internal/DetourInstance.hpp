#pragma once
#include <bit>
#include <memory>
#include <atomic>
#include <functional>
#include <mutex>
#include <vector>
#include <algorithm>
#include <exception>
#include <cstdint>

#ifdef _WIN32
#include <polyhook2/Detour/x64Detour.hpp>
#else
#include <Unreal/Hooks/Internal/PolyHookStubs.hpp>
#endif
#include <Unreal/Hooks/CallbackIterationData.hpp>
#include <Unreal/Hooks/Internal/Common.hpp>
#include <Unreal/Hooks/Internal/CallbackGarbageCollector.hpp>
#include <Unreal/Hooks/Internal/DetourTraits.hpp>
#include <Unreal/Hooks/Internal/Metadata.hpp>

#pragma push_macro("ensure")
#undef ensure

namespace RC::Unreal::Hook
{
    void SetOriginalFunctionCallResult(auto& IterationData, void* Value)
    {
        IterationData.SetOriginalFunctionCallResult(Value);
    }
    void SetCurrentCallbackInfo(auto& IterationData, Internal::FCallbackMetadata* Data)
    {
        IterationData.SetCurrentCallbackInfo(Data);
    }

    Internal::FCallbackMetadata* GetCurrentCallbackInfo(auto& IterationData)
    {
        return IterationData.GetCurrentCallbackInfo();
    }
}

namespace RC::Unreal::Hook::Internal
{
    template<EDetourTarget DetourTarget, typename InHookSig>
    class TDetourInstance;

    template<EDetourTarget DetourTarget, typename InHookReturnType, typename ...InArgs>
    class TDetourInstance<DetourTarget, std::function<InHookReturnType(InArgs...)>>;

    template<EDetourTarget DetourTarget>
    TDetourTraits<DetourTarget>::Impl* GetDetourInstance();

    // ProcessEvent needs default hook for asset loaded, CallbackReturnType/InHookReturnType must be default constructable and copyable, or void if InHookReturnType is void
    template<EDetourTarget DetourTarget, typename InHookReturnType, typename ...InArgs>
    class TDetourInstance<DetourTarget, std::function<InHookReturnType(InArgs...)>>
    {
    public:
        using FCallbackType = std::function<void(TCallbackIterationData<InHookReturnType>&, InArgs...)>;
        using FTargetFunctionType = Function<InHookReturnType(InArgs...)>;
        using FHookType = InHookReturnType(*)(InArgs...);

    UE_HOOK_PROTECTED:
        using FCallbackDataType = TCallbackData<FCallbackType>;
        using FCallbackVector = std::vector<std::shared_ptr<FCallbackDataType>>;
        using FCallbackVectorImmutablePtr = std::shared_ptr<const FCallbackVector>;

        // Pulls the metadata for the EDetourTarget value.
        // Postconditions: TargetFunction, bShouldHook, and DetourName are all non-null/empty
        TDetourInstance()
        {
            auto Metadata = GetDetourMetadata<DetourTarget>();
            TargetFunction = Metadata.TargetFunction;
            bShouldHook = Metadata.bShouldHook;
            DetourName = EnumToString(DetourTarget);

            if (!TargetFunction || !bShouldHook) [[unlikely]]
            {
                Output::send<LogLevel::Error>(STR("[{}] Detour is missing metadata! Target set = {}, ShouldHook set = {}"), DetourName, !!TargetFunction, !!bShouldHook);
                throw std::runtime_error("Detour is missing metadata or was provided nullptr for metadata fields! Check the UE4SS logs.");
            }
        }

        template<EDetourTarget Target>
        friend TDetourTraits<Target>::Impl* GetDetourInstance();
    public:
        TDetourInstance(const TDetourInstance&) = delete;
        TDetourInstance(TDetourInstance&&) = delete;

        ~TDetourInstance() = default;

    UE_HOOK_PROTECTED:
        // Initializes (but does not actually hook) the detour.
        // DO NOT CALL DIRECTLY, instead call EnsureHooked() for thread safety.
        // ActivateHook actually hooks the detour. Returns true if the PLHDetour is already instantiated.
        // Preconditions:   1. bShouldHook points to a true value (usually from the config file)
        //                  2. TargetFunction->is_ready() returns true
        // Postconditions:  PLHDetour is not nullptr
        bool InstallHook()
        {
            if(PLHDetour) return true;
            if(!(*bShouldHook)) [[unlikely]]
            {
                Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but hooking is disabled for this function.\n"), DetourName);
                return false;
            }

            if(!TargetFunction->is_ready()) [[unlikely]]
            {
                Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but function is unavailable.\n"), DetourName);
                return false;
            }

            PLHDetour = std::make_unique<PLH::x64Detour>(
                std::bit_cast<uint64_t>(TargetFunction->get_function_address()),
                std::bit_cast<uint64_t>(&StaticHookFn), &Trampoline);

            return true;
        }

        // Hooks the detour. Separated from install so behavior can be cleanly overridden.
        // Preconditions:   InstallHook() must have already succeeded for this to succeed (PLHDetour shouldn't be nullptr).
        // Postconditions:  The detour is installed and calls are actively being routed through the StaticHookFn
        bool ActivateHook()
        {
            if (!PLHDetour) [[unlikely]] return false;
            if(PLHDetour->isHooked()) [[unlikely]] return true;
        #ifndef UE_HOOK_TEST
            std::call_once(GCInstallFlag, [this] {
                FCallbackGarbageCollector::GetInstance()->AddLink([this]{ return CollectGarbage(); });
            });
        #endif
            return PLHDetour->hook();
        }

        // Unhooks the detour.
        // Preconditions:   InstallHook() must have already succeeded for this to succeed (PLHDetour shouldn't be nullptr).
        // Postconditions:  The detour is uninstalled and calls are NOT routed through the StaticHookFn,
        //                  callbacks are not removed, and remain valid if detour is reactivated.
        bool DeactivateHook()
        {
            auto Instance = GetDetourInstance<DetourTarget>();
            if (!Instance->PLHDetour) [[unlikely]] return false;
            if(!Instance->PLHDetour->isHooked()) [[unlikely]] return true;
            bool bSuccess = Instance->PLHDetour->unHook();
            Instance->PLHDetour = nullptr;
            return bSuccess;
        }

    public:
        friend auto UnrealInitializer::VerifyFNameConstructor(void*) -> void;

        // Ensure that the detour is hooked and active. Returns false if neither of these are true.
        static bool EnsureHooked()
        {
            const auto Instance = GetDetourInstance<DetourTarget>();
            std::lock_guard Guard(Instance->InstallMutex);
            if(!Instance->InstallHook()) [[unlikely]] return false;
            if(!Instance->ActivateHook()) [[unlikely]] return false;
            return true;
        }

        // Returns true if invalid (to-be-removed) callbacks exist in either callback vector.
        bool IsDirty() const { return bDirty.load(std::memory_order_acquire); }

        // Prunes invalid callbacks from the callback vectors.
        // Can be called manually from any thread to force GC for this detour, but the FCallbackGarbageCollector will also
        // periodically call this in its own thread, since this is a mutex-protected operation.
        // Returns true if the function ran (bDirty was true before CollectGarbage was called), and false otherwise.
        bool CollectGarbage()
        {
            // fast exit + avoids losing concurrent dirty sets
            if (!bDirty.exchange(false, std::memory_order_acq_rel)) return false;

            std::lock_guard Guard(WriteMutex);

            auto PruneFn = [](const std::shared_ptr<const FCallbackVector>& InVector)
                -> std::shared_ptr<const FCallbackVector>
            {
                auto OutVector = std::make_shared<FCallbackVector>();
                OutVector->reserve(InVector->size());
                for (const auto& CallbackData : *InVector)
                {
                    if (!CallbackData->IsInvalid(std::memory_order_acquire))
                        OutVector->push_back(CallbackData);
                }
                return OutVector; // implicit shared_ptr<T> -> shared_ptr<const T>
            };

            PreHookCallbacks.store(PruneFn(PreHookCallbacks.load(std::memory_order_acquire)), std::memory_order_release);
            PostHookCallbacks.store(PruneFn(PostHookCallbacks.load(std::memory_order_acquire)), std::memory_order_release);

            // If something got dirtied again during pruning, we'll handle it next time.
            return true;
        }

        // Adds a callback to the callback vector indicated by the CallbackType with the given CallbackOptions.
        // Can be called from any thread, but this is a mutex-protected operation so it's best to not call this in the hot path/game thread (though
        // it may be called from another registered callback; this is the only case where there's a potentially blocking mutex in the
        // hot path).
        // If the hook isn't installed yet, AddCallback will call EnsureHooked to try to install it (which may return false if the config says not
        // to hook it), in which case the callback will not be added.
        // In any error case, ERROR_ID is returned.
        GlobalCallbackId AddCallback(FCallbackType Callback, const EHookType CallbackType, FCallbackOptions CallbackOptions)
        {
            if(!EnsureHooked()) [[unlikely]]
            {
                Output::send<LogLevel::Error>(STR("[{}.{}.{}] Failed to add hook, detour installation likely failed!\n"), CallbackOptions.OwnerModName, DetourName, CallbackOptions.HookName);
                return ERROR_ID;
            }

            auto Id = IdCounter.fetch_add(1, std::memory_order_relaxed);

            // Test for overflow
            if(Id >= FIRST_FLAG_BIT) [[unlikely]]
            {
                Output::send<LogLevel::Error>(STR("[{}.{}.{}] Failed to add hook, there are too many hooks active in the game!\n"), CallbackOptions.OwnerModName, DetourName, CallbackOptions.HookName);
                return ERROR_ID;
            }

            // Set flags (this makes it globally unique and addressable to this DetourInstance)
            if(CallbackOptions.bOnce) Id |= static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Once);
            if(CallbackOptions.bReadonly) Id |= static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Readonly);
            if(CallbackType == EHookType::Pre) Id |= static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Prehook);
            Id |= static_cast<uint64_t>(DetourTarget);

            // Assign default metadata based on options
            if(CallbackOptions.HookName.empty()) CallbackOptions.HookName = StringType((CallbackOptions.bOnce ? STR("Once") : STR(""))) + (CallbackType == EHookType::Pre ? STR("PreHook") : STR("PostHook"));
            if(CallbackOptions.OwnerModName.empty()) CallbackOptions.OwnerModName = STR("UnknownMod");

            // Lock writing to the atomic pointer to prevent inconsistencies
            {
                std::lock_guard Guard(WriteMutex);
                auto OldCallbackVector = CallbackType == EHookType::Pre ? PreHookCallbacks.load(std::memory_order_acquire) : PostHookCallbacks.load(std::memory_order_acquire);

                auto NewCallbackData = std::make_shared<FCallbackDataType>(Id, CallbackOptions, std::move(Callback));

                std::shared_ptr<FCallbackVector> ModifiedCallbackVector{};

                // Might as well prune invalid callbacks since we copy all the pointers anyways
                if (!IsDirty())
                {
                    ModifiedCallbackVector = std::make_shared<FCallbackVector>(*OldCallbackVector);

                    if (CallbackOptions.bReadonly)
                    {
                        // Readonly always goes at the end (after any existing readonly).
                        ModifiedCallbackVector->push_back(std::move(NewCallbackData));
                    }
                    else
                    {
                        // Non-readonly must be inserted before the first readonly.
                        auto InsertionIterator = std::find_if(ModifiedCallbackVector->begin(), ModifiedCallbackVector->end(),
                                               [&](const auto& ExistingCallbackData) { return ExistingCallbackData && (ExistingCallbackData->Id & static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Readonly)); });

                        ModifiedCallbackVector->insert(InsertionIterator, std::move(NewCallbackData));
                    }
                }
                else
                {
                    ModifiedCallbackVector = std::make_shared<FCallbackVector>();
                    ModifiedCallbackVector->reserve(OldCallbackVector->size() + 1);

                    if (CallbackOptions.bReadonly)
                    {
                        // Prune invalids, keep order, then append new readonly at end.
                        for (auto& ExistingCallbackData : *OldCallbackVector)
                        {
                            if (!ExistingCallbackData) continue;
                            if (ExistingCallbackData->IsInvalid(std::memory_order_acquire)) continue;
                            ModifiedCallbackVector->push_back(ExistingCallbackData);
                        }
                        ModifiedCallbackVector->push_back(std::move(NewCallbackData));
                    }
                    else
                    {
                        // Prune invalids, keep order, but insert new non-readonly
                        // right before the first *valid* readonly we encounter.
                        bool bInserted = false;

                        for (auto& ExistingCallbackData : *OldCallbackVector)
                        {
                            if (!ExistingCallbackData) [[unlikely]] continue;
                            if (ExistingCallbackData->IsInvalid(std::memory_order_acquire)) continue;

                            if (!bInserted && (ExistingCallbackData->Id & static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Readonly))) [[unlikely]]
                            {
                                ModifiedCallbackVector->push_back(std::move(NewCallbackData));
                                bInserted = true;
                            }

                            ModifiedCallbackVector->push_back(ExistingCallbackData);
                        }

                        if (!bInserted)
                        {
                            ModifiedCallbackVector->push_back(std::move(NewCallbackData));
                        }
                    }
                    // Don't clear dirty here since the other vector might be dirty.
                }

                // 'Commit' the modified vector atomically
                CallbackType == EHookType::Pre ? PreHookCallbacks.store(ModifiedCallbackVector, std::memory_order_release) : PostHookCallbacks.store(ModifiedCallbackVector, std::memory_order_release);
            }
            Output::send<LogLevel::Verbose>(STR("[{}.{}.{}] Added {}hook with Id '{:#X}'!\n"),
                                            CallbackOptions.OwnerModName, DetourName, CallbackOptions.HookName,
                                            CallbackType == EHookType::Pre ? STR("pre") : STR("post"), Id);
            return Id;
        }

        // Invalidates the callback with the registered GlobalCallbackId, returns false if it doesn't exist or ERROR_ID was passed in
        // NEVER call this, directly or indirectly, from within a callback.
        bool RemoveCallback(GlobalCallbackId Id)
        {
            // If ERROR_ID was passed in, return false
            if(Id == ERROR_ID) [[unlikely]]
            {
                Output::send<LogLevel::Error>(STR("[{}] Failed to remove hook because ID was error sentinel! It was likely never hooked to begin with.\n"), DetourName);
                return false;
            }

            // If the Id doesn't belong to this detour, return false
            if((Id & DETOUR_MASK) != static_cast<uint64_t>(DetourTarget)) [[unlikely]]
            {
                Output::send<LogLevel::Error>(STR("[{}] Failed to remove hook because ID does not belong to this detour! It belongs to = {}\n"),
                                                DetourName, EnumToString(static_cast<EDetourTarget>(Id & DETOUR_MASK)));
                return false;
            }

            // Get the correct callback vector from the Id's encoding
            const auto IsPreHook = Id & static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Prehook);
            auto CallbackVector = IsPreHook ? PreHookCallbacks.load(std::memory_order_acquire) : PostHookCallbacks.load(std::memory_order_acquire);

            // Linear search for the callback with the Id and invalidate it.
            // TODO: You might be able bin search this if you move the mutex guard in AddCallback to also guard the IdCounter
            // (which you can then make non-atomic), then, since the bits set by the IdCounter only increment, if you mask
            // off non-IdCounter bits for comparison (which there is a defined constant for), it should be ordered, but this keeps it simple for now,
            // and Remove/Add hook won't typically be in the hot path anyways (once/exceptional callbacks are quickly invalidated
            // in the hot path, not through this function). You also have to consider readonly hooks, which are placed after non-readonly
            // hooks, in order, regardless of the IdCounter's value, which breaks up the overall ordering a bit (you'd have to <span> the
            // readonly/non-readonly subvectors to do it with STL).
            // Still possible though.
            for (auto& CallbackData : *CallbackVector)
            {
                if (CallbackData->Id != Id) [[likely]] continue;

                if (CallbackData->Invalidate())
                {
                    bDirty.store(true, std::memory_order_release);
                }
                CallbackData->WaitForExecutorsToFinish();
                return true;
            }

            return false;
        }

        // Invokes all registered callbacks with metadata and Args... in a thread safe, usually lock-free manner by calling InvokeCallbacks where needed.
        // Overriding functions must respect the semantics of, and use, TCallbackIterationDataImpl when calling registered callbacks and the original
        // function.
        // Returns the value that should be passed back to the game.
        // Postcondition:   1. All registered and valid callbacks are called with the provided args
        //                  2. Semantics of TCallbackIterationDataImpl are respected, especially where it involves the final return value.
        InHookReturnType Invoke(InArgs... Args)
        {
            // Make the ICallbackIterationData that gets passed by reference to each callback
            TCallbackIterationData<InHookReturnType> IterationData{ DetourName };

            // Call prehook callbacks
            InvokeCallbacks(EHookType::Pre, IterationData, Args...);

            if constexpr(CVoidReturnType<InHookReturnType>)
            {
                // Call the original function if none of the prehooks prevented it
                if(!IterationData.OriginalFunctionCallPrevented()) [[likely]]
                {
                    PLH::FnCast(Trampoline, TargetFunction->get_function_pointer())(Args...);
                }

                // Call posthook callbacks
                InvokeCallbacks(EHookType::Post, IterationData, Args...);
                return;
            }
            else
            {
                // Call the original function if none of the prehooks prevented it and store the result in the TCallbackIterationDataImpl
                if(!IterationData.OriginalFunctionCallPrevented()) [[likely]]
                {
                    auto ReturnValue = PLH::FnCast(Trampoline, TargetFunction->get_function_pointer())(Args...);
                    SetOriginalFunctionCallResult(IterationData, &ReturnValue);
                }

                // Call posthook callbacks
                InvokeCallbacks(EHookType::Post, IterationData, Args...);

                // Return the original function call result, or the overriden result if a hook set one
                return IterationData.GetCurrentResolvedReturnValue();
            }

            // TODO: (not super important) might be a good idea to 'invalidate' the TCallbackIterationDataImpl so if someone
            // kept a reference/pointer to it, despite the documentation, the functions become inert
        }

    UE_HOOK_PROTECTED:
        // Invokes all registered callbacks that matches the given EHookType with the given ICallbackIterationData<InHookReturnType>& and InArgs...
        void InvokeCallbacks(const EHookType HookType, TCallbackIterationData<InHookReturnType>& IterationData, InArgs... Args)
        {
            // Get the callback vector
            auto Callbacks = HookType == EHookType::Pre ? PreHookCallbacks.load(std::memory_order_acquire) : PostHookCallbacks.load(std::memory_order_acquire);

            // Single try/catch for the entire loop to minimize overhead (only enter try block once per invocation)
            try
            {
                for(const auto& CallbackInfo : *Callbacks)
                {
                    // Handle once/invalid semantics + executor accounting in a single packed atomic.
                    const bool bOnce = (CallbackInfo->Id & static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Once)) != 0;

                    bool bInvalidatedByOnce = false;
                    if (!CallbackInfo->TryBeginExecution(bOnce, bInvalidatedByOnce))
                    {
                        continue;
                    }

                    // If we just claimed a 'once' callback, mark the detour as dirty so the next GC pass prunes it.
                    if (bInvalidatedByOnce)
                    {
                        bDirty.store(true, std::memory_order_release);
                    }

                    // Set the current callback data that's used for metadata access in the passed in CallbackData
                    SetCurrentCallbackInfo(IterationData, CallbackInfo.get());

                    CallbackInfo->Callback(IterationData, Args...);

                    CallbackInfo->EndExecution();
                }
            }
            catch(const std::exception& ex)
            {
                auto* CurrentCallback = GetCurrentCallbackInfo(IterationData);
                if (CurrentCallback && CurrentCallback->Invalidate())
                {
                    bDirty.store(true, std::memory_order_release);
                }
                if (CurrentCallback)
                {
                    CurrentCallback->EndExecution();
                }
                Output::send<LogLevel::Error>(STR("[{}.{}.{}] Hook threw exception: \"{}\", removing hook!\n"),
                                                CurrentCallback ? CurrentCallback->OwnerModName : STR("Unknown"),
                                                DetourName,
                                                CurrentCallback ? CurrentCallback->HookName : STR("Unknown"),
                                                ensure_str(ex.what()));
            }
            catch(...)
            {
                auto* CurrentCallback = GetCurrentCallbackInfo(IterationData);

                if (CurrentCallback && CurrentCallback->Invalidate())
                {
                    bDirty.store(true, std::memory_order_release);
                }
                if (CurrentCallback)
                {
                    CurrentCallback->EndExecution();
                }
                Output::send<LogLevel::Error>(STR("[{}.{}.{}] Hook threw non-standard exception, removing hook!\n"),
                                                CurrentCallback ? CurrentCallback->OwnerModName : STR("Unknown"),
                                                DetourName,
                                                CurrentCallback ? CurrentCallback->HookName : STR("Unknown"));
            }
        }

        // 'static' in name only, unique per template instantiation for which there is always only one (enforced via protected ctors and friending
        // GetDetourInstance())
        static InHookReturnType StaticHookFn(InArgs... Args)
        {
            return GetDetourInstance<DetourTarget>()->Invoke(Args...);
        }

        // The name of the detour ('reflected' enum name as string)
        StringViewType DetourName;

        // A pointer to the boolean in the Config object that corresponds to whether this detour should be hooked,
        // or a pointer to an always-true boolean if there is no config option.
        const bool* bShouldHook;

        // The polyhook detour, trampoline, and target
        std::unique_ptr<PLH::x64Detour> PLHDetour{};
        uint64_t Trampoline = NULL;
        FTargetFunctionType* TargetFunction;

        // Objects for thread safety; uses RCU pattern for hot path access (which keeps the hot path only using atomics rather than mutexes,
        // unless the user adds a callback in their callback), uses vectors for better caching
        // (msvc doesn't implement flat_map yet so searching is going to be linear for now, unless someone wants to implement
        // the binary search strategy listed in RemoveHook)
        std::mutex WriteMutex;
        std::mutex InstallMutex;
        std::atomic<FCallbackVectorImmutablePtr> PreHookCallbacks = std::make_shared<const FCallbackVector>();
        std::atomic<FCallbackVectorImmutablePtr> PostHookCallbacks = std::make_shared<const FCallbackVector>();

        // Whether or not any callback vector contains invalid callbacks
        std::atomic_bool bDirty = false;

        // A helper object for std::call_once to ensure that only one link is registered to the CallbackGarbageCollector
        std::once_flag GCInstallFlag;

        // A counter that gets encoded into the bits of a GlobalCallbackId for uniqueness; unique per template instantiation,
        // for which there is always only one.
        inline static std::atomic_uint64_t IdCounter = 1;
    };
}

#pragma pop_macro("ensure")