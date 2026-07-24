std::unordered_map<File::StringType, int32_t> FSoftClassProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FSoftClassProperty::BitfieldInfos{};

TObjectPtr<UClass>& FSoftClassProperty::GetMetaClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MetaClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSoftClassProperty::MetaClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UClass>*>(this, offset);
}
const TObjectPtr<UClass>& FSoftClassProperty::GetMetaClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MetaClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSoftClassProperty::MetaClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UClass>*>(this, offset);
}

int32_t& FSoftClassProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

