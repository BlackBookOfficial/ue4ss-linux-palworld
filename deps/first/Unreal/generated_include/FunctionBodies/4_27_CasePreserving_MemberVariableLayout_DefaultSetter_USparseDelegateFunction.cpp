if (auto it = USparseDelegateFunction::MemberOffsets.find(STR("OwningClassName")); it == USparseDelegateFunction::MemberOffsets.end())
{
    USparseDelegateFunction::MemberOffsets.emplace(STR("OwningClassName"), 0xE8);
}

if (auto it = USparseDelegateFunction::MemberOffsets.find(STR("DelegateName")); it == USparseDelegateFunction::MemberOffsets.end())
{
    USparseDelegateFunction::MemberOffsets.emplace(STR("DelegateName"), 0xF4);
}

