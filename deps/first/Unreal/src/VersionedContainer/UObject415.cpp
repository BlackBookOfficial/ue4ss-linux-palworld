#include <Unreal/VersionedContainer/UObject415.hpp>
#include <Unreal/VersionedContainer/Flags415.hpp>
#include <Unreal/VersionedContainer/Flags.hpp>
#include <Unreal/VersionedContainer/Container.hpp>

namespace RC::Unreal
{
    auto UObject415::UObject_clear_flags(void* p_this, const EObjectFlags flags_to_clear) -> void
    {
        Flags::clear_flags(p_this, Flags415::to_impl_flags(flags_to_clear));
    }

    auto UObject415::UObject_set_flags_to(void* p_this, EObjectFlags new_flags) -> void
    {
        Flags::set_flags_to(p_this, Flags415::to_impl_flags(new_flags));
    }

    auto UObject415::UObject_set_flags(void* p_this, const EObjectFlags new_flags) -> void
    {
        Flags::set_flags(p_this, Flags415::to_impl_flags(new_flags));
    }

    auto UObject415::UObject_has_any_flag(void* p_this, const EObjectFlags flags_to_check) -> bool
    {
        return Flags::has_any_flag(p_this, Flags415::to_impl_flags(flags_to_check));
    }

    auto UObject415::UObject_has_all_flags(void* p_this, const EObjectFlags flags_to_check) -> bool
    {
        return Flags::has_all_flags(p_this, Flags415::to_impl_flags(flags_to_check));
    }

    bool UObject415::UObject_HasAnyInternalFlags(void* p_this, const EInternalObjectFlags FlagsToCheck)
    {
        return FUObjectArray::IndexToObject(UObject_get_internal_index(p_this))->HasAnyFlags(FlagsToCheck);
    }
}
