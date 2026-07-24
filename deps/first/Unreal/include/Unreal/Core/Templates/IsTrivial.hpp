// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/Templates/AndOrNot.hpp"
#include "Unreal/Core/Templates/IsTriviallyDestructible.hpp"
#include "Unreal/Core/Templates/IsTriviallyCopyConstructible.hpp"
#include "Unreal/Core/Templates/IsTriviallyCopyAssignable.hpp"

namespace RC::Unreal
{
    /**
     * Traits class which tests if a type is trivial.
     */
    template <typename T>
    struct TIsTrivial
    {
        enum { Value = TAnd<TIsTriviallyDestructible<T>, TIsTriviallyCopyConstructible<T>, TIsTriviallyCopyAssignable<T>>::Value };
    };
}