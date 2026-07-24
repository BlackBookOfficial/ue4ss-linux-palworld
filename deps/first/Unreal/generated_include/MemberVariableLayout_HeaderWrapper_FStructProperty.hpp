static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    TObjectPtr<UScriptStruct>& GetStruct();
    const TObjectPtr<UScriptStruct>& GetStruct() const;

public:
    static int32_t& UEP_TotalSize();
