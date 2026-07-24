// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreTypes.hpp"

namespace RC::Unreal
{
    // Specifies whether or not a container's removal operation should attempt to auto-shrink the container's reserved memory usage
    enum class EAllowShrinking : uint8
    {
        No,
        Yes,

        Default = Yes
    };
}

#define UE_ALLOWSHRINKING_BOOL_DEPRECATED(FunctionName) UE_DEPRECATED(5.6, FunctionName " with a boolean bAllowShrinking has been deprecated - please use the EAllowShrinking enum instead")
