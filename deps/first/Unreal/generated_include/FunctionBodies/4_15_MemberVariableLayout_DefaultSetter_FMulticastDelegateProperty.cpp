if (auto it = FMulticastDelegateProperty::MemberOffsets.find(STR("SignatureFunction")); it == FMulticastDelegateProperty::MemberOffsets.end())
{
    FMulticastDelegateProperty::MemberOffsets.emplace(STR("SignatureFunction"), 0x78);
}

if (auto it = FMulticastDelegateProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FMulticastDelegateProperty::MemberOffsets.end())
{
    FMulticastDelegateProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x80);
}
