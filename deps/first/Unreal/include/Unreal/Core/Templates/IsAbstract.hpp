// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

namespace RC::Unreal
{
    /**
    * Traits class which tests if a type is abstract.
    */
    template <typename T>
    struct TIsAbstract
    {
        enum { Value = __is_abstract(T) };
    };
}