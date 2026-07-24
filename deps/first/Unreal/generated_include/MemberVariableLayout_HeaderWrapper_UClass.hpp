static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    std::function<void(const void*)>*& GetClassConstructor();
    const std::function<void(const void*)>*& GetClassConstructor() const;

public:
    std::function<UObject*(void*)>*& GetClassVTableHelperCtorCaller();
    const std::function<UObject*(void*)>*& GetClassVTableHelperCtorCaller() const;

public:
    std::function<void(UObject*, void*)>*& GetClassAddReferencedObjects();
    const std::function<void(UObject*, void*)>*& GetClassAddReferencedObjects() const;

private:
    int32& GetClassUniqueBase();
    const int32& GetClassUniqueBase() const;
    uint32& GetClassUnique418();
    const uint32& GetClassUnique418() const;

private:
    uint32& GetClassFlagsBase();
    const uint32& GetClassFlagsBase() const;
    EClassFlags& GetClassFlags417();
    const EClassFlags& GetClassFlags417() const;

private:
    uint64& GetClassCastFlagsBase();
    const uint64& GetClassCastFlagsBase() const;
    EClassCastFlags& GetClassCastFlags420();
    const EClassCastFlags& GetClassCastFlags420() const;

public:
    TObjectPtr<UClass>& GetClassWithin();
    const TObjectPtr<UClass>& GetClassWithin() const;

public:
    UObject*& GetClassGeneratedBy();
    const UObject*& GetClassGeneratedBy() const;

public:
    FName& GetClassConfigName();
    const FName& GetClassConfigName() const;

private:
    bool& GetbCookedBase();
    const bool& GetbCookedBase() const;
    uint32& GetbCooked418();
    const uint32& GetbCooked418() const;

public:
    TArray<TObjectPtr<UField>,TSizedDefaultAllocator<32> >& GetNetFields();
    const TArray<TObjectPtr<UField>,TSizedDefaultAllocator<32> >& GetNetFields() const;

public:
    TObjectPtr<UObject>& GetClassDefaultObject();
    const TObjectPtr<UObject>& GetClassDefaultObject() const;

public:
    TMap<FName, TObjectPtr<UFunction>>& GetFuncMap();
    const TMap<FName, TObjectPtr<UFunction>>& GetFuncMap() const;

public:
    TArray<FImplementedInterface,TSizedDefaultAllocator<32> >& GetInterfaces();
    const TArray<FImplementedInterface,TSizedDefaultAllocator<32> >& GetInterfaces() const;

public:
    FGCReferenceTokenStream& GetReferenceTokenStream();
    const FGCReferenceTokenStream& GetReferenceTokenStream() const;

public:
    TArray<FNativeFunctionLookup,TSizedDefaultAllocator<32> >& GetNativeFunctionLookupTable();
    const TArray<FNativeFunctionLookup,TSizedDefaultAllocator<32> >& GetNativeFunctionLookupTable() const;

public:
    TMap<FName, UFunction *>& GetParentFuncMap();
    const TMap<FName, UFunction *>& GetParentFuncMap() const;

public:
    TMap<FName, UFunction *>& GetInterfaceFuncMap();
    const TMap<FName, UFunction *>& GetInterfaceFuncMap() const;

public:
    TMap<FName, UFunction *>& GetSuperFuncMap();
    const TMap<FName, UFunction *>& GetSuperFuncMap() const;

public:
    FStructProperty*& GetUberGraphFramePointerProperty();
    const FStructProperty*& GetUberGraphFramePointerProperty() const;

public:
    void*& GetSparseClassData();
    const void*& GetSparseClassData() const;

public:
    TObjectPtr<UScriptStruct>& GetSparseClassDataStruct();
    const TObjectPtr<UScriptStruct>& GetSparseClassDataStruct() const;

public:
    int32& GetFirstOwnedClassRep();
    const int32& GetFirstOwnedClassRep() const;

public:
    bool& GetbLayoutChanging();
    const bool& GetbLayoutChanging() const;

public:
    TMap<FName, UFunction *>& GetAllFunctionsCache();
    const TMap<FName, UFunction *>& GetAllFunctionsCache() const;

public:
    UE::GC::FSchemaOwner& GetReferenceSchema();
    const UE::GC::FSchemaOwner& GetReferenceSchema() const;

public:
    UE::FPlatformRWLock& GetFuncMapLock();
    const UE::FPlatformRWLock& GetFuncMapLock() const;

public:
    UE::FPlatformRWLock& GetAllFunctionsCacheLock();
    const UE::FPlatformRWLock& GetAllFunctionsCacheLock() const;

public:
    bool& GetbNeedsDynamicSubobjectInstancing();
    const bool& GetbNeedsDynamicSubobjectInstancing() const;

public:
    static int32_t& UEP_TotalSize();
