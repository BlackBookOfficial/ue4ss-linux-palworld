std::unordered_map<File::StringType, int32_t> UConsole::MemberOffsets{};

TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& UConsole::GetAutoComplete()
{
    static auto offset = MemberOffsets.find(STR("AutoComplete"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoComplete' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >*>(this, offset->second);
}
const TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& UConsole::GetAutoComplete() const
{
    static auto offset = MemberOffsets.find(STR("AutoComplete"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoComplete' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >*>(this, offset->second);
}

int32& UConsole::GetAutoCompleteCursor()
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteCursor"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteCursor' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<int32*>(this, offset->second);
}
const int32& UConsole::GetAutoCompleteCursor() const
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteCursor"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteCursor' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const int32*>(this, offset->second);
}

int32& UConsole::GetAutoCompleteIndex()
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteIndex"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteIndex' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<int32*>(this, offset->second);
}
const int32& UConsole::GetAutoCompleteIndex() const
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteIndex"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteIndex' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const int32*>(this, offset->second);
}

TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& UConsole::GetAutoCompleteList()
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteList"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteList' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >*>(this, offset->second);
}
const TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >& UConsole::GetAutoCompleteList() const
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteList"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteList' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TArray<FAutoCompleteCommand,TSizedDefaultAllocator<32> >*>(this, offset->second);
}

FAutoCompleteNode& UConsole::GetAutoCompleteTree()
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteTree"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteTree' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FAutoCompleteNode*>(this, offset->second);
}
const FAutoCompleteNode& UConsole::GetAutoCompleteTree() const
{
    static auto offset = MemberOffsets.find(STR("AutoCompleteTree"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::AutoCompleteTree' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FAutoCompleteNode*>(this, offset->second);
}

UConsoleSettings*& UConsole::GetConsoleSettings()
{
    static auto offset = MemberOffsets.find(STR("ConsoleSettings"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::ConsoleSettings' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<UConsoleSettings**>(this, offset->second);
}
const UConsoleSettings*& UConsole::GetConsoleSettings() const
{
    static auto offset = MemberOffsets.find(STR("ConsoleSettings"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::ConsoleSettings' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const UConsoleSettings**>(this, offset->second);
}

FName& UConsole::GetConsoleState()
{
    static auto offset = MemberOffsets.find(STR("ConsoleState"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::ConsoleState' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FName*>(this, offset->second);
}
const FName& UConsole::GetConsoleState() const
{
    static auto offset = MemberOffsets.find(STR("ConsoleState"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::ConsoleState' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FName*>(this, offset->second);
}

TObjectPtr<ULocalPlayer>& UConsole::GetConsoleTargetPlayer()
{
    static auto offset = MemberOffsets.find(STR("ConsoleTargetPlayer"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::ConsoleTargetPlayer' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TObjectPtr<ULocalPlayer>*>(this, offset->second);
}
const TObjectPtr<ULocalPlayer>& UConsole::GetConsoleTargetPlayer() const
{
    static auto offset = MemberOffsets.find(STR("ConsoleTargetPlayer"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::ConsoleTargetPlayer' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TObjectPtr<ULocalPlayer>*>(this, offset->second);
}

TObjectPtr<UTexture2D>& UConsole::GetDefaultTexture_Black()
{
    static auto offset = MemberOffsets.find(STR("DefaultTexture_Black"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::DefaultTexture_Black' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TObjectPtr<UTexture2D>*>(this, offset->second);
}
const TObjectPtr<UTexture2D>& UConsole::GetDefaultTexture_Black() const
{
    static auto offset = MemberOffsets.find(STR("DefaultTexture_Black"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::DefaultTexture_Black' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TObjectPtr<UTexture2D>*>(this, offset->second);
}

TObjectPtr<UTexture2D>& UConsole::GetDefaultTexture_White()
{
    static auto offset = MemberOffsets.find(STR("DefaultTexture_White"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::DefaultTexture_White' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TObjectPtr<UTexture2D>*>(this, offset->second);
}
const TObjectPtr<UTexture2D>& UConsole::GetDefaultTexture_White() const
{
    static auto offset = MemberOffsets.find(STR("DefaultTexture_White"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::DefaultTexture_White' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TObjectPtr<UTexture2D>*>(this, offset->second);
}

TArray<FString,TSizedDefaultAllocator<32> >& UConsole::GetHistoryBuffer()
{
    static auto offset = MemberOffsets.find(STR("HistoryBuffer"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::HistoryBuffer' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TArray<FString,TSizedDefaultAllocator<32> >*>(this, offset->second);
}
const TArray<FString,TSizedDefaultAllocator<32> >& UConsole::GetHistoryBuffer() const
{
    static auto offset = MemberOffsets.find(STR("HistoryBuffer"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::HistoryBuffer' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TArray<FString,TSizedDefaultAllocator<32> >*>(this, offset->second);
}

FString& UConsole::GetLastAutoCompletedCommand()
{
    static auto offset = MemberOffsets.find(STR("LastAutoCompletedCommand"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::LastAutoCompletedCommand' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FString*>(this, offset->second);
}
const FString& UConsole::GetLastAutoCompletedCommand() const
{
    static auto offset = MemberOffsets.find(STR("LastAutoCompletedCommand"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::LastAutoCompletedCommand' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FString*>(this, offset->second);
}

FString& UConsole::GetPrecompletedInputLine()
{
    static auto offset = MemberOffsets.find(STR("PrecompletedInputLine"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::PrecompletedInputLine' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FString*>(this, offset->second);
}
const FString& UConsole::GetPrecompletedInputLine() const
{
    static auto offset = MemberOffsets.find(STR("PrecompletedInputLine"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::PrecompletedInputLine' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FString*>(this, offset->second);
}

TWeakPtr<SWidget,1>& UConsole::GetPreviousFocusedWidget()
{
    static auto offset = MemberOffsets.find(STR("PreviousFocusedWidget"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::PreviousFocusedWidget' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TWeakPtr<SWidget,1>*>(this, offset->second);
}
const TWeakPtr<SWidget,1>& UConsole::GetPreviousFocusedWidget() const
{
    static auto offset = MemberOffsets.find(STR("PreviousFocusedWidget"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::PreviousFocusedWidget' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TWeakPtr<SWidget,1>*>(this, offset->second);
}

int32& UConsole::GetSBHead()
{
    static auto offset = MemberOffsets.find(STR("SBHead"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::SBHead' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<int32*>(this, offset->second);
}
const int32& UConsole::GetSBHead() const
{
    static auto offset = MemberOffsets.find(STR("SBHead"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::SBHead' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const int32*>(this, offset->second);
}

int32& UConsole::GetSBPos()
{
    static auto offset = MemberOffsets.find(STR("SBPos"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::SBPos' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<int32*>(this, offset->second);
}
const int32& UConsole::GetSBPos() const
{
    static auto offset = MemberOffsets.find(STR("SBPos"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::SBPos' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const int32*>(this, offset->second);
}

TArray<FString,TSizedDefaultAllocator<32> >& UConsole::GetScrollback()
{
    static auto offset = MemberOffsets.find(STR("Scrollback"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::Scrollback' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<TArray<FString,TSizedDefaultAllocator<32> >*>(this, offset->second);
}
const TArray<FString,TSizedDefaultAllocator<32> >& UConsole::GetScrollback() const
{
    static auto offset = MemberOffsets.find(STR("Scrollback"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::Scrollback' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const TArray<FString,TSizedDefaultAllocator<32> >*>(this, offset->second);
}

FString& UConsole::GetTypedStr()
{
    static auto offset = MemberOffsets.find(STR("TypedStr"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::TypedStr' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<FString*>(this, offset->second);
}
const FString& UConsole::GetTypedStr() const
{
    static auto offset = MemberOffsets.find(STR("TypedStr"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::TypedStr' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const FString*>(this, offset->second);
}

int32& UConsole::GetTypedStrPos()
{
    static auto offset = MemberOffsets.find(STR("TypedStrPos"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::TypedStrPos' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<int32*>(this, offset->second);
}
const int32& UConsole::GetTypedStrPos() const
{
    static auto offset = MemberOffsets.find(STR("TypedStrPos"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::TypedStrPos' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const int32*>(this, offset->second);
}

uint32& UConsole::GetbAutoCompleteLocked()
{
    static auto offset = MemberOffsets.find(STR("bAutoCompleteLocked"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bAutoCompleteLocked' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<uint32*>(this, offset->second);
}
const uint32& UConsole::GetbAutoCompleteLocked() const
{
    static auto offset = MemberOffsets.find(STR("bAutoCompleteLocked"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bAutoCompleteLocked' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset->second);
}

uint32& UConsole::GetbCaptureKeyInput()
{
    static auto offset = MemberOffsets.find(STR("bCaptureKeyInput"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bCaptureKeyInput' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<uint32*>(this, offset->second);
}
const uint32& UConsole::GetbCaptureKeyInput() const
{
    static auto offset = MemberOffsets.find(STR("bCaptureKeyInput"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bCaptureKeyInput' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset->second);
}

uint32& UConsole::GetbCtrl()
{
    static auto offset = MemberOffsets.find(STR("bCtrl"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bCtrl' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<uint32*>(this, offset->second);
}
const uint32& UConsole::GetbCtrl() const
{
    static auto offset = MemberOffsets.find(STR("bCtrl"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bCtrl' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset->second);
}

uint32& UConsole::GetbIsRuntimeAutoCompleteUpToDate()
{
    static auto offset = MemberOffsets.find(STR("bIsRuntimeAutoCompleteUpToDate"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bIsRuntimeAutoCompleteUpToDate' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<uint32*>(this, offset->second);
}
const uint32& UConsole::GetbIsRuntimeAutoCompleteUpToDate() const
{
    static auto offset = MemberOffsets.find(STR("bIsRuntimeAutoCompleteUpToDate"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bIsRuntimeAutoCompleteUpToDate' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset->second);
}

uint32& UConsole::GetbShift()
{
    static auto offset = MemberOffsets.find(STR("bShift"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bShift' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<uint32*>(this, offset->second);
}
const uint32& UConsole::GetbShift() const
{
    static auto offset = MemberOffsets.find(STR("bShift"));
    if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UConsole::bShift' that doesn't exist in this engine version."}; }
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset->second);
}

