// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <type_traits>

namespace RC::Unreal
{
    namespace UE
    {
        /**
         * Concept which describes an integral type.  We use this instead of std::integral because <concepts> isn't a well supported header yet.
         */
        template <typename T>
        concept CIntegral = std::is_integral_v<T>;
    }
}