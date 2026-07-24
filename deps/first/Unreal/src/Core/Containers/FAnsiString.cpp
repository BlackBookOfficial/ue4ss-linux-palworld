#include <Unreal/Core/Containers/FAnsiString.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/Core/Math/UnrealMathUtility.hpp>
#include <Unreal/Core/Containers/StringConv.hpp>

namespace RC::Unreal
{
    FAnsiString::FAnsiString(const FString& Str)
    {
        // Convert from TCHAR to ANSI
        if (!Str.IsEmpty())
        {
            auto Converted = StringCast<ANSICHAR>(*Str, Str.Len());
            int32 ConvertedLen = Converted.Length();
            
            Data.AddUninitialized(ConvertedLen + 1);
            std::memcpy(Data.GetData(), Converted.Get(), ConvertedLen * sizeof(ANSICHAR));
            Data[ConvertedLen] = ANSICHAR('\0');
        }
    }
    
    FAnsiString FAnsiString::Left(int32 Count) const
    {
        FAnsiString Result;
        if (Count > 0 && Len() > 0)
        {
            Count = FGenericPlatformMath::Min(Count, Len());
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData(), Count * sizeof(ANSICHAR));
            Result.Data[Count] = ANSICHAR('\0');
        }
        return Result;
    }
    FAnsiString FAnsiString::Right(int32 Count) const
    {
        FAnsiString Result;
        if (Count > 0 && Len() > 0)
        {
            Count = FGenericPlatformMath::Min(Count, Len());
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData() + (Len() - Count), Count * sizeof(ANSICHAR));
            Result.Data[Count] = ANSICHAR('\0');
        }
        return Result;
    }

    FAnsiString FAnsiString::Mid(int32 Start, int32 Count) const
    {
        FAnsiString Result;
        int32 StrLen = Len();
        
        if (Start >= 0 && Start < StrLen && Count > 0)
        {
            Count = FGenericPlatformMath::Min(Count, StrLen - Start);
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData() + Start, Count * sizeof(ANSICHAR));
            Result.Data[Count] = ANSICHAR('\0');
        }
        return Result;
    }

    FAnsiString FAnsiString::Replace(const ANSICHAR* SearchText, const ANSICHAR* ReplacementText, 
                                     ESearchCase::Type SearchCase) const
    {
        FAnsiString Result(*this);
        Result.ReplaceInline(SearchText, ReplacementText, SearchCase);
        return Result;
    }

    int32 FAnsiString::ReplaceInline(const ANSICHAR* SearchText, const ANSICHAR* ReplacementText,
                                     ESearchCase::Type SearchCase)
    {
        if (!SearchText || !*SearchText)
        {
            return 0;
        }

        int32 SearchTextLen = TCString<ANSICHAR>::Strlen(SearchText);
        int32 ReplacementTextLen = ReplacementText ? TCString<ANSICHAR>::Strlen(ReplacementText) : 0;
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
                TArray<ANSICHAR> NewData;
                NewData.AddUninitialized(NewLen + 1);
                
                int32 SrcPos = 0;
                int32 DstPos = 0;
                
                for (int32 i = 0; i < Positions.Num(); ++i)
                {
                    int32 ReplacePos = Positions[i];
                    
                    int32 CopyLen = ReplacePos - SrcPos;
                    if (CopyLen > 0)
                    {
                        std::memcpy(NewData.GetData() + DstPos, Data.GetData() + SrcPos, CopyLen * sizeof(ANSICHAR));
                        DstPos += CopyLen;
                    }
                    
                    if (ReplacementTextLen > 0)
                    {
                        std::memcpy(NewData.GetData() + DstPos, ReplacementText, ReplacementTextLen * sizeof(ANSICHAR));
                        DstPos += ReplacementTextLen;
                    }
                    
                    SrcPos = ReplacePos + SearchTextLen;
                }
                
                int32 RemainingLen = OldLen - SrcPos;
                if (RemainingLen > 0)
                {
                    std::memcpy(NewData.GetData() + DstPos, Data.GetData() + SrcPos, RemainingLen * sizeof(ANSICHAR));
                }
                
                NewData[NewLen] = ANSICHAR('\0');
                Data = MoveTemp(NewData);
            }
            else
            {
                for (int32 i = Positions.Num() - 1; i >= 0; --i)
                {
                    std::memcpy(Data.GetData() + Positions[i], ReplacementText, ReplacementTextLen * sizeof(ANSICHAR));
                }
            }
        }
        
        return NumReplacements;
    }

    FAnsiString FAnsiString::ToUpper() const
    {
        FAnsiString Result(*this);
        Result.ToUpperInline();
        return Result;
    }

    FAnsiString FAnsiString::ToLower() const
    {
        FAnsiString Result(*this);
        Result.ToLowerInline();
        return Result;
    }

    FAnsiString FAnsiString::TrimStart() const
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

    FAnsiString FAnsiString::TrimEnd() const
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

    FAnsiString FAnsiString::TrimStartAndEnd() const
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

    int32 FAnsiString::Split(const ANSICHAR* InS, TArray<FAnsiString>& OutArray, bool InCullEmpty) const
    {
        OutArray.Empty();
        
        if (!InS || !*InS)
        {
            OutArray.Add(*this);
            return 1;
        }
        
        int32 DelimLen = TCString<ANSICHAR>::Strlen(InS);
        int32 StartPos = 0;
        int32 FoundPos;
        
        while ((FoundPos = Find(InS, ESearchCase::CaseSensitive, ESearchDir::FromStart, StartPos)) != INDEX_NONE)
        {
            FAnsiString SubStr = Mid(StartPos, FoundPos - StartPos);
            if (!InCullEmpty || SubStr.Len() > 0)
            {
                OutArray.Add(MoveTemp(SubStr));
            }
            StartPos = FoundPos + DelimLen;
        }
        
        FAnsiString Remaining = Mid(StartPos);
        if (!InCullEmpty || Remaining.Len() > 0)
        {
            OutArray.Add(MoveTemp(Remaining));
        }
        
        return OutArray.Num();
    }

    FAnsiString FAnsiString::Reverse() const
    {
        FAnsiString Result;
        int32 StrLen = Len();
        
        if (StrLen > 0)
        {
            Result.Data.AddUninitialized(StrLen + 1);
            
            for (int32 i = 0; i < StrLen; ++i)
            {
                Result.Data[i] = Data[StrLen - 1 - i];
            }
            
            Result.Data[StrLen] = ANSICHAR('\0');
        }
        
        return Result;
    }
}