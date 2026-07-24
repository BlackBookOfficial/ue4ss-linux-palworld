if (auto it = FArchive::VTableLayoutMap.find(STR("__vecDelDtor")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FWeakObjectPtr")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FWeakObjectPtr"), 0x8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FSoftObjectPath")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FSoftObjectPath"), 0x10);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FSoftObjectPtr")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FSoftObjectPtr"), 0x18);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FLazyObjectPtr")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FLazyObjectPtr"), 0x20);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ptr_Ref_UObject")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ptr_Ref_UObject"), 0x28);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FText")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FText"), 0x30);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FName")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FName"), 0x38);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("ForceBlueprintFinalization")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("ForceBlueprintFinalization"), 0x40);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Serialize")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Serialize"), 0x48);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SerializeBits")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SerializeBits"), 0x50);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SerializeInt")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SerializeInt"), 0x58);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SerializeIntPacked")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SerializeIntPacked"), 0x60);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Preload")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Preload"), 0x68);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("CountBytes")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("CountBytes"), 0x70);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetArchiveName")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetArchiveName"), 0x78);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetLinker")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetLinker"), 0x80);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Tell")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Tell"), 0x88);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("TotalSize")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("TotalSize"), 0x90);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("AtEnd")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("AtEnd"), 0x98);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Seek")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Seek"), 0xA0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("AttachBulkData")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("AttachBulkData"), 0xA8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("DetachBulkData")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("DetachBulkData"), 0xB0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("IsProxyOf")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("IsProxyOf"), 0xB8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Precache")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Precache"), 0xC0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("FlushCache")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("FlushCache"), 0xC8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetCompressionMap")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetCompressionMap"), 0xD0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Flush")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Flush"), 0xD8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Close")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Close"), 0xE0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetError")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetError"), 0xE8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("MarkScriptSerializationStart")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("MarkScriptSerializationStart"), 0xF0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("MarkScriptSerializationEnd")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("MarkScriptSerializationEnd"), 0xF8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("MarkSearchableName")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("MarkSearchableName"), 0x100);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetArchetypeFromLoader")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetArchetypeFromLoader"), 0x108);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetCacheableArchive")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetCacheableArchive"), 0x110);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetCustomVersions")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetCustomVersions"), 0x118);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetCustomVersions")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetCustomVersions"), 0x120);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("ResetCustomVersions")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("ResetCustomVersions"), 0x128);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetFilterEditorOnly")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetFilterEditorOnly"), 0x130);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("UseToResolveEnumerators")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("UseToResolveEnumerators"), 0x138);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("ShouldSkipProperty")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("ShouldSkipProperty"), 0x140);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("PushSerializedProperty")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("PushSerializedProperty"), 0x148);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("PopSerializedProperty")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("PopSerializedProperty"), 0x150);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("AttachExternalReadDependency")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("AttachExternalReadDependency"), 0x158);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Reset")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Reset"), 0x160);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetIsLoading")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetIsLoading"), 0x168);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetIsSaving")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetIsSaving"), 0x170);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetIsTransacting")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetIsTransacting"), 0x178);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetIsTextFormat")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetIsTextFormat"), 0x180);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetWantBinaryPropertySerialization")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetWantBinaryPropertySerialization"), 0x188);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetForceUnicode")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetForceUnicode"), 0x190);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetIsPersistent")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetIsPersistent"), 0x198);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetUE4Ver")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetUE4Ver"), 0x1A0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetLicenseeUE4Ver")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetLicenseeUE4Ver"), 0x1A8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetEngineVer")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetEngineVer"), 0x1B0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetEngineNetVer")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetEngineNetVer"), 0x1B8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetGameNetVer")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetGameNetVer"), 0x1C0);
}

