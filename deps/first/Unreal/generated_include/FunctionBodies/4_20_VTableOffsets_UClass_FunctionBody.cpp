if (auto it = UClass::VTableLayoutMap.find(STR("__vecDelDtor")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetAuthoritativeClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetAuthoritativeClass"), 0x2C0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PostInitInstance")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PostInitInstance"), 0x2C8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("InitPropertiesFromCustomList")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("InitPropertiesFromCustomList"), 0x2D0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetPersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetPersistentUberGraphFrame"), 0x2D8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CreatePersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CreatePersistentUberGraphFrame"), 0x2E0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("DestroyPersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("DestroyPersistentUberGraphFrame"), 0x2E8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("SerializeDefaultObject")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("SerializeDefaultObject"), 0x2F0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PostLoadDefaultObject")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PostLoadDefaultObject"), 0x2F8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PurgeClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PurgeClass"), 0x300);
}

if (auto it = UClass::VTableLayoutMap.find(STR("IsFunctionImplementedInBlueprint")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("IsFunctionImplementedInBlueprint"), 0x308);
}

if (auto it = UClass::VTableLayoutMap.find(STR("HasProperty")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("HasProperty"), 0x310);
}

if (auto it = UClass::VTableLayoutMap.find(STR("FindArchetype")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("FindArchetype"), 0x318);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetArchetypeForCDO")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetArchetypeForCDO"), 0x320);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetRequiredPreloadDependencies")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetRequiredPreloadDependencies"), 0x328);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CreateDefaultObject")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CreateDefaultObject"), 0x330);
}

