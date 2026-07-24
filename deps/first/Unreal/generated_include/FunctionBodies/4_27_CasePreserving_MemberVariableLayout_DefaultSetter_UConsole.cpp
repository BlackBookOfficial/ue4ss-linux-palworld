if (auto it = UConsole::MemberOffsets.find(STR("AutoComplete")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoComplete"), 0x118);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteCursor")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteCursor"), 0xD8);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteIndex")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteIndex"), 0xD4);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteList")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteList"), 0xC0);
}

if (auto it = UConsole::MemberOffsets.find(STR("AutoCompleteTree")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("AutoCompleteTree"), 0xF0);
}

if (auto it = UConsole::MemberOffsets.find(STR("ConsoleSettings")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("ConsoleSettings"), 0x128);
}

if (auto it = UConsole::MemberOffsets.find(STR("ConsoleState")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("ConsoleState"), 0xE0);
}

if (auto it = UConsole::MemberOffsets.find(STR("ConsoleTargetPlayer")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("ConsoleTargetPlayer"), 0x40);
}

if (auto it = UConsole::MemberOffsets.find(STR("DefaultTexture_Black")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("DefaultTexture_Black"), 0x48);
}

if (auto it = UConsole::MemberOffsets.find(STR("DefaultTexture_White")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("DefaultTexture_White"), 0x50);
}

if (auto it = UConsole::MemberOffsets.find(STR("HistoryBuffer")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("HistoryBuffer"), 0x70);
}

if (auto it = UConsole::MemberOffsets.find(STR("LastAutoCompletedCommand")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("LastAutoCompletedCommand"), 0xA8);
}

if (auto it = UConsole::MemberOffsets.find(STR("PrecompletedInputLine")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("PrecompletedInputLine"), 0x98);
}

if (auto it = UConsole::MemberOffsets.find(STR("PreviousFocusedWidget")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("PreviousFocusedWidget"), 0x130);
}

if (auto it = UConsole::MemberOffsets.find(STR("SBHead")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("SBHead"), 0x68);
}

if (auto it = UConsole::MemberOffsets.find(STR("SBPos")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("SBPos"), 0x6C);
}

if (auto it = UConsole::MemberOffsets.find(STR("Scrollback")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("Scrollback"), 0x58);
}

if (auto it = UConsole::MemberOffsets.find(STR("TypedStr")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("TypedStr"), 0x80);
}

if (auto it = UConsole::MemberOffsets.find(STR("TypedStrPos")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("TypedStrPos"), 0x90);
}

if (auto it = UConsole::MemberOffsets.find(STR("bAutoCompleteLocked")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bAutoCompleteLocked"), 0xD0);
}

if (auto it = UConsole::MemberOffsets.find(STR("bCaptureKeyInput")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bCaptureKeyInput"), 0xB8);
}

if (auto it = UConsole::MemberOffsets.find(STR("bCtrl")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bCtrl"), 0xB8);
}

if (auto it = UConsole::MemberOffsets.find(STR("bIsRuntimeAutoCompleteUpToDate")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bIsRuntimeAutoCompleteUpToDate"), 0xDC);
}

if (auto it = UConsole::MemberOffsets.find(STR("bShift")); it == UConsole::MemberOffsets.end())
{
    UConsole::MemberOffsets.emplace(STR("bShift"), 0xB8);
}

