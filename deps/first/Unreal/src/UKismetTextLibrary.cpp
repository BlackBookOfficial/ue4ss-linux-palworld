#include <Unreal/UKismetTextLibrary.hpp>
#include <Unreal/BPMacros.hpp>
#include <Unreal/FString.hpp>

namespace RC::Unreal
{
    FString UKismetTextLibrary::Conv_TextToString(const FText& InText)
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetTextLibrary:Conv_TextToString")
        UE_SET_STATIC_SELF("/Script/Engine.Default__KismetTextLibrary")

        UE_COPY_PROPERTY(InText, FText)

        UE_CALL_STATIC_FUNCTION()

        UE_RETURN_PROPERTY(FString)
    }

    FText UKismetTextLibrary::Conv_StringToText(const FString& InString)
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Engine.KismetTextLibrary:Conv_StringToText")
        UE_SET_STATIC_SELF("/Script/Engine.Default__KismetTextLibrary")

        UE_COPY_PROPERTY(InString, FString)

        UE_CALL_STATIC_FUNCTION()

        UE_RETURN_PROPERTY(FText)
    }
}
