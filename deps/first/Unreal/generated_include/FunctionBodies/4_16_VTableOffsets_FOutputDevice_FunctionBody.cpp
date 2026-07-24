if (auto it = FOutputDevice::VTableLayoutMap.find(STR("__vecDelDtor")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("Serialize__Ptr_C_wchar_t__ELogVerbosity_Type__Ref_C_FName__C_double")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("Serialize__Ptr_C_wchar_t__ELogVerbosity_Type__Ref_C_FName__C_double"), 0x8);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("Serialize__Ptr_C_wchar_t__ELogVerbosity_Type__Ref_C_FName")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("Serialize__Ptr_C_wchar_t__ELogVerbosity_Type__Ref_C_FName"), 0x10);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("Flush")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("Flush"), 0x18);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("TearDown")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("TearDown"), 0x20);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("Dump")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("Dump"), 0x28);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("IsMemoryOnly")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("IsMemoryOnly"), 0x30);
}

if (auto it = FOutputDevice::VTableLayoutMap.find(STR("CanBeUsedOnAnyThread")); it == FOutputDevice::VTableLayoutMap.end())
{
    FOutputDevice::VTableLayoutMap.emplace(STR("CanBeUsedOnAnyThread"), 0x38);
}

