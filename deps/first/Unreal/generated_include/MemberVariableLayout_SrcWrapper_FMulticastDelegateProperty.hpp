std::unordered_map<File::StringType, int32_t> FMulticastDelegateProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FMulticastDelegateProperty::BitfieldInfos{};

TObjectPtr<UFunction>& FMulticastDelegateProperty::GetSignatureFunction()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SignatureFunction"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FMulticastDelegateProperty::SignatureFunction' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UFunction>*>(this, offset);
}
const TObjectPtr<UFunction>& FMulticastDelegateProperty::GetSignatureFunction() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SignatureFunction"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FMulticastDelegateProperty::SignatureFunction' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UFunction>*>(this, offset);
}

int32_t& FMulticastDelegateProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

