static std::unordered_map<File::StringType, int32_t> MemberOffsets;

public:
    TMap<FString, IConsoleObject *>& GetConsoleObjects();
    const TMap<FString, IConsoleObject *>& GetConsoleObjects() const;

public:
    TArray<FString,FDefaultAllocator>& GetHistoryEntries();
    const TArray<FString,FDefaultAllocator>& GetHistoryEntries() const;

public:
    TMap<FString, TArray<FString,TSizedDefaultAllocator<32> >>& GetHistoryEntriesMap();
    const TMap<FString, TArray<FString,TSizedDefaultAllocator<32> >>& GetHistoryEntriesMap() const;

public:
    IConsoleThreadPropagation*& GetThreadPropagationCallback();
    const IConsoleThreadPropagation*& GetThreadPropagationCallback() const;

public:
    uint32& GetThreadPropagationThreadId();
    const uint32& GetThreadPropagationThreadId() const;

public:
    bool& GetbCallAllConsoleVariableSinks();
    const bool& GetbCallAllConsoleVariableSinks() const;

public:
    bool& GetbHistoryWasLoaded();
    const bool& GetbHistoryWasLoaded() const;

