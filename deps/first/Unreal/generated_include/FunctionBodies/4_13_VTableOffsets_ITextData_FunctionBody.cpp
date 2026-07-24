if (auto it = ITextData::VTableLayoutMap.find(STR("__vecDelDtor")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("__vecDelDtor"), 0x0);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetDisplayString")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetDisplayString"), 0x8);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetLocalizedString")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetLocalizedString"), 0x10);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetMutableLocalizedString")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetMutableLocalizedString"), 0x18);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetTextHistory")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetTextHistory"), 0x20);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetMutableTextHistory")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetMutableTextHistory"), 0x28);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("PersistText")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("PersistText"), 0x30);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetGlobalHistoryRevision")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetGlobalHistoryRevision"), 0x38);
}

if (auto it = ITextData::VTableLayoutMap.find(STR("GetLocalHistoryRevision")); it == ITextData::VTableLayoutMap.end())
{
    ITextData::VTableLayoutMap.emplace(STR("GetLocalHistoryRevision"), 0x40);
}

