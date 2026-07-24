// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Unreal/Core/CoreTypes.hpp"
#include "Unreal/Core/Containers/ContainersFwd.hpp"
#include "Unreal/Core/Math/MathFwd.hpp"
#include "Unreal/Core/UObject/UObjectHierarchyFwd.hpp"

namespace RC::Unreal
{
  // Basic types
  class FName;
  class FExec;
  class FArchive;
  class FOutputDevice;
  class FFeedbackContext;
  struct FDateTime;
  struct FGuid;

  // Math - See Math/MathFwd.h

  // Misc
  /*struct FResourceSizeEx;*/
  class IConsoleVariable;
  class FRunnableThread;
  class FEvent;
  class IPlatformFile;
  class FMalloc;
  class IFileHandle;
  class FAutomationTestBase;
  struct FGenericMemoryStats;
  class FSHAHash;
  class FScriptArray;
  class FThreadSafeCounter;
  enum class EModuleChangeReason;
  struct FManifestContext;
  class IConsoleObject;
  class FConfigFile;
  class FConfigSection;

  // Text
  class FText;
  class FTextFilterString;
  enum class ETextFilterTextComparisonMode : uint8;
  enum class ETextFilterComparisonOperation : uint8;
}