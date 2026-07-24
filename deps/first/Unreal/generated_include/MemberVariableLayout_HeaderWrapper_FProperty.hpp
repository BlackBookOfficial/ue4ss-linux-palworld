static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    int32& GetArrayDim();
    const int32& GetArrayDim() const;

public:
    int32& GetElementSize();
    const int32& GetElementSize() const;

private:
    uint64& GetPropertyFlagsBase();
    const uint64& GetPropertyFlagsBase() const;
    EPropertyFlags& GetPropertyFlags420();
    const EPropertyFlags& GetPropertyFlags420() const;

public:
    uint16& GetRepIndex();
    const uint16& GetRepIndex() const;

public:
    FName& GetRepNotifyFunc();
    const FName& GetRepNotifyFunc() const;

public:
    int32& GetOffset_Internal();
    const int32& GetOffset_Internal() const;

public:
    FProperty*& GetPropertyLinkNext();
    const FProperty*& GetPropertyLinkNext() const;

public:
    FProperty*& GetNextRef();
    const FProperty*& GetNextRef() const;

public:
    FProperty*& GetDestructorLinkNext();
    const FProperty*& GetDestructorLinkNext() const;

public:
    FProperty*& GetPostConstructLinkNext();
    const FProperty*& GetPostConstructLinkNext() const;

public:
    static int32_t& UEP_TotalSize();
