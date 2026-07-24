std::unordered_map<File::StringType, int32_t> FUObjectArray::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FUObjectArray::BitfieldInfos{};

int32& FUObjectArray::GetObjFirstGCIndex()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjFirstGCIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjFirstGCIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FUObjectArray::GetObjFirstGCIndex() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjFirstGCIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjFirstGCIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& FUObjectArray::GetObjLastNonGCIndex()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjLastNonGCIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjLastNonGCIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FUObjectArray::GetObjLastNonGCIndex() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjLastNonGCIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjLastNonGCIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& FUObjectArray::GetOpenForDisregardForGCBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OpenForDisregardForGC"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::OpenForDisregardForGC' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FUObjectArray::GetOpenForDisregardForGCBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OpenForDisregardForGC"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::OpenForDisregardForGC' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

bool& FUObjectArray::GetOpenForDisregardForGC411()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OpenForDisregardForGC"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::OpenForDisregardForGC' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FUObjectArray::GetOpenForDisregardForGC411() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OpenForDisregardForGC"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::OpenForDisregardForGC' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

TUObjectArray& FUObjectArray::GetObjObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TUObjectArray*>(this, offset);
}
const TUObjectArray& FUObjectArray::GetObjObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TUObjectArray*>(this, offset);
}

TLockFreePointerList<int>& FUObjectArray::GetObjAvailableListBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjAvailableList"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjAvailableList' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TLockFreePointerList<int>*>(this, offset);
}
const TLockFreePointerList<int>& FUObjectArray::GetObjAvailableListBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjAvailableList"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjAvailableList' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TLockFreePointerList<int>*>(this, offset);
}

TArray<int,TSizedDefaultAllocator<32> >& FUObjectArray::GetObjAvailableList427()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjAvailableList"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjAvailableList' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<int,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<int,TSizedDefaultAllocator<32> >& FUObjectArray::GetObjAvailableList427() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjAvailableList"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjAvailableList' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<int,TSizedDefaultAllocator<32> >*>(this, offset);
}

TArray<FUObjectArray::FUObjectCreateListener *,TSizedDefaultAllocator<32> >& FUObjectArray::GetUObjectCreateListeners()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UObjectCreateListeners"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::UObjectCreateListeners' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FUObjectArray::FUObjectCreateListener *,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FUObjectArray::FUObjectCreateListener *,TSizedDefaultAllocator<32> >& FUObjectArray::GetUObjectCreateListeners() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UObjectCreateListeners"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::UObjectCreateListeners' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FUObjectArray::FUObjectCreateListener *,TSizedDefaultAllocator<32> >*>(this, offset);
}

TArray<FUObjectArray::FUObjectDeleteListener *,TSizedDefaultAllocator<32> >& FUObjectArray::GetUObjectDeleteListeners()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UObjectDeleteListeners"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::UObjectDeleteListeners' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FUObjectArray::FUObjectDeleteListener *,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FUObjectArray::FUObjectDeleteListener *,TSizedDefaultAllocator<32> >& FUObjectArray::GetUObjectDeleteListeners() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UObjectDeleteListeners"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::UObjectDeleteListeners' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FUObjectArray::FUObjectDeleteListener *,TSizedDefaultAllocator<32> >*>(this, offset);
}

int32& FUObjectArray::GetMaxObjectsNotConsideredByGC()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxObjectsNotConsideredByGC"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::MaxObjectsNotConsideredByGC' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FUObjectArray::GetMaxObjectsNotConsideredByGC() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxObjectsNotConsideredByGC"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::MaxObjectsNotConsideredByGC' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

FThreadSafeCounter& FUObjectArray::GetMasterSerialNumber()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MasterSerialNumber"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::MasterSerialNumber' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FThreadSafeCounter*>(this, offset);
}
const FThreadSafeCounter& FUObjectArray::GetMasterSerialNumber() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MasterSerialNumber"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::MasterSerialNumber' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FThreadSafeCounter*>(this, offset);
}

FThreadSafeCounter& FUObjectArray::GetPrimarySerialNumber()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PrimarySerialNumber"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::PrimarySerialNumber' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FThreadSafeCounter*>(this, offset);
}
const FThreadSafeCounter& FUObjectArray::GetPrimarySerialNumber() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PrimarySerialNumber"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::PrimarySerialNumber' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FThreadSafeCounter*>(this, offset);
}

bool& FUObjectArray::GetbShouldRecycleObjectIndices()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bShouldRecycleObjectIndices"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::bShouldRecycleObjectIndices' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FUObjectArray::GetbShouldRecycleObjectIndices() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bShouldRecycleObjectIndices"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::bShouldRecycleObjectIndices' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

int32& FUObjectArray::GetObjAvailableListEstimateCount()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjAvailableListEstimateCount"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjAvailableListEstimateCount' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FUObjectArray::GetObjAvailableListEstimateCount() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ObjAvailableListEstimateCount"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FUObjectArray::ObjAvailableListEstimateCount' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32_t& FUObjectArray::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

