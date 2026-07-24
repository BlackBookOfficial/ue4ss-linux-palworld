#pragma once

#include <String/StringType.hpp>
#include <DynamicOutput/DynamicOutput.hpp>

#include <Unreal/Hooks/Internal/CallbackIterationDataCommonImpl.hpp>
#include <Unreal/Hooks/Internal/Common.hpp>
#include <Unreal/Hooks/Internal/SetOnceField.h>

// This header intentionally contains only the public *shape* of callback iteration data.
// All operational logic lives in CallbackIterationData.cpp via explicit template instantiations.

namespace RC::Unreal { class UObject; }

namespace RC::Unreal::Hook
{
    // Non-void specialization.
    template<typename ReturnType>
    class TCallbackIterationData
    {
    UE_HOOK_PRIVATE:
        Internal::FCallbackIterationDataCommonImpl CommonImpl;

        Internal::TSetOnceField<ReturnType> ReturnOverride{};
        ReturnType OriginalFunctionCallResult{};
        Internal::FCallbackMetadata* ReturnOverrideSetter{};

    public:
        explicit TCallbackIterationData(StringViewType OwnerDetourName);
        TCallbackIterationData(const TCallbackIterationData&) = delete;
        TCallbackIterationData(TCallbackIterationData&&) = delete;
        TCallbackIterationData& operator=(const TCallbackIterationData&) = delete;
        TCallbackIterationData& operator=(TCallbackIterationData&&) = delete;
        ~TCallbackIterationData();

        // Prevent the original function from running. Does nothing in a posthook callback, but will still make checks to OriginalFunctionCallPrevented return true.
        // If the original function call is prevented and a return value override isn't supplied via TrySetReturnValue,
        // a default-constructed instance of the return type will be returned to the game, which is often 'false' or 'nullptr',
        // which is usually not desirable.
        void PreventOriginalFunctionCall();

        // Returns true if any callback that's been executed so far has called PreventOriginalFunctionCall.
        [[nodiscard]] bool OriginalFunctionCallPrevented() const;

        // Get the currently executing callback's registered name.
        [[nodiscard]] StringViewType GetCallbackName() const;

        // Get the currently executing callback's registered owner's name.
        [[nodiscard]] StringViewType GetOwnerModName() const;

        // Get the name of the TDetourInstance executing this callback.
        [[nodiscard]] StringViewType GetDetourName() const;

        // Removes the currently executing callback.
        // WARNING: THIS IS THE ONLY SAFE WAY FOR A CALLBACK TO REMOVE THEMSELVES WHILE EXECUTING!!!
        // Calling UnregisterCallback from within the callback you're trying to unregister, directly or indirectly,
        // will result in a deadlock and freeze/crash.
        void RemoveSelf();

        // Logs a message with the metadata of the current callback attached.
        void Log(StringViewType Msg) const;

        // Returns true if the currently executing callback is a 'readonly' callback.
        [[nodiscard]] bool IsReadOnly() const;

        // Attempts to set the value that will be returned instead of the result from the original function call.
        // Returns true if the attempt is successful, false if another callback has already overridden it. Remember
        // that mods have a defined load order, and callbacks execute in the order they're registered, so the first
        // mod to load (i.e. has the highest priority) gets precedence when setting the return value. Note that a mod
        // with higher precedence will lose that precedence if they unregister their hook.
        bool TrySetReturnValue(ReturnType Value);

        // Get the return value that will be returned by the hooked function at the current point of execution.
        // If a hook overrode the return value, it will be that value, otherwise it will be
        // the result of calling the original function. If the function hasn't been called yet
        // (executing a prehook) and no return value override has been provided, this is a
        // default-constructed instance of the ReturnType.
        [[nodiscard]] ReturnType GetCurrentResolvedReturnValue() const;

        // Returns true if the return value has been overridden.
        [[nodiscard]] bool IsReturnValueOverrode() const;

        // Returns the overridden return value supplied by a hook, or a default-constructed instance of the
        // return value. Because the return value can be a bool, you should call IsReturnValueOverrode to help
        // deduce whether this is actually the return value override.
        [[nodiscard]] ReturnType GetReturnValueOverride() const;

        // Returns the original function call result. May not be used if an override is provided by any hook, and
        // in a prehook, this is the default-constructed instance of the ReturnType.
        [[nodiscard]] ReturnType GetOriginalFunctionCallResult() const;

    UE_HOOK_PRIVATE:
        friend void SetOriginalFunctionCallResult(auto& IterationData, void* Value);
        friend void SetCurrentCallbackInfo(auto& IterationData, Internal::FCallbackMetadata* Data);
        friend Internal::FCallbackMetadata* GetCurrentCallbackInfo(auto& IterationData);

        void SetOriginalFunctionCallResult(void* Value);
        void SetCurrentCallbackInfo(Internal::FCallbackMetadata* Data);
        Internal::FCallbackMetadata* GetCurrentCallbackInfo();
    };

    // Void specialization.
    template<>
    class TCallbackIterationData<void>
    {
    UE_HOOK_PRIVATE:
        Internal::FCallbackIterationDataCommonImpl CommonImpl;

    public:
        explicit TCallbackIterationData(StringViewType OwnerDetourName);
        TCallbackIterationData(const TCallbackIterationData&) = delete;
        TCallbackIterationData(TCallbackIterationData&&) = delete;
        TCallbackIterationData& operator=(const TCallbackIterationData&) = delete;
        TCallbackIterationData& operator=(TCallbackIterationData&&) = delete;
        ~TCallbackIterationData();

        // Prevent the original function from running. Does nothing in a posthook callback, but will still make checks to OriginalFunctionCallPrevented return true.
        // If the original function call is prevented and a return value override isn't supplied via TrySetReturnValue,
        // a default-constructed instance of the return type will be returned to the game, which is often 'false' or 'nullptr',
        // which is usually not desirable.
        void PreventOriginalFunctionCall();

        // Returns true if any callback that's been executed so far has called PreventOriginalFunctionCall.
        [[nodiscard]] bool OriginalFunctionCallPrevented() const;

        // Get the currently executing callback's registered name.
        [[nodiscard]] StringViewType GetCallbackName() const;

        // Get the currently executing callback's registered owner's name.
        [[nodiscard]] StringViewType GetOwnerModName() const;

        // Get the name of the TDetourInstance executing this callback.
        [[nodiscard]] StringViewType GetDetourName() const;

        // Removes the currently executing callback.
        // WARNING: THIS IS THE ONLY SAFE WAY FOR A CALLBACK TO REMOVE THEMSELVES WHILE EXECUTING!!!
        // Calling UnregisterCallback from within the callback you're trying to unregister, directly or indirectly,
        // will result in a deadlock and freeze/crash.
        void RemoveSelf();

        // Logs a message with the metadata of the current callback attached.
        void Log(StringViewType Msg) const;

        // Returns true if the currently executing callback is a 'readonly' callback.
        [[nodiscard]] bool IsReadOnly() const;

    UE_HOOK_PRIVATE:
        friend void SetCurrentCallbackInfo(auto& IterationData, Internal::FCallbackMetadata* Data);
        friend Internal::FCallbackMetadata* GetCurrentCallbackInfo(auto& IterationData);

        void SetCurrentCallbackInfo(Internal::FCallbackMetadata* Data);
        Internal::FCallbackMetadata* GetCurrentCallbackInfo();
    };

    // =========================
    // Non-void ReturnType
    // =========================
    template<typename ReturnType>
    TCallbackIterationData<ReturnType>::TCallbackIterationData(const StringViewType OwnerDetourName)
        : CommonImpl(OwnerDetourName)
    {
    }

    template<typename ReturnType>
    TCallbackIterationData<ReturnType>::~TCallbackIterationData() = default;

    template<typename ReturnType>
    void TCallbackIterationData<ReturnType>::PreventOriginalFunctionCall()
    {
        return CommonImpl.PreventOriginalFunctionCall();
    }

    template<typename ReturnType>
    bool TCallbackIterationData<ReturnType>::OriginalFunctionCallPrevented() const
    {
        return CommonImpl.OriginalFunctionCallPrevented();
    }

    template<typename ReturnType>
    StringViewType TCallbackIterationData<ReturnType>::GetCallbackName() const
    {
        return CommonImpl.GetCallbackName();
    }

    template<typename ReturnType>
    StringViewType TCallbackIterationData<ReturnType>::GetOwnerModName() const
    {
        return CommonImpl.GetOwnerModName();
    }

    template<typename ReturnType>
    StringViewType TCallbackIterationData<ReturnType>::GetDetourName() const
    {
        return CommonImpl.GetDetourName();
    }

    template<typename ReturnType>
    void TCallbackIterationData<ReturnType>::RemoveSelf()
    {
        return CommonImpl.RemoveSelf();
    }

    template<typename ReturnType>
    void TCallbackIterationData<ReturnType>::Log(const StringViewType Msg) const
    {
        return CommonImpl.Log(Msg);
    }

    template<typename ReturnType>
    bool TCallbackIterationData<ReturnType>::IsReadOnly() const
    {
        return CommonImpl.IsReadOnly();
    }

    RC_UE_API StringType GetOwnerModNameFromMetadata(Internal::FCallbackMetadata* Metadata);
    RC_UE_API StringType GetHookNameFromMetadata(Internal::FCallbackMetadata* Metadata);

    template<typename ReturnType>
    bool TCallbackIterationData<ReturnType>::TrySetReturnValue(ReturnType Value)
    {
        if (CommonImpl.IsReadOnly())
        {
            Output::send<LogLevel::Error>(STR("[{}.{}.{}] Error setting return value: Callback was registered as readonly!\n"),
                                          CommonImpl.GetOwnerModName(), CommonImpl.GetDetourName(), CommonImpl.GetCallbackName());
            return false;
        }

        if (ReturnOverride.TrySetField(Value))
        {
            ReturnOverrideSetter = CommonImpl.GetCurrentCallbackInfo();
            return true;
        }

        // If TrySetField fails, then ReturnOverrideSetter should not be nullptr.
        if constexpr (std::equality_comparable<ReturnType>)
        {
            if (Value != ReturnOverride.GetField())
            {
                Output::send<LogLevel::Error>(
                    STR("[{}.{}.{}] Error setting return value because [{}.{}.{}] takes precedence! Change the load order of mods to change precendence, though compatibility changes may be needed!\n"),
                    CommonImpl.GetOwnerModName(), CommonImpl.GetDetourName(), CommonImpl.GetCallbackName(),
                    GetOwnerModNameFromMetadata(ReturnOverrideSetter), CommonImpl.GetDetourName(), GetHookNameFromMetadata(ReturnOverrideSetter));
            }
            else
            {
                Output::send<LogLevel::Warning>(
                    STR("[{}.{}.{}] Error setting return value because [{}.{}.{}] takes precedence! However, both mods tried to set the same return value, so there's not likely to be an issue.\n"),
                    CommonImpl.GetOwnerModName(), CommonImpl.GetDetourName(), CommonImpl.GetCallbackName(),
                    GetOwnerModNameFromMetadata(ReturnOverrideSetter), CommonImpl.GetDetourName(), GetHookNameFromMetadata(ReturnOverrideSetter));
            }
        }
        else
        {
            Output::send<LogLevel::Error>(
                STR("[{}.{}.{}] Error setting return value because [{}.{}.{}] takes precedence! Change the load order of mods to change precendence, though compatibility changes may be needed!\n"),
                CommonImpl.GetOwnerModName(), CommonImpl.GetDetourName(), CommonImpl.GetCallbackName(),
                GetOwnerModNameFromMetadata(ReturnOverrideSetter), CommonImpl.GetDetourName(), GetHookNameFromMetadata(ReturnOverrideSetter));
        }

        return false;
    }

    template<typename ReturnType>
    ReturnType TCallbackIterationData<ReturnType>::GetCurrentResolvedReturnValue() const
    {
        return IsReturnValueOverrode() ? GetReturnValueOverride() : GetOriginalFunctionCallResult();
    }

    template<typename ReturnType>
    bool TCallbackIterationData<ReturnType>::IsReturnValueOverrode() const
    {
        return ReturnOverride.IsSet();
    }

    template<typename ReturnType>
    ReturnType TCallbackIterationData<ReturnType>::GetReturnValueOverride() const
    {
        return ReturnOverride.GetField();
    }

    template<typename ReturnType>
    ReturnType TCallbackIterationData<ReturnType>::GetOriginalFunctionCallResult() const
    {
        return OriginalFunctionCallResult;
    }

    template<typename ReturnType>
    void TCallbackIterationData<ReturnType>::SetOriginalFunctionCallResult(void* Value)
    {
        OriginalFunctionCallResult = *static_cast<ReturnType*>(Value);
    }

    template<typename ReturnType>
    void TCallbackIterationData<ReturnType>::SetCurrentCallbackInfo(Internal::FCallbackMetadata* Data)
    {
        return CommonImpl.SetCurrentCallbackInfo(Data);
    }

    template<typename ReturnType>
    Internal::FCallbackMetadata* TCallbackIterationData<ReturnType>::GetCurrentCallbackInfo()
    {
        return CommonImpl.GetCurrentCallbackInfo();
    }

    // =========================
    // void specialization
    // =========================
    inline TCallbackIterationData<void>::TCallbackIterationData(const StringViewType OwnerDetourName)
        : CommonImpl(OwnerDetourName)
    {
    }

    inline TCallbackIterationData<void>::~TCallbackIterationData() = default;

    inline void TCallbackIterationData<void>::PreventOriginalFunctionCall()
    {
        return CommonImpl.PreventOriginalFunctionCall();
    }

    inline bool TCallbackIterationData<void>::OriginalFunctionCallPrevented() const
    {
        return CommonImpl.OriginalFunctionCallPrevented();
    }

    inline StringViewType TCallbackIterationData<void>::GetCallbackName() const
    {
        return CommonImpl.GetCallbackName();
    }

    inline StringViewType TCallbackIterationData<void>::GetOwnerModName() const
    {
        return CommonImpl.GetOwnerModName();
    }

    inline StringViewType TCallbackIterationData<void>::GetDetourName() const
    {
        return CommonImpl.GetDetourName();
    }

    inline void TCallbackIterationData<void>::RemoveSelf()
    {
        return CommonImpl.RemoveSelf();
    }

    inline void TCallbackIterationData<void>::Log(const StringViewType Msg) const
    {
        return CommonImpl.Log(Msg);
    }

    inline bool TCallbackIterationData<void>::IsReadOnly() const
    {
        return CommonImpl.IsReadOnly();
    }

    inline void TCallbackIterationData<void>::SetCurrentCallbackInfo(Internal::FCallbackMetadata* Data)
    {
        return CommonImpl.SetCurrentCallbackInfo(Data);
    }

    inline Internal::FCallbackMetadata* TCallbackIterationData<void>::GetCurrentCallbackInfo()
    {
        return CommonImpl.GetCurrentCallbackInfo();
    }
}
