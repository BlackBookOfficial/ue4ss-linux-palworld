#pragma once

#include <Helpers/Format.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/Core/Containers/FString.hpp>

namespace RC::Unreal
{
    class RC_UE_API FStrProperty : public TProperty_WithEqualityAndSerializer<FString, FProperty>
    {
        DECLARE_FIELD_CLASS(FStrProperty);
        DECLARE_VIRTUAL_TYPE(FStrProperty);
    };
}