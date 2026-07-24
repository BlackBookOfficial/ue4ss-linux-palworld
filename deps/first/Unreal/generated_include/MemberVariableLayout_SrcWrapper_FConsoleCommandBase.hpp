std::unordered_map<File::StringType, int32_t> FConsoleCommandBase::MemberOffsets{};

EConsoleVariableFlags& FConsoleCommandBase::GetFlags()
{
    static auto offset = MemberOffsets.find(STR("Flags"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleCommandBase::Flags' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<EConsoleVariableFlags*>(this, offset->second);
}
const EConsoleVariableFlags& FConsoleCommandBase::GetFlags() const
{
    static auto offset = MemberOffsets.find(STR("Flags"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleCommandBase::Flags' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const EConsoleVariableFlags*>(this, offset->second);
}

FString& FConsoleCommandBase::GetHelp()
{
    static auto offset = MemberOffsets.find(STR("Help"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleCommandBase::Help' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FString*>(this, offset->second);
}
const FString& FConsoleCommandBase::GetHelp() const
{
    static auto offset = MemberOffsets.find(STR("Help"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FConsoleCommandBase::Help' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FString*>(this, offset->second);
}

