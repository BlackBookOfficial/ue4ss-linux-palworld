#pragma once

#include <Unreal/VersionedContainer/UObjectBaseVC.hpp>
#include <Unreal/UnrealFlags.hpp>

namespace RC::Unreal
{
    class UObject425 : public UObjectBaseVC
    {
    private:
        // Overrides -> START
        auto UObject_clear_flags(void* p_this, const EObjectFlags flags_to_clear) -> void override;
        auto UObject_set_flags_to(void* p_this, EObjectFlags new_flags) -> void override;
        auto UObject_set_flags(void* p_this, const EObjectFlags new_flags) -> void override;
        auto UObject_has_any_flag(void* p_this, const EObjectFlags flags_to_check) -> bool override;
        auto UObject_has_all_flags(void* p_this, const EObjectFlags flags_to_check) -> bool override;
        bool UObject_HasAnyInternalFlags(void* p_this, const EInternalObjectFlags FlagsToCheck) override;
        // Overrides -> END
    };
}



