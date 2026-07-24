#include <Unreal/Property/FEnumProperty.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FEnumProperty);

#include <MemberVariableLayout_SrcWrapper_FEnumProperty.hpp>

    auto FEnumProperty::GetUnderlyingProperty() -> FNumericProperty*
    {
        return GetUnderlyingProp();
    }
}
