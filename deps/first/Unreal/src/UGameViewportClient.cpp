#include <Unreal/UGameViewportClient.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UGameViewportClient);

    Function<UGameViewportClient::TickSignature> UGameViewportClient::TickInternal;
}
