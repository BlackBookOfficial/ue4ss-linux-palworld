// ===========================================================================
// UE4SS Linux Native Port
// Copyright (c) 2026 BlackBookOfficial
// Based on RE-UE4SS by UE4SS-RE (https://github.com/UE4SS-RE/RE-UE4SS)
// Palworld fork by Yangff
// Linux native port by BlackBookOfficial
//
// Licensed under the MIT License. See LICENSE and NOTICE for details.
// ===========================================================================

#include <Unreal/NameTypes.hpp>

#include <fmt/core.h>
#include <fmt/xchar.h>

#include <cstdio>

#include <DynamicOutput/Output.hpp>

#include <Unreal/Core/Containers/FString.hpp>
#include <Unreal/Core/Containers/FUtf8String.hpp>
#include <Unreal/Core/Containers/FAnsiString.hpp>
#include <Unreal/BPMacros.hpp>
#include <Unreal/UnrealInitializer.hpp>

namespace RC::Unreal
{
    Function<void(const FName*, class FStringOut&)> FName::ToStringInternal;
    UFunction* FName::Conv_NameToStringInternal{};
    UObject* FName::KismetStringLibraryCDO{};
    Function<FName(const CharType*, EFindName)> FName::ConstructorInternal;

    // ---------------------------------------------------------------------
    // Linux/Palworld native name provider
    // ---------------------------------------------------------------------
    // Palworld's optimized Clang/LTO build has no standalone FName(const TCHAR*,
    // EFindName) constructor symbol — the string->FName logic is inlined into
    // callers, and the AOB scan + verification hook never fires. Without a working
    // string->ComparisonIndex primitive, UE4SS cannot bootstrap StaticFindObject
    // (which builds FName search keys), so KismetStringLibrary / Conv_NameToString
    // can never be resolved and init stalls.
    //
    // Investigation (behavior-driven, verified at runtime via gdb) located the
    // engine's own name-pool find-or-add routine. It is reached through a small
    // wrapper at 0x7941c10 which:
    //   1. walks the wide string to compute its length,
    //   2. sets a wide-flag bit (bit 0x20) if any char is non-ASCII,
    //   3. calls the hash+lookup core at 0x7941c70 with (rdi=string,
    //      esi=length | (wide_flag << 32)),
    //   4. the core hashes the string (polynomial, base 5), acquires the pool's
    //      pthread_rwlock, searches the hash table, and returns the existing
    //      ComparisonIndex in rax (low 32 bits) — find-or-add, non-duplicating.
    //
    // Verified oracle (deterministic across runs):
    //   "Object"              -> 0x1f0
    //   "Actor"               -> 0x1f8
    //   "Pawn"                -> 0x21e
    //   "Engine"              -> 0xe3
    //   "KismetStringLibrary" -> 0x617f6
    //
    // Rather than bake in the absolute address, we locate the wrapper at runtime
    // via a deterministic signature anchored on its stable structure (the unique
    // byte sequence of its prologue + the wide-flag computation).
    // ---------------------------------------------------------------------
#ifdef __linux__
    namespace PalworldNameProvider
    {
        // Resolved at init by LocateEngineFindName(). Points to the engine's
        // find-or-add wrapper (0x7941c10-equivalent). Signature:
        //   void find_name(uint64_t* out_index, const wchar_t* str)
        // The wrapper computes length + wide-flag and calls the hash/lookup core,
        // writing the resulting ComparisonIndex into *out_index.
        using EngineFindNameFn = void (*)(uint64_t*, const char16_t*);
        static EngineFindNameFn g_engine_find_name{};

        // Signature of the wrapper prologue. This is the function at 0x7941c10:
        //   push rbx; mov rax,rsi; mov rbx,rdi; test rsi,rsi; je +N;
        //   movzwl edi,[rax]; xor ecx,ecx; mov rsi,rax; test di,di
        // The 'movzwl (%rax),%edi; xor %ecx,%ecx; mov %rax,%rsi; test %di,%di'
        // sequence (scanning a wide string for length + ASCII-ness) is distinctive.
        // The conditional-jump offset (byte 11) is wildcarded as it may shift.
        static constexpr unsigned char kWrapperSig[] = {
            0x53,                                   // push rbx
            0x48, 0x89, 0xf0,                       // mov rax,rsi
            0x48, 0x89, 0xfb,                       // mov rbx,rdi
            0x48, 0x85, 0xf6,                       // test rsi,rsi
            0x74, /*wildcard*/ 0x00,                // je +N (offset wildcarded)
            0x0f, 0xb7, 0x38,                       // movzwl edi,[rax]
            0x31, 0xc9,                             // xor ecx,ecx
            0x48, 0x89, 0xc6,                       // mov rsi,rax
            0x66, 0x85, 0xff,                       // test di,di
        };
        static constexpr size_t kWildcardOffset = 11; // index of the wildcarded je offset byte

        auto LocateEngineFindName() -> EngineFindNameFn
        {
            if (g_engine_find_name) { return g_engine_find_name; }

            // Scan the main executable's r-xp segment for the wrapper signature.
            FILE* maps = fopen("/proc/self/maps", "r");
            char line[512];
            int seg_count = 0;
            while (fgets(line, sizeof(line), maps))
            {
                // Only the main executable text segment (r-xp, contains 'PalServer').
                if (!strstr(line, "r-xp") || !strstr(line, "PalServer")) { continue; }
                ++seg_count;
                uintptr_t start = 0, end = 0;
                if (sscanf(line, "%lx-%lx", &start, &end) != 2) { continue; }
                const auto* base = reinterpret_cast<const unsigned char*>(start);
                size_t size = end - start;
                // Search for the signature.
                for (size_t i = 0; i + sizeof(kWrapperSig) <= size; ++i)
                {
                    bool match = true;
                    for (size_t j = 0; j < sizeof(kWrapperSig); ++j)
                    {
                        if (j == kWildcardOffset) { continue; } // wildcarded byte
                        if (base[i + j] != kWrapperSig[j]) { match = false; break; }
                    }
                    if (!match) { continue; }
                    // Validate: the matched function should, shortly after, call a
                    // function (E8 xx xx xx xx) — the hash/lookup core. This weeds
                    // out coincidental byte matches.
                    bool has_call = false;
                    for (size_t j = i + sizeof(kWrapperSig); j < i + 0x60 && j + 5 <= size; ++j)
                    {
                        if (base[j] == 0xE8) { has_call = true; break; }
                    }
                    if (!has_call) { continue; }
                    g_engine_find_name = reinterpret_cast<EngineFindNameFn>(const_cast<unsigned char*>(base + i));
                    break;
                }
                if (g_engine_find_name) { break; }
            }
            fclose(maps);
            if (!g_engine_find_name)
            {
                // Log once: on failure every FName construction silently returns
                // None, which otherwise surfaces as inexplicable mod breakage.
                static bool scan_failure_logged = false;
                if (!scan_failure_logged)
                {
                    scan_failure_logged = true;
                    Output::send<LogLevel::Error>(STR("PalworldNameProvider: engine find-or-add signature not found. All FName string construction will return None. The Palworld binary likely changed (game update); kWrapperSig in NameTypes.cpp needs updating.\n"));
                }
            }
            return g_engine_find_name;
        }

        // Native FName(const CharType*, EFindName) backend for Linux/Palworld.
        // Delegates to the engine's own find-or-add name lookup and constructs an
        // FName from the returned ComparisonIndex. The Number field replicates the
        // engine's "_N" suffix parsing (see below) so constructed names compare
        // equal to engine-created names.
        auto FindName(const CharType* StrName, EFindName FindType) -> FName
        {
            if (!StrName) { return FName{}; }
            auto fn = LocateEngineFindName();
            if (!fn) { return FName{}; }

            // UE FName convention (FName::Init / SplitNameWithNumber): a trailing
            // "_N" suffix is split off — "BountyProof_1" resolves to the BASE name
            // "BountyProof" (ComparisonIndex) with a STORED Number of N + 1.
            // Stored Number 0 means "no suffix" (NAME_NO_NUMBER_INTERNAL), and
            // ToString prints Number - 1, so stored Number 2 displays as "_1".
            //
            // The engine's find-or-add performs this split internally and returns
            // the base name's ComparisonIndex. We must replicate the Number side
            // or FName equality (ComparisonIndex + Number) against engine-created
            // names — e.g. inventory item StaticIDs — fails. Verified empirically:
            // stored Number must be suffix + 1; storing the raw suffix (Number 1
            // for "_1") does NOT match game items.
            uint32_t parsed_number = 0;
            StringType base_name(StrName);
            const size_t len = base_name.size();
            if (len > 2)
            {
                size_t digit_start = len;
                while (digit_start > 0 && base_name[digit_start - 1] >= '0' && base_name[digit_start - 1] <= '9')
                {
                    --digit_start;
                }
                // Need at least one digit, a '_' before the digits, and at most 9
                // digits (larger suffixes don't occur in practice and overflow
                // even the engine's own parsing).
                if (digit_start < len && digit_start > 0 && base_name[digit_start - 1] == '_' && len - digit_start <= 9)
                {
                    uint32_t num = 0;
                    for (size_t i = digit_start; i < len; ++i)
                    {
                        num = num * 10 + static_cast<uint32_t>(base_name[i] - '0');
                    }
                    parsed_number = num + 1; // stored Number = suffix + 1
                }
            }

            // The engine wrapper writes a 64-bit value: high 32 = hash, low 32 =
            // ComparisonIndex. We only need the ComparisonIndex (low 32 bits).
            uint64_t result = 0;
            fn(&result, reinterpret_cast<const char16_t*>(StrName));
            const uint32_t comparison_index = static_cast<uint32_t>(result);
            if (comparison_index == 0) { return FName{}; }

            FName name{};
            name.ComparisonIndex = FNameEntryId::FromUnstableInt(comparison_index);
#if WITH_CASE_PRESERVING_NAME
            name.DisplayIndex = name.ComparisonIndex;
#endif
            name.Number = parsed_number;
            return name;
        }
    } // namespace PalworldNameProvider
#endif

    /** An unpacked FNameEntryId */
    struct FNameEntryHandle
    {
        uint32 Block = 0;
        uint32 Offset = 0;

        FNameEntryHandle(uint32 InBlock, uint32 InOffset)
            : Block(InBlock)
            , Offset(InOffset)
        {
            checkName(Block < FNameMaxBlocks);
            checkName(Offset < FNameBlockOffsets);
        }

        FNameEntryHandle(FNameEntryId Id)
            : Block(Id.ToUnstableInt() >> FNameBlockOffsetBits)
            , Offset(Id.ToUnstableInt() & (FNameBlockOffsets - 1))
        {
        }

        operator FNameEntryId() const
        {
            return FNameEntryId::FromUnstableInt(Block << FNameBlockOffsetBits | Offset);
        }

        explicit operator bool() const { return Block | Offset; }
    };

    static uint32 GetTypeHash(FNameEntryHandle Handle)
    {
        return (Handle.Block << (32 - FNameMaxBlockBits)) + Handle.Block // Let block index impact most hash bits
            + (Handle.Offset << FNameBlockOffsetBits) + Handle.Offset // Let offset impact most hash bits
            + (Handle.Offset >> 4); // Reduce impact of non-uniformly distributed entry name lengths
    }

    uint32 GetTypeHash(FNameEntryId Id)
    {
        return GetTypeHash(FNameEntryHandle(Id));
    }

    // Special wrapper for 'UKismetStringLibrary::Conv_NameToString' that doesn't use StaticFindObject and is safe to use during init.
    FString UKismetStringLibrary_Conv_NameToString(FName InName)
    {
        // We make some assumptions in this function to increase performance.
        // We assume that the CDO, and function always exist and never change or get reallocated.
        // If you use BPMacros, there will be a lot of error checking, but since FName::ToString is a very hot function,
        // we need to avoid as much overhead as possible.

        static const auto ParamStructSize = FName::Conv_NameToStringInternal->GetParmsSize();
        auto ParamData = static_cast<uint8*>(_malloca(ParamStructSize));
        FMemory::Memzero(ParamData, ParamStructSize);

        static const auto Offset = []() {
            return FName::Conv_NameToStringInternal->FindProperty(FName(TEXT("InName"), FNAME_Find))->GetOffset_Internal();
        }();
        *std::bit_cast<FName*>(&ParamData[Offset]) = InName;

        FName::KismetStringLibraryCDO->ProcessEvent(FName::Conv_NameToStringInternal, ParamData);

        static const auto ReturnOffset = []() {
            return FName::Conv_NameToStringInternal->GetReturnProperty()->GetOffset_Internal();
        }();
        const auto RetValue = *std::bit_cast<FString*>(&ParamData[ReturnOffset]);
        _freea(ParamData);
        return RetValue;
    }

    const StringType ToStringInternalWrapper_UsingScan(const FName* name)
    {
        // LEAK FIX (2026-08-03): the game's ToStringInternal appends into the
        // fork-owned FStringOut. An empty FStringOut has zero capacity, so the
        // FIRST append forces the game to allocate via its own TLS-cache
        // allocator — and the fork's TStringBase dtor frees via SystemFree
        // (glibc), which never returns the buffer to the game allocator
        // (~300B leaked per call; measured 425MB/min under census).
        // Pre-reserving with the FORK's own allocator gives the game capacity to
        // append into, so it NEVER calls the game allocator; the fork dtor then
        // SystemFrees its own buffer — correct ownership, zero leak.
        // NAME_SIZE is the FName max length (1024); +16 covers the numbered-name
        // suffix the game appends ("_1234567890") plus the null terminator.
        FStringOut string{};
        string.Reset(NAME_SIZE + 16);
        FName::ToStringInternal(name, string);

        StringType name_string{*string ? *string : STR("UE4SS_None")};
        return name_string;
    }

    const StringType ToStringInternalWrapper_UsingConv_NameToString(const FName* name)
    {
        const auto string = UKismetStringLibrary_Conv_NameToString(*name);

        StringType name_string{*string ? *string : STR("UE4SS_None")};
        return name_string;
    }

    const StringType ToStringInternalWrapper(const FName* name)
    {
        using namespace UnrealInitializer;
        if (StaticStorage::GlobalConfig.FNameToStringMethod == FNameToStringMethod::Scan && FName::ToStringInternal.is_ready())
        {
            return ToStringInternalWrapper_UsingScan(name);
        }
        else if (FName::Conv_NameToStringInternal)
        {
            return ToStringInternalWrapper_UsingConv_NameToString(name);
        }
        else
        {
#ifdef __linux__
            // Linux limited mode: FName::ToString is not available (stripped binary, dlsym failed).
            // Return a placeholder with the comparison index so callers get something identifiable
            // instead of crashing with an unhandled C++ exception through Lua C frames.
            return fmt::format(STR("FName_0x{:X}"), static_cast<uint32>(name->GetComparisonIndex().ToUnstableInt()));
#else
            throw std::runtime_error{"FName::ToString was not ready but was called anyway"};
#endif
        }
    }

    auto FName::ToString() -> StringType
    {
        return ToStringInternalWrapper(this);
    }

    auto FName::ToString() const -> const StringType
    {
        return ToStringInternalWrapper(this);
    }

    // Returns FString (TCHAR-based)
    FString FName::ToFString() const
    {
        StringType str = ToString();
        return FString(str);
    }

    FUtf8String FName::ToFUtf8String() const
    {
        StringType str = ToString();
        return FUtf8String(str);
    }

    FAnsiString FName::ToFAnsiString() const
    {
        StringType str = ToString();
        return FAnsiString(str);
    }

    uint32 FName::GetPlainNameString(TCHAR(&OutName)[NAME_SIZE])
    {
        const uint32 Entry = GetDisplayIndex().ToUnstableInt();
        auto String = FName(Entry).ToString();
        std::memcpy(OutName, &String[0], String.size() * sizeof(File::StringType::value_type));
        return static_cast<uint32>(String.size());
    }
}
