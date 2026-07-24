if (auto it = UScriptStruct::MemberOffsets.find(STR("StructFlags")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("StructFlags"), 0x98);
}

if (auto it = UScriptStruct::MemberOffsets.find(STR("bPrepareCppStructOpsCompleted")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("bPrepareCppStructOpsCompleted"), 0x9C);
}

if (auto it = UScriptStruct::MemberOffsets.find(STR("CppStructOps")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("CppStructOps"), 0xA0);
}

if (auto it = UScriptStruct::MemberOffsets.find(STR("UEP_TotalSize")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xA8);
}
