#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/FStrProperty.hpp>
#include <Unreal/VersionedContainer/Container.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FNumericProperty);
    std::unordered_map<File::StringType, uint32_t> FNumericProperty::VTableLayoutMap;

    auto FNumericProperty::IsFloatingPoint() const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FNumericProperty, IsFloatingPoint, bool)
    }

    auto FNumericProperty::IsInteger() const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FNumericProperty, IsInteger, bool)
    }

    auto FNumericProperty::GetIntPropertyEnum() const -> UEnum*
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FNumericProperty, GetIntPropertyEnum, UEnum*)
    }

    auto FNumericProperty::SetIntPropertyValue(void* Data, uint64 Value) const -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, SetIntPropertyValue_C__Ptr_void__uint64, void, PARAMS(void*, uint64), ARGS(Data, Value))
    }

    auto FNumericProperty::SetIntPropertyValue(void* Data, int64 Value) const -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, SetIntPropertyValue_C__Ptr_void__int64, void, PARAMS(void*, int64), ARGS(Data, Value))
    }

    auto FNumericProperty::SetFloatingPointPropertyValue(void* Data, double Value) -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, SetFloatingPointPropertyValue, void, PARAMS(void*, double), ARGS(Data, Value))
    }

    auto FNumericProperty::SetNumericPropertyValueFromString(void* Data, TCHAR const* Value) -> void
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, SetNumericPropertyValueFromString, void, PARAMS(void*, TCHAR const*), ARGS(Data, Value))
    }

    auto FNumericProperty::GetSignedIntPropertyValue(void* Data) -> int64
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, GetSignedIntPropertyValue, int64, PARAMS(void*), ARGS(Data))
    }

    auto FNumericProperty::GetUnsignedIntPropertyValue(void const* Data) -> uint64
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, GetUnsignedIntPropertyValue, uint64, PARAMS(void const*), ARGS(Data))
    }

    auto FNumericProperty::GetFloatingPointPropertyValue(void const* Data) -> double
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, GetFloatingPointPropertyValue, double, PARAMS(void const*), ARGS(Data))
    }

    auto FNumericProperty::GetNumericPropertyValueToString(void const* Data) -> FString
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, GetNumericPropertyValueToString, FString, PARAMS(void const*), ARGS(Data))
    }

    auto FNumericProperty::CanHoldDoubleValueInternal(double Value) const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, CanHoldDoubleValueInternal, bool, PARAMS(double), ARGS(Value))
    }

    auto FNumericProperty::CanHoldSignedValueInternal(int64 Value) const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, CanHoldSignedValueInternal, bool, PARAMS(int64), ARGS(Value))
    }

    auto FNumericProperty::CanHoldUnsignedValueInternal(uint64 Value) const -> bool
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FNumericProperty, CanHoldUnsignedValueInternal, bool, PARAMS(uint64), ARGS(Value))
    }
}