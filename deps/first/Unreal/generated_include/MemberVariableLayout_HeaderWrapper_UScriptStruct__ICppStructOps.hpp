static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    const int32& GetSize();
    const int32& GetSize() const;

public:
    const int32& GetAlignment();
    const int32& GetAlignment() const;

public:
    const UE::CoreUObject::Private::FStructOpsFakeVTable*& GetFakeVPtr();
    const UE::CoreUObject::Private::FStructOpsFakeVTable*& GetFakeVPtr() const;

public:
    static int32_t& UEP_TotalSize();
