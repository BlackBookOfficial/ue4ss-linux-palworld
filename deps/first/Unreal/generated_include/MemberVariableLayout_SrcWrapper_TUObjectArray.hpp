std::unordered_map<File::StringType, int32_t> TUObjectArray::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> TUObjectArray::BitfieldInfos{};

FUObjectItem**& TUObjectArray::GetObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Objects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::Objects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FUObjectItem***>(this, offset);
}
const FUObjectItem**& TUObjectArray::GetObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Objects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::Objects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FUObjectItem***>(this, offset);
}

FUObjectItem*& TUObjectArray::GetPreAllocatedObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PreAllocatedObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::PreAllocatedObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FUObjectItem**>(this, offset);
}
const FUObjectItem*& TUObjectArray::GetPreAllocatedObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PreAllocatedObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::PreAllocatedObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FUObjectItem**>(this, offset);
}

int32& TUObjectArray::GetMaxElements()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxElements"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::MaxElements' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& TUObjectArray::GetMaxElements() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxElements"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::MaxElements' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& TUObjectArray::GetNumElements()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumElements"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::NumElements' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& TUObjectArray::GetNumElements() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumElements"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::NumElements' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& TUObjectArray::GetMaxChunks()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxChunks"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::MaxChunks' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& TUObjectArray::GetMaxChunks() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxChunks"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::MaxChunks' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& TUObjectArray::GetNumChunks()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumChunks"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::NumChunks' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& TUObjectArray::GetNumChunks() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumChunks"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'TUObjectArray::NumChunks' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32_t& TUObjectArray::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

