// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <type_traits>

namespace RC::Unreal
{
    namespace UE
    {
        /**
         * Concept which describes a floating point type.  We use this instead of std::floating_point because <concepts> isn't a well supported header yet.
         */
        template <typename T>
        concept CFloatingPoint = std::is_floating_point_v<T>;
    }
}