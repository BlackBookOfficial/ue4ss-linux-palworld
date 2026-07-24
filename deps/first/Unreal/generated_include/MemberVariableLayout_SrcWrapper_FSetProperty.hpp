std::unordered_map<File::StringType, int32_t> FSetProperty::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FSetProperty::BitfieldInfos{};

FProperty*& FSetProperty::GetElementProp()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ElementProp"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSetProperty::ElementProp' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FProperty**>(this, offset);
}
const FProperty*& FSetProperty::GetElementProp() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ElementProp"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSetProperty::ElementProp' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FProperty**>(this, offset);
}

FScriptSetLayout& FSetProperty::GetSetLayoutBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SetLayout"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSetProperty::SetLayout' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FScriptSetLayout*>(this, offset);
}
const FScriptSetLayout& FSetProperty::GetSetLayoutBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SetLayout"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSetProperty::SetLayout' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FScriptSetLayout*>(this, offset);
}

FScriptSparseSetLayout& FSetProperty::GetSetLayout507()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SetLayout"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSetProperty::SetLayout' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FScriptSparseSetLayout*>(this, offset);
}
const FScriptSparseSetLayout& FSetProperty::GetSetLayout507() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SetLayout"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FSetProperty::SetLayout' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FScriptSparseSetLayout*>(this, offset);
}

int32_t& FSetProperty::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

