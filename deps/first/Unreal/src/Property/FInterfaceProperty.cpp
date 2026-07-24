#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FInterfaceProperty);

#include <MemberVariableLayout_SrcWrapper_FInterfaceProperty.hpp>

    void FInterfaceProperty::SetInterfaceClass(UClass* NewInterfaceClass)
    {
        GetInterfaceClass() = NewInterfaceClass;
    }
}
