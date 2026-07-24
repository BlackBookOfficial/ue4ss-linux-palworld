// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include <type_traits>

namespace RC::Unreal
{
    /**
    * Traits class which tests if a type has a trivial copy assignment operator.
    */
    template <typename T>
    struct TIsTriviallyCopyAssignable
    {
      enum { Value = std::is_trivially_copy_assignable_v<T> };
    };
}