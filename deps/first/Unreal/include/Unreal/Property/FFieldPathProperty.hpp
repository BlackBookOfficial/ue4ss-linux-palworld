#pragma once

#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/FieldPath.hpp>

namespace RC::Unreal
{
    class RC_UE_API FFieldPathProperty : public TProperty<FFieldPath, FProperty>
    {
        DECLARE_FIELD_CLASS(FFieldPathProperty);
        DECLARE_VIRTUAL_TYPE(FFieldPathProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FFieldPathProperty.hpp>
    };
}



