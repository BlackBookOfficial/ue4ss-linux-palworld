#include <Unreal/UnrealVersion.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

#define NOMINMAX
#ifdef _WIN32
#include <Windows.h>
#endif

#include <fmt/core.h>
#include <fmt/xchar.h>

namespace RC::Unreal
{
    int32_t Version::Major{-1};
    int32_t Version::Minor{-1};
    bool Version::DebugBuild{false};

    VersionStatus::VersionStatus(StatusCode StatusParam, StringType ErrorMessageParam) : Status(StatusParam), ErrorMessage(std::move(ErrorMessageParam)) {}

    auto Version::Initialize(void* Address) -> VersionStatus
    {
        uint16_t MajorVersion = Helper::Casting::ptr_cast_deref<uint16_t>(Address);
        uint16_t MinorVersion = Helper::Casting::ptr_cast_deref<uint16_t>(Address, 0x2);
        uint16_t PatchVersion = Helper::Casting::ptr_cast_deref<uint16_t>(Address, 0x4);

        if (MajorVersion < 4 || MajorVersion > 5)
        {
            return {VersionStatus::FAILURE, fmt::format(STR("Could not determine Unreal Engine version: major version was too big or too small ({})"), MajorVersion)};
        }

        if (MinorVersion > 30)
        {
            return {VersionStatus::FAILURE, fmt::format(STR("Could not determine Unreal Engine version: minor version was too big ({})"), MinorVersion)};
        }

        if (PatchVersion > 10)
        {
            return {VersionStatus::FAILURE, fmt::format(STR("Could not determine Unreal Engine version: patch version was too big ({})"), PatchVersion)};
        }

        const File::CharType* Branch = Helper::Casting::ptr_cast_deref<const File::CharType*>(Address, 0x10);
        void* BranchTest = Helper::Casting::ptr_cast_deref_safe<void*>(Branch, 0x0,
#ifdef _WIN32
            GetCurrentProcess()
#else
            nullptr
#endif
        );
        if (!BranchTest)
        {
            return {VersionStatus::FAILURE, fmt::format(STR("Could not determine Unreal Engine version: 'Branch' member variable FString data was nullptr"))};
        }

        auto BranchView = File::StringViewType{Branch};
        if (!BranchView.starts_with(STR("++")) && // Occurs in most games
            !BranchView.starts_with(STR("main")) && // Occurs in Dead Rock Galactic
            !BranchView.starts_with(STR("UE4"))) // Occurs in the 4.12 demo game
        {
            return {VersionStatus::FAILURE, fmt::format(STR("Could not determine Unreal Engine version: 'Branch' member variable FString does not start with '++'"))};
        }

        Major = static_cast<int32_t>(MajorVersion);
        Minor = static_cast<int32_t>(MinorVersion);

#if UNREAL_VERSION_RUN_TESTS == 1
        RunTests();
#endif

        return {VersionStatus::SUCCESS, STR("")};
    }

#if UNREAL_VERSION_RUN_TESTS == 1
    auto Version::RunTests() -> void
    {
        int32_t StashedMajor = Major;
        int32_t StashedMinor = Minor;

        Major = 4;
        Minor = 25;

        if (!IsEqual(4, 25))
        {
            throw std::runtime_error{"[UnrealVersion] Failed test #1 - !is_equal(4, 25) || Test ran with major = 4 and minor = 25"};
        }

        if (!IsAtLeast(4, 24))
        {
            throw std::runtime_error{"[UnrealVersion] Failed test #2 - !is_atleast(4, 24) || Test ran with major = 4 and minor = 25"};
        }

        if (IsAtMost(4, 24))
        {
            throw std::runtime_error{"[UnrealVersion] Failed test #3 - is_atmost(4, 24) || Test ran with major = 4 and minor = 25"};
        }

        if (IsBelow(4, 24))
        {
            throw std::runtime_error{"[UnrealVersion] Failed test #4 - is_below(4, 24) || Test ran with major = 4 and minor = 25"};
        }

        if (!IsAbove(4, 24))
        {
            throw std::runtime_error{"[UnrealVersion] Failed test #5 - !is_above(4, 24) || Test ran with major = 4 and minor = 25"};
        }

        Major = StashedMajor;
        Minor = StashedMinor;
    }
#endif
}
