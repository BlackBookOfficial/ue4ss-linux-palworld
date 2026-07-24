if (auto it = UConsole::VTableLayoutMap.find(STR("__vecDelDtor")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("SetInputText")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("SetInputText"), 0x208);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("SetCursorPos")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("SetCursorPos"), 0x210);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ConsoleCommand")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ConsoleCommand"), 0x218);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ClearOutput")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ClearOutput"), 0x220);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("OutputText")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("OutputText"), 0x228);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("StartTyping")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("StartTyping"), 0x230);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("FlushPlayerInput")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("FlushPlayerInput"), 0x238);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ProcessControlKey")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ProcessControlKey"), 0x240);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("AppendInputText")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("AppendInputText"), 0x248);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("BuildRuntimeAutoCompleteList")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("BuildRuntimeAutoCompleteList"), 0x250);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("UpdateCompleteIndices")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("UpdateCompleteIndices"), 0x258);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_Typing"), 0x260);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("PostRender_Console_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("PostRender_Console_Typing"), 0x268);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("BeginState_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("BeginState_Typing"), 0x270);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("EndState_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("EndState_Typing"), 0x278);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_Open"), 0x280);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputKey_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputKey_Open"), 0x288);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("PostRender_Console_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("PostRender_Console_Open"), 0x290);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("BeginState_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("BeginState_Open"), 0x298);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar"), 0x2A0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputKey")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputKey"), 0x2A8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputAxis")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputAxis"), 0x2B0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputTouch")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputTouch"), 0x2B8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("PostRender_Console")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("PostRender_Console"), 0x2C0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("FakeGotoState")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("FakeGotoState"), 0x2C8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ConsoleActive")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ConsoleActive"), 0x2D0);
}

