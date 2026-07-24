if (auto it = UClass::VTableLayoutMap.find(STR("__vecDelDtor")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetAuthoritativeClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetAuthoritativeClass"), 0x230);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetPersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetPersistentUberGraphFrame"), 0x238);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CreatePersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CreatePersistentUberGraphFrame"), 0x240);
}

if (auto it = UClass::VTableLayoutMap.find(STR("DestroyPersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("DestroyPersistentUberGraphFrame"), 0x248);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PurgeClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PurgeClass"), 0x250);
}

if (auto it = UClass::VTableLayoutMap.find(STR("IsFunctionImplementedInBlueprint")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("IsFunctionImplementedInBlueprint"), 0x258);
}

if (auto it = UClass::VTableLayoutMap.find(STR("HasProperty")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("HasProperty"), 0x260);
}

if (auto it = UClass::VTableLayoutMap.find(STR("FindArchetype")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("FindArchetype"), 0x268);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetRequiredPreloadDependencies")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetRequiredPreloadDependencies"), 0x270);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetArchetypeForCDO")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetArchetypeForCDO"), 0x278);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CreateDefaultObject")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CreateDefaultObject"), 0x280);
}

