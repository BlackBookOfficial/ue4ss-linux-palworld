#pragma once
#include <cstdint>
#include <limits>
#include <Unreal/Common.hpp>
#include <String/StringType.hpp>

namespace RC::Unreal::Hook::Internal
{
    enum class EHookType { Pre, Post };

#if defined(UE_HOOK_TEST)
    #define RC_UE_HOOK_TEST_ENABLED 1
#else
    #define RC_UE_HOOK_TEST_ENABLED 0
#endif

#define RC_UE_HOOK_GLOBAL_CALLBACK_ATTRIBUTE_FLAGS(X) \
    X(Readonly,(uint64_t{1} << 63))         \
    X(Once,    (uint64_t{1} << 62))         \
    X(Prehook, (uint64_t{1} << 61))

#define RC_UE_HOOK_DETOUR_TARGETS(X) \
    X(StaticConstructObject,           (uint64_t{1} << 60)) \
    X(ProcessEvent,                    (uint64_t{1} << 59)) \
    X(ProcessConsoleExec,              (uint64_t{1} << 58)) \
    X(UStructLink,                     (uint64_t{1} << 57)) \
    X(ProcessInternal,                 (uint64_t{1} << 56)) \
    X(ProcessLocalScriptFunction,      (uint64_t{1} << 55)) \
    X(LoadMap,                         (uint64_t{1} << 54)) \
    X(EngineTick,                      (uint64_t{1} << 53)) \
    X(InitGameState,                   (uint64_t{1} << 52)) \
    X(BeginPlay,                       (uint64_t{1} << 51)) \
    X(EndPlay,                         (uint64_t{1} << 50)) \
    X(AActorTick,                      (uint64_t{1} << 49)) \
    X(GameViewportClientTick,          (uint64_t{1} << 48)) \
    X(CallFunctionByNameWithArguments, (uint64_t{1} << 47)) \
    X(ULocalPlayerExec,                (uint64_t{1} << 46)) \
    X(FNameConstructor,                (uint64_t{1} << 45))

    inline constexpr uint64_t MinNonZero(const uint64_t A, const uint64_t B) noexcept
    {
        if (A == 0) return B;
        if (B == 0) return A;
        return (A < B) ? A : B;
    }

    // Lowest detour bit from the *maintained* list above.
    inline constexpr uint64_t ComputeLowestDetourTargetBit() noexcept
    {
        uint64_t Lowest = std::numeric_limits<uint64_t>::max();
#define RC_MIN_LOWEST(name, value) Lowest = MinNonZero(Lowest, (value));
        RC_UE_HOOK_DETOUR_TARGETS(RC_MIN_LOWEST)
#undef RC_MIN_LOWEST
        return Lowest;
    }

    inline constexpr uint64_t LOWEST_DETOUR_TARGET_BIT = ComputeLowestDetourTargetBit();
    static_assert(LOWEST_DETOUR_TARGET_BIT != std::numeric_limits<uint64_t>::max(),
                  "RC_UE_HOOK_DETOUR_TARGETS must contain at least one entry.");

#if RC_UE_HOOK_TEST_ENABLED
    // Auto-pick the next two lower bits, so maintainers never hand-edit these.
    inline constexpr uint64_t VOID_TEST_DETOUR_BIT    = (LOWEST_DETOUR_TARGET_BIT >> 1);
    inline constexpr uint64_t NONVOID_TEST_DETOUR_BIT = (LOWEST_DETOUR_TARGET_BIT >> 2);

    static_assert(VOID_TEST_DETOUR_BIT != 0 && NONVOID_TEST_DETOUR_BIT != 0,
                  "Not enough remaining detour-bit space for hook tests.");
    static_assert((VOID_TEST_DETOUR_BIT & (VOID_TEST_DETOUR_BIT - 1)) == 0 &&
                  (NONVOID_TEST_DETOUR_BIT & (NONVOID_TEST_DETOUR_BIT - 1)) == 0,
                  "Hook-test detour bits must be powers of two.");
#endif

    enum class EGlobalCallbackAttributeFlags : uint64_t
    {
#define RC_ENUM_ENTRY(name, value) name = (value),
        RC_UE_HOOK_GLOBAL_CALLBACK_ATTRIBUTE_FLAGS(RC_ENUM_ENTRY)
#undef RC_ENUM_ENTRY
    };

    enum class EDetourTarget : uint64_t
    {
#define RC_ENUM_ENTRY(name, value) name = (value),
        RC_UE_HOOK_DETOUR_TARGETS(RC_ENUM_ENTRY)
#undef RC_ENUM_ENTRY

#if RC_UE_HOOK_TEST_ENABLED
        VoidTest    = VOID_TEST_DETOUR_BIT,
        NonVoidTest = NONVOID_TEST_DETOUR_BIT,
#endif
    };

    inline constexpr StringViewType EnumToString(const EGlobalCallbackAttributeFlags Flag) noexcept
    {
        switch (Flag)
        {
#define RC_CASE(name, value) case EGlobalCallbackAttributeFlags::name: return STR(#name);
            RC_UE_HOOK_GLOBAL_CALLBACK_ATTRIBUTE_FLAGS(RC_CASE)
#undef RC_CASE
            default: return STR("UnknownCallbackType");
        }
    }

    inline constexpr StringViewType EnumToString(const EDetourTarget Flag) noexcept
    {
        switch (Flag)
        {
#define RC_CASE(name, value) case EDetourTarget::name: return STR(#name);
            RC_UE_HOOK_DETOUR_TARGETS(RC_CASE)
#undef RC_CASE

#if RC_UE_HOOK_TEST_ENABLED
            case EDetourTarget::VoidTest:    return STR("VoidTest");
            case EDetourTarget::NonVoidTest: return STR("NonVoidTest");
#endif
            default: return STR("UnknownDetourTarget");
        }
    }

    inline constexpr uint64_t ComputeGlobalCallbackTypeMask() noexcept
    {
        uint64_t Mask = 0;
#define RC_OR(name, value) Mask |= (value);
        RC_UE_HOOK_GLOBAL_CALLBACK_ATTRIBUTE_FLAGS(RC_OR)
#undef RC_OR
        return Mask;
    }

    inline constexpr uint64_t ComputeDetourMask() noexcept
    {
        uint64_t Mask = 0;
#define RC_OR(name, value) Mask |= (value);
        RC_UE_HOOK_DETOUR_TARGETS(RC_OR)
#undef RC_OR

#if RC_UE_HOOK_TEST_ENABLED
        Mask |= VOID_TEST_DETOUR_BIT;
        Mask |= NONVOID_TEST_DETOUR_BIT;
#endif
        return Mask;
    }

    inline constexpr uint64_t ComputeLowestFlagBit() noexcept
    {
        uint64_t Lowest = std::numeric_limits<uint64_t>::max();
#define RC_MIN(name, value) Lowest = MinNonZero(Lowest, (value));
        RC_UE_HOOK_GLOBAL_CALLBACK_ATTRIBUTE_FLAGS(RC_MIN)
        RC_UE_HOOK_DETOUR_TARGETS(RC_MIN)
#undef RC_MIN

#if RC_UE_HOOK_TEST_ENABLED
        Lowest = MinNonZero(Lowest, VOID_TEST_DETOUR_BIT);
        Lowest = MinNonZero(Lowest, NONVOID_TEST_DETOUR_BIT);
#endif
        return Lowest;
    }

    inline constexpr uint64_t CALLBACK_TYPE_MASK = ComputeGlobalCallbackTypeMask();
    inline constexpr uint64_t DETOUR_MASK        = ComputeDetourMask();
    inline constexpr uint64_t FIRST_FLAG_BIT     = ComputeLowestFlagBit();
    inline constexpr uint64_t ID_MASK            = ~(DETOUR_MASK | CALLBACK_TYPE_MASK);

    static_assert((DETOUR_MASK & CALLBACK_TYPE_MASK) == 0,
                  "EGlobalCallbackAttributeFlags and EDetourTarget must not overlap!");

#if RC_UE_HOOK_TEST_ENABLED
    // Extra sanity: test bits must not collide with the main detour list.
    static_assert((ComputeDetourMask() & (VOID_TEST_DETOUR_BIT | NONVOID_TEST_DETOUR_BIT)) ==
                  (VOID_TEST_DETOUR_BIT | NONVOID_TEST_DETOUR_BIT),
                  "Hook-test detours must be included in DETOUR_MASK.");
#endif

#undef RC_UE_HOOK_GLOBAL_CALLBACK_ATTRIBUTE_FLAGS
#undef RC_UE_HOOK_TEST_ENABLED

//intentionally 'leak' RC_UE_HOOK_DETOUR_TARGETS to be used in UnregisterCallback
}
