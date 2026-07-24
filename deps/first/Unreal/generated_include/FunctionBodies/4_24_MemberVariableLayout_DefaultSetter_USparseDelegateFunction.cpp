if (auto it = USparseDelegateFunction::MemberOffsets.find(STR("OwningClassName")); it == USparseDelegateFunction::MemberOffsets.end())
{
    USparseDelegateFunction::MemberOffsets.emplace(STR("OwningClassName"), 0xC8);
}

if (auto it = USparseDelegateFunction::MemberOffsets.find(STR("DelegateName")); it == USparseDelegateFunction::MemberOffsets.end())
{
    USparseDelegateFunction::MemberOffsets.emplace(STR("DelegateName"), 0xD0);
}

