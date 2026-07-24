#pragma once

#include <Unreal/Core/Containers/UnrealString.hpp>
#include <Unreal/Core/Misc/Crc.hpp>

#include <Helpers/String.hpp>

namespace RC::Unreal
{
    namespace UnrealInitializer
    {
        struct CacheInfo;
        RC_UE_API auto CreateCache(UnrealInitializer::CacheInfo& Target) -> void;
        RC_UE_API auto LoadCache(UnrealInitializer::CacheInfo& Target) -> void;
    }

    class RC_UE_API FString : public TStringBase<TCHAR>
    {
    private:
        using Super = TStringBase<TCHAR>;
        
        friend RC_UE_API auto UnrealInitializer::CreateCache(UnrealInitializer::CacheInfo& Target) -> void;
        friend RC_UE_API auto UnrealInitializer::LoadCache(UnrealInitializer::CacheInfo& Target) -> void;

    public:
        using Super::Super;
        
        FString() = default;
        explicit FString(TCHAR* Str) : Super(Str) {}
        explicit FString(const TCHAR* Str) : Super(Str) {}

        explicit FString(const StringType& str) : Super()
        {
            auto converted = ensure_str_as<TCHAR>(str);
            this->AppendChars(converted.c_str(), static_cast<int32>(converted.length()));
        }

        // Assignment operator
        FString& operator=(const FString& Other)
        {
            if (Data.Num() > 0 && Data.GetData())
            {
                Data.Empty();
            }
            Data = Other.Data;
            return *this;
        }

        // Keep GetCharTArray for backward compatibility but mark as deprecated
        [[deprecated("Use GetCharArray() to access the underlying array instead")]]
        [[nodiscard]] auto GetCharTArray() const -> const TArray<TCHAR>&
        {
            return Data;
        }

        [[deprecated("Use GetCharArray() to access the underlying array instead")]]
        [[nodiscard]] auto GetCharTArray() -> TArray<TCHAR>&
        {
            return Data;
        }

        auto SetCharArray(TArray<TCHAR>& NewArray) -> void
        {
            if (Data.Num() > 0 && Data.GetData())
            {
                Data.Empty();
            }
            Data = NewArray;
            Data.Add(STR('\0'));
        }

        // Clear method for compatibility
        auto Clear() -> void
        {
            Data.Empty();
        }

        // FString-specific methods
        static FString Printf(const TCHAR* Format, ...);
        FString& Appendf(const TCHAR* Format, ...);
        FString& AppendInt(int32 InNum);
        static FString FromInt(int32 InNum);
        
        // Methods that return FString
        FString Left(int32 Count) const;
        FString Right(int32 Count) const;
        FString Mid(int32 Start, int32 Count = MAX_int32) const;
        FString Replace(const TCHAR* SearchText, const TCHAR* ReplacementText, 
                       ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const;
        int32 ReplaceInline(const TCHAR* SearchText, const TCHAR* ReplacementText,
                           ESearchCase::Type SearchCase = ESearchCase::IgnoreCase);
        FString ToUpper() const;
        FString ToLower() const;
        FString TrimStart() const;
        FString TrimEnd() const;
        FString TrimStartAndEnd() const;
        FString Trim() const { return TrimStartAndEnd(); }
        FString Reverse() const;
        int32 Split(const TCHAR* InS, TArray<FString>& OutArray, bool InCullEmpty = true) const;
        
        // Hash function
        friend FORCEINLINE uint32 GetTypeHash(const FString& S)
        {
            return FCrc::Strihash_DEPRECATED(S.Len(), *S);
        }
    };

    class RC_UE_API FStringOut : public FString
    {
    public:
        FStringOut() = default;
        FStringOut(const FStringOut&); // Copy constructor
        FStringOut(FStringOut&&) noexcept;  // Move constructor
        ~FStringOut();
    };
}