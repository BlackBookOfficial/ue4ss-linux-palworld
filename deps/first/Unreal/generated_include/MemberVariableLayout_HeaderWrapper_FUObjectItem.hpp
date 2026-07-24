static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

private:
    UObjectBase*& GetObject();
    const UObjectBase*& GetObject() const;

public:
    int32& GetClusterAndFlags();
    const int32& GetClusterAndFlags() const;

public:
    int32& GetSerialNumber();
    const int32& GetSerialNumber() const;

private:
    int32& GetFlags();
    const int32& GetFlags() const;

public:
    int32& GetClusterIndex();
    const int32& GetClusterIndex() const;

public:
    int32& GetClusterRootIndex();
    const int32& GetClusterRootIndex() const;

public:
    int32& GetRefCount();
    const int32& GetRefCount() const;

public:
    int64& GetFlagsAndRefCount();
    const int64& GetFlagsAndRefCount() const;

public:
    uint8& GetRemoteId();
    const uint8& GetRemoteId() const;

public:
    uint32& GetObjectPtrLow();
    const uint32& GetObjectPtrLow() const;

public:
    static int32_t& UEP_TotalSize();
