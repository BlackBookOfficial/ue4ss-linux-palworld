#pragma once

#include <functional>
#include <Unreal/Common.hpp>
#include <Unreal/FFrame.hpp>
#include <map>
#include <atomic>

namespace RC::Unreal
{
    class UObject;

    using UnrealScriptFunction = void(*)(UObject* Context, FFrame& TheStack, void* RESULT_DECL);

    class RC_UE_API UnrealScriptFunctionCallableContext
    {
    public:
        UObject* Context;
        FFrame& TheStack;
        void* RESULT_DECL;

        UnrealScriptFunctionCallableContext(UObject* Context, FFrame& TheStack, void* RESULT_DECL);

        template<typename ReturnType>
        auto SetReturnValue(ReturnType NewValue) -> void
        {
            *static_cast<ReturnType*>(RESULT_DECL) = NewValue;
        }

        template<typename ParamStruct>
        auto GetParams() -> ParamStruct&
        {
            return *static_cast<ParamStruct*>(static_cast<void*>(TheStack.Locals()));
        }
    };
    using UnrealScriptFunctionCallable = std::function<void(UnrealScriptFunctionCallableContext& Context, void* CustomData)>;
    using CallbackId = int32_t;

    struct UnrealScriptCallbackData
    {
        UnrealScriptFunctionCallable Callable;
        void* CustomData;
        std::atomic<bool> UnregistrationRequested{};
        UObject* FireOnInstance{};

        UnrealScriptCallbackData() = default;
        UnrealScriptCallbackData(UnrealScriptFunctionCallable Callable, void* CustomData, UObject* FireOnInstance) : Callable(Callable), CustomData(CustomData), FireOnInstance(FireOnInstance) {};
    };

    class RC_UE_API UnrealScriptFunctionData
    {
    private:
        UnrealScriptFunction OriginalFunc;
        std::map<int32_t, UnrealScriptCallbackData> PreCallbacks;
        std::map<int32_t, UnrealScriptCallbackData> PostCallbacks;

    private:
        static std::atomic<CallbackId> HookIndexCounter;

    public:
        std::atomic<bool> bIsMidExecution{};

    public:
        UnrealScriptFunctionData(UnrealScriptFunction OriginalFuncPtr);
        inline auto GetOriginalFuncPtr() const -> UnrealScriptFunction { return OriginalFunc; }

        CallbackId AddPreCallback(const UnrealScriptFunctionCallable& Callable, void* CustomData = nullptr, UObject* FireOnInstance = nullptr);
        CallbackId AddPostCallback(const UnrealScriptFunctionCallable& Callable, void* CustomData = nullptr, UObject* FireOnInstance = nullptr);
        bool RemoveCallback(CallbackId CallbackId);

        void RemoveAllCallbacks();

        void FirePreCallbacks(UnrealScriptFunctionCallableContext& Context);
        void FirePostCallbacks(UnrealScriptFunctionCallableContext& Context);

        UnrealScriptCallbackData* GetCallbackData(CallbackId);

        static CallbackId MakeNewId();
    };

    namespace Internal {
        using HookedUFunctionMap = std::unordered_map<const UFunction*, UnrealScriptFunctionData>;
        auto RC_UE_API GetHookedFunctionsMap() -> HookedUFunctionMap&;

        auto UnrealScriptFunctionHook(UObject* Context, FFrame& TheStack, void* RESULT_DECL) -> void;
    }
}


