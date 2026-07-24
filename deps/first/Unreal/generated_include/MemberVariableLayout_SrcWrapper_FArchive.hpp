std::unordered_map<File::StringType, int32_t> FArchive::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> FArchive::BitfieldInfos{};

int32& FArchive::GetArNetVer()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArNetVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArNetVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArNetVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchive::GetArNetVer() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArNetVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArNetVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArNetVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& FArchive::GetArUE4Ver()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArUE4Ver"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArUE4Ver"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArUE4Ver' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchive::GetArUE4Ver() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArUE4Ver"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArUE4Ver"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArUE4Ver' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

int32& FArchive::GetArLicenseeUE4Ver()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArLicenseeUE4Ver"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArLicenseeUE4Ver"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArLicenseeUE4Ver' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchive::GetArLicenseeUE4Ver() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArLicenseeUE4Ver"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArLicenseeUE4Ver"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArLicenseeUE4Ver' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

FEngineVersionBase& FArchive::GetArEngineVer()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArEngineVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArEngineVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArEngineVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FEngineVersionBase*>(this, offset);
}
const FEngineVersionBase& FArchive::GetArEngineVer() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArEngineVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArEngineVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArEngineVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FEngineVersionBase*>(this, offset);
}

FCustomVersionContainer*& FArchive::GetCustomVersionContainer()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("CustomVersionContainer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("CustomVersionContainer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::CustomVersionContainer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FCustomVersionContainer**>(this, offset);
}
const FCustomVersionContainer*& FArchive::GetCustomVersionContainer() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("CustomVersionContainer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("CustomVersionContainer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::CustomVersionContainer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FCustomVersionContainer**>(this, offset);
}

BitfieldProxy FArchive::GetArIsLoading()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsLoading'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsLoading() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsLoading'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsSaving()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaving"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsSaving' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaving"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsSaving'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsSaving() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaving"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsSaving' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaving"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsSaving'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsTransacting()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTransacting"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsTransacting' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTransacting"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsTransacting'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsTransacting() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTransacting"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsTransacting' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTransacting"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsTransacting'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArWantBinaryPropertySerialization()
{
    static auto offset_it = MemberOffsets.find(STR("ArWantBinaryPropertySerialization"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArWantBinaryPropertySerialization' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArWantBinaryPropertySerialization"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArWantBinaryPropertySerialization'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArWantBinaryPropertySerialization() const
{
    static auto offset_it = MemberOffsets.find(STR("ArWantBinaryPropertySerialization"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArWantBinaryPropertySerialization' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArWantBinaryPropertySerialization"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArWantBinaryPropertySerialization'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArForceUnicode()
{
    static auto offset_it = MemberOffsets.find(STR("ArForceUnicode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArForceUnicode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceUnicode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArForceUnicode'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArForceUnicode() const
{
    static auto offset_it = MemberOffsets.find(STR("ArForceUnicode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArForceUnicode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceUnicode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArForceUnicode'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsPersistent()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsPersistent"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsPersistent' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsPersistent"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsPersistent'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsPersistent() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsPersistent"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsPersistent' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsPersistent"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsPersistent'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsError()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsError'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsError() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsError'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsCriticalError()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCriticalError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsCriticalError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCriticalError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsCriticalError'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsCriticalError() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCriticalError"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsCriticalError' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCriticalError"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsCriticalError'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArContainsCode()
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsCode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArContainsCode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsCode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArContainsCode'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArContainsCode() const
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsCode"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArContainsCode' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsCode"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArContainsCode'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArContainsMap()
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsMap"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArContainsMap' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsMap"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArContainsMap'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArContainsMap() const
{
    static auto offset_it = MemberOffsets.find(STR("ArContainsMap"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArContainsMap' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArContainsMap"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArContainsMap'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArRequiresLocalizationGather()
{
    static auto offset_it = MemberOffsets.find(STR("ArRequiresLocalizationGather"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArRequiresLocalizationGather' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArRequiresLocalizationGather"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArRequiresLocalizationGather'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArRequiresLocalizationGather() const
{
    static auto offset_it = MemberOffsets.find(STR("ArRequiresLocalizationGather"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArRequiresLocalizationGather' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArRequiresLocalizationGather"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArRequiresLocalizationGather'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArForceByteSwapping()
{
    static auto offset_it = MemberOffsets.find(STR("ArForceByteSwapping"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArForceByteSwapping' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceByteSwapping"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArForceByteSwapping'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArForceByteSwapping() const
{
    static auto offset_it = MemberOffsets.find(STR("ArForceByteSwapping"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArForceByteSwapping' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArForceByteSwapping"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArForceByteSwapping'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIgnoreArchetypeRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreArchetypeRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreArchetypeRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreArchetypeRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreArchetypeRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIgnoreArchetypeRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreArchetypeRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreArchetypeRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreArchetypeRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreArchetypeRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArNoDelta()
{
    static auto offset_it = MemberOffsets.find(STR("ArNoDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArNoDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArNoDelta'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArNoDelta() const
{
    static auto offset_it = MemberOffsets.find(STR("ArNoDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArNoDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArNoDelta'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIgnoreOuterRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreOuterRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreOuterRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreOuterRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreOuterRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIgnoreOuterRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreOuterRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreOuterRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreOuterRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreOuterRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIgnoreClassGeneratedByRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreClassGeneratedByRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassGeneratedByRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreClassGeneratedByRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIgnoreClassGeneratedByRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassGeneratedByRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreClassGeneratedByRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassGeneratedByRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreClassGeneratedByRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIgnoreClassRef()
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreClassRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreClassRef'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIgnoreClassRef() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIgnoreClassRef"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIgnoreClassRef' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIgnoreClassRef"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIgnoreClassRef'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArAllowLazyLoading()
{
    static auto offset_it = MemberOffsets.find(STR("ArAllowLazyLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArAllowLazyLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArAllowLazyLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArAllowLazyLoading'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArAllowLazyLoading() const
{
    static auto offset_it = MemberOffsets.find(STR("ArAllowLazyLoading"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArAllowLazyLoading' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArAllowLazyLoading"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArAllowLazyLoading'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsObjectReferenceCollector()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsObjectReferenceCollector"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsObjectReferenceCollector' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsObjectReferenceCollector"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsObjectReferenceCollector'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsObjectReferenceCollector() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsObjectReferenceCollector"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsObjectReferenceCollector' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsObjectReferenceCollector"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsObjectReferenceCollector'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsModifyingWeakAndStrongReferences()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsModifyingWeakAndStrongReferences' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsModifyingWeakAndStrongReferences'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsModifyingWeakAndStrongReferences() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsModifyingWeakAndStrongReferences' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsModifyingWeakAndStrongReferences"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsModifyingWeakAndStrongReferences'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsCountingMemory()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCountingMemory"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsCountingMemory' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCountingMemory"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsCountingMemory'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsCountingMemory() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsCountingMemory"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsCountingMemory' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsCountingMemory"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsCountingMemory'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArShouldSkipBulkData()
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipBulkData"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArShouldSkipBulkData' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipBulkData"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArShouldSkipBulkData'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArShouldSkipBulkData() const
{
    static auto offset_it = MemberOffsets.find(STR("ArShouldSkipBulkData"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArShouldSkipBulkData' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArShouldSkipBulkData"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArShouldSkipBulkData'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsFilterEditorOnly()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsFilterEditorOnly"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsFilterEditorOnly' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsFilterEditorOnly"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsFilterEditorOnly'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsFilterEditorOnly() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsFilterEditorOnly"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsFilterEditorOnly' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsFilterEditorOnly"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsFilterEditorOnly'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsSaveGame()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaveGame"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsSaveGame' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaveGame"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsSaveGame'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsSaveGame() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsSaveGame"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsSaveGame' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsSaveGame"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsSaveGame'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32& FArchive::GetArSerializingDefaults()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArSerializingDefaults"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArSerializingDefaults"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArSerializingDefaults' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int32*>(this, offset);
}
const int32& FArchive::GetArSerializingDefaults() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArSerializingDefaults"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArSerializingDefaults"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArSerializingDefaults' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int32*>(this, offset);
}

uint32& FArchive::GetArPortFlags()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArPortFlags"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArPortFlags"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArPortFlags' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FArchive::GetArPortFlags() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArPortFlags"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArPortFlags"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArPortFlags' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

int64& FArchive::GetArMaxSerializeSize()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArMaxSerializeSize"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArMaxSerializeSize"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArMaxSerializeSize' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<int64*>(this, offset);
}
const int64& FArchive::GetArMaxSerializeSize() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArMaxSerializeSize"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArMaxSerializeSize"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArMaxSerializeSize' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const int64*>(this, offset);
}

const ITargetPlatform*& FArchive::GetCookingTargetPlatform()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("CookingTargetPlatform"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("CookingTargetPlatform"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::CookingTargetPlatform' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const ITargetPlatform**>(this, offset);
}
const ITargetPlatform*& FArchive::GetCookingTargetPlatform() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("CookingTargetPlatform"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("CookingTargetPlatform"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::CookingTargetPlatform' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const ITargetPlatform**>(this, offset);
}

FProperty*& FArchive::GetSerializedProperty()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("SerializedProperty"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("SerializedProperty"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::SerializedProperty' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FProperty**>(this, offset);
}
const FProperty*& FArchive::GetSerializedProperty() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("SerializedProperty"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("SerializedProperty"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::SerializedProperty' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FProperty**>(this, offset);
}

bool& FArchive::GetbCustomVersionsAreReset()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("bCustomVersionsAreReset"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("bCustomVersionsAreReset"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::bCustomVersionsAreReset' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<bool*>(this, offset);
}
const bool& FArchive::GetbCustomVersionsAreReset() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("bCustomVersionsAreReset"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("bCustomVersionsAreReset"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::bCustomVersionsAreReset' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const bool*>(this, offset);
}

const FCustomPropertyListNode*& FArchive::GetArCustomPropertyList()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArCustomPropertyList"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArCustomPropertyList"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArCustomPropertyList' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FCustomPropertyListNode**>(this, offset);
}
const FCustomPropertyListNode*& FArchive::GetArCustomPropertyList() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArCustomPropertyList"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArCustomPropertyList"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArCustomPropertyList' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FCustomPropertyListNode**>(this, offset);
}

BitfieldProxy FArchive::GetArUseCustomPropertyList()
{
    static auto offset_it = MemberOffsets.find(STR("ArUseCustomPropertyList"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArUseCustomPropertyList' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArUseCustomPropertyList"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArUseCustomPropertyList'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArUseCustomPropertyList() const
{
    static auto offset_it = MemberOffsets.find(STR("ArUseCustomPropertyList"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArUseCustomPropertyList' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArUseCustomPropertyList"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArUseCustomPropertyList'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

uint32& FArchive::GetArEngineNetVer()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArEngineNetVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArEngineNetVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArEngineNetVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FArchive::GetArEngineNetVer() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArEngineNetVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArEngineNetVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArEngineNetVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

uint32& FArchive::GetArGameNetVer()
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArGameNetVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArGameNetVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArGameNetVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<uint32*>(this, offset);
}
const uint32& FArchive::GetArGameNetVer() const
{
    static const int32_t offset = []() -> int32_t {
        static auto& primary_offsets = Version::IsBelow(4, 25) ? FArchive::MemberOffsets : FArchiveState::MemberOffsets;
        auto offset_it = primary_offsets.find(STR("ArGameNetVer"));
        if (offset_it == primary_offsets.end()) {
            // Check in the other class if member not found
            static auto& fallback_offsets = Version::IsBelow(4, 25) ? FArchiveState::MemberOffsets : FArchive::MemberOffsets;
            if (&fallback_offsets != &primary_offsets) { // Only check if different from primary
                auto fallback_offset = fallback_offsets.find(STR("ArGameNetVer"));
                if (fallback_offset != fallback_offsets.end()) {
                    return fallback_offset->second;
                }
            }
            throw std::runtime_error{"Tried getting member variable 'FArchive::ArGameNetVer' that doesn't exist in this engine version or its parent class."};
        }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const uint32*>(this, offset);
}

BitfieldProxy FArchive::GetArIsTextFormat()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTextFormat"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsTextFormat' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTextFormat"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsTextFormat'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsTextFormat() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsTextFormat"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsTextFormat' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsTextFormat"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsTextFormat'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArIsNetArchive()
{
    static auto offset_it = MemberOffsets.find(STR("ArIsNetArchive"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsNetArchive' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsNetArchive"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsNetArchive'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArIsNetArchive() const
{
    static auto offset_it = MemberOffsets.find(STR("ArIsNetArchive"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArIsNetArchive' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArIsNetArchive"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArIsNetArchive'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy FArchive::GetArNoIntraPropertyDelta()
{
    static auto offset_it = MemberOffsets.find(STR("ArNoIntraPropertyDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArNoIntraPropertyDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoIntraPropertyDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArNoIntraPropertyDelta'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy FArchive::GetArNoIntraPropertyDelta() const
{
    static auto offset_it = MemberOffsets.find(STR("ArNoIntraPropertyDelta"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FArchive::ArNoIntraPropertyDelta' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("ArNoIntraPropertyDelta"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'FArchive::ArNoIntraPropertyDelta'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32_t& FArchive::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

