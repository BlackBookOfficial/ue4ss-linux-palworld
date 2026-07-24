std::unordered_map<File::StringType, int32_t> FConsoleVariableBase::MemberOffsets{};

EConsoleVariableFlags& FConsoleVariableBase::GetFlags()
{
    static auto offset = MemberOffsets.find(STR("Flags"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleVariableBase::Flags' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<EConsoleVariableFlags*>(this, offset->second);
}
const EConsoleVariableFlags& FConsoleVariableBase::GetFlags() const
{
    static auto offset = MemberOffsets.find(STR("Flags"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleVariableBase::Flags' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const EConsoleVariableFlags*>(this, offset->second);
}

FString& FConsoleVariableBase::GetHelp()
{
    static auto offset = MemberOffsets.find(STR("Help"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleVariableBase::Help' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FString*>(this, offset->second);
}
const FString& FConsoleVariableBase::GetHelp() const
{
    static auto offset = MemberOffsets.find(STR("Help"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleVariableBase::Help' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FString*>(this, offset->second);
}

bool& FConsoleVariableBase::GetbWarnedAboutThreadSafety()
{
    static auto offset = MemberOffsets.find(STR("bWarnedAboutThreadSafety"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleVariableBase::bWarnedAboutThreadSafety' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<bool*>(this, offset->second);
}
const bool& FConsoleVariableBase::GetbWarnedAboutThreadSafety() const
{
    static auto offset = MemberOffsets.find(STR("bWarnedAboutThreadSafety"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleVariableBase::bWarnedAboutThreadSafety' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const bool*>(this, offset->second);
}

