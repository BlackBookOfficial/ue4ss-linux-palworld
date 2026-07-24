#pragma once

#include <Unreal/Core/Containers/UnrealString.hpp>
#include <Unreal/Core/Misc/Crc.hpp>

#include <Helpers/String.hpp>

namespace RC::Unreal
{
    class FString;

    class RC_UE_API FUtf8String : public TStringBase<UTF8CHAR>
    {
    private:
        using Super = TStringBase<UTF8CHAR>;

    public:
        using Super::Super;
        
        FUtf8String() = default;
        explicit FUtf8String(const UTF8CHAR* Str) : Super(Str) {}
        explicit FUtf8String(UTF8CHAR* Str) : Super(Str) {}
        explicit FUtf8String(const StringType& str) : Super()
        {
            auto converted = to_utf8_string(str);  // Returns std::string (char-based)
            // UTF8CHAR is uint8, char might be signed, so reinterpret_cast is needed
            this->AppendChars(reinterpret_cast<const UTF8CHAR*>(converted.c_str()), static_cast<int32>(converted.length()));
        }
        
        // Conversion from FString
        explicit FUtf8String(const FString& Str);
        
        // Assignment operator
        FUtf8String& operator=(const FUtf8String& Other)
        {
            if (Data.Num() > 0 && Data.GetData())
            {
                Data.Empty();
            }
            Data = Other.Data;
            return *this;
        }
        
        // Methods that return FUtf8String
        FUtf8String Left(int32 Count) const;
        FUtf8String Right(int32 Count) const;
        FUtf8String Mid(int32 Start, int32 Count = MAX_int32) const;
        FUtf8String Replace(const UTF8CHAR* SearchText, const UTF8CHAR* ReplacementText,
                           ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const;
        int32 ReplaceInline(const UTF8CHAR* SearchText, const UTF8CHAR* ReplacementText,
                           ESearchCase::Type SearchCase = ESearchCase::IgnoreCase);
        FUtf8String ToUpper() const;
        FUtf8String ToLower() const;
        FUtf8String TrimStart() const;
        FUtf8String TrimEnd() const;
        FUtf8String TrimStartAndEnd() const;
        FUtf8String Trim() const { return TrimStartAndEnd(); }
        FUtf8String Reverse() const;
        int32 Split(const UTF8CHAR* InS, TArray<FUtf8String>& OutArray, bool InCullEmpty = true) const;
        
        // Hash function
        friend FORCEINLINE uint32 GetTypeHash(const FUtf8String& S)
        {
            return FCrc::Strihash_DEPRECATED(S.Len(), reinterpret_cast<const char*>(*S));
        }
    };
}