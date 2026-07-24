#pragma once
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <DynamicOutput/Output.hpp>
#include <Misc/Optional.hpp>
#include <Unreal/Core/Templates/AlignmentTemplates.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    // 
    // Encapsulates the memory layout logic for an optional without implementing the full FProperty API.
    //
    struct RC_UE_API FOptionalPropertyLayout
    {
        
        /*explicit FOptionalPropertyLayout(FProperty* InValueProperty)
        {
            GetValueProperty() = InValueProperty;
            check(GetValueProperty());
        }*/
    public:
        FProperty* ValueProperty;
      
        /*FProperty* GetValueProperty() const 
        {
            if (ValueProperty) { return ValueProperty; }
            int FPropertyFinalMemberOffset = FProperty::MemberOffsets.find(STR("RepNotifyFunc"))->second;
            int ValuePropertyOffset = FPropertyFinalMemberOffset + sizeof(FName);
            FProperty* ValueProperty2 = *Helper::Casting::ptr_cast<FProperty**>(this, ValuePropertyOffset);
            checkf(ValueProperty2, TEXT("Expected ValueProperty to be initialized"));
            ValueProperty = *ValueProperty2;
            return ValueProperty;
        }*/

        FProperty*& GetValueProperty() const 
        {
            static int ValuePropertyOffset = [] {
                auto FPropertyFinalMember = FProperty::MemberOffsets.find(STR("RepNotifyFunc"));
                if (FPropertyFinalMember == FProperty::MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FProperty::RepNotifyFunc' that doesn't exist in this engine version."}; }
                int FPropertyFinalOffset =  FPropertyFinalMember->second;
                return FPropertyFinalOffset + sizeof(FName);
            }();
            
            FProperty*& ValueProperty = *Helper::Casting::ptr_cast<FProperty**>(this, ValuePropertyOffset);
            checkf(ValueProperty, TEXT("Expected ValueProperty to be initialized"));
            return ValueProperty;
        }

        FORCEINLINE bool IsSet(const void* Data) const
        {
            checkSlow(Data);
            return GetValueProperty()->HasIntrusiveUnsetOptionalState()
                ? GetValueProperty()->IsIntrusiveOptionalValueSet(Data)
                : *GetIsSetPointer(Data);
        }
        FORCEINLINE void* MarkSetAndGetInitializedValuePointerToReplace(void* Data) const
        {
            checkSlow(Data);
            if (GetValueProperty()->HasIntrusiveUnsetOptionalState())
            {
                if (!IsSet(Data))
                {
                    // Need to destroy the value in its optional unset state first 
                    GetValueProperty()->DestroyValue(Data);
                    GetValueProperty()->InitializeValue(Data);
                }
            }
            else
            {
                bool* IsSetPointer = GetIsSetPointer(Data);
                if (!*IsSetPointer)
                {
                    GetValueProperty()->InitializeValue(Data);
                    *IsSetPointer = true;
                }
            }
            return Data;
        }
        FORCEINLINE void MarkUnset(void* Data) const
        {
            checkSlow(Data);
            if (GetValueProperty()->HasIntrusiveUnsetOptionalState())
            {
                GetValueProperty()->ClearIntrusiveOptionalValue(Data);
            }
            else
            {
                bool* IsSetPointer = GetIsSetPointer(Data);
                if (*IsSetPointer)
                {
                    GetValueProperty()->DestroyValue(Data);
                    *IsSetPointer = false;
                }
            }
        }

        // For reading the value of a set optional.
        // Must be called on a non-null pointer to a set optional.
        FORCEINLINE const void* GetValuePointerForRead(const void* Data) const 
        {
            checkSlow(Data && IsSet(Data));
            return Data; 
        }
        
        // For replacing the value of a set optional.
        // Must be called on a non-null pointer to a set optional.
        FORCEINLINE void* GetValuePointerForReplace(void* Data) const
        {
            checkSlow(Data && IsSet(Data));
            return Data;
        }

        // For reading the value of a set optional.
        // Must be called on a non-null pointer to an optional.
        // If called on an unset optional, will return null.
        FORCEINLINE const void* GetValuePointerForReadIfSet(const void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }
        
        // For replacing the value of a set optional.
        // Must be called on a non-null pointer to an optional.
        // If called on an unset optional, will return null.
        FORCEINLINE void* GetValuePointerForReplaceIfSet(void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }
        
        // For calling from polymorphic code that doesn't know whether it needs the value pointer for
        // read or replace, or whether it has a const pointer or not.
        // Must be called on a non-null pointer to a set optional.
        FORCEINLINE const void* GetValuePointerForReadOrReplace(const void* Data) const
        {
            checkSlow(Data && IsSet(Data));
            return Data;
        }
        FORCEINLINE void* GetValuePointerForReadOrReplace(void* Data) const
        {
            checkSlow(Data && IsSet(Data));
            return Data;
        }
        
        // For calling from polymorphic code that doesn't know whether it needs the value pointer for
        // read or replace, or whether it has a const pointer or not.
        // Must be called on a non-null pointer to an optional.
        // If called on an unset optional, will return null.
        FORCEINLINE const void* GetValuePointerForReadOrReplaceIfSet(const void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }
        FORCEINLINE void* GetValuePointerForReadOrReplaceIfSet(void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }

        FORCEINLINE int32 CalcSize() const
        {
            if (GetValueProperty()->HasIntrusiveUnsetOptionalState())
            {
                return GetValueProperty()->GetSize();
            }
            else
            {
                return Align(CalcIsSetOffset() + 1, GetValueProperty()->GetMinAlignment());
            }
        }
        
    protected:

        FORCEINLINE int32 CalcIsSetOffset() const
        {
            check(!GetValueProperty()->HasIntrusiveUnsetOptionalState());
            checkfSlow(
                GetValueProperty()->GetSize() == Align(ValueProperty->GetSize(), ValueProperty->GetMinAlignment()),
                TEXT("Expected optional value property to have aligned size, but got misaligned size %i for %s that has minimum alignment %i"),
                GetValueProperty()->GetSize(),
                *GetValueProperty()->GetFullName(),
                GetValueProperty()->GetMinAlignment());
            return GetValueProperty()->GetSize();
        }

        FORCEINLINE bool* GetIsSetPointer(void* Data) const
        {
            return reinterpret_cast<bool*>(reinterpret_cast<uint8*>(Data) + CalcIsSetOffset());
        }
        FORCEINLINE const bool* GetIsSetPointer(const void* Data) const
        {
            return reinterpret_cast<const bool*>(reinterpret_cast<const uint8*>(Data) + CalcIsSetOffset());
        }
    };

    class RC_UE_API FOptionalProperty : public FProperty/*, public FOptionalPropertyLayout*/
    {
        DECLARE_FIELD_CLASS(FOptionalProperty);
        DECLARE_VIRTUAL_TYPE(FOptionalProperty);

        /*FOptionalProperty(FFieldVariant InOwner, const FName& InName, EObjectFlags InObjectFlags);*/
        /*FOptionalProperty(FFieldVariant InOwner, const UECodeGen_Private::FGenericPropertyParams& Prop);*/
        /*virtual ~FOptionalProperty();*/

        // Sets the optional property's value property.
        void SetValueProperty(FProperty* InValueProperty);

        // TODO: Move FOptionalPropertyLayout methods back to it when multiple inheritance is supported
        // FOptionalPropertyLayout methods begin
        FProperty*& GetValueProperty() const 
        {
            static int ValuePropertyOffset = [] {
                auto FPropertyFinalMember = MemberOffsets.find(STR("RepNotifyFunc"));
                if (FPropertyFinalMember == MemberOffsets.end()) { throw std::runtime_error{"Tried getting member variable 'FProperty::RepNotifyFunc' that doesn't exist in this engine version."}; }
                int FPropertyFinalOffset =  FPropertyFinalMember->second;
                return FPropertyFinalOffset + sizeof(FName);
            }();
                
            FProperty*& ValueProperty = *Helper::Casting::ptr_cast<FProperty**>(this, ValuePropertyOffset);
            checkf(ValueProperty, TEXT("Expected ValueProperty to be initialized"));
            return ValueProperty;
        }
      

        FORCEINLINE bool IsSet(const void* Data) const
        {
            checkSlow(Data);
            return GetValueProperty()->HasIntrusiveUnsetOptionalState()
                ? GetValueProperty()->IsIntrusiveOptionalValueSet(Data)
                : *GetIsSetPointer(Data);
        }
        FORCEINLINE void* MarkSetAndGetInitializedValuePointerToReplace(void* Data) const
        {
            checkSlow(Data);
            if (GetValueProperty()->HasIntrusiveUnsetOptionalState())
            {
                if (!IsSet(Data))
                {
                    // Need to destroy the value in its optional unset state first 
                    GetValueProperty()->DestroyValue(Data);
                    GetValueProperty()->InitializeValue(Data);
                }
            }
            else
            {
                bool* IsSetPointer = GetIsSetPointer(Data);
                if (!*IsSetPointer)
                {
                    GetValueProperty()->InitializeValue(Data);
                    *IsSetPointer = true;
                }
            }
            return Data;
        }
        FORCEINLINE void MarkUnset(void* Data) const
        {
            checkSlow(Data);
            if (GetValueProperty()->HasIntrusiveUnsetOptionalState())
            {
                GetValueProperty()->ClearIntrusiveOptionalValue(Data);
            }
            else
            {
                bool* IsSetPointer = GetIsSetPointer(Data);
                if (*IsSetPointer)
                {
                    GetValueProperty()->DestroyValue(Data);
                    *IsSetPointer = false;
                }
            }
        }

        // For reading the value of a set optional.
        // Must be called on a non-null pointer to a set optional.
        FORCEINLINE const void* GetValuePointerForRead(const void* Data) const 
        {
            checkSlow(Data && IsSet(Data));
            return Data; 
        }
        
        // For replacing the value of a set optional.
        // Must be called on a non-null pointer to a set optional.
        FORCEINLINE void* GetValuePointerForReplace(void* Data) const
        {
            checkSlow(Data && IsSet(Data));
            return Data;
        }

        // For reading the value of a set optional.
        // Must be called on a non-null pointer to an optional.
        // If called on an unset optional, will return null.
        FORCEINLINE const void* GetValuePointerForReadIfSet(const void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }
        
        // For replacing the value of a set optional.
        // Must be called on a non-null pointer to an optional.
        // If called on an unset optional, will return null.
        FORCEINLINE void* GetValuePointerForReplaceIfSet(void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }
        
        // For calling from polymorphic code that doesn't know whether it needs the value pointer for
        // read or replace, or whether it has a const pointer or not.
        // Must be called on a non-null pointer to a set optional.
        FORCEINLINE const void* GetValuePointerForReadOrReplace(const void* Data) const
        {
            checkSlow(Data && IsSet(Data));
            return Data;
        }
        FORCEINLINE void* GetValuePointerForReadOrReplace(void* Data) const
        {
            checkSlow(Data && IsSet(Data));
            return Data;
        }
        
        // For calling from polymorphic code that doesn't know whether it needs the value pointer for
        // read or replace, or whether it has a const pointer or not.
        // Must be called on a non-null pointer to an optional.
        // If called on an unset optional, will return null.
        FORCEINLINE const void* GetValuePointerForReadOrReplaceIfSet(const void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }
        FORCEINLINE void* GetValuePointerForReadOrReplaceIfSet(void* Data) const
        {
            checkSlow(Data);
            return IsSet(Data) ? Data : nullptr;
        }

        FORCEINLINE int32 CalcSize() const
        {
            if (GetValueProperty()->HasIntrusiveUnsetOptionalState())
            {
                return GetValueProperty()->GetSize();
            }
            else
            {
                return Align(CalcIsSetOffset() + 1, GetValueProperty()->GetMinAlignment());
            }
        }
        
    protected:

        FORCEINLINE int32 CalcIsSetOffset() const
        {
            check(!GetValueProperty()->HasIntrusiveUnsetOptionalState());
            checkfSlow(
                GetValueProperty()->GetSize() == Align(ValueProperty->GetSize(), ValueProperty->GetMinAlignment()),
                TEXT("Expected optional value property to have aligned size, but got misaligned size %i for %s that has minimum alignment %i"),
                GetValueProperty()->GetSize(),
                *GetValueProperty()->GetFullName(),
                GetValueProperty()->GetMinAlignment());
            return GetValueProperty()->GetSize();
        }

        FORCEINLINE bool* GetIsSetPointer(void* Data) const
        {
            return reinterpret_cast<bool*>(reinterpret_cast<uint8*>(Data) + CalcIsSetOffset());
        }
        FORCEINLINE const bool* GetIsSetPointer(const void* Data) const
        {
            return reinterpret_cast<const bool*>(reinterpret_cast<const uint8*>(Data) + CalcIsSetOffset());
        }
        // FOptionalPropertyLayout methods end
    };
}



