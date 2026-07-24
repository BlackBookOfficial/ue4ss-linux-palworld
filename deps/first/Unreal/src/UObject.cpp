#include <Unreal/UObject.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/VersionedContainer/Container.hpp>
#include <Unreal/UPackage.hpp>
#include <Unreal/Core/Containers/Map.hpp>
#include <Helpers/Casting.hpp>
#include <DynamicOutput/DynamicOutput.hpp>

#define NOMINMAX
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UObject);

    RC_UE_API Function<UObject::ProcessEventSignature> UObject::ProcessEventInternal;
    RC_UE_API Function<UObject::ProcessConsoleExecSignature> UObject::ProcessConsoleExecInternal;
    RC_UE_API Function<UObject::ProcessInternalSignature> UObject::ProcessInternalInternal;
    RC_UE_API Function<UObject::ProcessLocalScriptFunctionSignature> UObject::ProcessLocalScriptFunctionInternal;
    RC_UE_API Function<UObject::CallFunctionByNameWithArgumentsSignature> UObject::CallFunctionByNameWithArgumentsInternal;
    RC_UE_API std::unordered_map<File::StringType, uint32_t> UObjectBase::VTableLayoutMap{};
    RC_UE_API std::unordered_map<File::StringType, uint32_t> UObjectBaseUtility::VTableLayoutMap{};
    RC_UE_API std::unordered_map<File::StringType, uint32_t> UObject::VTableLayoutMap{};

    #include <MemberVariableLayout_SrcWrapper_UObjectBase.hpp>
    
    static auto NeedsHighIndexCleaned() -> bool
    {
#ifdef _WIN32
        wchar_t exe_name[1024];
        GetModuleFileNameW(GetModuleHandle(nullptr), exe_name, 1023);
        auto exe_absolute_path = std::filesystem::path{exe_name};
        auto need_to_apply_patch = exe_absolute_path.filename() == STR("KINGDOM HEARTS III.exe");
        if (need_to_apply_patch)
        {
            Output::send<LogLevel::Verbose>(STR("Detected Kingdom Hearts 3, applying InternalIndex patch.\n"));
        }
        return need_to_apply_patch;
#else
        char exe_path[1024];
        ssize_t len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
        if (len <= 0) return false;
        exe_path[len] = '\0';
        auto exe_absolute_path = std::filesystem::path{exe_path};
        auto need_to_apply_patch = exe_absolute_path.filename() == "KINGDOM HEARTS III";
        if (need_to_apply_patch)
        {
            Output::send<LogLevel::Verbose>(STR("Detected Kingdom Hearts 3, applying InternalIndex patch.\n"));
        }
        return need_to_apply_patch;
#endif
    }

    int32 UObjectBase::GetInternalIndex()
    {
        static bool bNeedsHighIndexCleaned = NeedsHighIndexCleaned();
        static auto offset = MemberOffsets.find(STR("InternalIndex_Private"));
        if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UObjectBase::InternalIndex' that doesn't exist in this engine version."}; }
        if (bNeedsHighIndexCleaned)
        {
            auto InternalIndex = *Helper::Casting::ptr_cast<int32*>(this, offset->second);
            auto IndexHighByte = std::bit_cast<uint8_t*>(&InternalIndex) + 0x3;
            *IndexHighByte = 0;
            return InternalIndex;
        }
        else
        {
            return *Helper::Casting::ptr_cast<int32*>(this, offset->second);
        }
    }
    const int32 UObjectBase::GetInternalIndex() const
    {
        static bool bNeedsHighIndexCleaned = NeedsHighIndexCleaned();
        static auto offset = MemberOffsets.find(STR("InternalIndex_Private"));
        if (offset == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'UObjectBase::InternalIndex' that doesn't exist in this engine version."}; }
        if (bNeedsHighIndexCleaned)
        {
            auto InternalIndex = *Helper::Casting::ptr_cast<int32*>(this, offset->second);
            auto IndexHighByte = std::bit_cast<uint8_t*>(&InternalIndex) + 0x3;
            *IndexHighByte = 0;
            return InternalIndex;
        }
        else
        {
            return *Helper::Casting::ptr_cast<const int32*>(this, offset->second);
        }
    }

    auto UObjectBase::RegisterDependencies() -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObjectBase, RegisterDependencies, void)
    }

    auto UObjectBase::DeferredRegister(class UClass* UClassStaticClass, const File::CharType* PackageName, const File::CharType* Name) -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObjectBase, DeferredRegister, void, PARAMS(const UClass*, const File::CharType*, const File::CharType*), ARGS(UClassStaticClass, PackageName, Name))
    }

    auto UObjectBase::GetObjectItem() const -> const FUObjectItem*
    {
        return FUObjectArray::IndexToObject(GetInternalIndex());
    }

    auto UObjectBase::GetObjectItem() -> FUObjectItem*
    {
        return FUObjectArray::IndexToObject(GetInternalIndex());
    }

    auto UObjectBase::IsA(UClass* Class) const -> bool
    {
        return GetClassPrivate()->IsChildOf(Class);
    }
    auto UObjectBase::IsA(const UClass* Class) const -> bool
    {
        return GetClassPrivate()->IsChildOf(Class);
    }

    auto UObjectBaseUtility::CanBeClusterRoot() const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObjectBaseUtility, CanBeClusterRoot, bool)
    }

    auto UObjectBaseUtility::CanBeInCluster() const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObjectBaseUtility, CanBeInCluster, bool)
    }

    auto UObjectBaseUtility::CreateCluster() -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObjectBaseUtility, CreateCluster, void)
    }

    auto UObjectBaseUtility::OnClusterMarkedAsPendingKill() -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObjectBaseUtility, OnClusterMarkedAsPendingKill, void)
    }

    auto UObject::SetFlagsTo(EObjectFlags NewFlags) -> void
    {
        Container::UnrealObjectVC->UObject_set_flags_to(this, NewFlags);
    }

    FString UObject::GetDetailedInfoInternal() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetDetailedInfoInternal, FString)
    }

    void UObject::PostInitProperties()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PostInitProperties, void)
    }

    void UObject::PostCDOContruct()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PostCDOContruct, void)
    }

    bool UObject::PreSaveRoot(const TCHAR* Filename)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PreSaveRoot, bool, PARAMS(const TCHAR*), ARGS(Filename))
    }

    void UObject::PostSaveRoot(bool bCleanupIsRequired)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PostSaveRoot, void, PARAMS(bool), ARGS(bCleanupIsRequired))
    }

    void UObject::PreSave(const ITargetPlatform* TargetPlatform)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PreSave, void, PARAMS(const ITargetPlatform*), ARGS(TargetPlatform))
    }

    bool UObject::IsReadyForAsyncPostLoad() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsReadyForAsyncPostLoad, bool)
    }

    void UObject::PostLoad()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PostLoad, void)
    }

    void UObject::PostLoadSubobjects(FObjectInstancingGraph* OuterInstanceGraph)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PostLoadSubobjects, void, PARAMS(FObjectInstancingGraph*), ARGS(OuterInstanceGraph))
    }

    void UObject::BeginDestroy()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, BeginDestroy, void)
    }

    bool UObject::IsReadyForFinishDestroy()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsReadyForFinishDestroy, bool)
    }

    void UObject::FinishDestroy()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, FinishDestroy, void)
    }

    void UObject::Serialize(FStructuredArchive::FRecord Record)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, Serialize, void, PARAMS(FStructuredArchive::FRecord), ARGS(Record))
    }

    void UObject::Serialize(FArchive& Ar)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, Serialize_2, void, PARAMS(FArchive&), ARGS(Ar))
    }

    void UObject::ShutdownAfterError()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, ShutdownAfterError, void)
    }

    void UObject::PostInterpChange(FProperty* PropertyThatChanged)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PostInterpChange, void, PARAMS(FProperty*), ARGS(PropertyThatChanged))
    }

    void UObject::PostRename(UObject* OldOuter, const FName OldName)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PostRename, void, PARAMS(UObject*, const FName), ARGS(OldOuter, OldName))
    }

    void UObject::PreDuplicate(FObjectDuplicationParameters& DupParams)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PreDuplicate, void, PARAMS(FObjectDuplicationParameters&), ARGS(DupParams))
    }

    void UObject::PostDuplicate(bool bDuplicateForPIE)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PostDuplicate, void, PARAMS(bool), ARGS(bDuplicateForPIE))
    }

    bool UObject::NeedsLoadForClient() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, NeedsLoadForClient, bool)
    }

    bool UObject::NeedsLoadForServer() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, NeedsLoadForServer, bool)
    }

    bool UObject::NeedsLoadForTargetPlatform(const ITargetPlatform* TargetPlatform) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, NeedsLoadForTargetPlatform, bool, PARAMS(const ITargetPlatform*), ARGS(TargetPlatform))
    }

    bool UObject::NeedsLoadForEditorGame() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, NeedsLoadForEditorGame, bool)
    }

    bool UObject::IsEditorOnly() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsEditorOnly, bool)
    }

    bool UObject::IsPostLoadThreadSafe() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsPostLoadThreadSafe, bool)
    }

    bool UObject::IsDestructionThreadSafe() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsDestructionThreadSafe, bool)
    }

    void UObject::GetPreloadDependencies(TArray<UObject*>& OutDeps)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, GetPreloadDependencies, void, PARAMS(TArray<UObject*>&), ARGS(OutDeps))
    }

    void UObject::GetPrestreamPackages(TArray<UObject*>& OutPrestream)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, GetPrestreamPackages, void, PARAMS(TArray<UObject*>&), ARGS(OutPrestream))
    }

    void UObject::ExportCustomProperties(FOutputDevice& Out, uint32 Indent)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, ExportCustomProperties, void, PARAMS(FOutputDevice&, uint32), ARGS(Out, Indent))
    }

    void UObject::ImportCustomProperties(const TCHAR* SourceText, FFeedbackContext* Warn)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, ImportCustomProperties, void, PARAMS(const TCHAR*, FFeedbackContext*), ARGS(SourceText, Warn))
    }

    void UObject::PostEditImport()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PostEditImport, void)
    }

    void UObject::PostReloadConfig(FProperty* PropertyThatWasLoaded)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, PostReloadConfig, void, PARAMS(FProperty*), ARGS(PropertyThatWasLoaded))
    }

    bool UObject::Rename(const TCHAR* NewName, UObject* NewOuter, ERenameFlags Flags)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject,
                                         Rename,
                                         bool,
                                         PARAMS(const TCHAR*, UObject*, ERenameFlags),
                                         ARGS(NewName, NewOuter, Flags))
    }

    FString UObject::GetDesc()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetDesc, FString)
    }

    UScriptStruct* UObject::GetSparseClassDataStruct() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetSparseClassDataStruct, UScriptStruct*)
    }

    UWorld* UObject::GetWorld() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetWorld, UWorld*)
    }

    bool UObject::GetNativePropertyValues(TMap<FString, FString>& out_PropertyValues, uint32 ExportFlags) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject,
                                         GetNativePropertyValues,
                                         bool,
                                         PARAMS(TMap<FString, FString>&, uint32),
                                         ARGS(out_PropertyValues, ExportFlags))
    }

    void UObject::GetResourceSizeEx(FResourceSizeEx& CumulativeResourceSize)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, GetResourceSizeEx, void, PARAMS(FResourceSizeEx&), ARGS(CumulativeResourceSize))
    }

    FName UObject::GetExporterName()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetExporterName, FName)
    }

    FRestoreForUObjectOverwrite* UObject::GetRestoreForUObjectOverwrite()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetRestoreForUObjectOverwrite, FRestoreForUObjectOverwrite*)
    }

    bool UObject::AreNativePropertiesIdenticalTo(UObject* Other) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, AreNativePropertiesIdenticalTo, bool, PARAMS(UObject*), ARGS(Other))
    }

    void UObject::GetAssetRegistryTags(TArray<FAssetRegistryTag>& OutTags) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, GetAssetRegistryTags, void, PARAMS(TArray<FAssetRegistryTag>&), ARGS(OutTags))
    }

    bool UObject::IsAsset() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsAsset, bool)
    }

    FPrimaryAssetId UObject::GetPrimaryAssetId() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetPrimaryAssetId, FPrimaryAssetId)
    }

    bool UObject::IsLocalizedResource() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsLocalizedResource, bool)
    }

    bool UObject::IsSafeForRootSet() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsSafeForRootSet, bool)
    }

    void UObject::TagSubobjects(EObjectFlags NewFlags)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, TagSubobjects, void, PARAMS(EObjectFlags), ARGS(NewFlags))
    }

    void UObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, GetLifetimeReplicatedProps, void, PARAMS(TArray<FLifetimeProperty>&), ARGS(OutLifetimeProps))
    }

    bool UObject::IsNameStableForNetworking() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsNameStableForNetworking, bool)
    }

    bool UObject::IsFullNameStableForNetworking() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsFullNameStableForNetworking, bool)
    }

    bool UObject::IsSupportedForNetworking() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, IsSupportedForNetworking, bool)
    }

    void UObject::GetSubobjectsWithStableNamesForNetworking(TArray<UObject*>& ObjList)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject,
                                         GetSubobjectsWithStableNamesForNetworking,
                                         void,
                                         PARAMS(TArray<UObject*>&),
                                         ARGS(ObjList))
    }

    void UObject::PreNetReceive()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PreNetReceive, void)
    }

    void UObject::PostNetReceive()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PostNetReceive, void)
    }

    void UObject::PostRepNotifies()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PostRepNotifies, void)
    }

    void UObject::PreDestroyFromReplication()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, PreDestroyFromReplication, void)
    }

    void UObject::BuildSubobjectMapping(UObject* OtherObject, TMap<UObject*, UObject*>& ObjectMapping) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject,
                                         BuildSubobjectMapping,
                                         void,
                                         PARAMS(UObject*, TMap<UObject*, UObject*>&),
                                         ARGS(OtherObject, ObjectMapping))
    }

    const TCHAR* UObject::GetConfigOverridePlatform() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetConfigOverridePlatform, TCHAR*)
    }

    void UObject::OverridePerObjectConfigSection(FString& SectionName)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, OverridePerObjectConfigSection, void, PARAMS(FString&), ARGS(SectionName))
    }

    void UObject::ProcessEvent(UFunction* Function, void* Parms)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, ProcessEvent, void, PARAMS(UFunction*, void*), ARGS(Function, Parms))
    }

    int32 UObject::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, GetFunctionCallspace, int32, PARAMS(UFunction*, FFrame*), ARGS(Function, Stack))
    }

    bool UObject::CallRemoteFunction(UFunction* Function, void* Parms, struct FOutParmRec* OutParms, FFrame* Stack)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject,
                                         CallRemoteFunction,
                                         bool,
                                         PARAMS(UFunction*, void*, FOutParmRec*, FFrame*),
                                         ARGS(Function, Parms, OutParms, Stack))
    }

    bool UObject::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject,
                                         ProcessConsoleExec,
                                         bool,
                                         PARAMS(const TCHAR*, FOutputDevice&, UObject*),
                                         ARGS(Cmd, Ar, Executor))
    }

    UClass* UObject::RegenerateClass(UClass* ClassToRegenerate, UObject* PreviousCDO)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, RegenerateClass, UClass*, PARAMS(UClass*, UObject*), ARGS(ClassToRegenerate, PreviousCDO))
    }

    void UObject::MarkAsEditorOnlySubobject()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, MarkAsEditorOnlySubobject, void)
    }

    bool UObject::CheckDefaultSubobjectsInternal() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, CheckDefaultSubobjectsInternal, bool)
    }

    void UObject::ValidateGeneratedRepEnums(const TArray<struct FRepRecord>& ClassReps) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, ValidateGeneratedRepEnums, void, PARAMS(const TArray<FRepRecord>&), ARGS(ClassReps))
    }

    void UObject::SetNetPushIdDynamic(const int32 NewNetPushId)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UObject, SetNetPushIdDynamic, void, PARAMS(const int32), ARGS(NewNetPushId))
    }

    int32 UObject::GetNetPushIdDynamic() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UObject, GetNetPushIdDynamic, int32)
    }

    auto UObject::GetOutermost() -> UObject*
    {
        UObject* CurrentObject = this;
        while (CurrentObject->GetOuterPrivate())
        {
            CurrentObject = CurrentObject->GetOuterPrivate();
        }
        return CurrentObject;
    }

    auto UObject::GetTypedOuter(UClass* OuterType) -> UObject*
    {
        UObject* CurrentOuter = GetOuterPrivate();
        while (CurrentOuter != nullptr)
        {
            if (CurrentOuter->IsA(OuterType))
            {
                return CurrentOuter;
            }
            CurrentOuter = CurrentOuter->GetOuterPrivate();
        }
        return nullptr;
    }

    auto UObject::GetPathName(UObject* StopOuter) const -> StringType
    {
        StringType ResultName;
        GetPathName(StopOuter, ResultName);
        return ResultName;
    }

    auto UObject::GetPathName(UObject* StopOuter, StringType& ResultString) const -> void
    {
        if(this != StopOuter && this != nullptr)
        {
            auto* Outer = GetOuterPrivate();

            if (Outer && Outer != StopOuter)
            {
                Outer->GetPathName(StopOuter, ResultString);

                // SUBOBJECT_DELIMITER_CHAR is used to indicate that this object's outer is not a UPackage
                // We use the name of UPackage here instead of StaticClass because StaticClass has not yet been initialized,
                // and it cannot be initialized until after a bunch of GetPathName calls has already happened
                if (Outer->GetClassPrivate()
                    && Outer->GetClassPrivate()->GetNamePrivate() != GPackageName
                    && Outer->GetOuterPrivate()
                    && Outer->GetOuterPrivate()->GetClassPrivate()->GetNamePrivate() == GPackageName)
                {
                    ResultString.push_back(SUBOBJECT_DELIMITER_CHAR);
                }
                else
                {
                    ResultString.append(STR("."));
                }
            }
            ResultString.append(GetName());
        }
        else
        {
            ResultString.append(STR("None"));
        }
    }

    size_t UObject::HashObject()
    {
        return reinterpret_cast<size_t>(this);
    }

    size_t UObject::HashObject() const
    {
        return reinterpret_cast<size_t>(this);
    }

    auto UObject::GetFullName(UObject* StopOuter) const -> StringType
    {
        if (this == nullptr)
        {
            return STR("None");
        }
        else
        {
            StringType OutName;
            OutName.append(GetClassPrivate()->GetName() + STR(" "));
            GetPathName(StopOuter, OutName);
            return OutName;
        }
    }

    FProperty* UObject::GetPropertyByName(const TCHAR* PropertyName)
    {
        return GetPropertyByName(FName(ToCharTypePtr(PropertyName)));
    }

    FProperty* UObject::GetPropertyByName(FName PropertyName)
    {
        UStruct* Struct = IsA<UStruct>() ? static_cast<UStruct*>(this) : GetClassPrivate();
        for (FProperty* Property : TFieldRange<FProperty>(Struct, EFieldIterationFlags::IncludeDeprecated)) 
        {
            if (Property->GetFName().Equals(PropertyName))
            {
                return Property;
            }
        }
        return nullptr;
    }

    FProperty* UObject::GetPropertyByNameInChain(const TCHAR* PropertyName)
    {
        return GetPropertyByNameInChain(FName(ToCharTypePtr(PropertyName)));
    }

    FProperty* UObject::GetPropertyByNameInChain(const FName PropertyName)
    {
        UStruct* Struct = IsA<UStruct>() ? static_cast<UStruct*>(this) : GetClassPrivate();
        for (FProperty* Property : TFieldRange<FProperty>(Struct, EFieldIterationFlags::IncludeSuper | EFieldIterationFlags::IncludeDeprecated)) 
        {
            if (Property->GetFName().Equals(PropertyName))
            {
                return Property;
            }
        }
        return nullptr;
    }

    UFunction* UObject::GetFunctionByName(FName FunctionName)
    {
        for (UFunction* Function : TFieldRange<UFunction>(GetClassPrivate(), EFieldIterationFlags::None))
        {
            if (Function->GetNamePrivate() == FunctionName)
            {
                return Function;
            }
        }

        return nullptr;
    }

    UFunction* UObject::GetFunctionByNameInChain(FName FunctionName)
    {
        for (UFunction* Function : TFieldRange<UFunction>(GetClassPrivate(), EFieldIterationFlags::IncludeInterfaces | EFieldIterationFlags::IncludeSuper)) 
        {
            if (Function->GetNamePrivate() == FunctionName)
            {
                return Function;
            }
        }

        return nullptr;
    }


    UFunction* UObject::GetFunctionByName(const TCHAR* FunctionName)
    {
        return GetFunctionByName(FName(ToCharTypePtr(FunctionName)));
    }

    UFunction* UObject::GetFunctionByNameInChain(const TCHAR* FunctionName)
    {
        return GetFunctionByNameInChain(FName(ToCharTypePtr(FunctionName)));
    }

    void* UObject::GetValuePtrByPropertyName(const TCHAR* PropertyName)
    {
        return GetValuePtrByPropertyName(FName(ToCharTypePtr(PropertyName)));
    }

    void* UObject::GetValuePtrByPropertyName(FName PropertyName)
    {
        auto FoundProperty = GetPropertyByName(PropertyName);
        if (!FoundProperty) { return nullptr; }
        return FoundProperty->ContainerPtrToValuePtr<void>(this);
    }

    void* UObject::GetValuePtrByPropertyNameInChain(const TCHAR* PropertyName)
    {
        return GetValuePtrByPropertyNameInChain(FName(ToCharTypePtr(PropertyName)));
    }

    void* UObject::GetValuePtrByPropertyNameInChain(FName PropertyName)
    {
        auto FoundProperty = GetPropertyByNameInChain(PropertyName);
        if (!FoundProperty) { return nullptr; }
        return FoundProperty->ContainerPtrToValuePtr<void>(this);
    }

    bool UObject::IsReal(const void* pThis)
    {
        bool ObjectWasFound{};

        UObjectGlobals::ForEachUObject([&](void* RawObject, [[maybe_unused]]int32_t ChunkIndex, [[maybe_unused]]int32_t ObjectIndex) {
            if (pThis == RawObject)
            {
                ObjectWasFound = true;
                return LoopAction::Break;
            }

            return LoopAction::Continue;
        });

        return ObjectWasFound;
    }
}
