#pragma once

#include <Unreal/UObject.hpp>

namespace RC::Unreal
{
    class RC_UE_API UKismetTextLibrary : public UObject
    {
    public:
        static FString Conv_TextToString(const FText&);
        static FText Conv_StringToText(const FString&);
    };
}


