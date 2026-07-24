// WARNING: Nothing in this file should be used as if part of the public API.
//          Everything here is experimental, changes can and will happen arbitrarily without notice, or explanation.

#pragma once

#include <utility>
#include <bit>
#include <type_traits>
#include <fmt/core.h>

#include <Helpers/String.hpp>

#include <Unreal/UObject.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>

// Helper macro to create a helper function for retrieving properties from class instances by name.
// Use this macro to define properties for classes that haven't been generated with UVTD, for example in C++ mods.
// Properties defined this way can be accessed by name without needing to worry about changes to the class layout brought by game or engine updates.
// Logs an error, and aborts game execution if the property doesn't exist when access is attempted.
/**
 * @example
 *      class ACharacter : public AActor
 *      {
 *      public:
 *         RC_INTERNAL_DEFINE_BP_PROPERTY_PRIVATE(int32_t, JumpMaxCount);
 *         RC_INTERNAL_DEFINE_BP_PROPERTY_PRIVATE(int32_t, JumpCurrentCount);
 *         RC_INTERNAL_DEFINE_BP_PROPERTY_PRIVATE(bool, bCanBeDamaged);
 *      }
 *
 *      auto Character = static_cast<ACharacter*>(FindFirstOf(STR("Character")));
 *      Output::send(STR("You've jumped {}/{} times.\n"), Character->GetJumpCurrentCount(), Character->GetJumpMaxCount());
 *      Character->SetJumpMaxCount(3);
 *      Output::send(STR("You can now jump a total of 3 times.\n"));
 *      Character->GetRefJumpMaxCount() = 10;
 *      Output::send(STR("You can now jump a total of 10 times.\n"));
 *      Character->GetRefbCanBeDamaged() = false; // This is a compile error, because bitfields cannot be returned by reference.
 *      Character->SetbCanBeDamaged(false); // This is the correct way to set a bool.
 *
 */

#define RC_SELECT_ONE(SetOrGet, One) SetOrGet##One
#define RC_SELECT_TWO(SetOrGet, One, Two) SetOrGet##Two
#define RC_GET_SELECT_TWO_IF_EXISTS_MACRO(_1, _2, Name, ...) Name
#define RC_SELECT_TWO_IF_EXISTS(SetOrGet, ...) RC_GET_SELECT_TWO_IF_EXISTS_MACRO(__VA_ARGS__, RC_SELECT_TWO, RC_SELECT_ONE)(SetOrGet, __VA_ARGS__)

#define RC_DEFINE_PROPERTY_GET_BODY(Type, Name)                                                                                                                \
    return PropertyMacro::Internal::Get<Type>(STR(#Name), this);

#define RC_DEFINE_PROPERTY_GET_REF_BODY(Type, Name)                                                                                                            \
    return PropertyMacro::Internal::GetRef<Type>(STR(#Name), this);

#define RC_DEFINE_PROPERTY_SET_BODY(Type, Name)                                                                                                                \
    PropertyMacro::Internal::Set<Type>(STR(#Name), this, NewValue);

#define RC_INTERNAL_DEFINE_BP_PROPERTY_PRIVATE(Type, Name, ...)                                                                                                                       \
    inline auto RC_SELECT_TWO_IF_EXISTS(RC_INTERNAL_BP_Get, Name __VA_OPT__(, ) __VA_ARGS__)()                                                                                \
    {                                                                                                                                                          \
        RC_DEFINE_PROPERTY_GET_BODY(Type, Name)                                                                                                                \
    }/*                                                                                                                                                        \
    inline auto RC_SELECT_TWO_IF_EXISTS(BP_Get, Name __VA_OPT__(,) __VA_ARGS__)() const                                                                           \
    {                                                                                                                                                          \
        RC_DEFINE_PROPERTY_GET_BODY(const Type, Name)                                                                                                          \
    }*/                                                                                                                                                        \
    template<typename ReturnType = Type>                                                                                                                       \
    inline decltype(auto) RC_SELECT_TWO_IF_EXISTS(RC_INTERNAL_BP_GetRef, Name __VA_OPT__(, ) __VA_ARGS__)() requires (PropertyMacro::Internal::CanBeRef<ReturnType>)          \
    {                                                                                                                                                          \
        RC_DEFINE_PROPERTY_GET_REF_BODY(Type, Name)                                                                                                            \
    }                                                                                                                                                          \
    inline void RC_SELECT_TWO_IF_EXISTS(RC_INTERNAL_BP_Set, Name __VA_OPT__(, ) __VA_ARGS__)(Type NewValue)                                                                   \
    {                                                                                                                                                          \
        RC_DEFINE_PROPERTY_SET_BODY(Type, Name)                                                                                                                \
    }

namespace RC::Unreal::PropertyMacro::Internal
{
    template <typename T>
    concept CanBeRef = [] {
        static_assert(!std::is_same_v<std::remove_pointer_t<std::remove_reference_t<T>>, bool>,
                      "GetRef cannot be called on bool types, because: Can't determine if it's a bitfield.");
        return true;
    }();


    // TODO: Implement const version of 'GetPropertyByNameInChain' and all of the functions it depends on in the Unreal submodule.
    //       After that, uncomment the const version of the getter function.
    //       This is to allow getters to be used in const functions.
    //       Despite the fact that we could allow mutations of properties in const functions,
    //       we probably shouldn't (by making return types const) because C++ normally doesn't allow that.
    // Implementation details: 1. We're not using the convenience API (GetValuePtrByPropertyNameInChain) because we don't know if the property always exists.
    //                            If it does exist, we can retrieve the offset for the property, and the offset should never change at runtime so we can cache it.
    //                         2. Bools are more expensive because bitfields exist and they need extra processing, and properties cannot safely be cached.
    //                            We need the property to call 'GetPropertyValueInContainer' on so that we can get the bool representation of the bitfield for that property,
    //                            so we can't just cache the offset like we do with other properties.
    //                            This means we have to look up the property every single time.

    template<typename Type>
    static constexpr auto Get(const wchar_t* Name, auto* This)
    {
        if constexpr (std::is_same_v<std::remove_pointer_t<std::remove_reference_t<Type>>, bool>)
        {
            const auto Property = CastField<FBoolProperty>(This->GetPropertyByNameInChain(Name));
            if (!Property)
            {
                Output::send(STR("ERROR: BoolProperty '{}' not found in class '{}'\n"), Name, This->GetClassPrivate()->GetFullName());
                std::abort();
            }
            return Property->GetPropertyValueInContainer(This);
        }
        else
        {
            static const auto Offset = [&]() -> int32 {
                const auto Property = This->GetPropertyByNameInChain(Name);
                if (!Property)
                {
                    Output::send(STR("ERROR: Property '{}' not found in class '{}'\n"), Name, This->GetClassPrivate()->GetFullName());
                    std::abort();
                }
                return Property->GetOffset_Internal();
            }();
            auto ValuePtr = std::bit_cast<Type*>(std::bit_cast<uint8*>(This) + Offset);
            return *ValuePtr;
        }
    }

    template<typename Type>
    static constexpr auto& GetRef(const wchar_t* Name, auto* This)
    {
        static const auto Offset = [&]() -> int32 {
            const auto Property = This->GetPropertyByNameInChain(Name);
            if (!Property)
            {
                Output::send(STR("ERROR: Property '{}' not found in class '{}'\n"), Name, This->GetClassPrivate()->GetFullName());
                std::abort();
            }
            return Property->GetOffset_Internal();
        }();
        auto ValuePtr = std::bit_cast<Type*>(std::bit_cast<uint8*>(This) + Offset);
        return *ValuePtr;
    }

    template<typename Type>
    static constexpr auto Set(const wchar_t* Name, auto* This, auto NewValue)
    {
    if constexpr (std::is_same_v<std::remove_pointer_t<std::remove_reference_t<Type>>, bool>)
    {
        const auto Property = CastField<FBoolProperty>(This->GetPropertyByNameInChain(Name));
        if (!Property)
        {
            Output::send(STR("ERROR: BoolProperty '{}' not found in class '{}'\n"), Name, This->GetClassPrivate()->GetFullName());
            std::abort();
        }
        Property->SetPropertyValueInContainer(This, NewValue);
    }
    else
    {
        static const auto Offset = [&]() -> int32 {
            const auto Property = This->GetPropertyByNameInChain(Name);
            if (!Property)
            {
                Output::send(STR("ERROR: Property '{}' not found in class '{}'\n"), Name, This->GetClassPrivate()->GetFullName());
                std::abort();
            }
            return Property->GetOffset_Internal();
        }();
        *std::bit_cast<Type*>(std::bit_cast<uint8*>(This) + Offset) = NewValue; \
    }
    }
}
