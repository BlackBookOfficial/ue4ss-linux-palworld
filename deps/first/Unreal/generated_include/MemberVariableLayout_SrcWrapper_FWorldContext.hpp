std::unordered_map<File::StringType, int32_t> FWorldContext::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FWorldContext::BitfieldInfos{};

FName& FWorldContext::GetContextHandle()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ContextHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::ContextHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& FWorldContext::GetContextHandle() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ContextHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::ContextHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

FString& FWorldContext::GetTravelURL()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TravelURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::TravelURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& FWorldContext::GetTravelURL() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TravelURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::TravelURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

uint8& FWorldContext::GetTravelType()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TravelType"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::TravelType' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint8*>(this, offset);
}
const uint8& FWorldContext::GetTravelType() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TravelType"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::TravelType' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint8*>(this, offset);
}

FURL& FWorldContext::GetLastURL()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::LastURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FURL*>(this, offset);
}
const FURL& FWorldContext::GetLastURL() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::LastURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FURL*>(this, offset);
}

FURL& FWorldContext::GetLastRemoteURL()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRemoteURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::LastRemoteURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FURL*>(this, offset);
}
const FURL& FWorldContext::GetLastRemoteURL() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRemoteURL"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::LastRemoteURL' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FURL*>(this, offset);
}

TArray<FName,TSizedDefaultAllocator<32> >& FWorldContext::GetLevelsToLoadForPendingMapChange()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LevelsToLoadForPendingMapChange"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::LevelsToLoadForPendingMapChange' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FName,TSizedDefaultAllocator<32> >& FWorldContext::GetLevelsToLoadForPendingMapChange() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LevelsToLoadForPendingMapChange"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::LevelsToLoadForPendingMapChange' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}

FString& FWorldContext::GetPendingMapChangeFailureDescription()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PendingMapChangeFailureDescription"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PendingMapChangeFailureDescription' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& FWorldContext::GetPendingMapChangeFailureDescription() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PendingMapChangeFailureDescription"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PendingMapChangeFailureDescription' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

BitfieldProxy FWorldContext::GetbShouldCommitPendingMapChange()
{
    static auto offset_it = MemberOffsets.find(STR("bShouldCommitPendingMapChange"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::bShouldCommitPendingMapChange' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldCommitPendingMapChange"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FWorldContext::bShouldCommitPendingMapChange'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FWorldContext::GetbShouldCommitPendingMapChange() const
{
    static auto offset_it = MemberOffsets.find(STR("bShouldCommitPendingMapChange"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::bShouldCommitPendingMapChange' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bShouldCommitPendingMapChange"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FWorldContext::bShouldCommitPendingMapChange'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TObjectPtr<UGameViewportClient>& FWorldContext::GetGameViewport()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameViewport"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::GameViewport' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UGameViewportClient>*>(this, offset);
}
const TObjectPtr<UGameViewportClient>& FWorldContext::GetGameViewport() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameViewport"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::GameViewport' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UGameViewportClient>*>(this, offset);
}

int32& FWorldContext::GetPIEInstance()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEInstance"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEInstance' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FWorldContext::GetPIEInstance() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEInstance"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEInstance' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

FString& FWorldContext::GetPIEPrefix()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEPrefix"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEPrefix' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& FWorldContext::GetPIEPrefix() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEPrefix"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEPrefix' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

FString& FWorldContext::GetPIERemapPrefix()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIERemapPrefix"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIERemapPrefix' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& FWorldContext::GetPIERemapPrefix() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIERemapPrefix"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIERemapPrefix' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

bool& FWorldContext::GetRunAsDedicated()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RunAsDedicated"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::RunAsDedicated' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FWorldContext::GetRunAsDedicated() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RunAsDedicated"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::RunAsDedicated' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

bool& FWorldContext::GetbWaitingOnOnlineSubsystem()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bWaitingOnOnlineSubsystem"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::bWaitingOnOnlineSubsystem' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FWorldContext::GetbWaitingOnOnlineSubsystem() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bWaitingOnOnlineSubsystem"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::bWaitingOnOnlineSubsystem' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

uint32& FWorldContext::GetAudioDeviceHandle()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::AudioDeviceHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FWorldContext::GetAudioDeviceHandle() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceHandle"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::AudioDeviceHandle' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

TArray<TObjectPtr<UWorld> *,TSizedDefaultAllocator<32> >& FWorldContext::GetExternalReferences()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ExternalReferences"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::ExternalReferences' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TObjectPtr<UWorld> *,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<TObjectPtr<UWorld> *,TSizedDefaultAllocator<32> >& FWorldContext::GetExternalReferences() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ExternalReferences"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::ExternalReferences' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TObjectPtr<UWorld> *,TSizedDefaultAllocator<32> >*>(this, offset);
}

TObjectPtr<UWorld>& FWorldContext::GetThisCurrentWorld()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ThisCurrentWorld"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::ThisCurrentWorld' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UWorld>*>(this, offset);
}
const TObjectPtr<UWorld>& FWorldContext::GetThisCurrentWorld() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ThisCurrentWorld"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::ThisCurrentWorld' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UWorld>*>(this, offset);
}

FString& FWorldContext::GetCustomDescription()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CustomDescription"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::CustomDescription' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& FWorldContext::GetCustomDescription() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CustomDescription"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::CustomDescription' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

uint32& FWorldContext::GetAudioDeviceID()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceID"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::AudioDeviceID' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FWorldContext::GetAudioDeviceID() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AudioDeviceID"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::AudioDeviceID' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

float& FWorldContext::GetPIEFixedTickSeconds()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEFixedTickSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEFixedTickSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& FWorldContext::GetPIEFixedTickSeconds() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEFixedTickSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEFixedTickSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

float& FWorldContext::GetPIEAccumulatedTickSeconds()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEAccumulatedTickSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEAccumulatedTickSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& FWorldContext::GetPIEAccumulatedTickSeconds() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PIEAccumulatedTickSeconds"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::PIEAccumulatedTickSeconds' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

bool& FWorldContext::GetbIsPrimaryPIEInstance()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIsPrimaryPIEInstance"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::bIsPrimaryPIEInstance' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FWorldContext::GetbIsPrimaryPIEInstance() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bIsPrimaryPIEInstance"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::bIsPrimaryPIEInstance' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

TSet<FObjectKey,DefaultKeyFuncs<FObjectKey,0>,FDefaultSetAllocator>& FWorldContext::GetGarbageObjectsToVerify()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GarbageObjectsToVerify"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::GarbageObjectsToVerify' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSet<FObjectKey,DefaultKeyFuncs<FObjectKey,0>,FDefaultSetAllocator>*>(this, offset);
}
const TSet<FObjectKey,DefaultKeyFuncs<FObjectKey,0>,FDefaultSetAllocator>& FWorldContext::GetGarbageObjectsToVerify() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GarbageObjectsToVerify"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FWorldContext::GarbageObjectsToVerify' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSet<FObjectKey,DefaultKeyFuncs<FObjectKey,0>,FDefaultSetAllocator>*>(this, offset);
}

int32_t& FWorldContext::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

