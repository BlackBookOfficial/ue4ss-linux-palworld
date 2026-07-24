#include <Unreal/Property/FOptionalProperty.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FOptionalProperty)
    
    void FOptionalProperty::SetValueProperty(FProperty* InValueProperty)
    {
        check(!GetValueProperty());
        check(InValueProperty);
        GetValueProperty() = InValueProperty;
    }
}
