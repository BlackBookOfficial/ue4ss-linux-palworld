if (auto it = FInterfaceProperty::MemberOffsets.find(STR("InterfaceClass")); it == FInterfaceProperty::MemberOffsets.end())
{
    FInterfaceProperty::MemberOffsets.emplace(STR("InterfaceClass"), 0x78);
}

if (auto it = FInterfaceProperty::MemberOffsets.find(STR("UEP_TotalSize")); it == FInterfaceProperty::MemberOffsets.end())
{
    FInterfaceProperty::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x80);
}
