#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FClassProperty);
    IMPLEMENT_FIELD_CLASS(FClassPtrProperty);

#include <MemberVariableLayout_SrcWrapper_FClassProperty.hpp>

    void FClassProperty::SetMetaClass(UClass* NewMetaClass)
    {
        GetMetaClass() = NewMetaClass;
    }
}
