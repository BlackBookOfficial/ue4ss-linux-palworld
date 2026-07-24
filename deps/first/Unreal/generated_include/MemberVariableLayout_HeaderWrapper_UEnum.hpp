static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FString& GetCppType();
    const FString& GetCppType() const;

private:
    TArray<TPair<FName,unsigned char>,FDefaultAllocator>& GetNamesBase();
    const TArray<TPair<FName,unsigned char>,FDefaultAllocator>& GetNamesBase() const;
    TArray<TPair<FName,__int64>,FDefaultAllocator>& GetNames415();
    const TArray<TPair<FName,__int64>,FDefaultAllocator>& GetNames415() const;
    TArray<TTuple<FName,__int64>,FDefaultAllocator>& GetNames416();
    const TArray<TTuple<FName,__int64>,FDefaultAllocator>& GetNames416() const;
    UEnum::FNameData& GetNames507();
    const UEnum::FNameData& GetNames507() const;

public:
    UEnum::ECppForm& GetCppForm();
    const UEnum::ECppForm& GetCppForm() const;

public:
    std::function<void(int32)>*& GetEnumDisplayNameFn();
    const std::function<void(int32)>*& GetEnumDisplayNameFn() const;

public:
    EEnumFlags& GetEnumFlags_Internal();
    const EEnumFlags& GetEnumFlags_Internal() const;

public:
    FName& GetEnumPackage();
    const FName& GetEnumPackage() const;

public:
    static int32_t& UEP_TotalSize();
