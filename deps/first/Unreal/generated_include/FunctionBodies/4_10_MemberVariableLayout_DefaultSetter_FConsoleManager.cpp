if (auto it = FConsoleManager::MemberOffsets.find(STR("ConsoleObjects")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ConsoleObjects"), 0x8);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("ConsoleVariableChangeSinks")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ConsoleVariableChangeSinks"), 0x70);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("HistoryEntries")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("HistoryEntries"), 0x58);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("ThreadPropagationCallback")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ThreadPropagationCallback"), 0x80);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("ThreadPropagationThreadId")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("ThreadPropagationThreadId"), 0x88);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("bCallAllConsoleVariableSinks")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("bCallAllConsoleVariableSinks"), 0x8C);
}

if (auto it = FConsoleManager::MemberOffsets.find(STR("bHistoryWasLoaded")); it == FConsoleManager::MemberOffsets.end())
{
    FConsoleManager::MemberOffsets.emplace(STR("bHistoryWasLoaded"), 0x68);
}

