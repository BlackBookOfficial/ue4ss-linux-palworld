static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

private:
    uint32& GetFunctionFlagsBase();
    const uint32& GetFunctionFlagsBase() const;
    EFunctionFlags& GetFunctionFlags417();
    const EFunctionFlags& GetFunctionFlags417() const;

public:
    uint16& GetRepOffset();
    const uint16& GetRepOffset() const;

public:
    uint8& GetNumParms();
    const uint8& GetNumParms() const;

public:
    uint16& GetParmsSize();
    const uint16& GetParmsSize() const;

public:
    uint16& GetReturnValueOffset();
    const uint16& GetReturnValueOffset() const;

public:
    uint16& GetRPCId();
    const uint16& GetRPCId() const;

public:
    uint16& GetRPCResponseId();
    const uint16& GetRPCResponseId() const;

public:
    FProperty*& GetFirstPropertyToInit();
    const FProperty*& GetFirstPropertyToInit() const;

public:
    UFunction*& GetEventGraphFunction();
    const UFunction*& GetEventGraphFunction() const;

public:
    int32& GetEventGraphCallOffset();
    const int32& GetEventGraphCallOffset() const;

private:
    using FuncBase_Type = void (UObject::*)(FFrame&, void* const);
    FuncBase_Type& GetFuncBase();
    const FuncBase_Type& GetFuncBase() const;
    std::function<void(UObject*, FFrame&, void* const)>*& GetFunc419();
    const std::function<void(UObject*, FFrame&, void* const)>*& GetFunc419() const;

public:
    static int32_t& UEP_TotalSize();
