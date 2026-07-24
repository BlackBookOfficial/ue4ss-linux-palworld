if (auto it = FBoolProperty::MemberOffsets.find(STR("FieldSize")); it == FBoolProperty::MemberOffsets.end())
{
    FBoolProperty::MemberOffsets.emplace(STR("FieldSize"), 0x80);
}

if (auto it = FBoolProperty::MemberOffsets.find(STR("ByteOffset")); it == FBoolProperty::MemberOffsets.end())
{
    FBoolProperty::MemberOffsets.emplace(STR("ByteOffset"), 0x81);
}

if (auto it = FBoolProperty::MemberOffsets.find(STR("ByteMask")); it == FBoolProperty::MemberOffsets.end())
{
    FBoolProperty::MemberOffsets.emplace(STR("ByteMask"), 0x82);
}

if (auto it = FBoolProperty::MemberOffsets.find(STR("FieldMask")); it == FBoolProperty::MemberOffsets.end())
{
    FBoolProperty::MemberOffsets.emplace(STR("FieldMask"), 0x83);
}

if (auto it = FBoolProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FBoolProperty::MemberOffsets.end())
{
    FBoolProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x88);
}
