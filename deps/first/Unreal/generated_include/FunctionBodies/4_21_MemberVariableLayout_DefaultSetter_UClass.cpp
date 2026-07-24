if (auto it = UClass::MemberOffsets.find(STR("ClassConstructor")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassConstructor"), 0x98);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassVTableHelperCtorCaller")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassVTableHelperCtorCaller"), 0xA0);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassAddReferencedObjects")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassAddReferencedObjects"), 0xA8);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassUnique")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassUnique"), 0xB0);
    UClass::BitfieldInfos.emplace(STR("ClassUnique"), BitfieldInfo{0, 31, 4});
}

if (auto it = UClass::MemberOffsets.find(STR("bCooked")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("bCooked"), 0xB0);
    UClass::BitfieldInfos.emplace(STR("bCooked"), BitfieldInfo{31, 1, 4});
}

if (auto it = UClass::MemberOffsets.find(STR("ClassFlags")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassFlags"), 0xB4);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassCastFlags")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassCastFlags"), 0xB8);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassWithin")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassWithin"), 0xC0);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassGeneratedBy")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassGeneratedBy"), 0xC8);
}

if (auto it = UClass::MemberOffsets.find(STR("UberGraphFramePointerProperty")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("UberGraphFramePointerProperty"), 0xD0);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassConfigName")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassConfigName"), 0xD8);
}

if (auto it = UClass::MemberOffsets.find(STR("NetFields")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("NetFields"), 0xF0);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassDefaultObject")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassDefaultObject"), 0x100);
}

if (auto it = UClass::MemberOffsets.find(STR("FuncMap")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("FuncMap"), 0x108);
}

if (auto it = UClass::MemberOffsets.find(STR("SuperFuncMap")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("SuperFuncMap"), 0x158);
}

if (auto it = UClass::MemberOffsets.find(STR("Interfaces")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("Interfaces"), 0x1B0);
}

if (auto it = UClass::MemberOffsets.find(STR("ReferenceTokenStream")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ReferenceTokenStream"), 0x1C0);
}

if (auto it = UClass::MemberOffsets.find(STR("NativeFunctionLookupTable")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("NativeFunctionLookupTable"), 0x1F8);
}

if (auto it = UClass::MemberOffsets.find(STR("UEP_TotalSize")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x208);
}
