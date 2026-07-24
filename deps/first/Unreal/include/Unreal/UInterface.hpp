#pragma once

#include <Unreal/UObject.hpp>

namespace RC::Unreal
{
    class RC_UE_API UInterface : public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UInterface, CoreUObject);
    };
}


