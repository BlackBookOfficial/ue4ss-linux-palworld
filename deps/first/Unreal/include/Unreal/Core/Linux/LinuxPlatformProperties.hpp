// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreTypes.hpp"
#include "GenericPlatform/GenericPlatformProperties.hpp"

namespace RC::Unreal {
    template<bool HAS_EDITOR_DATA, bool IS_DEDICATED_SERVER, bool IS_CLIENT_ONLY>
    struct FLinuxPlatformProperties
        : public FGenericPlatformProperties
    {
        static FORCEINLINE bool HasEditorOnlyData() { return HAS_EDITOR_DATA; }
        static FORCEINLINE const char* IniPlatformName() { return "Linux"; }
        static FORCEINLINE const TCHAR* GetRuntimeSettingsClassName() { return TEXT("/Script/LinuxTargetPlatform.LinuxTargetSettings"); }
        static FORCEINLINE const char* GetPhysicsFormat() { return "PhysXPC"; }
        static FORCEINLINE bool IsGameOnly() { return UE_GAME; }
        static FORCEINLINE bool IsServerOnly() { return IS_DEDICATED_SERVER; }
        static FORCEINLINE bool IsClientOnly() { return IS_CLIENT_ONLY; }
        static FORCEINLINE const char* PlatformName()
        {
            if (IS_DEDICATED_SERVER) return "LinuxServer";
            if (HAS_EDITOR_DATA) return "Linux";
            if (IS_CLIENT_ONLY) return "LinuxClient";
            return "LinuxNoEditor";
        }
        static FORCEINLINE bool RequiresCookedData() { return !HAS_EDITOR_DATA; }
        static FORCEINLINE bool HasSecurePackageFormat() { return IS_DEDICATED_SERVER; }
        static FORCEINLINE bool SupportsAudioStreaming() { return !IsServerOnly(); }
        static FORCEINLINE bool SupportsMeshLODStreaming() { return !IsServerOnly() && !HasEditorOnlyData(); }
        static FORCEINLINE bool SupportsGrayscaleSRGB() { return false; }
        static FORCEINLINE bool SupportsMultipleGameInstances() { return true; }
        static FORCEINLINE bool SupportsTessellation() { return true; }
        static FORCEINLINE bool SupportsWindowedMode() { return true; }
        static FORCEINLINE bool HasFixedResolution() { return false; }
        static FORCEINLINE bool SupportsQuit() { return true; }
        static FORCEINLINE float GetVariantPriority()
        {
            if (IS_DEDICATED_SERVER) return 0.0f;
            if (HAS_EDITOR_DATA) return 0.0f;
            if (IS_CLIENT_ONLY) return 0.0f;
            return 1.0f;
        }
        static FORCEINLINE bool SupportsVirtualTextureStreaming() { return true; }
    };

    #ifdef PROPERTY_HEADER_SHOULD_DEFINE_TYPE
    typedef FLinuxPlatformProperties<WITH_EDITORONLY_DATA, UE_SERVER, !WITH_SERVER_CODE> FPlatformProperties;
    #endif
}
