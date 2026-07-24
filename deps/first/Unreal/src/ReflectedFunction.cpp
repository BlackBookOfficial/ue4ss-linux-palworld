#include <Unreal/ReflectedFunction.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <DynamicOutput/DynamicOutput.hpp>

namespace RC::Unreal
{
    auto ReflectedFunctionBase::AssignFunction(UFunction* Function_) -> void
    {
        if (!Function_) { return; }

        Function = Function_;
        ReturnValueOffset = Function_->GetReturnValueOffset();
    }

    auto ReflectedFunctionBase::IsValid() -> bool
    {
        if (!Function)
        {
            AssignFunction(UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, GetFullName()));
            if (!Function)
            {
                Output::send(STR("Was unable to locate '{}'\n"), File::StringViewType{GetFullName()});
                return false;
            }
        }

        return Function;
    }
}
