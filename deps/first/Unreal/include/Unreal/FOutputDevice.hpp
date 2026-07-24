#pragma once

#include <unordered_map>

#include <Unreal/Common.hpp>
#include <Unreal/Core/CoreTypes.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/LogVerbosity.hpp>
#include <Unreal/Core/Templates/IsArrayOrRefOfTypeByPredicate.hpp>
#include <Unreal/Core/Traits/IsCharEncodingCompatibleWith.hpp>
#include <Unreal/Core/Templates/AndOrNot.hpp>
#include <Unreal/Core/Templates/IsValidVariadicFunctionArg.hpp>
#include <Unreal/FArchive.hpp>

#include <Unreal/BitfieldProxy.hpp>

namespace RC::Unreal
{
    class RC_UE_API FOutputDevice
    {
    protected:
        /** Whether to output the 'Log: ' type front... */
        bool bSuppressEventTag;
        /** Whether to output a line-terminator after each log call... */
        bool bAutoEmitLineTerminator;

    public:
        static std::unordered_map<File::StringType, uint32_t> VTableLayoutMap;

    public:
        // This is a list of virtual functions, they don't need to be of the correct signature for our purposes.
        // The only virtuals that need to have the correct signature are the ones that are being used, the rest only needs to exist.
        // NOTE: If UE calls one of these and is expecting a return value, it might break if we don't return something.
        // DO NOT CALL ANY OF THESE VIRTUAL FUNCTIONS!
        // These are called by UE if we supply our own FOutputDevice.
        // Feel free to add proper signatures if you can guarantee that the position in the vtable is identical from 4.12 to now.
        virtual ~FOutputDevice() = default;
        virtual void Virtual_Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category);
        virtual void Virtual_Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time);
        virtual void Virtual_4();
        virtual void Virtual_5();
        virtual void Virtual_6();
        virtual void Virtual_7();
        virtual void Virtual_8();
        virtual void Virtual_9();
        virtual void Virtual_10();
        virtual void Virtual_11();
        virtual void Virtual_12();
        virtual void Virtual_13();
        virtual void Virtual_14();
        virtual void Virtual_15();
        virtual void Virtual_16();
        virtual void Virtual_17();
        virtual void Virtual_18();
        virtual void Virtual_19();
        virtual void Virtual_20();
        virtual void Virtual_21();
        virtual void Virtual_22();
        virtual void Virtual_23();
        virtual void Virtual_24();
        virtual void Virtual_25();
        virtual void Virtual_26();
        virtual void Virtual_27();
        virtual void Virtual_28();
        virtual void Virtual_29();
        virtual void Virtual_30();

    public:
#include <MemberVariableLayout_HeaderWrapper_FOutputDevice.hpp>

        // Wrappers for virtual engine functions
        // Missing the first overload because the generator doesn't support overloads
        void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time);
        void Serialize(const TCHAR* V, ELogVerbosity::Type Verbosity, const FName& Category, const double Time) const;
        void Flush();
        void TearDown();
        void Dump(FArchive& Ar);
        bool IsMemoryOnly() const;
        bool CanBeUsedOnAnyThread() const;
        // Added in 4.21, throws in lesser versions
        bool CanBeUsedOnMultipleThreads() const;

    public:
        void Log(const TCHAR* Str);
        void Log(const TCHAR* Str) const;

    private:
        void VARARGS LogfImpl(const TCHAR* Fmt, ...);
        void VARARGS LogfImpl(ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...);
        void VARARGS CategorizedLogfImpl(const FName& Category, ELogVerbosity::Type Verbosity, const TCHAR* Fmt, ...);

    public:
        template <typename FmtType>
        void Logf(const FmtType& Fmt)
        {
            static_assert(TIsArrayOrRefOfTypeByPredicate<FmtType, TIsCharEncodingCompatibleWithTCHAR>::Value, "Formatting string must be a TCHAR array.");
            return Log((const TCHAR*)Fmt);
        }

        template <typename FmtType, typename... Types>
        FORCEINLINE void Logf(const FmtType& Fmt, Types... Args)
        {
            static_assert(TIsArrayOrRefOfTypeByPredicate<FmtType, TIsCharEncodingCompatibleWithTCHAR>::Value, "Formatting string must be a TCHAR array.");
            static_assert(TAnd<TIsValidVariadicFunctionArg<Types>...>::Value, "Invalid argument(s) passed to FOutputDevice::Logf");

            LogfImpl((const TCHAR*)Fmt, Args...);
        }

        template <typename FmtType, typename... Types>
        FORCEINLINE void Logf(ELogVerbosity::Type Verbosity, const FmtType& Fmt, Types... Args)
        {
            static_assert(TIsArrayOrRefOfTypeByPredicate<FmtType, TIsCharEncodingCompatibleWithTCHAR>::Value, "Formatting string must be a TCHAR array.");
            static_assert(TAnd<TIsValidVariadicFunctionArg<Types>...>::Value, "Invalid argument(s) passed to FOutputDevice::Logf");

            LogfImpl(Verbosity, (const TCHAR*)Fmt, Args...);
        }

        template <typename FmtType, typename... Types>
        FORCEINLINE void CategorizedLogf(const FName& Category, ELogVerbosity::Type Verbosity, const FmtType& Fmt, Types... Args)
        {
            static_assert(TIsArrayOrRefOfTypeByPredicate<FmtType, TIsCharEncodingCompatibleWithTCHAR>::Value, "Formatting string must be a TCHAR array.");
            static_assert(TAnd<TIsValidVariadicFunctionArg<Types>...>::Value, "Invalid argument(s) passed to FOutputDevice::CategorizedLogf");

            CategorizedLogfImpl(Category, Verbosity, (const TCHAR*)Fmt, Args...);
        }
    };
}


