// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

namespace RC::Unreal
{
    template <typename T>
    struct TIsEnum
    {
        enum { Value = __is_enum(T) };
    };
}