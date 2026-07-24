if (auto it = UStruct::MemberOffsets.find(STR("SuperStruct")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("SuperStruct"), 0x40);
}

if (auto it = UStruct::MemberOffsets.find(STR("Children")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("Children"), 0x48);
}

if (auto it = UStruct::MemberOffsets.find(STR("PropertiesSize")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("PropertiesSize"), 0x50);
}

if (auto it = UStruct::MemberOffsets.find(STR("MinAlignment")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("MinAlignment"), 0x54);
}

if (auto it = UStruct::MemberOffsets.find(STR("Script")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("Script"), 0x58);
}

if (auto it = UStruct::MemberOffsets.find(STR("PropertyLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("PropertyLink"), 0x68);
}

if (auto it = UStruct::MemberOffsets.find(STR("RefLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("RefLink"), 0x70);
}

if (auto it = UStruct::MemberOffsets.find(STR("DestructorLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("DestructorLink"), 0x78);
}

if (auto it = UStruct::MemberOffsets.find(STR("PostConstructLink")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("PostConstructLink"), 0x80);
}

if (auto it = UStruct::MemberOffsets.find(STR("ScriptObjectReferences")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("ScriptObjectReferences"), 0x88);
}

if (auto it = UStruct::MemberOffsets.find(STR("UEP_TotalSize")); it == UStruct::MemberOffsets.end())
{
    UStruct::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x98);
}
