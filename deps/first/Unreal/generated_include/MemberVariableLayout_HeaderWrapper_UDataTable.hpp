static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    TObjectPtr<UScriptStruct>& GetRowStruct();
    const TObjectPtr<UScriptStruct>& GetRowStruct() const;

public:
    TMap<FName, unsigned char *>& GetRowMap();
    const TMap<FName, unsigned char *>& GetRowMap() const;

public:
    BitfieldProxy GetbStripFromClientBuilds();
    ConstBitfieldProxy GetbStripFromClientBuilds() const;

public:
    BitfieldProxy GetbIgnoreExtraFields();
    ConstBitfieldProxy GetbIgnoreExtraFields() const;

public:
    BitfieldProxy GetbIgnoreMissingFields();
    ConstBitfieldProxy GetbIgnoreMissingFields() const;

public:
    FString& GetImportKeyField();
    const FString& GetImportKeyField() const;

public:
    BitfieldProxy GetbPreserveExistingValues();
    ConstBitfieldProxy GetbPreserveExistingValues() const;

public:
    static int32_t& UEP_TotalSize();
