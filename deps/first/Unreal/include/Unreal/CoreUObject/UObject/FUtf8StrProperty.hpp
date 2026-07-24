#pragma once

#include <Helpers/Format.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/Core/Containers/FUtf8String.hpp>

namespace RC::Unreal
{
    class RC_UE_API FUtf8StrProperty : public TProperty_WithEqualityAndSerializer<FUtf8String, FProperty>
    {
        DECLARE_FIELD_CLASS(FUtf8StrProperty);
        DECLARE_VIRTUAL_TYPE(FUtf8StrProperty);
    };
}