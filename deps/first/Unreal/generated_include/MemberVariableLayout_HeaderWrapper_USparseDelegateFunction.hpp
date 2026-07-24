static std::unordered_map<File::StringType, int32_t> MemberOffsets;

public:
    FName& GetOwningClassName();
    const FName& GetOwningClassName() const;

public:
    FName& GetDelegateName();
    const FName& GetDelegateName() const;

