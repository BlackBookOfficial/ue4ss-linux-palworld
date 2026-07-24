static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    bool& GetbSuppressEventTag();
    const bool& GetbSuppressEventTag() const;

public:
    bool& GetbAutoEmitLineTerminator();
    const bool& GetbAutoEmitLineTerminator() const;

public:
    static int32_t& UEP_TotalSize();
