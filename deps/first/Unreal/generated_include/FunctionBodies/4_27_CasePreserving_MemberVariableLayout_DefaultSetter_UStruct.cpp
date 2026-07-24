if (auto it = UStruct::MemberOffsets.find(STR("SuperStruct")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("SuperStruct"), 0x48);
}

if (auto it = UStruct::MemberOffsets.find(STR("Children")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("Children"), 0x50);
}

if (auto it = UStruct::MemberOffsets.find(STR("ChildProperties")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("ChildProperties"), 0x58);
}

if (auto it = UStruct::MemberOffsets.find(STR("PropertiesSize")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("PropertiesSize"), 0x60);
}

if (auto it = UStruct::MemberOffsets.find(STR("MinAlignment")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("MinAlignment"), 0x64);
}

if (auto it = UStruct::MemberOffsets.find(STR("Script")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("Script"), 0x68);
}

if (auto it = UStruct::MemberOffsets.find(STR("PropertyLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("PropertyLink"), 0x78);
}

if (auto it = UStruct::MemberOffsets.find(STR("RefLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("RefLink"), 0x80);
}

if (auto it = UStruct::MemberOffsets.find(STR("DestructorLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("DestructorLink"), 0x88);
}

if (auto it = UStruct::MemberOffsets.find(STR("PostConstructLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("PostConstructLink"), 0x90);
}

if (auto it = UStruct::MemberOffsets.find(STR("ScriptAndPropertyObjectReferences")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("ScriptAndPropertyObjectReferences"), 0x98);
}

if (auto it = UStruct::MemberOffsets.find(STR("UnresolvedScriptProperties")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("UnresolvedScriptProperties"), 0xA8);
}

if (auto it = UStruct::MemberOffsets.find(STR("UEP_TotalSize")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xB8);
}
