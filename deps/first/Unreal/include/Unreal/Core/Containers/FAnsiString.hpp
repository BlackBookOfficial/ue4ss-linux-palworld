#pragma once

#include <Unreal/Core/Containers/UnrealString.hpp>
#include <Unreal/Core/Misc/Crc.hpp>

#include <Helpers/String.hpp>

namespace RC::Unreal
{
    class FString; // Forward declaration

    class RC_UE_API FAnsiString : public TStringBase<ANSICHAR>
    {
    private:
        using Super = TStringBase<ANSICHAR>;

    public:
        using Super::Super;
        
        FAnsiString() = default;
        explicit FAnsiString(const ANSICHAR* Str) : Super(Str) {}
        explicit FAnsiString(ANSICHAR* Str) : Super(Str) {}
        explicit FAnsiString(const StringType& str) : Super()
        {
            auto converted = ensure_str_as<ANSICHAR>(str);  // ANSICHAR is char
            this->AppendChars(converted.c_str(), static_cast<int32>(converted.length()));
        }
        
        // Conversion from FString
        explicit FAnsiString(const FString& Str);
        
        // Assignment operator
        FAnsiString& operator=(const FAnsiString& Other)
        {
            if (Data.Num() > 0 && Data.GetData())
            {
                Data.Empty();
            }
            Data = Other.Data;
            return *this;
        }
        
        // Methods that return FAnsiString
        FAnsiString Left(int32 Count) const;
        FAnsiString Right(int32 Count) const;
        FAnsiString Mid(int32 Start, int32 Count = MAX_int32) const;
        FAnsiString Replace(const ANSICHAR* SearchText, const ANSICHAR* ReplacementText,
                           ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const;
        int32 ReplaceInline(const ANSICHAR* SearchText, const ANSICHAR* ReplacementText,
                           ESearchCase::Type SearchCase = ESearchCase::IgnoreCase);
        FAnsiString ToUpper() const;
        FAnsiString ToLower() const;
        FAnsiString TrimStart() const;
        FAnsiString TrimEnd() const;
        FAnsiString TrimStartAndEnd() const;
        FAnsiString Trim() const { return TrimStartAndEnd(); }
        FAnsiString Reverse() const;
        int32 Split(const ANSICHAR* InS, TArray<FAnsiString>& OutArray, bool InCullEmpty = true) const;
        
        // Hash function
        friend FORCEINLINE uint32 GetTypeHash(const FAnsiString& S)
        {
            return FCrc::Strihash_DEPRECATED(S.Len(), *S);
        }
    };
}