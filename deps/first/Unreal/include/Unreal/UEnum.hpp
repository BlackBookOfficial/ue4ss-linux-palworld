#pragma once

/*=============================================================================
    UEnum.hpp: Forwarding include for backward compatibility

    UEnum and related class types have been consolidated into
    CoreUObject/UObject/Class.hpp to match Unreal Engine's structure.

    To disable deprecation warnings, define:
    RC_UNREAL_DISABLE_CLASS_DEPRECATION_WARNINGS
=============================================================================*/

#ifndef RC_UNREAL_DISABLE_CLASS_DEPRECATION_WARNINGS
#pragma message("UEnum.hpp is now a forwarding include. Please use <Unreal/CoreUObject/UObject/Class.hpp> instead.")
#endif

#include <Unreal/CoreUObject/UObject/Class.hpp>
