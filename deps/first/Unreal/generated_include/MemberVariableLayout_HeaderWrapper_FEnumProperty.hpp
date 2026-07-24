static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FNumericProperty*& GetUnderlyingProp();
    const FNumericProperty*& GetUnderlyingProp() const;

public:
    TObjectPtr<UEnum>& GetEnum();
    const TObjectPtr<UEnum>& GetEnum() const;

public:
    static int32_t& UEP_TotalSize();
