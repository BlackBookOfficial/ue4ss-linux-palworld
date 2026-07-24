#include <Unreal/Hooks/Internal/CallbackIterationDataCommonImpl.hpp>
#include <Unreal/Hooks/Internal/Metadata.hpp>

#include "DynamicOutput/Output.hpp"

namespace RC::Unreal::Hook::Internal
{
    FCallbackIterationDataCommonImpl::FCallbackIterationDataCommonImpl(const StringViewType InOwnerDetourName): OwnerDetourName(InOwnerDetourName)
    {
    }

    void FCallbackIterationDataCommonImpl::PreventOriginalFunctionCall()
    {
        if (IsReadOnly())
        {
            Output::send<LogLevel::Error>(STR("[{}.{}.{}] Error preventing original function call: Callback was registered as readonly!"),
                                          CurrentCallbackInfo->OwnerModName, OwnerDetourName, CurrentCallbackInfo->HookName);
            return;
        }
        bShouldPreventOriginalFunctionCall.TrySetField(true);
    }

    bool FCallbackIterationDataCommonImpl::OriginalFunctionCallPrevented() const
    {
        return bShouldPreventOriginalFunctionCall.IsSet() && bShouldPreventOriginalFunctionCall.GetField();
    }

    GlobalCallbackId FCallbackIterationDataCommonImpl::GetCallbackId() const
    {
        if (!CurrentCallbackInfo) throw std::runtime_error("GetCallbackId() may only be called during hook execution");
        return CurrentCallbackInfo->Id;
    }

    StringViewType FCallbackIterationDataCommonImpl::GetCallbackName() const
    {
        return CurrentCallbackInfo ? CurrentCallbackInfo->HookName : STR("NoCallback");
    }

    StringViewType FCallbackIterationDataCommonImpl::GetOwnerModName() const
    {
        return CurrentCallbackInfo ? CurrentCallbackInfo->OwnerModName : STR("NoCallback");
    }

    StringViewType FCallbackIterationDataCommonImpl::GetDetourName() const
    {
        return OwnerDetourName;
    }

    void FCallbackIterationDataCommonImpl::RemoveSelf()
    {
        if (!CurrentCallbackInfo) throw std::runtime_error("Can't call RemoveSelf (or any function within TCallbackIterationData) outside of a callback!");
        CurrentCallbackInfo->Invalidate();
    }

    void FCallbackIterationDataCommonImpl::Log(StringViewType Msg) const
    {
        if (!CurrentCallbackInfo) return;
        Output::send<LogLevel::Verbose>(STR("[{}.{}.{}] {}\n"),
                                        CurrentCallbackInfo->OwnerModName, OwnerDetourName, CurrentCallbackInfo->HookName, Msg);
    }

    void FCallbackIterationDataCommonImpl::SetCurrentCallbackInfo(Internal::FCallbackMetadata* Data)
    {
        CurrentCallbackInfo = Data;
    }

    FCallbackMetadata* FCallbackIterationDataCommonImpl::GetCurrentCallbackInfo() const
    {
        return CurrentCallbackInfo;
    }

    bool FCallbackIterationDataCommonImpl::IsReadOnly() const
    {
        return CurrentCallbackInfo && (CurrentCallbackInfo->Id & static_cast<uint64_t>(EGlobalCallbackAttributeFlags::Readonly));
    }
}