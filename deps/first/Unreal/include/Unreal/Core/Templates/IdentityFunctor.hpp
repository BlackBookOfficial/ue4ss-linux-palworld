// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/HAL/Platform.hpp>

namespace RC::Unreal {

    /**
     * A functor which returns whatever is passed to it.  Mainly used for generic composition.
     */
    struct FIdentityFunctor
    {
        template <typename T>
        FORCEINLINE T&& operator()(T&& Val) const
        {
            return (T&&)Val;
        }
    };

}