if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariable")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariable"), 0x0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariable_1")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariable_1"), 0x8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariable_2")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariable_2"), 0x10);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariable_3")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariable_3"), 0x18);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariable_4")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariable_4"), 0x20);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariableRef")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariableRef"), 0x28);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariableRef_1")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariableRef_1"), 0x30);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariableRef_2")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariableRef_2"), 0x38);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariableRef_3")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariableRef_3"), 0x40);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariableBitRef")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariableBitRef"), 0x48);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("CallAllConsoleVariableSinks")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("CallAllConsoleVariableSinks"), 0x50);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleVariableSink_Handle")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleVariableSink_Handle"), 0x58);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("UnregisterConsoleVariableSink_Handle")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("UnregisterConsoleVariableSink_Handle"), 0x60);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand"), 0x68);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_1")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_1"), 0x70);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_2")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_2"), 0x78);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_3")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_3"), 0x80);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_4")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_4"), 0x88);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_5")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_5"), 0x90);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_6")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_6"), 0x98);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterConsoleCommand_7")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterConsoleCommand_7"), 0xA0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("UnregisterConsoleObject")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("UnregisterConsoleObject"), 0xA8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("UnregisterConsoleObject_1")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("UnregisterConsoleObject_1"), 0xB0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("FindConsoleVariable")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("FindConsoleVariable"), 0xB8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("FindConsoleObject")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("FindConsoleObject"), 0xC0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("FindConsoleObjectName")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("FindConsoleObjectName"), 0xC8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("ForEachConsoleObjectThatStartsWith")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("ForEachConsoleObjectThatStartsWith"), 0xD0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("ForEachConsoleObjectThatContains")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("ForEachConsoleObjectThatContains"), 0xD8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("ProcessUserConsoleInput")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("ProcessUserConsoleInput"), 0xE0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("AddConsoleHistoryEntry")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("AddConsoleHistoryEntry"), 0xE8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("GetConsoleHistory")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("GetConsoleHistory"), 0xF0);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("IsNameRegistered")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("IsNameRegistered"), 0xF8);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("RegisterThreadPropagation")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("RegisterThreadPropagation"), 0x100);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("OnCVarUnregistered")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("OnCVarUnregistered"), 0x108);
}

if (auto it = IConsoleManager::VTableLayoutMap.find(STR("__vecDelDtor")); it == IConsoleManager::VTableLayoutMap.end())
{
    IConsoleManager::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x110);
}

