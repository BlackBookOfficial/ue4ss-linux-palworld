std::unordered_map<File::StringType, int32_t> FInterfaceProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FInterfaceProperty::BitfieldInfos{};

TObjectPtr<UClass>& FInterfaceProperty::GetInterfaceClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InterfaceClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FInterfaceProperty::InterfaceClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UClass>*>(this, offset);
}
const TObjectPtr<UClass>& FInterfaceProperty::GetInterfaceClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InterfaceClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FInterfaceProperty::InterfaceClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UClass>*>(this, offset);
}

int32_t& FInterfaceProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

