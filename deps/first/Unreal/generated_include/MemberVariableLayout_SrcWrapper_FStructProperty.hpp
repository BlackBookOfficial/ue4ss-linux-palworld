std::unordered_map<File::StringType, int32_t> FStructProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FStructProperty::BitfieldInfos{};

TObjectPtr<UScriptStruct>& FStructProperty::GetStruct()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Struct"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FStructProperty::Struct' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UScriptStruct>*>(this, offset);
}
const TObjectPtr<UScriptStruct>& FStructProperty::GetStruct() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Struct"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FStructProperty::Struct' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UScriptStruct>*>(this, offset);
}

int32_t& FStructProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

