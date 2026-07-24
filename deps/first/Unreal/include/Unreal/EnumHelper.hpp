#pragma once

#include <type_traits>

// Defines all bitwise operators for enum classes so it can be (mostly) used as a regular flags enum
#define ENUM_CLASS_FLAGS(Enum) \
    inline           Enum& operator|=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((std::underlying_type_t<Enum>)Lhs | (std::underlying_type_t<Enum>)Rhs); } \
    inline           Enum& operator&=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((std::underlying_type_t<Enum>)Lhs & (std::underlying_type_t<Enum>)Rhs); } \
    inline           Enum& operator^=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((std::underlying_type_t<Enum>)Lhs ^ (std::underlying_type_t<Enum>)Rhs); } \
    inline constexpr Enum  operator| (Enum  Lhs, Enum Rhs) { return (Enum)((std::underlying_type_t<Enum>)Lhs | (std::underlying_type_t<Enum>)Rhs); } \
    inline constexpr Enum  operator& (Enum  Lhs, Enum Rhs) { return (Enum)((std::underlying_type_t<Enum>)Lhs & (std::underlying_type_t<Enum>)Rhs); } \
    inline constexpr Enum  operator^ (Enum  Lhs, Enum Rhs) { return (Enum)((std::underlying_type_t<Enum>)Lhs ^ (std::underlying_type_t<Enum>)Rhs); } \
    inline constexpr bool  operator! (Enum  E)             { return !(std::underlying_type_t<Enum>)E; } \
    inline constexpr Enum  operator~ (Enum  E)             { return (Enum)~(std::underlying_type_t<Enum>)E; }

#define ENUM_MAKE_IMMUTABLE(Enum) \
    inline           Enum& operator|=(Enum& Lhs, Enum Rhs) { static_assert(false, "This enum cannot be modified directly"); return Lhs; } \
    inline           Enum& operator&=(Enum& Lhs, Enum Rhs) { static_assert(false, "This enum cannot be modified directly"); return Lhs; } \
    inline           Enum& operator^=(Enum& Lhs, Enum Rhs) { static_assert(false, "This enum cannot be modified directly"); return Lhs; } \
    inline constexpr Enum  operator| (Enum  Lhs, Enum Rhs) { static_assert(false, "This enum cannot be modified directly"); return Lhs; } \
    inline constexpr Enum  operator& (Enum  Lhs, Enum Rhs) { static_assert(false, "This enum cannot be modified directly"); return Lhs; } \
    inline constexpr Enum  operator^ (Enum  Lhs, Enum Rhs) { static_assert(false, "This enum cannot be modified directly"); return Lhs; } \
    inline constexpr bool  operator! (Enum  E)             { static_assert(false, "This enum cannot be modified directly"); return false; } \
    inline constexpr Enum  operator~ (Enum  E)             { static_assert(false, "This enum cannot be modified directly"); return E; }

