#include <stdexcept>

#include <Unreal/FText.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/UnrealVersion.hpp>

namespace RC::Unreal
{
    int32 FText::StaticSize_Private{-1};

    int32 FText::StaticSize()
    {
        if (StaticSize_Private < 0)
        {
            throw std::runtime_error{"[FText::StaticSize] StaticClassStorage is not valid"};
        }
        else
        {
            return StaticSize_Private;
        }
    }

    static FText& CopyFText(FText& Self, const FText& Other)
    {
        static const int32_t StaticSize = FText::StaticSize();
        if (StaticSize != sizeof(FText) && StaticSize < sizeof(FText))
        {
            // Memory layout doesn't match, let's try copy still, but make sure we don't overflow.
            // Yes, this a bit nasty, but it's a proven workaround for some games.
            // Also, previous to the introduction of this memcpy, we were treating FText as a POD type anyway,
            // so not calling assignment operators here doesn't change anything unless we properly implement TSharedRef in the future.
            std::memcpy(&Self, &Other, StaticSize);
        }
        else
        {
            Self.Data = Other.Data;
            Self.SharedRefCollector = Other.SharedRefCollector;
            Self.Flags = Other.Flags;
            Self.Unk = Other.Unk;
        }
        return Self;
    }

    FText::FText(const FText& Other)
    {
        CopyFText(*this, Other);
    }

    FText& FText::operator=(const FText& Other)
    {
        return CopyFText(*this, Other);
    }

    auto FText::ToFString() const -> FString
    {
        if (!Data) { std::abort(); }
        return UKismetTextLibrary::Conv_TextToString(*this);
    }

    auto FText::ToString() const -> StringType
    {
        if (!Data) { return {}; }
        return StringType(*ToFString());
    }

    auto FText::SetString(const FString&& NewString) -> void
    {
        FText Text = FText(std::forward<const FString>(NewString));

        Data = Text.Data;
        SharedRefCollector = Text.SharedRefCollector;
        Flags = Text.Flags;
        Unk = Text.Unk;
    }
}