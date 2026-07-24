#pragma once

#include <unordered_map>

#include <File/File.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/FString.hpp>

namespace RC::Unreal
{
    class RC_UE_API ITextData
    {
    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
        auto GetDisplayString() const -> const FString&;

    private:
        void* vtable;
    };
}

