std::unordered_map<File::StringType, int32_t> FConsoleManager::MemberOffsets{};

TMap<FString, IConsoleObject *>& FConsoleManager::GetConsoleObjects()
{
    static auto offset = MemberOffsets.find(STR("ConsoleObjects"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::ConsoleObjects' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TMap<FString, IConsoleObject *>*>(this, offset->second);
}
const TMap<FString, IConsoleObject *>& FConsoleManager::GetConsoleObjects() const
{
    static auto offset = MemberOffsets.find(STR("ConsoleObjects"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::ConsoleObjects' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TMap<FString, IConsoleObject *>*>(this, offset->second);
}

TArray<FString,FDefaultAllocator>& FConsoleManager::GetHistoryEntries()
{
    static auto offset = MemberOffsets.find(STR("HistoryEntries"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::HistoryEntries' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TArray<FString,FDefaultAllocator>*>(this, offset->second);
}
const TArray<FString,FDefaultAllocator>& FConsoleManager::GetHistoryEntries() const
{
    static auto offset = MemberOffsets.find(STR("HistoryEntries"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::HistoryEntries' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TArray<FString,FDefaultAllocator>*>(this, offset->second);
}

TMap<FString, TArray<FString,TSizedDefaultAllocator<32> >>& FConsoleManager::GetHistoryEntriesMap()
{
    static auto offset = MemberOffsets.find(STR("HistoryEntriesMap"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::HistoryEntriesMap' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TMap<FString, TArray<FString,TSizedDefaultAllocator<32> >>*>(this, offset->second);
}
const TMap<FString, TArray<FString,TSizedDefaultAllocator<32> >>& FConsoleManager::GetHistoryEntriesMap() const
{
    static auto offset = MemberOffsets.find(STR("HistoryEntriesMap"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::HistoryEntriesMap' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TMap<FString, TArray<FString,TSizedDefaultAllocator<32> >>*>(this, offset->second);
}

IConsoleThreadPropagation*& FConsoleManager::GetThreadPropagationCallback()
{
    static auto offset = MemberOffsets.find(STR("ThreadPropagationCallback"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::ThreadPropagationCallback' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<IConsoleThreadPropagation**>(this, offset->second);
}
const IConsoleThreadPropagation*& FConsoleManager::GetThreadPropagationCallback() const
{
    static auto offset = MemberOffsets.find(STR("ThreadPropagationCallback"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::ThreadPropagationCallback' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const IConsoleThreadPropagation**>(this, offset->second);
}

uint32& FConsoleManager::GetThreadPropagationThreadId()
{
    static auto offset = MemberOffsets.find(STR("ThreadPropagationThreadId"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::ThreadPropagationThreadId' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<uint32*>(this, offset->second);
}
const uint32& FConsoleManager::GetThreadPropagationThreadId() const
{
    static auto offset = MemberOffsets.find(STR("ThreadPropagationThreadId"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::ThreadPropagationThreadId' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset->second);
}

bool& FConsoleManager::GetbCallAllConsoleVariableSinks()
{
    static auto offset = MemberOffsets.find(STR("bCallAllConsoleVariableSinks"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::bCallAllConsoleVariableSinks' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<bool*>(this, offset->second);
}
const bool& FConsoleManager::GetbCallAllConsoleVariableSinks() const
{
    static auto offset = MemberOffsets.find(STR("bCallAllConsoleVariableSinks"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::bCallAllConsoleVariableSinks' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const bool*>(this, offset->second);
}

bool& FConsoleManager::GetbHistoryWasLoaded()
{
    static auto offset = MemberOffsets.find(STR("bHistoryWasLoaded"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::bHistoryWasLoaded' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<bool*>(this, offset->second);
}
const bool& FConsoleManager::GetbHistoryWasLoaded() const
{
    static auto offset = MemberOffsets.find(STR("bHistoryWasLoaded"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleManager::bHistoryWasLoaded' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const bool*>(this, offset->second);
}

