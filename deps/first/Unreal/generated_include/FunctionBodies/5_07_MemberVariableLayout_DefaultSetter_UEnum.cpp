if (auto it = UEnum::MemberOffsets.find(STR("CppType")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("CppType"), 0x30);
}

if (auto it = UEnum::MemberOffsets.find(STR("Names")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("Names"), 0x40);
}

if (auto it = UEnum::MemberOffsets.find(STR("CppForm")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("CppForm"), 0x58);
}

if (auto it = UEnum::MemberOffsets.find(STR("EnumFlags_Internal")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("EnumFlags_Internal"), 0x59);
}

if (auto it = UEnum::MemberOffsets.find(STR("EnumPackage")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("EnumPackage"), 0x5C);
}

if (auto it = UEnum::MemberOffsets.find(STR("EnumDisplayNameFn")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("EnumDisplayNameFn"), 0x68);
}

if (auto it = UEnum::MemberOffsets.find(STR("UEP_TotalSize")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x70);
}
