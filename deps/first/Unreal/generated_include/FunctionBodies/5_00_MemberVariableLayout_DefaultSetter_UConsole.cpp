if (auto it = UConsole::MemberOffsets.find(STR("AutoComplete")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoComplete"), 0x108);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteCursor")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteCursor"), 0xD0);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteIndex")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteIndex"), 0xCC);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteList")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteList"), 0xB8);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteTree")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteTree"), 0xE0);
}

if (auto it = UConsole::MemberOffsets.find(STR("ConsoleSettings")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("ConsoleSettings"), 0x118);
}

if (auto it = UConsole::MemberOffsets.find(STR("ConsoleState")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("ConsoleState"), 0xD8);
}

if (auto it = UConsole::MemberOffsets.find(STR("ConsoleTargetPlayer")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("ConsoleTargetPlayer"), 0x38);
}

if (auto it = UConsole::MemberOffsets.find(STR("DefaultTexture_Black")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("DefaultTexture_Black"), 0x40);
}

if (auto it = UConsole::MemberOffsets.find(STR("DefaultTexture_White")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("DefaultTexture_White"), 0x48);
}

if (auto it = UConsole::MemberOffsets.find(STR("HistoryBuffer")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("HistoryBuffer"), 0x68);
}

if (auto it = UConsole::MemberOffsets.find(STR("LastAutoCompletedCommand")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("LastAutoCompletedCommand"), 0xA0);
}

if (auto it = UConsole::MemberOffsets.find(STR("PrecompletedInputLine")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("PrecompletedInputLine"), 0x90);
}

if (auto it = UConsole::MemberOffsets.find(STR("PreviousFocusedWidget")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("PreviousFocusedWidget"), 0x120);
}

if (auto it = UConsole::MemberOffsets.find(STR("SBHead")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("SBHead"), 0x60);
}

if (auto it = UConsole::MemberOffsets.find(STR("SBPos")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("SBPos"), 0x64);
}

if (auto it = UConsole::MemberOffsets.find(STR("Scrollback")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("Scrollback"), 0x50);
}

if (auto it = UConsole::MemberOffsets.find(STR("TypedStr")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("TypedStr"), 0x78);
}

if (auto it = UConsole::MemberOffsets.find(STR("TypedStrPos")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("TypedStrPos"), 0x88);
}

if (auto it = UConsole::MemberOffsets.find(STR("bAutoCompleteLocked")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bAutoCompleteLocked"), 0xC8);
}

if (auto it = UConsole::MemberOffsets.find(STR("bCaptureKeyInput")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bCaptureKeyInput"), 0xB0);
}

if (auto it = UConsole::MemberOffsets.find(STR("bCtrl")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bCtrl"), 0xB0);
}

if (auto it = UConsole::MemberOffsets.find(STR("bIsRuntimeAutoCompleteUpToDate")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bIsRuntimeAutoCompleteUpToDate"), 0xD4);
}

if (auto it = UConsole::MemberOffsets.find(STR("bShift")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bShift"), 0xB0);
}

