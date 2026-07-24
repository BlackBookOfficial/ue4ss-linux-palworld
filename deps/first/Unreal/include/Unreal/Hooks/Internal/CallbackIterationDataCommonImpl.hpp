#pragma once
#include <String/StringType.hpp>
#include <Unreal/Hooks/GlobalCallbackId.hpp>
#include <Unreal/Hooks/Internal/SetOnceField.h>

namespace RC::Unreal::Hook::Internal
{
    struct FCallbackMetadata;

    class RC_UE_API FCallbackIterationDataCommonImpl
    {
    private:
        TSetOnceField<bool> bShouldPreventOriginalFunctionCall{};
        FCallbackMetadata* CurrentCallbackInfo{};
        StringViewType OwnerDetourName{};

    public:
        explicit FCallbackIterationDataCommonImpl(StringViewType InOwnerDetourName);

        void PreventOriginalFunctionCall();

        [[nodiscard]] bool OriginalFunctionCallPrevented() const;

        [[nodiscard]] GlobalCallbackId GetCallbackId() const;

        [[nodiscard]] StringViewType GetCallbackName() const;

        [[nodiscard]] StringViewType GetOwnerModName() const;

        [[nodiscard]] StringViewType GetDetourName() const;

        void RemoveSelf();

        void Log(StringViewType Msg) const;

        void SetCurrentCallbackInfo(FCallbackMetadata* Data);

        [[nodiscard]] FCallbackMetadata* GetCurrentCallbackInfo() const;

        [[nodiscard]] bool IsReadOnly() const;
    };
}