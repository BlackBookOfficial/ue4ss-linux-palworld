#include <Unreal/VersionedContainer/UObjectBaseVC.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    auto UObjectBaseVC::UObject_get_internal_index(const void* p_this) const -> int32_t
    {
        // TODO: Automate this offset
        return Helper::Casting::offset_deref<uint32_t>(p_this, 0xC);
    }
}
