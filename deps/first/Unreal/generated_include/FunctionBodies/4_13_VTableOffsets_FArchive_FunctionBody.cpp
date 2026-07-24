if (auto it = FArchive::VTableLayoutMap.find(STR("__vecDelDtor")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FStringAssetReference")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FStringAssetReference"), 0x8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FAssetPtr")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FAssetPtr"), 0x10);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FLazyObjectPtr")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FLazyObjectPtr"), 0x18);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ptr_Ref_UObject")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ptr_Ref_UObject"), 0x20);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FText")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FText"), 0x28);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("operator<<__Ref_FName")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("operator<<__Ref_FName"), 0x30);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("ForceBlueprintFinalization")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("ForceBlueprintFinalization"), 0x38);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Serialize")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Serialize"), 0x40);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SerializeBits")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SerializeBits"), 0x48);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SerializeInt")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SerializeInt"), 0x50);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SerializeIntPacked")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SerializeIntPacked"), 0x58);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Preload")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Preload"), 0x60);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("CountBytes")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("CountBytes"), 0x68);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetArchiveName")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetArchiveName"), 0x70);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetLinker")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetLinker"), 0x78);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Tell")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Tell"), 0x80);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("TotalSize")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("TotalSize"), 0x88);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("AtEnd")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("AtEnd"), 0x90);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Seek")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Seek"), 0x98);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("AttachBulkData")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("AttachBulkData"), 0xA0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("DetachBulkData")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("DetachBulkData"), 0xA8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Precache")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Precache"), 0xB0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("FlushCache")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("FlushCache"), 0xB8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetCompressionMap")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetCompressionMap"), 0xC0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Flush")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Flush"), 0xC8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("Close")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("Close"), 0xD0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("GetError")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("GetError"), 0xD8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("MarkScriptSerializationStart")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("MarkScriptSerializationStart"), 0xE0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("MarkScriptSerializationEnd")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("MarkScriptSerializationEnd"), 0xE8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("IndicateSerializationMismatch")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("IndicateSerializationMismatch"), 0xF0);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("IsCloseComplete")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("IsCloseComplete"), 0xF8);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("IsFilterEditorOnly")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("IsFilterEditorOnly"), 0x100);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("SetFilterEditorOnly")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("SetFilterEditorOnly"), 0x108);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("IsSaveGame")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("IsSaveGame"), 0x110);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("UseToResolveEnumerators")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("UseToResolveEnumerators"), 0x118);
}

if (auto it = FArchive::VTableLayoutMap.find(STR("ShouldSkipProperty")); it == FArchive::VTableLayoutMap.end())
{
    FArchive::VTableLayoutMap.emplace(STR("ShouldSkipProperty"), 0x120);
}

