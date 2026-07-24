#include <Unreal/ITextData.hpp>
#include <Unreal/VersionedContainer/Container.hpp>

namespace RC::Unreal
{
    std::unordered_map<File::StringType, uint32_t> ITextData::VTableLayoutMap;

    auto ITextData::GetDisplayString() const -> const FString&
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(ITextData, GetDisplayString, const FString&)
    }
}