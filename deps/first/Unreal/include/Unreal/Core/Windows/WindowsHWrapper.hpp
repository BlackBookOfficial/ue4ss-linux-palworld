// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

// #TODO: redirect to platform-agnostic version for the time being. Eventually this will become an error
#include "Unreal/Core/HAL/Platform.hpp"
#if !PLATFORM_WINDOWS
    #include "Unreal/Core/Microsoft/WindowsHWrapper.hpp"
#else

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/HAL/PlatformMemory.hpp"
#include "Unreal/Core/Windows/PreWindowsApi.hpp"
#ifndef STRICT
#define STRICT
#endif
#include "Unreal/Core/Windows/MinWindows.hpp"
#include "Unreal/Core/Windows/PostWindowsApi.hpp"

#endif //PLATFORM_*
