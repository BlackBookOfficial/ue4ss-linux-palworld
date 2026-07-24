#pragma once

/*=============================================================================
    FInterfaceProperty.hpp: Forwarding include for backward compatibility

    FInterfaceProperty has been consolidated into UnrealType.hpp to match
    Unreal Engine's structure.

    To disable deprecation warnings, define:
    RC_UNREAL_DISABLE_PROPERTY_DEPRECATION_WARNINGS
=============================================================================*/

#ifndef RC_UNREAL_DISABLE_PROPERTY_DEPRECATION_WARNINGS
#pragma message("Property/FInterfaceProperty.hpp is now a forwarding include. Please use <Unreal/CoreUObject/UObject/UnrealType.hpp> instead.")
#endif

#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
