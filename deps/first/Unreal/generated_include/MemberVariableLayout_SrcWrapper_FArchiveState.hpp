std::unordered_map<File::StringType, int32_t> FArchiveState::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FArchiveState::BitfieldInfos{};

BitfieldProxy FArchiveState::GetArIsLoading()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsLoading'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsLoading() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsLoading'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsSaving()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaving"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsSaving' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaving"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsSaving'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsSaving() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaving"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsSaving' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaving"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsSaving'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsTransacting()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTransacting"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsTransacting' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTransacting"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsTransacting'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsTransacting() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTransacting"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsTransacting' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTransacting"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsTransacting'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsTextFormat()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTextFormat"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsTextFormat' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTextFormat"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsTextFormat'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsTextFormat() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTextFormat"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsTextFormat' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTextFormat"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsTextFormat'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArWantBinaryPropertySerialization()
{
    static auto offset_it = MemberOffsets.find(STR("ArWantBinaryPropertySerialization"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArWantBinaryPropertySerialization' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArWantBinaryPropertySerialization"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArWantBinaryPropertySerialization'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArWantBinaryPropertySerialization() const
{
    static auto offset_it = MemberOffsets.find(STR("ArWantBinaryPropertySerialization"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArWantBinaryPropertySerialization' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArWantBinaryPropertySerialization"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArWantBinaryPropertySerialization'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArUseUnversionedPropertySerialization()
{
    static auto offset_it = MemberOffsets.find(STR("ArUseUnversionedPropertySerialization"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUseUnversionedPropertySerialization' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArUseUnversionedPropertySerialization"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArUseUnversionedPropertySerialization'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArUseUnversionedPropertySerialization() const
{
    static auto offset_it = MemberOffsets.find(STR("ArUseUnversionedPropertySerialization"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUseUnversionedPropertySerialization' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArUseUnversionedPropertySerialization"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArUseUnversionedPropertySerialization'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArForceUnicode()
{
    static auto offset_it = MemberOffsets.find(STR("ArForceUnicode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArForceUnicode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceUnicode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArForceUnicode'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArForceUnicode() const
{
    static auto offset_it = MemberOffsets.find(STR("ArForceUnicode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArForceUnicode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceUnicode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArForceUnicode'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsPersistent()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsPersistent"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsPersistent' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsPersistent"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsPersistent'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsPersistent() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsPersistent"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsPersistent' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsPersistent"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsPersistent'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsError()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsError'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsError() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsError'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsCriticalError()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCriticalError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsCriticalError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCriticalError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsCriticalError'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsCriticalError() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCriticalError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsCriticalError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCriticalError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsCriticalError'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArContainsCode()
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsCode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArContainsCode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsCode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArContainsCode'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArContainsCode() const
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsCode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArContainsCode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsCode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArContainsCode'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArContainsMap()
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsMap"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArContainsMap' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsMap"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArContainsMap'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArContainsMap() const
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsMap"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArContainsMap' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsMap"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArContainsMap'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArRequiresLocalizationGather()
{
    static auto offset_it = MemberOffsets.find(STR("ArRequiresLocalizationGather"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArRequiresLocalizationGather' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArRequiresLocalizationGather"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArRequiresLocalizationGather'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArRequiresLocalizationGather() const
{
    static auto offset_it = MemberOffsets.find(STR("ArRequiresLocalizationGather"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArRequiresLocalizationGather' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArRequiresLocalizationGather"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArRequiresLocalizationGather'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArForceByteSwapping()
{
    static auto offset_it = MemberOffsets.find(STR("ArForceByteSwapping"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArForceByteSwapping' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceByteSwapping"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArForceByteSwapping'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArForceByteSwapping() const
{
    static auto offset_it = MemberOffsets.find(STR("ArForceByteSwapping"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArForceByteSwapping' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceByteSwapping"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArForceByteSwapping'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIgnoreArchetypeRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreArchetypeRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreArchetypeRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreArchetypeRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreArchetypeRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIgnoreArchetypeRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreArchetypeRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreArchetypeRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreArchetypeRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreArchetypeRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArNoDelta()
{
    static auto offset_it = MemberOffsets.find(STR("ArNoDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArNoDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArNoDelta'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArNoDelta() const
{
    static auto offset_it = MemberOffsets.find(STR("ArNoDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArNoDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArNoDelta'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArNoIntraPropertyDelta()
{
    static auto offset_it = MemberOffsets.find(STR("ArNoIntraPropertyDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArNoIntraPropertyDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoIntraPropertyDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArNoIntraPropertyDelta'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArNoIntraPropertyDelta() const
{
    static auto offset_it = MemberOffsets.find(STR("ArNoIntraPropertyDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArNoIntraPropertyDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoIntraPropertyDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArNoIntraPropertyDelta'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIgnoreOuterRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreOuterRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreOuterRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreOuterRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreOuterRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIgnoreOuterRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreOuterRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreOuterRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreOuterRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreOuterRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIgnoreClassGeneratedByRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreClassGeneratedByRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassGeneratedByRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreClassGeneratedByRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIgnoreClassGeneratedByRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreClassGeneratedByRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassGeneratedByRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreClassGeneratedByRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIgnoreClassRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreClassRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreClassRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIgnoreClassRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIgnoreClassRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIgnoreClassRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArAllowLazyLoading()
{
    static auto offset_it = MemberOffsets.find(STR("ArAllowLazyLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArAllowLazyLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArAllowLazyLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArAllowLazyLoading'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArAllowLazyLoading() const
{
    static auto offset_it = MemberOffsets.find(STR("ArAllowLazyLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArAllowLazyLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArAllowLazyLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArAllowLazyLoading'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsObjectReferenceCollector()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsObjectReferenceCollector"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsObjectReferenceCollector' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsObjectReferenceCollector"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsObjectReferenceCollector'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsObjectReferenceCollector() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsObjectReferenceCollector"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsObjectReferenceCollector' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsObjectReferenceCollector"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsObjectReferenceCollector'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsModifyingWeakAndStrongReferences()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsModifyingWeakAndStrongReferences' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsModifyingWeakAndStrongReferences'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsModifyingWeakAndStrongReferences() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsModifyingWeakAndStrongReferences' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsModifyingWeakAndStrongReferences'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsCountingMemory()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCountingMemory"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsCountingMemory' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCountingMemory"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsCountingMemory'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsCountingMemory() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCountingMemory"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsCountingMemory' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCountingMemory"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsCountingMemory'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArShouldSkipBulkData()
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipBulkData"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArShouldSkipBulkData' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipBulkData"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArShouldSkipBulkData'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArShouldSkipBulkData() const
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipBulkData"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArShouldSkipBulkData' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipBulkData"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArShouldSkipBulkData'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsFilterEditorOnly()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsFilterEditorOnly"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsFilterEditorOnly' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsFilterEditorOnly"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsFilterEditorOnly'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsFilterEditorOnly() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsFilterEditorOnly"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsFilterEditorOnly' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsFilterEditorOnly"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsFilterEditorOnly'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsSaveGame()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaveGame"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsSaveGame' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaveGame"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsSaveGame'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsSaveGame() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaveGame"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsSaveGame' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaveGame"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsSaveGame'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsNetArchive()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsNetArchive"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsNetArchive' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsNetArchive"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsNetArchive'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsNetArchive() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsNetArchive"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsNetArchive' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsNetArchive"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsNetArchive'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArUseCustomPropertyList()
{
    static auto offset_it = MemberOffsets.find(STR("ArUseCustomPropertyList"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUseCustomPropertyList' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArUseCustomPropertyList"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArUseCustomPropertyList'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArUseCustomPropertyList() const
{
    static auto offset_it = MemberOffsets.find(STR("ArUseCustomPropertyList"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUseCustomPropertyList' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArUseCustomPropertyList"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArUseCustomPropertyList'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32& FArchiveState::GetArSerializingDefaults()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArSerializingDefaults"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArSerializingDefaults' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchiveState::GetArSerializingDefaults() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArSerializingDefaults"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArSerializingDefaults' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

uint32& FArchiveState::GetArPortFlags()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArPortFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArPortFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FArchiveState::GetArPortFlags() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArPortFlags"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArPortFlags' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

int64& FArchiveState::GetArMaxSerializeSize()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArMaxSerializeSize"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArMaxSerializeSize' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int64*>(this, offset);
}
const int64& FArchiveState::GetArMaxSerializeSize() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArMaxSerializeSize"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArMaxSerializeSize' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int64*>(this, offset);
}

int32& FArchiveState::GetArUE4Ver()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArUE4Ver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUE4Ver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchiveState::GetArUE4Ver() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArUE4Ver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUE4Ver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& FArchiveState::GetArLicenseeUE4Ver()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArLicenseeUE4Ver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArLicenseeUE4Ver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchiveState::GetArLicenseeUE4Ver() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArLicenseeUE4Ver"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArLicenseeUE4Ver' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

FEngineVersionBase& FArchiveState::GetArEngineVer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArEngineVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArEngineVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FEngineVersionBase*>(this, offset);
}
const FEngineVersionBase& FArchiveState::GetArEngineVer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArEngineVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArEngineVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FEngineVersionBase*>(this, offset);
}

uint32& FArchiveState::GetArEngineNetVer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArEngineNetVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArEngineNetVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FArchiveState::GetArEngineNetVer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArEngineNetVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArEngineNetVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

uint32& FArchiveState::GetArGameNetVer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArGameNetVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArGameNetVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FArchiveState::GetArGameNetVer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArGameNetVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArGameNetVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

FCustomVersionContainer*& FArchiveState::GetCustomVersionContainer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CustomVersionContainer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::CustomVersionContainer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FCustomVersionContainer**>(this, offset);
}
const FCustomVersionContainer*& FArchiveState::GetCustomVersionContainer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CustomVersionContainer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::CustomVersionContainer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FCustomVersionContainer**>(this, offset);
}

const FCustomPropertyListNode*& FArchiveState::GetArCustomPropertyList()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArCustomPropertyList"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArCustomPropertyList' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FCustomPropertyListNode**>(this, offset);
}
const FCustomPropertyListNode*& FArchiveState::GetArCustomPropertyList() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArCustomPropertyList"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArCustomPropertyList' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FCustomPropertyListNode**>(this, offset);
}

const ITargetPlatform*& FArchiveState::GetCookingTargetPlatform()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CookingTargetPlatform"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::CookingTargetPlatform' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const ITargetPlatform**>(this, offset);
}
const ITargetPlatform*& FArchiveState::GetCookingTargetPlatform() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("CookingTargetPlatform"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::CookingTargetPlatform' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const ITargetPlatform**>(this, offset);
}

FProperty*& FArchiveState::GetSerializedProperty()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SerializedProperty"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::SerializedProperty' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FProperty**>(this, offset);
}
const FProperty*& FArchiveState::GetSerializedProperty() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SerializedProperty"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::SerializedProperty' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FProperty**>(this, offset);
}

bool& FArchiveState::GetbCustomVersionsAreReset()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bCustomVersionsAreReset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::bCustomVersionsAreReset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FArchiveState::GetbCustomVersionsAreReset() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("bCustomVersionsAreReset"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::bCustomVersionsAreReset' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

FArchiveState*& FArchiveState::GetNextProxy()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NextProxy"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::NextProxy' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FArchiveState**>(this, offset);
}
const FArchiveState*& FArchiveState::GetNextProxy() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("NextProxy"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::NextProxy' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FArchiveState**>(this, offset);
}

BitfieldProxy FArchiveState::GetArIsLoadingFromCookedPackage()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsLoadingFromCookedPackage"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsLoadingFromCookedPackage' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsLoadingFromCookedPackage"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsLoadingFromCookedPackage'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsLoadingFromCookedPackage() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsLoadingFromCookedPackage"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsLoadingFromCookedPackage' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsLoadingFromCookedPackage"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsLoadingFromCookedPackage'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArShouldSkipCompilingAssets()
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipCompilingAssets"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArShouldSkipCompilingAssets' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipCompilingAssets"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArShouldSkipCompilingAssets'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArShouldSkipCompilingAssets() const
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipCompilingAssets"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArShouldSkipCompilingAssets' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipCompilingAssets"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArShouldSkipCompilingAssets'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FPackageFileVersion& FArchiveState::GetArUEVer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArUEVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUEVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FPackageFileVersion*>(this, offset);
}
const FPackageFileVersion& FArchiveState::GetArUEVer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArUEVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArUEVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FPackageFileVersion*>(this, offset);
}

int32& FArchiveState::GetArLicenseeUEVer()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArLicenseeUEVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArLicenseeUEVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchiveState::GetArLicenseeUEVer() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ArLicenseeUEVer"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArLicenseeUEVer' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

BitfieldProxy FArchiveState::GetArShouldSkipUpdateCustomVersion()
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipUpdateCustomVersion"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArShouldSkipUpdateCustomVersion' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipUpdateCustomVersion"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArShouldSkipUpdateCustomVersion'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArShouldSkipUpdateCustomVersion() const
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipUpdateCustomVersion"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArShouldSkipUpdateCustomVersion' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipUpdateCustomVersion"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArShouldSkipUpdateCustomVersion'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArMergeOverrides()
{
    static auto offset_it = MemberOffsets.find(STR("ArMergeOverrides"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArMergeOverrides' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArMergeOverrides"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArMergeOverrides'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArMergeOverrides() const
{
    static auto offset_it = MemberOffsets.find(STR("ArMergeOverrides"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArMergeOverrides' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArMergeOverrides"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArMergeOverrides'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FArchiveSavePackageData*& FArchiveState::GetSavePackageData()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SavePackageData"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::SavePackageData' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FArchiveSavePackageData**>(this, offset);
}
const FArchiveSavePackageData*& FArchiveState::GetSavePackageData() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("SavePackageData"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::SavePackageData' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FArchiveSavePackageData**>(this, offset);
}

BitfieldProxy FArchiveState::GetArPreserveArrayElements()
{
    static auto offset_it = MemberOffsets.find(STR("ArPreserveArrayElements"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArPreserveArrayElements' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArPreserveArrayElements"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArPreserveArrayElements'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArPreserveArrayElements() const
{
    static auto offset_it = MemberOffsets.find(STR("ArPreserveArrayElements"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArPreserveArrayElements' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArPreserveArrayElements"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArPreserveArrayElements'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchiveState::GetArIsSavingOptionalObject()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSavingOptionalObject"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsSavingOptionalObject' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSavingOptionalObject"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsSavingOptionalObject'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchiveState::GetArIsSavingOptionalObject() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSavingOptionalObject"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchiveState::ArIsSavingOptionalObject' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSavingOptionalObject"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchiveState::ArIsSavingOptionalObject'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32_t& FArchiveState::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

