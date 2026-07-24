#pragma once

/*=============================================================================
    FSetProperty.hpp: Forwarding include for backward compatibility

    FSetProperty has been consolidated into UnrealType.hpp to match
    Unreal Engine's structure. FScriptSetHelper remains in this file.

    To disable deprecation warnings, define:
    RC_UNREAL_DISABLE_PROPERTY_DEPRECATION_WARNINGS
=============================================================================*/

#ifndef RC_UNREAL_DISABLE_PROPERTY_DEPRECATION_WARNINGS
#pragma message("Property/FSetProperty.hpp is now a forwarding include. Please use <Unreal/CoreUObject/UObject/UnrealType.hpp> instead.")
#endif

#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
