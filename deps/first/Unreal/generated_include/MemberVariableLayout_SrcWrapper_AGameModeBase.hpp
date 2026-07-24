std::unordered_map<File::StringType, int32_t> AGameModeBase::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> AGameModeBase::BitfieldInfos{};

FString& AGameModeBase::GetOptionsString()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OptionsString"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::OptionsString' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& AGameModeBase::GetOptionsString() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OptionsString"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::OptionsString' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

TSubclassOf<AGameSession>& AGameModeBase::GetGameSessionClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameSessionClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::GameSessionClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<AGameSession>*>(this, offset);
}
const TSubclassOf<AGameSession>& AGameModeBase::GetGameSessionClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameSessionClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::GameSessionClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<AGameSession>*>(this, offset);
}

TSubclassOf<APlayerState>& AGameModeBase::GetPlayerStateClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PlayerStateClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::PlayerStateClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<APlayerState>*>(this, offset);
}
const TSubclassOf<APlayerState>& AGameModeBase::GetPlayerStateClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PlayerStateClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::PlayerStateClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<APlayerState>*>(this, offset);
}

TSubclassOf<AHUD>& AGameModeBase::GetHUDClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HUDClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::HUDClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<AHUD>*>(this, offset);
}
const TSubclassOf<AHUD>& AGameModeBase::GetHUDClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HUDClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::HUDClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<AHUD>*>(this, offset);
}

TSubclassOf<ASpectatorPawn>& AGameModeBase::GetSpectatorClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SpectatorClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::SpectatorClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<ASpectatorPawn>*>(this, offset);
}
const TSubclassOf<ASpectatorPawn>& AGameModeBase::GetSpectatorClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SpectatorClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::SpectatorClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<ASpectatorPawn>*>(this, offset);
}

TObjectPtr<AGameSession>& AGameModeBase::GetGameSession()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameSession"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::GameSession' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<AGameSession>*>(this, offset);
}
const TObjectPtr<AGameSession>& AGameModeBase::GetGameSession() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameSession"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::GameSession' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<AGameSession>*>(this, offset);
}

FText& AGameModeBase::GetDefaultPlayerName()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DefaultPlayerName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::DefaultPlayerName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FText*>(this, offset);
}
const FText& AGameModeBase::GetDefaultPlayerName() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DefaultPlayerName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::DefaultPlayerName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FText*>(this, offset);
}

BitfieldProxy AGameModeBase::GetbUseSeamlessTravel()
{
    static auto offset_it = MemberOffsets.find(STR("bUseSeamlessTravel"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::bUseSeamlessTravel' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bUseSeamlessTravel"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameModeBase::bUseSeamlessTravel'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameModeBase::GetbUseSeamlessTravel() const
{
    static auto offset_it = MemberOffsets.find(STR("bUseSeamlessTravel"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::bUseSeamlessTravel' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bUseSeamlessTravel"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameModeBase::bUseSeamlessTravel'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AGameModeBase::GetbStartPlayersAsSpectators()
{
    static auto offset_it = MemberOffsets.find(STR("bStartPlayersAsSpectators"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::bStartPlayersAsSpectators' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStartPlayersAsSpectators"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameModeBase::bStartPlayersAsSpectators'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameModeBase::GetbStartPlayersAsSpectators() const
{
    static auto offset_it = MemberOffsets.find(STR("bStartPlayersAsSpectators"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::bStartPlayersAsSpectators' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStartPlayersAsSpectators"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameModeBase::bStartPlayersAsSpectators'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AGameModeBase::GetbPauseable()
{
    static auto offset_it = MemberOffsets.find(STR("bPauseable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::bPauseable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPauseable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameModeBase::bPauseable'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameModeBase::GetbPauseable() const
{
    static auto offset_it = MemberOffsets.find(STR("bPauseable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::bPauseable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPauseable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameModeBase::bPauseable'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TSubclassOf<AServerStatReplicator>& AGameModeBase::GetServerStatReplicatorClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ServerStatReplicatorClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::ServerStatReplicatorClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<AServerStatReplicator>*>(this, offset);
}
const TSubclassOf<AServerStatReplicator>& AGameModeBase::GetServerStatReplicatorClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ServerStatReplicatorClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::ServerStatReplicatorClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<AServerStatReplicator>*>(this, offset);
}

TObjectPtr<AServerStatReplicator>& AGameModeBase::GetServerStatReplicator()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ServerStatReplicator"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::ServerStatReplicator' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<AServerStatReplicator>*>(this, offset);
}
const TObjectPtr<AServerStatReplicator>& AGameModeBase::GetServerStatReplicator() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ServerStatReplicator"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::ServerStatReplicator' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<AServerStatReplicator>*>(this, offset);
}

EReplicationSystem& AGameModeBase::GetGameNetDriverReplicationSystem()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameNetDriverReplicationSystem"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::GameNetDriverReplicationSystem' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EReplicationSystem*>(this, offset);
}
const EReplicationSystem& AGameModeBase::GetGameNetDriverReplicationSystem() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameNetDriverReplicationSystem"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameModeBase::GameNetDriverReplicationSystem' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EReplicationSystem*>(this, offset);
}

int32_t& AGameModeBase::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

