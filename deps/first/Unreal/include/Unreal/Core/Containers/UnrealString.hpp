#pragma once

#include <Function/Function.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/Core/Containers/Array.hpp>
#include <Unreal/Core/Containers/AllowShrinking.hpp>
#include <Unreal/Core/Misc/CString.hpp>
#include <Unreal/Core/Misc/CoreMiscDefines.hpp>
#include <Unreal/Core/Math/NumericLimits.hpp>
#include <Unreal/Core/Misc/Char.hpp>
#include <Unreal/Core/Math/UnrealMathUtility.hpp>

namespace RC::Unreal
{
    template<typename CharType>
    class TStringBase
    {
    public:
        typedef TArray<CharType> DataType;
        typedef CharType ElementType;
        
    protected:
        DataType Data{nullptr, 0, 0};

        static const CharType* GetEmptyString()
        {
            if constexpr (std::is_same_v<CharType, TCHAR>)
                return TEXT("");
            else if constexpr (std::is_same_v<CharType, UTF8CHAR>)
                return UTF8TEXT("");
            else if constexpr (std::is_same_v<CharType, ANSICHAR>)
                return "";
            else
                return nullptr;
        }

    public:
        TStringBase() = default;
        TStringBase(TStringBase&&) = default;
        TStringBase(const TStringBase&) = default;
        TStringBase& operator=(TStringBase&&) = default;
        TStringBase& operator=(const TStringBase&) = default;
        
        explicit TStringBase(const CharType* Str)
        {
            if (Str)
            {
                size_t StrLength = TCString<CharType>::Strlen(Str);
                if (StrLength > std::numeric_limits<int32_t>::max())
                {
                    throw std::runtime_error{"Tried to construct a string with a size larger than int32"};
                }

                int32_t SafeStrLength = static_cast<int32_t>(StrLength);
                Data.AddUninitialized(SafeStrLength);
                std::memcpy(Data.GetData(), Str, StrLength * sizeof(CharType));
                Data.Add(CharType('\0'));
            }
        }

        explicit TStringBase(CharType* Str) : TStringBase(const_cast<const CharType*>(Str)) {}

        // Core functionality
        [[nodiscard]] FORCEINLINE int32 Len() const 
        { 
            return Data.Num() ? Data.Num() - 1 : 0; 
        }

        [[nodiscard]] FORCEINLINE bool IsEmpty() const 
        { 
            return Data.Num() <= 1; 
        }

        /**
         * Get pointer to the string
         *
         * @Return Pointer to Array of CharType if Num, otherwise the empty string
         */
        [[nodiscard]] FORCEINLINE const CharType* operator*() const 
        { 
            return Data.Num() ? Data.GetData() : GetEmptyString(); 
        }

        [[nodiscard]] FORCEINLINE CharType& operator[](int32 Index)
        {
            checkf(IsValidIndex(Index), TEXT("String index out of bounds: Index %i from a string with a length of %i"), Index, Len());
            return Data.GetData()[Index];
        }

        [[nodiscard]] FORCEINLINE const CharType& operator[](int32 Index) const
        {
            checkf(IsValidIndex(Index), TEXT("String index out of bounds: Index %i from a string with a length of %i"), Index, Len());
            return Data.GetData()[Index];
        }

        [[nodiscard]] FORCEINLINE bool IsValidIndex(int32 Index) const
        {
            return Index >= 0 && Index < Len();
        }

        /** 
         * Get string as array of CharType 
         *
         * @warning: Operations on the TArray<CharType> can be unsafe, such as adding
         *        non-terminating 0's or removing the terminating zero.
         */
        [[nodiscard]] FORCEINLINE DataType& GetCharArray()
        {
            return Data;
        }

        /**
         * Get string as const array of CharType
         */
        [[nodiscard]] FORCEINLINE const DataType& GetCharArray() const
        {
            return Data;
        }

        /**
         * Run slow checks on this string
         */
        FORCEINLINE void CheckInvariants() const
        {
            int32 Num = Data.Num();
            checkSlow(Num >= 0);
            checkSlow(!Num || !Data.GetData()[Num - 1]);
            checkSlow(Data.GetSlack() >= 0);
        }

        void Empty(int32 Slack)
        {
            Data.Empty(Slack ? Slack + 1 : 0);
        }

        void Empty()
        {
            Data.Empty(0);
        }

        /**
         * Empties the string, but doesn't change memory allocation, unless the new size is larger than the current string.
         *
         * @param NewReservedSize The expected usage size (in characters, not including the terminator) after calling this function.
         */
        void Reset(int32 NewReservedSize = 0)
        {
            const int32 NewSizeIncludingTerminator = (NewReservedSize > 0) ? (NewReservedSize + 1) : 0;
            Data.Reset(NewSizeIncludingTerminator);
            if (NewSizeIncludingTerminator > 0)
            {
                Data.AddZeroed(1);
            }
        }

        /**
         * Remove unallocated empty character space from the end of this string
         */
        void Shrink()
        {
            Data.Shrink();
        }

        // To allow more efficient memory handling, automatically adds one for the string termination.
        FORCEINLINE void Reserve(int32 CharacterCount)
        {
            checkSlow(CharacterCount >= 0 && CharacterCount < MAX_int32);
            if (CharacterCount > 0)
            {
                Data.Reserve(CharacterCount + 1);
            }    
        }

        /**
         * Removes characters within the string.
         *
         * @param Index          The index of the first character to remove.
         * @param Count          The number of characters to remove.
         * @param AllowShrinking Whether or not to reallocate to shrink the storage after removal.
         */
        void RemoveAt(int32 Index, int32 Count = 1, EAllowShrinking AllowShrinking = EAllowShrinking::Default)
        {
            if (Count > 0)
            {
                CheckInvariants();
                
                const int32 NumToRemove = FMath::Min(Count, Len() - Index);
                Data.RemoveAt(Index, NumToRemove, AllowShrinking);
                
                CheckInvariants();
            }
        }

        /**
         * Inserts a character at the given index in the string.
         */
        void InsertAt(int32 Index, CharType Character)
        {
            CheckInvariants();
            
            if (Index >= 0 && Index <= Len())
            {
                if (Data.Num() == 0)
                {
                    Data.Add(Character);
                    Data.Add(CharType('\0'));
                }
                else
                {
                    Data.Insert(Character, Index);
                }
            }
            
            CheckInvariants();
        }

        // Comparison
        [[nodiscard]] bool Equals(const TStringBase& Other, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const
        {
            int32 Num = Data.Num();
            int32 OtherNum = Other.Data.Num();

            if (Num != OtherNum)
            {
                return Num + OtherNum == 1; // Handle special case where empty string == null string
            }
            else if (Num > 1)
            {
                if (SearchCase == ESearchCase::CaseSensitive)
                {
                    return TCString<CharType>::Strcmp(Data.GetData(), Other.Data.GetData()) == 0;
                }
                else
                {
                    return TCString<CharType>::Stricmp(Data.GetData(), Other.Data.GetData()) == 0;
                }
            }
            return true;
        }

        [[nodiscard]] int32 Compare(const TStringBase& Other, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const
        {
            if (SearchCase == ESearchCase::CaseSensitive)
            {
                return TCString<CharType>::Strcmp(**this, *Other);
            }
            else
            {
                return TCString<CharType>::Stricmp(**this, *Other);
            }
        }

        [[nodiscard]] bool operator==(const TStringBase& Other) const
        {
            return Equals(Other, ESearchCase::IgnoreCase);
        }

        [[nodiscard]] bool operator==(const CharType* Other) const
        {
            if (!Other) return IsEmpty();
            return TCString<CharType>::Strcmp(Data.GetData(), Other) == 0;
        }

        // Appending
        void AppendChars(const CharType* Str, int32 Count)
        {
            CheckInvariants();
            if (Str && Count > 0)
            {
                const int32 OldNum = Data.Num();

                // Reserve enough space - including an extra gap for a null terminator if we don't already have a string allocated
                Data.AddUninitialized(Count + (OldNum ? 0 : 1));

                CharType* Dest = Data.GetData() + OldNum - (OldNum ? 1 : 0);

                // Copy characters to end of string, overwriting null terminator if we already have one
                std::memcpy(Dest, Str, Count * sizeof(CharType));

                // (Re-)establish the null terminator
                Dest[Count] = CharType('\0');
            }
        }

        TStringBase& Append(const CharType* Str, int32 Count)
        {
            AppendChars(Str, Count);
            return *this;
        }

        TStringBase& Append(const CharType* Str)
        {
            if (Str)
            {
                AppendChars(Str, TCString<CharType>::Strlen(Str));
            }
            return *this;
        }

        TStringBase& Append(const TStringBase& Str)
        {
            AppendChars(Str.Data.GetData(), Str.Len());
            return *this;
        }

        TStringBase& AppendChar(CharType InChar)
        {
            CheckInvariants();
            
            if (Data.Num())
            {
                Data[Data.Num() - 1] = InChar;
            }
            else
            {
                Data.Add(InChar);
            }
            Data.Add(CharType('\0'));
            
            return *this;
        }

        TStringBase& operator+=(const CharType* Str)
        {
            return Append(Str);
        }

        TStringBase& operator+=(const TStringBase& Str)
        {
            return Append(Str);
        }

        TStringBase& operator+=(CharType Char)
        {
            return AppendChar(Char);
        }

        // Searching
        [[nodiscard]] int32 Find(const CharType* SubStr, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase,
                   ESearchDir::Type SearchDir = ESearchDir::FromStart, int32 StartPosition = INDEX_NONE) const
        {
            if (!SubStr || !*SubStr)
            {
                return INDEX_NONE;
            }

            const CharType* Start = Data.GetData();
            if (!Start || Len() == 0)
            {
                return INDEX_NONE;
            }

            int32 SubStrLen = TCString<CharType>::Strlen(SubStr);
            int32 StrLen = Len();

            if (SubStrLen > StrLen)
            {
                return INDEX_NONE;
            }

            if (SearchDir == ESearchDir::FromStart)
            {
                const CharType* SearchStart = (StartPosition != INDEX_NONE && StartPosition >= 0) ? Start + StartPosition : Start;
                
                if (SearchCase == ESearchCase::CaseSensitive)
                {
                    for (const CharType* Pos = SearchStart; Pos <= Start + StrLen - SubStrLen; ++Pos)
                    {
                        if (TCString<CharType>::Strncmp(Pos, SubStr, SubStrLen) == 0)
                        {
                            return static_cast<int32>(Pos - Start);
                        }
                    }
                }
                else
                {
                    for (const CharType* Pos = SearchStart; Pos <= Start + StrLen - SubStrLen; ++Pos)
                    {
                        if (TCString<CharType>::Strnicmp(Pos, SubStr, SubStrLen) == 0)
                        {
                            return static_cast<int32>(Pos - Start);
                        }
                    }
                }
            }
            else
            {
                const CharType* SearchStart = (StartPosition != INDEX_NONE && StartPosition < StrLen) ? 
                    Start + StartPosition : Start + StrLen - SubStrLen;
                
                if (SearchCase == ESearchCase::CaseSensitive)
                {
                    for (const CharType* Pos = SearchStart; Pos >= Start; --Pos)
                    {
                        if (TCString<CharType>::Strncmp(Pos, SubStr, SubStrLen) == 0)
                        {
                            return static_cast<int32>(Pos - Start);
                        }
                    }
                }
                else
                {
                    for (const CharType* Pos = SearchStart; Pos >= Start; --Pos)
                    {
                        if (TCString<CharType>::Strnicmp(Pos, SubStr, SubStrLen) == 0)
                        {
                            return static_cast<int32>(Pos - Start);
                        }
                    }
                }
            }

            return INDEX_NONE;
        }

        [[nodiscard]] int32 Find(const TStringBase& SubStr, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase,
                   ESearchDir::Type SearchDir = ESearchDir::FromStart, int32 StartPosition = INDEX_NONE) const
        {
            return Find(SubStr.Data.GetData(), SearchCase, SearchDir, StartPosition);
        }

        [[nodiscard]] FORCEINLINE bool Contains(const CharType* SubStr, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase,
                     ESearchDir::Type SearchDir = ESearchDir::FromStart) const
        {
            return Find(SubStr, SearchCase, SearchDir) != INDEX_NONE;
        }

        [[nodiscard]] FORCEINLINE bool Contains(const TStringBase& SubStr, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase,
                     ESearchDir::Type SearchDir = ESearchDir::FromStart) const
        {
            return Find(SubStr, SearchCase, SearchDir) != INDEX_NONE;
        }

        /**
         * Searches the string for a character
         *
         * @param InChar the character to search for
         * @param OutIndex out the position the character was found at, INDEX_NONE if return is false
         * @return true if character was found in this string, otherwise false
         */
        FORCEINLINE bool FindChar(CharType InChar, int32& OutIndex) const
        {
            return Data.Find(InChar, OutIndex);
        }

        /**
         * Searches the string for the last occurrence of a character
         *
         * @param InChar the character to search for
         * @param OutIndex out the position the character was found at, INDEX_NONE if return is false
         * @return true if character was found in this string, otherwise false
         */
        FORCEINLINE bool FindLastChar(CharType InChar, int32& OutIndex) const
        {
            return Data.FindLast(InChar, OutIndex);
        }

        // String tests
        [[nodiscard]] bool StartsWith(const CharType* InPrefix, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const
        {
            if (!InPrefix || !*InPrefix)
            {
                return true;
            }

            int32 PrefixLen = TCString<CharType>::Strlen(InPrefix);
            if (PrefixLen > Len())
            {
                return false;
            }

            if (SearchCase == ESearchCase::CaseSensitive)
            {
                return TCString<CharType>::Strncmp(Data.GetData(), InPrefix, PrefixLen) == 0;
            }
            else
            {
                return TCString<CharType>::Strnicmp(Data.GetData(), InPrefix, PrefixLen) == 0;
            }
        }

        [[nodiscard]] bool StartsWith(const TStringBase& InPrefix, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const
        {
            return StartsWith(InPrefix.Data.GetData(), SearchCase);
        }

        [[nodiscard]] bool EndsWith(const CharType* InSuffix, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const
        {
            if (!InSuffix || !*InSuffix)
            {
                return true;
            }

            int32 SuffixLen = TCString<CharType>::Strlen(InSuffix);
            if (SuffixLen > Len())
            {
                return false;
            }

            const CharType* Start = Data.GetData() + (Len() - SuffixLen);
            
            if (SearchCase == ESearchCase::CaseSensitive)
            {
                return TCString<CharType>::Strncmp(Start, InSuffix, SuffixLen) == 0;
            }
            else
            {
                return TCString<CharType>::Strnicmp(Start, InSuffix, SuffixLen) == 0;
            }
        }

        [[nodiscard]] bool EndsWith(const TStringBase& InSuffix, ESearchCase::Type SearchCase = ESearchCase::IgnoreCase) const
        {
            return EndsWith(InSuffix.Data.GetData(), SearchCase);
        }

        // Case conversion
        void ToUpperInline()
        {
            for (int32 i = 0; i < Len(); ++i)
            {
                Data[i] = TChar<CharType>::ToUpper(Data[i]);
            }
        }

        void ToLowerInline()
        {
            for (int32 i = 0; i < Len(); ++i)
            {
                Data[i] = TChar<CharType>::ToLower(Data[i]);
            }
        }

        void ReverseInline()
        {
            int32 StrLen = Len();
            if (StrLen > 1)
            {
                for (int32 i = 0; i < StrLen / 2; ++i)
                {
                    CharType Temp = Data[i];
                    Data[i] = Data[StrLen - 1 - i];
                    Data[StrLen - 1 - i] = Temp;
                }
            }
        }

        [[nodiscard]] bool IsNumeric() const
        {
            if (Len() == 0)
            {
                return false;
            }
            
            const CharType* Str = Data.GetData();
            
            if (*Str == CharType('-') || *Str == CharType('+'))
            {
                Str++;
                if (!*Str)
                {
                    return false;
                }
            }
            
            bool bHasDot = false;
            bool bHasDigit = false;
            
            while (*Str)
            {
                if (*Str == CharType('.'))
                {
                    if (bHasDot)
                    {
                        return false;
                    }
                    bHasDot = true;
                }
                else if (TChar<CharType>::IsDigit(*Str))
                {
                    bHasDigit = true;
                }
                else
                {
                    return false;
                }
                Str++;
            }
            
            return bHasDigit;
        }
    };

    // GetData overloads for any TStringBase specialization
    template<typename CharType>
    [[nodiscard]] inline CharType* GetData(TStringBase<CharType>& String)
    {
        return String.GetCharArray().GetData();
    }

    template<typename CharType>
    [[nodiscard]] inline const CharType* GetData(const TStringBase<CharType>& String)
    {
        return String.GetCharArray().GetData();
    }

    // GetNum overload for any TStringBase specialization
    template<typename CharType>
    [[nodiscard]] inline int32 GetNum(const TStringBase<CharType>& String)
    {
        return String.Len();
    }
}