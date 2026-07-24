#pragma once

#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>

namespace RC::Unreal
{
    class UnrealVirtual506 : public UnrealVirtualBaseVC
    {
        auto set_virtual_offsets() -> void override;
    };
}
