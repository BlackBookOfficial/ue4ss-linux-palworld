if (auto it = FNumericProperty::VTableLayoutMap.find(STR("__vecDelDtor")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("IsFloatingPoint")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("IsFloatingPoint"), 0x2A8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("IsInteger")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("IsInteger"), 0x2B0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetIntPropertyEnum")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetIntPropertyEnum"), 0x2B8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetIntPropertyValue_C__Ptr_void__int64")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetIntPropertyValue_C__Ptr_void__int64"), 0x2C0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetIntPropertyValue_C__Ptr_void__uint64")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetIntPropertyValue_C__Ptr_void__uint64"), 0x2C8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetFloatingPointPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetFloatingPointPropertyValue"), 0x2D0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("SetNumericPropertyValueFromString")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("SetNumericPropertyValueFromString"), 0x2D8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetSignedIntPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetSignedIntPropertyValue"), 0x2E0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetUnsignedIntPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetUnsignedIntPropertyValue"), 0x2E8);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetFloatingPointPropertyValue")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetFloatingPointPropertyValue"), 0x2F0);
}

if (auto it = FNumericProperty::VTableLayoutMap.find(STR("GetNumericPropertyValueToString")); it == FNumericProperty::VTableLayoutMap.end())
{
    FNumericProperty::VTableLayoutMap.emplace(STR("GetNumericPropertyValueToString"), 0x2F8);
}

