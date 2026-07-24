// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/HAL/PreprocessorHelpers.hpp>

// When passed to pragma message will result in clickable warning in VS
#define WARNING_LOCATION(Line) __FILE__ "(" PREPROCESSOR_TO_STRING(Line) ")"

namespace RC::Unreal
{
    #if UE_BUILD_DEBUG
            #define FORCEINLINE_DEBUGGABLE FORCEINLINE_DEBUGGABLE_ACTUAL
    #else
            #define FORCEINLINE_DEBUGGABLE FORCEINLINE
    #endif

    // Code analysis features
    #ifndef USING_CODE_ANALYSIS
            #define USING_CODE_ANALYSIS 0
    #endif

    #if USING_CODE_ANALYSIS
            #if !defined( CA_IN ) || !defined( CA_OUT ) || !defined( CA_READ_ONLY ) || !defined( CA_WRITE_ONLY ) || !defined( CA_VALID_POINTER ) || !defined( CA_CHECK_RETVAL ) || !defined( CA_NO_RETURN ) || !defined( CA_SUPPRESS ) || !defined( CA_ASSUME )
                    #error Code analysis macros are not configured correctly for this platform
            #endif
    #else
            // Just to be safe, define all of the code analysis macros to empty macros
            #define CA_IN 
            #define CA_OUT
            #define CA_READ_ONLY
            #define CA_WRITE_ONLY
            #define CA_VALID_POINTER
            #define CA_CHECK_RETVAL
            #define CA_NO_RETURN
            #define CA_SUPPRESS( WarningNumber )
            #define CA_ASSUME( Expr )
            #define CA_CONSTANT_IF(Condition) if (Condition)
    #endif

    #ifndef USING_THREAD_SANITISER
        #define USING_THREAD_SANITISER 0
    #endif

    #if USING_THREAD_SANITISER
        #if !defined( TSAN_SAFE ) || !defined( TSAN_BEFORE ) || !defined( TSAN_AFTER ) || !defined( TSAN_ATOMIC )
            #error Thread Sanitiser macros are not configured correctly for this platform
        #endif
    #else
        // Define TSAN macros to empty when not enabled
        #define TSAN_SAFE
        #define TSAN_BEFORE(Addr)
        #define TSAN_AFTER(Addr)
        #define TSAN_ATOMIC(Type) Type
    #endif

    enum {INDEX_NONE    = -1                };
    enum {UNICODE_BOM   = 0xfeff            };

    enum EForceInit 
    {
        ForceInit,
        ForceInitToZero
    };
    enum ENoInit {NoInit};
    enum EInPlace {InPlace};

    // Push and pop macro definitions
    #ifdef __clang__
            #define PUSH_MACRO(name) _Pragma(PREPROCESSOR_TO_STRING(push_macro(PREPROCESSOR_TO_STRING(name))))
            #define POP_MACRO(name) _Pragma(PREPROCESSOR_TO_STRING(pop_macro(PREPROCESSOR_TO_STRING(name))))
    #else
            #define PUSH_MACRO(name) __pragma(push_macro(PREPROCESSOR_TO_STRING(name)))
            #define POP_MACRO(name) __pragma(pop_macro(PREPROCESSOR_TO_STRING(name)))
    #endif

    /**
     * Macro for marking up code, functions and types deprecated by Unreal Engine in a particular version.
     *
     * This should be used as syntactic replacement for the [[deprecated]] attribute
     * and provides a UE version number.
     *
     * Features that are marked as deprecated are scheduled to be removed from UE's code base
     * in a future release. If you are using a deprecated feature in your code, you should
     * ensure that it still works in all Unreal Engine versions of interest.
     *
     *
     * @param VERSION The release number in which the feature was marked deprecated.
     * @param MESSAGE A message containing upgrade notes.
     */
    #if defined (__INTELLISENSE__)
    #define UE_DEPRECATED(Version, Message)
    #else
    #define UE_DEPRECATED(Version, Message) [[deprecated(Message " Unreal Engine has deprecated this function. Please ensure this code works in all versions of interest.")]]
    #endif

    template <bool bIsDeprecated>
    struct TStaticDeprecateExpression
    {
    };

    /**
     * Can be used in the same contexts as static_assert but gives a warning rather than an error, and 'fails' if the expression is true rather than false.
     */
    #define UE_STATIC_DEPRECATE(Version, bExpression, Message) \
        struct PREPROCESSOR_JOIN(FDeprecationMsg_, __LINE__) { \
            [[deprecated(Message " Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.")]] \
            static constexpr int condition(TStaticDeprecateExpression<true>) { return 1; } \
            static constexpr int condition(TStaticDeprecateExpression<false>) { return 1; } \
        }; \
        enum class PREPROCESSOR_JOIN(EDeprecationMsg_, __LINE__) { Value = PREPROCESSOR_JOIN(FDeprecationMsg_, __LINE__)::condition(TStaticDeprecateExpression<!!(bExpression)>()) }

    // These defines are used to mark a difference between two pointers as expected to fit into the specified range
    // while still leaving something searchable if the surrounding code is updated to work with a 64 bit count/range
    // in the future
    #define UE_PTRDIFF_TO_INT32(argument) static_cast<int32>(argument)
    #define UE_PTRDIFF_TO_UINT32(argument) static_cast<uint32>(argument)


      /**
      * Makes a type non-copyable and non-movable by deleting copy/move constructors and assignment/move operators.
      * The macro should be placed in the public section of the type for better compiler diagnostic messages.
      * Example usage:
      *
      *    class FMyClassName
      *    {
      *    public:
      *        UE_NONCOPYABLE(FMyClassName)
      *        FMyClassName() = default;
      *    };
      */
      #define UE_NONCOPYABLE(TypeName) \
        TypeName(TypeName&&) = delete; \
        TypeName(const TypeName&) = delete; \
        TypeName& operator=(const TypeName&) = delete; \
        TypeName& operator=(TypeName&&) = delete;
}
