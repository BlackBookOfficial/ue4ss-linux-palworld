#include <Unreal/Core/Containers/FUtf8String.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/Core/Math/UnrealMathUtility.hpp>
#include <Unreal/Core/Containers/StringConv.hpp>

namespace RC::Unreal
{
    FUtf8String::FUtf8String(const FString& Str)
    {
        // Convert from TCHAR to UTF8
        if (!Str.IsEmpty())
        {
            auto Converted = StringCast<UTF8CHAR>(*Str, Str.Len());
            int32 ConvertedLen = Converted.Length();
            
            Data.AddUninitialized(ConvertedLen + 1);
            std::memcpy(Data.GetData(), Converted.Get(), ConvertedLen * sizeof(UTF8CHAR));
            Data[ConvertedLen] = UTF8CHAR('\0');
        }
    }

    FUtf8String FUtf8String::Left(int32 Count) const
    {
        FUtf8String Result;
        if (Count > 0 && Len() > 0)
        {
            Count = FGenericPlatformMath::Min(Count, Len());
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData(), Count * sizeof(UTF8CHAR));
            Result.Data[Count] = UTF8CHAR('\0');
        }
        return Result;
    }

    FUtf8String FUtf8String::Right(int32 Count) const
    {
        FUtf8String Result;
        if (Count > 0 && Len() > 0)
        {
            Count = FGenericPlatformMath::Min(Count, Len());
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData() + (Len() - Count), Count * sizeof(UTF8CHAR));
            Result.Data[Count] = UTF8CHAR('\0');
        }
        return Result;
    }

    FUtf8String FUtf8String::Mid(int32 Start, int32 Count) const
    {
        FUtf8String Result;
        int32 StrLen = Len();
        
        if (Start >= 0 && Start < StrLen && Count > 0)
        {
            Count = FGenericPlatformMath::Min(Count, StrLen - Start);
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData() + Start, Count * sizeof(UTF8CHAR));
            Result.Data[Count] = UTF8CHAR('\0');
        }
        return Result;
    }

    FUtf8String FUtf8String::Replace(const UTF8CHAR* SearchText, const UTF8CHAR* ReplacementText, 
                                     ESearchCase::Type SearchCase) const
    {
        FUtf8String Result(*this);
        Result.ReplaceInline(SearchText, ReplacementText, SearchCase);
        return Result;
    }

    int32 FUtf8String::ReplaceInline(const UTF8CHAR* SearchText, const UTF8CHAR* ReplacementText,
                                     ESearchCase::Type SearchCase)
    {
        if (!SearchText || !*SearchText)
        {
            return 0;
        }

        int32 SearchTextLen = TCString<UTF8CHAR>::Strlen(SearchText);
        int32 ReplacementTextLen = ReplacementText ? TCString<UTF8CHAR>::Strlen(ReplacementText) : 0;
        int32 NumReplacements = 0;

        TArray<int32> Positions;
        int32 Pos = 0;
        while ((Pos = Find(SearchText, SearchCase, ESearchDir::FromStart, Pos)) != INDEX_NONE)
        {
            Positions.Add(Pos);
            Pos += SearchTextLen;
        }

        NumReplacements = Positions.Num();
        
        if (NumReplacements > 0)
        {
            int32 OldLen = Len();
            int32 NewLen = OldLen + (ReplacementTextLen - SearchTextLen) * NumReplacements;
            
            if (NewLen != OldLen)
            {
                TArray<UTF8CHAR> NewData;
                NewData.AddUninitialized(NewLen + 1);
                
                int32 SrcPos = 0;
                int32 DstPos = 0;
                
                for (int32 i = 0; i < Positions.Num(); ++i)
                {
                    int32 ReplacePos = Positions[i];
                    
                    int32 CopyLen = ReplacePos - SrcPos;
                    if (CopyLen > 0)
                    {
                        std::memcpy(NewData.GetData() + DstPos, Data.GetData() + SrcPos, CopyLen * sizeof(UTF8CHAR));
                        DstPos += CopyLen;
                    }
                    
                    if (ReplacementTextLen > 0)
                    {
                        std::memcpy(NewData.GetData() + DstPos, ReplacementText, ReplacementTextLen * sizeof(UTF8CHAR));
                        DstPos += ReplacementTextLen;
                    }
                    
                    SrcPos = ReplacePos + SearchTextLen;
                }
                
                int32 RemainingLen = OldLen - SrcPos;
                if (RemainingLen > 0)
                {
                    std::memcpy(NewData.GetData() + DstPos, Data.GetData() + SrcPos, RemainingLen * sizeof(UTF8CHAR));
                }
                
                NewData[NewLen] = UTF8CHAR('\0');
                Data = MoveTemp(NewData);
            }
            else
            {
                for (int32 i = Positions.Num() - 1; i >= 0; --i)
                {
                    std::memcpy(Data.GetData() + Positions[i], ReplacementText, ReplacementTextLen * sizeof(UTF8CHAR));
                }
            }
        }
        
        return NumReplacements;
    }

    FUtf8String FUtf8String::ToUpper() const
    {
        FUtf8String Result(*this);
        Result.ToUpperInline();
        return Result;
    }

    FUtf8String FUtf8String::ToLower() const
    {
        FUtf8String Result(*this);
        Result.ToLowerInline();
        return Result;
    }

    FUtf8String FUtf8String::TrimStart() const
    {
        int32 StartIndex = 0;
        while (StartIndex < Len() && FChar::IsWhitespace(Data[StartIndex]))
        {
            ++StartIndex;
        }
        
        if (StartIndex == 0)
        {
            return *this;
        }
        
        return Mid(StartIndex);
    }

    FUtf8String FUtf8String::TrimEnd() const
    {
        int32 EndIndex = Len() - 1;
        while (EndIndex >= 0 && FChar::IsWhitespace(Data[EndIndex]))
        {
            --EndIndex;
        }
        
        if (EndIndex == Len() - 1)
        {
            return *this;
        }
        
        return Left(EndIndex + 1);
    }

    FUtf8String FUtf8String::TrimStartAndEnd() const
    {
        int32 StartIndex = 0;
        while (StartIndex < Len() && FChar::IsWhitespace(Data[StartIndex]))
        {
            ++StartIndex;
        }
        
        int32 EndIndex = Len() - 1;
        while (EndIndex >= StartIndex && FChar::IsWhitespace(Data[EndIndex]))
        {
            --EndIndex;
        }
        
        if (StartIndex == 0 && EndIndex == Len() - 1)
        {
            return *this;
        }
        
        return Mid(StartIndex, EndIndex - StartIndex + 1);
    }

    int32 FUtf8String::Split(const UTF8CHAR* InS, TArray<FUtf8String>& OutArray, bool InCullEmpty) const
    {
        OutArray.Empty();
        
        if (!InS || !*InS)
        {
            OutArray.Add(*this);
            return 1;
        }
        
        int32 DelimLen = TCString<UTF8CHAR>::Strlen(InS);
        int32 StartPos = 0;
        int32 FoundPos;
        
        while ((FoundPos = Find(InS, ESearchCase::CaseSensitive, ESearchDir::FromStart, StartPos)) != INDEX_NONE)
        {
            FUtf8String SubStr = Mid(StartPos, FoundPos - StartPos);
            if (!InCullEmpty || SubStr.Len() > 0)
            {
                OutArray.Add(MoveTemp(SubStr));
            }
            StartPos = FoundPos + DelimLen;
        }
        
        FUtf8String Remaining = Mid(StartPos);
        if (!InCullEmpty || Remaining.Len() > 0)
        {
            OutArray.Add(MoveTemp(Remaining));
        }
        
        return OutArray.Num();
    }

    FUtf8String FUtf8String::Reverse() const
    {
        FUtf8String Result;
        int32 StrLen = Len();
        
        if (StrLen > 0)
        {
            Result.Data.AddUninitialized(StrLen + 1);
            
            for (int32 i = 0; i < StrLen; ++i)
            {
                Result.Data[i] = Data[StrLen - 1 - i];
            }
            
            Result.Data[StrLen] = UTF8CHAR('\0');
        }
        
        return Result;
    }
}