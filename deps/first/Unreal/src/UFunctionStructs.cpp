#include <Unreal/UFunctionStructs.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <DynamicOutput/Output.hpp>
#include <Helpers/Format.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>

namespace RC::Unreal
{
    std::atomic<CallbackId> UnrealScriptFunctionData::HookIndexCounter{1};

    UnrealScriptFunctionData::UnrealScriptFunctionData(UnrealScriptFunction OriginalFuncPtr) {
        this->OriginalFunc = OriginalFuncPtr;
    }

    CallbackId UnrealScriptFunctionData::AddPreCallback(const UnrealScriptFunctionCallable& Callable, void* CustomData, UObject* FireOnInstance)
    {
        CallbackId NewCallbackId = MakeNewId();
        this->PreCallbacks.emplace(std::piecewise_construct, std::forward_as_tuple(NewCallbackId), std::forward_as_tuple(Callable, CustomData, FireOnInstance));
        return NewCallbackId;
    }

    CallbackId UnrealScriptFunctionData::AddPostCallback(const UnrealScriptFunctionCallable& Callable, void* CustomData, UObject* FireOnInstance)
    {
        CallbackId NewCallbackId = MakeNewId();
        this->PostCallbacks.emplace(std::piecewise_construct, std::forward_as_tuple(NewCallbackId), std::forward_as_tuple(Callable, CustomData, FireOnInstance));
        return NewCallbackId;
    }

    bool UnrealScriptFunctionData::RemoveCallback(CallbackId CallbackId)
    {
        auto CallbackData = GetCallbackData(CallbackId);
        if (CallbackData)
        {
            if (bIsMidExecution)
            {
                // Hook will be unregistered after the callback is done executing.
                CallbackData->UnregistrationRequested = true;
                return true;
            }
            else
            {
                return PreCallbacks.erase(CallbackId) || PostCallbacks.erase(CallbackId);
            }
        }
        else
        {
            return false;
        }
    }

    void UnrealScriptFunctionData::RemoveAllCallbacks()
    {
        for (auto PreCallbackIterator = PreCallbacks.begin(); PreCallbackIterator != PreCallbacks.end();)
        {
            if (bIsMidExecution)
            {
                // Hook will be unregistered after the callback is done executing.
                PreCallbackIterator->second.UnregistrationRequested = true;
                ++PreCallbackIterator;
            }
            else
            {
                PreCallbackIterator = PreCallbacks.erase(PreCallbackIterator);
            }
        }

        for (auto PostCallbackIterator = PostCallbacks.begin(); PostCallbackIterator != PostCallbacks.end();)
        {
            if (bIsMidExecution)
            {
                // Hook will be unregistered after the callback is done executing.
                PostCallbackIterator->second.UnregistrationRequested = true;
                ++PostCallbackIterator;
            }
            else
            {
                PostCallbackIterator = PostCallbacks.erase(PostCallbackIterator);
            }
        }
    }

    void UnrealScriptFunctionData::FirePreCallbacks(UnrealScriptFunctionCallableContext& Context)
    {
        for (auto PreCallbackIterator = PreCallbacks.begin(); PreCallbackIterator != PreCallbacks.end();)
        {
            // Skip callbacks that don't match the instance filter
            if (PreCallbackIterator->second.FireOnInstance && PreCallbackIterator->second.FireOnInstance != Context.Context)
            {
                ++PreCallbackIterator;
                continue;
            }
            // Skip callbacks that have been marked for unregistration or have invalid Callable
            if (PreCallbackIterator->second.UnregistrationRequested || !PreCallbackIterator->second.Callable)
            {
                PreCallbackIterator = PreCallbacks.erase(PreCallbackIterator);
                continue;
            }
            PreCallbackIterator->second.Callable(Context, PreCallbackIterator->second.CustomData);
            if (PreCallbackIterator->second.UnregistrationRequested)
            {
                PreCallbackIterator = PreCallbacks.erase(PreCallbackIterator);
            }
            else
            {
                ++PreCallbackIterator;
            }
        }
    }

    void UnrealScriptFunctionData::FirePostCallbacks(UnrealScriptFunctionCallableContext& Context)
    {
        for (auto PostCallbackIterator = PostCallbacks.begin(); PostCallbackIterator != PostCallbacks.end();)
        {
            // Skip callbacks that have been marked for unregistration or have invalid Callable
            if (PostCallbackIterator->second.UnregistrationRequested || !PostCallbackIterator->second.Callable)
            {
                PostCallbackIterator = PostCallbacks.erase(PostCallbackIterator);
                continue;
            }
            PostCallbackIterator->second.Callable(Context, PostCallbackIterator->second.CustomData);
            if (PostCallbackIterator->second.UnregistrationRequested)
            {
                PostCallbackIterator = PostCallbacks.erase(PostCallbackIterator);
            }
            else
            {
                ++PostCallbackIterator;
            }
        }
    }

    UnrealScriptCallbackData* UnrealScriptFunctionData::GetCallbackData(CallbackId CallbackId)
    {
        auto PreIterator = PreCallbacks.find(CallbackId);
        if (PreIterator != PreCallbacks.end()) { return &PreIterator->second; }

        auto PostIterator = PostCallbacks.find(CallbackId);
        if (PostIterator != PostCallbacks.end()) { return &PostIterator->second; }

        return nullptr;
    }

    CallbackId UnrealScriptFunctionData::MakeNewId()
    {
        return HookIndexCounter++;
    }

    UnrealScriptFunctionCallableContext::UnrealScriptFunctionCallableContext(UObject* Context, FFrame& TheStack, void* RESULT_DECL)
            : Context(Context),
              TheStack(TheStack),
              RESULT_DECL(RESULT_DECL) {}

    static Internal::HookedUFunctionMap GHookedScriptFunctions{};

    auto Internal::GetHookedFunctionsMap() -> HookedUFunctionMap&
    {
        return GHookedScriptFunctions;
    }

    auto Internal::UnrealScriptFunctionHook(UObject* Context, FFrame& TheStack, void* RESULT_DECL) -> void
    {
        try
        {
            HookedUFunctionMap& FunctionMap = GetHookedFunctionsMap();
            auto FunctionBeingExecuted = TheStack.CurrentNativeFunction() ? TheStack.CurrentNativeFunction() : *std::bit_cast<UFunction**>(&TheStack.Code()[0-sizeof(uint64)]);
            auto Iterator = FunctionMap.find(FunctionBeingExecuted);
            if (Iterator == FunctionMap.end() && TheStack.Code())
            {
                // TODO: Is &Code[0-sizeof(uint64)] always a valid pointer to access ?
                //       We don't care if the deref ends up being garbage, the map lookup will fail and save us.
                //       But if the address of Code-8 is invalid, that will cause a crash.
                //       There has to be a better way to do this surely ?
                FunctionBeingExecuted = *std::bit_cast<UFunction**>(&TheStack.Code()[0-sizeof(uint64)]);
                Iterator = FunctionMap.find(FunctionBeingExecuted);
            }

            if (Iterator == FunctionMap.end())
            {
                // For some reason, CurrentNativeFunction isn't hooked.
                // This could be due to a bug.
                // Either way, if CurrentNativeFunction is nullptr, it might be safe to call ProcessInternal.
                // If CurrentNativeFunction is non-nullptr, then we call whatever is stored in CurrentNativeFunction.Func.
                if (FunctionBeingExecuted)
                {
                    Output::send<LogLevel::Warning>(STR("Tried to execute UFunction::FuncPtr hook but there was no function map entry for UFunction:\n\t{:016X} {}.\n\tExecuting original function instead.\n"),
                                                    std::bit_cast<uintptr_t>(FunctionBeingExecuted),
                                                    FunctionBeingExecuted ? FunctionBeingExecuted->GetFullName() : STR("None"));
                    FunctionBeingExecuted->GetFuncPtr()(Context, TheStack, RESULT_DECL);
                }
                else
                {
                    Output::send<LogLevel::Warning>(STR("Tried to execute UFunction::FuncPtr hook but there was no function map entry for UFunction:\n\t{:016X} {}.\n\tNo original function to execute.\n\tExecuting ProcessInternal instead.\n"),
                                                    std::bit_cast<uintptr_t>(FunctionBeingExecuted),
                                                    FunctionBeingExecuted ? FunctionBeingExecuted->GetFullName() : STR("None"));
                    static auto Object_ExecuteUbergraph = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR("/Script/CoreUObject.Object:ExecuteUbergraph"));
                    static auto ProcessInternal = Object_ExecuteUbergraph->GetFuncPtr();
                    Output::send(STR("Object_ExecuteUbergraph: {}\n"), (void*)Object_ExecuteUbergraph);
                    Output::send(STR("ProcessInternal: {}\n"), (void*)ProcessInternal);
                    ProcessInternal(Context, TheStack, RESULT_DECL);
                }
            }
            else
            {
                FFrame* NewStackPtr = &TheStack;
                std::map<FProperty*, FOutParmRec*> OriginalOutParmsMap; // Map to track original out params

                if (TheStack.Code() && GNatives_Internal)
                {
                    // Create a new stack frame
                    NewStackPtr = FFrame::MallocAndMemsetNewFrame();
                    NewStackPtr->Object() = Context;
                    NewStackPtr->Node() = FunctionBeingExecuted;
                    NewStackPtr->PreviousFrame() = &TheStack;
                    if (Version::IsBelow(4, 25))
                    {
                        NewStackPtr->PropertyChainForCompiledIn() = std::bit_cast<FField*>(FunctionBeingExecuted->GetChildren().Get());
                    }
                    else
                    {
                        NewStackPtr->PropertyChainForCompiledIn() = FunctionBeingExecuted->GetChildProperties();
                    }
                    auto NewLocals = static_cast<uint8*>(alloca(FunctionBeingExecuted->GetParmsSize()));
                    NewStackPtr->Locals() = NewLocals;

                    // Map out parameters for later use
                    FOutParmRec* CurrentOutParm = TheStack.OutParms();
                    while (CurrentOutParm)
                    {
                        OriginalOutParmsMap[CurrentOutParm->Property] = CurrentOutParm;
                        CurrentOutParm = CurrentOutParm->NextOutParm;
                    }

                    // Loop through parameters and evaluate them
                    for (FProperty* prop : TFieldRange<FProperty>(FunctionBeingExecuted, EFieldIterationFlags::IncludeDeprecated))
                    {
                        // Skip non parameters and return values
                        if (!prop->HasAnyPropertyFlags(CPF_Parm) || prop->HasAnyPropertyFlags(CPF_ReturnParm)) 
                            continue;

                        // Initialize property storage
                        uint8* PropertyData = prop->ContainerPtrToValuePtr<uint8>(NewStackPtr->Locals());
                        prop->InitializeValue(PropertyData);

                        if (prop->HasAnyPropertyFlags(CPF_OutParm))
                        {
                            // Create new out parameter slot and add it to the linked list
                            FOutParmRec* NewOutParam = static_cast<FOutParmRec*>(alloca(sizeof(Unreal::FOutParmRec)));
                            NewOutParam->Property = prop;
                            NewOutParam->NextOutParm = NewStackPtr->OutParms();
                            NewStackPtr->OutParms() = NewOutParam;

                            // Step the original stack to get the address for the out param
                            TheStack.StepCompiledIn(PropertyData, prop);
                            NewOutParam->PropAddr = TheStack.MostRecentPropertyAddress();
                        }
                        else
                        {
                            // Regular parameter - evaluate it from the original stack
                            TheStack.StepCompiledIn(PropertyData, prop);
                        }
                    }

                    // Code pointer needs to move past the parameters
                    TheStack.Code() += !!TheStack.Code();
                }

                // Create function context with our (possibly new) stack frame
                UnrealScriptFunctionCallableContext FuncContext(Context, *NewStackPtr, RESULT_DECL);
                
                Iterator->second.bIsMidExecution = true;

                try
                {
                    // Fire pre callbacks with all parameters now properly populated
                    Iterator->second.FirePreCallbacks(FuncContext);
                }
                catch (std::exception& e)
                {
                    Output::send(STR("Error executing hook pre-callback {}: {}\n"), 
                                 FunctionBeingExecuted->GetPathName(), ensure_str(e.what()));
                }

                // Execute the original function with our stack
                Iterator->second.GetOriginalFuncPtr()(Context, *NewStackPtr, RESULT_DECL);
                
                try
                {
                    // Fire post callbacks
                    Iterator->second.FirePostCallbacks(FuncContext);
                }
                catch (std::exception& e)
                {
                    Output::send(STR("Error executing hook post-callback {}: {}\n"), 
                                 FunctionBeingExecuted->GetPathName(), ensure_str(e.what()));
                }

                // Copy out parameter values back to the original frame
                if (TheStack.Code() && GNatives_Internal)
                {
                    // Copy out parameter values back to the original frame
                    for (FOutParmRec* OutParam = NewStackPtr->OutParms(); OutParam; OutParam = OutParam->NextOutParm)
                    {
                        auto OriginalIt = OriginalOutParmsMap.find(OutParam->Property);
                        if (OriginalIt != OriginalOutParmsMap.end())
                        {
                            // Copy the value back to the original out parameter
                            OutParam->Property->CopyCompleteValue(OriginalIt->second->PropAddr, OutParam->PropAddr);
                        }
                    }

                    // Clean up the temporary stack frame
                    for (FProperty* prop : TFieldRange<FProperty>(FunctionBeingExecuted, EFieldIterationFlags::IncludeDeprecated))
                    {
                        if (!prop->HasAnyPropertyFlags(CPF_Parm)) continue;
                        if (prop->HasAnyPropertyFlags(CPF_ReturnParm)) continue;

                        uint8* PropertyData = prop->ContainerPtrToValuePtr<uint8>(NewStackPtr->Locals());
                        prop->DestroyValue(PropertyData);
                    }
                    FMemory::Free(NewStackPtr);
                }
                    
                Iterator->second.bIsMidExecution = false;
            }
        }
        catch (std::exception& e)
        {
            Output::send(STR("Error executing hooked function: {}\n"), ensure_str(e.what()));
        }
    }
}
