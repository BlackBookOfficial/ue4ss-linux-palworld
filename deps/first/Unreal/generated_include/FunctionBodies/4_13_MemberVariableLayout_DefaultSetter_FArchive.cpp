if (auto it = FArchive::MemberOffsets.find(STR("ArUE4Ver")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArUE4Ver"), 0x8);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArLicenseeUE4Ver")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArLicenseeUE4Ver"), 0xC);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArEngineVer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArEngineVer"), 0x10);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArEngineNetVer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArEngineNetVer"), 0x1C);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArGameNetVer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArGameNetVer"), 0x20);
}

if (auto it = FArchive::MemberOffsets.find(STR("CustomVersionContainer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("CustomVersionContainer"), 0x28);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsLoading")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsLoading"), 0x30);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsSaving")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsSaving"), 0x31);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsTransacting")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsTransacting"), 0x32);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArWantBinaryPropertySerialization")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArWantBinaryPropertySerialization"), 0x33);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArForceUnicode")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArForceUnicode"), 0x34);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsPersistent")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsPersistent"), 0x35);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsError")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsError"), 0x36);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsCriticalError")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsCriticalError"), 0x37);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArContainsCode")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArContainsCode"), 0x38);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArContainsMap")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArContainsMap"), 0x39);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArRequiresLocalizationGather")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArRequiresLocalizationGather"), 0x3A);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArForceByteSwapping")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArForceByteSwapping"), 0x3B);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreArchetypeRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreArchetypeRef"), 0x3C);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArNoDelta")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArNoDelta"), 0x3D);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreOuterRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreOuterRef"), 0x3E);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreClassGeneratedByRef"), 0x3F);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreClassRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreClassRef"), 0x40);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArAllowLazyLoading")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArAllowLazyLoading"), 0x41);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsObjectReferenceCollector")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsObjectReferenceCollector"), 0x42);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsModifyingWeakAndStrongReferences"), 0x43);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsCountingMemory")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsCountingMemory"), 0x44);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArShouldSkipBulkData")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArShouldSkipBulkData"), 0x45);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsFilterEditorOnly")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsFilterEditorOnly"), 0x46);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsSaveGame")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsSaveGame"), 0x47);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArSerializingDefaults")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArSerializingDefaults"), 0x48);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArPortFlags")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArPortFlags"), 0x4C);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArMaxSerializeSize")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArMaxSerializeSize"), 0x50);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArCustomPropertyList")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArCustomPropertyList"), 0x58);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArUseCustomPropertyList")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArUseCustomPropertyList"), 0x60);
}

if (auto it = FArchive::MemberOffsets.find(STR("CookingTargetPlatform")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("CookingTargetPlatform"), 0x68);
}

if (auto it = FArchive::MemberOffsets.find(STR("SerializedProperty")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("SerializedProperty"), 0x70);
}

if (auto it = FArchive::MemberOffsets.find(STR("bCustomVersionsAreReset")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("bCustomVersionsAreReset"), 0x78);
}

if (auto it = FArchive::MemberOffsets.find(STR("UEP_TotalSize")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x80);
}
