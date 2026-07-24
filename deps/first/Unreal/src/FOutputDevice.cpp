#include <Unreal/FOutputDevice.hpp>
#include <Function/Function.hpp>
#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <Unreal/Core/Misc/VarargsHelper.hpp>
#include <Unreal/Core/Misc/CString.hpp>
#include <Unreal/NameTypes.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    std::unordered_map<File::StringType, uint32_t> FOutputDevice::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_FOutputDevice.hpp>

    void FOutputDevice::Virtual_Serialize(const TCHAR* V, [[maybe_unused]]ELogVerbosity::Type Verbosity, [[maybe_unused]]const FName& Category)
    {
        Output::send(STR("{}\n"), (const CharType*) V);
    }
    void FOutputDevice::Virtual_Serialize(const TCHAR* V, [[maybe_unused]]ELogVerbosity::Type Verbosity, [[maybe_unused]]const FName& Category, [[maybe_unused]]const double Time)
    {
        Output::send(STR("{}\n"), (const CharType*) V);
    }
    void FOutputDevice::Virtual_4()
    {
        Output::send(STR("FOutputDevice::Virtual_4\n"));
    }
    void FOutputDevice::Virtual_5()
    {
        Output::send(STR("FOutputDevice::Virtual_5\n"));
    }
    void FOutputDevice::Virtual_6()
    {
        Output::send(STR("FOutputDevice::Virtual_6\n"));
    }
    void FOutputDevice::Virtual_7()
    {
        Output::send(STR("FOutputDevice::Virtual_7\n"));
    }
    void FOutputDevice::Virtual_8()
    {
        Output::send(STR("FOutputDevice::Virtual_8\n"));
    }
    void FOutputDevice::Virtual_9()
    {
        Output::send(STR("FOutputDevice::Virtual_9\n"));
    }
    void FOutputDevice::Virtual_10()
    {
        Output::send(STR("FOutputDevice::Virtual_10\n"));
    }
    void FOutputDevice::Virtual_11()
    {
        Output::send(STR("FOutputDevice::Virtual_11\n"));
    }
    void FOutputDevice::Virtual_12()
    {
        Output::send(STR("FOutputDevice::Virtual_12\n"));
    }
    void FOutputDevice::Virtual_13()
    {
        Output::send(STR("FOutputDevice::Virtual_13\n"));
    }
    void FOutputDevice::Virtual_14()
    {
        Output::send(STR("FOutputDevice::Virtual_14\n"));
    }
    void FOutputDevice::Virtual_15()
    {
        Output::send(STR("FOutputDevice::Virtual_15\n"));
    }
    void FOutputDevice::Virtual_16()
    {
        Output::send(STR("FOutputDevice::Virtual_16\n"));
    }
    void FOutputDevice::Virtual_17()
    {
        Output::send(STR("FOutputDevice::Virtual_17\n"));
    }
    void FOutputDevice::Virtual_18()
    {
        Output::send(STR("FOutputDevice::Virtual_18\n"));
    }
    void FOutputDevice::Virtual_19()
    {
        Output::send(STR("FOutputDevice::Virtual_19\n"));
    }
    void FOutputDevice::Virtual_20()
    {
        Output::send(STR("FOutputDevice::Virtual_20\n"));
    }
    void FOutputDevice::Virtual_21()
    {
        Output::send(STR("FOutputDevice::Virtual_21\n"));
    }
    void FOutputDevice::Virtual_22()
    {
        Output::send(STR("FOutputDevice::Virtual_22\n"));
    }
    void FOutputDevice::Virtual_23()
    {
        Output::send(STR("FOutputDevice::Virtual_23\n"));
    }
    void FOutputDevice::Virtual_24()
    {
        Output::send(STR("FOutputDevice::Virtual_24\n"));
    }
    void FOutputDevice::Virtual_25()
    {
        Output::send(STR("FOutputDevice::Virtual_25\n"));
    }
    void FOutputDevice::Virtual_26()
    {
        Output::send(STR("FOutputDevice::Virtual_26\n"));
    }
    void FOutputDevice::Virtual_27()
    {
        Output::send(STR("FOutputDevice::Virtual_27\n"));
    }
    void FOutputDevice::Virtual_28()
    {
        Output::send(STR("FOutputDevice::Virtual_28\n"));
    }
    void FOutputDevice::Virtual_29()
    {
        Output::send(STR("FOutputDevice::Virtual_29\n"));
    }
    void FOutputDevice::Virtual_30()
    {
        Output::send(STR("FOutputDevice::Virtual_30\n"));
    }

    void FOutputDevice::Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_MULTI_NAME(FOutputDevice,
                                         Serialize__Ptr_C_wchar_t__ELogVerbosity_Type__Ref_C_FName__C_double,
                                         void,
                                         PARAMS(const TCHAR*, ELogVerbosity::Type, const FName&, const double),
                                         ARGS(V, Verbosity, Category, Time),
                                         STR("Serialize"))
    }

    void FOutputDevice::Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_MULTI_NAME(FOutputDevice,
                                         Serialize__Ptr_C_wchar_t__ELogVerbosity_Type__Ref_C_FName__C_double,
                                         void,
                                         PARAMS(const TCHAR*, ELogVerbosity::Type, const FName&, const double),
                                         ARGS(V, Verbosity, Category, Time),
                                         STR("Serialize"))
    }

    void FOutputDevice::Flush()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FOutputDevice, Flush, void)
    }

    void FOutputDevice::TearDown()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FOutputDevice, TearDown, void)
    }

    void FOutputDevice::Dump(FArchive& Ar)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FOutputDevice, Dump, void, PARAMS(FArchive&), ARGS(Ar))
    }

    bool FOutputDevice::IsMemoryOnly() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FOutputDevice, IsMemoryOnly, bool)
    }

    bool FOutputDevice::CanBeUsedOnAnyThread() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FOutputDevice, CanBeUsedOnAnyThread, bool)
    }

    bool FOutputDevice::CanBeUsedOnMultipleThreads() const
    {
        if (Version::IsBelow(4, 21))
        {
            throw std::runtime_error{"FOutputDevice::CanBeUsedOnMultipleThreads is only available in 4.21+"};
        }

        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FOutputDevice, CanBeUsedOnMultipleThreads, bool)
    }

    void FOutputDevice::Log(const TCHAR* Str)
    {
        Serialize(Str, ELogVerbosity::Verbose, FName(), 0);
    }

    void FOutputDevice::Log(const TCHAR* Str) const
    {
        Serialize(Str, ELogVerbosity::Verbose, FName(), 0);
    }

    // Do not inline these functions, in case we need to capture a call stack in FOutputDeviceError::Serialize. We need to be certain of how many frames to ignore.
    FORCENOINLINE void FOutputDevice::CategorizedLogfImpl(const FName& Category, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...)
    {
        GROWABLE_LOGF(Serialize(Buffer, Verbosity, Category, 0))
    }
    FORCENOINLINE void FOutputDevice::LogfImpl(ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...)
    {
        // call serialize with the final buffer
        GROWABLE_LOGF(Serialize(Buffer, Verbosity, NAME_None, 0))
    }
    FORCENOINLINE void FOutputDevice::LogfImpl(const TCHAR* Fmt, ...)
    {
        GROWABLE_LOGF(Serialize(Buffer, ELogVerbosity::Verbose, FName(), 0))
    }

}
