if (auto it = UScriptStruct::MemberOffsets.find(STR("StructFlags")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("StructFlags"), 0xB0);
}

if (auto it = UScriptStruct::MemberOffsets.find(STR("bPrepareCppStructOpsCompleted")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("bPrepareCppStructOpsCompleted"), 0xB4);
}

if (auto it = UScriptStruct::MemberOffsets.find(STR("CppStructOps")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("CppStructOps"), 0xB8);
}

if (auto it = UScriptStruct::MemberOffsets.find(STR("UEP_TotalSize")); it == UScriptStruct::MemberOffsets.end())
{
    UScriptStruct::MemberOffsets.emplace(STR("UEP_TotalSize"), 0xC0);
}
