#pragma once

#include <string>

#include <Function/Function.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/ITextData.hpp>
#include <Unreal/UKismetTextLibrary.hpp>

namespace RC::Unreal
{
    class FString;

    class RC_UE_API FText
    {
    private:
        friend class TypeChecker;

    public:
        static int32 StaticSize_Private;
        static int32 StaticSize();
    public:
        ITextData* Data{nullptr};
        void* SharedRefCollector{nullptr};
        uint32 Flags;
        uint32 Unk;

    private:
        auto construct_with_string(const FString&& String) -> void
        {
            *this = UKismetTextLibrary::Conv_StringToText(std::forward<const FString>(String));
        }

    public:
        FText() = default;

        explicit FText(const FString&& String)
        {
            construct_with_string(std::forward<const FString>(String));
        }

        explicit FText(const CharType* String)
        {
            FString Str = FString(FromCharTypePtr<TCHAR>(String));
            construct_with_string(std::forward<const FString>(Str));
        }

        explicit FText(StringViewType String) : FText(String.data())
        {
        }

        FText(const FText& Other);

        FText& operator=(const FText& Other);

        auto inline operator==(const FString& Other) const -> bool
        {
            return ToFString() == Other;
        }

        auto inline operator==(const CharType* Other) const -> bool
        {
            return StringType(*ToFString()) == Other;
        }

        // Beware: Unsafe to call 'ToFString' as 'Data' may be nullptr, call 'ToString' instead.
        auto ToFString() const -> FString;
        auto ToString() const -> StringType;

        auto SetString(const FString&&) -> void;
    };
}