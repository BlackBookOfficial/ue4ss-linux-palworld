if (auto it = FArchive::MemberOffsets.find(STR("ArIsLoading")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsLoading"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArIsLoading"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsSaving")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsSaving"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArIsSaving"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsTransacting")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsTransacting"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArIsTransacting"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArWantBinaryPropertySerialization")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArWantBinaryPropertySerialization"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArWantBinaryPropertySerialization"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArForceUnicode")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArForceUnicode"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArForceUnicode"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsPersistent")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsPersistent"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArIsPersistent"), BitfieldInfo{5, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsError")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsError"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArIsError"), BitfieldInfo{6, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsCriticalError")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsCriticalError"), 0x28);
    FArchive::BitfieldInfos.emplace(STR("ArIsCriticalError"), BitfieldInfo{7, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArContainsCode")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArContainsCode"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArContainsCode"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArContainsMap")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArContainsMap"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArContainsMap"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArRequiresLocalizationGather")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArRequiresLocalizationGather"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArRequiresLocalizationGather"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArForceByteSwapping")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArForceByteSwapping"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArForceByteSwapping"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreArchetypeRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreArchetypeRef"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArIgnoreArchetypeRef"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArNoDelta")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArNoDelta"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArNoDelta"), BitfieldInfo{5, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreOuterRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreOuterRef"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArIgnoreOuterRef"), BitfieldInfo{6, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreClassGeneratedByRef"), 0x29);
    FArchive::BitfieldInfos.emplace(STR("ArIgnoreClassGeneratedByRef"), BitfieldInfo{7, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIgnoreClassRef")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIgnoreClassRef"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArIgnoreClassRef"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArAllowLazyLoading")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArAllowLazyLoading"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArAllowLazyLoading"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsObjectReferenceCollector")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsObjectReferenceCollector"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArIsObjectReferenceCollector"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsModifyingWeakAndStrongReferences"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArIsModifyingWeakAndStrongReferences"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsCountingMemory")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsCountingMemory"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArIsCountingMemory"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArShouldSkipBulkData")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArShouldSkipBulkData"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArShouldSkipBulkData"), BitfieldInfo{5, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsFilterEditorOnly")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsFilterEditorOnly"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArIsFilterEditorOnly"), BitfieldInfo{6, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArIsSaveGame")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArIsSaveGame"), 0x2A);
    FArchive::BitfieldInfos.emplace(STR("ArIsSaveGame"), BitfieldInfo{7, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArUseCustomPropertyList")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArUseCustomPropertyList"), 0x2B);
    FArchive::BitfieldInfos.emplace(STR("ArUseCustomPropertyList"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchive::MemberOffsets.find(STR("ArSerializingDefaults")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArSerializingDefaults"), 0x2C);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArPortFlags")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArPortFlags"), 0x30);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArMaxSerializeSize")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArMaxSerializeSize"), 0x38);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArUE4Ver")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArUE4Ver"), 0x40);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArLicenseeUE4Ver")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArLicenseeUE4Ver"), 0x44);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArEngineVer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArEngineVer"), 0x48);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArEngineNetVer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArEngineNetVer"), 0x54);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArGameNetVer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArGameNetVer"), 0x58);
}

if (auto it = FArchive::MemberOffsets.find(STR("CustomVersionContainer")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("CustomVersionContainer"), 0x60);
}

if (auto it = FArchive::MemberOffsets.find(STR("ArCustomPropertyList")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("ArCustomPropertyList"), 0x68);
}

if (auto it = FArchive::MemberOffsets.find(STR("CookingTargetPlatform")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("CookingTargetPlatform"), 0x70);
}

if (auto it = FArchive::MemberOffsets.find(STR("SerializedProperty")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("SerializedProperty"), 0x78);
}

if (auto it = FArchive::MemberOffsets.find(STR("bCustomVersionsAreReset")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("bCustomVersionsAreReset"), 0x80);
}

if (auto it = FArchive::MemberOffsets.find(STR("UEP_TotalSize")); it == FArchive::MemberOffsets.end())
{
    FArchive::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x88);
}
