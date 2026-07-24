if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetCPPTypeCustom")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetCPPTypeCustom"), 0x198);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("LoadObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("LoadObjectPropertyValue"), 0x1A0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPtrPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPtrPropertyValue"), 0x1A8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPropertyValue"), 0x1B0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPropertyValue_InContainer")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPropertyValue_InContainer"), 0x1B8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPropertyValue"), 0x1C0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPtrPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPtrPropertyValue"), 0x1C8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPropertyValue_InContainer")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPropertyValue_InContainer"), 0x1D0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("CheckValidObject")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("CheckValidObject"), 0x1D8);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("AllowObjectTypeReinterpretationTo")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("AllowObjectTypeReinterpretationTo"), 0x1E0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("AllowCrossLevel")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("AllowCrossLevel"), 0x1E8);
}

