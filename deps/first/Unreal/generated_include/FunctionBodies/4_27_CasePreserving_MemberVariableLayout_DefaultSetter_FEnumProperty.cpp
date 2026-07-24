if (auto it = FEnumProperty::MemberOffsets.find(STR("UnderlyingProp")); it == FEnumProperty::MemberOffsets.end())
{
    FEnumProperty::MemberOffsets.emplace(STR("UnderlyingProp"), 0x80);
}

if (auto it = FEnumProperty::MemberOffsets.find(STR("Enum")); it == FEnumProperty::MemberOffsets.end())
{
    FEnumProperty::MemberOffsets.emplace(STR("Enum"), 0x88);
}

if (auto it = FEnumProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FEnumProperty::MemberOffsets.end())
{
    FEnumProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x90);
}
