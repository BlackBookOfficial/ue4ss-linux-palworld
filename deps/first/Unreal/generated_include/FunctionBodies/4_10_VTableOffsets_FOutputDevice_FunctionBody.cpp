if (auto it = FOutputDevice::VTableLayoutMap.find(STR("__vecDelDtor")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("Serialize")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("Serialize"), 0x8);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("Flush")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("Flush"), 0x10);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("TearDown")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("TearDown"), 0x18);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("CanBeUsedOnAnyThread")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("CanBeUsedOnAnyThread"), 0x20);
}

