if (auto it = FDelegateProperty::MemberOffsets.find(STR("SignatureFunction")); it == FDelegateProperty::MemberOffsets.end())
{
    FDelegateProperty::MemberOffsets.emplace(STR("SignatureFunction"), 0x70);
}

if (auto it = FDelegateProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FDelegateProperty::MemberOffsets.end())
{
    FDelegateProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x78);
}
