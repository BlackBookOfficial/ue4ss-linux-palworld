#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>
#include <Unreal/FString.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FObjectPropertyBase);
    IMPLEMENT_FIELD_CLASS(FObjectProperty);
    IMPLEMENT_FIELD_CLASS(FObjectPtrProperty);
    IMPLEMENT_FIELD_CLASS(FAssetObjectProperty);
    IMPLEMENT_FIELD_CLASS(FAssetClassProperty);
    std::unordered_map<File::StringType, uint32_t> FObjectPropertyBase::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_FObjectPropertyBase.hpp>

    void FObjectPropertyBase::SetPropertyClass(UClass* NewPropertyClass)
    {
        GetPropertyClass() = NewPropertyClass;
    }

    FString FObjectPropertyBase::GetCPPTypeCustom(FString* ExtendedTypeText, uint32 CPPExportFlags, const FString& InnerNativeTypeName) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FObjectPropertyBase,
                                          GetCPPTypeCustom,
                                          FString,
                                          PARAMS(FString*, uint32, const FString&),
                                          ARGS(ExtendedTypeText, CPPExportFlags, InnerNativeTypeName))
    }

    UObject* FObjectPropertyBase::LoadObjectPropertyValue(const void* PropertyValueAddress) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FObjectPropertyBase,
                                         LoadObjectPropertyValue,
                                         UObject*,
                                         PARAMS(const void*),
                                         ARGS(PropertyValueAddress))
    }

    UObject* FObjectPropertyBase::GetObjectPropertyValue(const void* PropertyValueAddress) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FObjectPropertyBase,
                                         GetObjectPropertyValue,
                                         UObject*,
                                         PARAMS(const void*),
                                         ARGS(PropertyValueAddress))
    }

    void FObjectPropertyBase::SetObjectPropertyValue(void* PropertyValueAddress, UObject* Value) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FObjectPropertyBase,
                                         SetObjectPropertyValue,
                                         void,
                                         PARAMS(void*, UObject*),
                                         ARGS(PropertyValueAddress, Value))
    }

    bool FObjectPropertyBase::AllowCrossLevel() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FObjectPropertyBase, AllowCrossLevel, bool)
    }

    void FObjectPropertyBase::CheckValidObject(void* Value) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FObjectPropertyBase, CheckValidObject, void, PARAMS(void*), ARGS(Value))
    }
}
