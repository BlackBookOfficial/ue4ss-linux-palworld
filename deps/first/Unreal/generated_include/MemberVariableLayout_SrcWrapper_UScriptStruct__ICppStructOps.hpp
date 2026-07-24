std::unordered_map<File::StringType, int32_t> UScriptStruct::ICppStructOps::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UScriptStruct::ICppStructOps::BitfieldInfos{};

const int32& UScriptStruct::ICppStructOps::GetSize()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Size"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::ICppStructOps::Size' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}
const int32& UScriptStruct::ICppStructOps::GetSize() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Size"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::ICppStructOps::Size' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

const int32& UScriptStruct::ICppStructOps::GetAlignment()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Alignment"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::ICppStructOps::Alignment' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}
const int32& UScriptStruct::ICppStructOps::GetAlignment() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Alignment"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::ICppStructOps::Alignment' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

const UE::CoreUObject::Private::FStructOpsFakeVTable*& UScriptStruct::ICppStructOps::GetFakeVPtr()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FakeVPtr"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::ICppStructOps::FakeVPtr' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UE::CoreUObject::Private::FStructOpsFakeVTable**>(this, offset);
}
const UE::CoreUObject::Private::FStructOpsFakeVTable*& UScriptStruct::ICppStructOps::GetFakeVPtr() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FakeVPtr"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UScriptStruct::ICppStructOps::FakeVPtr' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UE::CoreUObject::Private::FStructOpsFakeVTable**>(this, offset);
}

int32_t& UScriptStruct::ICppStructOps::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

