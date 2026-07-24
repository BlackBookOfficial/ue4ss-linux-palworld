if (auto it = UField::MemberOffsets.find(STR("Next")); it == UField::MemberOffsets.end())
{
    UField::MemberOffsets.emplace(STR("Next"), 0x30);
}

if (auto it = UField::MemberOffsets.find(STR("UEP_TotalSize")); it == UField::MemberOffsets.end())
{
    UField::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x38);
}
