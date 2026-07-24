static std::unordered_map<File::StringType, int32_t> MemberOffsets;

public:
    TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& GetAutoComplete();
    const TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& GetAutoComplete() const;

public:
    int32& GetAutoCompleteCursor();
    const int32& GetAutoCompleteCursor() const;

public:
    int32& GetAutoCompleteIndex();
    const int32& GetAutoCompleteIndex() const;

public:
    TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& GetAutoCompleteList();
    const TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& GetAutoCompleteList() const;

public:
    FAutoCompleteNode& GetAutoCompleteTree();
    const FAutoCompleteNode& GetAutoCompleteTree() const;

public:
    UConsoleSettings*& GetConsoleSettings();
    const UConsoleSettings*& GetConsoleSettings() const;

public:
    FName& GetConsoleState();
    const FName& GetConsoleState() const;

public:
    TObjectPtr<ULocalPlayer>& GetConsoleTargetPlayer();
    const TObjectPtr<ULocalPlayer>& GetConsoleTargetPlayer() const;

public:
    TObjectPtr<UTexture2D>& GetDefaultTexture_Black();
    const TObjectPtr<UTexture2D>& GetDefaultTexture_Black() const;

public:
    TObjectPtr<UTexture2D>& GetDefaultTexture_White();
    const TObjectPtr<UTexture2D>& GetDefaultTexture_White() const;

public:
    TArray<FString,TSizedDefaultAllocator<32> >& GetHistoryBuffer();
    const TArray<FString,TSizedDefaultAllocator<32> >& GetHistoryBuffer() const;

public:
    FString& GetLastAutoCompletedCommand();
    const FString& GetLastAutoCompletedCommand() const;

public:
    FString& GetPrecompletedInputLine();
    const FString& GetPrecompletedInputLine() const;

public:
    TWeakPtr<SWidget,1>& GetPreviousFocusedWidget();
    const TWeakPtr<SWidget,1>& GetPreviousFocusedWidget() const;

public:
    int32& GetSBHead();
    const int32& GetSBHead() const;

public:
    int32& GetSBPos();
    const int32& GetSBPos() const;

public:
    TArray<FString,TSizedDefaultAllocator<32> >& GetScrollback();
    const TArray<FString,TSizedDefaultAllocator<32> >& GetScrollback() const;

public:
    FString& GetTypedStr();
    const FString& GetTypedStr() const;

public:
    int32& GetTypedStrPos();
    const int32& GetTypedStrPos() const;

public:
    uint32& GetbAutoCompleteLocked();
    const uint32& GetbAutoCompleteLocked() const;

public:
    uint32& GetbCaptureKeyInput();
    const uint32& GetbCaptureKeyInput() const;

public:
    uint32& GetbCtrl();
    const uint32& GetbCtrl() const;

public:
    uint32& GetbIsRuntimeAutoCompleteUpToDate();
    const uint32& GetbIsRuntimeAutoCompleteUpToDate() const;

public:
    uint32& GetbShift();
    const uint32& GetbShift() const;

