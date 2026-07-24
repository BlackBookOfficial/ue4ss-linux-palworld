#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/Core/HAL/Platform.hpp>

namespace RC::Unreal
{
    //URL structure.
#if !LESSEQUAL421
    #pragma pack(push, 1)
#endif
    struct RC_UE_API FURL
    {
        // Protocol, i.e. "unreal" or "http".
        FString Protocol;

        // Optional hostname, i.e. "204.157.115.40" or "unreal.epicgames.com", blank if local.
        FString Host;

        // Optional host port.
        int32 Port;
        
#if !LESSEQUAL421
        int32 Valid;
#endif

        // Map name, i.e. "SkyCity", default is "Entry".
        FString Map;

        // Optional place to download Map if client does not possess it
        FString RedirectURL;

        // Options.
        TArray<FString> Op;

        // Portal to enter through, default is "".
        FString Portal;

#if !LESSEQUAL421
    };
    #pragma pack(pop)
#else
        int32 Valid;
};
#endif

}
