if (auto it = FNumericProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("IsFloatingPoint")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("IsFloatingPoint"), 0x1D0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("IsInteger")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("IsInteger"), 0x1D8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetIntPropertyEnum")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetIntPropertyEnum"), 0x1E0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetIntPropertyValue_C__Ptr_void__int64")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetIntPropertyValue_C__Ptr_void__int64"), 0x1E8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetIntPropertyValue_C__Ptr_void__uint64")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetIntPropertyValue_C__Ptr_void__uint64"), 0x1F0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetFloatingPointPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetFloatingPointPropertyValue"), 0x1F8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetNumericPropertyValueFromString")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetNumericPropertyValueFromString"), 0x200);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetNumericPropertyValueFromString_InContainer")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetNumericPropertyValueFromString_InContainer"), 0x208);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetSignedIntPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetSignedIntPropertyValue"), 0x210);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetSignedIntPropertyValue_InContainer")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetSignedIntPropertyValue_InContainer"), 0x218);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetUnsignedIntPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetUnsignedIntPropertyValue"), 0x220);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetUnsignedIntPropertyValue_InContainer")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetUnsignedIntPropertyValue_InContainer"), 0x228);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetFloatingPointPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetFloatingPointPropertyValue"), 0x230);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetNumericPropertyValueToString")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetNumericPropertyValueToString"), 0x238);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetNumericPropertyValueToString_InContainer")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetNumericPropertyValueToString_InContainer"), 0x240);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("CanHoldDoubleValueInternal")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("CanHoldDoubleValueInternal"), 0x248);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("CanHoldSignedValueInternal")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("CanHoldSignedValueInternal"), 0x250);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("CanHoldUnsignedValueInternal")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("CanHoldUnsignedValueInternal"), 0x258);
}

