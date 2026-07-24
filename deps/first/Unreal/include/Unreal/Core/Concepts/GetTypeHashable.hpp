// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/CoreTypes.hpp>
#include <Unreal/Core/Templates/TypeHash.hpp>

namespace RC::Unreal
{
    
    /**
     * Describes a type with a GetTypeHash overload.
     */
    struct CGetTypeHashable {
        template <typename T>
        auto Requires(uint32& Result, const T& Val) -> decltype(
            Result = GetTypeHash(Val)
        );
    };
    
}