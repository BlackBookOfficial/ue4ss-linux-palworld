// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/Templates/Invoke.hpp>
#include <Unreal/Core/Templates/UnrealTemplate.hpp>

namespace RC::Unreal {

    /**
     * Helper class to reverse a predicate.
     * Performs Predicate(B, A)
     */
    template <typename PredicateType>
    class TReversePredicate
    {
        const PredicateType& Predicate;

    public:
        TReversePredicate( const PredicateType& InPredicate )
            : Predicate( InPredicate )
        {
        }

        template <typename T>
        FORCEINLINE bool operator()( T&& A, T&& B ) const
        {
            return Invoke( Predicate, Forward<T>(B), Forward<T>(A) );
        }
    };

}