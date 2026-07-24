#pragma once

/*=============================================================================
    UnrealType.hpp: Unreal engine base type definitions.
=============================================================================*/
#include <Unreal/FField.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/TObjectPtr.hpp>
#include <Unreal/FWeakObjectPtr.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/FText.hpp>
#include <Unreal/FieldPath.hpp>
#include <Unreal/FSoftObjectPath.hpp>
#include <Unreal/PersistentObjectPtr.hpp>
#include <Unreal/SoftObjectPtr.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/Core/Containers/Map.hpp>
#include <Unreal/Core/Containers/Set.hpp>
#include <Unreal/Core/Containers/ScriptArray.hpp>

#include <Unreal/Core/Serialization/MemoryImage.hpp>

namespace RC::Unreal
{
    // Forward declarations
    class FString;
    class UEnum;
    class UScriptStruct;
    struct FImplementedInterface;

    /*-----------------------------------------------------------------------------
        FProperty.
    -----------------------------------------------------------------------------*/

    enum class EPropertyObjectReferenceType
    {
        None = 0,
        Strong = 1 << 0,
        Weak = 1 << 1,
    };

    namespace UEProperty_Private { class FProperty_DoNotUse; }
    
    /** Type of pointer provided for property API functions */
    enum class EPropertyPointerType
    {
        Direct = 0, /** Raw property access */
        Container = 1, /** Property access through its owner container */
    };

    namespace UE::GC
    {
        class FPropertyStack;
        class FSchemaBuilder;
    }

    class RC_UE_API FProperty : public FField
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FProperty, CASTCLASS_FProperty);
        DECLARE_VIRTUAL_TYPE(FProperty);

    public:
        static std::unordered_map<File::StringType, uint32> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_FProperty.hpp>

    private:
        FORCEINLINE void* ContainerVoidPtrToValuePtrInternal(void* ContainerPtr, int32 ArrayIndex) const
        {
            checkf((ArrayIndex >= 0) && (ArrayIndex < ArrayDim), TEXT("Array index out of bounds: %i from an array of size %i"), ArrayIndex, ArrayDim);
            check(ContainerPtr);

            if (0)
            {
                // in the future, these checks will be tested if the property is NOT relative to a UClass
                check(!GetOwner<UClass>()); // Check we are _not_ calling this on a direct child property of a UClass, you should pass in a UObject* in that case
            }

            return static_cast<uint8*>(ContainerPtr) + GetOffset_Internal() + static_cast<size_t>(GetElementSize()) * ArrayIndex;
        }

        FORCEINLINE void* ContainerUObjectPtrToValuePtrInternal(UObject* ContainerPtr, int32 ArrayIndex) const
        {
            checkf((ArrayIndex >= 0) && (ArrayIndex < ArrayDim), TEXT("Array index out of bounds: %i from an array of size %i"), ArrayIndex, ArrayDim);
            check(ContainerPtr);

            // in the future, these checks will be tested if the property is supposed to be from a UClass
            // need something for networking, since those are NOT live uobjects, just memory blocks
            check(static_cast<UObject*>(ContainerPtr)->IsValidLowLevel()); // Check it's a valid UObject that was passed in
            check(static_cast<UObject*>(ContainerPtr)->GetClass() != nullptr);
            check(GetOwner<UClass>()); // Check that the outer of this property is a UClass (not another property)

            // Check that the object we are accessing is of the class that contains this property
            checkf(static_cast<UObject*>(ContainerPtr)->IsA(GetOwner<UClass>()), TEXT("'%s' is of class '%s' however property '%s' belongs to class '%s'"),
                *static_cast<UObject*>(ContainerPtr)->GetName(),
                *static_cast<UObject*>(ContainerPtr)->GetClass()->GetName(),
                *GetName(),
                *GetOwner<UClass>()->GetName());

            if (0)
            {
                // in the future, these checks will be tested if the property is NOT relative to a UClass
                check(!GetOwner<UClass>()); // Check we are _not_ calling this on a direct child property of a UClass, you should pass in a UObject* in that case
            }

            return static_cast<uint8*>(static_cast<void*>(ContainerPtr)) + GetOffset_Internal() + static_cast<size_t>(GetElementSize()) * ArrayIndex;
        }
    public:
        /** Return offset of property from container base. */
        UE_FORCEINLINE_HINT int32 GetOffset_ForInternal() const
        {
            return GetOffset_Internal();
        }

        void LinkWithoutChangingOffset(FArchive& Ar)
        {
            LinkInternal(Ar);
        }

        int32 Link(FArchive& Ar)
        {
            LinkInternal(Ar);
            return SetupOffset();
        }

    protected:
        void LinkInternal(FArchive& Ar);
    public:
        /**
         * Returns the total size of the property, correctly handling the statically sized array properties
         * Equivalent to element size for other properties
         */
        // @TODO: Surely this can have an int32 overflow. This should probably return size_t. Just
        // need to audit all callers to make such a change.
        FORCEINLINE int32 GetSize() const
        {
            return GetArrayDim() * GetElementSize();
        }
        FORCEINLINE int32 GetSize() // TODO: Remove non-const version, kept in for backwards compatibility
        {
            return GetArrayDim() * GetElementSize();
        }

        /** Returns the property flags for this property */
        EPropertyFlags& GetPropertyFlags();
        const EPropertyFlags& GetPropertyFlags() const;

        UE_FORCEINLINE_HINT bool HasAnyPropertyFlags( uint64 FlagsToCheck ) const
        {
            return (GetPropertyFlags() & FlagsToCheck) != 0 || FlagsToCheck == CPF_AllFlags;
        }

        inline auto HasAllPropertyFlags(EPropertyFlags flags_to_check) -> bool
        {
            return ((GetPropertyFlags() & flags_to_check) == flags_to_check);
        }

        inline auto HasAllPropertyFlags(EPropertyFlags flags_to_check) const -> bool
        {
            return ((GetPropertyFlags() & flags_to_check) == flags_to_check);
        }

        /** See if the offset of this property is below the supplied container size */
        FORCEINLINE bool IsInContainer(int32 ContainerSize) const
        {
            return GetOffset_Internal() + GetSize() <= ContainerSize;
        }
        /** See if the offset of this property is below the supplied container size */
        FORCEINLINE bool IsInContainer(const UStruct* ContainerClass) const
        {
            return GetOffset_Internal() + GetSize() <= (ContainerClass ? ContainerClass->GetPropertiesSize() : MAX_int32);
        }

        /**
         *    Get the pointer to property value in a supplied 'container'.
         *    You can _only_ call this function on a UObject* or a uint8*. If the property you want is a 'top level' UObject property, you _must_
         *    call the function passing in a UObject* and not a uint8*. There are checks inside the function to verify this.
         *    @param    ContainerPtr            UObject* or uint8* to container of property value
         *    @param    ArrayIndex                In array case, index of array element we want
         */
        template<typename ValueType>
        FORCEINLINE ValueType* ContainerPtrToValuePtr(UObject* ContainerPtr, int32 ArrayIndex = 0) const
        {
            return static_cast<ValueType*>(ContainerUObjectPtrToValuePtrInternal(ContainerPtr, ArrayIndex));
        }

        template<typename ValueType>
        FORCEINLINE ValueType* ContainerPtrToValuePtr(void* ContainerPtr, int32 ArrayIndex = 0) const
        {
            return static_cast<ValueType*>(ContainerVoidPtrToValuePtrInternal(ContainerPtr, ArrayIndex));
        }

        template<typename ValueType>
        FORCEINLINE ValueType const* ContainerPtrToValuePtr(UObject const* ContainerPtr, int32 ArrayIndex = 0) const
        {
            return ContainerPtrToValuePtr<ValueType>(const_cast<UObject*>(ContainerPtr), ArrayIndex);
        }

        template<typename ValueType>
        FORCEINLINE ValueType const* ContainerPtrToValuePtr(void const* ContainerPtr, int32 ArrayIndex = 0) const
        {
            return ContainerPtrToValuePtr<ValueType>(const_cast<void*>(ContainerPtr), ArrayIndex);
        }

        auto GetCPPMacroType(FString& ExtendedTypeText) const -> FString;

        auto PassCPPArgsByRef() const -> bool;

        auto GetCPPType(FString* ExtendedTypeText = nullptr, uint32 CPPExportFlags = 0) const -> FString;

        auto GetCPPTypeForwardDeclaration() const -> FString;

        using EConvertFromTypeResult = int32; // Remove if/when we have an EConvertFromTypeResult implementation, safe to use if you know the underlying enum numbers
        using FPropertyTag = void*; // Remove if/when we have a FPropertyTag implementation, for now, probably a bad idea to call
        class FStructuredArchive { public: enum class FSlot {}; }; // Remove if/when we have a FStructuredArchive implementation, for now, probably a bad idea to call
        auto ConvertFromType(const FPropertyTag& Tag, FStructuredArchive::FSlot Slot, uint8* Data, UStruct* DefaultsStruct) -> EConvertFromTypeResult;

        /**
         * Determines whether the property values are identical.
         *
         * @param A    property data to be compared, already offset
         * @param B    property data to be compared, already offset
         * @param PortFlags allows caller more control over how the property values are compared
         * @return true if the property values are identical
         */
        auto Identical(const void* A, const void* B, uint32 PortFlags = 0) -> bool;

        /**
         * Determines whether the property values are identical.
         *
         * @param A property container of data to be compared, NOT offset
         * @param B property container of data to be compared, NOT offset
         * @param ArrayIndex
         * @param PortFlags allows caller more control over how the property values are compared
         * @return true if the property values are identical
         */
        auto Identical_InContainer(const void* A, const void* B, int32 ArrayIndex = 0, uint32 PortFlags = 0) -> bool;

        auto SerializeItem(FStructuredArchive::FSlot Slot, void* Value, void const* Defaults = nullptr) const -> void;

        using UPackageMap = void*; // Remove if/when we have a UPackageMap implementation, for now, probably a bad idea to call
        auto NetSerializeItem(FArchive& Ar, UPackageMap* Map, void* Data, TArray<uint8>* MetaData = nullptr) const -> bool;

        auto SupportsNetSharedSerialization() const -> bool;

        /**
         * Emits garbage collection reference information for this property
         * @param Schema The schema builder to emit references to
         * @param BaseOffset The base offset of the property's container
         * @param DebugPath Stack of properties for debugging
         */
        void EmitReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, UE::GC::FPropertyStack& DebugPath);

        /**
         * Exports the property value into the text string provided
         *
         * @param ValueStr string to serialize the property value into
         * @param PropertyValue property value to serialize
         * @param DefaultValue the default value of the property, or nullptr to serialize everything
         * @param Parent parent object on which the property is set
         * @param PortFlags the additional flags for property serialization
         * @param ExportRootScope the scope to create relative paths from, if the PPF_ExportsNotFullyQualified flag is passed in. If nullptr, the package containing the object will be used instead.
         */
        auto ExportTextItem(FString& ValueStr, const void* PropertyValue, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) -> void;

        void ExportText_Internal(FString& ValueStr, const void* PropertyValue, EPropertyPointerType PointerType, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const;

        void ExportTextItem_Direct(FString& ValueStr, const void* PropertyValue, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const
        {
            ExportText_Internal(ValueStr, PropertyValue, EPropertyPointerType::Direct, DefaultValue, Parent, PortFlags, ExportRootScope);
        }

        void ExportTextItem_InContainer(FString& ValueStr, const void* Container, const void* DefaultValue, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) const
        {
            ExportText_Internal(ValueStr, Container, EPropertyPointerType::Container, DefaultValue, Parent, PortFlags, ExportRootScope);
        }

        /**
         * Imports the property value from the provided text string
         *
         * @param Buffer the text to read the value from
         * @param Data the property value to serialize the data into
         * @param PortFlags the extra flags for parsing the value
         * @param OwnerObject the object owning this property's value
         * @param ErrorText
         * @return the remaining string after the value has been read, or nullptr if the value has not been read
         */
        const TCHAR* ImportText(const TCHAR* Buffer, void* Data, int32 PortFlags, UObject* OwnerObject, FOutputDevice* ErrorText) const;
        const TCHAR* ImportText_Internal(const TCHAR* Buffer, void* ContainerOrPropertyPtr, EPropertyPointerType PointerType, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const;
        const TCHAR* ImportText_Internal(const TCHAR* Buffer, void* ContainerOrPropertyPtr, int32 PortFlags, UObject* OwnerObject, FOutputDevice* ErrorText) const;

        /**
         * Import a text value
         * @param Buffer        Text representing the property value
         * @param Container    Pointer to the container that owns this property (either UObject pointer or a struct pointer)
         * @param OwnerObject    Object that owns the property container (if the container is an UObject then Container is also OwnerObject)
         * @param PortFlags    Flags controlling the behavior when importing the value
         * @param ErrorText    Output device for throwing warnings or errors on import
         * @returns Buffer pointer advanced by the number of characters consumed when reading the text value
         */
        const TCHAR* ImportText_InContainer(const TCHAR* Buffer, void* Container, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const
        {
            //Do not allow property import on Config properties when it's restricted
            if ((PortFlags & EPropertyPortFlags::PPF_RestrictImportTypes) && (GetPropertyFlags() & CPF_Config))
            {
                return nullptr;
            }
            if (Buffer == nullptr)
            {
                return nullptr;
            }

            //Imports should always process deprecated properties
            PortFlags |= EPropertyPortFlags::PPF_UseDeprecatedProperties;

            return ImportText_Internal(Buffer, Container, EPropertyPointerType::Container, OwnerObject, PortFlags, ErrorText);
        }

        /**
         * Import a text value
         * @param Buffer        Text representing the property value
         * @param PropertyPtr    Pointer to property value
         * @param OwnerObject    Object that owns the property
         * @param PortFlags    Flags controlling the behavior when importing the value
         * @param ErrorText    Output device for throwing warnings or errors on import
         * @returns Buffer pointer advanced by the number of characters consumed when reading the text value
         */
        const TCHAR* ImportText_Direct(const TCHAR* Buffer, void* PropertyPtr, UObject* OwnerObject, int32 PortFlags, FOutputDevice* ErrorText) const
        {
            //Do not allow property import on Config properties when it's restricted
            if ((PortFlags & EPropertyPortFlags::PPF_RestrictImportTypes) && (GetPropertyFlags() & CPF_Config))
            {
                return nullptr;
            }
            if (Buffer == nullptr)
            {
                return nullptr;
            }

            //Imports should always process deprecated properties
            PortFlags |= EPropertyPortFlags::PPF_UseDeprecatedProperties;

            return ImportText_Internal(Buffer, PropertyPtr, EPropertyPointerType::Direct, OwnerObject, PortFlags, ErrorText);
        }

        /** Allocates and initializes memory to hold a value this property represents */
        void* AllocateAndInitializeValue() const;

        /** Destroys and frees memory with a value this property represents */
        void DestroyAndFreeValue(void* InMemory);

        /**
         * Exports the property value to the string if it differs from the delta value specified
         *
         * @param ValueStr string to append the property value to
         * @param Data property value to serialize
         * @param Delta default property value, serialization is skipped if it is identical to the data
         * @param Parent parent object on which property is being serialized
         * @param PortFlags the additional flags for property serialization
         * @param ExportRootScope the scope to create relative paths from, if the PPF_ExportsNotFullyQualified flag is passed in
         * @return true if the value was different from delta and was actually serialized to string
         */
        auto ExportText_Direct(FString& ValueStr, const void* Data, const void* Delta, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = nullptr) -> bool;

        /**
         * Exports the property value to the string if it is different from the default value specified, in the container
         *
         * @param Index index of the value if the property represents the statically sized array
         * @param ValueStr string to serialize the value into
         * @param Data the pointer to the container with the property value
         * @param Delta the pointer to the container with the default property value
         * @param Parent the pointer to the UObject which property is being exported
         * @param PortFlags the additional flags for property serialization
         * @param ExportRootScope the scope to create relative paths from, if the PPF_ExportsNotFullyQualified flag is passed in
         * @return true if the value was different from delta and was actually serialized to string
         */
        auto ExportText_InContainer(int32 Index, FString& ValueStr, const void* Data, const void* Delta, UObject* Parent, int32 PortFlags, UObject* ExportRootScope = NULL) -> bool;

    public:
        /**
         * Copy the value for a single element of this property.
         * Behaves exactly the same as copy_complete_value for non-static sized array properties
         *
         * @param Dest the address where the value should be copied to
         * @param Src the address of the value to copy from
         */
        auto CopySingleValue(void* Dest, void const* Src) -> void;

        /**
         * Returns the hash value for an element of this property.
         */
        uint32 GetValueTypeHash(const void* Src) const;

        /**
         * Copies specified number of property values from src address to dest
         * Internal function, do not call directly!
         */
        void CopyValuesInternal(void* Dest, const void* Src, int32 Count) const;

        auto GetValueTypeHashInternal(const void* Src) const -> uint32;

        /**
         * Copy the value for all elements of this property.
         *
         * @param Dest the address where the value should be copied to
         * @param Src the address of the value to copy from
         */
        void CopyCompleteValue(void* Dest, const void* Src) const;

        auto CopyCompleteValue_InContainer(void* Dest, const void* Src) -> void;

        /**
         * Copy the value for a single element of this property. To the script VM.
         *
         * @param Dest the address where the value should be copied to
         * @param Src the address of the value to copy from. should be evaluated the same way as Dest
         */
        auto CopySingleValueToScriptVM(void* Dest, void const* Src) const -> void;

        /**
         * Copy the value for all elements of this property. To the script VM.
         *
         * @param Dest the address where the value should be copied to
         * @param Src the address of the value to copy from. should be evaluated the same way as Dest
         */
        auto CopyCompleteValueToScriptVM(void* Dest, void const* Src) const -> void;

        /**
         * Copy the value for a single element of this property. From the script VM.
         *
         * @param Dest the address where the value should be copied to
         * @param Src the address of the value to copy from. should be evaluated the same way as Dest
         */
        auto CopySingleValueFromScriptVM(void* Dest, void const* Src) const -> void;

        /**
         * Copy the value for all elements of this property. From the script VM.
         *
         * @param Dest the address where the value should be copied to
         * @param Src the address of the value to copy from. should be evaluated the same way as Dest
         */
        auto CopyCompleteValueFromScriptVM(void* Dest, void const* Src) const -> void;

        /**
         * Equivalent to the above functions, but using the container and aware of getters/setters when the container has them
         * (at UE 5.2 and above).
         */
        void CopyCompleteValueToScriptVM_InContainer( void* OutValue, void const* InContainer ) const;

        /**
         * Zeros the value for this property. The existing data is assumed valid (so for example this calls FString::Empty)
         * This only does one item and not the entire fixed size array.
         *
         * @param Data the address of the value for this property that should be cleared.
         */
        auto ClearValue(void* Data) -> void;
        auto ClearValue(void* Data) const -> void;

        /**
         * Zeros the value for this property. The existing data is assumed valid (so for example this calls FString::Empty)
         * This only does one item and not the entire fixed size array.
         *
         * @param Data the address of the container of the value for this property that should be cleared.
         */
        auto ClearValue_InContainer(void* Data, int32 ArrayIndex = 0) -> void;
        auto ClearValueInternal(void* Data) const -> void;

        /**
         * Destroys the value for this property. The existing data is assumed valid (so for example this calls FString::Empty)
         * This does the entire fixed size array.
         *
         * @param Dest the address of the value for this property that should be destroyed.
         */
        auto DestroyValue(void* Dest) -> void;
        auto DestroyValue(void* Dest) const -> void;

        /**
         * Destroys the value for this property. The existing data is assumed valid (so for example this calls FString::Empty)
         * This does the entire fixed size array.
         *
         * @param Dest the address of the container containing the value that should be destroyed.
         */
        auto DestroyValue_InContainer(void* Dest) -> void;
        auto DestroyValueInternal(void* Dest) const -> void;

        /**
         * Zeros, copies from the default, or calls the constructor for on the value for this property.
         * The existing data is assumed invalid (so for example this might indirectly call FString::FString,
         * This will do the entire fixed size array.
         *
         * @param Dest the address of the value for this property that should be cleared.
         */
        void InitializeValue( void* Dest ) const;

        /**
         * Zeros, copies from the default, or calls the constructor for on the value for this property.
         * The existing data is assumed invalid (so for example this might indirectly call FString::FString,
         * This will do the entire fixed size array.
         *
         * @param Dest the address of the container of value for this property that should be cleared.
         */
        /**
     * Zeros, copies from the default, or calls the constructor for on the value for this property. 
     * The existing data is assumed invalid (so for example this might indirectly call FString::FString,
     * This will do the entire fixed size array.
     *
     * @param    Dest        the address of the container of value for this property that should be cleared.
     */
        inline void InitializeValue_InContainer( void* Dest ) const
        {
            if (GetPropertyFlags() & CPF_ZeroConstructor)
            {
                FMemory::Memzero(ContainerPtrToValuePtr<void>(Dest), static_cast<size_t>(GetElementSize()) * GetArrayDim());
            }
            else
            {
                InitializeValueInternal(ContainerPtrToValuePtr<void>(Dest));
            }
        }
    protected:   
        auto InitializeValueInternal(void* Dest) const -> void;
    public:
        auto GetID() const -> FName;

        auto InstanceSubobjects(void* Data, void const* DefaultData, UObject* Owner, struct FObjectInstancingGraph* InstanceGraph) -> void;

        auto GetMinAlignment() const -> int32;

        /**
         * Returns true if this property, or in the case of e.g. array or struct properties any sub- property, contains a
         * UObject reference.
         * @param    EncounteredStructProps        used to check for recursion in arrays
         * @param    InReferenceType                type of object reference (strong / weak)
         *
         * @return true if property (or sub- properties) contains the specified type of UObject reference, false otherwise
         */
        auto ContainsObjectReference(TArray<const class FStructProperty*>& EncounteredStructProps, EPropertyObjectReferenceType InReferenceType = EPropertyObjectReferenceType::Strong) const -> bool;
        auto ContainsObjectReference(TArray<const class FStructProperty*>& EncounteredStructProps) const -> bool;

        /**
         * Returns true if this property, or in the case of e.g. array or struct properties any sub- property, contains a
         * weak UObject reference.
         *
         * @return true if property (or sub- properties) contain a weak UObject reference, false otherwise
         */
        bool ContainsWeakObjectReference() const
        {
            TArray<const FStructProperty*> EncounteredStructProps;
            return ContainsObjectReference(EncounteredStructProps, EPropertyObjectReferenceType::Weak);
        }

        /**
         * Returns true if this property, or in the case of e.g. array or struct properties any sub- property, contains a
         * UObject reference that is marked CPF_NeedCtorLink (i.e. instanced keyword).
         *
         * @return true if property (or sub- properties) contain a FObjectProperty that is marked CPF_NeedCtorLink, false otherwise
         */
        UE_FORCEINLINE_HINT bool ContainsInstancedObjectProperty() const
        {
            return (GetPropertyFlags()&(CPF_ContainsInstancedReference | CPF_InstancedReference)) != 0;
        }

        /**
         * Emits tokens used by realtime garbage collection code to passed in ReferenceTokenStream. The offset emitted is relative
         * to the passed in BaseOffset which is used by e.g. arrays of structs.
         */
        auto EmitReferenceInfo(UClass& OwnerClass, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps) -> void;

        auto SameType(const FProperty* Other) const -> bool;

        /**
         * Copies specified number of property values into the kismet VM
         * Internal function, do not call directly!
         */
        auto CopyValuesToScriptVMInternal(void* Dest, const void* Src, int32 Count) -> void;

        /**
         * Copies specified number of property values from the kismet VM
         * Internal function, do not call directly!
         */
        auto CopyValuesFromScriptVMInternal(void* Dest, const void* Src, int32 Count) -> void;
    protected:
        auto CopyValuesFromScriptVMInternal_Impl(void* Dest, const void* Src, int32 Count) -> void;
        auto CopyValuesToScriptVMInternal_Impl(void* Dest, const void* Src, int32 Count) -> void;

    public:
        /**
         * Returns whether this type has a special state for an unset TOptional meaning the size TOptional<T> and T are the same.
         * Properties must implement this function explicitly even if they do not have such a state.
         * @see Optional.h - HasIntrusiveUnsetOptionalState
         * @see FOptionalProperty
         */
        bool HasIntrusiveUnsetOptionalState();

        /**
         * Initialize the value at the given address to an unset TOptional using an intrusive state rather than a trailing boolean.
         * @see TOptional::TOptional
         * @see Constructor taking FIntrusiveUnsetOptionalState
         */
        void InitializeIntrusiveUnsetOptionalValue(void* Data) const;

        /**
         * Returns whether an optional value of this inner type is unset. Only valid to call if HasIntrusiveUnsetOptionalState returns true.
         * Equivalent to TOptional<T>::IsSet()
         * @see operator==(FIntrusiveUnsetOptionalState)
         *
         * @param Data Address of value to inspect, already offset.
         * @return true if the value is unset
         */
        bool IsIntrusiveOptionalValueSet(const void* Data) const;

        /**
         * Set the value to its special unset state. Equivalent to TOptional<T>::Reset. Only valid to call if HasIntrusiveUnsetOptionalState returns true.
         * @see operator=(FIntrusiveUnsetOptionalState)
         *
         * @param Data Address of the value, already offset.
         */
        void ClearIntrusiveOptionalValue(void* Data) const;

        /**
         * For properties returning true from HasIntrusiveUnsetOptionalState which also contain object references,
         * emit information for the garbage collector to safely gather the references from the value whether the
         * optional value is set or unset.
         */
        void EmitIntrusiveOptionalReferenceInfo(UE::GC::FSchemaBuilder& Schema, int32 BaseOffset, TArray<const FStructProperty*>& EncounteredStructProps, UE::GC::FPropertyStack& DebugPath);

        //auto copy_values_internal_impl(void* dest, void const* src, int32 count);

    private:
        /** Set the alignment offset for this property 
         * @return the size of the structure including this newly added property
        */
        int32 SetupOffset();

    protected:
        friend class FMapProperty;
        friend class UEProperty_Private::FProperty_DoNotUse;

        void SetOffset_Internal(int32 NewOffset);

    };

    class FPropertyHelpers
    {
    public:
        static COREUOBJECT_API const TCHAR* ReadToken( const TCHAR* Buffer, FString& Out, bool DottedNames = false);

        // @param Out Appended to
        static COREUOBJECT_API const TCHAR* ReadToken( const TCHAR* Buffer, FStringBuilderBase& Out, bool DottedNames = false);
    };

    namespace UEProperty_Private
    {
        /** FProperty methods FOR INTERNAL USE ONLY -- only authorized users should be making use of this. -- DO NOT USE! */
        class FProperty_DoNotUse
        {
        public:
            /** 
             * To facilitate runtime binding with native C++ data-members, we need 
             * a way of updating a property's generated offset.
             * This is needed for pre-generated properties, which are then loaded 
             * later, and fixed up to point at explicitly mapped C++ data-members.
             * 
             * Explicitly exposed for this singular case -- DO NOT USE otherwise.
             */
            static void Unsafe_AlterOffset(FProperty& Property, const int32 OffsetOverride)
            {
                Property.SetOffset_Internal(OffsetOverride);
            }
        };
    }

    // ===================================================================
    // TPROPERTY TEMPLATES
    // Generic property templates for C++ types
    // From: TProperty.hpp
    // ===================================================================

    /** Implements common operations for the provided template type */
    template<typename InTCppType>
    class TPropertyTypeFundamentals
    {
    public:
        typedef InTCppType TCppType;
        enum
        {
            CPPSize = sizeof(TCppType),
            CPPAlignment = alignof(TCppType)
        };

        /** Convert the address of a value of the property to the proper type */
        FORCEINLINE static auto GetPropertyValuePtr(const void* Value) -> const TCppType*
        {
            return std::bit_cast<const TCppType*>(Value);
        }

        /** Convert the address of a value of the property to the proper type */
        FORCEINLINE static auto GetPropertyValuePtr(void* Value) -> TCppType*
        {
            return std::bit_cast<TCppType*>(Value);
        }

        /** Get the value of the property from an address */
        FORCEINLINE static auto GetPropertyValue(const void* Value) -> const TCppType&
        {
            return *GetPropertyValuePtr(Value);
        }

        /** Get the default value of the cpp type, just the default constructor, which works even for things like int32 */
        FORCEINLINE static auto GetDefaultPropertyValue() -> TCppType
        {
            return TCppType();
        }

        /** Get the value of the property from an address, unless it is NULL, then return the default value */
        FORCEINLINE static auto GetOptionalPropertyValue(const void* Value) -> TCppType
        {
            return Value ? GetPropertyValue(Value) : GetDefaultPropertyValue();
        }

        /** Set the value of a property at an address */
        FORCEINLINE static auto SetPropertyValue(void* PropertyValue, const TCppType& Value) -> void
        {
            *GetPropertyValuePtr(PropertyValue) = Value;
        }

        /** Initialize the value of a property at an address, this assumes over uninitialized memory */
        FORCEINLINE static auto InitializePropertyValue(void* Value) -> TCppType*
        {
            return new (Value) TCppType();
        }

        /** Destroy the value of a property at an address */
        FORCEINLINE static auto DestroyPropertyValue(void* Value) -> void
        {
            GetPropertyValuePtr(Value)->~TCppType();
        }
    };

    /** Generic property implementation for standard C++ types */
    template<typename InTCppType, class TInPropertyBaseClass>
    class TProperty : public TInPropertyBaseClass, public TPropertyTypeFundamentals<InTCppType>
    {
    public:
        typedef InTCppType TCppType;
        typedef TInPropertyBaseClass Super;
        typedef TPropertyTypeFundamentals<InTCppType> TTypeFundamentals;

        /** Convert the address of a container to the address of the property value, in the proper type */
        FORCEINLINE auto GetPropertyValuePtrInContainer(const void* A, int32_t ArrayIndex = 0) -> const TCppType*
        {
            AssetTypeEquality();
            return TTypeFundamentals::GetPropertyValuePtr(Super::template ContainerPtrToValuePtr<void>(A, ArrayIndex));
        }

        /** Convert the address of a container to the address of the property value, in the proper type */
        FORCEINLINE auto GetPropertyValuePtrInContainer(void* A, int32_t ArrayIndex = 0) -> TCppType*
        {
            AssetTypeEquality();
            return TTypeFundamentals::GetPropertyValuePtr(Super::template ContainerPtrToValuePtr<void>(A, ArrayIndex));
        }

        /** Get the value of the property from a container address */
        FORCEINLINE auto GetPropertyValueInContainer(void const* A, int32_t ArrayIndex = 0) -> TCppType const&
        {
            return *GetPropertyValuePtrInContainer(A, ArrayIndex);
        }

        /** Get the value of the property from a container address, unless it is NULL, then return the default value */
        FORCEINLINE auto GetOptionalPropertyValueInContainer(const void* A, int32_t ArrayIndex = 0) -> TCppType
        {
            AssetTypeEquality();
            return A ? GetPropertyValueInContainer(A, ArrayIndex) : TTypeFundamentals::GetDefaultPropertyValue();
        }

        /** Set the value of a property in a container */
        FORCEINLINE auto SetPropertyValueInContainer(void* A, const TCppType& Value, int32_t ArrayIndex = 0) -> void
        {
            *GetPropertyValuePtrInContainer(A, ArrayIndex) = Value;
        }
    protected:
        auto InitializeValueImpl(void* Dest) -> void
        {
            AssetTypeEquality();
            for (int32_t i = 0; i < this->GetArrayDim(); i++)
            {
                TTypeFundamentals::InitializePropertyValue((uint8_t*)Dest + i * this->GetElementSize());
            }
        }

        auto DestroyValueImpl(void* Dest) -> void
        {
            AssetTypeEquality();
            for (int32_t i = 0; i < this->GetArrayDim(); i++)
            {
                TTypeFundamentals::DestroyPropertyValue((uint8_t*) Dest + i * this->GetElementSize());
            }
        }

        auto ClearValueImpl(void* Data) -> void
        {
            AssetTypeEquality();
            TTypeFundamentals::SetPropertyValue(Data, TTypeFundamentals::GetDefaultPropertyValue());
        }

        auto CopyValuesInternalImpl(void* Dest, void const* Src, int32_t Count) -> void
        {
            AssetTypeEquality();
            for (int32_t i = 0; i < Count; i++)
            {
                TTypeFundamentals::GetPropertyValuePtr(Dest)[i] = TTypeFundamentals::GetPropertyValuePtr(Src)[i];
            }
        }

        FORCEINLINE auto AssetTypeEquality()
        {
            if (this->GetElementSize() != TTypeFundamentals::CPPSize)
            {
                throw std::runtime_error("Type equality assertion failed: GetElementSize() != TTypeFundamentals::CPPSize");
            }
        }
    };

    template<typename InTCppType, class TInPropertyBaseClass>
    class TProperty_WithEqualityAndSerializer : public TProperty<InTCppType, TInPropertyBaseClass>
    {
    public:
        typedef TProperty<InTCppType, TInPropertyBaseClass> Super;
        typedef InTCppType TCppType;
        typedef typename Super::TTypeFundamentals TTypeFundamentals;
    protected:
        auto IdenticalImpl(const void* A, const void* B, uint32_t PortFlags) -> bool
        {
            // RHS is the same as TTypeFundamentals::GetOptionalPropertyValue(B) but avoids an unnecessary copy of B
            return TTypeFundamentals::GetPropertyValue(A) == (B ? TTypeFundamentals::GetPropertyValue(B) : TTypeFundamentals::GetDefaultPropertyValue());
        }

        //virtual void SerializeItem(FStructuredArchive::FSlot Slot, void *Value, void const *Defaults) const override {
        //    Slot << *TTypeFundamentals::GetPropertyValuePtr(Value);
        //}
    };

    // From: https://stackoverflow.com/a/22592618
    template<class SupposedTProperty>
    struct IsTPropertyHelper
    {
    private:
#pragma warning(disable: 4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"
        template<class InTCppType, class TInPropertyBaseClass>
        static decltype(static_cast<const ::RC::Unreal::TProperty<InTCppType, TInPropertyBaseClass>&>(std::declval<SupposedTProperty>()), std::true_type{})
        test(const ::RC::Unreal::TProperty<InTCppType, TInPropertyBaseClass>&);

        static std::false_type test(...);
#pragma clang diagnostic pop
#pragma warning(default: 4068)
    public:
        static constexpr bool value = decltype(IsTPropertyHelper::test(std::declval<SupposedTProperty>()))::value;
    };
    template<class SupposedTProperty>
    inline constexpr bool IsTProperty = IsTPropertyHelper<SupposedTProperty>::value;

    // ===================================================================
    // NUMERIC PROPERTIES
    // ===================================================================

    class RC_UE_API FNumericProperty : public FProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FNumericProperty, CASTCLASS_FNumericProperty);
        DECLARE_VIRTUAL_TYPE(FNumericProperty);

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
        /** Return true if this property is for a floating point number **/
        auto IsFloatingPoint() const -> bool;

        /** Return true if this property is for a integral or enum type **/
        auto IsInteger() const -> bool;

        /** Return the UEnum if this property is a FByteProperty with a non-null Enum **/
        auto GetIntPropertyEnum() const -> UEnum*;

        // TODO: The vtable offset generator isn't currently capable of handling multiple functions with the same name
        //       As a result, these two functions map to the same offset
        auto SetIntPropertyValue(void* Data, uint64 Value) const -> void;
        auto SetIntPropertyValue(void* Data, int64 Value) const -> void;

        /**
         * Set the value of a floating point property type
         * @param data - pointer to property data to set
         * @param value - Value to set data to
        **/
        auto SetFloatingPointPropertyValue(void* Data, double Value) -> void;

        /**
         * Set the value of any numeric type from a string point
         * @param data - pointer to property data to set
         * @param value - Value (as a string) to set
         * CAUTION: This routine does not do enum name conversion
        **/
        auto SetNumericPropertyValueFromString(void* Data, TCHAR const* Value) -> void;

        /**
         * Gets the value of a signed integral property type
         * @param data - pointer to property data to get
         * @return Data as a signed int
        **/
        auto GetSignedIntPropertyValue(void* Data) -> int64;

        /**
         * Gets the value of an unsigned integral property type
         * @param data - pointer to property data to get
         * @return Data as an unsigned int
        **/
        auto GetUnsignedIntPropertyValue(void const* Data) -> uint64;

        /**
         * Gets the value of an floating point property type
         * @param data - pointer to property data to get
         * @return Data as a double
        **/
        auto GetFloatingPointPropertyValue(void const* Data) -> double;

        /**
         * Get the value of any numeric type and return it as a string
         * @param data - pointer to property data to get
         * @return Data as a string
         * CAUTION: This routine does not do enum name conversion
        **/
        auto GetNumericPropertyValueToString(void const* Data) -> FString;

        auto CanHoldDoubleValueInternal(double Value) const -> bool;

        auto CanHoldSignedValueInternal(int64 Value) const -> bool;

        auto CanHoldUnsignedValueInternal(uint64 Value) const -> bool;

        /** Return true if this property is a FByteProperty with a non-null Enum **/
        auto IsEnum() -> bool
        {
            return !!GetIntPropertyEnum();
        }
    };

    template<typename InTCppType>
    class TProperty_Numeric : public TProperty_WithEqualityAndSerializer<InTCppType, FNumericProperty>
    {
    public:
        typedef TProperty_WithEqualityAndSerializer<InTCppType, FNumericProperty> Super;
        typedef InTCppType TCppType;
        typedef typename Super::TTypeFundamentals TTypeFundamentals;

    public:
        auto IsUnsignedInteger() -> bool
        {
            return std::is_unsigned_v<TCppType>;
        }

        auto SetUnsignedIntPropertyValue(void* data, uint64_t value) -> void
        {
            if (!std::is_integral_v<TCppType>)
            {
                throw std::runtime_error("Cannot set floating point property value to integral value");
            }
            TTypeFundamentals::SetPropertyValue(data, (TCppType) value);
        }

        /**
         * Set the value of a signed integral property type
         * @param data - pointer to property data to set
         * @param value - Value to set data to
        **/
        auto SetSignedIntPropertyValue(void* data, int64_t value) -> void
        {
            if (!std::is_integral_v<TCppType>)
            {
                throw std::runtime_error("Cannot set floating point property value to integral value");
            }
            TTypeFundamentals::SetPropertyValue(data, (TCppType) value);
        }
    };

    // Numeric property concrete types

    class RC_UE_API FByteProperty : public TProperty_Numeric<uint8>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FByteProperty, CASTCLASS_FByteProperty);
        DECLARE_VIRTUAL_TYPE(FByteProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FByteProperty.hpp>
    };

    class RC_UE_API FInt8Property : public TProperty_Numeric<int8>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FInt8Property, CASTCLASS_FInt8Property);
        DECLARE_VIRTUAL_TYPE(FInt8Property);
    };

    class RC_UE_API FInt16Property : public TProperty_Numeric<int16>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FInt16Property, CASTCLASS_FInt16Property);
        DECLARE_VIRTUAL_TYPE(FInt16Property);
    };

    class RC_UE_API FIntProperty : public TProperty_Numeric<int32>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FIntProperty, CASTCLASS_FIntProperty);
        DECLARE_VIRTUAL_TYPE(FIntProperty);
    };

    class RC_UE_API FInt64Property : public TProperty_Numeric<int64>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FInt64Property, CASTCLASS_FInt64Property);
        DECLARE_VIRTUAL_TYPE(FInt64Property);
    };

    class RC_UE_API FUInt16Property : public TProperty_Numeric<uint16>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FUInt16Property, CASTCLASS_FUInt16Property);
        DECLARE_VIRTUAL_TYPE(FUInt16Property);
    };

    class RC_UE_API FUInt32Property : public TProperty_Numeric<uint32>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FUInt32Property, CASTCLASS_FUInt32Property);
        DECLARE_VIRTUAL_TYPE(FUInt32Property);
    };

    class RC_UE_API FUInt64Property : public TProperty_Numeric<uint64>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FUInt64Property, CASTCLASS_FUInt64Property);
        DECLARE_VIRTUAL_TYPE(FUInt64Property);
    };

    class RC_UE_API FFloatProperty : public TProperty_Numeric<float>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FFloatProperty, CASTCLASS_FFloatProperty);
        DECLARE_VIRTUAL_TYPE(FFloatProperty);
    };

    class RC_UE_API FDoubleProperty : public TProperty_Numeric<double>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FDoubleProperty, CASTCLASS_FDoubleProperty);
        DECLARE_VIRTUAL_TYPE(FDoubleProperty);
    };

    // ===================================================================
    // BOOL PROPERTY
    // ===================================================================

    class RC_UE_API FBoolProperty : public FProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FBoolProperty, CASTCLASS_FBoolProperty);
        DECLARE_VIRTUAL_TYPE(FBoolProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FBoolProperty.hpp>

    public:
        //Emulate the CPP type API, see TPropertyTypeFundamentals
        //this is incomplete as some operations make no sense for bitfields, for example they don't have a usable address
        typedef bool TCppType;

        /** Returns the value of the boolean property */
        FORCEINLINE auto GetPropertyValue(const void* A) -> bool
        {
            uint8_t* ByteValue = (uint8_t*)A + GetByteOffset();
            return !!(*ByteValue & GetFieldMask());
        }

        /** Returns the value of the boolean property inside of it's container */
        FORCEINLINE auto GetPropertyValueInContainer(const void* A, int32_t ArrayIndex = 0) -> bool
        {
            return GetPropertyValue(ContainerPtrToValuePtr<void>(A, ArrayIndex));
        }

        /** Returns the default value of the boolean property */
        FORCEINLINE static auto GetDefaultPropertyValue() -> bool
        {
            return false;
        }

        /** Returns the property value from the given address, or default value if it represents the nullptr */
        FORCEINLINE auto GetOptionalPropertyValue(const void* B) -> bool
        {
            return B ? GetPropertyValue(B) : GetDefaultPropertyValue();
        }

        /** Returns the property value from the given container address, or default value if it represents the nullptr */
        FORCEINLINE auto GetOptionalPropertyValueInContainer(const void* B, int32_t ArrayIndex = 0) -> bool
        {
            return B ? GetPropertyValueInContainer(B, ArrayIndex) : GetDefaultPropertyValue();
        }

        /** Updates property value to the provided one */
        FORCEINLINE auto SetPropertyValue(void* A, bool Value) -> void
        {
            uint8_t* byte_value = (uint8_t*)A + GetByteOffset();
            *byte_value = ((*byte_value) & ~GetFieldMask()) | (Value ? GetByteMask() : 0);
        }

        /** Updates property value inside of the container */
        FORCEINLINE auto SetPropertyValueInContainer(void* A, bool Value, int32_t ArrayIndex = 0)
        {
            SetPropertyValue(ContainerPtrToValuePtr<void>(A, ArrayIndex), Value);
        }

        /** If the return value is true this FBoolProperty represents C++ bool type */
        FORCEINLINE auto IsNativeBool() -> bool
        {
            return GetFieldMask() == 0xff;
        }
    };

    // ===================================================================
    // OBJECT PROPERTIES
    // ===================================================================

    class RC_UE_API FObjectPropertyBase : public FProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FObjectPropertyBase, CASTCLASS_FObjectPropertyBase);
        DECLARE_VIRTUAL_TYPE(FObjectPropertyBase);

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_FObjectPropertyBase.hpp>

    public:
        void SetPropertyClass(UClass* NewPropertyClass);

        // Virtual Functions
    public:
        FString GetCPPTypeCustom(FString* ExtendedTypeText, uint32 CPPExportFlags, const FString& InnerNativeTypeName) const;
        UObject* LoadObjectPropertyValue(const void* PropertyValueAddress) const;
        UObject* GetObjectPropertyValue(const void* PropertyValueAddress) const;
        void SetObjectPropertyValue(void* PropertyValueAddress, UObject* Value) const;
        bool AllowCrossLevel() const;
        void CheckValidObject(void* Value) const;
    };

    template<typename InTCppType>
    class TFObjectPropertyBase : public TProperty<InTCppType, FObjectPropertyBase>
    {
    };

    class RC_UE_API FObjectProperty : public TFObjectPropertyBase<UObject*>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FObjectProperty, CASTCLASS_FObjectProperty);
        DECLARE_VIRTUAL_TYPE(FObjectProperty);
    };

    class RC_UE_API FObjectPtrProperty : public FObjectProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FObjectPtrProperty, CASTCLASS_FObjectPtrProperty)
    };

    class RC_UE_API FAssetObjectProperty : public FObjectProperty
    {
        DECLARE_FIELD_CLASS(FAssetObjectProperty)
    };

    class RC_UE_API FAssetClassProperty : public FAssetObjectProperty
    {
        DECLARE_FIELD_CLASS(FAssetClassProperty)
    };

    class RC_UE_API FWeakObjectProperty : public TFObjectPropertyBase<FWeakObjectPtr>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FWeakObjectProperty, CASTCLASS_FWeakObjectProperty);
        DECLARE_VIRTUAL_TYPE(FWeakObjectProperty);
    };

    struct FLazyObjectPtr : public TPersistentObjectPtr<FUniqueObjectGuid>
    {
    };

    class RC_UE_API FLazyObjectProperty : public TFObjectPropertyBase<FLazyObjectPtr>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FLazyObjectProperty, CASTCLASS_FLazyObjectProperty);
        DECLARE_VIRTUAL_TYPE(FLazyObjectProperty);

    public:
    };

    class RC_UE_API FSoftObjectProperty : public TFObjectPropertyBase<FSoftObjectPtr>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FSoftObjectProperty, CASTCLASS_FSoftObjectProperty);
        DECLARE_VIRTUAL_TYPE(FSoftObjectProperty);
    };

    class RC_UE_API FClassProperty : public FObjectProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FClassProperty, CASTCLASS_FClassProperty);
        DECLARE_VIRTUAL_TYPE(FClassProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FClassProperty.hpp>

    public:
        void SetMetaClass(UClass* NewMetaClass);
    };

    class RC_UE_API FClassPtrProperty : public FClassProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FClassPtrProperty, CASTCLASS_FClassPtrProperty)
    };

    class RC_UE_API FSoftClassProperty : public FSoftObjectProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FSoftClassProperty, CASTCLASS_FSoftClassProperty);
        DECLARE_VIRTUAL_TYPE(FSoftClassProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FSoftClassProperty.hpp>

    public:
        void SetMetaClass(UClass* NewMetaClass);
    };

    // ===================================================================
    // INTERFACE PROPERTY
    // ===================================================================

    class FScriptInterface
    {
    public:
        UObject* ObjectPointer{};
        void* InterfacePointer{};
    };

    class RC_UE_API FInterfaceProperty : public TProperty<FScriptInterface, FProperty>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FInterfaceProperty, CASTCLASS_FInterfaceProperty);
        DECLARE_VIRTUAL_TYPE(FInterfaceProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FInterfaceProperty.hpp>

    public:
        void SetInterfaceClass(UClass* NewInterfaceClass);
    };

    // ===================================================================
    // NAME PROPERTY
    // ===================================================================

    class RC_UE_API FNameProperty : public TProperty_WithEqualityAndSerializer<FName, FProperty>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FNameProperty, CASTCLASS_FNameProperty);
        DECLARE_VIRTUAL_TYPE(FNameProperty);
    };

    // ===================================================================
    // CONTAINER PROPERTIES - Array
    // ===================================================================

    //
    // Describes a dynamic array.
    //

    using FFreezableScriptArray = TScriptArray<TMemoryImageAllocator<DEFAULT_ALIGNMENT>>;

#if !PLATFORM_ANDROID || !PLATFORM_32BITS
    static_assert(sizeof(FScriptArray) == sizeof(FFreezableScriptArray) && alignof(FScriptArray) == alignof(FFreezableScriptArray), "FScriptArray and FFreezableScriptArray are expected to be layout-compatible");
#endif
    
    class FScriptArrayHelper;
    class RC_UE_API FArrayProperty : public FProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FArrayProperty, CASTCLASS_FArrayProperty);
        DECLARE_VIRTUAL_TYPE(FArrayProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FArrayProperty.hpp>
    };

    


    // ===================================================================
    // CONTAINER PROPERTIES - Map
    // ===================================================================

    typedef TProperty<FScriptMap, FProperty> FMapProperty_Super;

    class RC_UE_API FMapProperty : public FMapProperty_Super
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FMapProperty, CASTCLASS_FMapProperty);
        DECLARE_VIRTUAL_TYPE(FMapProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FMapProperty.hpp>
    };

    // ===================================================================
    // CONTAINER PROPERTIES - Set
    // ===================================================================

    class RC_UE_API FSetProperty : public TProperty<FScriptSet, FProperty>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FSetProperty, CASTCLASS_FSetProperty);
        DECLARE_VIRTUAL_TYPE(FSetProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FSetProperty.hpp>

    public:
        FScriptSetLayout& GetSetLayout()
        {
            return GetSetLayoutBase();
        }

        const FScriptSetLayout& GetSetLayout() const
        {
            return GetSetLayoutBase();
        }
    };

    /**
     * FScriptArrayHelper: Pseudo dynamic array. Used to work with array properties in a sensible way.
     **/
    class FScriptArrayHelper
    {
        enum EInternal { Internal };

        template <typename CallableType>
        auto WithScriptArray(CallableType&& Callable) const
        {
            if (!!(ArrayFlags & EArrayPropertyFlags::UsesMemoryImageAllocator))
            {
                return Callable(FreezableArray);
            }
            else
            {
                return Callable(HeapArray);
            }
        }

    public:
        /**
         *    Constructor, brings together a property and an instance of the property located in memory
         *    @param    InProperty: the property associated with this memory
         *    @param    InArray: pointer to raw memory that corresponds to this array. This can be NULL, and sometimes is, but in that case almost all operations will crash.
        **/
        UE_FORCEINLINE_HINT FScriptArrayHelper(const FArrayProperty* InProperty, const void* InArray)
            : FScriptArrayHelper(Internal, InProperty->GetInner(), InArray, InProperty->GetInner()->GetElementSize(), InProperty->GetInner()->GetMinAlignment(), InProperty->GetArrayFlags())
        {
        }

        /**
         *    Index range check
         *    @param    Index: Index to check
         *    @return true if accessing this element is legal.
        **/
        UE_FORCEINLINE_HINT bool IsValidIndex( int32 Index ) const
        {
            return Index >= 0 && Index < Num();
        }
        /**
         *    Return the number of elements in the array.
         *    @return    The number of elements in the array.
        **/
        inline int32 Num() const
        {
            int32 Result = WithScriptArray([](auto* Array) { return Array->Num(); });
            checkSlow(Result >= 0);
            return Result;
        }
        /**
         *    Return the number of elements in the array without validating the state of the array.
         *    Needed to allow reading of the num when the array is 'invalid' during its intrusive unset state.
         *    @return    The number of elements in the array.
        **/
        inline int32 NumUnchecked() const
        {
            int32 Result = WithScriptArray([](auto* Array) { return Array->NumUnchecked(); });
            return Result;
        }
        /**
         *    Returns a uint8 pointer to an element in the array
         *    @param    Index: index of the item to return a pointer to.
         *    @return    Pointer to this element, or NULL if the array is empty
        **/
        inline uint8* GetRawPtr(int32 Index = 0)
        {
            if (!Num())
            {
                checkSlow(!Index);
                return NULL;
            }
            checkSlow(IsValidIndex(Index)); 
            return (uint8*)WithScriptArray([](auto* Array) { return Array->GetData(); }) + Index * static_cast<size_t>(ElementSize);
        }
        /**
         *    Returns a uint8 pointer to an element in the array. This call is identical to GetRawPtr and is
         *  here to provide interface parity with FScriptSetHelper*.
         *    @param    Index: index of the item to return a pointer to.
         *    @return    Pointer to this element, or NULL if the array is empty
        **/
        UE_FORCEINLINE_HINT uint8* GetElementPtr(int32 Index = 0)
        {
            return GetRawPtr(Index);
        }
        /**
        *    Empty the array, then add blank, constructed values to a given size.
        *    @param    Count: the number of items the array will have on completion.
        **/
        void EmptyAndAddValues(int32 Count)
        { 
            check(Count>=0);
            checkSlow(Num() >= 0); 
            EmptyValues(Count);
            AddValues(Count);
        }
        /**
        *    Empty the array, then add uninitialized values to a given size.
        *    @param    Count: the number of items the array will have on completion.
        **/
        void EmptyAndAddUninitializedValues(int32 Count)
        { 
            check(Count>=0);
            checkSlow(Num() >= 0); 
            EmptyValues(Count);
            AddUninitializedValues(Count);
        }
        /**
        *    Expand the array, if needed, so that the given index is valid
        *    @param    Index: index for the item that we want to ensure is valid
        *    @return true if expansion was necessary
        *    NOTE: This is not a count, it is an INDEX, so the final count will be at least Index+1 this matches the usage.
        **/
        bool ExpandForIndex(int32 Index)
        { 
            check(Index>=0);
            checkSlow(Num() >= 0); 
            if (Index >= Num())
            {
                AddValues(Index - Num() + 1);
                return true;
            }
            return false;
        }
        /**
        *    Add or remove elements to set the array to a given size.
        *    @param    Count: the number of items the array will have on completion.
        **/
        void Resize(int32 Count)
        {
            if (Count < 0)
            {
                UE::Core::Private::OnInvalidArrayNum(Count);
            }

            int32 OldNum = Num();
            if (Count > OldNum)
            {
                AddValues(Count - OldNum);
            }
            else if (Count < OldNum)
            {
                RemoveValues(Count, OldNum - Count);
            }
        }
        /**
        *    Add blank, constructed values to the end of the array.
        *    @param    Count: the number of items to insert.
        *    @return    the index of the first newly added item.
        **/
        int32 AddValues(int32 Count)
        { 
            const int32 OldNum = AddUninitializedValues(Count);        
            ConstructItems(OldNum, Count);
            return OldNum;
        }
        /**
        *    Add a blank, constructed values to the end of the array.
        *    @return    the index of the newly added item.
        **/
        UE_FORCEINLINE_HINT int32 AddValue()
        { 
            return AddValues(1);
        }
        /**
        *    Add uninitialized values to the end of the array.
        *    @param    Count: the number of items to insert.
        *    @return    the index of the first newly added item.
        **/
        int32 AddUninitializedValues(int32 Count)
        {
            check(Count>=0);
            checkSlow(Num() >= 0);
            const int32 OldNum = WithScriptArray([this, Count](auto* Array) { return Array->Add(Count, ElementSize, ElementAlignment); });
            return OldNum;
        }
        /**
        *    Add an uninitialized value to the end of the array.
        *    @return    the index of the newly added item.
        **/
        UE_FORCEINLINE_HINT int32 AddUninitializedValue()
        {
            return AddUninitializedValues(1);
        }
        /**
         *    Insert blank, constructed values into the array.
         *    @param    Index: index of the first inserted item after completion
         *    @param    Count: the number of items to insert.
        **/
        void InsertValues( int32 Index, int32 Count = 1)
        {
            check(Count>=0);
            check(Index>=0 && Index <= Num());
            WithScriptArray([this, Index, Count](auto* Array) { Array->Insert(Index, Count, ElementSize, ElementAlignment); });
            ConstructItems(Index, Count);
        }
        /**
         *    Remove all values from the array, calling destructors, etc as appropriate.
         *    @param Slack: used to presize the array for a subsequent add, to avoid reallocation.
        **/
        void EmptyValues(int32 Slack = 0)
        {
            checkSlow(Slack>=0);
            const int32 OldNum = NumUnchecked();
            if (OldNum)
            {
                DestructItems(0, OldNum);
            }
            if (OldNum || Slack)
            {
                WithScriptArray([this, Slack](auto* Array) { Array->Empty(Slack, ElementSize, ElementAlignment); });
            }
        }
        /**
         *    Remove values from the array, calling destructors, etc as appropriate.
         *    @param Index: first item to remove.
         *    @param Count: number of items to remove.
        **/
        void RemoveValues(int32 Index, int32 Count = 1)
        {
            check(Count>=0);
            check(Index>=0 && Index + Count <= Num());
            DestructItems(Index, Count);
            WithScriptArray([this, Index, Count](auto* Array) { Array->Remove(Index, Count, ElementSize, ElementAlignment); });
        }

        /**
        *    Clear values in the array. The meaning of clear is defined by the property system.
        *    @param Index: first item to clear.
        *    @param Count: number of items to clear.
        **/
        void ClearValues(int32 Index, int32 Count = 1)
        {
            check(Count>=0);
            check(Index>=0);
            ClearItems(Index, Count);
        }

        /**
         *    Swap two elements in the array, does not call constructors and destructors
         *    @param A index of one item to swap.
         *    @param B index of the other item to swap.
        **/
        void SwapValues(int32 A, int32 B)
        {
            WithScriptArray([this, A, B](auto* Array) { Array->SwapMemory(A, B, ElementSize); });
        }

        /**
         *    Move the allocation from another array and make it our own.
         *    @note The arrays MUST be of the same type, and this function will NOT validate that!
         *    @param InOtherArray The array to move the allocation from.
        **/
        void MoveAssign(void* InOtherArray)
        {
            checkSlow(InOtherArray);
            // FScriptArray::MoveAssign does not call destructors for our elements, so do that before calling it.
            DestructItems(0, Num());
            WithScriptArray([this, InOtherArray](auto* Array) { Array->MoveAssign(*static_cast<decltype(Array)>(InOtherArray), ElementSize, ElementAlignment); });
        }

        /**
         *    Used by memory counting archives to accumulate the size of this array.
         *    @param Ar archive to accumulate sizes
        **/
        void CountBytes( FArchive& Ar  ) const
        {
            WithScriptArray([this, &Ar](auto* Array) { Array->CountBytes(Ar, ElementSize); });
        }

        /**
         * Destroys the container object - THERE SHOULD BE NO MORE USE OF THIS HELPER AFTER THIS FUNCTION IS CALLED!
         */
        void DestroyContainer_Unsafe()
        {
            WithScriptArray([](auto* Array) { DestructItem(Array); });
        }

        static FScriptArrayHelper CreateHelperFormInnerProperty(const FProperty* InInnerProperty, const void *InArray, EArrayPropertyFlags InArrayFlags = EArrayPropertyFlags::None)
        {
            return FScriptArrayHelper(Internal, InInnerProperty, InArray, InInnerProperty->GetElementSize(), InInnerProperty->GetMinAlignment(), InArrayFlags);
        }

    private:
        FScriptArrayHelper(EInternal, const FProperty* InInnerProperty, const void* InArray, int32 InElementSize, uint32 InElementAlignment, EArrayPropertyFlags InArrayFlags)
            : InnerProperty(InInnerProperty)
            , ElementSize(InElementSize)
            , ElementAlignment(InElementAlignment)
            , ArrayFlags(InArrayFlags)
        {
            //@todo, we are casting away the const here
            if (!!(InArrayFlags & EArrayPropertyFlags::UsesMemoryImageAllocator))
            {
                FreezableArray = (FFreezableScriptArray*)InArray;
            }
            else
            {
                HeapArray = (FScriptArray*)InArray;
            }

            check(ElementSize > 0);
            check(InnerProperty);
        }

        /**
         *    Internal function to call into the property system to construct / initialize elements.
         *    @param Index: first item to .
         *    @param Count: number of items to .
        **/
        void ConstructItems(int32 Index, int32 Count)
        {
            checkSlow(Count >= 0);
            checkSlow(Index >= 0); 
            checkSlow(Index <= Num());
            checkSlow(Index + Count <= Num());
            if (Count > 0)
            {
                uint8* Dest = GetRawPtr(Index);
                if (InnerProperty->GetPropertyFlags() & CPF_ZeroConstructor)
                {
                    FMemory::Memzero(Dest, Count * static_cast<size_t>(ElementSize));
                }
                else
                {
                    for (int32 LoopIndex = 0; LoopIndex < Count; LoopIndex++, Dest += ElementSize)
                    {
                        InnerProperty->InitializeValue(Dest);
                    }
                }
            }
        }
        /**
         *    Internal function to call into the property system to destruct elements.
         *    @param Index: first item to .
         *    @param Count: number of items to .
        **/
        void DestructItems(int32 Index, int32 Count)
        {
            if (!(InnerProperty->GetPropertyFlags() & (CPF_IsPlainOldData | CPF_NoDestructor)))
            {
                checkSlow(Count >= 0);
                checkSlow(Index >= 0); 
                checkSlow(Index + Count <= Num());
                if (Count > 0)
                {
                    uint8* Dest = GetRawPtr(Index);
                    for (int32 LoopIndex = 0; LoopIndex < Count; LoopIndex++, Dest += ElementSize)
                    {
                        InnerProperty->DestroyValue(Dest);
                    }
                }
            }
        }
        /**
         *    Internal function to call into the property system to clear elements.
         *    @param Index: first item to .
         *    @param Count: number of items to .
        **/
        void ClearItems(int32 Index, int32 Count)
        {
            checkSlow(Count >= 0);
            checkSlow(Index >= 0); 
            checkSlow(Index < Num());
            checkSlow(Index + Count <= Num());
            if (Count > 0)
            {
                uint8* Dest = GetRawPtr(Index);
                if ((InnerProperty->GetPropertyFlags() & (CPF_ZeroConstructor | CPF_NoDestructor)) == (CPF_ZeroConstructor | CPF_NoDestructor))
                {
                    FMemory::Memzero(Dest, Count * static_cast<size_t>(ElementSize));
                }
                else
                {
                    for (int32 LoopIndex = 0; LoopIndex < Count; LoopIndex++, Dest += ElementSize)
                    {
                        InnerProperty->ClearValue(Dest);
                    }
                }
            }
        }

        const FProperty* InnerProperty;
        union
        {
            FScriptArray* HeapArray;
            FFreezableScriptArray* FreezableArray;
        };
        int32 ElementSize;
        uint32 ElementAlignment;
        EArrayPropertyFlags ArrayFlags;
    };

    class FScriptArrayHelper_InContainer : public FScriptArrayHelper
    {
    public:
        UE_FORCEINLINE_HINT FScriptArrayHelper_InContainer(const FArrayProperty* InProperty, const void* InContainer, int32 FixedArrayIndex=0)
            :FScriptArrayHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InContainer, FixedArrayIndex))
        {
        }

        UE_FORCEINLINE_HINT FScriptArrayHelper_InContainer(const FArrayProperty* InProperty, const UObject* InContainer, int32 FixedArrayIndex=0)
            :FScriptArrayHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InContainer, FixedArrayIndex))
        {
        }
    };

    /**
     * Templated iterator to go through script helper containers that may contain invalid entries
     * that are not part of the valid number of elements (i.e. GetMaxIndex() != Num() ).
     * The iterator
     *  - will advance to the first valid entry on creation and when incremented
     *  - can be dereferenced to an internal index to be used with methods like Get<Item>Ptr or Get<Item>PtrWithoutCheck
     *  - can also be used directly with methods like Get<Item>PtrChecked
     *  - can return the associated logical index (number of valid visited entries) by calling GetLogicalIndex()
     */
    template<typename ContainerType>
    struct TScriptContainerIterator
    {
        explicit TScriptContainerIterator(const ContainerType& InContainer) : Container(InContainer)
        {
            Advance();
        }

        explicit TScriptContainerIterator(const ContainerType& InContainer, const int32 InLogicalIndex) : Container(InContainer)
        {
            const int32 MaxIndex = Container.GetMaxIndex();
            if (MaxIndex == Container.Num())
            {
                InternalIndex = InLogicalIndex;
                LogicalIndex = InLogicalIndex;
                return;
            }

            do
            {
                Advance();
            }
            while (LogicalIndex < InLogicalIndex && InternalIndex < MaxIndex);
        }

        TScriptContainerIterator& operator++()
        {
            Advance();
            return *this;
        }

        TScriptContainerIterator operator++(int)
        {
            const TScriptContainerIterator Temp(*this);
            Advance();
            return Temp;
        }

        explicit operator bool() const
        {
            return Container.IsValidIndex(InternalIndex);
        }

        int32 GetInternalIndex() const
        {
            return InternalIndex;
        }

        int32 GetLogicalIndex() const
        {
            return LogicalIndex;
        }

        UE_DEPRECATED(5.4, "Use Iterator directly, GetInternalIndex or GetLogicalIndex instead.")
        int32 operator*() const
        {
            return InternalIndex;
        }

    private:
        const ContainerType& Container;
        int32 InternalIndex = INDEX_NONE;
        int32 LogicalIndex = INDEX_NONE;

        void Advance()
        {
            ++InternalIndex;
            const int32 MaxIndex = Container.GetMaxIndex();
            while (InternalIndex < MaxIndex && !Container.IsValidIndex(InternalIndex))
            {
                ++InternalIndex;
            }

            ++LogicalIndex;
        }
    };

    /**
     * FScriptSetHelper: Pseudo dynamic Set. Used to work with Set properties in a sensible way.
     * Note that the set can contain invalid entries some number of valid entries (i.e. Num() ) can
     * be smaller that the actual number of elements (i.e. GetMaxIndex() ).
     *
     * Internal index naming is used to identify the actual index in the container which can point to
     * an invalid entry. It can be used for methods like Get<Item>Ptr, Get<Item>PtrWithoutCheck or IsValidIndex.
     *
     * Logical index naming is used to identify only valid entries in the container so it can be smaller than the
     * internal index in case we skipped invalid entries to reach the next valid one. This index is used on method
     * like FindNth<Item>Ptr or FindInternalIndex.
     * This is also the type of index we receive from most editor events (e.g. property change events) so it is
     * strongly suggested to rely on FScriptSetHelper::FIterator to iterate or convert to internal index.
     */
    class FScriptSetHelper
    {
        friend class FSetProperty;

    public:

        using FIterator = TScriptContainerIterator<FScriptSetHelper>;

        FIterator CreateIterator() const
        {
            return FIterator(*this);
        }

        FIterator CreateIterator(const int32 InLogicalIndex) const
        {
            return FIterator(*this, InLogicalIndex);
        }

        /**
        * Constructor, brings together a property and an instance of the property located in memory
        *
        * @param  InProperty  The property associated with this memory
        * @param  InSet       Pointer to raw memory that corresponds to this Set. This can be NULL, and sometimes is, but in that case almost all operations will crash.
        */
        FORCEINLINE FScriptSetHelper(const FSetProperty* InProperty, const void* InSet)
            : ElementProp(const_cast<FProperty*>(InProperty->GetElementProp()))
            , Set((FScriptSet*)InSet)  //@todo, we are casting away the const here
            , SetLayout(InProperty->GetSetLayout())
        {
            check(ElementProp);
        }

        /**
        * Index range check
        *
        * @param InternalIndex Index to check
        *
        * @return true if accessing this element is legal.
        */
        FORCEINLINE bool IsValidIndex(int32 InternalIndex) const
        {
            return Set->IsValidIndex(InternalIndex);
        }

        /**
        * Returns the number of elements in the set.
        *
        * @return The number of elements in the set.
        */
        FORCEINLINE int32 Num() const
        {
            const int32 Result = Set->Num();
            checkSlow(Result >= 0); 
            return Result;
        }

        /**
        * Returns the number of elements in the set.
        *    Needed to allow reading of the num when the set is 'invalid' during its intrusive unset state.
        * @return The number of elements in the set.
        */
        FORCEINLINE int32 NumUnchecked() const
        {
            const int32 Result = Set->NumUnchecked();
            return Result;
        }

        /**
        * Returns the (non-inclusive) maximum index of elements in the set.
        *
        * @return The (non-inclusive) maximum index of elements in the set.
        */
        FORCEINLINE int32 GetMaxIndex() const
        {
            const int32 Result = Set->GetMaxIndex();
            checkSlow(Result >= Num());
            return Result;
        }

        /**
        * Static version of Num() used when you don't need to bother to construct a FScriptSetHelper. Returns the number of elements in the set.
        *
        * @param  Target  Pointer to the raw memory associated with a FScriptSet
        *
        * @return The number of elements in the set.
        */
        static FORCEINLINE int32 Num(const void* Target)
        {
            const int32 Result = ((const FScriptSet*)Target)->Num();
            checkSlow(Result >= 0); 
            return Result;
        }

        /**
        * Returns a uint8 pointer to the element in the set.
        *
        * @param InternalIndex index of the item to return a pointer to.
        *
        * @return Pointer to the element, or nullptr if the set is empty.
        */
        FORCEINLINE uint8* GetElementPtr(int32 InternalIndex)
        {
            if (Num() == 0)
            {
                checkf(InternalIndex == 0, TEXT("Legacy implementation was only allowing requesting InternalIndex 0 on an empty container."));
                return nullptr;
            }

            checkf(IsValidIndex(InternalIndex), TEXT("Invalid internal index. Use IsValidIndex before calling this method."));
            return (uint8*)Set->GetData(InternalIndex, SetLayout);
        }

        /**
        * Returns a uint8 pointer to the element in the set.
        *
        * @param InternalIndex index of the item to return a pointer to.
        *
        * @return Pointer to the element, or nullptr if the set is empty.
        */
        FORCEINLINE const uint8* GetElementPtr(int32 InternalIndex) const
        {
            return const_cast<FScriptSetHelper*>(this)->GetElementPtr(InternalIndex);
        }

        /**
         * Returns a uint8 pointer to the element in the set.
         *
         * @param Iterator A valid iterator of the item to return a pointer to.
         *
         * @return Pointer to the element, or will fail a check if an invalid iterator is provided.
         */
        FORCEINLINE uint8* GetElementPtr(const FIterator Iterator)
        {
            checkf(Iterator, TEXT("Invalid Iterator. Test Iterator before calling this method."));
            return (uint8*)Set->GetData(Iterator.GetInternalIndex(), SetLayout);
        }

        /**
         * Returns a uint8 pointer to the element in the set.
         *
         * @param Iterator A valid iterator of the item to return a pointer to.
         *
         * @return Pointer to the element, or will fail a check if an invalid iterator is provided.
         */
        FORCEINLINE const uint8* GetElementPtr(const FIterator Iterator) const
        {
            return const_cast<FScriptSetHelper*>(this)->GetElementPtr(Iterator);
        }

        /**
        * Returns a uint8 pointer to the the Nth valid element in the set (skipping invalid entries).
        * NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead.
        *
        * @return Pointer to the element, or nullptr if the index is invalid.
        */
        uint8* FindNthElementPtr(int32 N)
        {
            const int32 InternalIndex = FindInternalIndex(N);
            return (InternalIndex != INDEX_NONE) ? GetElementPtrWithoutCheck(InternalIndex) : nullptr;
        }

        /**
        * Returns a uint8 pointer to the the Nth valid element in the set (skipping invalid entries).
        * NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead.
        *
        * @return Pointer to the element, or nullptr if the index is invalid.
        */
        const uint8* FindNthElementPtr(int32 N) const
        {
            const int32 InternalIndex = FindInternalIndex(N);
            return (InternalIndex != INDEX_NONE) ? GetElementPtrWithoutCheck(InternalIndex) : nullptr;
        }

        /**
        * Move the allocation from another set and make it our own.
        * @note The sets MUST be of the same type, and this function will NOT validate that!
        *
        * @param InOtherSet The set to move the allocation from.
        */
        void MoveAssign(void* InOtherSet)
        {
            FScriptSet* OtherSet = (FScriptSet*)InOtherSet;
            checkSlow(OtherSet);
            Set->MoveAssign(*OtherSet, SetLayout);
        }

        /**
        * Add an uninitialized value to the end of the set.
        *
        * @return  The index of the added element.
        */
        FORCEINLINE int32 AddUninitializedValue()
        {
            checkSlow(Num() >= 0);

            return Set->AddUninitialized(SetLayout);
        }

        /**
        *    Remove all values from the set, calling destructors, etc as appropriate.
        *    @param Slack: used to presize the set for a subsequent add, to avoid reallocation.
        **/
        void EmptyElements(int32 Slack = 0)
        {
            checkSlow(Slack >= 0);

            int32 OldNum = NumUnchecked();
            if (OldNum)
            {
                DestructItems(0, OldNum);
            }
            if (OldNum || Slack)
            {
                Set->Empty(Slack, SetLayout);
            }
        }

        /**
        * Adds a blank, constructed value to a given size.
        * Note that this will create an invalid Set because all the keys will be default constructed, and the set needs rehashing.
        *
        * @return  The index of the first element added.
        **/
        int32 AddDefaultValue_Invalid_NeedsRehash()
        {
            checkSlow(Num() >= 0);

            int32 Result = AddUninitializedValue();
            ConstructItem(Result);

            return Result;
        }

        /**
        * Returns the property representing the element of the set
        */
        FProperty* GetElementProperty() const
        {
            return ElementProp;
        }

        /**
        * Removes an element at the specified index, destroying it.
        *
        * @param InternalIndex The index of the element to remove.
        */
        void RemoveAt(int32 InternalIndex, int32 Count = 1)
        {
            check(IsValidIndex(InternalIndex));

            DestructItems(InternalIndex, Count);
            for (; Count; ++InternalIndex)
            {
                if (IsValidIndex(InternalIndex))
                {
                    Set->RemoveAt(InternalIndex, SetLayout);
                    --Count;
                }
            }
        }

        /**
        * Rehashes the keys in the set.
        * This function must be called to create a valid set.
        */
        COREUOBJECT_API void Rehash();

        /**
         * Sets have gaps in their indices, so this function translates a logical index (ie. Nth element)
         * to an internal index that can be used for the other functions in this class.
         * NOTE: This is slow, do not use this for iteration! Use CreateIterator() instead.
         */
        int32 FindInternalIndex(int32 LogicalIdx) const
        {
            if (LogicalIdx < 0 || LogicalIdx >= Num())
            {
                return INDEX_NONE;
            }

            // if set is compact, use random access
            if (Num() == GetMaxIndex())
            {
                return IsValidIndex(LogicalIdx) ? LogicalIdx : INDEX_NONE;
            }

            int32 MaxIndex = GetMaxIndex();
            for (int32 Actual = 0; Actual < MaxIndex; ++Actual)
            {
                if (IsValidIndex(Actual))
                {
                    if (LogicalIdx == 0)
                    {
                        return Actual;
                    }
                    --LogicalIdx;
                }
            }
            return INDEX_NONE;
        }

        /**
         * Sets have gaps in their indices, so this function translates a internal index
         * to an logical index (ie. Nth element).
         * NOTE: This is slow, do not use this for iteration!
         */
        int32 FindLogicalIndex(int32 InternalIdx) const
        {
            if (!IsValidIndex(InternalIdx))
            {
                return INDEX_NONE;
            }

            // if set is compact, use random access
            if (GetMaxIndex() == Num())
            {
                return  InternalIdx;
            }

            int32 LogicalIndex = InternalIdx;
            for (int i = 0; i < InternalIdx; ++i)
            {
                if (!IsValidIndex(i))
                {
                    LogicalIndex--;
                }
            }

            return LogicalIndex;
        }

        /**
        * Finds the index of an element in a set
        *
        * @param  ElementToFind        The address of an element to search for.
        * @param  IndexHint         The index to start searching from.
        *
        * @return The index of an element found in SetHelper, or -1 if none was found.
        */
        int32 FindElementIndex(const void* ElementToFind, int32 IndexHint = 0) const
        {
            const int32 SetMax = GetMaxIndex();
            if (SetMax == 0)
            {
                return INDEX_NONE;
            }

            if (IndexHint >= SetMax)
            {
                IndexHint = 0;
            }

            check(IndexHint >= 0);

            FProperty* LocalKeyProp = this->ElementProp; // prevent aliasing in loop below

            int32 InternalIndex = IndexHint;
            for (;;)
            {
                if (IsValidIndex(InternalIndex))
                {
                    const void* ElementToCheck = GetElementPtrWithoutCheck(InternalIndex);
                    if (LocalKeyProp->Identical(ElementToFind, ElementToCheck))
                    {
                        return InternalIndex;
                    }
                }

                ++InternalIndex;
                if (InternalIndex == SetMax)
                {
                    InternalIndex = 0;
                }

                if (InternalIndex == IndexHint)
                {
                    return INDEX_NONE;
                }
            }
        }

        /**
        * Finds the pair in a map which matches the key in another pair.
        *
        * @param  PairWithKeyToFind  The address of a map pair which contains the key to search for.
        * @param  IndexHint          The index to start searching from.
        *
        * @return A pointer to the found pair, or nullptr if none was found.
        */
        FORCEINLINE uint8* FindElementPtr(const void* ElementToFind, int32 IndexHint = 0)
        {
            const int32 InternalIndex = FindElementIndex(ElementToFind, IndexHint);
            uint8* Result = (InternalIndex >= 0 ? GetElementPtrWithoutCheck(InternalIndex) : nullptr);
            return Result;
        }

        /** Finds element index from hash, rather than linearly searching */
        FORCEINLINE int32 FindElementIndexFromHash(const void* ElementToFind) const
        {
            FProperty* LocalElementPropForCapture = ElementProp;
            return Set->FindIndex(
                ElementToFind,
                SetLayout,
                [LocalElementPropForCapture](const void* Element) { return LocalElementPropForCapture->GetValueTypeHash(Element); },
                [LocalElementPropForCapture](const void* A, const void* B) { return LocalElementPropForCapture->Identical(A, B); }
            );
        }

        /** Finds element pointer from hash, rather than linearly searching */
        FORCEINLINE uint8* FindElementPtrFromHash(const void* ElementToFind)
        {
            const int32 InternalIndex = FindElementIndexFromHash(ElementToFind);
            uint8* Result = (InternalIndex >= 0 ? GetElementPtrWithoutCheck(InternalIndex) : nullptr);
            return Result;
        }

        /** Adds the element to the set, returning true if the element was added, or false if the element was already present */
        void AddElement(const void* ElementToAdd)
        {
            FProperty* LocalElementPropForCapture = ElementProp;
            FScriptSetLayout& LocalSetLayoutForCapture = SetLayout;
            Set->Add(
                ElementToAdd,
                SetLayout,
                [LocalElementPropForCapture](const void* Element) { return LocalElementPropForCapture->GetValueTypeHash(Element); },
                [LocalElementPropForCapture](const void* A, const void* B) { return LocalElementPropForCapture->Identical(A, B); },
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-lambda-capture"
#endif
                [LocalElementPropForCapture, ElementToAdd, LocalSetLayoutForCapture](void* NewElement)
                {
                    if (LocalElementPropForCapture->GetPropertyFlags() & CPF_ZeroConstructor)
                    {
                        FMemory::Memzero(NewElement, LocalElementPropForCapture->GetSize());
                    }
                    else
                    {
                        LocalElementPropForCapture->InitializeValue(NewElement);
                    }

                    LocalElementPropForCapture->CopySingleValueToScriptVM(NewElement, ElementToAdd);
                },
#ifdef __clang__
#pragma clang diagnostic pop
#endif
                [LocalElementPropForCapture](void* Element)
                {
                    if (!(LocalElementPropForCapture->GetPropertyFlags() & (CPF_IsPlainOldData | CPF_NoDestructor)))
                    {
                        LocalElementPropForCapture->DestroyValue(Element);
                    }
                }
            );
        }

        /** Removes the element from the set */
        bool RemoveElement(const void* ElementToRemove)
        {
            FProperty* LocalElementPropForCapture = ElementProp;
            int32 FoundIndex = Set->FindIndex(
                ElementToRemove,
                SetLayout,
                [LocalElementPropForCapture](const void* Element) { return LocalElementPropForCapture->GetValueTypeHash(Element); },
                [LocalElementPropForCapture](const void* A, const void* B) { return LocalElementPropForCapture->Identical(A, B); }
            );
            if (FoundIndex != INDEX_NONE)
            {
                RemoveAt(FoundIndex);
                return true;
            }
            else
            {
                return false;
            }
        }

        static FScriptSetHelper CreateHelperFormElementProperty(FProperty* InElementProperty, const void *InSet)
        {
            check(InElementProperty);

            FScriptSetHelper ScriptSetHelper;
            ScriptSetHelper.ElementProp = InElementProperty;
            ScriptSetHelper.Set = (FScriptSet*)InSet;

            const int32 ElementPropSize = InElementProperty->GetSize();
            const int32 ElementPropAlignment = InElementProperty->GetMinAlignment();
            ScriptSetHelper.SetLayout = FScriptSet::GetScriptLayout(ElementPropSize, ElementPropAlignment);

            return ScriptSetHelper;
        }

    private: 
        FScriptSetHelper()
            : ElementProp(nullptr)
            , Set(nullptr)
            , SetLayout(FScriptSet::GetScriptLayout(0, 1))
        {}

        /**
        * Internal function to call into the property system to construct / initialize elements.
        *
        * @param InternalIndex First item to construct.
        * @param Count Number of items to construct.
        */
        void ConstructItem(int32 InternalIndex)
        {
            check(IsValidIndex(InternalIndex));

            bool bZeroElement = !!(ElementProp->GetPropertyFlags() & CPF_ZeroConstructor);
            uint8* Dest = GetElementPtrWithoutCheck(InternalIndex);

            if (bZeroElement)
            {
                // If any nested property needs zeroing, just pre-zero the whole space
                FMemory::Memzero(Dest, SetLayout.Size);
            }

            if (!bZeroElement)
            {
                ElementProp->InitializeValue_InContainer(Dest);
            }
        }

        /**
        * Internal function to call into the property system to destruct elements.
        */
        void DestructItems(int32 InternalIndex, int32 Count)
        {
            check(InternalIndex >= 0);
            check(Count >= 0);

            if (Count == 0)
            {
                return;
            }

            bool bDestroyElements = !(ElementProp->GetPropertyFlags() & (CPF_IsPlainOldData | CPF_NoDestructor));

            if (bDestroyElements)
            {
                uint32 Stride = SetLayout.Size;
                uint8* ElementPtr = GetElementPtrWithoutCheck(InternalIndex);

                for (; Count; ++InternalIndex)
                {
                    if (IsValidIndex(InternalIndex))
                    {
                        ElementProp->DestroyValue_InContainer(ElementPtr);
                        --Count;
                    }
                    ElementPtr += Stride;
                }
            }
        }

        /**
        * Returns a uint8 pointer to the element in the array without checking the index.
        *
        * @param InternalIndex index of the item to return a pointer to.
        *
        * @return Pointer to the element, or nullptr if the array is empty.
        */
        FORCEINLINE uint8* GetElementPtrWithoutCheck(int32 InternalIndex)
        {
            return (uint8*)Set->GetData(InternalIndex, SetLayout);
        }

        /**
        * Returns a uint8 pointer to the element in the array without checking the index.
        *
        * @param InternalIndex index of the item to return a pointer to.
        *
        * @return Pointer to the pair, or nullptr if the array is empty.
        */
        FORCEINLINE const uint8* GetElementPtrWithoutCheck(int32 InternalIndex) const
        {
            return const_cast<FScriptSetHelper*>(this)->GetElementPtrWithoutCheck(InternalIndex);
        }

    public:
        FProperty*       ElementProp;
        FScriptSet*      Set;
        FScriptSetLayout SetLayout;
    };

    class FScriptSetHelper_InContainer : public FScriptSetHelper
    {
    public:
        FORCEINLINE FScriptSetHelper_InContainer(const FSetProperty* InProperty, const void* InArray, int32 FixedArrayIndex=0)
            :FScriptSetHelper(InProperty, InProperty->ContainerPtrToValuePtr<void>(InArray, FixedArrayIndex))
        {
        }
    };

    // ===================================================================
    // STRUCT PROPERTY
    // ===================================================================

    class RC_UE_API FStructProperty : public FProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FStructProperty, CASTCLASS_FStructProperty);
        DECLARE_VIRTUAL_TYPE(FStructProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FStructProperty.hpp>
    };

    // ===================================================================
    // DELEGATE PROPERTIES
    // ===================================================================

    template <typename TWeakPtr = FWeakObjectPtr>
    class TScriptDelegate
    {
    public:
        TWeakPtr Object;
        FName FunctionName;

    public:
        TScriptDelegate() : Object(), FunctionName(NAME_None) {}

        TScriptDelegate(const TScriptDelegate& Other)
            : Object(Other.Object), FunctionName(Other.FunctionName) {}

        TScriptDelegate& operator=(const TScriptDelegate& Other)
        {
            if (this != &Other)
            {
                Object = Other.Object;
                FunctionName = Other.FunctionName;
            }
            return *this;
        }

        void BindUFunction(UObject* InObject, const FName& InFunctionName)
        {
            Object = InObject;
            FunctionName = InFunctionName;
        }

        void Unbind()
        {
            Object = TWeakPtr();
            FunctionName = NAME_None;
        }

        void Clear()
        {
            Unbind();
        }

        bool IsBound() const
        {
            return IsBound_Internal<UObject>();
        }

        bool IsBoundToObject(void const* InUserObject) const
        {
            return InUserObject && (InUserObject == GetUObject());
        }

        bool IsBoundToObjectEvenIfUnreachable(void const* InUserObject) const
        {
            return InUserObject && (InUserObject == GetUObjectEvenIfUnreachable());
        }

        bool IsCompactable() const
        {
            return FunctionName == NAME_None || Object.Get() == nullptr;
        }

        UObject* GetUObject() const
        {
            return static_cast<UObject*>(Object.Get());
        }

        UObject* GetUObjectEvenIfUnreachable() const
        {
            return static_cast<UObject*>(Object.GetEvenIfUnreachable());
        }

        FName GetFunctionName() const
        {
            return FunctionName;
        }

        TWeakPtr& GetUObjectRef()
        {
            return Object;
        }

        const TWeakPtr& GetUObjectRef() const
        {
            return Object;
        }

        bool operator==(const TScriptDelegate& Other) const
        {
            return Object == Other.Object && FunctionName == Other.FunctionName;
        }

        bool operator!=(const TScriptDelegate& Other) const
        {
            return !(*this == Other);
        }

        template<typename UObjectTemplate>
        void ProcessDelegate(void* Parameters) const
        {
            auto ObjectPtr = static_cast<UObjectTemplate*>(Object.Get());
            auto Function = ObjectPtr->GetFunctionByName(FunctionName);
            ObjectPtr->ProcessEvent(Function, Parameters);
        }

        template<typename UObjectTemplate>
        bool IsBound_Internal() const
        {
            if (FunctionName != NAME_None)
            {
                if (UObject* ObjectPtr = Object.Get())
                {
                    // Here, we're supposed to cast to 'UObjectTemplate*' instead of assuming it's UObject*.
                    return ObjectPtr->GetFunctionByName(FunctionName) != nullptr;
                }
            }
            return false;
        }
    };
    using FScriptDelegate = TScriptDelegate<>;

    class RC_UE_API FDelegateProperty : public TProperty<FScriptDelegate, FProperty>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FDelegateProperty, CASTCLASS_FDelegateProperty);
        DECLARE_VIRTUAL_TYPE(FDelegateProperty);

    public:
#include <MemberVariableLayout_HeaderWrapper_FDelegateProperty.hpp>

    };

    template <typename TWeakPtr = FWeakObjectPtr>
    class TMulticastScriptDelegate
    {
    private:
        using FInvocationList = TArray<TScriptDelegate<TWeakPtr>>;

    public:
        FInvocationList InvocationList;

    public:
        TMulticastScriptDelegate() = default;

        TMulticastScriptDelegate(const TMulticastScriptDelegate& Other)
            : InvocationList(Other.InvocationList) {}

        TMulticastScriptDelegate& operator=(const TMulticastScriptDelegate& Other)
        {
            if (this != &Other)
            {
                InvocationList = Other.InvocationList;
            }
            return *this;
        }

        TMulticastScriptDelegate(TMulticastScriptDelegate&& Other) noexcept
            : InvocationList(std::move(Other.InvocationList)) {}

        TMulticastScriptDelegate& operator=(TMulticastScriptDelegate&& Other) noexcept
        {
            if (this != &Other)
            {
                InvocationList = std::move(Other.InvocationList);
            }
            return *this;
        }

        bool IsBound() const
        {
            return InvocationList.Num() > 0;
        }

        int32 Num() const
        {
            return InvocationList.Num();
        }

        bool Contains(const TScriptDelegate<TWeakPtr>& InDelegate) const
        {
            const UObject* Object = InDelegate.GetUObject();
            FName FunctionName = InDelegate.GetFunctionName();
            return Contains(Object, FunctionName);
        }

        bool Contains(const UObject* InObject, FName InFunctionName) const
        {
            for (int32 i = 0; i < InvocationList.Num(); ++i)
            {
                const auto& Delegate = InvocationList[i];
                if (Delegate.GetFunctionName() == InFunctionName &&
                    Delegate.IsBoundToObjectEvenIfUnreachable(InObject))
                {
                    return true;
                }
            }
            return false;
        }

        TArray<UObject*> GetAllObjects() const
        {
            TArray<UObject*> Result;
            for (int32 i = 0; i < InvocationList.Num(); ++i)
            {
                if (UObject* Obj = InvocationList[i].GetUObject())
                {
                    Result.Add(Obj);
                }
            }
            return Result;
        }

        template<typename UObjectTemplate>
        void ProcessMulticastDelegate(void* Parameters) const
        {
            if (InvocationList.Num() > 0)
            {
                using FInlineInvocationList = TArray<TScriptDelegate<TWeakPtr>, TInlineAllocator<4>>;
                FInlineInvocationList InvocationListCopy = FInlineInvocationList(InvocationList);
                for (const auto& InvocationElement : InvocationListCopy)
                {
                    if (InvocationElement.IsBound())
                    {
                        InvocationElement.template ProcessDelegate<UObjectTemplate>(Parameters);
                    }
                }
            }
        }
    };
    using FMulticastScriptDelegate = TMulticastScriptDelegate<>;

    class RC_UE_API FMulticastDelegateProperty : public FProperty
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FMulticastDelegateProperty, CASTCLASS_FMulticastDelegateProperty);
        DECLARE_VIRTUAL_TYPE(FMulticastDelegateProperty);

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
#include <MemberVariableLayout_HeaderWrapper_FMulticastDelegateProperty.hpp>

    // Virtual Functions
    public:
        const FMulticastScriptDelegate* GetMulticastDelegate(const void* PropertyValue) const;
        void SetMulticastDelegate(void* PropertyValue, FMulticastScriptDelegate ScriptDelegate) const;
        void AddDelegate(FScriptDelegate ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const;
        void RemoveDelegate(const FScriptDelegate& ScriptDelegate, UObject* Parent = nullptr, void* PropertyValue = nullptr) const;
        void ClearDelegate(UObject* Parent = nullptr, void* PropertyValue = nullptr) const;
    };

    class RC_UE_API FMulticastInlineDelegateProperty : public TProperty<FMulticastScriptDelegate, FMulticastDelegateProperty>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FMulticastInlineDelegateProperty, CASTCLASS_FMulticastInlineDelegateProperty);
        DECLARE_VIRTUAL_TYPE(FMulticastInlineDelegateProperty);
    };

    struct RC_UE_API FSparseDelegate
    {
    public:
        bool bIsBound;

    public:
        FSparseDelegate() : bIsBound(false) {}

        bool IsBound() const
        {
            return bIsBound;
        }
    };

    class RC_UE_API FMulticastSparseDelegateProperty : public TProperty<FSparseDelegate, FMulticastDelegateProperty>
    {
        DECLARE_FIELD_CLASS_WITH_CAST(FMulticastSparseDelegateProperty, CASTCLASS_FMulticastSparseDelegateProperty);
        DECLARE_VIRTUAL_TYPE(FMulticastSparseDelegateProperty);
    };
    
    /*-----------------------------------------------------------------------------
    PropertyList.
    -----------------------------------------------------------------------------*/
    
    
    /** Describes a single node in a custom property list. */
    struct COREUOBJECT_API FCustomPropertyListNode
    {
        /** The property that's being referenced at this node. */
        FProperty* Property;

        /** Used to identify which array index is specifically being referenced if this is an array property. Defaults to 0. */
        int32 ArrayIndex;

        /** If this node represents a struct property, this may contain a "sub" property list for the struct itself. */
        struct FCustomPropertyListNode* SubPropertyList;

        /** Points to the next node in the list. */
        struct FCustomPropertyListNode* PropertyListNext;

        /** Default constructor. */
        FCustomPropertyListNode(FProperty* InProperty = nullptr, int32 InArrayIndex = 0)
            :Property(InProperty)
            , ArrayIndex(InArrayIndex)
            , SubPropertyList(nullptr)
            , PropertyListNext(nullptr)
        {
        }

        /** Convenience method to return the next property in the list and advance the given ptr. */
        FORCEINLINE static FProperty* GetNextPropertyAndAdvance(const FCustomPropertyListNode*& Node)
        {
            if (Node)
            {
                Node = Node->PropertyListNext;
            }

            return Node ? Node->Property : nullptr;
        }
    };

    /*-----------------------------------------------------------------------------
    TFieldIterator.
    -----------------------------------------------------------------------------*/
    
    /** TFieldIterator construction flags */
    enum class EFieldIterationFlags : uint8
    {
        None                = 0,
        IncludeSuper        = 1 << 0, // Include super class
        IncludeDeprecated   = 1 << 1, // Include deprecated properties
        IncludeInterfaces   = 1 << 2, // Include interfaces

        IncludeAll          = IncludeSuper | IncludeDeprecated | IncludeInterfaces,

        Default             = IncludeSuper | IncludeDeprecated,
    };
    ENUM_CLASS_FLAGS(EFieldIterationFlags);

    /** Old-style TFieldIterator construction flags */
    namespace EFieldIteratorFlags
    {
        enum SuperClassFlags
        {
            ExcludeSuper = (uint8)EFieldIterationFlags::None,
            IncludeSuper = (uint8)EFieldIterationFlags::IncludeSuper,
        };

        enum DeprecatedPropertyFlags
        {
            ExcludeDeprecated = (uint8)EFieldIterationFlags::None,
            IncludeDeprecated = (uint8)EFieldIterationFlags::IncludeDeprecated,
        };

        enum InterfaceClassFlags
        {
            ExcludeInterfaces = (uint8)EFieldIterationFlags::None,
            IncludeInterfaces = (uint8)EFieldIterationFlags::IncludeInterfaces,
        };
    }

    template <class FieldType>
    FieldType* GetChildFieldsFromStruct(UStruct* Owner)
    {
        check(false);
        return nullptr;
    }

    template <>
    inline UField* GetChildFieldsFromStruct(UStruct* Owner)
    {
        // UField is always stored in Children, regardless of version
        return Owner->GetChildren();
    }

    template <>
    inline FField* GetChildFieldsFromStruct(UStruct* Owner)
    {
        if (Version::IsBelow(4, 25))
        {
            // In < 4.25, FField* is actually UField*, so we need to cast
            return std::bit_cast<FField*>(Owner->GetChildren().Get());
        }
        else
        {
            return Owner->GetChildProperties();
        }
    }

    // Helper to get next field in version-aware manner
    template <class FieldType>
    FieldType* GetNextField(FieldType* Field)
    {
        check(false);
        return nullptr;
    }

    template <>
    inline UField* GetNextField(UField* Field)
    {
        // UField::GetNext() works in all versions
        return Field->GetNext();
    }

    template <>
    inline FField* GetNextField(FField* Field)
    {
        if (Version::IsBelow(4, 25))
        {
            UField* AsUField = std::bit_cast<UField*>(Field);
            return std::bit_cast<FField*>(AsUField->GetNext().Get());
        }
        else
        {
            return Field->GetNextFFieldUnsafe();
        }
    }

    //
    // For iterating through a linked list of fields.
    //
    template <class T>
    class TFieldIterator
    {
    private:
        /** The object being searched for the specified field */
        UStruct* Struct;
        /** The current location in the list of fields being iterated */
        typename T::BaseFieldClass* Field;
        /** The index of the current interface being iterated */
        int32 InterfaceIndex;
        /** Whether to include the super class or not */
        const bool bIncludeSuper;
        /** Whether to include deprecated fields or not */
        const bool bIncludeDeprecated;
        /** Whether to include interface fields or not */
        const bool bIncludeInterface;

    public:
        TFieldIterator(UStruct* InStruct, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::Default)
            : Struct            ( InStruct )
            , Field             ( InStruct ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(InStruct) : NULL )
            , InterfaceIndex    ( -1 )
            , bIncludeSuper     ( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeSuper) )
            , bIncludeDeprecated( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeDeprecated) )
            , bIncludeInterface ( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeInterfaces) && InStruct && InStruct->IsA(UClass::StaticClass()) )
        {
            IterateToNext();
        }

        /** Legacy version taking the flags as 3 separate values */
        TFieldIterator(const UStruct*                               InStruct,
                       EFieldIteratorFlags::SuperClassFlags         InSuperClassFlags,
                       EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedFieldFlags = EFieldIteratorFlags::IncludeDeprecated,
                       EFieldIteratorFlags::InterfaceClassFlags     InInterfaceFieldFlags  = EFieldIteratorFlags::ExcludeInterfaces)
            : TFieldIterator(InStruct, (EFieldIterationFlags)(InSuperClassFlags | InDeprecatedFieldFlags | InInterfaceFieldFlags))
        {
        }

        /** conversion to "bool" returning true if the iterator is valid. */
        UE_FORCEINLINE_HINT explicit operator bool() const
        {
            return Field != NULL;
        }
        /** inverse of the "bool" operator */
        UE_FORCEINLINE_HINT bool operator !() const
        {
            return !(bool)*this;
        }

        inline bool operator==(const TFieldIterator<T>& Rhs) const { return Field == Rhs.Field; }
        inline bool operator!=(const TFieldIterator<T>& Rhs) const { return Field != Rhs.Field; }

        inline void operator++()
        {
            checkSlow(Field);
            Field = GetNextField(Field);
            IterateToNext();
        }
        inline T* operator*()
        {
            checkSlow(Field);
            return (T*)Field;
        }
        inline const T* operator*() const
        {
            checkSlow(Field);
            return (const T*)Field;
        }
        inline T* operator->()
        {
            checkSlow(Field);
            return (T*)Field;
        }
        inline const UStruct* GetStruct()
        {
            return Struct;
        }
    protected:
        inline void IterateToNext()
        {
            if (Version::IsBelow(4, 25))
            {
                IterateToNext_Pre425();
            }
            else
            {
                IterateToNext_425Plus();
            }
        }

    private:
        // Pre-4.25 specialized iteration path
        inline void IterateToNext_Pre425()
        {
            typename T::BaseFieldClass* CurrentField  = Field;
            UStruct* CurrentStruct = Struct;

            while (CurrentStruct)
            {
                for (; CurrentField; CurrentField = GetNextField(CurrentField))
                {
                    // In pre-4.25, work with UField directly to avoid expensive GetClass() calls
                    if constexpr (std::is_same_v<typename T::BaseFieldClass, FField>)
                    {
                        UField* CurrentUField = std::bit_cast<UField*>(CurrentField);
                        UClass* UFieldClass = CurrentUField->GetClassPrivate();

                        if (!UFieldClass->HasAllCastFlags(static_cast<EClassCastFlags>(T::StaticClassCastFlags())))
                        {
                            continue;
                        }

                        if (UFieldClass->HasAllCastFlags(CASTCLASS_FProperty))
                        {
                            FProperty* Prop = (FProperty*)CurrentField;
                            if (Prop->HasAllPropertyFlags(CPF_Deprecated) && !bIncludeDeprecated)
                            {
                                continue;
                            }
                        }
                    }
                    else
                    {
                        // For UField-derived types (UFunction, etc.)
                        UField* CurrentUField = (UField*)CurrentField;
                        UClass* UFieldClass = CurrentUField->GetClassPrivate();

                        if (!UFieldClass->HasAllCastFlags(static_cast<EClassCastFlags>(T::StaticClassCastFlags())))
                        {
                            continue;
                        }
                    }

                    Struct = CurrentStruct;
                    Field = CurrentField;
                    return;
                }

                if (bIncludeInterface)
                {
                    // We shouldn't be able to get here for non-classes
                    UClass* CurrentClass = (UClass*)CurrentStruct;
                    ++InterfaceIndex;
                    if (InterfaceIndex < CurrentClass->GetInterfaces().Num())
                    {
                        FImplementedInterface& Interface = CurrentClass->GetInterfaces()[InterfaceIndex];
                        CurrentField = Interface.Class ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(Interface.Class) : nullptr;
                        continue;
                    }
                }

                if (bIncludeSuper)
                {
                    CurrentStruct = CurrentStruct->GetSuperStruct();
                    if (CurrentStruct)
                    {
                        CurrentField   = GetChildFieldsFromStruct<typename T::BaseFieldClass>(CurrentStruct);
                        InterfaceIndex = -1;
                        continue;
                    }
                }

                break;
            }

            Struct = CurrentStruct;
            Field  = CurrentField;
        }

        // 4.25+ specialized iteration path
        inline void IterateToNext_425Plus()
        {
            typename T::BaseFieldClass* CurrentField  = Field;
            UStruct* CurrentStruct = Struct;

            while (CurrentStruct)
            {
                for (; CurrentField; CurrentField = GetNextField(CurrentField))
                {
                    // For UField-derived types (UFunction, etc.), use GetClassPrivate() which returns UClass*
                    // For FField-derived types (FProperty, etc.), use GetClass() which returns FFieldClass
                    if constexpr (std::is_same_v<typename T::BaseFieldClass, UField>)
                    {
                        UField* CurrentUField = (UField*)CurrentField;
                        UClass* UFieldClass = CurrentUField->GetClassPrivate();

                        if (!UFieldClass->HasAllCastFlags(static_cast<EClassCastFlags>(T::StaticClassCastFlags())))
                        {
                            continue;
                        }
                    }
                    else
                    {
                        // Cache GetClass() result to avoid multiple calls per iteration
                        auto FieldClass = CurrentField->GetClass();

                        if (!FieldClass.HasAllCastFlags(T::StaticClassCastFlags()))
                        {
                            continue;
                        }

                        // Check for deprecated properties - reuse cached FieldClass to avoid second GetClass() call
                        if (!bIncludeDeprecated && FieldClass.HasAllCastFlags(CASTCLASS_FProperty))
                        {
                            FProperty* Prop = (FProperty*)CurrentField;
                            if (Prop->HasAllPropertyFlags(CPF_Deprecated))
                            {
                                continue;
                            }
                        }
                    }

                    Struct = CurrentStruct;
                    Field = CurrentField;
                    return;
                }

                if (bIncludeInterface)
                {
                    // We shouldn't be able to get here for non-classes
                    UClass* CurrentClass = (UClass*)CurrentStruct;
                    ++InterfaceIndex;
                    if (InterfaceIndex < CurrentClass->GetInterfaces().Num())
                    {
                        FImplementedInterface& Interface = CurrentClass->GetInterfaces()[InterfaceIndex];
                        CurrentField = Interface.Class ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(Interface.Class) : nullptr;
                        continue;
                    }
                }

                if (bIncludeSuper)
                {
                    CurrentStruct = CurrentStruct->GetSuperStruct();
                    if (CurrentStruct)
                    {
                        CurrentField   = GetChildFieldsFromStruct<typename T::BaseFieldClass>(CurrentStruct);
                        InterfaceIndex = -1;
                        continue;
                    }
                }

                break;
            }

            Struct = CurrentStruct;
            Field  = CurrentField;
        }
    };

    template <typename T>
    struct TFieldRange
    {
        TFieldRange(UStruct* InStruct, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::Default)
            : Begin(InStruct, InIterationFlags)
        {
        }

        /** Legacy version taking the flags as 3 separate values */
        TFieldRange(UStruct*                                     InStruct,
                    EFieldIteratorFlags::SuperClassFlags         InSuperClassFlags,
                    EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedFieldFlags = EFieldIteratorFlags::IncludeDeprecated,
                    EFieldIteratorFlags::InterfaceClassFlags     InInterfaceFieldFlags  = EFieldIteratorFlags::ExcludeInterfaces)
            : TFieldRange(InStruct, (EFieldIterationFlags)(InSuperClassFlags | InDeprecatedFieldFlags | InInterfaceFieldFlags))
        {
        }

        friend TFieldIterator<T> begin(const TFieldRange& Range) { return Range.Begin; }
        friend TFieldIterator<T> end  (const TFieldRange& Range) { return TFieldIterator<T>(NULL); }

        TFieldIterator<T> Begin;
    };

    //
    // Simple iterator for walking up the super struct chain
    //
    class TSuperStructIterator
    {
    private:
        UStruct* Current;

    public:
        TSuperStructIterator(UStruct* InStruct)
            : Current(InStruct ? InStruct->GetSuperStruct() : nullptr)
        {
        }

        /** conversion to "bool" returning true if the iterator is valid. */
        UE_FORCEINLINE_HINT explicit operator bool() const
        {
            return Current != nullptr;
        }
        /** inverse of the "bool" operator */
        UE_FORCEINLINE_HINT bool operator !() const
        {
            return Current == nullptr;
        }

        inline bool operator==(const TSuperStructIterator& Rhs) const { return Current == Rhs.Current; }
        inline bool operator!=(const TSuperStructIterator& Rhs) const { return Current != Rhs.Current; }

        inline void operator++()
        {
            checkSlow(Current);
            Current = Current->GetSuperStruct();
        }
        inline UStruct* operator*()
        {
            checkSlow(Current);
            return Current;
        }
        inline const UStruct* operator*() const
        {
            checkSlow(Current);
            return Current;
        }
        inline UStruct* operator->()
        {
            checkSlow(Current);
            return Current;
        }
    };

    struct TSuperStructRange
    {
        TSuperStructRange(UStruct* InStruct)
            : Begin(InStruct)
        {
        }

        friend TSuperStructIterator begin(const TSuperStructRange& Range) { return Range.Begin; }
        friend TSuperStructIterator end  (const TSuperStructRange& Range) { return TSuperStructIterator(nullptr); }

        TSuperStructIterator Begin;
    };

    //
    // Reverse field range - iterates fields from parent to child (reverse inheritance order)
    // Collects struct hierarchy then iterates root->child, yielding each struct's fields in order
    //
    template <typename T>
    struct TReverseFieldRange
    {
    private:
        std::vector<UStruct*> StructHierarchy;
        EFieldIterationFlags Flags;

        class TIterator
        {
        private:
            /** Pointer to the array of structs to iterate through */
            const std::vector<UStruct*>* StructArray;
            /** Current struct being iterated */
            UStruct* Struct;
            /** The current location in the list of fields being iterated */
            typename T::BaseFieldClass* Field;
            /** Index into StructArray */
            size_t StructIndex;
            /** Whether to include deprecated fields or not */
            const bool bIncludeDeprecated;

            inline void IterateToNext()
            {
                while (StructIndex < StructArray->size())
                {
                    while (Field)
                    {
                        bool bPassesFilter = true;
                        
                        if constexpr (std::is_same_v<typename T::BaseFieldClass, UField>)
                        {
                            UField* CurrentUField = static_cast<UField*>(Field);
                            UClass* UFieldClass = CurrentUField->GetClassPrivate();

                            if (!UFieldClass->HasAllCastFlags(static_cast<EClassCastFlags>(T::StaticClassCastFlags())))
                            {
                                bPassesFilter = false;
                            }
                        }
                        else
                        {
                            auto FieldClass = Field->GetClass();

                            if (!FieldClass.HasAllCastFlags(T::StaticClassCastFlags()))
                            {
                                bPassesFilter = false;
                            }
                            else if (FieldClass.HasAllCastFlags(CASTCLASS_FProperty))
                            {
                                FProperty* Prop = static_cast<FProperty*>(Field);
                                if (Prop->HasAllPropertyFlags(CPF_Deprecated) && !bIncludeDeprecated)
                                {
                                    bPassesFilter = false;
                                }
                            }
                        }

                        if (bPassesFilter)
                        {
                            return;
                        }

                        Field = GetNextField(Field);
                    }

                    ++StructIndex;
                    if (StructIndex < StructArray->size())
                    {
                        Struct = (*StructArray)[StructIndex];
                        Field = GetChildFieldsFromStruct<typename T::BaseFieldClass>(Struct);
                    }
                }
            }

        public:
            TIterator(const std::vector<UStruct*>* InStructs, EFieldIterationFlags InIterationFlags, size_t InIndex)
                : StructArray(InStructs)
                , Struct(InStructs && InIndex < InStructs->size() ? (*InStructs)[InIndex] : nullptr)
                , Field(Struct ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(Struct) : nullptr)
                , StructIndex(InIndex)
                , bIncludeDeprecated(EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeDeprecated))
            {
                IterateToNext();
            }

            inline void operator++()
            {
                checkSlow(Field);
                Field = GetNextField(Field);
                IterateToNext();
            }

            inline T* operator*()
            {
                checkSlow(Field);
                return static_cast<T*>(Field);
            }
            inline const T* operator*() const
            {
                checkSlow(Field);
                return static_cast<const T*>(Field);
            }

            inline T* operator->()
            {
                checkSlow(Field);
                return static_cast<T*>(Field);
            }

            inline const UStruct* GetStruct() const
            {
                return Struct;
            }

            inline bool operator==(const TIterator& Rhs) const { return Field == Rhs.Field; }
            inline bool operator!=(const TIterator& Rhs) const { return Field != Rhs.Field; }
        };

    public:
        TReverseFieldRange(UStruct* InStruct, EFieldIterationFlags InFlags = EFieldIterationFlags::IncludeDeprecated)
            : Flags(InFlags)
        {
            if (!InStruct) return;
            
            StructHierarchy.push_back(InStruct);
            for (UStruct* SuperStruct : TSuperStructRange(InStruct))
            {
                if (!SuperStruct) break;
                StructHierarchy.push_back(SuperStruct);
            }
            
            std::reverse(StructHierarchy.begin(), StructHierarchy.end());
        }

        TIterator begin() const { return TIterator(&StructHierarchy, Flags, 0); }
        TIterator end() const { return TIterator(&StructHierarchy, Flags, StructHierarchy.size()); }
    };
}
