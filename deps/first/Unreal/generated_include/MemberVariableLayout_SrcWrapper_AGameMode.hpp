std::unordered_map<File::StringType, int32_t> AGameMode::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> AGameMode::BitfieldInfos{};

FName& AGameMode::GetMatchState()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MatchState"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::MatchState' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& AGameMode::GetMatchState() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MatchState"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::MatchState' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

BitfieldProxy AGameMode::GetbUseSeamlessTravel()
{
    static auto offset_it = MemberOffsets.find(STR("bUseSeamlessTravel"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bUseSeamlessTravel' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bUseSeamlessTravel"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bUseSeamlessTravel'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameMode::GetbUseSeamlessTravel() const
{
    static auto offset_it = MemberOffsets.find(STR("bUseSeamlessTravel"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bUseSeamlessTravel' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bUseSeamlessTravel"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bUseSeamlessTravel'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AGameMode::GetbPauseable()
{
    static auto offset_it = MemberOffsets.find(STR("bPauseable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bPauseable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPauseable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bPauseable'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameMode::GetbPauseable() const
{
    static auto offset_it = MemberOffsets.find(STR("bPauseable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bPauseable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPauseable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bPauseable'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AGameMode::GetbStartPlayersAsSpectators()
{
    static auto offset_it = MemberOffsets.find(STR("bStartPlayersAsSpectators"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bStartPlayersAsSpectators' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStartPlayersAsSpectators"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bStartPlayersAsSpectators'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameMode::GetbStartPlayersAsSpectators() const
{
    static auto offset_it = MemberOffsets.find(STR("bStartPlayersAsSpectators"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bStartPlayersAsSpectators' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStartPlayersAsSpectators"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bStartPlayersAsSpectators'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AGameMode::GetbDelayedStart()
{
    static auto offset_it = MemberOffsets.find(STR("bDelayedStart"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bDelayedStart' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDelayedStart"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bDelayedStart'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AGameMode::GetbDelayedStart() const
{
    static auto offset_it = MemberOffsets.find(STR("bDelayedStart"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bDelayedStart' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bDelayedStart"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AGameMode::bDelayedStart'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FString& AGameMode::GetOptionsString()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OptionsString"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::OptionsString' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& AGameMode::GetOptionsString() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OptionsString"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::OptionsString' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

TSubclassOf<AHUD>& AGameMode::GetHUDClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HUDClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::HUDClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<AHUD>*>(this, offset);
}
const TSubclassOf<AHUD>& AGameMode::GetHUDClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HUDClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::HUDClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<AHUD>*>(this, offset);
}

int32& AGameMode::GetNumSpectators()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumSpectators"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumSpectators' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AGameMode::GetNumSpectators() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumSpectators"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumSpectators' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& AGameMode::GetNumPlayers()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumPlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumPlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AGameMode::GetNumPlayers() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumPlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumPlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& AGameMode::GetNumBots()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumBots"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumBots' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AGameMode::GetNumBots() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumBots"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumBots' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

float& AGameMode::GetMinRespawnDelay()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MinRespawnDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::MinRespawnDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AGameMode::GetMinRespawnDelay() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MinRespawnDelay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::MinRespawnDelay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

AGameSession*& AGameMode::GetGameSession()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameSession"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::GameSession' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<AGameSession**>(this, offset);
}
const AGameSession*& AGameMode::GetGameSession() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameSession"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::GameSession' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const AGameSession**>(this, offset);
}

int32& AGameMode::GetNumTravellingPlayers()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumTravellingPlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumTravellingPlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AGameMode::GetNumTravellingPlayers() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumTravellingPlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::NumTravellingPlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& AGameMode::GetCurrentID()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentID"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::CurrentID' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AGameMode::GetCurrentID() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CurrentID"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::CurrentID' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

FText& AGameMode::GetDefaultPlayerName()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DefaultPlayerName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::DefaultPlayerName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FText*>(this, offset);
}
const FText& AGameMode::GetDefaultPlayerName() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DefaultPlayerName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::DefaultPlayerName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FText*>(this, offset);
}

TSubclassOf<ULocalMessage>& AGameMode::GetEngineMessageClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EngineMessageClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::EngineMessageClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<ULocalMessage>*>(this, offset);
}
const TSubclassOf<ULocalMessage>& AGameMode::GetEngineMessageClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EngineMessageClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::EngineMessageClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<ULocalMessage>*>(this, offset);
}

TSubclassOf<ASpectatorPawn>& AGameMode::GetSpectatorClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SpectatorClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::SpectatorClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<ASpectatorPawn>*>(this, offset);
}
const TSubclassOf<ASpectatorPawn>& AGameMode::GetSpectatorClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SpectatorClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::SpectatorClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<ASpectatorPawn>*>(this, offset);
}

TSubclassOf<APlayerState>& AGameMode::GetPlayerStateClass()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PlayerStateClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::PlayerStateClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TSubclassOf<APlayerState>*>(this, offset);
}
const TSubclassOf<APlayerState>& AGameMode::GetPlayerStateClass() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PlayerStateClass"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::PlayerStateClass' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TSubclassOf<APlayerState>*>(this, offset);
}

TArray<TObjectPtr<APlayerState>,TSizedDefaultAllocator<32> >& AGameMode::GetInactivePlayerArray()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InactivePlayerArray"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::InactivePlayerArray' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TObjectPtr<APlayerState>,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<TObjectPtr<APlayerState>,TSizedDefaultAllocator<32> >& AGameMode::GetInactivePlayerArray() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InactivePlayerArray"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::InactivePlayerArray' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TObjectPtr<APlayerState>,TSizedDefaultAllocator<32> >*>(this, offset);
}

TArray<FGameClassShortName,FDefaultAllocator>& AGameMode::GetGameModeClassAliases()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameModeClassAliases"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::GameModeClassAliases' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FGameClassShortName,FDefaultAllocator>*>(this, offset);
}
const TArray<FGameClassShortName,FDefaultAllocator>& AGameMode::GetGameModeClassAliases() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("GameModeClassAliases"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::GameModeClassAliases' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FGameClassShortName,FDefaultAllocator>*>(this, offset);
}

float& AGameMode::GetInactivePlayerStateLifeSpan()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InactivePlayerStateLifeSpan"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::InactivePlayerStateLifeSpan' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AGameMode::GetInactivePlayerStateLifeSpan() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InactivePlayerStateLifeSpan"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::InactivePlayerStateLifeSpan' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

bool& AGameMode::GetbHandleDedicatedServerReplays()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHandleDedicatedServerReplays"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bHandleDedicatedServerReplays' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& AGameMode::GetbHandleDedicatedServerReplays() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bHandleDedicatedServerReplays"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::bHandleDedicatedServerReplays' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

int32& AGameMode::GetMaxInactivePlayers()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxInactivePlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::MaxInactivePlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AGameMode::GetMaxInactivePlayers() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MaxInactivePlayers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AGameMode::MaxInactivePlayers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32_t& AGameMode::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

