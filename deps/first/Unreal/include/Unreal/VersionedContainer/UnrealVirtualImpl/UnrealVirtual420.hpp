#pragma once

#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>

namespace RC::Unreal
{
    class UnrealVirtual420 : public UnrealVirtualBaseVC
    {
        auto set_virtual_offsets() -> void override;
    };
}
