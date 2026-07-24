if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsLoading")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsLoading"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsLoading"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsSaving")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsSaving"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsSaving"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsTransacting")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsTransacting"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsTransacting"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsTextFormat")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsTextFormat"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsTextFormat"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArWantBinaryPropertySerialization")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArWantBinaryPropertySerialization"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArWantBinaryPropertySerialization"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArUseUnversionedPropertySerialization")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArUseUnversionedPropertySerialization"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArUseUnversionedPropertySerialization"), BitfieldInfo{5, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArForceUnicode")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArForceUnicode"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArForceUnicode"), BitfieldInfo{6, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsPersistent")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsPersistent"), 0x28);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsPersistent"), BitfieldInfo{7, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsError")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsError"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsError"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsCriticalError")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsCriticalError"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsCriticalError"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArContainsCode")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArContainsCode"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArContainsCode"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArContainsMap")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArContainsMap"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArContainsMap"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArRequiresLocalizationGather")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArRequiresLocalizationGather"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArRequiresLocalizationGather"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArForceByteSwapping")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArForceByteSwapping"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArForceByteSwapping"), BitfieldInfo{5, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIgnoreArchetypeRef")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIgnoreArchetypeRef"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArIgnoreArchetypeRef"), BitfieldInfo{6, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArNoDelta")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArNoDelta"), 0x29);
    FArchiveState::BitfieldInfos.emplace(STR("ArNoDelta"), BitfieldInfo{7, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArNoIntraPropertyDelta")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArNoIntraPropertyDelta"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArNoIntraPropertyDelta"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIgnoreOuterRef")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIgnoreOuterRef"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArIgnoreOuterRef"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIgnoreClassGeneratedByRef"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArIgnoreClassGeneratedByRef"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIgnoreClassRef")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIgnoreClassRef"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArIgnoreClassRef"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArAllowLazyLoading")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArAllowLazyLoading"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArAllowLazyLoading"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsObjectReferenceCollector")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsObjectReferenceCollector"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsObjectReferenceCollector"), BitfieldInfo{5, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsModifyingWeakAndStrongReferences"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsModifyingWeakAndStrongReferences"), BitfieldInfo{6, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsCountingMemory")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsCountingMemory"), 0x2A);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsCountingMemory"), BitfieldInfo{7, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArShouldSkipBulkData")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArShouldSkipBulkData"), 0x2B);
    FArchiveState::BitfieldInfos.emplace(STR("ArShouldSkipBulkData"), BitfieldInfo{0, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsFilterEditorOnly")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsFilterEditorOnly"), 0x2B);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsFilterEditorOnly"), BitfieldInfo{1, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsSaveGame")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsSaveGame"), 0x2B);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsSaveGame"), BitfieldInfo{2, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArIsNetArchive")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArIsNetArchive"), 0x2B);
    FArchiveState::BitfieldInfos.emplace(STR("ArIsNetArchive"), BitfieldInfo{3, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArUseCustomPropertyList")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArUseCustomPropertyList"), 0x2B);
    FArchiveState::BitfieldInfos.emplace(STR("ArUseCustomPropertyList"), BitfieldInfo{4, 1, 1});
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArSerializingDefaults")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArSerializingDefaults"), 0x2C);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArPortFlags")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArPortFlags"), 0x30);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArMaxSerializeSize")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArMaxSerializeSize"), 0x38);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArUE4Ver")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArUE4Ver"), 0x40);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArLicenseeUE4Ver")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArLicenseeUE4Ver"), 0x44);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArEngineVer")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArEngineVer"), 0x48);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArEngineNetVer")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArEngineNetVer"), 0x54);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArGameNetVer")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArGameNetVer"), 0x58);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("CustomVersionContainer")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("CustomVersionContainer"), 0x60);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("ArCustomPropertyList")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("ArCustomPropertyList"), 0x68);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("CookingTargetPlatform")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("CookingTargetPlatform"), 0x70);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("SerializedProperty")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("SerializedProperty"), 0x78);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("bCustomVersionsAreReset")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("bCustomVersionsAreReset"), 0x88);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("NextProxy")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("NextProxy"), 0x90);
}

if (auto it = FArchiveState::MemberOffsets.find(STR("UEP_TotalSize")); it == FArchiveState::MemberOffsets.end())
{
    FArchiveState::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x98);
}
