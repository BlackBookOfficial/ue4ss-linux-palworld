static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    int32& GetCurrentNetSpeed();
    const int32& GetCurrentNetSpeed() const;

public:
    int32& GetConfiguredInternetSpeed();
    const int32& GetConfiguredInternetSpeed() const;

public:
    int32& GetConfiguredLanSpeed();
    const int32& GetConfiguredLanSpeed() const;

public:
    static int32_t& UEP_TotalSize();
