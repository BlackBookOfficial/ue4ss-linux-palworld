std::unordered_map<File::StringType, int32_t> USparseDelegateFunction::MemberOffsets{};

FName& USparseDelegateFunction::GetOwningClassName()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OwningClassName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'USparseDelegateFunction::OwningClassName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& USparseDelegateFunction::GetOwningClassName() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OwningClassName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'USparseDelegateFunction::OwningClassName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FName& USparseDelegateFunction::GetDelegateName()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DelegateName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'USparseDelegateFunction::DelegateName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& USparseDelegateFunction::GetDelegateName() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DelegateName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'USparseDelegateFunction::DelegateName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

