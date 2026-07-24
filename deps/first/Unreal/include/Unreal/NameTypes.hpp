#pragma once

#include <string>

#include <Function/Function.hpp>
#include <Unreal/Common.hpp>
#include <Unreal/Core/HAL/Platform.hpp>
#include <Unreal/FArchive.hpp>
#include <Unreal/Core/Misc/AssertionMacros.hpp>
#include <Unreal/Core/Templates/UnrealTemplate.hpp>
#include <Unreal/Core/Misc/IntrusiveUnsetOptionalState.hpp>

#include <String/StringType.hpp>
#include <Unreal/UnrealVersion.hpp>

#define INVALID_LONGPACKAGE_CHARACTERS TEXT("\\:*?\"<>|' ,.&!~\n\r\t@#")

namespace RC::Unreal
{
    class FUtf8String;
    class FAnsiString;
    class FString;
    
    namespace UnrealInitializer
    {
        struct CacheInfo;
        RC_UE_API auto CreateCache(UnrealInitializer::CacheInfo& Target) -> void;
    }

    enum {NAME_SIZE    = 1024};

    enum EFindName
    {
        FNAME_Find,
        FNAME_Add,
        FNAME_Replace_Not_Safe_For_Threading
    };

    enum class ENameCase : uint8
    {
        CaseSensitive,
        IgnoreCase
    };

    /** Opaque id to a deduplicated name */
    struct FNameEntryId
    {
        constexpr static bool bHasIntrusiveUnsetOptionalState = true;
        using IntrusiveUnsetOptionalStateType = FNameEntryId;
        
        // Default initialize to be equal to NAME_None
        constexpr FNameEntryId() : Value(0) {}
        constexpr FNameEntryId(ENoInit) {}
        constexpr explicit FNameEntryId(FIntrusiveUnsetOptionalState) : Value(~0u) {}

        enum EName
        {
            NAME_None
        };

      
        bool IsNone() const
        {
            return Value == 0;
        }

        /** Slow alphabetical order that is stable / deterministic over process runs */
        int32 CompareLexical(FNameEntryId Rhs) const;
        bool LexicalLess(FNameEntryId Rhs) const { return CompareLexical(Rhs) < 0; }

        /** Fast non-alphabetical order that is only stable during this process' lifetime */
        int32 CompareFast(FNameEntryId Rhs) const { return Value - Rhs.Value; };
        bool FastLess(FNameEntryId Rhs) const { return CompareFast(Rhs) < 0; }

        /** Fast non-alphabetical order that is only stable during this process' lifetime */
        bool operator<(FNameEntryId Rhs) const { return Value < Rhs.Value; }

        /** Fast non-alphabetical order that is only stable during this process' lifetime */
        bool operator>(FNameEntryId Rhs) const { return Rhs.Value < Value; }
        bool operator==(FNameEntryId Rhs) const { return Value == Rhs.Value; }
        bool operator!=(FNameEntryId Rhs) const { return Value != Rhs.Value; }

        // Returns true if this FNameEntryId is not equivalent to NAME_None
        explicit operator bool() const { return Value != 0; }

        /**
         * Implicit conversion to uint32 for backwards compatibility
         * @deprecated Use ToUnstableInt() instead to make it explicit that this is a process-specific unstable integer
         */
        [[deprecated("Use ToUnstableInt() instead - this implicit conversion will be removed in a future version")]]
        operator uint32() const { return Value; }

        /** Get process specific integer */
        uint32 ToUnstableInt() const { return Value; }

        /** Create from unstable int produced by this process */
        static FNameEntryId FromUnstableInt(uint32 UnstableInt)
        {
            FNameEntryId Id;
            Id.Value = UnstableInt;
            return Id;
        }

        FORCEINLINE static FNameEntryId FromEName(EName Ename)
        {
            return Ename == NAME_None ? FNameEntryId() : FromValidEName(Ename);
        }

        friend inline bool operator==(FNameEntryId Id, EName Ename)
        {
            return Ename == NAME_None ? !Id : Id == FromValidENamePostInit(Ename);
        }

        private:
        uint32 Value;

        static FNameEntryId FromValidEName(EName Ename);
        static FNameEntryId FromValidENamePostInit(EName Ename);

        public:
        friend inline bool operator==(EName Ename, FNameEntryId Id) { return Id == Ename; }
        friend inline bool operator!=(EName Ename, FNameEntryId Id) { return !(Id == Ename); }
        friend inline bool operator!=(FNameEntryId Id, EName Ename) { return !(Id == Ename); }
        friend CORE_API uint32 GetTypeHash(FNameEntryId Id);

        /** Serialize as process specific unstable int */
        friend FArchive& operator<<(FArchive& Ar, FNameEntryId& InId);
    };

    /**
     * Legacy typedef - this is no longer an index
     *
     * Use GetTypeHash(FName) or GetTypeHash(FNameEntryId) for hashing
     * To compare with ENames use FName(EName) or FName::ToEName() instead
     */
    typedef FNameEntryId NAME_INDEX;

    #define checkName checkSlow

    /** Externally, the instance number to represent no instance number is NAME_NO_NUMBER, 
    but internally, we add 1 to indices, so we use this #define internally for 
    zero'd memory initialization will still make NAME_None as expected */
#define NAME_NO_NUMBER_INTERNAL    0

    /** Conversion routines between external representations and internal */
#define NAME_INTERNAL_TO_EXTERNAL(x) (x - 1)
#define NAME_EXTERNAL_TO_INTERNAL(x) (x + 1)

    /** Special value for an FName with no number */
#define NAME_NO_NUMBER NAME_INTERNAL_TO_EXTERNAL(NAME_NO_NUMBER_INTERNAL)


    /** Remember to update natvis if you change these */
    static constexpr uint32 FNameMaxBlockBits = 13; // Limit block array a bit, still allowing 8k * block size = 1GB - 2G of FName entry data
    static constexpr uint32 FNameBlockOffsetBits = 16;
    static constexpr uint32 FNameMaxBlocks = 1 << FNameMaxBlockBits;
    static constexpr uint32 FNameBlockOffsets = 1 << FNameBlockOffsetBits;
    static constexpr uint32 FNameEntryIdBits = FNameBlockOffsetBits + FNameMaxBlockBits;
    static constexpr uint32 FNameEntryIdMask = (1 << FNameEntryIdBits ) - 1;

    /*----------------------------------------------------------------------------
            FNameEntry.
    ----------------------------------------------------------------------------*/

    /** Implementation detail exposed for debug visualizers */
    struct FNameEntryHeader
    {
        uint16 bIsWide : 1;
    #if WITH_CASE_PRESERVING_NAME
        uint16 Len : 15;
    #else
        static constexpr inline uint32 ProbeHashBits = 5;
        uint16 LowercaseProbeHash : ProbeHashBits;
        uint16 Len : 10;
    #endif
    };

    /**
     * A global deduplicated name stored in the global name table.
     */
    struct FNameEntry
    {
    private:
    #if WITH_CASE_PRESERVING_NAME
        FNameEntryId ComparisonId;
    #endif
        FNameEntryHeader Header;

        // Unaligned to reduce alignment waste for non-numbered entries
        struct FNumberedData
        {
        #if UE_FNAME_OUTLINE_NUMBER    
        #if WITH_CASE_PRESERVING_NAME // ComparisonId is 4B-aligned, 4B-align Id/Number by 2B pad after 2B Header
            uint8 Pad[sizeof(Header) % alignof(decltype(ComparisonId))]; 
        #endif
            uint8 Id[sizeof(FNameEntryId)];
            uint8 Number[sizeof(uint32)];
        #endif // UE_FNAME_OUTLINE_NUMBER    
        };
    };

    // TODO:   Figure out what's going on here
    //         It shouldn't be required to use 'alignas' here to make sure it's aligned properly in containers (like TArray)
    //         I've never seen an FName not be 8-byte aligned in memory,
    //         but it is 4-byte aligned in the source so hopefully this doesn't cause any problems
    // UPDATE: This matters in the UE VM, when ElementSize is 0xC in memory for case-preserving games, it must be aligned by 0x4 in that case
#pragma warning(disable: 4324) // Suppressing warning about struct alignment

#ifndef FNAME_ALIGN8
    class alignas(4) RC_UE_API FName
#else
    class alignas(8) RC_UE_API FName
#endif
    {
    private:
        friend RC_UE_API auto UnrealInitializer::CreateCache(UnrealInitializer::CacheInfo& Target) -> void;

        FNameEntryId ComparisonIndex{};
#ifdef WITH_CASE_PRESERVING_NAME
        FNameEntryId DisplayIndex{};
#endif
        uint32 Number{};

    public:
        static Function<void(const FName*, class FStringOut&)> ToStringInternal;
        static UFunction* Conv_NameToStringInternal;
        static UObject* KismetStringLibraryCDO;
        static Function<FName(const CharType*, EFindName)> ConstructorInternal;

    private:
        auto construct_with_string(const CharType* StrName, EFindName FindType, void* FunctionAddressOverride) -> void
        {
            if (!ConstructorInternal.is_ready() && !FunctionAddressOverride) { return; }

            // Assign the temporary address if one exists
            if (FunctionAddressOverride) { ConstructorInternal.assign_temp_address(FunctionAddressOverride); }

            FName Name = ConstructorInternal(StrName, FindType);
            ComparisonIndex = Name.ComparisonIndex;
#ifdef WITH_CASE_PRESERVING_NAME
            DisplayIndex = Name.DisplayIndex;
#endif
            Number = Name.Number;

            // Reset the address to what it was before it was overridden by a temporary address
            if (FunctionAddressOverride) { ConstructorInternal.reset_address(); }
        }

        auto construct_with_string(const CharType* Name, uint32 InNumber, EFindName FindType, void* FunctionAddressOverride) -> void
        {
            construct_with_string(Name, FindType, FunctionAddressOverride);
            Number = InNumber;
        }

    public:
        FName() = default;

        // Construct from an existing FName without looking up
        // Safe to pass to Unreal Engine internals
        // Not safe to use for return values from Unreal Engine internals
        explicit FName(int64_t IndexAndNumber)
        {
            // Split the 64-bit integer into two 32-bit integers
            Number = (IndexAndNumber & 0xFFFFFFFF00000000LL) >> 32;
            ComparisonIndex = FNameEntryId::FromUnstableInt(static_cast<uint32>(IndexAndNumber & 0xFFFFFFFFLL));
#ifdef WITH_CASE_PRESERVING_NAME
            DisplayIndex = ComparisonIndex;
#endif
        }

        // Construct from an existing FName without looking up
        // Safe to pass to Unreal Engine internals
        // Not safe to use for return values from Unreal Engine internals
        explicit FName(uint32_t IndexParam, uint32_t NumberParam)
        {
            ComparisonIndex = FNameEntryId::FromUnstableInt(IndexParam);
#ifdef WITH_CASE_PRESERVING_NAME
            DisplayIndex = FNameEntryId::FromUnstableInt(IndexParam);
#endif
            Number = NumberParam;
        }

#ifdef WITH_CASE_PRESERVING_NAME
        // Construct from an existing FName without looking up
        // Safe to pass to Unreal Engine internals
        // Not safe to use for return values from Unreal Engine internals
        explicit FName(uint32_t IndexParam, uint32_t DisplayIndexParam, uint32_t NumberParam)
        {
            ComparisonIndex = IndexParam;
            DisplayIndex = DisplayIndexParam;
            Number = NumberParam;
        }
#endif

        // Create or lookup an FName from a string
        // Not safe to pass to Unreal Engine internals (may create unexpected name table entries with default FNAME_Add)
        // Safe to use for return values from Unreal Engine internals
        // Use FNAME_Find if you only want to lookup existing names without creating new ones
        explicit FName(const CharType* StrName, EFindName FindType = FNAME_Add, void* FunctionAddressOverride = nullptr)
        {
            construct_with_string(StrName, FindType, FunctionAddressOverride);
        }

        explicit FName(StringViewType str_name, EFindName FindType = FNAME_Add, void* FunctionAddressOverride = nullptr)
        {
            construct_with_string(str_name.data(), FindType, FunctionAddressOverride);
        }

        explicit FName(StringViewType Name, uint32 InNumber, EFindName FindType = FNAME_Add, void* FunctionAddressOverride = nullptr)
        {
            construct_with_string(Name.data(), InNumber, FindType, FunctionAddressOverride);
        }

        auto inline operator==(FName other) const -> bool
        {
            return ToUnstableInt() == other.ToUnstableInt();
        }

        auto inline operator==(const CharType* Other) -> bool
        {
            return ToString() == Other;
        }

        auto inline operator!=(FName Other) const -> bool
        {
            return !(*this == Other);
        }

        auto inline operator!() const -> bool
        {
            return IsNone();
        }

        // Returns whether the ComparisonIndex is equal
        // Use this when you don't care for an identical match
        // The operator overloads will make sure both ComparisonIndex and Number are equal
        [[nodiscard]] auto Equals(const FName& Other) const -> bool
        {
            return ComparisonIndex == Other.ComparisonIndex;
        }

        // Check to see if this FName matches the other FName, potentially also checking for any case variations
        [[nodiscard]] FORCEINLINE bool IsEqual(const FName& Rhs, const ENameCase CompareMethod = ENameCase::IgnoreCase, const bool bCompareNumber = true) const
        {
            return ((CompareMethod == ENameCase::IgnoreCase) ? GetComparisonIndex() == Rhs.GetComparisonIndex() : GetDisplayIndexFast() == Rhs.GetDisplayIndexFast())
                && (!bCompareNumber || GetNumber() == Rhs.GetNumber());
        }

        auto ToString() -> StringType;
        auto ToString() const -> const StringType;

        FString ToFString() const;
        FUtf8String ToFUtf8String() const;
        FAnsiString ToFAnsiString() const;
        
        uint32 GetPlainNameString(TCHAR(&OutName)[NAME_SIZE]);

        [[nodiscard]] auto GetComparisonIndex() const -> FNameEntryId { return ComparisonIndex; }
        [[nodiscard]] auto GetDisplayIndex() const -> FNameEntryId
        {
            return GetDisplayIndexFast();
        }
        [[nodiscard]] FORCEINLINE FNameEntryId GetDisplayIndexFast() const
        {
#ifdef WITH_CASE_PRESERVING_NAME
            return DisplayIndex;
#else
            return ComparisonIndex;
#endif
        }
        [[nodiscard]] FORCEINLINE FNameEntryId GetComparisonIndexInternal() const
        {
            return ComparisonIndex;
        }
        [[nodiscard]] auto GetNumber() const -> int32 { return Number; }

        /** Returns an integer that compares equal in the same way FNames do, only usable within the current process */
#if UE_FNAME_OUTLINE_NUMBER
        [[nodiscard]] FORCEINLINE uint64 ToUnstableInt() const
        {
            return ComparisonIndex.ToUnstableInt();
        }
#elif WITH_CASE_PRESERVING_NAME
        // Temp fix that only fixes case pres for under UE 5.1.
        // TODO: UE4SS - abstract for other versions
        [[nodiscard]] FORCEINLINE uint64 ToUnstableInt() const
        {
            // With case preserving: ComparisonIndex at 0, DisplayIndex at 4, Number at 8
            // Only return ComparisonIndex and Number for comparison
            return static_cast<uint64>(ComparisonIndex) | (static_cast<uint64>(Number) << 32);
        }
#else
        [[nodiscard]] FORCEINLINE uint64 ToUnstableInt() const
        {
            static_assert(STRUCT_OFFSET(FName, ComparisonIndex) == 0);
            static_assert(STRUCT_OFFSET(FName, Number) == 4);
            static_assert((STRUCT_OFFSET(FName, Number) + sizeof(FName::Number)) == sizeof(uint64));

            uint64 Out = 0;
            FMemory::Memcpy(&Out, this, sizeof(uint64));
            return Out;
        }
#endif

        /** True for FName(), FName(NAME_None) and FName("None") */
        [[nodiscard]] FORCEINLINE bool IsNone() const
        {
#if PLATFORM_64BITS && !WITH_CASE_PRESERVING_NAME
            return ToUnstableInt() == 0;
#else
            return ComparisonIndex == 0 && GetNumber() == NAME_NO_NUMBER_INTERNAL;
#endif
        }

        /**
         * Compares name to passed in one. Sort is alphabetical ascending.
         *
         * @param    Other    Name to compare this against
         * @return    < 0 is this < Other, 0 if this == Other, > 0 if this > Other
         */
        [[nodiscard]] int32 Compare( const FName& Other ) const;

        /**
         * Fast non-alphabetical order that is only stable during this process' lifetime.
         *
         * @param    Other    Name to compare this against
         * @return    < 0 is this < Other, 0 if this == Other, > 0 if this > Other
         */
        [[nodiscard]] FORCEINLINE int32 CompareIndexes(const FName& Other) const
        {
            if (int32 ComparisonDiff = ComparisonIndex.CompareFast(Other.ComparisonIndex))
            {
                return ComparisonDiff;
            }

#if UE_FNAME_OUTLINE_NUMBER
            return 0;  // If comparison indices are the same we are the same
#else //UE_FNAME_OUTLINE_NUMBER
            return GetNumber() - Other.GetNumber();
#endif //UE_FNAME_OUTLINE_NUMBER
        }
        
    };
#pragma warning(default: 4324)



    RC_UE_API inline uint32 GetTypeHash(FName N)
    {
        if (Version::IsAtLeast(4, 23))
        {
            return GetTypeHash(N.GetComparisonIndex()) + N.GetNumber();
        }
        else
        {
            return N.GetComparisonIndex().ToUnstableInt() + N.GetNumber();
        }
    }

    /** FNames act like PODs. */
    template <> struct TIsPODType<FName> { enum { Value = true }; };
    
    static FName NAME_None = FName(0, 0);

}

namespace std
{
    template<>
    struct hash<RC::Unreal::FName>
    {
        auto operator()(const RC::Unreal::FName& name) const -> size_t
        {
            size_t ComparisonIndexHash = hash<uint32_t>()(name.GetComparisonIndex().ToUnstableInt());
            size_t NumberHash = hash<uint32_t>()(name.GetNumber());
            return ComparisonIndexHash ^ NumberHash;
        }
    };
}