if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetCPPTypeCustom")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetCPPTypeCustom"), 0x310);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("GetObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("GetObjectPropertyValue"), 0x318);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("SetObjectPropertyValue")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("SetObjectPropertyValue"), 0x320);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("AllowCrossLevel")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("AllowCrossLevel"), 0x328);
}

if (auto it = FObjectPropertyBase::VTableLayoutMap.find(STR("CheckValidObject")); it == FObjectPropertyBase::VTableLayoutMap.end())
{
    FObjectPropertyBase::VTableLayoutMap.emplace(STR("CheckValidObject"), 0x330);
}

