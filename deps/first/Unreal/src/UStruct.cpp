#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/FField.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UStruct);

    Function<UStruct::LinkSignature> UStruct::LinkInternal;
    std::unordered_map<File::StringType, uint32_t> UStruct::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_UStruct.hpp>

    UStruct* UStruct::GetInheritanceSuper() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UStruct, GetInheritanceSuper, UStruct*)
    }

    void UStruct::Link(FArchive& Ar, bool bRelinkExistingProperties)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, Link, void, PARAMS(FArchive&, bool), ARGS(Ar, bRelinkExistingProperties))
    }

    void UStruct::SerializeBin(FArchive& Ar, void* Data) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, SerializeBin, void, PARAMS(FArchive&, void*), ARGS(Ar, Data))

    }

    void UStruct::SerializeTaggedProperties(FArchive& Ar, uint8* Data, UStruct* DefaultsStruct, uint8* Defaults, const UObject* BreakRecursionIfFullyLoad) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct,
                                         SerializeTaggedProperties,
                                         void,
                                         PARAMS(FArchive&, uint8*, UStruct*, uint8*, const UObject*),
                                         ARGS(Ar, Data, DefaultsStruct, Defaults, BreakRecursionIfFullyLoad))
    }

    void UStruct::InitializeStruct(void* Dest, int32 ArrayDim) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, InitializeStruct, void, PARAMS(void*, int32), PARAMS(Dest, ArrayDim))
    }

    void UStruct::DestroyStruct(void* Dest, int32 ArrayDim) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, DestroyStruct, void, PARAMS(void*, int32), ARGS(Dest, ArrayDim))
    }

    FProperty* UStruct::CustomFindProperty(const FName InName) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, CustomFindProperty, FProperty*, PARAMS(const FName), ARGS(InName))
    }

    EExprToken UStruct::SerializeExpr(int32& iCode, FArchive& Ar)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, SerializeExpr, EExprToken, PARAMS(int32&, FArchive&), ARGS(iCode, Ar))
    }

    const TCHAR* UStruct::GetPrefixCPP() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UStruct, GetPrefixCPP, const TCHAR*)
    }

    void UStruct::SetSuperStruct(UStruct* NewSuperStruct)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, SetSuperStruct, void, PARAMS(UStruct*), ARGS(NewSuperStruct))
    }

    FString UStruct::PropertyNameToDisplayName(FName InName) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, PropertyNameToDisplayName, FString, PARAMS(FName), ARGS(InName))
    }

    FString UStruct::GetAuthoredNameForField(const UField* Field) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, GetAuthoredNameForField, FString, PARAMS(const UField*), ARGS(Field))
    }

    bool UStruct::IsStructTrashed() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UStruct, IsStructTrashed, bool)
    }

    FName UStruct::FindPropertyNameFromGuid(const FGuid& PropertyGuid) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, FindPropertyNameFromGuid, FName, PARAMS(const FGuid&), ARGS(PropertyGuid))
    }

    FGuid UStruct::FindPropertyGuidFromName(const FName InName) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UStruct, FindPropertyGuidFromName, FGuid, PARAMS(const FName), ARGS(InName))
    }

    bool UStruct::ArePropertyGuidsAvailable() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(UStruct, ArePropertyGuidsAvailable, bool)
    }

    auto UStruct::ForEachFunction() -> TFieldRange<UFunction>
    {
        // Use TFieldRange for optimized iteration (backwards compatible with range-based for)
        // Exclude super classes - only iterate functions in this struct
        return TFieldRange<UFunction>(this, EFieldIterationFlags::None);
    }

    auto UStruct::ForEachProperty() -> TFieldRange<FProperty>
    {
        // Use TFieldRange for optimized iteration (backwards compatible with range-based for)
        // Include deprecated properties to match original behavior
        return TFieldRange<FProperty>(this, EFieldIterationFlags::IncludeDeprecated);
    }

    auto UStruct::ForEachSuperStruct() -> TSuperStructRange
    {
        // Use TSuperStructRange for optimized iteration (backwards compatible with range-based for)
        return TSuperStructRange(this);
    }

    auto UStruct::ForEachPropertyInChain() -> TFieldRange<FProperty>
    {
        // Use TFieldRange with IncludeSuper for optimized iteration (backwards compatible with range-based for)
        // Include super classes and deprecated properties to match original behavior (Default = IncludeSuper | IncludeDeprecated)
        return TFieldRange<FProperty>(this, EFieldIterationFlags::Default);
    }

    auto UStruct::OrderedForEachPropertyInChain() -> TReverseFieldRange<FProperty>
    {
        // Use TReverseFieldRange for optimized reverse iteration (backwards compatible with range-based for)
        // This eliminates coroutine overhead while maintaining parent-to-child iteration order
        return TReverseFieldRange<FProperty>(this, EFieldIterationFlags::IncludeDeprecated);
    }

    auto UStruct::ForEachFunctionInChain() -> TFieldRange<UFunction>
    {
        return TFieldRange<UFunction>(this, EFieldIterationFlags::IncludeAll);
    }

    struct FPropertyCacheKey
    {
        void* ClassPtr;
        FName PropertyName;
        bool operator==(const FPropertyCacheKey& Other) const
        {
            return (ClassPtr == Other.ClassPtr && PropertyName == Other.PropertyName);
        }
    };
    struct FPropertyCacheKeyHash
    {
        size_t operator()(const FPropertyCacheKey& Item) const
        {
            return std::hash<uintptr_t>()((uintptr_t)Item.ClassPtr) ^ std::hash<FName>()(Item.PropertyName);
        }
    };
    FProperty* UStruct::FindProperty(FName PropertyName)
    {
        static std::unordered_map<FPropertyCacheKey, FProperty*, FPropertyCacheKeyHash> PropertyCache;
        FPropertyCacheKey CacheIndex{this, PropertyName};
        if (PropertyCache.contains(CacheIndex)) { return PropertyCache[CacheIndex]; }

        for (FProperty* Property : TFieldRange<FProperty>(this, EFieldIterationFlags::IncludeSuper | EFieldIterationFlags::IncludeDeprecated))
        {
            if (Property->GetFName() == PropertyName)
            {
                PropertyCache[CacheIndex] = Property;
                return Property;
            }
        }
        return nullptr;
    }

    bool UStruct::HasChildren()
    {
        if (Version::IsBelow(4, 25))
        {
            return GetChildren();
        }
        else
        {
            return GetChildProperties() || GetChildren();
        }
    }

    FProperty* UStruct::GetFirstProperty()
    {
        if (Version::IsBelow(4, 25))
        {
            // In <4.25, this is safe if a UField is a property, which 'CastField' checks
            // In <4.25, all properties are of type UField
            return CastField<FProperty>(std::bit_cast<FField*>(GetChildren().Get()));
        }
        else
        {
            return CastField<FProperty>(GetChildProperties());
        }
    }

    const UStruct*& UStruct::GetSuperStruct() const
    {
        // TNonAccessTrackedObjectPtr can be interpreted as TObjectPtr, or T*.
        static_assert(sizeof(TObjectPtr<UStruct>) == sizeof(void*));
        return *std::bit_cast<const UStruct**>(&GetSuperStruct507());
    }

    UStruct*& UStruct::GetSuperStruct()
    {
        // TNonAccessTrackedObjectPtr can be interpreted as TObjectPtr, or T*.
        static_assert(sizeof(TObjectPtr<UStruct>) == sizeof(void*));
        return *std::bit_cast<UStruct**>(&GetSuperStruct507());
    }

    const int16& UStruct::GetMinAlignment() const
    {
        return GetMinAlignment506();
    }

    int16& UStruct::GetMinAlignment()
    {
        return GetMinAlignment506();
    }
}
