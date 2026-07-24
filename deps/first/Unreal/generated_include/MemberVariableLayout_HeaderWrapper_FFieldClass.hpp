static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FName& GetFName();
    const FName& GetFName() const;

public:
    uint64& GetId();
    const uint64& GetId() const;

private:
    uint64& GetCastFlagsBase();
    const uint64& GetCastFlagsBase() const;
    EClassCastFlags& GetCastFlags507();
    const EClassCastFlags& GetCastFlags507() const;

public:
    EClassFlags& GetClassFlags();
    const EClassFlags& GetClassFlags() const;

public:
    FFieldClass*& GetSuperClass();
    const FFieldClass*& GetSuperClass() const;

public:
    FField*& GetDefaultObject();
    const FField*& GetDefaultObject() const;

public:
    std::function<FField*(const void*, const void*, EObjectFlags)>*& GetConstructFn();
    const std::function<FField*(const void*, const void*, EObjectFlags)>*& GetConstructFn() const;

public:
    FThreadSafeCounter& GetUnqiueNameIndexCounter();
    const FThreadSafeCounter& GetUnqiueNameIndexCounter() const;

public:
    std::atomic<int>& GetUniqueNameIndexCounter();
    const std::atomic<int>& GetUniqueNameIndexCounter() const;

public:
    static int32_t& UEP_TotalSize();
