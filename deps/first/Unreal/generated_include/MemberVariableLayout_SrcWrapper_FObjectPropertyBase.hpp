std::unordered_map<File::StringType, int32_t> FObjectPropertyBase::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FObjectPropertyBase::BitfieldInfos{};

TObjectPtr<UClass>& FObjectPropertyBase::GetPropertyClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PropertyClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FObjectPropertyBase::PropertyClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UClass>*>(this, offset);
}
const TObjectPtr<UClass>& FObjectPropertyBase::GetPropertyClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PropertyClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FObjectPropertyBase::PropertyClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UClass>*>(this, offset);
}

int32_t& FObjectPropertyBase::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

