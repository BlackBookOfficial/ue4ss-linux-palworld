static std::unordered_map<File::StringType, int32_t> MemberOffsets;
static std::unordered_map<File::StringType, BitfieldInfo> BitfieldInfos;

public:
    TObjectPtr<UGameViewportClient>& GetViewportClient();
    const TObjectPtr<UGameViewportClient>& GetViewportClient() const;

public:
    FVector& GetLastViewLocation();
    const FVector& GetLastViewLocation() const;

public:
    TEnumAsByte<enum EAspectRatioAxisConstraint>& GetAspectRatioAxisConstraint();
    const TEnumAsByte<enum EAspectRatioAxisConstraint>& GetAspectRatioAxisConstraint() const;

public:
    BitfieldProxy GetbSentSplitJoin();
    ConstBitfieldProxy GetbSentSplitJoin() const;

public:
    int32& GetControllerId();
    const int32& GetControllerId() const;

public:
    bool& GetbEmulateSplitscreen();
    const bool& GetbEmulateSplitscreen() const;

public:
    int32& GetConnectionIdentifier();
    const int32& GetConnectionIdentifier() const;

public:
    static int32_t& UEP_TotalSize();
