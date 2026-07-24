#pragma once

#include <stdexcept>

#include <File/File.hpp>
#include <Function/Function.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/UObjectArray.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/VersionedContainer/Container.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/UnrealFlags.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/UObjectMacros.hpp>
#include <Unreal/TObjectPtr.hpp>
#include <Unreal/FArchive.hpp>
#include <Unreal/FPrimaryAssetId.hpp>

#include <String/StringType.hpp>

#include "Containers/Map.hpp"

#define SUBOBJECT_DELIMITER_CHAR ':'

namespace RC::Unreal
{
    class UObject;
    struct FFrame;

    namespace UnrealInitializer
    {
        struct CacheInfo;
        RC_UE_API auto CreateCache(CacheInfo&) -> void;
        RC_UE_API auto LoadCache(CacheInfo&) -> void;
    }

    // Placeholder types for virtual functions
    // TODO: Remove when they are implemented
    using FRestoreForUObjectOverwrite = void*;
    using FObjectDuplicationParameters = void*;
    using FResourceSizeEx = void*;
    using FAssetRegistryTag = void*;

    class RC_UE_API UObjectBase
    {
    private:
        friend class FUObjectCreateListener;
        friend class FUObjectDeleteListener;

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_UObjectBase.hpp>

        // Pulled out of the HeaderWrapper because we need a custom check before we return the index.
        // Temporary fix for Kingdom Hearts 3.
        // Used to get access to the exe name so that we can apply the fix only to KH3.
        // TODO: See if there's some way to tell the compiler to only compile the function if it doesn't already exist.
        //       That would make these sorts of changes much easier to deal with in the future.
        int32 GetInternalIndex();
        const int32 GetInternalIndex() const;

    public:
        // Wrappers for virtual engine functions
        auto RegisterDependencies() -> void;
        auto DeferredRegister(class UClass* UClassStaticClass, const File::CharType* PackageName, const File::CharType* Name) -> void;

    public:
        auto GetObjectItem() const -> const struct FUObjectItem*;
        auto GetObjectItem() -> struct FUObjectItem*;

        /**
         * Checks whenever this object is an instance of the specified class
         */
        auto IsA(UClass* Class) const -> bool;
        auto IsA(const UClass* Class) const -> bool;

        /**
         * Templated version of the IsA(UClass*) function
         */
        template<UObjectDerivative T>
        inline auto IsA() const -> bool
        {
            return IsA(T::StaticClass());
        }

        /**
         * Allocates a UObjectBase from the free store or the permanent object pool
         *
         * @param Size size of uobject to allocate
         * @param Alignment alignment of uobject to allocate
         * @param bAllowPermanent if true, allow allocation in the permanent object pool, if it fits
         * @return newly allocated UObjectBase (not really a UObjectBase yet, no constructor like thing has been called).
         */
        inline static UObjectBase* AllocateUObject(int32 Size, int32 Alignment, bool bAllowPermanent)
        {
            if (bAllowPermanent)
            {
                Output::send<LogLevel::Error>(STR("Allocating to permanent storage is not currently supported. Allocating with standard Malloc instead.\n"));
            }
            void* Result = FMemory::Malloc(Size, Alignment);
            return (UObjectBase*)Result;
        };
    };

    class RC_UE_API UObjectBaseUtility : public UObjectBase
    {
    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
        // Wrappers for virtual engine functions
        auto CanBeClusterRoot() const -> bool;
        auto CanBeInCluster() const -> bool;
        auto CreateCluster() -> void;
        auto OnClusterMarkedAsPendingKill() -> void;
    };

    class RC_UE_API UObject : public UObjectBaseUtility
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UObject, CoreUObject);

    public:
        using ProcessEventSignature = void(UObject* Context, class UFunction* Function, void* Params);
        static Function<ProcessEventSignature> ProcessEventInternal;

        using ProcessConsoleExecSignature = bool(UObject* Context, const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor);
        static Function<ProcessConsoleExecSignature> ProcessConsoleExecInternal;

        using ProcessInternalSignature = void(UObject* Context, FFrame& Stack, void* RESULT_DECL);
        static Function<ProcessInternalSignature> ProcessInternalInternal;

        using ProcessLocalScriptFunctionSignature = void(UObject* Context, FFrame& Stack, void* RESULT_DECL);
        static Function<ProcessLocalScriptFunctionSignature> ProcessLocalScriptFunctionInternal;

        using CallFunctionByNameWithArgumentsSignature = bool(UObject* Context, const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec);
        static Function<CallFunctionByNameWithArgumentsSignature> CallFunctionByNameWithArgumentsInternal;
    protected:
        friend RC_UE_API void UnrealInitializer::CreateCache(UnrealInitializer::CacheInfo&);
        friend RC_UE_API void UnrealInitializer::LoadCache(UnrealInitializer::CacheInfo&);
        friend RC_UE_API void HookProcessEvent();
        friend struct FWeakObjectPtr;
        friend class AActor;
        friend class UAssetRegistry;

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

        // Wrappers for virtual engine functions
        FString GetDetailedInfoInternal() const;
        void PostInitProperties();
        void PostCDOContruct();
        bool PreSaveRoot(const TCHAR* Filename);
        void PostSaveRoot(bool bCleanupIsRequired);
        void PreSave(const class ITargetPlatform* TargetPlatform);
        bool IsReadyForAsyncPostLoad() const;
        void PostLoad();
        void PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph);
        void BeginDestroy();
        bool IsReadyForFinishDestroy();
        void FinishDestroy();
        // Implement this when the vtable offset generator supports multiple functions with the same name
        class FStructuredArchive { public: enum class FRecord {}; };
        void Serialize(FStructuredArchive::FRecord Record);
        void Serialize(FArchive& Ar);
        void ShutdownAfterError();
        void PostInterpChange(class FProperty* PropertyThatChanged);
        void PostRename(UObject* OldOuter, const FName OldName);
        void PreDuplicate(FObjectDuplicationParameters& DupParams);
        void PostDuplicate(bool bDuplicateForPIE);
        // Implement this when the vtable offset generator supports multiple functions with the same name
        //void PostDuplicate(EDuplicateMode::Type DuplicateMode);
        bool NeedsLoadForClient() const;
        bool NeedsLoadForServer() const;
        bool NeedsLoadForTargetPlatform(const class ITargetPlatform* TargetPlatform) const;
        bool NeedsLoadForEditorGame() const;
        bool IsEditorOnly() const;
        bool IsPostLoadThreadSafe() const;
        bool IsDestructionThreadSafe() const;
        void GetPreloadDependencies(TArray<UObject*>& OutDeps);
        void GetPrestreamPackages(TArray<UObject*>& OutPrestream);
        void ExportCustomProperties(FOutputDevice& Out, uint32 Indent);
        void ImportCustomProperties(const TCHAR* SourceText, class FFeedbackContext* Warn);
        void PostEditImport();
        void PostReloadConfig(class FProperty* PropertyThatWasLoaded);
        bool Rename(const TCHAR* NewName=nullptr, UObject* NewOuter=nullptr, ERenameFlags Flags=REN_None);
        FString GetDesc();
        class UScriptStruct* GetSparseClassDataStruct() const;
        class UWorld* GetWorld() const;
        bool GetNativePropertyValues(TMap<FString, FString>& out_PropertyValues, uint32 ExportFlags=0) const;
        void GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize);
        FName GetExporterName();
        FRestoreForUObjectOverwrite* GetRestoreForUObjectOverwrite();
        bool AreNativePropertiesIdenticalTo(UObject* Other) const;
        void GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const;
        bool IsAsset() const;
        FPrimaryAssetId GetPrimaryAssetId() const;
        bool IsLocalizedResource() const;
        bool IsSafeForRootSet() const;
        void TagSubobjects(EObjectFlags NewFlags);
        void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const;
        bool IsNameStableForNetworking() const;
        bool IsFullNameStableForNetworking() const;
        bool IsSupportedForNetworking() const;
        void GetSubobjectsWithStableNamesForNetworking(TArray<UObject*>& ObjList);
        void PreNetReceive();
        void PostNetReceive();
        void PostRepNotifies();
        void PreDestroyFromReplication();
        void BuildSubobjectMapping(UObject* OtherObject, TMap<UObject*, UObject*>& ObjectMapping) const;
        const TCHAR* GetConfigOverridePlatform() const;
        void OverridePerObjectConfigSection(FString& SectionName);
        void ProcessEvent(UFunction* Function, void* Parms);
        int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack);
        bool CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack);
        bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor);
        UClass* RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO);
        void MarkAsEditorOnlySubobject();
        bool CheckDefaultSubobjectsInternal() const;
        void ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const;
        void SetNetPushIdDynamic(const int32 NewNetPushId);
        int32 GetNetPushIdDynamic() const;

    public:
        /**
         * Updates the flags currently set on the object to the provided ones
         * This function overwrites the flags completely, use set_flags or clear_flags to
         * add or remove flags instead
         */
        auto SetFlagsTo(EObjectFlags NewFlags) -> void;

        /**
         * Returns the name of this object, as string
         */
        inline auto GetName() const -> StringType
        {
            return GetNamePrivate().ToString();
        }

        /** Returns the logical name of this object */
        FORCEINLINE FName GetFName() const
        {
            return GetNamePrivate();
        }

        /**
         * Adds new flags to the object
         */
        inline auto SetFlags(EObjectFlags NewFlags) -> void
        {
            Container::UnrealObjectVC->UObject_set_flags(this, NewFlags);
        }

        /**
         * Removes the provided flags from the object
         */
        inline auto ClearFlags(EObjectFlags ClearFlags) -> void
        {
            Container::UnrealObjectVC->UObject_clear_flags(this, ClearFlags);
        }

        /**
         * Checks whenever the object has any of the provided flags set
         */
        inline auto HasAnyFlags(EObjectFlags FlagsToCheck) -> bool
        {
            return Container::UnrealObjectVC->UObject_has_any_flag(this, FlagsToCheck);
        }

        /**
         * Checks whenever the object has all of the flags specified
         */
        auto HasAllFlags(EObjectFlags FlagsToCheck) -> bool
        {
            return Container::UnrealObjectVC->UObject_has_all_flags(this, FlagsToCheck);
        }

        bool HasAnyInternalFlags(EInternalObjectFlags FlagsToCheck)
        {
            return FUObjectArray::IndexToObject(GetInternalIndex())->HasAnyFlags(FlagsToCheck);
        }

        bool IsUnreachable()
        {
            return UObjectArray::IndexToObject(GetInternalIndex())->IsUnreachable();
        }

        void SetRootSet()
        {
            UObjectArray::IndexToObject(GetInternalIndex())->SetRootSet();
        }


        void ClearRootSet()
        {
            UObjectArray::IndexToObject(GetInternalIndex())->UnsetRootSet();
        }

        bool IsRootSet()
        {
            return FUObjectArray::IndexToObject(GetInternalIndex())->IsRootSet();
        }

        /**
         * Returns the outermost object for this object, normally the returned
         * object will always represent the UPackage instance
         */
        auto GetOutermost() -> UObject*;

        /**
         * Returns the first outer of the object that is a subclass of the provided type
         */
        auto GetTypedOuter(UClass* OuterType) -> UObject*;

         /**
          * Templated version of the get_typed_outer function above,
          * returns the object already casted to the provided type too
          */
         template<UObjectDerivative T>
         auto GetTypedOuter() -> T*
         {
              return Cast<T>(GetTypedOuter(T::StaticClass()));
         }

        /**
         * Returns the full path to the object in form of Package.Outer:ObjectName
         * Safe to call on the NULL objects and will return None in that case
         */
        auto GetPathName(UObject* StopOuter = nullptr) const -> StringType;

        /**
         * Returns the full name of the object in form Class Package.Outer:ObjectName
         */
        auto GetFullName(UObject* StopOuter = nullptr) const -> StringType;

        auto GetPathName(UObject* StopOuter, StringType& ResultString) const -> void;

        size_t HashObject();
        size_t HashObject() const;

        void* GetValuePtrByPropertyName(const TCHAR*);

        template<UObjectPointerDerivativeOrAnyNonUObject ReturnType>
        ReturnType* GetValuePtrByPropertyName(const TCHAR* PropertyName)
        {
            return static_cast<ReturnType*>(GetValuePtrByPropertyName(PropertyName));
        }

        void* GetValuePtrByPropertyName(FName);

        template<UObjectPointerDerivativeOrAnyNonUObject ReturnType>
        ReturnType* GetValuePtrByPropertyName(FName PropertyName)
        {
            return static_cast<ReturnType*>(GetValuePtrByPropertyName(PropertyName));
        }

        void* GetValuePtrByPropertyNameInChain(const TCHAR*);

        template<UObjectPointerDerivativeOrAnyNonUObject ReturnType>
        ReturnType* GetValuePtrByPropertyNameInChain(const TCHAR* PropertyName)
        {
            return static_cast<ReturnType*>(GetValuePtrByPropertyNameInChain(PropertyName));
        }

        void* GetValuePtrByPropertyNameInChain(FName);

        template<UObjectPointerDerivativeOrAnyNonUObject ReturnType>
        ReturnType* GetValuePtrByPropertyNameInChain(FName PropertyName)
        {
            return static_cast<ReturnType*>(GetValuePtrByPropertyNameInChain(PropertyName));
        }

        FProperty* GetPropertyByName(FName);
        FProperty* GetPropertyByName(const TCHAR*);
        FProperty* GetPropertyByNameInChain(FName);
        FProperty* GetPropertyByNameInChain(const TCHAR*);

        UFunction* GetFunctionByName(FName);
        UFunction* GetFunctionByNameInChain(FName);
        UFunction* GetFunctionByName(const TCHAR*);
        UFunction* GetFunctionByNameInChain(const TCHAR*);

        static bool IsReal(const void* RawObject);
    };

    template<UObjectDerivative CastResultType>
    auto Cast(UObject* Object) -> CastResultType*
    {
        return Object != nullptr && Object->IsA<CastResultType>() ? static_cast<CastResultType*>(Object) : nullptr;
    }
}



