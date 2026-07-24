#pragma once
#include <Unreal/Hooks/Internal/DetourInstance.hpp>
#include <Unreal/Hooks/Internal/Common.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/Hooks/Internal/DetourTraits.hpp>
#include <Unreal/Hooks/Internal/ProcessEventProfiler.hpp>

#include <chrono>
#include <Zydis/Zydis.h>
#include <ASMHelper/ASMHelper.hpp>
#ifdef _WIN32
#include <polyhook2/ZydisDisassembler.hpp>
#include <Unreal/Core/Windows/WindowsHWrapper.hpp>
#endif
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UnrealInitializer.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/FFrame.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <Unreal/UEngine.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/UAssetRegistry.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/UGameViewportClient.hpp>
#include <Unreal/AGameModeBase.hpp>
#include <Unreal/ULocalPlayer.hpp>
#include <Unreal/Searcher/ObjectSearcher.hpp>

#pragma push_macro("ensure")
#undef ensure

namespace RC::Unreal::Hook::Internal
{
    // Subclass for ProcessConsoleExec to additionally call PLHDetour->setDetourScheme(PLH::x64Detour::INPLACE_SHORT) for WINE
    class FProcessConsoleExecDetour : public TDetourInstance<EDetourTarget::ProcessConsoleExec, ProcessConsoleExecSignature> 
    {
    UE_HOOK_PROTECTED:
        FProcessConsoleExecDetour() = default;
        using Base = TDetourInstance<EDetourTarget::ProcessConsoleExec, ProcessConsoleExecSignature>;

        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;
    public:
        bool InstallHook()
        {
            auto Installed = Base::InstallHook();
            if(!Installed) return false;
            #ifdef _WIN32
            static std::atomic_bool bSchemeSet = false;
            if (auto Module = GetModuleHandle(L"ntdll.dll"); !bSchemeSet.exchange(true, std::memory_order_acq_rel) && Module && GetProcAddress(Module, "wine_get_version"))
            {
                PLHDetour->setDetourScheme(PLH::x64Detour::INPLACE_SHORT);
            }
            #endif
            return true;
        }
    };

    // Subclass for CallFunctionByNameWithArguments to disassemble the instructions at the current TargetFunction and retarget it to the intended
    // target.
    class FCallFunctionByNameWithArgumentsDetour : public TDetourInstance<EDetourTarget::CallFunctionByNameWithArguments, CallFunctionByNameWithArgumentsSignature> 
    {
    public:
        bool InstallHook()
        {
            if(PLHDetour) return true;
            if(!(*bShouldHook)) 
            {
                Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but hooking is disabled for this function.\n"), DetourName);
                return false;
            }
            if(!TargetFunction->is_ready()) 
            {
                if(!UObject::ProcessConsoleExecInternal.is_ready()) 
                {
                    Output::send<LogLevel::Warning>(STR("[{}] Cannot retrieve CallFunctionByNameWithArguments because ProcessConsoleExec is not available.\n"), DetourName);
                    return false;
                }
                auto ProcessConsoleExec = UObject::ProcessConsoleExecInternal.get_function_address();
                int CallCount{};
                auto Data = std::bit_cast<ZyanU8*>(ProcessConsoleExec);
                ZydisDecoder Decoder;
                ZydisDecoderInit(&Decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
                ZyanU64 RuntimeAddress = std::bit_cast<ZyanU64>(ProcessConsoleExec);
                ZyanUSize Offset = 0;
                const ZyanUSize NumBytesToDecode = 164;
                ZydisDecodedInstruction Instruction;
                ZydisDecodedOperand Operands[10]{};
                while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&Decoder, Data + Offset, NumBytesToDecode - Offset, &Instruction, Operands)))
                {
                    if (Instruction.mnemonic == ZYDIS_MNEMONIC_CALL)
                    {
                        ++CallCount;
                    }
                
                    if (CallCount == 1)
                    {
                        auto FunctionPtr = ASM::resolve_function_address_from_potential_jmp(std::bit_cast<void*>(RuntimeAddress));
                        UObject::CallFunctionByNameWithArgumentsInternal.assign_address(FunctionPtr);
                        break;
                    }
                    Offset += Instruction.length;
                    RuntimeAddress += Instruction.length;
                }
            }

            if(!TargetFunction->is_ready()) 
            {
                Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but function is unavailable.\n"), DetourName);
                return false;
            }

            PLHDetour = std::make_unique<PLH::x64Detour>(
                std::bit_cast<uint64_t>(TargetFunction->get_function_address()),
                std::bit_cast<uint64_t>(&StaticHookFn), &Trampoline);

            return true;
        }

    UE_HOOK_PROTECTED:
        FCallFunctionByNameWithArgumentsDetour() = default;
        using Base = TDetourInstance<EDetourTarget::CallFunctionByNameWithArguments, CallFunctionByNameWithArgumentsSignature>;
        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;
    };

    // Subclass for ULocalPlayerExec to disassemble the instructions at the current TargetFunction and retarget it to the intended
    // target, as well as adjusting the 'this' pointer between the original function call and callback invocations.
    class FULocalPlayerExecDetour : public TDetourInstance<EDetourTarget::ULocalPlayerExec, ULocalPlayerExecSignature> 
    {
    UE_HOOK_PROTECTED:
        FULocalPlayerExecDetour() = default;
        using Base = TDetourInstance<EDetourTarget::ULocalPlayerExec, ULocalPlayerExecSignature>;
        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;
    public:
        bool InstallHook()
        {
            if(PLHDetour) return true;
            if(!(*bShouldHook)) 
            {
                Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but hooking is disabled for this function.\n"), DetourName);
                return false;
            }

            auto* LocalPlayer = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.Default__LocalPlayer"));
            if (!LocalPlayer)
            {
                Output::send<LogLevel::Warning>(STR("Tried to hook ULocalPlayer::Exec but was unable to find 'Engine.Default__LocalPlayer' to use to retrieve its address.\n"));
                return false;
            }

            auto VTable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(LocalPlayer + UnrealInitializer::StaticStorage::GlobalConfig.FExecVTableOffsetInLocalPlayer));
            auto Func = *std::bit_cast<void**>(VTable + 0x8);
            {
                auto Data = std::bit_cast<ZyanU8*>(Func);
                ZydisDecoder Decoder;
                ZydisDecoderInit(&Decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
                ZyanU64 RuntimeAddress = std::bit_cast<ZyanU64>(Func);
                ZyanUSize Offset = 0;
                const ZyanUSize NumBytesToDecode = 8;
                ZydisDecodedInstruction Instruction;
                ZydisDecodedOperand Operands[10]{};
                while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&Decoder, Data + Offset, NumBytesToDecode - Offset, &Instruction, Operands)))
                {
                    if (Instruction.mnemonic == ZYDIS_MNEMONIC_JMP)
                    {
                        ZyanU64 ResultAddress{};
                        if (ZYAN_SUCCESS(ZydisCalcAbsoluteAddress(&Instruction, &Operands[0], RuntimeAddress, &ResultAddress)))
                        {
                            TargetFunction->assign_address(std::bit_cast<void*>(ResultAddress));
                        }
                        else
                        {
                            Output::send<LogLevel::Warning>(STR("Tried to hook ULocalPlayer::Exec but was unable to resolve JMP instruction.\n"));
                        }
                    }
                    else
                    {
                        TargetFunction->assign_address(std::bit_cast<void*>(Func));
                    }
                    break;
                }
            }

            return Base::InstallHook();
        }

        bool Invoke(ULocalPlayer* Context, UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
        {
            static const auto FExecVTableOffsetInLocalPlayer = UnrealInitializer::StaticStorage::GlobalConfig.FExecVTableOffsetInLocalPlayer;

            Context = std::bit_cast<ULocalPlayer*>(std::bit_cast<uint8_t*>(Context) - FExecVTableOffsetInLocalPlayer);
            TCallbackIterationData<bool> IterationData{ DetourName };

            InvokeCallbacks(EHookType::Pre, IterationData, Context, InWorld, Cmd, Ar);

            Context = std::bit_cast<ULocalPlayer*>(std::bit_cast<uint8_t*>(Context) + FExecVTableOffsetInLocalPlayer);
            if(!IterationData.OriginalFunctionCallPrevented()) 
            {
                auto ReturnValue = PLH::FnCast(Trampoline, TargetFunction->get_function_pointer())(Context, InWorld, Cmd, Ar);
                SetOriginalFunctionCallResult(IterationData, &ReturnValue);
            }
            Context = std::bit_cast<ULocalPlayer*>(std::bit_cast<uint8_t*>(Context) - FExecVTableOffsetInLocalPlayer);
            InvokeCallbacks(EHookType::Post, IterationData, Context, InWorld, Cmd, Ar);

            return IterationData.GetCurrentResolvedReturnValue();
        }

    };

    // Subclass for UStructLink, which is not exposed publicly and only used to facilitate object searching
    class FUStructLinkDetour : public TDetourInstance<EDetourTarget::UStructLink, std::function<void(UStruct*, FArchive&, bool)>> 
    {
    public:
        void Invoke(UStruct* Context, FArchive& Ar, bool bRelinkExistingProperties)
        {
            PLH::FnCast(Trampoline, TargetFunction->get_function_pointer())(Context, Ar, bRelinkExistingProperties);
            if (!UnrealInitializer::StaticStorage::bIsInitialized) { return; }

            auto* ObjectItem = Context->GetObjectItem();
            if (Context->IsA<UClass>())
            {
                std::lock_guard<std::mutex> AnyPoolLock(ObjectSearcherPool<UClass, AnySuperStruct>::PoolMutex);
                ObjectSearcherPool<UClass, AnySuperStruct>::Add(ObjectItem);

                if (static_cast<const UClass*>(Context)->IsChildOf<AActor>())
                {
                    std::lock_guard<std::mutex> ActorPoolLock(ObjectSearcherPool<UClass, AActor>::PoolMutex);
                    ObjectSearcherPool<UClass, AActor>::Add(ObjectItem);
                }
            }
        }

    UE_HOOK_PROTECTED:
        FUStructLinkDetour() = default;
        using Base = TDetourInstance<EDetourTarget::UStructLink, std::function<void(UStruct*, FArchive&, bool)>>;
        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;
    };

    class FInitGameStateDetour : public TDetourInstance<EDetourTarget::InitGameState, InitGameStateSignature>
    {
    public:
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
                std::bit_cast<uint64_t>(&NewStaticHookFn), &Trampoline);

            return true;
        }

        static void NewStaticHookFn(AGameModeBase* Context, void* dummy1, void* dummy2, void* dummy3)
        {
            return GetDetourInstance<EDetourTarget::InitGameState>()->Invoke(Context, dummy1, dummy2, dummy3);
        }

        void Invoke(AGameModeBase* Context, void* dummy1, void* dummy2, void* dummy3)
        {
            // Make the ICallbackIterationData that gets passed by reference to each callback
            TCallbackIterationData<void> IterationData{ DetourName };

            // Call prehook callbacks
            InvokeCallbacks(EHookType::Pre, IterationData, Context);

            // Call the original function if none of the prehooks prevented it
            if(!IterationData.OriginalFunctionCallPrevented()) [[likely]]
            {
                PLH::FnCast(Trampoline, NewStaticHookFn)(Context, dummy1, dummy2, dummy3);
            }

            // Call posthook callbacks
            InvokeCallbacks(EHookType::Post, IterationData, Context);
        }
    protected:
        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;
        FInitGameStateDetour() = default;
    };

    // Subclass for StaticConstructObject, which handles the different versions of the function.
    class FStaticConstructObjectDetour : public TDetourInstance<EDetourTarget::StaticConstructObject, StaticConstructObjectSignature> 
    {
    UE_HOOK_PROTECTED:
        using FDeprecatedTargetFunctionType = decltype(RC::Unreal::UObjectGlobals::GlobalState::StaticConstructObjectInternalDeprecated);
        using FNativeParams55 = UObjectGlobals::Below56::FStaticConstructObjectParameters;
        using FNativeParamsLatest = UObjectGlobals::Above55::FStaticConstructObjectParameters;
        using FCallbackParams = RC::Unreal::FStaticConstructObjectParameters;
        enum ESigType 
        {
            Base,
            v426,
            v506
        };
    UE_HOOK_PROTECTED:
        using BaseClass = TDetourInstance<EDetourTarget::StaticConstructObject, StaticConstructObjectSignature>;
        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;

        FStaticConstructObjectDetour() : BaseClass()
        {
            SigType = Version::IsAtMost(4, 25) ? Base : Version::IsAtMost(5, 5) ? v426 : v506;
        }

    public:
        bool InstallHook()
        {
            if(PLHDetour) return true;
            if(!(*bShouldHook)) 
            {
                Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but hooking is disabled for this function.\n"), DetourName);
                return false;
            }
            switch(SigType) 
            {
                case Base: 
                {
                    if(!DeprecatedTarget->is_ready())
                    {
                        Output::send<LogLevel::Warning>(STR("[{}] Tried to install hook but function is unavailable.\n"), DetourName);
                        return false;
                    }

                    PLHDetour = std::make_unique<PLH::x64Detour>(
                        std::bit_cast<uint64_t>(DeprecatedTarget->get_function_address()),
                        std::bit_cast<uint64_t>(&Hook425), &Trampoline);

                    return true;
                }
                case v426:
                case v506: 
                {
                    return BaseClass::InstallHook();
                }
                default: 
                {
                    return false;
                }
            }
        }

        UObject* Invoke425(const FCallbackParams& Params) 
        {
            TCallbackIterationData<UObject*> IterationData{ DetourName };
            InvokeCallbacks(EHookType::Pre, IterationData, Params);
            if(!IterationData.OriginalFunctionCallPrevented()) 
            {
                auto ReturnValue = PLH::FnCast(Trampoline, DeprecatedTarget->get_function_pointer())(Params.Class,
                                                                                                           Params.Outer,
                                                                                                           Params.Name,
                                                                                                           Params.SetFlags,
                                                                                                           Params.InternalSetFlags,
                                                                                                           Params.Template,
                                                                                                           Params.bCopyTransientsFromClassDefaults,
                                                                                                           Params.InstanceGraph,
                                                                                                           Params.bAssumeTemplateIsArchetype,
                                                                                                           Params.ExternalPackage);
                SetOriginalFunctionCallResult(IterationData, &ReturnValue);
            }
            InvokeCallbacks(EHookType::Post, IterationData, Params);

            return IterationData.GetCurrentResolvedReturnValue();
        }

    UE_HOOK_PROTECTED:
        static UObject* Hook425(StaticConstructObject_Internal_Params_Deprecated) 
        {
            FCallbackParams Params{ InClass_, InOuter_ };
            Params.Name = InName_;
            Params.InternalSetFlags = InternalSetFlags_;
            Params.SetFlags = InFlags_;
            Params.Template = InTemplate_;
            Params.bCopyTransientsFromClassDefaults = bCopyTransientsFromClassDefaults_;
            Params.InstanceGraph = InInstanceGraph_;
            Params.bAssumeTemplateIsArchetype = bAssumeTemplateIsArchetype_;
            Params.ExternalPackage = static_cast<UPackage*>(ExternalPackage_);
            return reinterpret_cast<FStaticConstructObjectDetour*>( // have to reinterpret_pointer_cast since we can't use overrides with this version
                GetDetourInstance<EDetourTarget::StaticConstructObject>())->Invoke425(Params);
        }

    UE_HOOK_PRIVATE:
        FDeprecatedTargetFunctionType* DeprecatedTarget = &RC::Unreal::UObjectGlobals::GlobalState::StaticConstructObjectInternalDeprecated;
        ESigType SigType;
    };

#ifdef UE_HOOK_TEST
    class FTestVoidDetourHolder 
    {
    public:
        void Target(int Value) 
        {
            // just do something so that the function is long enough to hook
            std::vector<int> Ints;
            for(auto I = 0; I < 10; ++I) {
                Ints.push_back(Value + I);
            }
            Ints.clear();
        }
    };

    class FTestNonVoidDetourHolder 
    {
    public:
        bool Target(int value) 
        {
            // just do something so that the function is long enough to hook
            std::vector<int> Ints;
            for(auto i = 0; i < 10; ++i) {
                Ints.push_back(value + i);
            }
            Ints.clear();
            return Ints.empty();
        }
    };

    class TestVoidDetour : public TDetourInstance<EDetourTarget::VoidTest, std::function<void(FTestVoidDetourHolder*, int)>> 
    {
    public:
        TestVoidDetour() : TDetourInstance<EDetourTarget::VoidTest, std::function<void(FTestVoidDetourHolder*, int)>>() 
        {
            static_assert(sizeof(void*) == sizeof(decltype(&FTestVoidDetourHolder::Target)));
            TargetFunction->assign_address(std::bit_cast<void*>(&FTestVoidDetourHolder::Target));
        }
    };

    class TestNonVoidDetour : public TDetourInstance<EDetourTarget::NonVoidTest, std::function<bool(FTestNonVoidDetourHolder*, int)>> 
    {
    public:
        TestNonVoidDetour() : TDetourInstance<EDetourTarget::NonVoidTest, std::function<bool(FTestNonVoidDetourHolder*, int)>>() 
        {
            static_assert(sizeof(void*) == sizeof(decltype(&FTestNonVoidDetourHolder::Target)));
            TargetFunction->assign_address(std::bit_cast<void*>(&FTestNonVoidDetourHolder::Target));
        }
    };
#endif

    #ifdef UE4SS_PROFILERS
    // Subclass for ProcessEvent with profiling support
    class FProcessEventDetour : public TDetourInstance<EDetourTarget::ProcessEvent, ProcessEventSignature>
    {
    UE_HOOK_PROTECTED:
        FProcessEventDetour() = default;
        using Base = TDetourInstance<EDetourTarget::ProcessEvent, ProcessEventSignature>;

        template<EDetourTarget Target>
        friend auto GetDetourInstance() -> TDetourTraits<Target>::Impl*;

    public:
        void Invoke(UObject* Context, UFunction* Function, void* Parms)
        {
            if (ProcessEventProfiler::IsProfilingEnabled())
            {
                const bool bCapturing = ProcessEventProfiler::IsCaptureEnabled();
                auto totalStart = std::chrono::high_resolution_clock::now();

                TCallbackIterationData<void> IterationData{ DetourName };

                // Pre-callbacks with timing
                auto preStart = std::chrono::high_resolution_clock::now();
                InvokeCallbacks(EHookType::Pre, IterationData, Context, Function, Parms);
                auto preEnd = std::chrono::high_resolution_clock::now();
                uint64_t preCallbacksNs = std::chrono::duration_cast<std::chrono::nanoseconds>(preEnd - preStart).count();

                // Original function with timing
                uint64_t originalNs = 0;
                if (!IterationData.OriginalFunctionCallPrevented())
                {
                    auto origStart = std::chrono::high_resolution_clock::now();
                    PLH::FnCast(Trampoline, TargetFunction->get_function_pointer())(Context, Function, Parms);
                    auto origEnd = std::chrono::high_resolution_clock::now();
                    originalNs = std::chrono::duration_cast<std::chrono::nanoseconds>(origEnd - origStart).count();
                }

                // Post-callbacks with timing
                auto postStart = std::chrono::high_resolution_clock::now();
                InvokeCallbacks(EHookType::Post, IterationData, Context, Function, Parms);
                auto postEnd = std::chrono::high_resolution_clock::now();
                uint64_t postCallbacksNs = std::chrono::duration_cast<std::chrono::nanoseconds>(postEnd - postStart).count();

                uint64_t totalNs = std::chrono::duration_cast<std::chrono::nanoseconds>(postEnd - totalStart).count();

                ProcessEventProfiler::RecordCall(totalNs, preCallbacksNs, postCallbacksNs, originalNs);

                if (bCapturing && Function)
                {
                    ProcessEventCallStats stats;
                    stats.FunctionName = to_string(Function->GetName());
                    stats.TotalTimeNs = totalNs;
                    stats.PreCallbacksTimeNs = preCallbacksNs;
                    stats.PostCallbacksTimeNs = postCallbacksNs;
                    stats.OriginalFunctionTimeNs = originalNs;
                    ProcessEventProfiler::AddCapturedCall(std::move(stats));
                }

                return;
            }

            // Normal path - use base class implementation
            Base::Invoke(Context, Function, Parms);
        }
    };
#endif

    // Retrieves the TDetourInstance from the EDetourTarget value.
    template<EDetourTarget DetourTarget>
    inline TDetourTraits<DetourTarget>::Impl* GetDetourInstance()
    {
        using Impl = TDetourTraits<DetourTarget>::Impl;

        static Impl* Instance = new Impl();
        return Instance;
    }
}

#pragma pop_macro("ensure")