static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    BitfieldProxy GetArIsLoading();
    ConstBitfieldProxy GetArIsLoading() const;

public:
    BitfieldProxy GetArIsSaving();
    ConstBitfieldProxy GetArIsSaving() const;

public:
    BitfieldProxy GetArIsTransacting();
    ConstBitfieldProxy GetArIsTransacting() const;

public:
    BitfieldProxy GetArIsTextFormat();
    ConstBitfieldProxy GetArIsTextFormat() const;

public:
    BitfieldProxy GetArWantBinaryPropertySerialization();
    ConstBitfieldProxy GetArWantBinaryPropertySerialization() const;

public:
    BitfieldProxy GetArUseUnversionedPropertySerialization();
    ConstBitfieldProxy GetArUseUnversionedPropertySerialization() const;

public:
    BitfieldProxy GetArForceUnicode();
    ConstBitfieldProxy GetArForceUnicode() const;

public:
    BitfieldProxy GetArIsPersistent();
    ConstBitfieldProxy GetArIsPersistent() const;

public:
    BitfieldProxy GetArIsError();
    ConstBitfieldProxy GetArIsError() const;

public:
    BitfieldProxy GetArIsCriticalError();
    ConstBitfieldProxy GetArIsCriticalError() const;

public:
    BitfieldProxy GetArContainsCode();
    ConstBitfieldProxy GetArContainsCode() const;

public:
    BitfieldProxy GetArContainsMap();
    ConstBitfieldProxy GetArContainsMap() const;

public:
    BitfieldProxy GetArRequiresLocalizationGather();
    ConstBitfieldProxy GetArRequiresLocalizationGather() const;

public:
    BitfieldProxy GetArForceByteSwapping();
    ConstBitfieldProxy GetArForceByteSwapping() const;

public:
    BitfieldProxy GetArIgnoreArchetypeRef();
    ConstBitfieldProxy GetArIgnoreArchetypeRef() const;

public:
    BitfieldProxy GetArNoDelta();
    ConstBitfieldProxy GetArNoDelta() const;

public:
    BitfieldProxy GetArNoIntraPropertyDelta();
    ConstBitfieldProxy GetArNoIntraPropertyDelta() const;

public:
    BitfieldProxy GetArIgnoreOuterRef();
    ConstBitfieldProxy GetArIgnoreOuterRef() const;

public:
    BitfieldProxy GetArIgnoreClassGeneratedByRef();
    ConstBitfieldProxy GetArIgnoreClassGeneratedByRef() const;

public:
    BitfieldProxy GetArIgnoreClassRef();
    ConstBitfieldProxy GetArIgnoreClassRef() const;

public:
    BitfieldProxy GetArAllowLazyLoading();
    ConstBitfieldProxy GetArAllowLazyLoading() const;

public:
    BitfieldProxy GetArIsObjectReferenceCollector();
    ConstBitfieldProxy GetArIsObjectReferenceCollector() const;

public:
    BitfieldProxy GetArIsModifyingWeakAndStrongReferences();
    ConstBitfieldProxy GetArIsModifyingWeakAndStrongReferences() const;

public:
    BitfieldProxy GetArIsCountingMemory();
    ConstBitfieldProxy GetArIsCountingMemory() const;

public:
    BitfieldProxy GetArShouldSkipBulkData();
    ConstBitfieldProxy GetArShouldSkipBulkData() const;

public:
    BitfieldProxy GetArIsFilterEditorOnly();
    ConstBitfieldProxy GetArIsFilterEditorOnly() const;

public:
    BitfieldProxy GetArIsSaveGame();
    ConstBitfieldProxy GetArIsSaveGame() const;

public:
    BitfieldProxy GetArIsNetArchive();
    ConstBitfieldProxy GetArIsNetArchive() const;

public:
    BitfieldProxy GetArUseCustomPropertyList();
    ConstBitfieldProxy GetArUseCustomPropertyList() const;

public:
    int32& GetArSerializingDefaults();
    const int32& GetArSerializingDefaults() const;

public:
    uint32& GetArPortFlags();
    const uint32& GetArPortFlags() const;

public:
    int64& GetArMaxSerializeSize();
    const int64& GetArMaxSerializeSize() const;

public:
    int32& GetArUE4Ver();
    const int32& GetArUE4Ver() const;

public:
    int32& GetArLicenseeUE4Ver();
    const int32& GetArLicenseeUE4Ver() const;

public:
    FEngineVersionBase& GetArEngineVer();
    const FEngineVersionBase& GetArEngineVer() const;

public:
    uint32& GetArEngineNetVer();
    const uint32& GetArEngineNetVer() const;

public:
    uint32& GetArGameNetVer();
    const uint32& GetArGameNetVer() const;

public:
    FCustomVersionContainer*& GetCustomVersionContainer();
    const FCustomVersionContainer*& GetCustomVersionContainer() const;

public:
    const FCustomPropertyListNode*& GetArCustomPropertyList();
    const FCustomPropertyListNode*& GetArCustomPropertyList() const;

public:
    const ITargetPlatform*& GetCookingTargetPlatform();
    const ITargetPlatform*& GetCookingTargetPlatform() const;

public:
    FProperty*& GetSerializedProperty();
    const FProperty*& GetSerializedProperty() const;

public:
    bool& GetbCustomVersionsAreReset();
    const bool& GetbCustomVersionsAreReset() const;

public:
    FArchiveState*& GetNextProxy();
    const FArchiveState*& GetNextProxy() const;

public:
    BitfieldProxy GetArIsLoadingFromCookedPackage();
    ConstBitfieldProxy GetArIsLoadingFromCookedPackage() const;

public:
    BitfieldProxy GetArShouldSkipCompilingAssets();
    ConstBitfieldProxy GetArShouldSkipCompilingAssets() const;

public:
    FPackageFileVersion& GetArUEVer();
    const FPackageFileVersion& GetArUEVer() const;

public:
    int32& GetArLicenseeUEVer();
    const int32& GetArLicenseeUEVer() const;

public:
    BitfieldProxy GetArShouldSkipUpdateCustomVersion();
    ConstBitfieldProxy GetArShouldSkipUpdateCustomVersion() const;

public:
    BitfieldProxy GetArMergeOverrides();
    ConstBitfieldProxy GetArMergeOverrides() const;

public:
    FArchiveSavePackageData*& GetSavePackageData();
    const FArchiveSavePackageData*& GetSavePackageData() const;

public:
    BitfieldProxy GetArPreserveArrayElements();
    ConstBitfieldProxy GetArPreserveArrayElements() const;

public:
    BitfieldProxy GetArIsSavingOptionalObject();
    ConstBitfieldProxy GetArIsSavingOptionalObject() const;

public:
    static int32_t& UEP_TotalSize();
