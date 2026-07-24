std::unordered_map<File::StringType, int32_t> UScriptStruct::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UScriptStruct::BitfieldInfos{};

EStructFlags& UScriptStruct::GetStructFlags()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StructFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::StructFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EStructFlags*>(this, offset);
}
const EStructFlags& UScriptStruct::GetStructFlags() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StructFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::StructFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EStructFlags*>(this, offset);
}

bool& UScriptStruct::GetbCppStructOpsFromBaseClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bCppStructOpsFromBaseClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::bCppStructOpsFromBaseClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UScriptStruct::GetbCppStructOpsFromBaseClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bCppStructOpsFromBaseClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::bCppStructOpsFromBaseClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

bool& UScriptStruct::GetbPrepareCppStructOpsCompleted()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bPrepareCppStructOpsCompleted"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::bPrepareCppStructOpsCompleted' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UScriptStruct::GetbPrepareCppStructOpsCompleted() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bPrepareCppStructOpsCompleted"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::bPrepareCppStructOpsCompleted' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

UScriptStruct::ICppStructOps*& UScriptStruct::GetCppStructOps()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CppStructOps"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::CppStructOps' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<UScriptStruct::ICppStructOps**>(this, offset);
}
const UScriptStruct::ICppStructOps*& UScriptStruct::GetCppStructOps() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CppStructOps"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::CppStructOps' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UScriptStruct::ICppStructOps**>(this, offset);
}

int32_t& UScriptStruct::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

