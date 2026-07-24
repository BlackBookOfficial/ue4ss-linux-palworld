if (auto it = UObjectBase::VTableLayoutMap.find(STR("__vecDelDtor")); it == UObjectBase::VTableLayoutMap.end())
{
    UObjectBase::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = UObjectBase::VTableLayoutMap.find(STR("RegisterDependencies")); it == UObjectBase::VTableLayoutMap.end())
{
    UObjectBase::VTableLayoutMap.emplace(STR("RegisterDependencies"), 0x8);
}

if (auto it = UObjectBase::VTableLayoutMap.find(STR("DeferredRegister")); it == UObjectBase::VTableLayoutMap.end())
{
    UObjectBase::VTableLayoutMap.emplace(STR("DeferredRegister"), 0x10);
}

