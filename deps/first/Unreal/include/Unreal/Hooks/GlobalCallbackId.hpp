#pragma once
#include <String/StringType.hpp>
#include <Unreal/Common.hpp>
#include <Hooks/Internal/Constants.hpp>

namespace RC::Unreal::Hook
{
    // ID type returned from registering a callback that can be used to unregister a callback via UnregisterCallback
    using GlobalCallbackId = uint64_t;

    // Error sentinel for invalid GlobalCallbackIds
    inline static constexpr GlobalCallbackId ERROR_ID = 0;

    // Decodes information from a GlobalCallbackId. Useful for debugging.
    class RC_UE_API FGlobalCallbackIdDecoder
    {
    private:
        StringViewType DetourOwnerName;
        GlobalCallbackId Id;

    public:
        explicit FGlobalCallbackIdDecoder(GlobalCallbackId InId);
        ~FGlobalCallbackIdDecoder() = default;
        [[nodiscard]] bool IsOnceCallback() const;
        [[nodiscard]] bool IsPreHook() const;
        [[nodiscard]] bool IsReadOnly() const;
        [[nodiscard]] uint64_t GetDetourOwnerValue() const;
        [[nodiscard]] GlobalCallbackId GetId() const;
        [[nodiscard]] StringViewType GetDetourOwnerName() const;
    };
}
