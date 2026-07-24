std::unordered_map<File::StringType, int32_t> UEnum::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UEnum::BitfieldInfos{};

FString& UEnum::GetCppType()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CppType"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::CppType' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& UEnum::GetCppType() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CppType"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::CppType' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

TArray<TPair<FName,unsigned char>,FDefaultAllocator>& UEnum::GetNamesBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TPair<FName,unsigned char>,FDefaultAllocator>*>(this, offset);
}
const TArray<TPair<FName,unsigned char>,FDefaultAllocator>& UEnum::GetNamesBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TPair<FName,unsigned char>,FDefaultAllocator>*>(this, offset);
}

TArray<TPair<FName,__int64>,FDefaultAllocator>& UEnum::GetNames415()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TPair<FName,__int64>,FDefaultAllocator>*>(this, offset);
}
const TArray<TPair<FName,__int64>,FDefaultAllocator>& UEnum::GetNames415() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TPair<FName,__int64>,FDefaultAllocator>*>(this, offset);
}

TArray<TTuple<FName,__int64>,FDefaultAllocator>& UEnum::GetNames416()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TTuple<FName,__int64>,FDefaultAllocator>*>(this, offset);
}
const TArray<TTuple<FName,__int64>,FDefaultAllocator>& UEnum::GetNames416() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TTuple<FName,__int64>,FDefaultAllocator>*>(this, offset);
}

UEnum::FNameData& UEnum::GetNames507()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<UEnum::FNameData*>(this, offset);
}
const UEnum::FNameData& UEnum::GetNames507() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Names"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::Names' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UEnum::FNameData*>(this, offset);
}

UEnum::ECppForm& UEnum::GetCppForm()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CppForm"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::CppForm' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<UEnum::ECppForm*>(this, offset);
}
const UEnum::ECppForm& UEnum::GetCppForm() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CppForm"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::CppForm' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UEnum::ECppForm*>(this, offset);
}

std::function<void(int32)>*& UEnum::GetEnumDisplayNameFn()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EnumDisplayNameFn"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::EnumDisplayNameFn' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<std::function<void(int32)>**>(this, offset);
}
const std::function<void(int32)>*& UEnum::GetEnumDisplayNameFn() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EnumDisplayNameFn"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::EnumDisplayNameFn' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const std::function<void(int32)>**>(this, offset);
}

EEnumFlags& UEnum::GetEnumFlags_Internal()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EnumFlags_Internal"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::EnumFlags_Internal' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EEnumFlags*>(this, offset);
}
const EEnumFlags& UEnum::GetEnumFlags_Internal() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EnumFlags_Internal"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::EnumFlags_Internal' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EEnumFlags*>(this, offset);
}

FName& UEnum::GetEnumPackage()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EnumPackage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::EnumPackage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UEnum::GetEnumPackage() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EnumPackage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UEnum::EnumPackage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

int32_t& UEnum::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

