if (auto it = UConsole::VTableLayoutMap.find(STR("__vecDelDtor")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("SetInputText")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("SetInputText"), 0x2B8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("SetCursorPos")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("SetCursorPos"), 0x2C0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ConsoleCommand")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ConsoleCommand"), 0x2C8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ClearOutput")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ClearOutput"), 0x2D0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("OutputText")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("OutputText"), 0x2D8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("StartTyping")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("StartTyping"), 0x2E0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("FlushPlayerInput")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("FlushPlayerInput"), 0x2E8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ProcessControlKey")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ProcessControlKey"), 0x2F0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ProcessShiftKey")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ProcessShiftKey"), 0x2F8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("AppendInputText")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("AppendInputText"), 0x300);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("BuildRuntimeAutoCompleteList")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("BuildRuntimeAutoCompleteList"), 0x308);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("AugmentRuntimeAutoCompleteList")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("AugmentRuntimeAutoCompleteList"), 0x310);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("UpdateCompleteIndices")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("UpdateCompleteIndices"), 0x318);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_Typing"), 0x320);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_Typing_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_Typing_1"), 0x328);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("PostRender_Console_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("PostRender_Console_Typing"), 0x330);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("BeginState_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("BeginState_Typing"), 0x338);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("EndState_Typing")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("EndState_Typing"), 0x340);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_Open"), 0x348);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_Open_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_Open_1"), 0x350);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputKey_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputKey_Open"), 0x358);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputKey_Open_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputKey_Open_1"), 0x360);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("PostRender_Console_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("PostRender_Console_Open"), 0x368);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("BeginState_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("BeginState_Open"), 0x370);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("EndState_Open")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("EndState_Open"), 0x378);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar"), 0x380);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputChar_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputChar_1"), 0x388);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputKey")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputKey"), 0x390);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputKey_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputKey_1"), 0x398);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputAxis")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputAxis"), 0x3A0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputAxis_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputAxis_1"), 0x3A8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputTouch")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputTouch"), 0x3B0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("InputTouch_1")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("InputTouch_1"), 0x3B8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("PostRender_Console")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("PostRender_Console"), 0x3C0);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("FakeGotoState")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("FakeGotoState"), 0x3C8);
}

if (auto it = UConsole::VTableLayoutMap.find(STR("ConsoleActive")); it == UConsole::VTableLayoutMap.end())
{
    UConsole::VTableLayoutMap.emplace(STR("ConsoleActive"), 0x3D0);
}

