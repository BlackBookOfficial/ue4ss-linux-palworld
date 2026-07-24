std::unordered_map<File::StringType, int32_t> AActor::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> AActor::BitfieldInfos{};

FActorTickFunction& AActor::GetPrimaryActorTick()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PrimaryActorTick"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::PrimaryActorTick' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorTickFunction*>(this, offset);
}
const FActorTickFunction& AActor::GetPrimaryActorTick() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PrimaryActorTick"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::PrimaryActorTick' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorTickFunction*>(this, offset);
}

float& AActor::GetCustomTimeDilation()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CustomTimeDilation"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::CustomTimeDilation' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetCustomTimeDilation() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CustomTimeDilation"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::CustomTimeDilation' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

BitfieldProxy AActor::GetbHidden()
{
    static auto offset_it = MemberOffsets.find(STR("bHidden"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHidden' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHidden"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHidden'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbHidden() const
{
    static auto offset_it = MemberOffsets.find(STR("bHidden"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHidden' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHidden"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHidden'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbNetTemporary()
{
    static auto offset_it = MemberOffsets.find(STR("bNetTemporary"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetTemporary' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetTemporary"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetTemporary'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbNetTemporary() const
{
    static auto offset_it = MemberOffsets.find(STR("bNetTemporary"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetTemporary' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetTemporary"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetTemporary'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbNetStartup()
{
    static auto offset_it = MemberOffsets.find(STR("bNetStartup"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetStartup' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetStartup"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetStartup'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbNetStartup() const
{
    static auto offset_it = MemberOffsets.find(STR("bNetStartup"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetStartup' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetStartup"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetStartup'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbOnlyRelevantToOwner()
{
    static auto offset_it = MemberOffsets.find(STR("bOnlyRelevantToOwner"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bOnlyRelevantToOwner' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bOnlyRelevantToOwner"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bOnlyRelevantToOwner'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbOnlyRelevantToOwner() const
{
    static auto offset_it = MemberOffsets.find(STR("bOnlyRelevantToOwner"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bOnlyRelevantToOwner' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bOnlyRelevantToOwner"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bOnlyRelevantToOwner'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbAlwaysRelevant()
{
    static auto offset_it = MemberOffsets.find(STR("bAlwaysRelevant"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAlwaysRelevant' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAlwaysRelevant"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAlwaysRelevant'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbAlwaysRelevant() const
{
    static auto offset_it = MemberOffsets.find(STR("bAlwaysRelevant"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAlwaysRelevant' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAlwaysRelevant"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAlwaysRelevant'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbReplicateMovement()
{
    static auto offset_it = MemberOffsets.find(STR("bReplicateMovement"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplicateMovement' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplicateMovement"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplicateMovement'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbReplicateMovement() const
{
    static auto offset_it = MemberOffsets.find(STR("bReplicateMovement"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplicateMovement' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplicateMovement"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplicateMovement'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbTearOff()
{
    static auto offset_it = MemberOffsets.find(STR("bTearOff"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bTearOff' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTearOff"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bTearOff'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbTearOff() const
{
    static auto offset_it = MemberOffsets.find(STR("bTearOff"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bTearOff' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTearOff"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bTearOff'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbExchangedRoles()
{
    static auto offset_it = MemberOffsets.find(STR("bExchangedRoles"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bExchangedRoles' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bExchangedRoles"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bExchangedRoles'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbExchangedRoles() const
{
    static auto offset_it = MemberOffsets.find(STR("bExchangedRoles"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bExchangedRoles' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bExchangedRoles"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bExchangedRoles'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbPendingNetUpdate()
{
    static auto offset_it = MemberOffsets.find(STR("bPendingNetUpdate"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bPendingNetUpdate' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPendingNetUpdate"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bPendingNetUpdate'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbPendingNetUpdate() const
{
    static auto offset_it = MemberOffsets.find(STR("bPendingNetUpdate"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bPendingNetUpdate' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPendingNetUpdate"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bPendingNetUpdate'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbNetLoadOnClient()
{
    static auto offset_it = MemberOffsets.find(STR("bNetLoadOnClient"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetLoadOnClient' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetLoadOnClient"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetLoadOnClient'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbNetLoadOnClient() const
{
    static auto offset_it = MemberOffsets.find(STR("bNetLoadOnClient"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetLoadOnClient' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetLoadOnClient"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetLoadOnClient'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbNetUseOwnerRelevancy()
{
    static auto offset_it = MemberOffsets.find(STR("bNetUseOwnerRelevancy"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetUseOwnerRelevancy' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetUseOwnerRelevancy"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetUseOwnerRelevancy'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbNetUseOwnerRelevancy() const
{
    static auto offset_it = MemberOffsets.find(STR("bNetUseOwnerRelevancy"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetUseOwnerRelevancy' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetUseOwnerRelevancy"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetUseOwnerRelevancy'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbBlockInput()
{
    static auto offset_it = MemberOffsets.find(STR("bBlockInput"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bBlockInput' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bBlockInput"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bBlockInput'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbBlockInput() const
{
    static auto offset_it = MemberOffsets.find(STR("bBlockInput"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bBlockInput' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bBlockInput"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bBlockInput'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbRunningUserConstructionScript()
{
    static auto offset_it = MemberOffsets.find(STR("bRunningUserConstructionScript"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bRunningUserConstructionScript' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRunningUserConstructionScript"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bRunningUserConstructionScript'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbRunningUserConstructionScript() const
{
    static auto offset_it = MemberOffsets.find(STR("bRunningUserConstructionScript"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bRunningUserConstructionScript' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRunningUserConstructionScript"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bRunningUserConstructionScript'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbHasFinishedSpawning()
{
    static auto offset_it = MemberOffsets.find(STR("bHasFinishedSpawning"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasFinishedSpawning' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasFinishedSpawning"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasFinishedSpawning'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbHasFinishedSpawning() const
{
    static auto offset_it = MemberOffsets.find(STR("bHasFinishedSpawning"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasFinishedSpawning' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasFinishedSpawning"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasFinishedSpawning'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbActorEnableCollision()
{
    static auto offset_it = MemberOffsets.find(STR("bActorEnableCollision"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorEnableCollision' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorEnableCollision"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorEnableCollision'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorEnableCollision() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorEnableCollision"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorEnableCollision' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorEnableCollision"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorEnableCollision'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbReplicates()
{
    static auto offset_it = MemberOffsets.find(STR("bReplicates"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplicates' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplicates"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplicates'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbReplicates() const
{
    static auto offset_it = MemberOffsets.find(STR("bReplicates"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplicates' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplicates"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplicates'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TEnumAsByte<enum ENetRole>& AActor::GetRemoteRole()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RemoteRole"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::RemoteRole' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum ENetRole>*>(this, offset);
}
const TEnumAsByte<enum ENetRole>& AActor::GetRemoteRole() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RemoteRole"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::RemoteRole' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum ENetRole>*>(this, offset);
}

TObjectPtr<AActor>& AActor::GetOwner()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Owner"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Owner' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<AActor>*>(this, offset);
}
const TObjectPtr<AActor>& AActor::GetOwner() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Owner"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Owner' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<AActor>*>(this, offset);
}

FRepMovement& AActor::GetReplicatedMovement()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReplicatedMovement"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ReplicatedMovement' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FRepMovement*>(this, offset);
}
const FRepMovement& AActor::GetReplicatedMovement() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReplicatedMovement"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ReplicatedMovement' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FRepMovement*>(this, offset);
}

FRepAttachment& AActor::GetAttachmentReplication()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AttachmentReplication"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::AttachmentReplication' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FRepAttachment*>(this, offset);
}
const FRepAttachment& AActor::GetAttachmentReplication() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AttachmentReplication"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::AttachmentReplication' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FRepAttachment*>(this, offset);
}

TEnumAsByte<enum ENetRole>& AActor::GetRole()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Role"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Role' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum ENetRole>*>(this, offset);
}
const TEnumAsByte<enum ENetRole>& AActor::GetRole() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Role"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Role' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum ENetRole>*>(this, offset);
}

TEnumAsByte<enum ENetDormancy>& AActor::GetNetDormancy()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetDormancy"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetDormancy' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum ENetDormancy>*>(this, offset);
}
const TEnumAsByte<enum ENetDormancy>& AActor::GetNetDormancy() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetDormancy"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetDormancy' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum ENetDormancy>*>(this, offset);
}

TEnumAsByte<enum EAutoReceiveInput::Type>& AActor::GetAutoReceiveInput()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AutoReceiveInput"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::AutoReceiveInput' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum EAutoReceiveInput::Type>*>(this, offset);
}
const TEnumAsByte<enum EAutoReceiveInput::Type>& AActor::GetAutoReceiveInput() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("AutoReceiveInput"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::AutoReceiveInput' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum EAutoReceiveInput::Type>*>(this, offset);
}

int32& AActor::GetInputPriority()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InputPriority"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InputPriority' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AActor::GetInputPriority() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InputPriority"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InputPriority' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

TObjectPtr<UInputComponent>& AActor::GetInputComponent()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InputComponent"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InputComponent' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UInputComponent>*>(this, offset);
}
const TObjectPtr<UInputComponent>& AActor::GetInputComponent() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InputComponent"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InputComponent' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UInputComponent>*>(this, offset);
}

TEnumAsByte<enum EInputConsumeOptions>& AActor::GetInputConsumeOption_DEPRECATED()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InputConsumeOption_DEPRECATED"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InputConsumeOption_DEPRECATED' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TEnumAsByte<enum EInputConsumeOptions>*>(this, offset);
}
const TEnumAsByte<enum EInputConsumeOptions>& AActor::GetInputConsumeOption_DEPRECATED() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InputConsumeOption_DEPRECATED"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InputConsumeOption_DEPRECATED' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TEnumAsByte<enum EInputConsumeOptions>*>(this, offset);
}

float& AActor::GetNetCullDistanceSquared()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetCullDistanceSquared"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetCullDistanceSquared' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetNetCullDistanceSquared() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetCullDistanceSquared"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetCullDistanceSquared' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

int32& AActor::GetNetTag()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetTag"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetTag' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AActor::GetNetTag() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetTag"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetTag' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

float& AActor::GetNetUpdateTime()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetUpdateTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetUpdateTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetNetUpdateTime() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetUpdateTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetUpdateTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

float& AActor::GetNetUpdateFrequency()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetUpdateFrequency"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetUpdateFrequency' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetNetUpdateFrequency() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetUpdateFrequency"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetUpdateFrequency' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

float& AActor::GetNetPriority()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetPriority"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetPriority' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetNetPriority() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetPriority"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetPriority' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

float& AActor::GetLastNetUpdateTime()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastNetUpdateTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::LastNetUpdateTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetLastNetUpdateTime() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastNetUpdateTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::LastNetUpdateTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

FName& AActor::GetNetDriverName()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetDriverName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetDriverName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FName*>(this, offset);
}
const FName& AActor::GetNetDriverName() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NetDriverName"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::NetDriverName' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FName*>(this, offset);
}

BitfieldProxy AActor::GetbAutoDestroyWhenFinished()
{
    static auto offset_it = MemberOffsets.find(STR("bAutoDestroyWhenFinished"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAutoDestroyWhenFinished' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAutoDestroyWhenFinished"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAutoDestroyWhenFinished'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbAutoDestroyWhenFinished() const
{
    static auto offset_it = MemberOffsets.find(STR("bAutoDestroyWhenFinished"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAutoDestroyWhenFinished' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAutoDestroyWhenFinished"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAutoDestroyWhenFinished'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbCanBeDamaged()
{
    static auto offset_it = MemberOffsets.find(STR("bCanBeDamaged"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCanBeDamaged' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCanBeDamaged"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCanBeDamaged'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbCanBeDamaged() const
{
    static auto offset_it = MemberOffsets.find(STR("bCanBeDamaged"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCanBeDamaged' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCanBeDamaged"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCanBeDamaged'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbActorIsBeingDestroyed()
{
    static auto offset_it = MemberOffsets.find(STR("bActorIsBeingDestroyed"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorIsBeingDestroyed' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorIsBeingDestroyed"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorIsBeingDestroyed'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorIsBeingDestroyed() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorIsBeingDestroyed"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorIsBeingDestroyed' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorIsBeingDestroyed"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorIsBeingDestroyed'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbCollideWhenPlacing()
{
    static auto offset_it = MemberOffsets.find(STR("bCollideWhenPlacing"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCollideWhenPlacing' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCollideWhenPlacing"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCollideWhenPlacing'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbCollideWhenPlacing() const
{
    static auto offset_it = MemberOffsets.find(STR("bCollideWhenPlacing"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCollideWhenPlacing' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCollideWhenPlacing"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCollideWhenPlacing'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbFindCameraComponentWhenViewTarget()
{
    static auto offset_it = MemberOffsets.find(STR("bFindCameraComponentWhenViewTarget"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bFindCameraComponentWhenViewTarget' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bFindCameraComponentWhenViewTarget"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bFindCameraComponentWhenViewTarget'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbFindCameraComponentWhenViewTarget() const
{
    static auto offset_it = MemberOffsets.find(STR("bFindCameraComponentWhenViewTarget"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bFindCameraComponentWhenViewTarget' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bFindCameraComponentWhenViewTarget"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bFindCameraComponentWhenViewTarget'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbRelevantForNetworkReplays()
{
    static auto offset_it = MemberOffsets.find(STR("bRelevantForNetworkReplays"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bRelevantForNetworkReplays' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRelevantForNetworkReplays"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bRelevantForNetworkReplays'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbRelevantForNetworkReplays() const
{
    static auto offset_it = MemberOffsets.find(STR("bRelevantForNetworkReplays"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bRelevantForNetworkReplays' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRelevantForNetworkReplays"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bRelevantForNetworkReplays'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

ESpawnActorCollisionHandlingMethod& AActor::GetSpawnCollisionHandlingMethod()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SpawnCollisionHandlingMethod"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::SpawnCollisionHandlingMethod' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<ESpawnActorCollisionHandlingMethod*>(this, offset);
}
const ESpawnActorCollisionHandlingMethod& AActor::GetSpawnCollisionHandlingMethod() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SpawnCollisionHandlingMethod"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::SpawnCollisionHandlingMethod' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const ESpawnActorCollisionHandlingMethod*>(this, offset);
}

float& AActor::GetCreationTime()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CreationTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::CreationTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetCreationTime() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CreationTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::CreationTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

TArray<TObjectPtr<AActor>,TSizedDefaultAllocator<32> >& AActor::GetChildren()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Children"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Children' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<TObjectPtr<AActor>,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<TObjectPtr<AActor>,TSizedDefaultAllocator<32> >& AActor::GetChildren() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Children"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Children' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<TObjectPtr<AActor>,TSizedDefaultAllocator<32> >*>(this, offset);
}

TObjectPtr<USceneComponent>& AActor::GetRootComponent()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RootComponent"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::RootComponent' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<USceneComponent>*>(this, offset);
}
const TObjectPtr<USceneComponent>& AActor::GetRootComponent() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RootComponent"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::RootComponent' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<USceneComponent>*>(this, offset);
}

TArray<AMatineeActor *,TSizedDefaultAllocator<32> >& AActor::GetControllingMatineeActors()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ControllingMatineeActors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ControllingMatineeActors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<AMatineeActor *,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<AMatineeActor *,TSizedDefaultAllocator<32> >& AActor::GetControllingMatineeActors() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ControllingMatineeActors"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ControllingMatineeActors' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<AMatineeActor *,TSizedDefaultAllocator<32> >*>(this, offset);
}

float& AActor::GetInitialLifeSpan()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InitialLifeSpan"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InitialLifeSpan' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetInitialLifeSpan() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("InitialLifeSpan"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::InitialLifeSpan' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

FTimerHandle& AActor::GetTimerHandle_LifeSpanExpired()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimerHandle_LifeSpanExpired"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::TimerHandle_LifeSpanExpired' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FTimerHandle*>(this, offset);
}
const FTimerHandle& AActor::GetTimerHandle_LifeSpanExpired() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("TimerHandle_LifeSpanExpired"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::TimerHandle_LifeSpanExpired' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FTimerHandle*>(this, offset);
}

BitfieldProxy AActor::GetbAllowReceiveTickEventOnDedicatedServer()
{
    static auto offset_it = MemberOffsets.find(STR("bAllowReceiveTickEventOnDedicatedServer"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAllowReceiveTickEventOnDedicatedServer' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAllowReceiveTickEventOnDedicatedServer"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAllowReceiveTickEventOnDedicatedServer'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbAllowReceiveTickEventOnDedicatedServer() const
{
    static auto offset_it = MemberOffsets.find(STR("bAllowReceiveTickEventOnDedicatedServer"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAllowReceiveTickEventOnDedicatedServer' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAllowReceiveTickEventOnDedicatedServer"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAllowReceiveTickEventOnDedicatedServer'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TArray<FName,TSizedDefaultAllocator<32> >& AActor::GetLayers()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Layers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Layers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FName,TSizedDefaultAllocator<32> >& AActor::GetLayers() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Layers"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Layers' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}

TWeakObjectPtr<AActor,FWeakObjectPtr>& AActor::GetParentComponentActor()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParentComponentActor"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ParentComponentActor' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakObjectPtr<AActor,FWeakObjectPtr>*>(this, offset);
}
const TWeakObjectPtr<AActor,FWeakObjectPtr>& AActor::GetParentComponentActor() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParentComponentActor"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ParentComponentActor' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakObjectPtr<AActor,FWeakObjectPtr>*>(this, offset);
}

BitfieldProxy AActor::GetbActorInitialized()
{
    static auto offset_it = MemberOffsets.find(STR("bActorInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorInitialized'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorInitialized() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorInitialized"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorInitialized' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorInitialized"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorInitialized'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbActorHasBegunPlay()
{
    static auto offset_it = MemberOffsets.find(STR("bActorHasBegunPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorHasBegunPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorHasBegunPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorHasBegunPlay'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorHasBegunPlay() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorHasBegunPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorHasBegunPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorHasBegunPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorHasBegunPlay'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbActorSeamlessTraveled()
{
    static auto offset_it = MemberOffsets.find(STR("bActorSeamlessTraveled"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorSeamlessTraveled' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorSeamlessTraveled"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorSeamlessTraveled'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorSeamlessTraveled() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorSeamlessTraveled"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorSeamlessTraveled' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorSeamlessTraveled"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorSeamlessTraveled'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbIgnoresOriginShifting()
{
    static auto offset_it = MemberOffsets.find(STR("bIgnoresOriginShifting"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bIgnoresOriginShifting' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIgnoresOriginShifting"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bIgnoresOriginShifting'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbIgnoresOriginShifting() const
{
    static auto offset_it = MemberOffsets.find(STR("bIgnoresOriginShifting"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bIgnoresOriginShifting' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIgnoresOriginShifting"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bIgnoresOriginShifting'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbEnableAutoLODGeneration()
{
    static auto offset_it = MemberOffsets.find(STR("bEnableAutoLODGeneration"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bEnableAutoLODGeneration' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bEnableAutoLODGeneration"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bEnableAutoLODGeneration'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbEnableAutoLODGeneration() const
{
    static auto offset_it = MemberOffsets.find(STR("bEnableAutoLODGeneration"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bEnableAutoLODGeneration' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bEnableAutoLODGeneration"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bEnableAutoLODGeneration'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TArray<FName,TSizedDefaultAllocator<32> >& AActor::GetTags()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Tags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Tags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<FName,TSizedDefaultAllocator<32> >& AActor::GetTags() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("Tags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::Tags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<FName,TSizedDefaultAllocator<32> >*>(this, offset);
}

uint64& AActor::GetHiddenEditorViews()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HiddenEditorViews"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::HiddenEditorViews' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint64*>(this, offset);
}
const uint64& AActor::GetHiddenEditorViews() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HiddenEditorViews"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::HiddenEditorViews' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint64*>(this, offset);
}

FTakeAnyDamageSignature& AActor::GetOnTakeAnyDamage()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnTakeAnyDamage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnTakeAnyDamage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FTakeAnyDamageSignature*>(this, offset);
}
const FTakeAnyDamageSignature& AActor::GetOnTakeAnyDamage() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnTakeAnyDamage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnTakeAnyDamage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FTakeAnyDamageSignature*>(this, offset);
}

FTakePointDamageSignature& AActor::GetOnTakePointDamage()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnTakePointDamage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnTakePointDamage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FTakePointDamageSignature*>(this, offset);
}
const FTakePointDamageSignature& AActor::GetOnTakePointDamage() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnTakePointDamage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnTakePointDamage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FTakePointDamageSignature*>(this, offset);
}

FActorBeginOverlapSignature& AActor::GetOnActorBeginOverlap()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnActorBeginOverlap"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnActorBeginOverlap' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorBeginOverlapSignature*>(this, offset);
}
const FActorBeginOverlapSignature& AActor::GetOnActorBeginOverlap() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnActorBeginOverlap"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnActorBeginOverlap' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorBeginOverlapSignature*>(this, offset);
}

FActorEndOverlapSignature& AActor::GetOnActorEndOverlap()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnActorEndOverlap"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnActorEndOverlap' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorEndOverlapSignature*>(this, offset);
}
const FActorEndOverlapSignature& AActor::GetOnActorEndOverlap() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnActorEndOverlap"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnActorEndOverlap' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorEndOverlapSignature*>(this, offset);
}

FActorBeginCursorOverSignature& AActor::GetOnBeginCursorOver()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnBeginCursorOver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnBeginCursorOver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorBeginCursorOverSignature*>(this, offset);
}
const FActorBeginCursorOverSignature& AActor::GetOnBeginCursorOver() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnBeginCursorOver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnBeginCursorOver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorBeginCursorOverSignature*>(this, offset);
}

FActorEndCursorOverSignature& AActor::GetOnEndCursorOver()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnEndCursorOver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnEndCursorOver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorEndCursorOverSignature*>(this, offset);
}
const FActorEndCursorOverSignature& AActor::GetOnEndCursorOver() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnEndCursorOver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnEndCursorOver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorEndCursorOverSignature*>(this, offset);
}

FActorOnClickedSignature& AActor::GetOnClicked()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnClicked"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnClicked' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorOnClickedSignature*>(this, offset);
}
const FActorOnClickedSignature& AActor::GetOnClicked() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnClicked"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnClicked' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorOnClickedSignature*>(this, offset);
}

FActorOnReleasedSignature& AActor::GetOnReleased()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnReleased"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnReleased' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorOnReleasedSignature*>(this, offset);
}
const FActorOnReleasedSignature& AActor::GetOnReleased() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnReleased"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnReleased' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorOnReleasedSignature*>(this, offset);
}

FActorOnInputTouchBeginSignature& AActor::GetOnInputTouchBegin()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchBegin"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchBegin' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorOnInputTouchBeginSignature*>(this, offset);
}
const FActorOnInputTouchBeginSignature& AActor::GetOnInputTouchBegin() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchBegin"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchBegin' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorOnInputTouchBeginSignature*>(this, offset);
}

FActorOnInputTouchEndSignature& AActor::GetOnInputTouchEnd()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchEnd"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchEnd' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorOnInputTouchEndSignature*>(this, offset);
}
const FActorOnInputTouchEndSignature& AActor::GetOnInputTouchEnd() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchEnd"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchEnd' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorOnInputTouchEndSignature*>(this, offset);
}

FActorBeginTouchOverSignature& AActor::GetOnInputTouchEnter()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchEnter"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchEnter' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorBeginTouchOverSignature*>(this, offset);
}
const FActorBeginTouchOverSignature& AActor::GetOnInputTouchEnter() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchEnter"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchEnter' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorBeginTouchOverSignature*>(this, offset);
}

FActorEndTouchOverSignature& AActor::GetOnInputTouchLeave()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchLeave"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchLeave' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorEndTouchOverSignature*>(this, offset);
}
const FActorEndTouchOverSignature& AActor::GetOnInputTouchLeave() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnInputTouchLeave"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnInputTouchLeave' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorEndTouchOverSignature*>(this, offset);
}

FActorHitSignature& AActor::GetOnActorHit()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnActorHit"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnActorHit' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorHitSignature*>(this, offset);
}
const FActorHitSignature& AActor::GetOnActorHit() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnActorHit"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnActorHit' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorHitSignature*>(this, offset);
}

FActorDestroyedSignature& AActor::GetOnDestroyed()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnDestroyed"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnDestroyed' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorDestroyedSignature*>(this, offset);
}
const FActorDestroyedSignature& AActor::GetOnDestroyed() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnDestroyed"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnDestroyed' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorDestroyedSignature*>(this, offset);
}

FActorEndPlaySignature& AActor::GetOnEndPlay()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnEndPlay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnEndPlay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorEndPlaySignature*>(this, offset);
}
const FActorEndPlaySignature& AActor::GetOnEndPlay() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnEndPlay"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnEndPlay' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorEndPlaySignature*>(this, offset);
}

FRenderCommandFence& AActor::GetDetachFence()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DetachFence"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::DetachFence' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FRenderCommandFence*>(this, offset);
}
const FRenderCommandFence& AActor::GetDetachFence() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DetachFence"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::DetachFence' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FRenderCommandFence*>(this, offset);
}

BitfieldProxy AActor::GetbAllowTickBeforeBeginPlay()
{
    static auto offset_it = MemberOffsets.find(STR("bAllowTickBeforeBeginPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAllowTickBeforeBeginPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAllowTickBeforeBeginPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAllowTickBeforeBeginPlay'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbAllowTickBeforeBeginPlay() const
{
    static auto offset_it = MemberOffsets.find(STR("bAllowTickBeforeBeginPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAllowTickBeforeBeginPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAllowTickBeforeBeginPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAllowTickBeforeBeginPlay'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbTickFunctionsRegistered()
{
    static auto offset_it = MemberOffsets.find(STR("bTickFunctionsRegistered"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bTickFunctionsRegistered' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTickFunctionsRegistered"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bTickFunctionsRegistered'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbTickFunctionsRegistered() const
{
    static auto offset_it = MemberOffsets.find(STR("bTickFunctionsRegistered"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bTickFunctionsRegistered' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bTickFunctionsRegistered"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bTickFunctionsRegistered'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbNetCheckedInitialPhysicsState()
{
    static auto offset_it = MemberOffsets.find(STR("bNetCheckedInitialPhysicsState"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetCheckedInitialPhysicsState' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetCheckedInitialPhysicsState"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetCheckedInitialPhysicsState'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbNetCheckedInitialPhysicsState() const
{
    static auto offset_it = MemberOffsets.find(STR("bNetCheckedInitialPhysicsState"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bNetCheckedInitialPhysicsState' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bNetCheckedInitialPhysicsState"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bNetCheckedInitialPhysicsState'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TWeakObjectPtr<AActor,FWeakObjectPtr>& AActor::GetParentComponentActor_DEPRECATED()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParentComponentActor_DEPRECATED"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ParentComponentActor_DEPRECATED' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakObjectPtr<AActor,FWeakObjectPtr>*>(this, offset);
}
const TWeakObjectPtr<AActor,FWeakObjectPtr>& AActor::GetParentComponentActor_DEPRECATED() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParentComponentActor_DEPRECATED"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ParentComponentActor_DEPRECATED' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakObjectPtr<AActor,FWeakObjectPtr>*>(this, offset);
}

TWeakObjectPtr<UChildActorComponent,FWeakObjectPtr>& AActor::GetParentComponent()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParentComponent"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ParentComponent' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TWeakObjectPtr<UChildActorComponent,FWeakObjectPtr>*>(this, offset);
}
const TWeakObjectPtr<UChildActorComponent,FWeakObjectPtr>& AActor::GetParentComponent() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ParentComponent"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ParentComponent' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TWeakObjectPtr<UChildActorComponent,FWeakObjectPtr>*>(this, offset);
}

BitfieldProxy AActor::GetActorHasBegunPlay()
{
    static auto offset_it = MemberOffsets.find(STR("ActorHasBegunPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ActorHasBegunPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ActorHasBegunPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::ActorHasBegunPlay'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetActorHasBegunPlay() const
{
    static auto offset_it = MemberOffsets.find(STR("ActorHasBegunPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ActorHasBegunPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ActorHasBegunPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::ActorHasBegunPlay'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

float& AActor::GetMinNetUpdateFrequency()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MinNetUpdateFrequency"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::MinNetUpdateFrequency' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetMinNetUpdateFrequency() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("MinNetUpdateFrequency"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::MinNetUpdateFrequency' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

BitfieldProxy AActor::GetbGenerateOverlapEventsDuringLevelStreaming()
{
    static auto offset_it = MemberOffsets.find(STR("bGenerateOverlapEventsDuringLevelStreaming"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bGenerateOverlapEventsDuringLevelStreaming' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bGenerateOverlapEventsDuringLevelStreaming"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bGenerateOverlapEventsDuringLevelStreaming'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbGenerateOverlapEventsDuringLevelStreaming() const
{
    static auto offset_it = MemberOffsets.find(STR("bGenerateOverlapEventsDuringLevelStreaming"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bGenerateOverlapEventsDuringLevelStreaming' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bGenerateOverlapEventsDuringLevelStreaming"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bGenerateOverlapEventsDuringLevelStreaming'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbHasDeferredComponentRegistration()
{
    static auto offset_it = MemberOffsets.find(STR("bHasDeferredComponentRegistration"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasDeferredComponentRegistration' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasDeferredComponentRegistration"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasDeferredComponentRegistration'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbHasDeferredComponentRegistration() const
{
    static auto offset_it = MemberOffsets.find(STR("bHasDeferredComponentRegistration"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasDeferredComponentRegistration' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasDeferredComponentRegistration"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasDeferredComponentRegistration'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbCanBeInCluster()
{
    static auto offset_it = MemberOffsets.find(STR("bCanBeInCluster"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCanBeInCluster' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCanBeInCluster"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCanBeInCluster'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbCanBeInCluster() const
{
    static auto offset_it = MemberOffsets.find(STR("bCanBeInCluster"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCanBeInCluster' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCanBeInCluster"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCanBeInCluster'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbReplayRewindable()
{
    static auto offset_it = MemberOffsets.find(STR("bReplayRewindable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplayRewindable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplayRewindable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplayRewindable'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbReplayRewindable() const
{
    static auto offset_it = MemberOffsets.find(STR("bReplayRewindable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplayRewindable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplayRewindable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplayRewindable'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbIsEditorOnlyActor()
{
    static auto offset_it = MemberOffsets.find(STR("bIsEditorOnlyActor"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bIsEditorOnlyActor' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsEditorOnlyActor"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bIsEditorOnlyActor'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbIsEditorOnlyActor() const
{
    static auto offset_it = MemberOffsets.find(STR("bIsEditorOnlyActor"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bIsEditorOnlyActor' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIsEditorOnlyActor"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bIsEditorOnlyActor'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbActorWantsDestroyDuringBeginPlay()
{
    static auto offset_it = MemberOffsets.find(STR("bActorWantsDestroyDuringBeginPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorWantsDestroyDuringBeginPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorWantsDestroyDuringBeginPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorWantsDestroyDuringBeginPlay'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorWantsDestroyDuringBeginPlay() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorWantsDestroyDuringBeginPlay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorWantsDestroyDuringBeginPlay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorWantsDestroyDuringBeginPlay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorWantsDestroyDuringBeginPlay'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FTakeRadialDamageSignature& AActor::GetOnTakeRadialDamage()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnTakeRadialDamage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnTakeRadialDamage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FTakeRadialDamageSignature*>(this, offset);
}
const FTakeRadialDamageSignature& AActor::GetOnTakeRadialDamage() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("OnTakeRadialDamage"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::OnTakeRadialDamage' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FTakeRadialDamageSignature*>(this, offset);
}

float& AActor::GetCachedLastRenderTime()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CachedLastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::CachedLastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetCachedLastRenderTime() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CachedLastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::CachedLastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

BitfieldProxy AActor::GetbRelevantForLevelBounds()
{
    static auto offset_it = MemberOffsets.find(STR("bRelevantForLevelBounds"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bRelevantForLevelBounds' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRelevantForLevelBounds"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bRelevantForLevelBounds'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbRelevantForLevelBounds() const
{
    static auto offset_it = MemberOffsets.find(STR("bRelevantForLevelBounds"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bRelevantForLevelBounds' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bRelevantForLevelBounds"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bRelevantForLevelBounds'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

float& AActor::GetLastRenderTimeBase()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::LastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<float*>(this, offset);
}
const float& AActor::GetLastRenderTimeBase() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::LastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const float*>(this, offset);
}

FActorLastRenderTime& AActor::GetLastRenderTime505()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::LastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FActorLastRenderTime*>(this, offset);
}
const FActorLastRenderTime& AActor::GetLastRenderTime505() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("LastRenderTime"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::LastRenderTime' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FActorLastRenderTime*>(this, offset);
}

BitfieldProxy AActor::GetbActorBeginningPlayFromLevelStreaming()
{
    static auto offset_it = MemberOffsets.find(STR("bActorBeginningPlayFromLevelStreaming"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorBeginningPlayFromLevelStreaming' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorBeginningPlayFromLevelStreaming"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorBeginningPlayFromLevelStreaming'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorBeginningPlayFromLevelStreaming() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorBeginningPlayFromLevelStreaming"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorBeginningPlayFromLevelStreaming' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorBeginningPlayFromLevelStreaming"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorBeginningPlayFromLevelStreaming'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

EActorUpdateOverlapsMethod& AActor::GetUpdateOverlapsMethodDuringLevelStreaming()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UpdateOverlapsMethodDuringLevelStreaming"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::UpdateOverlapsMethodDuringLevelStreaming' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EActorUpdateOverlapsMethod*>(this, offset);
}
const EActorUpdateOverlapsMethod& AActor::GetUpdateOverlapsMethodDuringLevelStreaming() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("UpdateOverlapsMethodDuringLevelStreaming"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::UpdateOverlapsMethodDuringLevelStreaming' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EActorUpdateOverlapsMethod*>(this, offset);
}

EActorUpdateOverlapsMethod& AActor::GetDefaultUpdateOverlapsMethodDuringLevelStreaming()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DefaultUpdateOverlapsMethodDuringLevelStreaming"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::DefaultUpdateOverlapsMethodDuringLevelStreaming' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EActorUpdateOverlapsMethod*>(this, offset);
}
const EActorUpdateOverlapsMethod& AActor::GetDefaultUpdateOverlapsMethodDuringLevelStreaming() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("DefaultUpdateOverlapsMethodDuringLevelStreaming"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::DefaultUpdateOverlapsMethodDuringLevelStreaming' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EActorUpdateOverlapsMethod*>(this, offset);
}

BitfieldProxy AActor::GetbActorIsBeingConstructed()
{
    static auto offset_it = MemberOffsets.find(STR("bActorIsBeingConstructed"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorIsBeingConstructed' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorIsBeingConstructed"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorIsBeingConstructed'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorIsBeingConstructed() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorIsBeingConstructed"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorIsBeingConstructed' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorIsBeingConstructed"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorIsBeingConstructed'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbForceNetAddressable()
{
    static auto offset_it = MemberOffsets.find(STR("bForceNetAddressable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bForceNetAddressable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bForceNetAddressable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bForceNetAddressable'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbForceNetAddressable() const
{
    static auto offset_it = MemberOffsets.find(STR("bForceNetAddressable"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bForceNetAddressable' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bForceNetAddressable"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bForceNetAddressable'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbCallPreReplication()
{
    static auto offset_it = MemberOffsets.find(STR("bCallPreReplication"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCallPreReplication' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCallPreReplication"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCallPreReplication'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbCallPreReplication() const
{
    static auto offset_it = MemberOffsets.find(STR("bCallPreReplication"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCallPreReplication' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCallPreReplication"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCallPreReplication'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbCallPreReplicationForReplay()
{
    static auto offset_it = MemberOffsets.find(STR("bCallPreReplicationForReplay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCallPreReplicationForReplay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCallPreReplicationForReplay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCallPreReplicationForReplay'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbCallPreReplicationForReplay() const
{
    static auto offset_it = MemberOffsets.find(STR("bCallPreReplicationForReplay"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bCallPreReplicationForReplay' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bCallPreReplicationForReplay"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bCallPreReplicationForReplay'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32& AActor::GetRayTracingGroupId()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RayTracingGroupId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::RayTracingGroupId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& AActor::GetRayTracingGroupId() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RayTracingGroupId"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::RayTracingGroupId' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

BitfieldProxy AActor::GetbReplicateUsingRegisteredSubObjectList()
{
    static auto offset_it = MemberOffsets.find(STR("bReplicateUsingRegisteredSubObjectList"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplicateUsingRegisteredSubObjectList' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplicateUsingRegisteredSubObjectList"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplicateUsingRegisteredSubObjectList'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbReplicateUsingRegisteredSubObjectList() const
{
    static auto offset_it = MemberOffsets.find(STR("bReplicateUsingRegisteredSubObjectList"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bReplicateUsingRegisteredSubObjectList' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bReplicateUsingRegisteredSubObjectList"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bReplicateUsingRegisteredSubObjectList'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbHasRegisteredAllComponents()
{
    static auto offset_it = MemberOffsets.find(STR("bHasRegisteredAllComponents"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasRegisteredAllComponents' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasRegisteredAllComponents"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasRegisteredAllComponents'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbHasRegisteredAllComponents() const
{
    static auto offset_it = MemberOffsets.find(STR("bHasRegisteredAllComponents"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasRegisteredAllComponents' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasRegisteredAllComponents"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasRegisteredAllComponents'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbAsyncPhysicsTickEnabled()
{
    static auto offset_it = MemberOffsets.find(STR("bAsyncPhysicsTickEnabled"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAsyncPhysicsTickEnabled' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAsyncPhysicsTickEnabled"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAsyncPhysicsTickEnabled'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbAsyncPhysicsTickEnabled() const
{
    static auto offset_it = MemberOffsets.find(STR("bAsyncPhysicsTickEnabled"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bAsyncPhysicsTickEnabled' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bAsyncPhysicsTickEnabled"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bAsyncPhysicsTickEnabled'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

UE::Net::FSubObjectRegistry& AActor::GetReplicatedSubObjects()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReplicatedSubObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ReplicatedSubObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<UE::Net::FSubObjectRegistry*>(this, offset);
}
const UE::Net::FSubObjectRegistry& AActor::GetReplicatedSubObjects() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReplicatedSubObjects"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ReplicatedSubObjects' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const UE::Net::FSubObjectRegistry*>(this, offset);
}

TArray<UE::Net::FReplicatedComponentInfo,TSizedDefaultAllocator<32> >& AActor::GetReplicatedComponentsInfo()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReplicatedComponentsInfo"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ReplicatedComponentsInfo' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TArray<UE::Net::FReplicatedComponentInfo,TSizedDefaultAllocator<32> >*>(this, offset);
}
const TArray<UE::Net::FReplicatedComponentInfo,TSizedDefaultAllocator<32> >& AActor::GetReplicatedComponentsInfo() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ReplicatedComponentsInfo"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ReplicatedComponentsInfo' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TArray<UE::Net::FReplicatedComponentInfo,TSizedDefaultAllocator<32> >*>(this, offset);
}

EPhysicsReplicationMode& AActor::GetPhysicsReplicationMode()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PhysicsReplicationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::PhysicsReplicationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<EPhysicsReplicationMode*>(this, offset);
}
const EPhysicsReplicationMode& AActor::GetPhysicsReplicationMode() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("PhysicsReplicationMode"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::PhysicsReplicationMode' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const EPhysicsReplicationMode*>(this, offset);
}

uint8& AActor::GetActorCategory()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ActorCategory"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ActorCategory' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint8*>(this, offset);
}
const uint8& AActor::GetActorCategory() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ActorCategory"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::ActorCategory' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint8*>(this, offset);
}

BitfieldProxy AActor::GetbHasPreRegisteredAllComponents()
{
    static auto offset_it = MemberOffsets.find(STR("bHasPreRegisteredAllComponents"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasPreRegisteredAllComponents' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasPreRegisteredAllComponents"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasPreRegisteredAllComponents'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbHasPreRegisteredAllComponents() const
{
    static auto offset_it = MemberOffsets.find(STR("bHasPreRegisteredAllComponents"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bHasPreRegisteredAllComponents' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bHasPreRegisteredAllComponents"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bHasPreRegisteredAllComponents'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy AActor::GetbActorIsPendingPostNetInit()
{
    static auto offset_it = MemberOffsets.find(STR("bActorIsPendingPostNetInit"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorIsPendingPostNetInit' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorIsPendingPostNetInit"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorIsPendingPostNetInit'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy AActor::GetbActorIsPendingPostNetInit() const
{
    static auto offset_it = MemberOffsets.find(STR("bActorIsPendingPostNetInit"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::bActorIsPendingPostNetInit' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bActorIsPendingPostNetInit"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'AActor::bActorIsPendingPostNetInit'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

TObjectPtr<UHLODLayer>& AActor::GetHLODLayer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HLODLayer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::HLODLayer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UHLODLayer>*>(this, offset);
}
const TObjectPtr<UHLODLayer>& AActor::GetHLODLayer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("HLODLayer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'AActor::HLODLayer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UHLODLayer>*>(this, offset);
}

int32_t& AActor::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

