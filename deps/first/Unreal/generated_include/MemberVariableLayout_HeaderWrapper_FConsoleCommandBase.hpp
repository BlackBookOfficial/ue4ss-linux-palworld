static std::unordered_map<File::StringType, int32_t> MemberOffsets;

public:
    EConsoleVariableFlags& GetFlags();
    const EConsoleVariableFlags& GetFlags() const;

public:
    FString& GetHelp();
    const FString& GetHelp() const;

