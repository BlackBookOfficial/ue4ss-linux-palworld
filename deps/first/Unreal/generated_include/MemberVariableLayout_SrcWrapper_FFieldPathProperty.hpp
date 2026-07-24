std::unordered_map<File::StringType, int32_t> FFieldPathProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FFieldPathProperty::BitfieldInfos{};

FFieldClass*& FFieldPathProperty::GetPropertyClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PropertyClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FFieldPathProperty::PropertyClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FFieldClass**>(this, offset);
}
const FFieldClass*& FFieldPathProperty::GetPropertyClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PropertyClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FFieldPathProperty::PropertyClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FFieldClass**>(this, offset);
}

int32_t& FFieldPathProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

