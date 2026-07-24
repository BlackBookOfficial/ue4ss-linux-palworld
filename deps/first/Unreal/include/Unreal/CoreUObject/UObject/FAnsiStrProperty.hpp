#pragma once

#include <Helpers/Format.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/Core/Containers/FAnsiString.hpp>

namespace RC::Unreal
{
    class RC_UE_API FAnsiStrProperty : public TProperty_WithEqualityAndSerializer<FAnsiString, FProperty>
    {
        DECLARE_FIELD_CLASS(FAnsiStrProperty);
        DECLARE_VIRTUAL_TYPE(FAnsiStrProperty);
    };
}