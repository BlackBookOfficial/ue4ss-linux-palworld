#pragma once

#include <array>

#include <Unreal/UnrealFlags.hpp>

namespace RC::Unreal
{
    class UObjectBaseVC
    {
    private:
        using UObject = void;

    public:
        virtual ~UObjectBaseVC() = default; // Virtual Destructor
        UObjectBaseVC() = default; // Constructor
        UObjectBaseVC(const UObjectBaseVC&) = delete;  // Copy constructor
        UObjectBaseVC(UObjectBaseVC&&) = delete;  // Move constructor
        UObjectBaseVC& operator=(const UObjectBaseVC&) = delete;  // Copy assignment operator
        UObjectBaseVC& operator=(UObjectBaseVC&&) = delete;  // Move assignment operator

    public:
        virtual auto UObject_clear_flags(UObject* p_this, EObjectFlags flags_to_clear) -> void = 0;
        virtual auto UObject_set_flags_to(UObject* p_this, EObjectFlags new_flags) -> void = 0;
        virtual auto UObject_set_flags(UObject* p_this, EObjectFlags new_flags) -> void = 0;
        virtual auto UObject_has_any_flag(UObject* p_this, const EObjectFlags flags_to_check) -> bool = 0;
        virtual auto UObject_has_all_flags(UObject* p_this, const EObjectFlags flags_to_check) -> bool = 0;
        virtual bool UObject_HasAnyInternalFlags(UObject* p_this, const EInternalObjectFlags FlagsToCheck) = 0;

        virtual auto UObject_get_internal_index(const UObject* p_this) const -> int32_t;
    };
}



