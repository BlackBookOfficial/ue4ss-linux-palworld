if (auto it = FConsoleManager::MemberOffsets.find(STR("ConsoleObjects")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ConsoleObjects"), 0x8);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("ConsoleVariableChangeSinks")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ConsoleVariableChangeSinks"), 0xB0);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("HistoryEntriesMap")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("HistoryEntriesMap"), 0x60);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("ThreadPropagationCallback")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ThreadPropagationCallback"), 0xC0);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("ThreadPropagationThreadId")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ThreadPropagationThreadId"), 0xC8);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("bCallAllConsoleVariableSinks")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("bCallAllConsoleVariableSinks"), 0xCC);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("bHistoryWasLoaded")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("bHistoryWasLoaded"), 0x58);
}

