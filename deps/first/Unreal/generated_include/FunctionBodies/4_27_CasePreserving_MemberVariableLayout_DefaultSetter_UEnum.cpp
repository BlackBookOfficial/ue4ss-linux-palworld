if (auto it = UEnum::MemberOffsets.find(STR("CppType")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("CppType"), 0x38);
}

if (auto it = UEnum::MemberOffsets.find(STR("Names")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("Names"), 0x48);
}

if (auto it = UEnum::MemberOffsets.find(STR("CppForm")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("CppForm"), 0x58);
}

if (auto it = UEnum::MemberOffsets.find(STR("EnumFlags_Internal")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("EnumFlags_Internal"), 0x5C);
}

if (auto it = UEnum::MemberOffsets.find(STR("EnumDisplayNameFn")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("EnumDisplayNameFn"), 0x60);
}

if (auto it = UEnum::MemberOffsets.find(STR("UEP_TotalSize")); it == UEnum::MemberOffsets.end())
{
    UEnum::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x68);
}
