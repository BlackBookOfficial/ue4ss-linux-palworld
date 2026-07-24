static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

private:
    ObjectPtr_Private::TNonAccessTrackedObjectPtr<UStruct>& GetSuperStructBase();
    const ObjectPtr_Private::TNonAccessTrackedObjectPtr<UStruct>& GetSuperStructBase() const;
    TObjectPtr<UStruct>& GetSuperStruct507();
    const TObjectPtr<UStruct>& GetSuperStruct507() const;

public:
    TObjectPtr<UField>& GetChildren();
    const TObjectPtr<UField>& GetChildren() const;

public:
    int32& GetPropertiesSize();
    const int32& GetPropertiesSize() const;

private:
    int32& GetMinAlignmentBase();
    const int32& GetMinAlignmentBase() const;
    int16& GetMinAlignment506();
    const int16& GetMinAlignment506() const;

public:
    TArray<unsigned char,TSizedDefaultAllocator<32> >& GetScript();
    const TArray<unsigned char,TSizedDefaultAllocator<32> >& GetScript() const;

public:
    FProperty*& GetPropertyLink();
    const FProperty*& GetPropertyLink() const;

public:
    FProperty*& GetRefLink();
    const FProperty*& GetRefLink() const;

public:
    FProperty*& GetDestructorLink();
    const FProperty*& GetDestructorLink() const;

public:
    FProperty*& GetPostConstructLink();
    const FProperty*& GetPostConstructLink() const;

public:
    TArray<UObject *,TSizedDefaultAllocator<32> >& GetScriptObjectReferences();
    const TArray<UObject *,TSizedDefaultAllocator<32> >& GetScriptObjectReferences() const;

public:
    FField*& GetChildProperties();
    const FField*& GetChildProperties() const;

public:
    TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& GetScriptAndPropertyObjectReferences();
    const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& GetScriptAndPropertyObjectReferences() const;

public:
    TArray<TTuple<TFieldPath<FField>,int>,TSizedDefaultAllocator<32> >*& GetUnresolvedScriptProperties();
    const TArray<TTuple<TFieldPath<FField>,int>,TSizedDefaultAllocator<32> >*& GetUnresolvedScriptProperties() const;

public:
    std::atomic<unsigned short>& GetStructStateFlags();
    const std::atomic<unsigned short>& GetStructStateFlags() const;

public:
    static int32_t& UEP_TotalSize();
