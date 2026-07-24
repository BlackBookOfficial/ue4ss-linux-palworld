#pragma once

/*=============================================================================
    Class.hpp: UClass definition.
=============================================================================*/
#include <format>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <functional>

#include <Constructs/Generator.hpp>
#include <Constructs/Loop.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/UObjectGlobals.hpp>
#include <Unreal/UnrealCoreStructs.hpp>
#include <Unreal/FField.hpp>
#include <Unreal/Script.hpp>
#include <Unreal/FieldPath.hpp>
#include <Unreal/UFunctionStructs.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/Core/Templates/Tuple.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/FText.hpp>
#include <Unreal/UnrealFlags.hpp>

namespace RC::Unreal
{
    // Forward declarations for GC schema types
    namespace UE::GC
    {
        class FSchemaOwner;
    }

    // Forward declaration for platform types
    namespace UE
    {
        class FPlatformRWLock;
    }

    class FProperty;
    class UFunction;
    template <typename T> struct TFieldRange;
    template <typename T> struct TReverseFieldRange;
    struct TSuperStructRange;
    struct FFrame;
    struct FGCReferenceTokenStream;

    // Forward declarations for versioned member types
    namespace ObjectPtr_Private
    {
        template <typename T> struct TNonAccessTrackedObjectPtr;
    }
    namespace UE::CoreUObject::Private
    {
        struct FStructOpsFakeVTable;
    }

    /*-----------------------------------------------------------------------------
        UField.
    -----------------------------------------------------------------------------*/

    //
    // Base class of reflection data objects.
    //
    class RC_UE_API UField : public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UField, CoreUObject);

        friend class FField;
        template <class T>
        friend class TFieldIterator;

        // Friend declarations for TFieldIterator helper functions
        template <class FieldType>
        friend FieldType* GetChildFieldsFromStruct(UStruct* Owner);
        template <class FieldType>
        friend FieldType* GetNextField(FieldType* Field);

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

        // Type aliases for TFieldIterator compatibility (UE < 4.25)
        using BaseFieldClass = UField;
        using FieldTypeClass = UClass;

    public:
#include <MemberVariableLayout_HeaderWrapper_UField.hpp>

    protected:
        friend class UStruct;

        inline static constexpr uint64 StaticClassCastFlagsPrivate()
        {
            return uint64(CASTCLASS_UField);
        }
        inline static constexpr uint64 StaticClassCastFlags()
        {
            return uint64(CASTCLASS_UField);
        }

        /**
         * Returns the next UField in a linked list defined by the UClass::Children property
         * Keep in mind that in UE versions below 4.25 it will also include UProperty objects!
         * Only for internal use, if you want to iterate properties or functions use for_each_property/function
         */
        [[deprecated("Use 'GetNext' instead")]]
        auto GetNextField() -> UField*;

        /**
         * Attempts to convert this UField to the FField object instance
         * The conversion is only possible for UE versions below 4.25, after 4.25 the
         * UField and FField have been separated
         * This function will throw the exception if the UE version is above 4.25
         */
        auto AsFFieldUnsafe() -> class FField*;

        // Virtual Functions
    public:
        void AddCppProperty(FProperty* Property);
        void Bind();
    };

    /*-----------------------------------------------------------------------------
        UStruct.
    -----------------------------------------------------------------------------*/

    /**
     * Base class for all UObject types that contain fields.
     */
    class RC_UE_API UStruct : public UField
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UStruct, CoreUObject, CASTCLASS_UStruct)

    public:
        using LinkSignature = void(UStruct* Context, FArchive& Ar, bool bRelinkExistingProperties);
        static Function<LinkSignature> LinkInternal;

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_UStruct.hpp>

    public:
        // Versioned member wrappers
        const UStruct*& GetSuperStruct() const;
        UStruct*& GetSuperStruct();
        const int16& GetMinAlignment() const;
        int16& GetMinAlignment();

    public:
        // Wrappers for virtual engine functions
        UStruct* GetInheritanceSuper() const;
        void Link(FArchive& Ar, bool bRelinkExistingProperties);
        void SerializeBin(FArchive& Ar, void* Data) const;
        class FStructuredArchive { enum class FSlot {}; }; // Remove if/when we have a FStructuredArchive implementation, for now, probably a bad idea to call
        //void SerializeBin(FStructuredArchive::FSlot Slot, void* Data) const;
        void SerializeTaggedProperties(FArchive& Ar, uint8* Data, UStruct* DefaultsStruct, uint8* Defaults, const UObject* BreakRecursionIfFullyLoad = nullptr) const;
        //void SerializeTaggedProperties(FStructuredArchive::FSlot Slot, uint8* Data, UStruct* DefaultsStruct, uint8* Defaults, const UObject* BreakRecursionIfFullyLoad = nullptr) const;
        void InitializeStruct(void* Dest, int32 ArrayDim = 1) const;
        void DestroyStruct(void* Dest, int32 ArrayDim = 1) const;
        FProperty* CustomFindProperty(const FName InName) const;
        EExprToken SerializeExpr(int32& iCode, FArchive& Ar);
        const TCHAR* GetPrefixCPP() const;
        void SetSuperStruct(UStruct* NewSuperStruct);
        FString PropertyNameToDisplayName(FName InName) const;
        FString GetAuthoredNameForField(const UField* Field) const;
        //FString GetAuthoredNameForField(const FField* Field) const;
        bool IsStructTrashed() const;
        FName FindPropertyNameFromGuid(const FGuid& PropertyGuid) const;
        FGuid FindPropertyGuidFromName(const FName InName) const;
        bool ArePropertyGuidsAvailable() const;

    private:
        FORCEINLINE static bool IsChildOfInternal(const UStruct* This, const UStruct* Struct)
        {
            auto* CurrentStruct = This;
            do {
                if (CurrentStruct == Struct)
                {
                    return true;
                }
                CurrentStruct = CurrentStruct->GetSuperStruct();
            }
            while (CurrentStruct);
            return false;
        }

    public:
        /**
         * Checks if this struct is a child of the provided one
         */
        auto IsChildOf(UStruct* Struct) -> bool
        {
            return IsChildOfInternal(this, Struct);
        }

        auto IsChildOf(const UStruct* Struct) const -> bool
        {
            return IsChildOfInternal(this, Struct);
        }

        template<UObjectDerivative UObjectDerivedType>
        auto IsChildOf() const -> bool
        {
            return IsChildOf(UObjectDerivedType::StaticClass());
        }

        /**
         * Iterates properties of this object and calls the provided function on each of them
         * Will stop the iteration once the callable returns Break
         * @deprecated Use TFieldRange<FProperty>(struct, EFieldIterationFlags::IncludeDeprecated) directly
         */
        [[deprecated("Use TFieldRange<FProperty>(struct, EFieldIterationFlags::IncludeDeprecated) directly")]]
        auto ForEachProperty() -> TFieldRange<FProperty>;

        /**
         * Iterates over all functions in this struct.
         * Uses TFieldRange for optimized iteration (backwards compatible with range-based for).
         * @deprecated Use TFieldRange<UFunction>(struct, EFieldIterationFlags::None) directly
         */
        [[deprecated("Use TFieldRange<UFunction>(struct, EFieldIterationFlags::None) directly")]]
        auto ForEachFunction() -> TFieldRange<UFunction>;

        /**
         * Iterates over all super structs in the inheritance chain.
         * Uses TSuperStructRange for optimized iteration (backwards compatible with range-based for).
         * @deprecated Use TSuperStructRange(struct) directly
         */
        [[deprecated("Use TSuperStructRange(struct) directly")]]
        auto ForEachSuperStruct() -> TSuperStructRange;

        /**
         * Iterates every property starting with the properties from the child context and then iterating every super struct and calls the provided function on each of them
         * Will stop the iteration once the callable returns Break
         * @deprecated Use TFieldRange<FProperty>(struct, EFieldIterationFlags::Default) directly
         */
        [[deprecated("Use TFieldRange<FProperty>(struct, EFieldIterationFlags::Default) directly")]]
        auto ForEachPropertyInChain() -> TFieldRange<FProperty>;

        /**
         * Iterates every property in every super struct starting at the highest parent and calls the provided function on each of them
         * Will stop the iteration once the callable returns Break
         * @deprecated Use TReverseFieldRange<FProperty>(struct, EFieldIterationFlags::IncludeDeprecated) directly
         */
        [[deprecated("Use TReverseFieldRange<FProperty>(struct, EFieldIterationFlags::IncludeDeprecated) directly")]]
        auto OrderedForEachPropertyInChain() -> TReverseFieldRange<FProperty>;

        /**
         * Iterates every function in every super struct and calls the provided function on each of them
         * Will stop the iteration once the callable returns Break
         * @deprecated Use TFieldRange<UFunction>(struct, EFieldIterationFlags::IncludeAll) directly
         */
        [[deprecated("Use TFieldRange<UFunction>(struct, EFieldIterationFlags::IncludeAll) directly")]]
        auto ForEachFunctionInChain() -> TFieldRange<UFunction>;

        /**
         * Finds a property by FName
         * Returns the property or nullptr if one isn't found
         */
        FProperty* FindProperty(FName PropertyName);

        /**
         * Returns true if either 'ChildProperties' or 'Children' is non-nullptr
         */
        bool HasChildren();

        FProperty* GetFirstProperty();

        inline int32 GetStructureSize() const
        {
            // Temporary implementation of 'Align' from AlignmentTemplates.h.
            // Remove when/if we have a generic implementation.
            auto Align = [](int32 Val, uint64 Alignment) {
                return (int32)(((uint64)Val + Alignment - 1) & ~(Alignment - 1));
            };
            return Align(GetPropertiesSize(), GetMinAlignment());
        }
    };

    /*-----------------------------------------------------------------------------
        UScriptStruct.
    -----------------------------------------------------------------------------*/

    /**
     * Reflection data for a standalone structure declared in a header or as a user defined struct
     */
    class RC_UE_API UScriptStruct : public UStruct
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UScriptStruct, CoreUObject, CASTCLASS_UScriptStruct);

    public:
        struct RC_UE_API ICppStructOps
        {
            static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

        public:
#include <MemberVariableLayout_HeaderWrapper_UScriptStruct__ICppStructOps.hpp>

        public:
            // Wrappers for virtual engine functions
            void Construct(void* Dest);
            void Destruct(void *Dest);
            bool Copy(void* Dest, void const* Src, int32 ArrayDim);
        };

    public:
#include <MemberVariableLayout_HeaderWrapper_UScriptStruct.hpp>

    public:
        int32 GetSize();

        /**
         * Returns the struct acting as a parent to this struct
         * Can totally return nullptr since most structs do not have a parent struct
         */
        auto GetSuperScriptStruct() -> UScriptStruct*;

        /**
         * Checks if the struct has any of the provided flags set
         * Returns true if at least one of the provided struct flags is set
         */
        inline auto HasAnyStructFlags(EStructFlags flags_to_check) const
        {
            return (GetStructFlags() & flags_to_check) != 0;
        }

        /**
         * Checks if the struct has all of the provided flags set
         * Returns true only if all of the provided struct flags are set
         */
        inline auto HasAllStructFlags(EStructFlags flags_to_check) const
        {
            return (GetStructFlags() & flags_to_check) == flags_to_check;
        }

        void CopyScriptStruct(void* Dest, void const* Src, int32 ArrayDim = 1)/* const*/;
    };

    /*-----------------------------------------------------------------------------
        UFunction.
    -----------------------------------------------------------------------------*/

    //
    // Reflection data for a replicated or Kismet callable function.
    //
    class RC_UE_API UFunction : public UStruct
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UFunction, CoreUObject, CASTCLASS_UFunction)

    public:
#include <MemberVariableLayout_HeaderWrapper_UFunction.hpp>

        std::function<void(UObject*, FFrame&, void* const)>*& GetFunc()
        {
            return GetFunc419();
        }

    public:
        /**
         * Retrieves the flag set on this function object
         * Function calls define their type, metadata, access and additional attributes
         */
        const uint32& GetFunctionFlags() const;
        uint32& GetFunctionFlags();

        /**
         * Checks if function has any of the flags specified
         * Returns true if either of the provided flags are set on the function
         */
        inline auto HasAnyFunctionFlags(EFunctionFlags function_flags) -> bool
        {
            return (GetFunctionFlags() & function_flags) != 0;
        }

        /**
         * Checks if function has all of the specified flags
         * Returns true only if all of the provided flags are set on the function
         */
        inline auto HasAllFunctionFlags(EFunctionFlags function_flags) -> bool
        {
            return (GetFunctionFlags() & function_flags) == function_flags;
        }

        /**
         * Returns amount of parameters of the function, including
         * output parameters and the return value if it is defined for the function
         */
        //auto GetNumParms() -> uint8_t;

        //uint16 GetReturnValueOffset();

        /**
         * Returns the total size of the function params used by the function
         * Keep in mind that this value is different from properties size, as it includes
         * only function parameters and does not include other local variables
         */
        //auto GetParmsSize() -> int32_t;

        /**
         * Retrieves the return property of the function, or returns nullptr
         * if the function does not have a return value
         */
        auto GetReturnProperty() -> FProperty*;

        /**
         * Retrieves the pointer to the underlying native function
         * For script functions that would point to UObject::ProcessInternal, which handles
         * execution of the Blueprint VM bytecode, otherwise it would point to the actual native function
         */
        auto GetFuncPtr() -> UnrealScriptFunction;

        /**
         * Updates function pointer to the new value
         * The provided function will be executed when this UFunction object is called
         */
        auto SetFuncPtr(UnrealScriptFunction NewFuncPtr) -> void;

        auto RegisterPreHook(const UnrealScriptFunctionCallable& PreCallback, void* CustomData = nullptr) -> CallbackId;
        auto RegisterPostHook(const UnrealScriptFunctionCallable& PostCallback, void* CustomData = nullptr) -> CallbackId;

        // Same as 'RegisterPre/PostHook' except it only fires if the instance pointer matches the context pointer.
        // Only safe if you can guarantee the validity of the instance passed to these functions.
        auto RegisterPreHookForInstance(const UnrealScriptFunctionCallable& PreCallback, void* CustomData = nullptr, UObject* FireOnInstance = nullptr) -> CallbackId;
        auto RegisterPostHookForInstance(const UnrealScriptFunctionCallable& PostCallback, void* CustomData = nullptr, UObject* FireOnInstance = nullptr) -> CallbackId;

        auto UnregisterHook(CallbackId CallbackId) -> bool;
        auto UnregisterAllHooks() -> void;
        auto GetFunctionHookCallbackData(CallbackId) -> UnrealScriptCallbackData*;
    protected:
        auto GetFunctionHookData() -> UnrealScriptFunctionData&;
    };

    /*-----------------------------------------------------------------------------
        UDelegateFunction.
    -----------------------------------------------------------------------------*/

    //
    // Function definition used by dynamic delegate declarations.
    //
    class RC_UE_API UDelegateFunction : public UFunction
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UDelegateFunction, CoreUObject, CASTCLASS_UDelegateFunction)
    };

    /*-----------------------------------------------------------------------------
        USparseDelegateFunction.
    -----------------------------------------------------------------------------*/

    //
    // Function definition used by sparse dynamic delegate declarations.
    //
    class RC_UE_API USparseDelegateFunction : public UDelegateFunction
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(USparseDelegateFunction, CoreUObject, CASTCLASS_USparseDelegateFunction)

    public:
#include <MemberVariableLayout_HeaderWrapper_USparseDelegateFunction.hpp>
    };

    /*-----------------------------------------------------------------------------
        UEnum.
    -----------------------------------------------------------------------------*/

    // The "UEnum::Names" pair is "TPair<FName, uint8>" in earlier engine versions
    // This can cause a problem, therefore, you should be careful when using this pair
    // This is a case where we perhaps should abstract this array and deny direct access to the TArray
    using FEnumNamePair = TPair<FName, int64_t>;
    using FEnumNameArray = TArray<FEnumNamePair>;

    //
    // Reflection data for an enumeration.
    //
    class RC_UE_API UEnum : public UField
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UEnum, CoreUObject, CASTCLASS_UEnum)

    public:
        enum class ECppForm
        {
            /**
             * Regular enums are declared using the normal enum keyword
             * Their constants are unscoped and usually prefixed with enum name
             */
            Regular,
            /**
             * Namespaced enums use the namespace for enum name + enum keyword for type
             * They are scoped to their namespace
             */
            Namespaced,
            /**
             * Enum classes are C++11 enum class enumerations that are properly scoped
             * They can also specify any integral underlying type
             */
            EnumClass
        };

    private:
        TArray<TPair<FName, uint8>>& GetEnumNamesOldUnsafe();
        TArray<TPair<FName, int64>>& GetEnumNamesNewUnsafe();

        // UE 5.7+ FNameData - provides access to the new parallel array structure
        struct RC_UE_API FNameData
        {
            static constexpr uintptr_t TagDynamic = 0x1;
            static constexpr uintptr_t MaskPointer = ~TagDynamic;

            uintptr_t TaggedNames;
            uintptr_t TaggedValues;
            int32 NumValues;

            [[nodiscard]] int32 Num() const { return NumValues; }

            [[nodiscard]] bool IsValidIndex(int32 Index) const
            {
                return Index >= 0 && Index < NumValues;
            }

            [[nodiscard]] bool IsDynamic() const
            {
                return (TaggedNames & TagDynamic) != 0;
            }

            [[nodiscard]] const FName* GetNames() const
            {
                return reinterpret_cast<const FName*>(TaggedNames & MaskPointer);
            }

            [[nodiscard]] FName* GetMutableNames()
            {
                return reinterpret_cast<FName*>(TaggedNames & MaskPointer);
            }

            [[nodiscard]] const int64* GetValues() const
            {
                return reinterpret_cast<const int64*>(TaggedValues & MaskPointer);
            }

            [[nodiscard]] int64* GetMutableValues()
            {
                return reinterpret_cast<int64*>(TaggedValues & MaskPointer);
            }

            [[nodiscard]] FName GetNameAt(int32 Index) const
            {
                return GetNames()[Index];
            }

            [[nodiscard]] int64 GetValueAt(int32 Index) const
            {
                return GetValues()[Index];
            }

            [[nodiscard]] TPair<FName, int64> operator[](int32 Index) const
            {
                return { GetNameAt(Index), GetValueAt(Index) };
            }

            // Convert static arrays to dynamic (mutable) arrays by copying.
            // This allows modification of enum names/values that were compiled-in.
            void MakeDynamic();

            // Reallocate arrays with new size, preserving existing data up to min(oldSize, newSize).
            // Automatically calls MakeDynamic() if not already dynamic.
            void Reallocate(int32 NewSize);
        };

        FNameData& GetEnumNameDataUnsafe();

    public:
#include <MemberVariableLayout_HeaderWrapper_UEnum.hpp>

    public:
        /**
         * Returns the array of enumeration constants and their values
         * Keep in mind that enumeration can have gaps as well as negative values
         * The last entry of the array will always be a _MAX constant
         */
        auto GetEnumNames() -> TArray<TPair<FName, int64>>;
        auto GetEnumNameByIndex(int32 Index) -> TPair<FName, int64>;
        void GetEnumNamesAsVector(std::vector<std::pair<FName, int64>>& OutNames);

        /**
         * Returns the flags set on the enumeration object
         * Will return EEnumFlags::None on older UE versions
         */
        auto GetEnumFlags() -> EEnumFlags;

        auto ForEachName() -> Generator<TPair<FName, int64>>
        {
            if (Version::IsBelow(4, 15))
            {
                for (TPair<FName, uint8>& Elem : GetEnumNamesOldUnsafe()) {
                    co_yield TPair<FName, int64>{Elem.Key, Elem.Value};
                }
            }
            else if (Version::IsBelow(5, 7))
            {
                for (TPair<FName, int64>& Elem : GetEnumNamesNewUnsafe()) {
                    co_yield Elem;
                }
            }
            else
            {
                // UE 5.7+: FNameData uses parallel arrays with tagged pointers.
                // The TagDynamic bit must be set after InitializeFromCompiledInData() is called.
                // Skip enums that haven't been initialized yet.
                auto& NameData = GetEnumNameDataUnsafe();
                if (!NameData.IsDynamic()) {
                    co_return;
                }
                for (int32 i = 0; i < NameData.Num(); ++i) {
                    co_yield NameData[i];
                }
            }
        }

        /**
        * Gets the name for the enumerator with the input value, if found.
        *
        * @param Value of the enum to find.
        *
        * @return Name of the enumerator, if found, as an FName.
        */
        FName GetNameByValue(int64 Value);

        /**
        * @return   The number of enumerators.
        */
        int32 NumEnums();

        /**
        * Find the longest common prefix of all items in the enumeration.
        *
        * @return   the longest common prefix between all items in the enum.  If a common prefix
        *           cannot be found, returns the full name of the enum.
        */
        StringType GenerateEnumPrefix();


        /**
        * Edits the name of the enumerator at the given location in the names array.
        *
        * @note Wrapper around the TArray method to handle UEnum names array changing types
        * after UE 4.14
        *
        * @param Index Location in array of the element to edit.
        * @param NewName New name as an FName.
        */
        void EditNameAt(int32 Index, FName NewName);

        /**
        * Edits the value of the enumerator at the given location in the names array.
        *
        * @note Wrapper around the TArray method to handle UEnum names array changing types
        * after UE 4.14
        *
        * @param Index Location in array of the element to edit.
        * @param NewValue New value to use.
        */
        void EditValueAt(int32 Index, int64 NewValue);

        /**
         * Removes an element (or elements) at given location in UEnum names array,
         * optionally shrinking the array.
         *
         * @note Wrapper around TArray::RemoveAt to handle UEnum names array changing types
         * after UE 4.14
         *
         * @param Index Location in array of the element to remove.
         * @param Count (Optional) Number of elements to remove. Default is 1.
         * @param bAllowShrinking (Optional) Tells if this call can shrink array if suitable after remove. Default is true.
         */
        void RemoveFromNamesAt(int32 Index, int32 Count = 1, EAllowShrinking AllowShrinking = EAllowShrinking::Default);
        UE_ALLOWSHRINKING_BOOL_DEPRECATED("RemoveFromNamesAt")
        FORCEINLINE void RemoveFromNamesAt(int32 Index, int32 Count, bool bAllowShrinking)
        {
            RemoveFromNamesAt(Index, Count, bAllowShrinking ? EAllowShrinking::Yes : EAllowShrinking::No);
        };


        /**
         *
         * Inserts a given element into the UEnum names array at given location. Move semantics
         * version.  Optionally shifts all enum values greater than inserted value by one.
         *
         * @note Wrapper around TArray::RemoveAt to handle UEnum names array changing types
         * after UE 4.14
         *
         * @param Item The element to insert.
         * @param Index Tells where to insert the new elements.
         * @param bShiftValues (Optional) Tells if this call should shift enum values greater than the inserted value. Default is false.
         * @returns Location at which the insert was done, or -1 if failed.
         *
         */
        int32 InsertIntoNames(const TPair<FName, int64>& Item, int32 Index, bool bShiftValues = false);


        /**
         * Retrieves the enumeration index associated with the provided enum name
         * Returns INDEX_NONE if there is no enumeration constant with the provided name
         */
        //auto GetIndexByName(const std::wstring& name) -> int32_t;

        //auto GetValueByName(const std::wstring& name) -> int64_t;
    };

    class RC_UE_API UUserDefinedEnum : public UEnum
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UUserDefinedEnum, Engine);
    };

    /*-----------------------------------------------------------------------------
        FImplementedInterface.
    -----------------------------------------------------------------------------*/

    struct RC_UE_API FImplementedInterface
    {
        UClass* Class;
        int32_t PointerOffset;
        bool bImplementedByK2;
    };
    
    /** A struct that maps a string name to a native function */
    struct RC_UE_API FNativeFunctionLookup
    {
        FName Name;
        FNativeFuncPtr Pointer;

        FNativeFunctionLookup(FName InName, FNativeFuncPtr InPointer)
            :    Name(InName)
            ,    Pointer(InPointer)
        {}
    };

    /*-----------------------------------------------------------------------------
        UClass.
    -----------------------------------------------------------------------------*/
    class FObjectInitializer;
    /**
     * An object class.
     */
    class RC_UE_API UClass : public UStruct
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UClass, CoreUObject, CASTCLASS_UClass);
    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;
        
        typedef UObject*    (*ClassVTableHelperCtorCallerType)    (FVTableHelper& Helper);
        typedef UClass* (*StaticClassFunctionType)();
        
    public:
#include <MemberVariableLayout_HeaderWrapper_UClass.hpp>

    public:
        struct Offset
        {
            /* Temporary implementation, based on:
                ClassConstructorType ClassConstructor;
                ClassVTableHelperCtorCallerType ClassVTableHelperCtorCaller;
                ClassAddReferencedObjectsType ClassAddReferencedObjects;
                mutable uint32 ClassUnique:31;                                   // 0x??
                uint32 bCooked:1;                                                // 0x??
                EClassFlags ClassFlags;                                          // 0xCC
                EClassCastFlags ClassCastFlags;                                  // 0xD0
                UClass* ClassWithin;                                             // 0xD8
                UObject* ClassGeneratedBy;                                       // 0xE0
                FName ClassConfigName;                                           // 0xE8
                TArray<FRepRecord> ClassReps;                                    // 0xF0
                TArray<UField*> NetFields;                                       // 0x100 -
                int32 FirstOwnedClassRep = 0;                                    // 0x114 -0x4
                UObject* ClassDefaultObject;                                     // 0x118
                void* SparseClassData;                                           // 0x120
                UScriptStruct* SparseClassDataStruct;                            // 0x128
                TMap<FName, UFunction*> FuncMap;                                 // 0x130
                mutable TMap<FName, UFunction*> SuperFuncMap;                    // 0x180
                mutable FRWLock SuperFuncMapLock;                                // 0x??? ; size 0x8
                TArray<FImplementedInterface> Interfaces;                        // 0x1D8 ?
            //*/
            static int32_t class_config_name;
        };
    public:
        auto CreateDefaultObject() -> UObject*;

        auto HasAnyClassFlags(EClassFlags FlagsToCheck) -> bool;
        auto HasAllClassFlags(EClassFlags FlagsToCheck) -> bool;
        auto GetClassFlags() -> uint32&
        {
            return GetClassFlagsBase();
        }
        //auto GetClassWithin() -> UClass*;
        //auto GetClassConfigName() -> FName;
        //auto GetClassDefaultObject() -> UObject*;
        //auto GetInterfaces() -> TArray<FImplementedInterface>&;

        bool HasAnyCastFlag(EClassCastFlags FlagToCheck) const;
        bool HasAllCastFlags(EClassCastFlags FlagsToCheck) const;

        auto GetSuperClass() -> UClass* { return static_cast<UClass*>(GetSuperStruct()); }
        auto GetSuperClass() const -> const UClass* { return static_cast<const UClass*>(GetSuperStruct()); }

        uint64& GetClassCastFlags()
        {
            return GetClassCastFlagsBase();
        }
        const uint64& GetClassCastFlags() const
        {
            return GetClassCastFlagsBase();
        }
    };

    // TODO: Move these elsewhere
    class RC_UE_API UBlueprintGeneratedClass : public UClass
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UBlueprintGeneratedClass, Engine);
    };

    class RC_UE_API UWidgetBlueprintGeneratedClass : public UClass
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UWidgetBlueprintGeneratedClass, Engine);
    };

    class RC_UE_API UAnimBlueprintGeneratedClass : public UClass
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UAnimBlueprintGeneratedClass, Engine);
    };
}
