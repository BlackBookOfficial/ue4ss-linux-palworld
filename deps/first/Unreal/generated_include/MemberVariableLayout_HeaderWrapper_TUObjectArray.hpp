static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FUObjectItem**& GetObjects();
    const FUObjectItem**& GetObjects() const;

public:
    FUObjectItem*& GetPreAllocatedObjects();
    const FUObjectItem*& GetPreAllocatedObjects() const;

public:
    int32& GetMaxElements();
    const int32& GetMaxElements() const;

public:
    int32& GetNumElements();
    const int32& GetNumElements() const;

public:
    int32& GetMaxChunks();
    const int32& GetMaxChunks() const;

public:
    int32& GetNumChunks();
    const int32& GetNumChunks() const;

public:
    static int32_t& UEP_TotalSize();
