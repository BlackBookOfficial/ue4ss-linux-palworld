if (auto it = FByteProperty::MemberOffsets.find(STR("Enum")); it == FByteProperty::MemberOffsets.end())
{
    FByteProperty::MemberOffsets.emplace(STR("Enum"), 0x80);
}

if (auto it = FByteProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FByteProperty::MemberOffsets.end())
{
    FByteProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x88);
}
