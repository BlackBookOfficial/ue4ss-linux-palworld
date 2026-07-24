#include <Unreal/FArchive.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    std::unordered_map<File::StringType, uint32_t> FArchiveState::VTableLayoutMap;
    std::unordered_map<File::StringType, uint32_t> FArchive::VTableLayoutMap;

    #include <MemberVariableLayout_SrcWrapper_FArchiveState.hpp>
    #include <MemberVariableLayout_SrcWrapper_FArchive.hpp>

    /*-----------------------------------------------------------------------------
        FArchiveState virtual function implementations.
    -----------------------------------------------------------------------------*/

    FArchiveState* FArchiveState::GetInnermostState() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, GetInnermostState, FArchiveState*)
    }

    void FArchiveState::CountBytes(SIZE_T InNum, SIZE_T InMax) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, CountBytes, void, PARAMS(SIZE_T, SIZE_T), ARGS(InNum, InMax))
    }

    const TCHAR* FArchiveState::GetArchiveName() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, GetArchiveName, const TCHAR*)
    }

    ULinkerLoad* FArchiveState::GetLinker() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, GetLinker, ULinkerLoad*)
    }

    int64 FArchiveState::Tell() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, Tell, int64)
    }

    int64 FArchiveState::TotalSize() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, TotalSize, int64)
    }

    bool FArchiveState::AtEnd() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, AtEnd, bool)
    }

    UObject* FArchiveState::GetArchetypeFromLoader(const UObject* Obj) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, GetArchetypeFromLoader, UObject*, PARAMS(const UObject*), ARGS(Obj))
    }

    uint32 FArchiveState::EngineNetVer() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, EngineNetVer, uint32)
    }

    uint32 FArchiveState::GameNetVer() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, GameNetVer, uint32)
    }

    FCustomVersionContainer& FArchiveState::GetCustomVersions() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, GetCustomVersions, FCustomVersionContainer&)
    }

    void FArchiveState::SetCustomVersions(const FCustomVersionContainer& CustomVersions) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetCustomVersions, void, PARAMS(const FCustomVersionContainer&), ARGS(CustomVersions))
    }

    void FArchiveState::ResetCustomVersions() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, ResetCustomVersions, void)
    }

    void FArchiveState::SetFilterEditorOnly(bool InFilterEditorOnly) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetFilterEditorOnly, void, PARAMS(bool), ARGS(InFilterEditorOnly))
    }

    bool FArchiveState::UseToResolveEnumerators() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, UseToResolveEnumerators, bool)
    }

    bool FArchiveState::ShouldSkipProperty(const FProperty* InProperty) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, ShouldSkipProperty, bool, PARAMS(const FProperty*), ARGS(InProperty))
    }

    void FArchiveState::SetSerializedProperty(FProperty* InProperty) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetSerializedProperty, void, PARAMS(FProperty*), ARGS(InProperty))
    }

    void FArchiveState::SetSerializedPropertyChain(const FCustomPropertyListNode* InPropertyChain) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetSerializedPropertyChain, void, PARAMS(const FCustomPropertyListNode*), ARGS(InPropertyChain))
    }

    void FArchiveState::SetSerializeContext(FStructuredArchive* InStructuredArchive) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetSerializeContext, void, PARAMS(FStructuredArchive*), ARGS(InStructuredArchive))
    }

    FStructuredArchive* FArchiveState::GetSerializeContext() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, GetSerializeContext, FStructuredArchive*)
    }

    void FArchiveState::Reset() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchiveState, Reset, void)
    }

    void FArchiveState::SetIsLoading(bool bInIsLoading) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetIsLoading, void, PARAMS(bool), ARGS(bInIsLoading))
    }

    void FArchiveState::SetIsLoadingFromCookedPackage(bool bInIsLoadingFromCookedPackage) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetIsLoadingFromCookedPackage, void, PARAMS(bool), ARGS(bInIsLoadingFromCookedPackage))
    }

    void FArchiveState::SetIsSaving(bool bInIsSaving) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetIsSaving, void, PARAMS(bool), ARGS(bInIsSaving))
    }

    void FArchiveState::SetIsTransacting(bool bInIsTransacting) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetIsTransacting, void, PARAMS(bool), ARGS(bInIsTransacting))
    }

    void FArchiveState::SetIsTextFormat(bool bInIsTextFormat) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetIsTextFormat, void, PARAMS(bool), ARGS(bInIsTextFormat))
    }

    void FArchiveState::SetWantBinaryPropertySerialization(bool bInWantBinarySerialization) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetWantBinaryPropertySerialization, void, PARAMS(bool), ARGS(bInWantBinarySerialization))
    }

    void FArchiveState::SetUseUnversionedPropertySerialization(bool bInUseUnversioned) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetUseUnversionedPropertySerialization, void, PARAMS(bool), ARGS(bInUseUnversioned))
    }

    void FArchiveState::SetForceUnicode(bool bInForceUnicode) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetForceUnicode, void, PARAMS(bool), ARGS(bInForceUnicode))
    }

    void FArchiveState::SetIsPersistent(bool bInIsPersistent) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetIsPersistent, void, PARAMS(bool), ARGS(bInIsPersistent))
    }

    void FArchiveState::SetUEVer(int32 InVer) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetUEVer, void, PARAMS(int32), ARGS(InVer))
    }

    void FArchiveState::SetLicenseeUEVer(int32 InVer) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetLicenseeUEVer, void, PARAMS(int32), ARGS(InVer))
    }

    void FArchiveState::SetEngineVer(const FEngineVersionBase& InVer) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetEngineVer, void, PARAMS(const FEngineVersionBase&), ARGS(InVer))
    }

    void FArchiveState::SetEngineNetVer(uint32 InVer) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetEngineNetVer, void, PARAMS(uint32), ARGS(InVer))
    }

    void FArchiveState::SetGameNetVer(uint32 InVer) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchiveState, SetGameNetVer, void, PARAMS(uint32), ARGS(InVer))
    }

    /*-----------------------------------------------------------------------------
        FArchive virtual function implementations.
    -----------------------------------------------------------------------------*/

    FArchive& FArchive::operator<<(class FName& Value) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, operator<<, FArchive&, PARAMS(FName&), ARGS(Value))
    }

    void FArchive::ForceBlueprintFinalization() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchive, ForceBlueprintFinalization, void)
    }

    void FArchive::Serialize(void* V, int64 Length) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, Serialize, void, PARAMS(void*, int64), ARGS(V, Length))
    }

    void FArchive::SerializeBits(void* Bits, int64 LengthBits) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, SerializeBits, void, PARAMS(void*, int64), ARGS(Bits, LengthBits))
    }

    void FArchive::SerializeInt(uint32& Value, uint32 Max) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, SerializeInt, void, PARAMS(uint32&, uint32), ARGS(Value, Max))
    }

    void FArchive::SerializeIntPacked(uint32& Value) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, SerializeIntPacked, void, PARAMS(uint32&), ARGS(Value))
    }

    int64 FArchive::SerializeIntPacked64(int64& Value) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, SerializeIntPacked64, int64, PARAMS(int64&), ARGS(Value))
    }

    void FArchive::Preload(UObject* Object) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, Preload, void, PARAMS(UObject*), ARGS(Object))
    }

    void FArchive::Seek(int64 InPos) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, Seek, void, PARAMS(int64), ARGS(InPos))
    }

    void FArchive::AttachBulkData(UObject* Owner, FUntypedBulkData* BulkData) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, AttachBulkData, void, PARAMS(UObject*, FUntypedBulkData*), ARGS(Owner, BulkData))
    }

    void FArchive::DetachBulkData(FUntypedBulkData* BulkData, bool bEnsureBulkDataIsLoaded) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, DetachBulkData, void, PARAMS(FUntypedBulkData*, bool), ARGS(BulkData, bEnsureBulkDataIsLoaded))
    }

    bool FArchive::SerializeBulkData(FUntypedBulkData& BulkData, const FBulkDataSerializationParams& Params) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, SerializeBulkData, bool, PARAMS(FUntypedBulkData&, const FBulkDataSerializationParams&), ARGS(BulkData, Params))
    }

    bool FArchive::IsProxyOf(FArchive* InOther) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, IsProxyOf, bool, PARAMS(FArchive*), ARGS(InOther))
    }

    void FArchive::Precache(int64 PrecacheOffset, int64 PrecacheSize) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, Precache, void, PARAMS(int64, int64), ARGS(PrecacheOffset, PrecacheSize))
    }

    void FArchive::FlushCache() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchive, FlushCache, void)
    }

    bool FArchive::SetCompressionMap(TArray<FCompressedChunk>* CompressedChunks, uint32 CompressionFlags) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, SetCompressionMap, bool, PARAMS(TArray<FCompressedChunk>*, uint32), ARGS(CompressedChunks, CompressionFlags))
    }

    bool FArchive::Flush() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchive, Flush, bool)
    }

    bool FArchive::Close() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchive, Close, bool)
    }

    void FArchive::MarkScriptSerializationStart(const UObject* Object) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, MarkScriptSerializationStart, void, PARAMS(const UObject*), ARGS(Object))
    }

    void FArchive::MarkScriptSerializationEnd(const UObject* Object) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, MarkScriptSerializationEnd, void, PARAMS(const UObject*), ARGS(Object))
    }

    void FArchive::MarkSearchableName(const UObject* TypeObject, const FName& ValueName) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, MarkSearchableName, void, PARAMS(const UObject*, const FName&), ARGS(TypeObject, ValueName))
    }

    void FArchive::UsingCustomVersion(const FGuid& Key) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, UsingCustomVersion, void, PARAMS(const FGuid&), ARGS(Key))
    }

    FArchive* FArchive::GetCacheableArchive() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchive, GetCacheableArchive, FArchive*)
    }

    void FArchive::PushSerializedProperty(FProperty* InProperty, const bool bIsEditorOnlyProperty) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, PushSerializedProperty, void, PARAMS(FProperty*, const bool), ARGS(InProperty, bIsEditorOnlyProperty))
    }

    void FArchive::PopSerializedProperty(FProperty* InProperty, const bool bIsEditorOnlyProperty) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, PopSerializedProperty, void, PARAMS(FProperty*, const bool), ARGS(InProperty, bIsEditorOnlyProperty))
    }

    void FArchive::AttachExternalReadDependency(FExternalReadCallback& ReadCallback) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, AttachExternalReadDependency, void, PARAMS(FExternalReadCallback&), ARGS(ReadCallback))
    }

    void FArchive::PushFileRegionType(uint32 Type) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FArchive, PushFileRegionType, void, PARAMS(uint32), ARGS(Type))
    }

    void FArchive::PopFileRegionType() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FArchive, PopFileRegionType, void)
    }
}
