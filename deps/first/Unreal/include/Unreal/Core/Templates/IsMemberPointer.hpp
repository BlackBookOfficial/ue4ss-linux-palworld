// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/CoreTypes.hpp>
#include <Unreal/Core/Templates/IsPointer.hpp>

namespace RC::Unreal {
    /**
     * Traits class which tests if a type is a pointer to member (data member or member function).
     */
    template <typename T>
    struct TIsMemberPointer
    {
        enum { Value = false };
    };

    template <typename T, typename U> struct TIsMemberPointer<T U::*> { enum { Value = true }; };

    template <typename T> struct TIsMemberPointer<const          T> { enum { Value = TIsPointer<T>::Value }; };
    template <typename T> struct TIsMemberPointer<      volatile T> { enum { Value = TIsPointer<T>::Value }; };
    template <typename T> struct TIsMemberPointer<const volatile T> { enum { Value = TIsPointer<T>::Value }; };
}