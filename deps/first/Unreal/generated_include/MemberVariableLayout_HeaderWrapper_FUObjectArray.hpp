static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    int32& GetObjFirstGCIndex();
    const int32& GetObjFirstGCIndex() const;

public:
    int32& GetObjLastNonGCIndex();
    const int32& GetObjLastNonGCIndex() const;

private:
    int32& GetOpenForDisregardForGCBase();
    const int32& GetOpenForDisregardForGCBase() const;
    bool& GetOpenForDisregardForGC411();
    const bool& GetOpenForDisregardForGC411() const;

public:
    TUObjectArray& GetObjObjects();
    const TUObjectArray& GetObjObjects() const;

private:
    TLockFreePointerList<int>& GetObjAvailableListBase();
    const TLockFreePointerList<int>& GetObjAvailableListBase() const;
    TArray<int,TSizedDefaultAllocator<32> >& GetObjAvailableList427();
    const TArray<int,TSizedDefaultAllocator<32> >& GetObjAvailableList427() const;

public:
    TArray<FUObjectArray::FUObjectCreateListener *,TSizedDefaultAllocator<32> >& GetUObjectCreateListeners();
    const TArray<FUObjectArray::FUObjectCreateListener *,TSizedDefaultAllocator<32> >& GetUObjectCreateListeners() const;

public:
    TArray<FUObjectArray::FUObjectDeleteListener *,TSizedDefaultAllocator<32> >& GetUObjectDeleteListeners();
    const TArray<FUObjectArray::FUObjectDeleteListener *,TSizedDefaultAllocator<32> >& GetUObjectDeleteListeners() const;

public:
    int32& GetMaxObjectsNotConsideredByGC();
    const int32& GetMaxObjectsNotConsideredByGC() const;

public:
    FThreadSafeCounter& GetMasterSerialNumber();
    const FThreadSafeCounter& GetMasterSerialNumber() const;

public:
    FThreadSafeCounter& GetPrimarySerialNumber();
    const FThreadSafeCounter& GetPrimarySerialNumber() const;

public:
    bool& GetbShouldRecycleObjectIndices();
    const bool& GetbShouldRecycleObjectIndices() const;

public:
    int32& GetObjAvailableListEstimateCount();
    const int32& GetObjAvailableListEstimateCount() const;

public:
    static int32_t& UEP_TotalSize();
