static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    FString& GetOptionsString();
    const FString& GetOptionsString() const;

public:
    TSubclassOf<AGameSession>& GetGameSessionClass();
    const TSubclassOf<AGameSession>& GetGameSessionClass() const;

public:
    TSubclassOf<APlayerState>& GetPlayerStateClass();
    const TSubclassOf<APlayerState>& GetPlayerStateClass() const;

public:
    TSubclassOf<AHUD>& GetHUDClass();
    const TSubclassOf<AHUD>& GetHUDClass() const;

public:
    TSubclassOf<ASpectatorPawn>& GetSpectatorClass();
    const TSubclassOf<ASpectatorPawn>& GetSpectatorClass() const;

public:
    TObjectPtr<AGameSession>& GetGameSession();
    const TObjectPtr<AGameSession>& GetGameSession() const;

public:
    FText& GetDefaultPlayerName();
    const FText& GetDefaultPlayerName() const;

public:
    BitfieldProxy GetbUseSeamlessTravel();
    ConstBitfieldProxy GetbUseSeamlessTravel() const;

public:
    BitfieldProxy GetbStartPlayersAsSpectators();
    ConstBitfieldProxy GetbStartPlayersAsSpectators() const;

public:
    BitfieldProxy GetbPauseable();
    ConstBitfieldProxy GetbPauseable() const;

public:
    TSubclassOf<AServerStatReplicator>& GetServerStatReplicatorClass();
    const TSubclassOf<AServerStatReplicator>& GetServerStatReplicatorClass() const;

public:
    TObjectPtr<AServerStatReplicator>& GetServerStatReplicator();
    const TObjectPtr<AServerStatReplicator>& GetServerStatReplicator() const;

public:
    EReplicationSystem& GetGameNetDriverReplicationSystem();
    const EReplicationSystem& GetGameNetDriverReplicationSystem() const;

public:
    static int32_t& UEP_TotalSize();
