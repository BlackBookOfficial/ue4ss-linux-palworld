static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    EStructFlags& GetStructFlags();
    const EStructFlags& GetStructFlags() const;

public:
    bool& GetbCppStructOpsFromBaseClass();
    const bool& GetbCppStructOpsFromBaseClass() const;

public:
    bool& GetbPrepareCppStructOpsCompleted();
    const bool& GetbPrepareCppStructOpsCompleted() const;

public:
    UScriptStruct::ICppStructOps*& GetCppStructOps();
    const UScriptStruct::ICppStructOps*& GetCppStructOps() const;

public:
    static int32_t& UEP_TotalSize();
