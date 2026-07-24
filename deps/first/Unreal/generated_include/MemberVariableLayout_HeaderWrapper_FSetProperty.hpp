static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FProperty*& GetElementProp();
    const FProperty*& GetElementProp() const;

private:
    FScriptSetLayout& GetSetLayoutBase();
    const FScriptSetLayout& GetSetLayoutBase() const;
    FScriptSparseSetLayout& GetSetLayout507();
    const FScriptSparseSetLayout& GetSetLayout507() const;

public:
    static int32_t& UEP_TotalSize();
