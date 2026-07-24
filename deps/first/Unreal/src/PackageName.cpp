#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/PackageName.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/FText.hpp>

namespace RC::Unreal
{
    namespace PackageNameConstants
    {
        const int32 MinPackageNameLength = 4;
    }

    bool FPackageName::IsShortPackageName(FStringView PossiblyLongName)
    {
        for (TCHAR Char : PossiblyLongName)
        {
            if (Char == '/')
            {
                return false;
            }
        }
        return true;
    }

    bool FPackageName::IsValidLongPackageName(FStringView InLongPackageName, bool bIncludeReadOnlyRoots /*= false*/, EErrorCode* OutReason /*= nullptr */)
    {
        (void)bIncludeReadOnlyRoots;

        if (!IsValidTextForLongPackageName(InLongPackageName, OutReason))
        {
            return false;
        }

        // We're supposed to be verifying that the roots are valid here, but we're skipping this step.
        return true;
    }

    bool FPackageName::IsValidLongPackageName(FStringView InLongPackageName, bool bIncludeReadOnlyRoots, FText* OutReason)
    {
        (void)OutReason;

        EErrorCode Reason;
        if (!IsValidLongPackageName(InLongPackageName, bIncludeReadOnlyRoots, &Reason))
        {
            // We're supposed to resolve the OutReason here, but we're skipping this step.
            return false;
        }
        return true;
    }

    bool FPackageName::IsValidTextForLongPackageName(FStringView InLongPackageName, FText* OutReason)
    {
        (void)OutReason;

        EErrorCode Reason;
        if (!IsValidTextForLongPackageName(InLongPackageName, &Reason))
        {
            // We're supposed to set OutReason here, but we're skipping this step.
            return false;
        }
        return true;
    }

    bool FPackageName::IsValidTextForLongPackageName(FStringView InLongPackageName, EErrorCode* OutReason /*= nullptr */)
    {
        if (InLongPackageName.length() < PackageNameConstants::MinPackageNameLength)
        {
            if (OutReason) *OutReason = EErrorCode::LongPackageNames_PathTooShort;
            return false;
        }
        if (InLongPackageName[0] != '/')
        {
            if (OutReason) *OutReason = EErrorCode::LongPackageNames_PathWithNoStartingSlash;
            return false;
        }
        if (InLongPackageName[InLongPackageName.length() - 1] == '/')
        {
            if (OutReason) *OutReason = EErrorCode::LongPackageNames_PathWithTrailingSlash;
            return false;
        }
        if (DoesPackageNameContainInvalidCharacters(InLongPackageName, OutReason))
        {
            return false;
        }
        if (OutReason) *OutReason = EErrorCode::PackageNameUnknown;
        return true;
    }

    bool FPackageName::DoesPackageNameContainInvalidCharacters(FStringView InLongPackageName, FText* OutReason)
    {
        (void)OutReason;

        EErrorCode Reason;
        if (DoesPackageNameContainInvalidCharacters(InLongPackageName, &Reason))
        {
            // We're supposed to set OutReason here, but we're skipping this step.
            return true;
        }
        return false;
    }

    bool FPackageName::DoesPackageNameContainInvalidCharacters(FStringView InLongPackageName, EErrorCode* OutReason /*= nullptr */)
    {
        File::StringType MatchedInvalidChars{};
        for (const TCHAR* InvalidCharacters = INVALID_LONGPACKAGE_CHARACTERS;  *InvalidCharacters; ++InvalidCharacters)
        {
            FStringView::size_type OutIndex = InLongPackageName.find(*InvalidCharacters);
            if (OutIndex != InLongPackageName.npos)
            {
                MatchedInvalidChars += *InvalidCharacters;
            }
        }
        if (MatchedInvalidChars.length())
        {
            if (OutReason) *OutReason = EErrorCode::PackageNameContainsInvalidCharacters;
            return true;
        }
        if (OutReason) *OutReason = EErrorCode::PackageNameUnknown;
        return false;
    }
}
