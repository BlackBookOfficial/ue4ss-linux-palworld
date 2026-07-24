if (auto it = UScriptStruct::ICppStructOps::MemberOffsets.find(STR("FakeVPtr")); it == UScriptStruct::ICppStructOps::MemberOffsets.end())
{
    UScriptStruct::ICppStructOps::MemberOffsets.emplace(STR("FakeVPtr"), 0x0);
}

if (auto it = UScriptStruct::ICppStructOps::MemberOffsets.find(STR("Size")); it == UScriptStruct::ICppStructOps::MemberOffsets.end())
{
    UScriptStruct::ICppStructOps::MemberOffsets.emplace(STR("Size"), 0x8);
}

if (auto it = UScriptStruct::ICppStructOps::MemberOffsets.find(STR("Alignment")); it == UScriptStruct::ICppStructOps::MemberOffsets.end())
{
    UScriptStruct::ICppStructOps::MemberOffsets.emplace(STR("Alignment"), 0xC);
}

if (auto it = UScriptStruct::ICppStructOps::MemberOffsets.find(STR("UEP_TotalSize")); it == UScriptStruct::ICppStructOps::MemberOffsets.end())
{
    UScriptStruct::ICppStructOps::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x10);
}
