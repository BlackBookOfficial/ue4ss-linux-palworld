static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FName& GetMatchState();
    const FName& GetMatchState() const;

public:
    BitfieldProxy GetbUseSeamlessTravel();
    ConstBitfieldProxy GetbUseSeamlessTravel() const;

public:
    BitfieldProxy GetbPauseable();
    ConstBitfieldProxy GetbPauseable() const;

public:
    BitfieldProxy GetbStartPlayersAsSpectators();
    ConstBitfieldProxy GetbStartPlayersAsSpectators() const;

public:
    BitfieldProxy GetbDelayedStart();
    ConstBitfieldProxy GetbDelayedStart() const;

public:
    FString& GetOptionsString();
    const FString& GetOptionsString() const;

public:
    TSubclassOf<AHUD>& GetHUDClass();
    const TSubclassOf<AHUD>& GetHUDClass() const;

public:
    int32& GetNumSpectators();
    const int32& GetNumSpectators() const;

public:
    int32& GetNumPlayers();
    const int32& GetNumPlayers() const;

public:
    int32& GetNumBots();
    const int32& GetNumBots() const;

public:
    float& GetMinRespawnDelay();
    const float& GetMinRespawnDelay() const;

public:
    AGameSession*& GetGameSession();
    const AGameSession*& GetGameSession() const;

public:
    int32& GetNumTravellingPlayers();
    const int32& GetNumTravellingPlayers() const;

public:
    int32& GetCurrentID();
    const int32& GetCurrentID() const;

public:
    FText& GetDefaultPlayerName();
    const FText& GetDefaultPlayerName() const;

public:
    TSubclassOf<ULocalMessage>& GetEngineMessageClass();
    const TSubclassOf<ULocalMessage>& GetEngineMessageClass() const;

public:
    TSubclassOf<ASpectatorPawn>& GetSpectatorClass();
    const TSubclassOf<ASpectatorPawn>& GetSpectatorClass() const;

public:
    TSubclassOf<APlayerState>& GetPlayerStateClass();
    const TSubclassOf<APlayerState>& GetPlayerStateClass() const;

public:
    TArray<TObjectPtr<APlayerState>,TSizedDefaultAllocator<32> >& GetInactivePlayerArray();
    const TArray<TObjectPtr<APlayerState>,TSizedDefaultAllocator<32> >& GetInactivePlayerArray() const;

public:
    TArray<FGameClassShortName,FDefaultAllocator>& GetGameModeClassAliases();
    const TArray<FGameClassShortName,FDefaultAllocator>& GetGameModeClassAliases() const;

public:
    float& GetInactivePlayerStateLifeSpan();
    const float& GetInactivePlayerStateLifeSpan() const;

public:
    bool& GetbHandleDedicatedServerReplays();
    const bool& GetbHandleDedicatedServerReplays() const;

public:
    int32& GetMaxInactivePlayers();
    const int32& GetMaxInactivePlayers() const;

public:
    static int32_t& UEP_TotalSize();
