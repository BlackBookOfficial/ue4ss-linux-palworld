static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FProperty*& GetKeyProp();
    const FProperty*& GetKeyProp() const;

public:
    FProperty*& GetValueProp();
    const FProperty*& GetValueProp() const;

public:
    FScriptMapLayout& GetMapLayout();
    const FScriptMapLayout& GetMapLayout() const;

public:
    EMapPropertyFlags& GetMapFlags();
    const EMapPropertyFlags& GetMapFlags() const;

public:
    static int32_t& UEP_TotalSize();
