#pragma once

#include <unordered_map>
#include <functional>

#include <Unreal/Common.hpp>

namespace RC::Unreal
{
    class FName;

    RC_UE_API extern FName GWorldName;
    RC_UE_API extern FName GLevelName;
    RC_UE_API extern FName GPackageName;
    RC_UE_API extern FName GPropertyName;
    RC_UE_API extern FName GFunctionName;

    enum class InternalType
    {
        Array,
        Map,
    };

    class RC_UE_API TypeChecker
    {
    private:
        constexpr static int32_t FFieldClassOffset = 0x8;

    public:
        auto static get_world_name() -> FName;
        auto static get_level_name() -> FName;

    public:
        auto static store_all_object_names() -> void;
        auto static store_all_object_types() -> bool;

        // Returns true if the UObject inherits from the Property class
        // DO NOT RUN IN 4.25+!
        auto static is_property(class UObject* object) -> bool;
        auto static is_property(class FField* object) -> bool;
    };
}



