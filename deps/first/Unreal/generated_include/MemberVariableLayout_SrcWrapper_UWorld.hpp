std::unordered_map<File::StringType, int32_t> UWorld::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UWorld::BitfieldInfos{};

TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& UWorld::GetExtraReferencedObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ExtraReferencedObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::ExtraReferencedObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& UWorld::GetExtraReferencedObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ExtraReferencedObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::ExtraReferencedObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >*>(this, offset);
}

TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& UWorld::GetPerModuleDataObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PerModuleDataObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PerModuleDataObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >& UWorld::GetPerModuleDataObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PerModuleDataObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PerModuleDataObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TObjectPtr<UObject>,TSizedDefaultAllocator<32> >*>(this, offset);
}

FString& UWorld::GetStreamingLevelsPrefix()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StreamingLevelsPrefix"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::StreamingLevelsPrefix' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& UWorld::GetStreamingLevelsPrefix() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StreamingLevelsPrefix"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::StreamingLevelsPrefix' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

TArray<FVector,TSizedDefaultAllocator<32> >& UWorld::GetViewLocationsRenderedLastFrame()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewLocationsRenderedLastFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::ViewLocationsRenderedLastFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FVector,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FVector,TSizedDefaultAllocator<32> >& UWorld::GetViewLocationsRenderedLastFrame() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewLocationsRenderedLastFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::ViewLocationsRenderedLastFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FVector,TSizedDefaultAllocator<32> >*>(this, offset);
}

BitfieldProxy UWorld::GetbWorldWasLoadedThisTick()
{
    static auto offset_it = MemberOffsets.find(STR("bWorldWasLoadedThisTick"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bWorldWasLoadedThisTick' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bWorldWasLoadedThisTick"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bWorldWasLoadedThisTick'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbWorldWasLoadedThisTick() const
{
    static auto offset_it = MemberOffsets.find(STR("bWorldWasLoadedThisTick"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bWorldWasLoadedThisTick' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bWorldWasLoadedThisTick"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bWorldWasLoadedThisTick'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbTriggerPostLoadMap()
{
    static auto offset_it = MemberOffsets.find(STR("bTriggerPostLoadMap"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bTriggerPostLoadMap' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTriggerPostLoadMap"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bTriggerPostLoadMap'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbTriggerPostLoadMap() const
{
    static auto offset_it = MemberOffsets.find(STR("bTriggerPostLoadMap"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bTriggerPostLoadMap' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTriggerPostLoadMap"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bTriggerPostLoadMap'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TObjectPtr<AGameModeBase>& UWorld::GetAuthorityGameMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AuthorityGameMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AuthorityGameMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<AGameModeBase>*>(this, offset);
}
const TObjectPtr<AGameModeBase>& UWorld::GetAuthorityGameMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AuthorityGameMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AuthorityGameMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<AGameModeBase>*>(this, offset);
}

TSet<AActor *,DefaultKeyFuncs<AActor *,0>,FDefaultSetAllocator>& UWorld::GetNetworkActors()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetworkActors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NetworkActors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSet<AActor *,DefaultKeyFuncs<AActor *,0>,FDefaultSetAllocator>*>(this, offset);
}
const TSet<AActor *,DefaultKeyFuncs<AActor *,0>,FDefaultSetAllocator>& UWorld::GetNetworkActors() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetworkActors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NetworkActors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSet<AActor *,DefaultKeyFuncs<AActor *,0>,FDefaultSetAllocator>*>(this, offset);
}

BitfieldProxy UWorld::GetbRequiresHitProxies()
{
    static auto offset_it = MemberOffsets.find(STR("bRequiresHitProxies"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bRequiresHitProxies' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRequiresHitProxies"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bRequiresHitProxies'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbRequiresHitProxies() const
{
    static auto offset_it = MemberOffsets.find(STR("bRequiresHitProxies"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bRequiresHitProxies' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRequiresHitProxies"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bRequiresHitProxies'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbStreamingDataDirty()
{
    static auto offset_it = MemberOffsets.find(STR("bStreamingDataDirty"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bStreamingDataDirty' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStreamingDataDirty"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bStreamingDataDirty'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbStreamingDataDirty() const
{
    static auto offset_it = MemberOffsets.find(STR("bStreamingDataDirty"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bStreamingDataDirty' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStreamingDataDirty"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bStreamingDataDirty'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

double& UWorld::GetBuildStreamingDataTimer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("BuildStreamingDataTimer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::BuildStreamingDataTimer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetBuildStreamingDataTimer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("BuildStreamingDataTimer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::BuildStreamingDataTimer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

FURL& UWorld::GetURL()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("URL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::URL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FURL*>(this, offset);
}
const FURL& UWorld::GetURL() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("URL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::URL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FURL*>(this, offset);
}

BitfieldProxy UWorld::GetbInTick()
{
    static auto offset_it = MemberOffsets.find(STR("bInTick"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bInTick' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bInTick"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bInTick'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbInTick() const
{
    static auto offset_it = MemberOffsets.find(STR("bInTick"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bInTick' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bInTick"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bInTick'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbIsBuilt()
{
    static auto offset_it = MemberOffsets.find(STR("bIsBuilt"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsBuilt' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsBuilt"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsBuilt'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsBuilt() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsBuilt"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsBuilt' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsBuilt"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsBuilt'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbTickNewlySpawned()
{
    static auto offset_it = MemberOffsets.find(STR("bTickNewlySpawned"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bTickNewlySpawned' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTickNewlySpawned"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bTickNewlySpawned'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbTickNewlySpawned() const
{
    static auto offset_it = MemberOffsets.find(STR("bTickNewlySpawned"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bTickNewlySpawned' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTickNewlySpawned"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bTickNewlySpawned'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbPostTickComponentUpdate()
{
    static auto offset_it = MemberOffsets.find(STR("bPostTickComponentUpdate"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bPostTickComponentUpdate' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPostTickComponentUpdate"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bPostTickComponentUpdate'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbPostTickComponentUpdate() const
{
    static auto offset_it = MemberOffsets.find(STR("bPostTickComponentUpdate"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bPostTickComponentUpdate' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPostTickComponentUpdate"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bPostTickComponentUpdate'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32& UWorld::GetPlayerNum()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PlayerNum"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PlayerNum' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UWorld::GetPlayerNum() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PlayerNum"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PlayerNum' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

float& UWorld::GetTimeSinceLastPendingKillPurge()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimeSinceLastPendingKillPurge"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::TimeSinceLastPendingKillPurge' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetTimeSinceLastPendingKillPurge() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimeSinceLastPendingKillPurge"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::TimeSinceLastPendingKillPurge' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

bool& UWorld::GetFullPurgeTriggered()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FullPurgeTriggered"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::FullPurgeTriggered' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetFullPurgeTriggered() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FullPurgeTriggered"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::FullPurgeTriggered' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

bool& UWorld::GetbShouldDelayGarbageCollect()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bShouldDelayGarbageCollect"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldDelayGarbageCollect' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbShouldDelayGarbageCollect() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bShouldDelayGarbageCollect"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldDelayGarbageCollect' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

BitfieldProxy UWorld::GetbIsWorldInitialized()
{
    static auto offset_it = MemberOffsets.find(STR("bIsWorldInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsWorldInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsWorldInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsWorldInitialized'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsWorldInitialized() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsWorldInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsWorldInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsWorldInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsWorldInitialized'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32& UWorld::GetStreamingVolumeUpdateDelay()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StreamingVolumeUpdateDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::StreamingVolumeUpdateDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UWorld::GetStreamingVolumeUpdateDelay() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("StreamingVolumeUpdateDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::StreamingVolumeUpdateDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

BitfieldProxy UWorld::GetbIsLevelStreamingFrozen()
{
    static auto offset_it = MemberOffsets.find(STR("bIsLevelStreamingFrozen"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsLevelStreamingFrozen' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsLevelStreamingFrozen"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsLevelStreamingFrozen'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsLevelStreamingFrozen() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsLevelStreamingFrozen"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsLevelStreamingFrozen' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsLevelStreamingFrozen"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsLevelStreamingFrozen'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbShouldForceUnloadStreamingLevels()
{
    static auto offset_it = MemberOffsets.find(STR("bShouldForceUnloadStreamingLevels"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldForceUnloadStreamingLevels' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldForceUnloadStreamingLevels"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldForceUnloadStreamingLevels'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbShouldForceUnloadStreamingLevels() const
{
    static auto offset_it = MemberOffsets.find(STR("bShouldForceUnloadStreamingLevels"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldForceUnloadStreamingLevels' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldForceUnloadStreamingLevels"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldForceUnloadStreamingLevels'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbShouldForceVisibleStreamingLevels()
{
    static auto offset_it = MemberOffsets.find(STR("bShouldForceVisibleStreamingLevels"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldForceVisibleStreamingLevels' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldForceVisibleStreamingLevels"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldForceVisibleStreamingLevels'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbShouldForceVisibleStreamingLevels() const
{
    static auto offset_it = MemberOffsets.find(STR("bShouldForceVisibleStreamingLevels"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldForceVisibleStreamingLevels' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldForceVisibleStreamingLevels"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldForceVisibleStreamingLevels'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbDoDelayedUpdateCullDistanceVolumes()
{
    static auto offset_it = MemberOffsets.find(STR("bDoDelayedUpdateCullDistanceVolumes"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDoDelayedUpdateCullDistanceVolumes' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDoDelayedUpdateCullDistanceVolumes"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDoDelayedUpdateCullDistanceVolumes'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbDoDelayedUpdateCullDistanceVolumes() const
{
    static auto offset_it = MemberOffsets.find(STR("bDoDelayedUpdateCullDistanceVolumes"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDoDelayedUpdateCullDistanceVolumes' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDoDelayedUpdateCullDistanceVolumes"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDoDelayedUpdateCullDistanceVolumes'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

bool& UWorld::GetbHack_Force_UsesGameHiddenFlags_True()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHack_Force_UsesGameHiddenFlags_True"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bHack_Force_UsesGameHiddenFlags_True' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbHack_Force_UsesGameHiddenFlags_True() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHack_Force_UsesGameHiddenFlags_True"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bHack_Force_UsesGameHiddenFlags_True' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

BitfieldProxy UWorld::GetbIsRunningConstructionScript()
{
    static auto offset_it = MemberOffsets.find(STR("bIsRunningConstructionScript"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsRunningConstructionScript' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsRunningConstructionScript"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsRunningConstructionScript'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsRunningConstructionScript() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsRunningConstructionScript"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsRunningConstructionScript' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsRunningConstructionScript"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsRunningConstructionScript'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbShouldSimulatePhysics()
{
    static auto offset_it = MemberOffsets.find(STR("bShouldSimulatePhysics"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldSimulatePhysics' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldSimulatePhysics"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldSimulatePhysics'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbShouldSimulatePhysics() const
{
    static auto offset_it = MemberOffsets.find(STR("bShouldSimulatePhysics"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldSimulatePhysics' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldSimulatePhysics"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldSimulatePhysics'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FName& UWorld::GetDebugDrawTraceTag()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DebugDrawTraceTag"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::DebugDrawTraceTag' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UWorld::GetDebugDrawTraceTag() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DebugDrawTraceTag"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::DebugDrawTraceTag' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

uint32& UWorld::GetAudioDeviceHandle()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AudioDeviceHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetAudioDeviceHandle() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AudioDeviceHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

double& UWorld::GetLastTimeUnbuiltLightingWasEncountered()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastTimeUnbuiltLightingWasEncountered"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LastTimeUnbuiltLightingWasEncountered' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetLastTimeUnbuiltLightingWasEncountered() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastTimeUnbuiltLightingWasEncountered"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LastTimeUnbuiltLightingWasEncountered' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

float& UWorld::GetTimeSecondsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::TimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetTimeSecondsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::TimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

double& UWorld::GetTimeSeconds501()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::TimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetTimeSeconds501() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::TimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

float& UWorld::GetRealTimeSecondsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RealTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::RealTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetRealTimeSecondsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RealTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::RealTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

double& UWorld::GetRealTimeSeconds501()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RealTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::RealTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetRealTimeSeconds501() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RealTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::RealTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

float& UWorld::GetAudioTimeSecondsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AudioTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetAudioTimeSecondsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AudioTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

double& UWorld::GetAudioTimeSeconds501()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AudioTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetAudioTimeSeconds501() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AudioTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

float& UWorld::GetDeltaTimeSeconds()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DeltaTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::DeltaTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetDeltaTimeSeconds() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DeltaTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::DeltaTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

float& UWorld::GetPauseDelayBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PauseDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PauseDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetPauseDelayBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PauseDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PauseDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

double& UWorld::GetPauseDelay501()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PauseDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PauseDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetPauseDelay501() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PauseDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PauseDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

bool& UWorld::GetbOriginOffsetThisFrame()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bOriginOffsetThisFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bOriginOffsetThisFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbOriginOffsetThisFrame() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bOriginOffsetThisFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bOriginOffsetThisFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

FString& UWorld::GetNextURL()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NextURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NextURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& UWorld::GetNextURL() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NextURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NextURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

float& UWorld::GetNextSwitchCountdown()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NextSwitchCountdown"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NextSwitchCountdown' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetNextSwitchCountdown() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NextSwitchCountdown"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NextSwitchCountdown' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

TArray<FName,TSizedDefaultAllocator<32> >& UWorld::GetPreparingLevelNames()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PreparingLevelNames"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PreparingLevelNames' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FName,TSizedDefaultAllocator<32> >& UWorld::GetPreparingLevelNames() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PreparingLevelNames"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PreparingLevelNames' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}

FName& UWorld::GetCommittedPersistentLevelName()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CommittedPersistentLevelName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::CommittedPersistentLevelName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& UWorld::GetCommittedPersistentLevelName() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CommittedPersistentLevelName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::CommittedPersistentLevelName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

uint32& UWorld::GetNumLightingUnbuiltObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumLightingUnbuiltObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumLightingUnbuiltObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetNumLightingUnbuiltObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumLightingUnbuiltObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumLightingUnbuiltObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

BitfieldProxy UWorld::GetbDropDetail()
{
    static auto offset_it = MemberOffsets.find(STR("bDropDetail"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDropDetail' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDropDetail"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDropDetail'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbDropDetail() const
{
    static auto offset_it = MemberOffsets.find(STR("bDropDetail"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDropDetail' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDropDetail"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDropDetail'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbAggressiveLOD()
{
    static auto offset_it = MemberOffsets.find(STR("bAggressiveLOD"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAggressiveLOD' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAggressiveLOD"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bAggressiveLOD'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbAggressiveLOD() const
{
    static auto offset_it = MemberOffsets.find(STR("bAggressiveLOD"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAggressiveLOD' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAggressiveLOD"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bAggressiveLOD'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbIsDefaultLevel()
{
    static auto offset_it = MemberOffsets.find(STR("bIsDefaultLevel"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsDefaultLevel' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsDefaultLevel"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsDefaultLevel'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsDefaultLevel() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsDefaultLevel"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsDefaultLevel' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsDefaultLevel"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsDefaultLevel'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbRequestedBlockOnAsyncLoading()
{
    static auto offset_it = MemberOffsets.find(STR("bRequestedBlockOnAsyncLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bRequestedBlockOnAsyncLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRequestedBlockOnAsyncLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bRequestedBlockOnAsyncLoading'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbRequestedBlockOnAsyncLoading() const
{
    static auto offset_it = MemberOffsets.find(STR("bRequestedBlockOnAsyncLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bRequestedBlockOnAsyncLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRequestedBlockOnAsyncLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bRequestedBlockOnAsyncLoading'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbActorsInitialized()
{
    static auto offset_it = MemberOffsets.find(STR("bActorsInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bActorsInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorsInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bActorsInitialized'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbActorsInitialized() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorsInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bActorsInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorsInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bActorsInitialized'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbBegunPlay()
{
    static auto offset_it = MemberOffsets.find(STR("bBegunPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bBegunPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bBegunPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bBegunPlay'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbBegunPlay() const
{
    static auto offset_it = MemberOffsets.find(STR("bBegunPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bBegunPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bBegunPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bBegunPlay'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbMatchStarted()
{
    static auto offset_it = MemberOffsets.find(STR("bMatchStarted"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bMatchStarted' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bMatchStarted"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bMatchStarted'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbMatchStarted() const
{
    static auto offset_it = MemberOffsets.find(STR("bMatchStarted"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bMatchStarted' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bMatchStarted"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bMatchStarted'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbPlayersOnly()
{
    static auto offset_it = MemberOffsets.find(STR("bPlayersOnly"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bPlayersOnly' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPlayersOnly"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bPlayersOnly'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbPlayersOnly() const
{
    static auto offset_it = MemberOffsets.find(STR("bPlayersOnly"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bPlayersOnly' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPlayersOnly"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bPlayersOnly'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbPlayersOnlyPending()
{
    static auto offset_it = MemberOffsets.find(STR("bPlayersOnlyPending"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bPlayersOnlyPending' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPlayersOnlyPending"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bPlayersOnlyPending'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbPlayersOnlyPending() const
{
    static auto offset_it = MemberOffsets.find(STR("bPlayersOnlyPending"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bPlayersOnlyPending' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPlayersOnlyPending"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bPlayersOnlyPending'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbStartup()
{
    static auto offset_it = MemberOffsets.find(STR("bStartup"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bStartup' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStartup"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bStartup'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbStartup() const
{
    static auto offset_it = MemberOffsets.find(STR("bStartup"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bStartup' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStartup"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bStartup'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbIsTearingDown()
{
    static auto offset_it = MemberOffsets.find(STR("bIsTearingDown"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsTearingDown' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsTearingDown"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsTearingDown'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsTearingDown() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsTearingDown"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsTearingDown' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsTearingDown"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsTearingDown'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbKismetScriptError()
{
    static auto offset_it = MemberOffsets.find(STR("bKismetScriptError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bKismetScriptError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bKismetScriptError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bKismetScriptError'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbKismetScriptError() const
{
    static auto offset_it = MemberOffsets.find(STR("bKismetScriptError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bKismetScriptError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bKismetScriptError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bKismetScriptError'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbDebugPauseExecution()
{
    static auto offset_it = MemberOffsets.find(STR("bDebugPauseExecution"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDebugPauseExecution' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDebugPauseExecution"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDebugPauseExecution'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbDebugPauseExecution() const
{
    static auto offset_it = MemberOffsets.find(STR("bDebugPauseExecution"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDebugPauseExecution' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDebugPauseExecution"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDebugPauseExecution'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbAllowAudioPlayback()
{
    static auto offset_it = MemberOffsets.find(STR("bAllowAudioPlayback"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAllowAudioPlayback' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAllowAudioPlayback"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bAllowAudioPlayback'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbAllowAudioPlayback() const
{
    static auto offset_it = MemberOffsets.find(STR("bAllowAudioPlayback"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAllowAudioPlayback' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAllowAudioPlayback"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bAllowAudioPlayback'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbDebugFrameStepExecution()
{
    static auto offset_it = MemberOffsets.find(STR("bDebugFrameStepExecution"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDebugFrameStepExecution' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDebugFrameStepExecution"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDebugFrameStepExecution'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbDebugFrameStepExecution() const
{
    static auto offset_it = MemberOffsets.find(STR("bDebugFrameStepExecution"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDebugFrameStepExecution' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDebugFrameStepExecution"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bDebugFrameStepExecution'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbAreConstraintsDirty()
{
    static auto offset_it = MemberOffsets.find(STR("bAreConstraintsDirty"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAreConstraintsDirty' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAreConstraintsDirty"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bAreConstraintsDirty'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbAreConstraintsDirty() const
{
    static auto offset_it = MemberOffsets.find(STR("bAreConstraintsDirty"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAreConstraintsDirty' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAreConstraintsDirty"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bAreConstraintsDirty'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FThreadSafeCounter& UWorld::GetAsyncPreRegisterLevelStreamingTasks()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AsyncPreRegisterLevelStreamingTasks"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AsyncPreRegisterLevelStreamingTasks' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FThreadSafeCounter*>(this, offset);
}
const FThreadSafeCounter& UWorld::GetAsyncPreRegisterLevelStreamingTasks() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AsyncPreRegisterLevelStreamingTasks"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::AsyncPreRegisterLevelStreamingTasks' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FThreadSafeCounter*>(this, offset);
}

bool& UWorld::GetbCreateRenderStateForHiddenComponents()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bCreateRenderStateForHiddenComponents"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bCreateRenderStateForHiddenComponents' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbCreateRenderStateForHiddenComponents() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bCreateRenderStateForHiddenComponents"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bCreateRenderStateForHiddenComponents' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

BitfieldProxy UWorld::GetbShouldTick()
{
    static auto offset_it = MemberOffsets.find(STR("bShouldTick"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldTick' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldTick"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldTick'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbShouldTick() const
{
    static auto offset_it = MemberOffsets.find(STR("bShouldTick"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bShouldTick' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldTick"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bShouldTick'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

float& UWorld::GetUnpausedTimeSecondsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UnpausedTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::UnpausedTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetUnpausedTimeSecondsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UnpausedTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::UnpausedTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

double& UWorld::GetUnpausedTimeSeconds501()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UnpausedTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::UnpausedTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetUnpausedTimeSeconds501() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UnpausedTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::UnpausedTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

uint32& UWorld::GetNumInvalidReflectionCaptureComponents()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumInvalidReflectionCaptureComponents"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumInvalidReflectionCaptureComponents' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetNumInvalidReflectionCaptureComponents() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumInvalidReflectionCaptureComponents"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumInvalidReflectionCaptureComponents' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

int32& UWorld::GetNumTextureStreamingUnbuiltComponents()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumTextureStreamingUnbuiltComponents"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumTextureStreamingUnbuiltComponents' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UWorld::GetNumTextureStreamingUnbuiltComponents() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumTextureStreamingUnbuiltComponents"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumTextureStreamingUnbuiltComponents' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& UWorld::GetNumTextureStreamingDirtyResources()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumTextureStreamingDirtyResources"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumTextureStreamingDirtyResources' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UWorld::GetNumTextureStreamingDirtyResources() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumTextureStreamingDirtyResources"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumTextureStreamingDirtyResources' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

BitfieldProxy UWorld::GetbIsCameraMoveableWhenPaused()
{
    static auto offset_it = MemberOffsets.find(STR("bIsCameraMoveableWhenPaused"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsCameraMoveableWhenPaused' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsCameraMoveableWhenPaused"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsCameraMoveableWhenPaused'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbIsCameraMoveableWhenPaused() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsCameraMoveableWhenPaused"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsCameraMoveableWhenPaused' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsCameraMoveableWhenPaused"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bIsCameraMoveableWhenPaused'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FVector& UWorld::GetOriginOffsetThisFrame()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OriginOffsetThisFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::OriginOffsetThisFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FVector*>(this, offset);
}
const FVector& UWorld::GetOriginOffsetThisFrame() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OriginOffsetThisFrame"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::OriginOffsetThisFrame' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FVector*>(this, offset);
}

bool& UWorld::GetbDebugDrawAllTraceTags()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bDebugDrawAllTraceTags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDebugDrawAllTraceTags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbDebugDrawAllTraceTags() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bDebugDrawAllTraceTags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bDebugDrawAllTraceTags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

int32& UWorld::GetActiveLevelCollectionIndex()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ActiveLevelCollectionIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::ActiveLevelCollectionIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UWorld::GetActiveLevelCollectionIndex() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ActiveLevelCollectionIndex"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::ActiveLevelCollectionIndex' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

uint32& UWorld::GetNumUnbuiltReflectionCaptures()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumUnbuiltReflectionCaptures"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumUnbuiltReflectionCaptures' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetNumUnbuiltReflectionCaptures() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumUnbuiltReflectionCaptures"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumUnbuiltReflectionCaptures' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

BitfieldProxy UWorld::GetbMaterialParameterCollectionInstanceNeedsDeferredUpdate()
{
    static auto offset_it = MemberOffsets.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bMaterialParameterCollectionInstanceNeedsDeferredUpdate' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bMaterialParameterCollectionInstanceNeedsDeferredUpdate'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbMaterialParameterCollectionInstanceNeedsDeferredUpdate() const
{
    static auto offset_it = MemberOffsets.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bMaterialParameterCollectionInstanceNeedsDeferredUpdate' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bMaterialParameterCollectionInstanceNeedsDeferredUpdate"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bMaterialParameterCollectionInstanceNeedsDeferredUpdate'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbCleanedUpWorld()
{
    static auto offset_it = MemberOffsets.find(STR("bCleanedUpWorld"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bCleanedUpWorld' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCleanedUpWorld"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bCleanedUpWorld'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbCleanedUpWorld() const
{
    static auto offset_it = MemberOffsets.find(STR("bCleanedUpWorld"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bCleanedUpWorld' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCleanedUpWorld"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bCleanedUpWorld'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UWorld::GetbMarkedObjectsPendingKill()
{
    static auto offset_it = MemberOffsets.find(STR("bMarkedObjectsPendingKill"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bMarkedObjectsPendingKill' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bMarkedObjectsPendingKill"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bMarkedObjectsPendingKill'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbMarkedObjectsPendingKill() const
{
    static auto offset_it = MemberOffsets.find(STR("bMarkedObjectsPendingKill"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bMarkedObjectsPendingKill' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bMarkedObjectsPendingKill"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bMarkedObjectsPendingKill'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TArray<AActor *,TSizedDefaultAllocator<32> >& UWorld::GetLevelSequenceActors()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LevelSequenceActors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LevelSequenceActors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<AActor *,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<AActor *,TSizedDefaultAllocator<32> >& UWorld::GetLevelSequenceActors() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LevelSequenceActors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LevelSequenceActors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<AActor *,TSizedDefaultAllocator<32> >*>(this, offset);
}

uint16& UWorld::GetNumStreamingLevelsBeingLoaded()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumStreamingLevelsBeingLoaded"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumStreamingLevelsBeingLoaded' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint16*>(this, offset);
}
const uint16& UWorld::GetNumStreamingLevelsBeingLoaded() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumStreamingLevelsBeingLoaded"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::NumStreamingLevelsBeingLoaded' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint16*>(this, offset);
}

uint32& UWorld::GetCleanupWorldTag()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CleanupWorldTag"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::CleanupWorldTag' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetCleanupWorldTag() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CleanupWorldTag"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::CleanupWorldTag' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

bool& UWorld::GetbAllowDeferredPhysicsStateCreation()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bAllowDeferredPhysicsStateCreation"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAllowDeferredPhysicsStateCreation' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbAllowDeferredPhysicsStateCreation() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bAllowDeferredPhysicsStateCreation"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bAllowDeferredPhysicsStateCreation' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

BitfieldProxy UWorld::GetbInitializedAndNeedsCleanup()
{
    static auto offset_it = MemberOffsets.find(STR("bInitializedAndNeedsCleanup"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bInitializedAndNeedsCleanup' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bInitializedAndNeedsCleanup"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bInitializedAndNeedsCleanup'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbInitializedAndNeedsCleanup() const
{
    static auto offset_it = MemberOffsets.find(STR("bInitializedAndNeedsCleanup"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bInitializedAndNeedsCleanup' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bInitializedAndNeedsCleanup"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bInitializedAndNeedsCleanup'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

uint32& UWorld::GetIsInBlockTillLevelStreamingCompleted()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("IsInBlockTillLevelStreamingCompleted"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::IsInBlockTillLevelStreamingCompleted' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetIsInBlockTillLevelStreamingCompleted() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("IsInBlockTillLevelStreamingCompleted"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::IsInBlockTillLevelStreamingCompleted' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

int32& UWorld::GetBlockTillLevelStreamingCompletedEpoch()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("BlockTillLevelStreamingCompletedEpoch"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::BlockTillLevelStreamingCompletedEpoch' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UWorld::GetBlockTillLevelStreamingCompletedEpoch() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("BlockTillLevelStreamingCompletedEpoch"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::BlockTillLevelStreamingCompletedEpoch' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

uint32& UWorld::GetLWILastAssignedUID()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LWILastAssignedUID"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LWILastAssignedUID' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UWorld::GetLWILastAssignedUID() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LWILastAssignedUID"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LWILastAssignedUID' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

float& UWorld::GetDeltaRealTimeSeconds()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DeltaRealTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::DeltaRealTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& UWorld::GetDeltaRealTimeSeconds() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DeltaRealTimeSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::DeltaRealTimeSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

TOptional<bool>& UWorld::GetbSupportsMakingVisibleTransactionRequests()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bSupportsMakingVisibleTransactionRequests"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bSupportsMakingVisibleTransactionRequests' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TOptional<bool>*>(this, offset);
}
const TOptional<bool>& UWorld::GetbSupportsMakingVisibleTransactionRequests() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bSupportsMakingVisibleTransactionRequests"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bSupportsMakingVisibleTransactionRequests' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TOptional<bool>*>(this, offset);
}

TOptional<bool>& UWorld::GetbSupportsMakingInvisibleTransactionRequests()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bSupportsMakingInvisibleTransactionRequests"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bSupportsMakingInvisibleTransactionRequests' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TOptional<bool>*>(this, offset);
}
const TOptional<bool>& UWorld::GetbSupportsMakingInvisibleTransactionRequests() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bSupportsMakingInvisibleTransactionRequests"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bSupportsMakingInvisibleTransactionRequests' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TOptional<bool>*>(this, offset);
}

double& UWorld::GetLastRenderTime()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<double*>(this, offset);
}
const double& UWorld::GetLastRenderTime() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::LastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const double*>(this, offset);
}

BitfieldProxy UWorld::GetbHasEverBeenInitialized()
{
    static auto offset_it = MemberOffsets.find(STR("bHasEverBeenInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bHasEverBeenInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasEverBeenInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bHasEverBeenInitialized'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UWorld::GetbHasEverBeenInitialized() const
{
    static auto offset_it = MemberOffsets.find(STR("bHasEverBeenInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bHasEverBeenInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasEverBeenInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UWorld::bHasEverBeenInitialized'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

bool& UWorld::GetbIsBeingCleanedUp()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIsBeingCleanedUp"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsBeingCleanedUp' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& UWorld::GetbIsBeingCleanedUp() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIsBeingCleanedUp"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::bIsBeingCleanedUp' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

UE::FPlatformRWLock& UWorld::GetPendingVisibilityLock()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PendingVisibilityLock"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PendingVisibilityLock' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<UE::FPlatformRWLock*>(this, offset);
}
const UE::FPlatformRWLock& UWorld::GetPendingVisibilityLock() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PendingVisibilityLock"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PendingVisibilityLock' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UE::FPlatformRWLock*>(this, offset);
}

TArray<double,TSizedDefaultAllocator<32> >& UWorld::GetPostProcessVolumeCachedSizes()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PostProcessVolumeCachedSizes"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PostProcessVolumeCachedSizes' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<double,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<double,TSizedDefaultAllocator<32> >& UWorld::GetPostProcessVolumeCachedSizes() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PostProcessVolumeCachedSizes"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UWorld::PostProcessVolumeCachedSizes' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<double,TSizedDefaultAllocator<32> >*>(this, offset);
}

int32_t& UWorld::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

