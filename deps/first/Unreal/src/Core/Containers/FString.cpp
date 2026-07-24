#define NOMINMAX

#include <Unreal/FString.hpp>
#include <Unreal/FMemory.hpp>
#include <Unreal/Core/Misc/VarArgs.hpp>
#include <Unreal/Core/Math/UnrealMathUtility.hpp>

namespace RC::Unreal
{
    FStringOut::FStringOut(const FStringOut& Other)
    {
        Data = Other.Data;
    }

    FStringOut::FStringOut(FStringOut&& Other) noexcept
    {
        Data = Other.Data;
        Other.Data.SetNum(0);
        Other.Data.SetDataPtr(nullptr);
    }

    FStringOut::~FStringOut() = default;

#define STARTING_BUFFER_SIZE 512

    FString FString::Printf(const TCHAR* Format, ...)
    {
        int32 BufferSize = STARTING_BUFFER_SIZE;
        TCHAR StartingBuffer[STARTING_BUFFER_SIZE];
        TCHAR* Buffer = StartingBuffer;
        int32 Result = -1;

        GET_TYPED_VARARGS_RESULT(TCHAR, Buffer, BufferSize, BufferSize-1, Format, Format, Result);

        if (Result == -1)
        {
            Buffer = nullptr;
            while (Result == -1)
            {
                BufferSize *= 2;
                Buffer = (TCHAR*)FMemory::Realloc(Buffer, BufferSize * sizeof(TCHAR));
                GET_TYPED_VARARGS_RESULT(TCHAR, Buffer, BufferSize, BufferSize-1, Format, Format, Result);
            }
        }

        Buffer[Result] = TEXT('\0');
        FString ResultString(Buffer);

        if (BufferSize != STARTING_BUFFER_SIZE)
        {
            FMemory::Free(Buffer);
        }

        return ResultString;
    }
    
    FString& FString::Appendf(const TCHAR* Format, ...)
    {
        int32 BufferSize = STARTING_BUFFER_SIZE;
        TCHAR StartingBuffer[STARTING_BUFFER_SIZE];
        TCHAR* Buffer = StartingBuffer;
        int32 Result = -1;

        GET_TYPED_VARARGS_RESULT(TCHAR, Buffer, BufferSize, BufferSize-1, Format, Format, Result);

        if (Result == -1)
        {
            Buffer = nullptr;
            while (Result == -1)
            {
                BufferSize *= 2;
                Buffer = (TCHAR*)FMemory::Realloc(Buffer, BufferSize * sizeof(TCHAR));
                GET_TYPED_VARARGS_RESULT(TCHAR, Buffer, BufferSize, BufferSize-1, Format, Format, Result);
            }
        }

        Buffer[Result] = TEXT('\0');
        *this += Buffer;

        if (BufferSize != STARTING_BUFFER_SIZE)
        {
            FMemory::Free(Buffer);
        }

        return *this;
    }

    FString& FString::AppendInt(int32 InNum)
    {
        return Appendf(TEXT("%d"), InNum);
    }

    FString FString::FromInt(int32 InNum)
    {
        return Printf(TEXT("%d"), InNum);
    }

    FString FString::Left(int32 Count) const
    {
        FString Result;
        if (Count > 0 && Len() > 0)
        {
            Count = FGenericPlatformMath::Min(Count, Len());
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData(), Count * sizeof(TCHAR));
            Result.Data[Count] = TEXT('\0');
        }
        return Result;
    }

    FString FString::Right(int32 Count) const
    {
        FString Result;
        if (Count > 0 && Len() > 0)
        {
            Count = FGenericPlatformMath::Min(Count, Len());
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData() + (Len() - Count), Count * sizeof(TCHAR));
            Result.Data[Count] = TEXT('\0');
        }
        return Result;
    }

    FString FString::Mid(int32 Start, int32 Count) const
    {
        FString Result;
        int32 StrLen = Len();
        
        if (Start >= 0 && Start < StrLen && Count > 0)
        {
            Count = FGenericPlatformMath::Min(Count, StrLen - Start);
            Result.Data.AddUninitialized(Count + 1);
            std::memcpy(Result.Data.GetData(), Data.GetData() + Start, Count * sizeof(TCHAR));
            Result.Data[Count] = TEXT('\0');
        }
        return Result;
    }

    FString FString::Replace(const TCHAR* SearchText, const TCHAR* ReplacementText, 
                             ESearchCase::Type SearchCase) const
    {
        FString Result(*this);
        Result.ReplaceInline(SearchText, ReplacementText, SearchCase);
        return Result;
    }

    int32 FString::ReplaceInline(const TCHAR* SearchText, const TCHAR* ReplacementText,
                                 ESearchCase::Type SearchCase)
    {
        if (!SearchText || !*SearchText)
        {
            return 0;
        }

        int32 SearchTextLen = TCString<TCHAR>::Strlen(SearchText);
        int32 ReplacementTextLen = ReplacementText ? TCString<TCHAR>::Strlen(ReplacementText) : 0;
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
                TArray<TCHAR> NewData;
                NewData.AddUninitialized(NewLen + 1);
                
                int32 SrcPos = 0;
                int32 DstPos = 0;
                
                for (int32 i = 0; i < Positions.Num(); ++i)
                {
                    int32 ReplacePos = Positions[i];
                    
                    int32 CopyLen = ReplacePos - SrcPos;
                    if (CopyLen > 0)
                    {
                        std::memcpy(NewData.GetData() + DstPos, Data.GetData() + SrcPos, CopyLen * sizeof(TCHAR));
                        DstPos += CopyLen;
                    }
                    
                    if (ReplacementTextLen > 0)
                    {
                        std::memcpy(NewData.GetData() + DstPos, ReplacementText, ReplacementTextLen * sizeof(TCHAR));
                        DstPos += ReplacementTextLen;
                    }
                    
                    SrcPos = ReplacePos + SearchTextLen;
                }
                
                int32 RemainingLen = OldLen - SrcPos;
                if (RemainingLen > 0)
                {
                    std::memcpy(NewData.GetData() + DstPos, Data.GetData() + SrcPos, RemainingLen * sizeof(TCHAR));
                }
                
                NewData[NewLen] = TEXT('\0');
                Data = MoveTemp(NewData);
            }
            else
            {
                for (int32 i = Positions.Num() - 1; i >= 0; --i)
                {
                    std::memcpy(Data.GetData() + Positions[i], ReplacementText, ReplacementTextLen * sizeof(TCHAR));
                }
            }
        }
        
        return NumReplacements;
    }

    FString FString::ToUpper() const
    {
        FString Result(*this);
        Result.ToUpperInline();
        return Result;
    }

    FString FString::ToLower() const
    {
        FString Result(*this);
        Result.ToLowerInline();
        return Result;
    }

    FString FString::TrimStart() const
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

    FString FString::TrimEnd() const
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

    FString FString::TrimStartAndEnd() const
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

    int32 FString::Split(const TCHAR* InS, TArray<FString>& OutArray, bool InCullEmpty) const
    {
        OutArray.Empty();
        
        if (!InS || !*InS)
        {
            OutArray.Add(*this);
            return 1;
        }
        
        int32 DelimLen = TCString<TCHAR>::Strlen(InS);
        int32 StartPos = 0;
        int32 FoundPos;
        
        while ((FoundPos = Find(InS, ESearchCase::CaseSensitive, ESearchDir::FromStart, StartPos)) != INDEX_NONE)
        {
            FString SubStr = Mid(StartPos, FoundPos - StartPos);
            if (!InCullEmpty || SubStr.Len() > 0)
            {
                OutArray.Add(MoveTemp(SubStr));
            }
            StartPos = FoundPos + DelimLen;
        }
        
        FString Remaining = Mid(StartPos);
        if (!InCullEmpty || Remaining.Len() > 0)
        {
            OutArray.Add(MoveTemp(Remaining));
        }
        
        return OutArray.Num();
    }

    FString FString::Reverse() const
    {
        FString Result;
        int32 StrLen = Len();
        
        if (StrLen > 0)
        {
            Result.Data.AddUninitialized(StrLen + 1);
            
            for (int32 i = 0; i < StrLen; ++i)
            {
                Result.Data[i] = Data[StrLen - 1 - i];
            }
            
            Result.Data[StrLen] = TEXT('\0');
        }
        
        return Result;
    }

#undef STARTING_BUFFER_SIZE
}