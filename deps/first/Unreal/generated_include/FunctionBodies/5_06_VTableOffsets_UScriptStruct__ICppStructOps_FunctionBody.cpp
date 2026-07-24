if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("__vecDelDtor")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("GetCapabilities")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("GetCapabilities"), 0x8);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Construct")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Construct"), 0x10);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("ConstructForTests")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("ConstructForTests"), 0x18);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Destruct")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Destruct"), 0x20);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Serialize__FStructuredArchiveSlot__Ptr_void__Ptr_UStruct__Ptr_C_void")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Serialize__FStructuredArchiveSlot__Ptr_void__Ptr_UStruct__Ptr_C_void"), 0x28);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Serialize__Ref_FArchive__Ptr_void__Ptr_UStruct__Ptr_C_void")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Serialize__Ref_FArchive__Ptr_void__Ptr_UStruct__Ptr_C_void"), 0x30);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Serialize__FStructuredArchiveSlot__Ptr_void")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Serialize__FStructuredArchiveSlot__Ptr_void"), 0x38);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Serialize__Ref_FArchive__Ptr_void")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Serialize__Ref_FArchive__Ptr_void"), 0x40);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("PostSerialize")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("PostSerialize"), 0x48);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("NetSerialize")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("NetSerialize"), 0x50);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("NetDeltaSerialize")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("NetDeltaSerialize"), 0x58);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("PostScriptConstruct")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("PostScriptConstruct"), 0x60);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("GetPreloadDependencies")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("GetPreloadDependencies"), 0x68);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Copy")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Copy"), 0x70);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Identical")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Identical"), 0x78);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("ExportTextItem")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("ExportTextItem"), 0x80);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("ImportTextItem")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("ImportTextItem"), 0x88);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("FindInnerPropertyInstance")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("FindInnerPropertyInstance"), 0x90);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("AddStructReferencedObjects")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("AddStructReferencedObjects"), 0x98);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("SerializeFromMismatchedTag")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("SerializeFromMismatchedTag"), 0xA0);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("StructuredSerializeFromMismatchedTag")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("StructuredSerializeFromMismatchedTag"), 0xA8);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("GetStructTypeHash")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("GetStructTypeHash"), 0xB0);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("InitializeIntrusiveUnsetOptionalValue")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("InitializeIntrusiveUnsetOptionalValue"), 0xB8);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("IsIntrusiveOptionalValueSet")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("IsIntrusiveOptionalValueSet"), 0xC0);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("ClearIntrusiveOptionalValue")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("ClearIntrusiveOptionalValue"), 0xC8);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("IsIntrusiveOptionalSafeForGC")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("IsIntrusiveOptionalSafeForGC"), 0xD0);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("Visit")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("Visit"), 0xD8);
}

if (auto it = UScriptStruct::ICppStructOps::VTableLayoutMap.find(STR("ResolveVisitedPathInfo")); it == UScriptStruct::ICppStructOps::VTableLayoutMap.end())
{
    UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(STR("ResolveVisitedPathInfo"), 0xE0);
}

