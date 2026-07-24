std::unordered_map<File::StringType, int32_t> ULocalPlayer::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> ULocalPlayer::BitfieldInfos{};

TObjectPtr<UGameViewportClient>& ULocalPlayer::GetViewportClient()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportClient"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::ViewportClient' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UGameViewportClient>*>(this, offset);
}
const TObjectPtr<UGameViewportClient>& ULocalPlayer::GetViewportClient() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ViewportClient"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::ViewportClient' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UGameViewportClient>*>(this, offset);
}

FVector& ULocalPlayer::GetLastViewLocation()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastViewLocation"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::LastViewLocation' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FVector*>(this, offset);
}
const FVector& ULocalPlayer::GetLastViewLocation() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastViewLocation"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::LastViewLocation' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FVector*>(this, offset);
}

TEnumAsByte<enum EAspectRatioAxisConstraint>& ULocalPlayer::GetAspectRatioAxisConstraint()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AspectRatioAxisConstraint"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::AspectRatioAxisConstraint' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum EAspectRatioAxisConstraint>*>(this, offset);
}
const TEnumAsByte<enum EAspectRatioAxisConstraint>& ULocalPlayer::GetAspectRatioAxisConstraint() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AspectRatioAxisConstraint"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::AspectRatioAxisConstraint' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum EAspectRatioAxisConstraint>*>(this, offset);
}

BitfieldProxy ULocalPlayer::GetbSentSplitJoin()
{
    static auto offset_it = MemberOffsets.find(STR("bSentSplitJoin"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::bSentSplitJoin' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bSentSplitJoin"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'ULocalPlayer::bSentSplitJoin'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy ULocalPlayer::GetbSentSplitJoin() const
{
    static auto offset_it = MemberOffsets.find(STR("bSentSplitJoin"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::bSentSplitJoin' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bSentSplitJoin"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'ULocalPlayer::bSentSplitJoin'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32& ULocalPlayer::GetControllerId()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ControllerId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::ControllerId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& ULocalPlayer::GetControllerId() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ControllerId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::ControllerId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

bool& ULocalPlayer::GetbEmulateSplitscreen()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bEmulateSplitscreen"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::bEmulateSplitscreen' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& ULocalPlayer::GetbEmulateSplitscreen() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bEmulateSplitscreen"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::bEmulateSplitscreen' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

int32& ULocalPlayer::GetConnectionIdentifier()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ConnectionIdentifier"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::ConnectionIdentifier' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& ULocalPlayer::GetConnectionIdentifier() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ConnectionIdentifier"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'ULocalPlayer::ConnectionIdentifier' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32_t& ULocalPlayer::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

