if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetCPPTypeCustom")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetCPPTypeCustom"), 0x1E0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("LoadObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("LoadObjectPropertyValue"), 0x1E8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPropertyValueUnchecked")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPropertyValueUnchecked"), 0x1F0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPtrPropertyValueUnchecked")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPtrPropertyValueUnchecked"), 0x1F8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPropertyValueUnchecked_InContainer")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPropertyValueUnchecked_InContainer"), 0x200);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPtrPropertyValueUnchecked_InContainer")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPtrPropertyValueUnchecked_InContainer"), 0x208);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPropertyValue"), 0x210);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPtrPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPtrPropertyValue"), 0x218);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPropertyValue_InContainer")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPropertyValue_InContainer"), 0x220);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPtrPropertyValue_InContainer")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPtrPropertyValue_InContainer"), 0x228);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("CheckValidObject")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("CheckValidObject"), 0x230);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("AllowObjectTypeReinterpretationTo")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("AllowObjectTypeReinterpretationTo"), 0x238);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("AllowCrossLevel")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("AllowCrossLevel"), 0x240);
}

