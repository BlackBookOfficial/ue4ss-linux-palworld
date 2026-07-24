// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <Unreal/Core/HAL/Platform.hpp>
#include "Unreal/Core/HAL/PlatformMisc.hpp"
#include "Unreal/Core/Templates/AndOrNot.hpp"
#include "Unreal/Core/Templates/EnableIf.hpp"
#include "Unreal/Core/Templates/IsArrayOrRefOfType.hpp"
#include "Unreal/Core/Templates/IsValidVariadicFunctionArg.hpp"

namespace RC::Unreal
{
#ifndef UE_DEBUG_SECTION
#if (DO_CHECK || DO_GUARD_SLOW || DO_ENSURE) && !PLATFORM_CPU_ARM_FAMILY
    // We'll put all assert implementation code into a separate section in the linked
    // executable. This code should never execute so using a separate section keeps
    // it well off the hot path and hopefully out of the instruction cache. It also
    // facilitates reasoning about the makeup of a compiled/linked binary.
#define UE_DEBUG_SECTION PLATFORM_CODE_SECTION(".uedbg")
#else
    // On ARM we can't do this because the executable will require jumps larger
    // than the branch instruction can handle. Clang will only generate
    // the trampolines in the .text segment of the binary. If the uedbg segment
    // is present it will generate code that it cannot link.
#define UE_DEBUG_SECTION
#endif // DO_CHECK || DO_GUARD_SLOW
#endif
#if !DO_CHECK
    #ifndef checkCode
        #define checkCode( Code )        do { Code; } while ( false );
    #endif
    #ifndef verify
        #define verify(expr)
    #endif
    #ifndef check
        #define check(expr)                
    #endif

        // Technically we could use just the _F version (lambda-based) for asserts
        // both with and without formatted messages. However MSVC emits extra
        // unnecessary instructions when using a lambda; hence the Exec() impl.
        #define UE_CHECK_IMPL(expr) \
            { \
                throw std::runtime_error{}; \
            }
        
        /**
         * verifyf, checkf: Same as verify, check but with printf style additional parameters
         * Read about __VA_ARGS__ (variadic macros) on http://gcc.gnu.org/onlinedocs/gcc-3.4.4/cpp.pdf.
         */
    #ifndef verifyf
        #define verifyf(expr, format,  ...)    
    #endif
    #ifndef checkf
        #define checkf(expr, format,  ...)
    #endif

        #define UE_CHECK_F_IMPL(expr, format, ...) \
            { \
                Output::send<LogLevel::Error>(format); \
            }

        #define UE_VERIFY_F_IMPL(expr, format, ...) \
                { \
                    throw std::runtime_error{fmt::format(format)}; \
                }


        /**
         * Denotes code paths that should never be reached.
         */
    #ifndef checkNoEntry
        #define checkNoEntry()       check(!"Enclosing block should never be called")
    #endif

        /**
         * Denotes code paths that should not be executed more than once.
         */
    #ifndef checkNoReentry
        #define checkNoReentry()     { static bool s_beenHere##__LINE__ = false;                                         \
                                       check( !"Enclosing block was called more than once" || !s_beenHere##__LINE__ );   \
                                       s_beenHere##__LINE__ = true; }
    #endif

        class FRecursionScopeMarker
        {
        public: 
            FRecursionScopeMarker(uint16 &InCounter) : Counter( InCounter ) { ++Counter; }
            ~FRecursionScopeMarker() { --Counter; }
        private:
            uint16& Counter;
        };

        /**
         * Denotes code paths that should never be called recursively.
         */
    #ifndef checkNoRecursion
        #define checkNoRecursion()  static uint16 RecursionCounter##__LINE__ = 0;                                            \
                                    check( !"Enclosing block was entered recursively" || RecursionCounter##__LINE__ == 0 );  \
                                    const FRecursionScopeMarker ScopeMarker##__LINE__( RecursionCounter##__LINE__ )
    #endif

    #ifndef unimplemented
        #define unimplemented()        check(!"Unimplemented function called")
    #endif

    #else
        #define checkCode(...)
        #define check(expr)                    { CA_ASSUME(expr); }
        #define checkf(expr, format, ...)    { CA_ASSUME(expr); }
        #define checkNoEntry()
        #define checkNoReentry()
        #define checkNoRecursion()
        #define verify(expr)                { if(UNLIKELY(!(expr))){ CA_ASSUME(false); } }
        #define verifyf(expr, format, ...)    { if(UNLIKELY(!(expr))){ CA_ASSUME(false); } }
        #define unimplemented()                { CA_ASSUME(false); }
    #endif

    //
    // Check for development only.
    //
    #if DO_GUARD_SLOW
        #define checkSlow(expr)                    check(expr)
        #define checkfSlow(expr, format, ...)    checkf(expr, format, ##__VA_ARGS__)
        #define verifySlow(expr)                check(expr)
    #else
        #define checkSlow(expr)                    { CA_ASSUME(expr); }
        #define checkfSlow(expr, format, ...)    { CA_ASSUME(expr); }
        #define verifySlow(expr)                { if(UNLIKELY(!(expr))) { CA_ASSUME(false); } }
    #endif

    // MSVC (v19.00.24215.1 at time of writing) ignores no-inline attributes on
    // lambdas. This can be worked around by calling the lambda from inside this
    // templated (and correctly non-inlined) function.
    template <typename RetType = void, class InnerType, typename... ArgTypes>
    RetType FORCENOINLINE UE_DEBUG_SECTION DispatchCheckVerify(InnerType&& Inner, ArgTypes const&... Args)
    {
        return Inner(Args...);
    }

    /**
     * ensure() can be used to test for *non-fatal* errors at runtime
     *
     * Rather than crashing, an error report (with a full call stack) will be logged and submitted to the crash server. 
     * This is useful when you want runtime code verification but you're handling the error case anyway.
     *
     * Note: ensure() can be nested within conditionals!
     *
     * Example:
     *
     *        if (ensure(InObject != nullptr))
     *        {
     *            InObject->Modify();
     *        }
     *
     * This code is safe to execute as the pointer dereference is wrapped in a non-nullptr conditional block, but
     * you still want to find out if this ever happens so you can avoid side effects.  Using ensure() here will
     * force a crash report to be generated without crashing the application (and potentially causing editor
     * users to lose unsaved work.)
     *
     * ensure() resolves to just evaluate the expression when DO_CHECK is 0 (typically shipping or test builds).
     *
     * By default a given call site will only print the callstack and submit the 'crash report' the first time an
     * ensure is hit in a session; ensureAlways can be used instead if you want to handle every failure
     */

    #if DO_ENSURE

        #define UE_ENSURE_IMPL(Capture, Always, InExpression, ...) \
            (LIKELY(!!(InExpression)) || (DispatchCheckVerify<bool>([Capture] () FORCENOINLINE UE_DEBUG_SECTION \
            { \
                static bool bExecuted = false; \
                if ((!bExecuted || Always) && FPlatformMisc::IsEnsureAllowed()) \
                { \
                    bExecuted = true; \
                    /* FDebug::OptionallyLogFormattedEnsureMessageReturningFalse(true, #InExpression, __FILE__, __LINE__, ##__VA_ARGS__);*/ \
                    if (!FPlatformMisc::IsDebuggerPresent()) \
                    { \
                        /* FPlatformMisc::PromptForRemoteDebugging(true);*/ \
                        return false; \
                    } \
                    return true; \
                } \
                return false; \
            }) && ([] () { PLATFORM_BREAK(); } (), false)))

        #define ensure(           InExpression                ) UE_ENSURE_IMPL( , false, InExpression, TEXT(""))
        #define ensureMsgf(       InExpression, InFormat, ... ) UE_ENSURE_IMPL(&, false, InExpression, InFormat, ##__VA_ARGS__)
        #define ensureAlways(     InExpression                ) UE_ENSURE_IMPL( , true,  InExpression, TEXT(""))
        #define ensureAlwaysMsgf( InExpression, InFormat, ... ) UE_ENSURE_IMPL(&, true,  InExpression, InFormat, ##__VA_ARGS__)

    #else    // DO_ENSURE

        #define ensure(           InExpression                ) (!!(InExpression))
        #define ensureMsgf(       InExpression, InFormat, ... ) (!!(InExpression))
        #define ensureAlways(     InExpression                ) (!!(InExpression))
        #define ensureAlwaysMsgf( InExpression, InFormat, ... ) (!!(InExpression))
    
#endif // DO_CHECK
}