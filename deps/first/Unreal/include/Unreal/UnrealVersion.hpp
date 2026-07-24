#pragma once

#include <cassert>
#include <utility>
#include <format>

#include <Helpers/ASM.hpp>
#include <Helpers/String.hpp>
#include <File/File.hpp>
// Using Common.hpp directly rather than UObjectGlobals.hpp to alleviate common circular include issues
#include <Unreal/Common.hpp>

#include <String/StringType.hpp>

#ifndef UNREAL_VERSION_RUN_TESTS
#define UNREAL_VERSION_RUN_TESTS 0
#endif

namespace RC::Unreal
{
    struct RC_UE_API VersionStatus
    {
        enum StatusCode
        {
            SUCCESS,
            FAILURE,
        };

        StringType ErrorMessage{};
        StatusCode Status{};

        VersionStatus() = default;
        VersionStatus(StatusCode StatusParam, StringType ErrorMessageParam);
    };

    class RC_UE_API Version
    {
    public:
        static int32_t Major;
        static int32_t Minor;
        static bool DebugBuild;

        auto static Initialize(void* Address) -> VersionStatus;

        [[nodiscard]]
        FORCEINLINE auto static IsEqual(int32_t major_p, int32_t minor_p) -> bool { return (Major == major_p && Minor == minor_p); }

        [[nodiscard]]
        FORCEINLINE auto static IsAtLeast(int32_t major_p, int32_t minor_p) -> bool { return ((Major > major_p) || (Major == major_p && Minor >= minor_p)); }

        [[nodiscard]]
        FORCEINLINE auto static IsAtMost(int32_t major_p, int32_t minor_p) -> bool { return ((Major < major_p) || (Major == major_p && Minor <= minor_p)); }

        [[nodiscard]]
        FORCEINLINE auto static IsBelow(int32_t major_p, int32_t minor_p) -> bool { return ((Major < major_p) || (Major == major_p && Minor < minor_p)); }

        [[nodiscard]]
        FORCEINLINE auto static IsAbove(int32_t major_p, int32_t minor_p) -> bool { return ((Major > major_p) || (Major == major_p && Minor > minor_p)); }

        [[nodiscard]]
        FORCEINLINE auto static IsDebug() -> bool { return DebugBuild; }

#if UNREAL_VERSION_RUN_TESTS == 1
        auto static RunTests() -> void;
#endif
    };
}