if (auto it = USparseDelegateFunction::MemberOffsets.find(STR("OwningClassName")); it == USparseDelegateFunction::MemberOffsets.end())
{
    USparseDelegateFunction::MemberOffsets.emplace(STR("OwningClassName"), 0xE0);
}

if (auto it = USparseDelegateFunction::MemberOffsets.find(STR("DelegateName")); it == USparseDelegateFunction::MemberOffsets.end())
{
    USparseDelegateFunction::MemberOffsets.emplace(STR("DelegateName"), 0xE8);
}

