static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FProperty*& GetInner();
    const FProperty*& GetInner() const;

public:
    EArrayPropertyFlags& GetArrayFlags();
    const EArrayPropertyFlags& GetArrayFlags() const;

public:
    static int32_t& UEP_TotalSize();
