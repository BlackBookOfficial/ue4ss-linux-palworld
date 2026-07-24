// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#if defined(__clang__)
    #include "Clang/ClangPlatformCompilerPreSetup.hpp"
#else
    // GCC compiler pre-setup

    #ifndef DISABLE_DEPRECATION
        #define DEPRECATED(VERSION, MESSAGE) DEPRECATED_MACRO(4.22, "The DEPRECATED macro has been deprecated in favor of UE_DEPRECATED().") __attribute__((deprecated(MESSAGE " Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.")))

        #define PRAGMA_DISABLE_DEPRECATION_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")

        #define PRAGMA_ENABLE_DEPRECATION_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif // DISABLE_DEPRECATION

    #ifndef PRAGMA_DISABLE_OVERLOADED_VIRTUAL_WARNINGS
        #define PRAGMA_DISABLE_OVERLOADED_VIRTUAL_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Woverloaded-virtual\"")
    #endif

    #ifndef PRAGMA_ENABLE_OVERLOADED_VIRTUAL_WARNINGS
        #define PRAGMA_ENABLE_OVERLOADED_VIRTUAL_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_MISSING_BRACES_WARNINGS
        #define PRAGMA_DISABLE_MISSING_BRACES_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wmissing-braces\"")
    #endif

    #ifndef PRAGMA_ENABLE_MISSING_BRACES_WARNINGS
        #define PRAGMA_ENABLE_MISSING_BRACES_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS
        #define PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wshadow\"")
    #endif

    #ifndef PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS
        #define PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_UNSAFE_TYPECAST_WARNINGS
        #define PRAGMA_DISABLE_UNSAFE_TYPECAST_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wfloat-conversion\"") \
            _Pragma("GCC diagnostic ignored \"-Wnarrowing\"")
    #endif

    #ifndef PRAGMA_ENABLE_UNSAFE_TYPECAST_WARNINGS
        #define PRAGMA_ENABLE_UNSAFE_TYPECAST_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS
        #define PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wundef\"")
    #endif

    #ifndef PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS
        #define PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS
        #define PRAGMA_DISABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wdelete-non-virtual-dtor\"")
    #endif

    #ifndef PRAGMA_ENABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS
        #define PRAGMA_ENABLE_MISSING_VIRTUAL_DESTRUCTOR_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_REORDER_WARNINGS
        #define PRAGMA_DISABLE_REORDER_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wreorder\"")
    #endif

    #ifndef PRAGMA_ENABLE_REORDER_WARNINGS
        #define PRAGMA_ENABLE_REORDER_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_REGISTER_WARNINGS
        #define PRAGMA_DISABLE_REGISTER_WARNINGS \
            _Pragma("GCC diagnostic push") \
            _Pragma("GCC diagnostic ignored \"-Wregister\"")
    #endif

    #ifndef PRAGMA_ENABLE_REGISTER_WARNINGS
        #define PRAGMA_ENABLE_REGISTER_WARNINGS \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_DISABLE_UNINITIALIZED_CONST_REFERENCE_WARNINGS
        #define PRAGMA_DISABLE_UNINITIALIZED_CONST_REFERENCE_WARNINGS
    #endif

    #ifndef PRAGMA_ENABLE_UNINITIALIZED_CONST_REFERENCE_WARNINGS
        #define PRAGMA_ENABLE_UNINITIALIZED_CONST_REFERENCE_WARNINGS
    #endif

    #ifndef PRAGMA_POP
        #define PRAGMA_POP \
            _Pragma("GCC diagnostic pop")
    #endif

    #ifndef PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
        #define PRAGMA_PUSH_PLATFORM_DEFAULT_PACKING
    #endif

    #ifndef PRAGMA_POP_PLATFORM_DEFAULT_PACKING
        #define PRAGMA_POP_PLATFORM_DEFAULT_PACKING
    #endif

    #ifndef EMIT_CUSTOM_WARNING_AT_LINE
        #define EMIT_CUSTOM_WARNING_AT_LINE(Line, Warning) \
            _Pragma(PREPROCESSOR_TO_STRING(message(Warning)))
    #endif
#endif // defined(__clang__)

#ifndef THIRD_PARTY_INCLUDES_START
    #define THIRD_PARTY_INCLUDES_START \
        PRAGMA_DISABLE_REORDER_WARNINGS \
        PRAGMA_DISABLE_SHADOW_VARIABLE_WARNINGS \
        PRAGMA_DISABLE_UNDEFINED_IDENTIFIER_WARNINGS \
        PRAGMA_DISABLE_DEPRECATION_WARNINGS \
        PRAGMA_DISABLE_OVERLOADED_VIRTUAL_WARNINGS \
        PRAGMA_DISABLE_MISSING_BRACES_WARNINGS \
        PRAGMA_DISABLE_UNINITIALIZED_CONST_REFERENCE_WARNINGS
#endif

#ifndef THIRD_PARTY_INCLUDES_END
    #define THIRD_PARTY_INCLUDES_END \
        PRAGMA_ENABLE_UNINITIALIZED_CONST_REFERENCE_WARNINGS \
        PRAGMA_DISABLE_MISSING_BRACES_WARNINGS \
        PRAGMA_DISABLE_OVERLOADED_VIRTUAL_WARNINGS \
        PRAGMA_ENABLE_DEPRECATION_WARNINGS \
        PRAGMA_ENABLE_UNDEFINED_IDENTIFIER_WARNINGS \
        PRAGMA_ENABLE_SHADOW_VARIABLE_WARNINGS \
        PRAGMA_ENABLE_REORDER_WARNINGS
#endif
