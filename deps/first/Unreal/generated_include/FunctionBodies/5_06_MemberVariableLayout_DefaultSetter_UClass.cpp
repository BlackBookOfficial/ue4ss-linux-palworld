if (auto it = UClass::MemberOffsets.find(STR("ClassConstructor")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassConstructor"), 0xB0);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassVTableHelperCtorCaller")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassVTableHelperCtorCaller"), 0xB8);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassUnique")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassUnique"), 0xC8);
}

if (auto it = UClass::MemberOffsets.find(STR("FirstOwnedClassRep")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("FirstOwnedClassRep"), 0xCC);
}

if (auto it = UClass::MemberOffsets.find(STR("bCooked")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("bCooked"), 0xD0);
}

if (auto it = UClass::MemberOffsets.find(STR("bLayoutChanging")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("bLayoutChanging"), 0xD1);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassFlags")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassFlags"), 0xD4);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassCastFlags")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassCastFlags"), 0xD8);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassWithin")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassWithin"), 0xE0);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassConfigName")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassConfigName"), 0xE8);
}

if (auto it = UClass::MemberOffsets.find(STR("NetFields")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("NetFields"), 0x100);
}

if (auto it = UClass::MemberOffsets.find(STR("ClassDefaultObject")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ClassDefaultObject"), 0x110);
}

if (auto it = UClass::MemberOffsets.find(STR("SparseClassData")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("SparseClassData"), 0x118);
}

if (auto it = UClass::MemberOffsets.find(STR("SparseClassDataStruct")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("SparseClassDataStruct"), 0x120);
}

if (auto it = UClass::MemberOffsets.find(STR("FuncMap")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("FuncMap"), 0x128);
}

if (auto it = UClass::MemberOffsets.find(STR("FuncMapLock")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("FuncMapLock"), 0x178);
}

if (auto it = UClass::MemberOffsets.find(STR("AllFunctionsCache")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("AllFunctionsCache"), 0x180);
}

if (auto it = UClass::MemberOffsets.find(STR("AllFunctionsCacheLock")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("AllFunctionsCacheLock"), 0x1D0);
}

if (auto it = UClass::MemberOffsets.find(STR("Interfaces")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("Interfaces"), 0x1D8);
}

if (auto it = UClass::MemberOffsets.find(STR("ReferenceSchema")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("ReferenceSchema"), 0x1E8);
}

if (auto it = UClass::MemberOffsets.find(STR("NativeFunctionLookupTable")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("NativeFunctionLookupTable"), 0x1F0);
}

if (auto it = UClass::MemberOffsets.find(STR("UEP_TotalSize")); it == UClass::MemberOffsets.end())
{
    UClass::MemberOffsets.emplace(STR("UEP_TotalSize"), 0x200);
}
