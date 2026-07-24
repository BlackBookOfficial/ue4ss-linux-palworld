#pragma once

#include <File/Macros.hpp>

#include <Unreal/Common.hpp>
#include <Unreal/UObject.hpp>

namespace RC::Unreal
{
    class RC_UE_API ReflectedFunctionBase
    {
    protected:
        class UFunction* Function{nullptr};
        const File::CharType* FunctionFullNameNoType{};
        int32 ReturnValueOffset{};

    public:
        ReflectedFunctionBase(const File::CharType* FunctionName) : Function(nullptr), FunctionFullNameNoType(FunctionName) {}

    public:
        auto GetFullName() const -> const File::CharType* { return FunctionFullNameNoType; }
        auto AssignFunction(UFunction* Function_) -> void;
        auto IsValid() -> bool;
        int32 GetReturnValueOffset() { return ReturnValueOffset; }
    };

    template<typename Owner>
    class RC_UE_API StaticReflectedFunctionBase : public ReflectedFunctionBase
    {
    public:
        template<typename ParamsType>
        auto operator()(ParamsType& params)
        {
            Owner::Self->ProcessEvent(this->Function, &params);
        }
    };

    class RC_UE_API InstancedReflectedFunction: public ReflectedFunctionBase
    {
    public:
        template<typename ParamsType>
        auto operator()(UObject* Instance, ParamsType& Params)
        {
            Instance->ProcessEvent(this->Function, &Params);
        }
    };
}


