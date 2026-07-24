#include <Unreal/Hooks/CallbackIterationData.hpp>
#include <DynamicOutput/Output.hpp>
#include <Unreal/Hooks/Internal/Metadata.hpp>

#include <concepts>

#pragma push_macro("ensure")
#undef ensure

namespace RC::Unreal::Hook
{
    StringType GetOwnerModNameFromMetadata(Internal::FCallbackMetadata* Metadata)
    {
        return Metadata->OwnerModName;
    }

    StringType GetHookNameFromMetadata(Internal::FCallbackMetadata* Metadata)
    {
        return Metadata->HookName;
    }
}

#pragma pop_macro("ensure")
