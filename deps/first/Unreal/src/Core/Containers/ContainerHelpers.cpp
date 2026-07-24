// Copyright Epic Games, Inc. All Rights Reserved.

#include "Containers/ContainerHelpers.hpp"
#include <DynamicOutput/Output.hpp>


namespace RC::Unreal
{
    void UE::Core::Private::OnInvalidArrayNum(unsigned long long NewNum)
    {
        Output::send<LogLevel::Error>(STR("Trying to resize TArray to an invalid size of %llu"), NewNum);
        for (;;);
    }

    void UE::Core::Private::OnInvalidSetNum(unsigned long long NewNum)
    {
        Output::send<LogLevel::LogLevel::Error>(STR("Trying to resize TSet to an invalid size of %llu"), NewNum);
        for (;;);
    }
}

