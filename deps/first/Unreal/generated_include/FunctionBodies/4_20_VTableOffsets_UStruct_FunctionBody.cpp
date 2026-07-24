if (auto it = UStruct::VTableLayoutMap.find(STR("__vecDelDtor")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetInheritanceSuper")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetInheritanceSuper"), 0x250);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("Link")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("Link"), 0x258);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeBin")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeBin"), 0x260);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeTaggedProperties")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeTaggedProperties"), 0x268);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("InitializeStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("InitializeStruct"), 0x270);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("DestroyStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("DestroyStruct"), 0x278);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeExpr")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeExpr"), 0x280);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetPrefixCPP")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetPrefixCPP"), 0x288);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SetSuperStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SetSuperStruct"), 0x290);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeSuperStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeSuperStruct"), 0x298);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("PropertyNameToDisplayName")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("PropertyNameToDisplayName"), 0x2A0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("FindPropertyNameFromGuid")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("FindPropertyNameFromGuid"), 0x2A8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("FindPropertyGuidFromName")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("FindPropertyGuidFromName"), 0x2B0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("ArePropertyGuidsAvailable")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("ArePropertyGuidsAvailable"), 0x2B8);
}

