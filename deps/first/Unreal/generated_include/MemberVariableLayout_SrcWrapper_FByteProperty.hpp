std::unordered_map<File::StringType, int32_t> FByteProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FByteProperty::BitfieldInfos{};

TObjectPtr<UEnum>& FByteProperty::GetEnum()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Enum"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FByteProperty::Enum' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UEnum>*>(this, offset);
}
const TObjectPtr<UEnum>& FByteProperty::GetEnum() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Enum"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FByteProperty::Enum' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UEnum>*>(this, offset);
}

int32_t& FByteProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

