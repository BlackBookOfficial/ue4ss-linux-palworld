#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FInt8Property);

    IMPLEMENT_FIELD_CLASS(FInt16Property);

    IMPLEMENT_FIELD_CLASS(FIntProperty);

    IMPLEMENT_FIELD_CLASS(FInt64Property);

    IMPLEMENT_FIELD_CLASS(FUInt16Property);

    IMPLEMENT_FIELD_CLASS(FUInt32Property);

    IMPLEMENT_FIELD_CLASS(FUInt64Property);

    IMPLEMENT_FIELD_CLASS(FFloatProperty);

    IMPLEMENT_FIELD_CLASS(FDoubleProperty);

    IMPLEMENT_FIELD_CLASS(FByteProperty);
#include <MemberVariableLayout_SrcWrapper_FByteProperty.hpp>
}
