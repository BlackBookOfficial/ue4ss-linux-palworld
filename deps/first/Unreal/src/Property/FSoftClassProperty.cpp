#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FSoftClassProperty);

#include <MemberVariableLayout_SrcWrapper_FSoftClassProperty.hpp>

    void FSoftClassProperty::SetMetaClass(UClass* NewMetaClass)
    {
        GetMetaClass() = NewMetaClass;
    }
}
