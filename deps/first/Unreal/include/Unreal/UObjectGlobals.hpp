#pragma once

#include <array>
#include <vector>
#include <functional>

#include <Function/Function.hpp>
#include <Constructs/Loop.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/UnrealFlags.hpp>
#include <Unreal/Core/Templates/Function.hpp>
#include <Unreal/UFunctionStructs.hpp>

#include <String/StringType.hpp>

#ifndef UE_WITH_REMOTE_OBJECT_HANDLE
#define UE_WITH_REMOTE_OBJECT_HANDLE 0
#endif

namespace RC::Unreal
{
    class UObject;
    struct ObjectSearcher;

    // Temporary empty implementations
    struct FObjectInstancingGraph {};
    class FFeedbackContext {};

    /** Concept describing the type of the pointer pointing to the UObject-derived object */
    template<typename SupposedUObject>
    concept UObjectPointerDerivative = std::is_convertible_v<SupposedUObject, UObject*>;

    /** Concept describing the type derived from the UObject */
    template<typename SupposedUObject>
    concept UObjectDerivative = std::is_convertible_v<SupposedUObject, UObject>;

    /** Concept describing the type derived from the UClass */
    template<typename SupposedUClass>
    concept UClassDerivative = std::is_convertible_v<SupposedUClass, class UClass>;

    /** Concept describing a type that must be a pointer if derived from UObject */
    template<typename T>
    concept UObjectPointerDerivativeOrAnyNonUObject = !UObjectDerivative<T> || UObjectPointerDerivative<T>;

    struct FRemoteObjectId
    {
    private:
        union
        {
            struct
            {
                uint64 SerialNumber : 54;
                uint64 ServerId : 10;
            };
            uint64 Id = 0;
        };
    };

    /** Casts the object to the provided type if possible, returns nullptr otherwise */
    template<UObjectDerivative CastResultType>
    auto Cast(UObject* Object) -> CastResultType*;

    // Adapted from UE source
    // This struct becomes deprecated in 4.26+ and as such is only used if <=4.25 is detected
#define StaticConstructObject_Internal_Params_Deprecated \
    const UClass* InClass_,\
    UObject* InOuter_,\
    FName InName_,\
    EObjectFlags InFlags_,\
    EInternalObjectFlags InternalSetFlags_,\
    UObject* InTemplate_,\
    bool bCopyTransientsFromClassDefaults_,\
    FObjectInstancingGraph* InInstanceGraph_,\
    bool bAssumeTemplateIsArchetype_,\
    void* ExternalPackage_\

    // Generic struct, to be converted to an engine version specific struct at the call-site.
    struct RC_UE_API FStaticConstructObjectParameters
    {
    public:
        /** The class of the object to create */
        const class UClass* Class;

        /** The object to create this object within (the Outer property for the new object will be set to the value specified here). */
        UObject* Outer;

        /** The name to give the new object.If no value(NAME_None) is specified, the object will be given a unique name in the form of ClassName_#. */
        FName Name;

        /** The ObjectFlags to assign to the new object. some flags can affect the behavior of constructing the object. */
        EObjectFlags SetFlags = RF_NoFlags;

        /** The InternalObjectFlags to assign to the new object. some flags can affect the behavior of constructing the object. */
        EInternalObjectFlags InternalSetFlags = EInternalObjectFlags::None;

        /** If true, copy transient from the class defaults instead of the pass in archetype ptr(often these are the same) */
        bool bCopyTransientsFromClassDefaults = false;

        /** If true, Template is guaranteed to be an archetype */
        bool bAssumeTemplateIsArchetype = false;

        /**
         * If specified, the property values from this object will be copied to the new object, and the new object's ObjectArchetype value will be set to this object.
         * If nullptr, the class default object is used instead.
         */
        UObject* Template = nullptr;

        /** Contains the mappings of instanced objects and components to their templates */
        struct FObjectInstancingGraph* InstanceGraph = nullptr;

        /** Assign an external Package to the created object if non-null */
        class UPackage* ExternalPackage = nullptr;

    public:
        FStaticConstructObjectParameters(const class UClass* InClass, UObject* InOuter = nullptr) : Class(InClass), Outer(InOuter) {}
    };
}

namespace RC::Unreal::UObjectGlobals
{
    static inline UPackage* ANY_PACKAGE{reinterpret_cast<UPackage*>(-1)};

    // Internal game functions
    struct GlobalState
    {
        RC_UE_API static Function<UObject*(StaticConstructObject_Internal_Params_Deprecated)> StaticConstructObjectInternalDeprecated;
        RC_UE_API static Function<UObject*(const FStaticConstructObjectParameters&)> StaticConstructObjectInternal;
    };

    // Setup internal game functions
    RC_UE_API auto SetupStaticConstructObjectInternalAddress(void* FunctionAddress) -> void;

    //Iterates object array and calls the provided function for each object
    RC_UE_API auto ForEachUObject(const std::function<LoopAction(UObject* object, int32 object_index, int32 chunk_index)>& RawObject) -> void;

    RC_UE_API auto ForEachUObjectInChunk(int32_t ChunkIndex, const std::function<LoopAction(UObject*, int32)>& Callable) -> void;

    RC_UE_API auto ForEachUObjectInRange(int32_t Start, int32_t End, const std::function<LoopAction(UObject*, int32, int32)>& Callable) -> void;

    RC_UE_API auto StaticConstructObject(const FStaticConstructObjectParameters& Params) -> UObject*;

    template<UObjectPointerDerivative ObjectType = UObject*>
    auto StaticConstructObject(const FStaticConstructObjectParameters& Params) -> ObjectType
    {
        return static_cast<ObjectType>(StaticConstructObject(Params));
    }

    template<typename ObjectType>
    ObjectType* NewObject(UObject* Outer,
                          const UClass* Class,
                          FName Name = NAME_None,
                          EObjectFlags Flags = RF_NoFlags,
                          UObject* Template = nullptr,
                          bool bCopyTransientsFromClassDefaults = false,
                          FObjectInstancingGraph* InInstanceGraph = nullptr,
                          UPackage* ExternalPackage = nullptr)
    {
        FStaticConstructObjectParameters Params{Class};
        Params.Outer = Outer;
        Params.Name = Name;
        Params.SetFlags = Flags;
        Params.Template = Template;
        Params.bCopyTransientsFromClassDefaults = bCopyTransientsFromClassDefaults;
        Params.InstanceGraph = InInstanceGraph;
        Params.ExternalPackage = ExternalPackage;
        return StaticConstructObject<ObjectType*>(Params);
    }

    template<typename ObjectType>
    ObjectType* NewObject(UObject* Outer,
                          FName Name,
                          EObjectFlags Flags = RF_NoFlags,
                          UObject* Template = nullptr,
                          bool bCopyTransientsFromClassDefaults = false,
                          FObjectInstancingGraph* InInstanceGraph = nullptr)
    {
        FStaticConstructObjectParameters Params{ObjectType::StaticClass()};
        Params.Outer = Outer;
        Params.Name = Name;
        Params.SetFlags = Flags;
        Params.Template = Template;
        Params.bCopyTransientsFromClassDefaults = bCopyTransientsFromClassDefaults;
        Params.InstanceGraph = InInstanceGraph;
        return StaticConstructObject<ObjectType*>(Params);
    }

    // UE compatible overload for 'FindObject'.
    RC_UE_API UObject* FindObject(UClass* Class, UObject* InOuter, File::StringViewType InName, bool bExactClass = false, ObjectSearcher* = nullptr);
    RC_UE_API UObject* FindObject(UClass* Class, UObject* InOuter, const TCHAR* InName, bool bExactClass = false, ObjectSearcher* = nullptr);

    // Convenience overload for the UE compatible 'FindObject' overload.
    // It exists so that you don't have to specify all the optional params in order to specify a searcher.
    RC_UE_API UObject* FindObject(ObjectSearcher&, UClass* Class, UObject* InOuter, File::StringViewType InName, bool bExactClass = false);
    RC_UE_API UObject* FindObject(ObjectSearcher&, UClass* Class, UObject* InOuter, const TCHAR* InName, bool bExactClass = false);

    template<UObjectDerivative ObjectType>
    ObjectType* FindObject(UObject* Outer, const TCHAR* Name, bool ExactClass = false)
    {
        return static_cast<ObjectType*>(FindObject(ObjectType::StaticClass(), Outer, Name, ExactClass));
    }

    // Internal game function implementations
    // Slow implementation that's to be avoided whenever possible
    // This only exists for compatibility reasons with old Lua scripts
    // All params except 'orig_in_name' are also just there for compatibility reasons and do not have any effect
    RC_UE_API auto StaticFindObject_InternalSlow(UClass* Object, UObject* ChunkIndex, const CharType* OrigInName, bool bExactClass = false) -> UObject*;
    RC_UE_API auto StaticFindObject_InternalNoToStringFromStrings(const std::vector<StringViewType>& NameParts) -> UObject*;
    RC_UE_API auto StaticFindObject_InternalNoToStringFromNames(const std::vector<FName>& NameParts) -> UObject*;

    template<UObjectPointerDerivative ObjectType = UObject*>
    auto StaticFindObject(UClass* ObjectClass, UObject* InObjectPackage, const CharType* OrigInName, bool bExactClass = false) -> ObjectType
    {
        return static_cast<ObjectType>(FindObject(ObjectClass, InObjectPackage, OrigInName, bExactClass));
    }
    template<UObjectPointerDerivative ObjectType = UObject*>
    auto StaticFindObject(UClass* ObjectClass, UObject* InObjectPackage, StringViewType OrigInName, bool bExactClass = false) -> ObjectType
    {
        return static_cast<ObjectType>(FindObject(ObjectClass, InObjectPackage, OrigInName.data(), bExactClass));
    }

    template<UObjectPointerDerivative ObjectType = UObject*>
    auto StaticFindObject(UClass* ObjectClass, UObject* InObjectPackage, const StringType& OrigInName, bool bExactClass = false) -> ObjectType
    {
        return static_cast<ObjectType>(FindObject(ObjectClass, InObjectPackage, OrigInName.c_str(), bExactClass));
    }

    // Custom Helpers -> START
    // Find the first instance of a class
    // Does not find ClassDefaultObjects (CDO) or non-instances of classes
    // Takes inheritance into account, that means you can give it an FName of "Controller" and
    // it will also find instances of "PlayerController" and any instances from any other derived class
    RC_UE_API auto FindFirstOf(FName Object) -> UObject*;
    RC_UE_API auto FindFirstOf(const CharType* ClassName) -> UObject*;
    RC_UE_API auto FindFirstOf(StringViewType ClassName) -> UObject*;
    RC_UE_API auto FindFirstOf(const StringType& ClassName) -> UObject*;
    RC_UE_API auto FindFirstOf(std::string_view ClassName) -> UObject*;
    RC_UE_API auto FindFirstOf(const std::string& ClassName) -> UObject*;

    // Find all instances of a class
    // Follows the same rules as 'find_first_of'
    RC_UE_API auto FindAllOf(FName SuperStruct, std::vector<UObject*>& ChunkIndex) -> void;
    RC_UE_API auto FindAllOf(const CharType* ClassName, std::vector<UObject*>& OutStorage) -> void;
    RC_UE_API auto FindAllOf(StringViewType ClassName, std::vector<UObject*>& OutStorage) -> void;
    RC_UE_API auto FindAllOf(const StringType& ClassName, std::vector<UObject*>& OutStorage) -> void;
    RC_UE_API auto FindAllOf(std::string_view ClassName, std::vector<UObject*>& OutStorage) -> void;
    RC_UE_API auto FindAllOf(const std::string& ClassName, std::vector<UObject*>& OutStorage) -> void;

    // Find a specified number of objects with the specified class (or none) and name (or none)
    // Must have at least either class or name, or both
    // Required & banned flags can be specified or left to the default (no required/banned flags)
    // Find one or specified amount of objects
    // Specify 0 for 'num_objects_to_find' to not limit to number of objects to find
    // The 'flags' parameters for the following functions are of type EObjectFlags
    RC_UE_API auto FindObjects(size_t Object, const FName ClassName, const FName ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags = {}, int32 BannedFlags = {}, bool bExactClass = true) -> void;
    RC_UE_API auto FindObjects(size_t NumObjectsToFind, const CharType* ClassName, const CharType* ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags = {}, int32 BannedFlags = {}, bool bExactClass = true) -> void;
    RC_UE_API auto FindObject(const FName ClassName, const FName ObjectShortName, int32 RequiredFlags = {}, int32 BannedFlags = {}) -> UObject*;
    RC_UE_API auto FindObject(const CharType* ClassName, const CharType* ObjectShortName, int32 RequiredFlags = {}, int32 BannedFlags = {}) -> UObject*;

    // Find all objects
    // The 'flags' parameters for the following functions are of type EObjectFlags
    RC_UE_API auto FindObjects(const FName ClassName, const FName ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags = {}, int32 BannedFlags = {}, bool bExactClass = true) -> void;
    RC_UE_API auto FindObjects(const CharType* ClassName, const CharType* ObjectShortName, std::vector<UObject*>& OutStorage, int32 RequiredFlags = {}, int32 BannedFlags = {}, bool bExactClass = true) -> void;

    // Register a UFunction hook through all known means.
    RC_UE_API auto RegisterHook(class UFunction* Function, UnrealScriptFunctionCallable, UnrealScriptFunctionCallable, void*) -> std::pair<int, int>;
    RC_UE_API auto RegisterHook(const StringType& FunctionFullNameNoType, UnrealScriptFunctionCallable, UnrealScriptFunctionCallable, void*) -> std::pair<int, int>;
    RC_UE_API auto UnregisterHook(class UFunction* Function, std::pair<int, int>) -> void;
    RC_UE_API auto UnregisterHook(const StringType& FunctionFullNameNoType, std::pair<int, int>) -> void;
    // Custom Helpers -> END

    // Version specific parameter structures for StaticConstructObject
    namespace Below56 {
        struct FStaticConstructObjectParameters
        {
            const class UClass* Class;
            UObject* Outer;
            FName Name;
            EObjectFlags SetFlags = RF_NoFlags;
            EInternalObjectFlags InternalSetFlags = EInternalObjectFlags::None;
            bool bCopyTransientsFromClassDefaults = false;
            bool bAssumeTemplateIsArchetype = false;
            UObject* Template = nullptr;
            struct FObjectInstancingGraph* InstanceGraph = nullptr;
            class UPackage* ExternalPackage = nullptr;

            // 5.00+
            TFunction<void()> PropertyInitCallback{};

            // 5.00+
            void* SubobjectOverrides = nullptr;
        };
    }

    namespace Above55 {
        struct FStaticConstructObjectParameters
        {
            const class UClass* Class;
            UObject* Outer;
            FName Name;
            EObjectFlags SetFlags = RF_NoFlags;
            EInternalObjectFlags InternalSetFlags = EInternalObjectFlags::None;
            bool bCopyTransientsFromClassDefaults = false;
            bool bAssumeTemplateIsArchetype = false;
            UObject* Template = nullptr;
            struct FObjectInstancingGraph* InstanceGraph = nullptr;
            class UPackage* ExternalPackage = nullptr;

            // 5.00+
            // In 5.6, TFunction was changed, and we don't currently support it, so we must use padding instead.
            uint8 PropertyInitCallback[0x30]{};

            // 5.6 Additions -> START
            int32 SerialNumber = 0;
            #if UE_WITH_REMOTE_OBJECT_HANDLE
            FRemoteObjectId RemoteId;
            // UE::RemoteObject::Serialization::FRemoteObjectConstructionOverrides*
            void* RemoteSubObjectOverrides = nullptr;
            #endif // UE_WITH_REMOTE_OBJECT_HANDLE
            // 5.6 Additions -> END

            // 5.00+
            void* SubobjectOverrides = nullptr;
        };
    }
}



