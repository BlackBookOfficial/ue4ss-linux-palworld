#include <stdexcept>
#include <Unreal/Hooks/GlobalCallbackId.hpp>
#include <DynamicOutput/Output.hpp>

namespace RC::Unreal::Hook
{
    FGlobalCallbackIdDecoder::FGlobalCallbackIdDecoder(const GlobalCallbackId InId): Id(InId)
    {
        if (!InId) throw std::runtime_error("Can't create a FGlobalCallbackIdDecoderImpl with an invalid (ERROR_ID) GlobalCallbackId!");
        const auto EnumValue = static_cast<Internal::EDetourTarget>(Id & Internal::DETOUR_MASK);
        DetourOwnerName = EnumToString(EnumValue);
        if(DetourOwnerName.empty()) {
            Output::send<LogLevel::Error>(STR("[FGlobalCallbackIdDecoder] GetDetourOwnerName() failed with owner value = {:#X}, Id = {:#X}\n"),
                                          Id & Internal::DETOUR_MASK, Id);
            DetourOwnerName = STR("UnknownOwner");
        }
    }

    bool FGlobalCallbackIdDecoder::IsOnceCallback() const
    { return Id & static_cast<uint64_t>(Internal::EGlobalCallbackAttributeFlags::Once); }

    bool FGlobalCallbackIdDecoder::IsPreHook() const
    { return Id & static_cast<uint64_t>(Internal::EGlobalCallbackAttributeFlags::Prehook); }

    bool FGlobalCallbackIdDecoder::IsReadOnly() const
    { return Id & static_cast<uint64_t>(Internal::EGlobalCallbackAttributeFlags::Readonly); }

    uint64_t FGlobalCallbackIdDecoder::GetDetourOwnerValue() const
    { return Id & Internal::DETOUR_MASK; }

    GlobalCallbackId FGlobalCallbackIdDecoder::GetId() const
    { return Id; }

    StringViewType FGlobalCallbackIdDecoder::GetDetourOwnerName() const
    { return DetourOwnerName; }
}