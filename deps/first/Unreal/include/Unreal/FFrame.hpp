#pragma once

#include <Unreal/Common.hpp>
#include <Unreal/FOutputDevice.hpp>

namespace RC::Unreal
{
    class FFieldClass;
    class UClass;
    class FFieldClassVariant;
    class UObject;
    class FField;
    struct FOutParmRec;
    class UFunction;

    using FlowStackType = uint8[0x30];
    using FlowStackTypePtr = uint8*;

    struct RC_UE_API FOutParmRec
    {
        FProperty* Property{};
        uint8* PropAddr{};
        FOutParmRec* NextOutParm{};
    };

    struct RC_UE_API FFrame_50_AndBelow : public FOutputDevice
    {
        using FFrame = FFrame_50_AndBelow;

        // Variables.
        UFunction* Node;
        UObject* Object;
        uint8* Code;
        uint8* Locals;

        FProperty* MostRecentProperty;
        uint8* MostRecentPropertyAddress;

        /** The execution flow stack for compiled Kismet code */
        FlowStackType FlowStack;

        /** Previous frame on the stack */
        FFrame* PreviousFrame;

        /** contains information on any out parameters */
        FOutParmRec* OutParms;

        /** If a class is compiled in then this is set to the property chain for compiled-in functions. In that case, we follow the links to setup the args instead of executing by code. */
        FField* PropertyChainForCompiledIn;

        /** Currently executed native function */
        UFunction* CurrentNativeFunction;

        bool bArrayContextFailed;
    };

    struct RC_UE_API FFrame_51_AndAbove : public FOutputDevice
    {
        using FFrame = FFrame_51_AndAbove;

        // Variables.
        UFunction* Node;
        UObject* Object;
        uint8* Code;
        uint8* Locals;

        FProperty* MostRecentProperty;
        uint8* MostRecentPropertyAddress;
        uint8* MostRecentPropertyContainer; // New in 5.1.

        /** The execution flow stack for compiled Kismet code */
        FlowStackType FlowStack;

        /** Previous frame on the stack */
        FFrame* PreviousFrame;

        /** contains information on any out parameters */
        FOutParmRec* OutParms;

        /** If a class is compiled in then this is set to the property chain for compiled-in functions. In that case, we follow the links to setup the args instead of executing by code. */
        FField* PropertyChainForCompiledIn;

        /** Currently executed native function */
        UFunction* CurrentNativeFunction;

        /** Previous tracking frame */
        FFrame* PreviousTrackingFrame;

        bool bArrayContextFailed;

        /** If this flag gets set (usually from throwing a EBlueprintExceptionType::AbortExecution exception), execution shall immediately stop and return */
        bool bAbortingExecution;
    };

    struct RC_UE_API FFrame
    {
        UFunction*& Node();
        UObject*& Object();
        uint8*& Code();
        uint8*& Locals();
        FProperty*& MostRecentProperty();
        uint8*& MostRecentPropertyAddress();
        uint8*& MostRecentPropertyContainer();
        FlowStackTypePtr FlowStack();
        FFrame*& PreviousFrame();
        FOutParmRec*& OutParms();
        FField*& PropertyChainForCompiledIn();
        UFunction*& CurrentNativeFunction();
        FFrame*& PreviousTrackingFrame();
        bool& bArrayContextFailed();
        bool& bAbortingExecution();

        // Functions.
        void Step(UObject* Context, void* RESULT_DECL);

        /** Replacement for Step that uses an explicitly specified property to unpack arguments **/
        void StepExplicitProperty(void*const Result, FProperty* Property);

        /**
         * Replacement for Step that checks the for byte code, and if none exists, then PropertyChainForCompiledIn is used.
         * Also makes an effort to verify that the params are in the correct order and the types are compatible.
         **/
        template<class TProperty>
        void StepCompiledIn(void* Result)
        {
            StepCompiledIn(Result, TProperty::StaticClass());
        }
        void StepCompiledIn(void* Result, FFieldClassVariant ExpectedPropertyType);
        void StepCompiledIn(void* Result, FProperty* Property);
        
        /**
         * Creates a new FFrame with its members initialized to 0.
         *
         * This function creates a new instance of an FFrame-derived object (either FFrame_50_AndBelow or FFrame_51_AndAbove,
         * depending on the engine version).
         *
         * @return A pointer to the newly allocated duplicate frame. 
         *
         * @note The caller is responsible for manual deletion of the returned frame to avoid memory leaks.
         *       This function uses ::Malloc and returns a raw pointer, so the caller must invoke 
         *       ::Free on the returned pointer when it is no longer needed.
         *
         * @warning Manual memory management is required for the returned pointer. Failure to delete the 
         *          returned FFrame will result in a memory leak.
         *
         * @warning This function performs a reinterpret_cast based on engine version checks and assumes 
         *          that the provided frame can be safely cast to the appropriate derived type. Use with caution.
         */
        static FFrame* MallocAndMemsetNewFrame();
    };

    RC_UE_API void* FindOutParamValueAddress(FFrame&, FProperty* Param);
}