std::unordered_map<File::StringType, int32_t> UDataTable::MemberOffsets{};
std::unordered_map<File::StringType, BitfieldInfo> UDataTable::BitfieldInfos{};

TObjectPtr<UScriptStruct>& UDataTable::GetRowStruct()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RowStruct"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::RowStruct' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TObjectPtr<UScriptStruct>*>(this, offset);
}
const TObjectPtr<UScriptStruct>& UDataTable::GetRowStruct() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RowStruct"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::RowStruct' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TObjectPtr<UScriptStruct>*>(this, offset);
}

TMap<FName, unsigned char *>& UDataTable::GetRowMap()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RowMap"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::RowMap' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<TMap<FName, unsigned char *>*>(this, offset);
}
const TMap<FName, unsigned char *>& UDataTable::GetRowMap() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("RowMap"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::RowMap' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const TMap<FName, unsigned char *>*>(this, offset);
}

BitfieldProxy UDataTable::GetbStripFromClientBuilds()
{
    static auto offset_it = MemberOffsets.find(STR("bStripFromClientBuilds"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bStripFromClientBuilds' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStripFromClientBuilds"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bStripFromClientBuilds'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UDataTable::GetbStripFromClientBuilds() const
{
    static auto offset_it = MemberOffsets.find(STR("bStripFromClientBuilds"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bStripFromClientBuilds' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bStripFromClientBuilds"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bStripFromClientBuilds'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UDataTable::GetbIgnoreExtraFields()
{
    static auto offset_it = MemberOffsets.find(STR("bIgnoreExtraFields"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bIgnoreExtraFields' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIgnoreExtraFields"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bIgnoreExtraFields'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UDataTable::GetbIgnoreExtraFields() const
{
    static auto offset_it = MemberOffsets.find(STR("bIgnoreExtraFields"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bIgnoreExtraFields' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIgnoreExtraFields"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bIgnoreExtraFields'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

BitfieldProxy UDataTable::GetbIgnoreMissingFields()
{
    static auto offset_it = MemberOffsets.find(STR("bIgnoreMissingFields"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bIgnoreMissingFields' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIgnoreMissingFields"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bIgnoreMissingFields'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UDataTable::GetbIgnoreMissingFields() const
{
    static auto offset_it = MemberOffsets.find(STR("bIgnoreMissingFields"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bIgnoreMissingFields' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bIgnoreMissingFields"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bIgnoreMissingFields'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

FString& UDataTable::GetImportKeyField()
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ImportKeyField"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::ImportKeyField' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<FString*>(this, offset);
}
const FString& UDataTable::GetImportKeyField() const
{
    static const int32_t offset = []() -> int32_t {
        auto offset_it = MemberOffsets.find(STR("ImportKeyField"));
        if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::ImportKeyField' that doesn't exist in this engine version."}; }
        return offset_it->second;
    }();
    return *Helper::Casting::ptr_cast<const FString*>(this, offset);
}

BitfieldProxy UDataTable::GetbPreserveExistingValues()
{
    static auto offset_it = MemberOffsets.find(STR("bPreserveExistingValues"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bPreserveExistingValues' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPreserveExistingValues"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bPreserveExistingValues'."}; }
    auto& info = bitfield_it->second;
    return BitfieldProxy(Helper::Casting::ptr_cast<void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}
ConstBitfieldProxy UDataTable::GetbPreserveExistingValues() const
{
    static auto offset_it = MemberOffsets.find(STR("bPreserveExistingValues"));
    if (offset_it == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UDataTable::bPreserveExistingValues' that doesn't exist in this engine version."}; }
    static auto bitfield_it = BitfieldInfos.find(STR("bPreserveExistingValues"));
    if (bitfield_it == BitfieldInfos.end()) { throw std::runtime_error{"Bitfield info not found for 'UDataTable::bPreserveExistingValues'."}; }
    auto& info = bitfield_it->second;
    return ConstBitfieldProxy(Helper::Casting::ptr_cast<const void*>(this, offset_it->second), info.bit_pos, info.bit_len, info.storage_size);
}

int32_t& UDataTable::UEP_TotalSize()
{
    static int32_t cached = []() {
        auto it = MemberOffsets.find(STR("UEP_TotalSize"));
        return it != MemberOffsets.end() ? it->second : -1;
    }();
    return cached;
}

