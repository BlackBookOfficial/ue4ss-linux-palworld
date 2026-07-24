if (auto it = UStruct::VTableLayoutMap.find(STR("__vecDelDtor")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetInheritanceSuper")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetInheritanceSuper"), 0x2C0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("Link")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("Link"), 0x2C8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeBin_C__FStructuredArchiveSlot__Ptr_void")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeBin_C__FStructuredArchiveSlot__Ptr_void"), 0x2D0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeBin_C__Ref_FArchive__Ptr_void")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeBin_C__Ref_FArchive__Ptr_void"), 0x2D8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeTaggedProperties_C__FStructuredArchiveSlot__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeTaggedProperties_C__FStructuredArchiveSlot__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject"), 0x2E0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeTaggedProperties_C__Ref_FArchive__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeTaggedProperties_C__Ref_FArchive__Ptr_uint8__Ptr_UStruct__Ptr_uint8__Ptr_C_UObject"), 0x2E8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("PreloadChildren")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("PreloadChildren"), 0x2F0);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("InitializeStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("InitializeStruct"), 0x2F8);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("DestroyStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("DestroyStruct"), 0x300);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("CustomFindProperty")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("CustomFindProperty"), 0x308);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SerializeExpr")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SerializeExpr"), 0x310);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetPrefixCPP")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetPrefixCPP"), 0x318);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("SetSuperStruct")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("SetSuperStruct"), 0x320);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetAuthoredNameForField_C__Ptr_C_FField")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetAuthoredNameForField_C__Ptr_C_FField"), 0x328);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("GetAuthoredNameForField_C__Ptr_C_UField")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("GetAuthoredNameForField_C__Ptr_C_UField"), 0x330);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("IsStructTrashed")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("IsStructTrashed"), 0x338);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("Visit_C__Ref_FPropertyVisitorContext__C_TFunctionRef_enum_EPropertyVisitorControlFlow_cdecl_FPropertyVisitorContext_const_&_")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("Visit_C__Ref_FPropertyVisitorContext__C_TFunctionRef_enum_EPropertyVisitorControlFlow_cdecl_FPropertyVisitorContext_const_&_"), 0x340);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("ResolveVisitedPathInfo")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("ResolveVisitedPathInfo"), 0x348);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("FindPropertyNameFromGuid")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("FindPropertyNameFromGuid"), 0x350);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("FindPropertyGuidFromName")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("FindPropertyGuidFromName"), 0x358);
}

if (auto it = UStruct::VTableLayoutMap.find(STR("ArePropertyGuidsAvailable")); it == UStruct::VTableLayoutMap.end())
{
    UStruct::VTableLayoutMap.emplace(STR("ArePropertyGuidsAvailable"), 0x360);
}

