if (auto it = FArrayProperty::MemberOffsets.find(STR("Inner")); it == FArrayProperty::MemberOffsets.end())
{
    FArrayProperty::MemberOffsets.emplace(STR("Inner"), 0x70);
}

if (auto it = FArrayProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FArrayProperty::MemberOffsets.end())
{
    FArrayProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x78);
}
