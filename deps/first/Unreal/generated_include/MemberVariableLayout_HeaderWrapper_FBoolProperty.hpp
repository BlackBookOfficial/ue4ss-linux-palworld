static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    uint8& GetFieldSize();
    const uint8& GetFieldSize() const;

public:
    uint8& GetByteOffset();
    const uint8& GetByteOffset() const;

public:
    uint8& GetByteMask();
    const uint8& GetByteMask() const;

public:
    uint8& GetFieldMask();
    const uint8& GetFieldMask() const;

public:
    static int32_t& UEP_TotalSize();
