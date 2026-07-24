// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <cstdint>

// WARNING: Any change in these constants will require a re-patch and re-build of LLVM!

namespace RC::Unreal
{
    #ifdef __cplusplus
    extern "C"
    {
    #endif

    // An enumerator of transactional memory validation levels.
    // Memory validation is used to detect modification by open-code to memory that was written by a
    // transaction. In this situation, aborting the transaction can corrupt memory as the undo will
    // overwrite the writes made in the open-code.
    typedef enum
    {
        // Use the default memory validation level.
        autortfm_memory_validation_level_default,

        // Disable memory validation.
        autortfm_memory_validation_level_disabled,

        // Enable memory validation. Memory validation failures are treated as warnings.
        autortfm_memory_validation_level_warn,

        // Enable memory validation. Memory validation are treated as fatal.
        autortfm_memory_validation_level_error,
    } autortfm_memory_validation_level;

    #ifdef __cplusplus
    }
    #endif

    #ifdef __cplusplus
    namespace AutoRTFM::Constants
    {
        inline constexpr uint32_t Major = 0;
        inline constexpr uint32_t Minor = 2;
        inline constexpr uint32_t Patch = 0;

        // The Magic Prefix constant - an arbitrarily chosen address prefix, shared
        // between the AutoRTFM compiler and runtime.
        // We add this prefix value to open function pointer addresses in our custom 
        // LLVM pass. At runtime, if we detect the Magic Prefix in the the top 16 bits
        // of an open function pointer address, we assume that we can find a closed
        // variant pointer residing 8 bytes before the function address.
        inline constexpr uint64_t MagicPrefix = 0xa273'0000'0000'0000;

    } // namespace AutoRTFM::Constants
    #endif
}