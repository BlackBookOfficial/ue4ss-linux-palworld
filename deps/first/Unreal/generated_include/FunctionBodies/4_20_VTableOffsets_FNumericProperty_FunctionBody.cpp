if (auto it = FNumericProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("IsFloatingPoint")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("IsFloatingPoint"), 0x330);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("IsInteger")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("IsInteger"), 0x338);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetIntPropertyEnum")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetIntPropertyEnum"), 0x340);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetIntPropertyValue_C__Ptr_void__int64")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetIntPropertyValue_C__Ptr_void__int64"), 0x348);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetIntPropertyValue_C__Ptr_void__uint64")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetIntPropertyValue_C__Ptr_void__uint64"), 0x350);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetFloatingPointPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetFloatingPointPropertyValue"), 0x358);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetNumericPropertyValueFromString")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetNumericPropertyValueFromString"), 0x360);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetSignedIntPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetSignedIntPropertyValue"), 0x368);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetUnsignedIntPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetUnsignedIntPropertyValue"), 0x370);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetFloatingPointPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetFloatingPointPropertyValue"), 0x378);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetNumericPropertyValueToString")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetNumericPropertyValueToString"), 0x380);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("CanHoldDoubleValueInternal")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("CanHoldDoubleValueInternal"), 0x388);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("CanHoldSignedValueInternal")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("CanHoldSignedValueInternal"), 0x390);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("CanHoldUnsignedValueInternal")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("CanHoldUnsignedValueInternal"), 0x398);
}

