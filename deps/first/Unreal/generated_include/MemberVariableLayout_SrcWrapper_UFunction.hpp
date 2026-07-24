std::unordered_map<File::StringType, int32_t> UFunction::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UFunction::BitfieldInfos{};

uint32& UFunction::GetFunctionFlagsBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FunctionFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::FunctionFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& UFunction::GetFunctionFlagsBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FunctionFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::FunctionFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

EFunctionFlags& UFunction::GetFunctionFlags417()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FunctionFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::FunctionFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EFunctionFlags*>(this, offset);
}
const EFunctionFlags& UFunction::GetFunctionFlags417() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FunctionFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::FunctionFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EFunctionFlags*>(this, offset);
}

uint16& UFunction::GetRepOffset()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RepOffset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::RepOffset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint16*>(this, offset);
}
const uint16& UFunction::GetRepOffset() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RepOffset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::RepOffset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint16*>(this, offset);
}

uint8& UFunction::GetNumParms()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumParms"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::NumParms' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint8*>(this, offset);
}
const uint8& UFunction::GetNumParms() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NumParms"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::NumParms' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint8*>(this, offset);
}

uint16& UFunction::GetParmsSize()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParmsSize"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::ParmsSize' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint16*>(this, offset);
}
const uint16& UFunction::GetParmsSize() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParmsSize"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::ParmsSize' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint16*>(this, offset);
}

uint16& UFunction::GetReturnValueOffset()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReturnValueOffset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::ReturnValueOffset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint16*>(this, offset);
}
const uint16& UFunction::GetReturnValueOffset() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReturnValueOffset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::ReturnValueOffset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint16*>(this, offset);
}

uint16& UFunction::GetRPCId()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RPCId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::RPCId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint16*>(this, offset);
}
const uint16& UFunction::GetRPCId() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RPCId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::RPCId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint16*>(this, offset);
}

uint16& UFunction::GetRPCResponseId()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RPCResponseId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::RPCResponseId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint16*>(this, offset);
}
const uint16& UFunction::GetRPCResponseId() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RPCResponseId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::RPCResponseId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint16*>(this, offset);
}

FProperty*& UFunction::GetFirstPropertyToInit()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FirstPropertyToInit"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::FirstPropertyToInit' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FProperty**>(this, offset);
}
const FProperty*& UFunction::GetFirstPropertyToInit() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("FirstPropertyToInit"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::FirstPropertyToInit' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FProperty**>(this, offset);
}

UFunction*& UFunction::GetEventGraphFunction()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EventGraphFunction"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::EventGraphFunction' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<UFunction**>(this, offset);
}
const UFunction*& UFunction::GetEventGraphFunction() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EventGraphFunction"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::EventGraphFunction' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UFunction**>(this, offset);
}

int32& UFunction::GetEventGraphCallOffset()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EventGraphCallOffset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::EventGraphCallOffset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& UFunction::GetEventGraphCallOffset() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("EventGraphCallOffset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::EventGraphCallOffset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

UFunction::FuncBase_Type& UFunction::GetFuncBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Func"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::Func' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FuncBase_Type*>(this, offset);
}
const UFunction::FuncBase_Type& UFunction::GetFuncBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Func"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::Func' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FuncBase_Type*>(this, offset);
}

std::function<void(UObject*, FFrame&, void* const)>*& UFunction::GetFunc419()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Func"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::Func' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<std::function<void(UObject*, FFrame&, void* const)>**>(this, offset);
}
const std::function<void(UObject*, FFrame&, void* const)>*& UFunction::GetFunc419() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Func"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UFunction::Func' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const std::function<void(UObject*, FFrame&, void* const)>**>(this, offset);
}

int32_t& UFunction::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

