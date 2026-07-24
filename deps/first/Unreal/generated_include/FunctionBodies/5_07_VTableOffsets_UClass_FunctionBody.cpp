if (auto it = UClass::VTableLayoutMap.find(STR("__vecDelDtor")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetAuthoritativeClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetAuthoritativeClass"), 0x368);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetPropertyLinkFlags")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetPropertyLinkFlags"), 0x370);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PostInitInstance")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PostInitInstance"), 0x378);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PostLoadInstance")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PostLoadInstance"), 0x380);
}

if (auto it = UClass::VTableLayoutMap.find(STR("InitPropertiesFromCustomList")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("InitPropertiesFromCustomList"), 0x388);
}

if (auto it = UClass::VTableLayoutMap.find(STR("SetupObjectInitializer")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("SetupObjectInitializer"), 0x390);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CanCreateAssetOfClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CanCreateAssetOfClass"), 0x398);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetPersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetPersistentUberGraphFrame"), 0x3A0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CreatePersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CreatePersistentUberGraphFrame"), 0x3A8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("DestroyPersistentUberGraphFrame")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("DestroyPersistentUberGraphFrame"), 0x3B0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("SerializeDefaultObject__Ptr_UObject__Ref_FArchive")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("SerializeDefaultObject__Ptr_UObject__Ref_FArchive"), 0x3B8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("SerializeDefaultObject__Ptr_UObject__FStructuredArchiveSlot")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("SerializeDefaultObject__Ptr_UObject__FStructuredArchiveSlot"), 0x3C0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PostLoadDefaultObject")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PostLoadDefaultObject"), 0x3C8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("PurgeClass")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("PurgeClass"), 0x3D0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("IsFunctionImplementedInScript")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("IsFunctionImplementedInScript"), 0x3D8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("HasProperty")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("HasProperty"), 0x3E0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("FindArchetype")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("FindArchetype"), 0x3E8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetArchetypeForCDO")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetArchetypeForCDO"), 0x3F0);
}

if (auto it = UClass::VTableLayoutMap.find(STR("GetDefaultObjectPreloadDependencies")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("GetDefaultObjectPreloadDependencies"), 0x3F8);
}

if (auto it = UClass::VTableLayoutMap.find(STR("CreateDefaultObject")); it == UClass::VTableLayoutMap.end())
{
    UClass::VTableLayoutMap.emplace(STR("CreateDefaultObject"), 0x400);
}

