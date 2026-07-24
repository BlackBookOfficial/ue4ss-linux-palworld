#pragma once

#include <unordered_map>

#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/Core/Containers/Array.hpp>

#include <Unreal/BitfieldProxy.hpp>

namespace RC::Unreal
{
    // Non-existant structs.
    struct FArchiveSavePackageData {};
    struct FCustomVersionContainer {};
    struct FEngineVersionBase {};
    struct FPackageFileVersion {};
    class ITargetPlatform {};
    struct FCompressedChunk {};
    struct FBulkDataSerializationParams {};
    struct FExternalReadCallback {};

    // Forward declarations.
    class FProperty;
    class UObject;
    class ULinkerLoad;
    class FStructuredArchive;
    class FUntypedBulkData;
    struct FCustomPropertyListNode;

    class FArchiveState
    {
    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_FArchiveState.hpp>

    public:
        FArchiveState* GetInnermostState() const;
        void CountBytes(SIZE_T InNum, SIZE_T InMax) const;
        const TCHAR* GetArchiveName() const;
        ULinkerLoad* GetLinker() const;
        int64 Tell() const;
        int64 TotalSize() const;
        bool AtEnd() const;
        UObject* GetArchetypeFromLoader(const UObject* Obj) const;
        uint32 EngineNetVer() const;
        uint32 GameNetVer() const;
        FCustomVersionContainer& GetCustomVersions() const;
        void SetCustomVersions(const FCustomVersionContainer& CustomVersions) const;
        void ResetCustomVersions() const;
        void SetFilterEditorOnly(bool InFilterEditorOnly) const;
        bool UseToResolveEnumerators() const;
        bool ShouldSkipProperty(const FProperty* InProperty) const;
        void SetSerializedProperty(FProperty* InProperty) const;
        void SetSerializedPropertyChain(const FCustomPropertyListNode* InPropertyChain) const;
        void SetSerializeContext(FStructuredArchive* InStructuredArchive) const;
        FStructuredArchive* GetSerializeContext() const;
        void Reset() const;
        void SetIsLoading(bool bInIsLoading) const;
        void SetIsLoadingFromCookedPackage(bool bInIsLoadingFromCookedPackage) const;
        void SetIsSaving(bool bInIsSaving) const;
        void SetIsTransacting(bool bInIsTransacting) const;
        void SetIsTextFormat(bool bInIsTextFormat) const;
        void SetWantBinaryPropertySerialization(bool bInWantBinarySerialization) const;
        void SetUseUnversionedPropertySerialization(bool bInUseUnversioned) const;
        void SetForceUnicode(bool bInForceUnicode) const;
        void SetIsPersistent(bool bInIsPersistent) const;
        void SetUEVer(int32 InVer) const;
        void SetLicenseeUEVer(int32 InVer) const;
        void SetEngineVer(const FEngineVersionBase& InVer) const;
        void SetEngineNetVer(uint32 InVer) const;
        void SetGameNetVer(uint32 InVer) const;
    };

    class FArchive : public FArchiveState
    {
    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_FArchive.hpp>

    public:
        /** Returns true if this archive is for loading data. */
        FORCEINLINE bool IsLoading() const
        {
            return GetArIsLoading();
        }

        /** Returns true if this archive is loading from a cooked package. */
        FORCEINLINE bool IsLoadingFromCookedPackage() const
        {
            return GetArIsLoadingFromCookedPackage();
        }

        /** Returns true if this archive is for saving data, this can also be a pre-save preparation archive. */
        FORCEINLINE bool IsSaving() const
        {
            return GetArIsSaving();
        }

        /** Returns true if this archive should modify/search weak object references as well as strong ones. */
        FORCEINLINE bool IsModifyingWeakAndStrongReferences() const
        {
            return GetArIsModifyingWeakAndStrongReferences();
        }
        
        FArchive& operator<<(FName& Value) const;
        void ForceBlueprintFinalization() const;
        void Serialize(void* V, int64 Length) const;
        void SerializeBits(void* Bits, int64 LengthBits) const;
        void SerializeInt(uint32& Value, uint32 Max) const;
        void SerializeIntPacked(uint32& Value) const;
        int64 SerializeIntPacked64(int64& Value) const;
        void Preload(UObject* Object) const;
        void Seek(int64 InPos) const;
        void AttachBulkData(UObject* Owner, FUntypedBulkData* BulkData) const;
        void DetachBulkData(FUntypedBulkData* BulkData, bool bEnsureBulkDataIsLoaded) const;
        bool SerializeBulkData(FUntypedBulkData& BulkData, const FBulkDataSerializationParams& Params) const;
        bool IsProxyOf(FArchive* InOther) const;
        void Precache(int64 PrecacheOffset, int64 PrecacheSize) const;
        void FlushCache() const;
        bool SetCompressionMap(TArray<FCompressedChunk>* CompressedChunks, uint32 CompressionFlags) const;
        bool Flush() const;
        bool Close() const;
        void MarkScriptSerializationStart(const UObject* Object) const;
        void MarkScriptSerializationEnd(const UObject* Object) const;
        void MarkSearchableName(const UObject* TypeObject, const FName& ValueName) const;
        void UsingCustomVersion(const FGuid& Key) const;
        FArchive* GetCacheableArchive() const;
        void PushSerializedProperty(FProperty* InProperty, const bool bIsEditorOnlyProperty) const;
        void PopSerializedProperty(FProperty* InProperty, const bool bIsEditorOnlyProperty) const;
        void AttachExternalReadDependency(FExternalReadCallback& ReadCallback) const;
        void PushFileRegionType(uint32 Type) const;
        void PopFileRegionType() const;
    };
}


