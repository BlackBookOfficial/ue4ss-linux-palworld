static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    EObjectFlags& GetObjectFlags();
    const EObjectFlags& GetObjectFlags() const;

public:
    int32& GetInternalIndex_Private();
    const int32& GetInternalIndex_Private() const;

public:
    UClass*& GetClassPrivate();
    const UClass*& GetClassPrivate() const;

public:
    FName& GetNamePrivate();
    const FName& GetNamePrivate() const;

public:
    UObject*& GetOuterPrivate();
    const UObject*& GetOuterPrivate() const;

public:
    static int32_t& UEP_TotalSize();
