#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/UObject.hpp>

namespace RC::Unreal
{
    class UEnum;

    class RC_UE_API UKismetNodeHelperLibrary : public UObject
    {
    public:
        static StringType GetEnumeratorUserFriendlyName(const UEnum* Enum, uint8 EnumeratorValue);
    };
}


