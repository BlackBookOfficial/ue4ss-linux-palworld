#pragma once

#include <File/File.hpp>

namespace RC::Unreal
{
    class FPackageName
    {
    private:
        using FStringView = File::StringViewType;

    public:
        enum class EErrorCode
        {
            PackageNameUnknown,
            PackageNameEmptyPath,
            PackageNamePathNotMounted,
            PackageNameFullObjectPathNotAllowed,
            PackageNameContainsInvalidCharacters,
            LongPackageNames_PathTooShort,
            LongPackageNames_PathWithNoStartingSlash,
            LongPackageNames_PathWithTrailingSlash,
        };

    public:
        static bool IsShortPackageName(FStringView PossiblyLongName);

        static bool IsValidLongPackageName(FStringView InLongPackageName, bool bIncludeReadOnlyRoots = false, EErrorCode* OutReason = nullptr);
        static bool IsValidLongPackageName(FStringView InLongPackageName, bool bIncludeReadOnlyRoots, class FText* OutReason );

        static bool IsValidTextForLongPackageName(FStringView InLongPackageName, EErrorCode* OutReason = nullptr);
        static bool IsValidTextForLongPackageName(FStringView InLongPackageName, FText* OutReason);

        static bool DoesPackageNameContainInvalidCharacters(FStringView InLongPackageName, FText* OutReason);
        static bool DoesPackageNameContainInvalidCharacters(FStringView InLongPackageName, EErrorCode* OutReason = nullptr);
    };
}


