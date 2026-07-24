#pragma once
#include <Unreal/Hooks/Internal/Common.hpp>
#include <memory>

namespace RC::Unreal::Hook::Internal
{
    // Represents a field that can only be set once.
    // NOT THREAD SAFE ON ITS OWN, but used by thread safe operations.
    template<typename T>
    class TSetOnceField
    {
    public:
        bool TrySetField(T Value)
        {
            if (bIsSet)
            {
                return false;
            }
            Field = std::move(Value);
            bIsSet = true;
            return true;
        }

        const T& GetField() const { return Field; }
        [[nodiscard]] bool IsSet() const { return bIsSet; }

    UE_HOOK_PRIVATE:
        T Field{};
        bool bIsSet = false;
    };
}