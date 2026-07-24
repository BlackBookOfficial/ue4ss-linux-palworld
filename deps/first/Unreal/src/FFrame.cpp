#include <Unreal/FFrame.hpp>
#include <Unreal/Script.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <stdexcept>

#include <DynamicOutput/Output.hpp>

namespace RC::Unreal
{
    UFunction*& FFrame::Node()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->Node;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->Node;
        }
    }

    UObject*& FFrame::Object()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->Object;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->Object;
        }
    }

    uint8*& FFrame::Code()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->Code;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->Code;
        }
    }

    uint8*& FFrame::Locals()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->Locals;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->Locals;
        }
    }

    FProperty*& FFrame::MostRecentProperty()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->MostRecentProperty;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->MostRecentProperty;
        }
    }

    uint8*& FFrame::MostRecentPropertyAddress()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->MostRecentPropertyAddress;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->MostRecentPropertyAddress;
        }
    }

    uint8*& FFrame::MostRecentPropertyContainer()
    {
        if (Version::IsBelow(5, 1))
        {
            throw std::runtime_error{"FFrame::MostRecentPropertyContainer doesn't exist in <=5.0."};
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->MostRecentPropertyContainer;
        }
    }

    FlowStackTypePtr FFrame::FlowStack()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->FlowStack;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->FlowStack;
        }
    }

    FFrame*& FFrame::PreviousFrame()
    {
        if (Version::IsBelow(5, 1))
        {
            auto* frame50 = reinterpret_cast<FFrame_50_AndBelow*>(this);
            // Obtain the address of the PreviousTrackingFrame member.
            FFrame** memberAddress = reinterpret_cast<FFrame**>(&frame50->PreviousFrame);
            // Dereference to get a reference to the pointer member.
            return *memberAddress;
        }
        else
        {
            auto* frame51 = reinterpret_cast<FFrame_51_AndAbove*>(this);
            // Obtain the address of the PreviousTrackingFrame member.
            FFrame** memberAddress = reinterpret_cast<FFrame**>(&frame51->PreviousFrame);
            // Dereference to get a reference to the pointer member.
            return *memberAddress;
        }
    }

    FOutParmRec*& FFrame::OutParms()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->OutParms;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->OutParms;
        }
    }

    FField*& FFrame::PropertyChainForCompiledIn()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->PropertyChainForCompiledIn;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->PropertyChainForCompiledIn;
        }
    }

    UFunction*& FFrame::CurrentNativeFunction()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->CurrentNativeFunction;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->CurrentNativeFunction;
        }
    }

    FFrame*& FFrame::PreviousTrackingFrame()
    {
        if (Version::IsBelow(5, 1))
        {
            throw std::runtime_error{"FFrame::PreviousTrackingFrame doesn't exist in <=5.0."};
        }
        else
        {
            auto* frame51 = reinterpret_cast<FFrame_51_AndAbove*>(this);
            // Obtain the address of the PreviousTrackingFrame member.
            FFrame** memberAddress = reinterpret_cast<FFrame**>(&frame51->PreviousTrackingFrame);
            // Dereference to get a reference to the pointer member.
            return *memberAddress;
        }
    }

    bool& FFrame::bArrayContextFailed()
    {
        if (Version::IsBelow(5, 1))
        {
            return std::bit_cast<FFrame_50_AndBelow*>(this)->bArrayContextFailed;
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->bArrayContextFailed;
        }
    }

    bool& FFrame::bAbortingExecution()
    {
        if (Version::IsBelow(5, 1))
        {
            throw std::runtime_error{"FFrame::bAbortingExecution doesn't exist in <=5.0."};
        }
        else
        {
            return std::bit_cast<FFrame_51_AndAbove*>(this)->bAbortingExecution;
        }
    }

    void FFrame::Step(UObject* Context, void* RESULT_DECL)
    {
        if (!GNatives_Internal)
        {
            Output::send<LogLevel::Error>(STR("Error: GNatives not available, unable to Step frame.\n"));
            return;
        }
        
        int32 B = *Code()++;
        GNatives_Internal[B](Context,*this, RESULT_DECL);
    }

    void FFrame::StepExplicitProperty(void*const Result, FProperty* Property)
    {
        checkSlow(Result != NULL);

        if (Property->HasAnyPropertyFlags(CPF_OutParm))
        {
            // look through the out parameter infos and find the one that has the address of this property
            FOutParmRec* Out = OutParms();
            checkSlow(Out);
            while (Out->Property != Property)
            {
                Out = Out->NextOutParm;
                checkSlow(Out);
            }
            MostRecentPropertyAddress() = Out->PropAddr;
            if (Version::IsAtLeast(5, 1)) { MostRecentPropertyContainer() = nullptr; }
            
            // no need to copy property value, since the caller is just looking for MostRecentPropertyAddress
        }
        else
        {
            MostRecentPropertyAddress() = Property->ContainerPtrToValuePtr<uint8>(Locals());
            if (Version::IsAtLeast(5, 1)) { MostRecentPropertyContainer() = Locals(); }
            Property->CopyCompleteValueToScriptVM(Result, MostRecentPropertyContainer());
        }
    }

    void FFrame::StepCompiledIn(void* Result, FFieldClassVariant ExpectedPropertyType)
    {
        if (Code())
        {
            Step(Object(), Result);
        }
        else
        {
            checkSlow(ExpectedPropertyType && ExpectedPropertyType->IsChildOf(FProperty::StaticClass().ToFieldClass()));
            checkSlow(PropertyChainForCompiledIn() && PropertyChainForCompiledIn()->IsA(ExpectedPropertyType));
            auto Property = static_cast<FProperty*>(PropertyChainForCompiledIn());
            PropertyChainForCompiledIn() = static_cast<FField*>(Property->GetNextRef());
            StepExplicitProperty(Result, Property);
        }
    }

    void FFrame::StepCompiledIn(void* Result, FProperty* Property)
    {
        StepCompiledIn(Result, Property->GetClass());
    }

    FFrame* FFrame::MallocAndMemsetNewFrame()
    {
        FFrame* NewFrame = nullptr;

        if (Version::IsBelow(5, 1))
        {
            NewFrame = static_cast<FFrame*>(FMemory::Malloc(sizeof(FFrame_50_AndBelow)));
            FMemory::Memset(NewFrame, 0, sizeof(FFrame_50_AndBelow));
        }
        else
        {
            NewFrame = static_cast<FFrame*>(FMemory::Malloc(sizeof(FFrame_51_AndAbove)));
            FMemory::Memset(NewFrame, 0, sizeof(FFrame_51_AndAbove));
        }

        if (!NewFrame) {
            Output::send<LogLevel::Error>(STR("Failed to allocate new FFrame.\n"));
        }

        return NewFrame;
    }

    void* FindOutParamValueAddress(FFrame& Stack, FProperty* Param)
    {
        auto OutParams = Stack.OutParms();
        while (OutParams && OutParams->Property != Param)
        {
            OutParams = OutParams->NextOutParm;
        }
        return OutParams ? OutParams->PropAddr : nullptr;
    }
}