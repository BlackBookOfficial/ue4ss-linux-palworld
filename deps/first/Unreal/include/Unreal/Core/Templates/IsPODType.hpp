// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


namespace RC::Unreal
{
    /**
     * Traits class which tests if a type is POD.
     */
    template <typename T>
    struct TIsPODType 
    { 
        enum { Value = __is_pod(T) };
    };
}