std::unordered_map<File::StringType, int32_t> FDelegateProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FDelegateProperty::BitfieldInfos{};

TObjectPtr<UFunction>& FDelegateProperty::GetSignatureFunction()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SignatureFunction"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FDelegateProperty::SignatureFunction' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UFunction>*>(this, offset);
}
const TObjectPtr<UFunction>& FDelegateProperty::GetSignatureFunction() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SignatureFunction"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FDelegateProperty::SignatureFunction' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UFunction>*>(this, offset);
}

int32_t& FDelegateProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

