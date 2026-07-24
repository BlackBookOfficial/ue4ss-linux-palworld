#include <Unreal/UEngine.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UEngine);

    Function<UEngine::LoadMapSignature> UEngine::LoadMapInternal;
    Function<UEngine::TickSignature> UEngine::TickInternal;
    std::unordered_map<File::StringType, uint32_t> UEngine::VTableLayoutMap;
}