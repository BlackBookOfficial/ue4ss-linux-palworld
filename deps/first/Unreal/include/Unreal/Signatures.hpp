#pragma once

#include <string>
#include <unordered_set>

#include <Unreal/Common.hpp>
#include <Unreal/UnrealInitializer.hpp>

#include <String/StringType.hpp>

namespace RC::Unreal::Signatures
{
    enum ScanStatus
    {
        Failed,
        Succeeded,
    };

    struct RC_UE_API ScanError
    {
        std::string Message;
        bool bIsFatal{true};

        ScanError(std::string_view Error, bool IsFatal = true) : Message(Error), bIsFatal(IsFatal) {}
    };

    struct RC_UE_API ScanResult
    {
        std::vector<StringType> SuccessMessage{};
        std::unordered_set<StringType> InfoMessages{};
        std::vector<ScanError> Errors;
        ScanStatus Status{ScanStatus::Failed};
    };

    auto RC_UE_API ScanForGameFunctionsAndData(const UnrealInitializer::Config&) -> ScanResult;
    auto RC_UE_API ScanForGUObjectArray(const UnrealInitializer::Config&) -> ScanResult;

    auto RC_UE_API ScanForGameFunctionsAndDataImpl(const UnrealInitializer::Config&) -> ScanResult;
    auto RC_UE_API ScanForGUObjectArrayImpl(const UnrealInitializer::Config&) -> ScanResult;
}



