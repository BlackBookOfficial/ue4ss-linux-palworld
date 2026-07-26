#include <Unreal/FMemory.hpp>
#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>
#include <Unreal/UnrealInitializer.hpp>

namespace RC::Unreal
{
    FMalloc** GMalloc{};
    std::unordered_map<File::StringType, uint32_t> FMalloc::VTableLayoutMap;

    template<class T>
    static constexpr T Min(const T A, const T B)
    {
        return (A <= B) ? A : B;
    }

    static uint32 CountTrailingZeros(uint32 Value)
    {
        if (Value == 0)
        {
            return 32;
        }
#ifdef _MSC_VER
        unsigned long BitIndex;    // 0-based, where the LSB is 0 and MSB is 31
        _BitScanForward(&BitIndex, Value);    // Scans from LSB to MSB
        return BitIndex;
#else
        return __builtin_ctz(Value);
#endif
    }

    void* FMalloc::Malloc(SIZE_T Count, uint32 Alignment)
    {
#ifdef __linux__
        static bool s_logged = false;
        if (!s_logged) {
            s_logged = true;
            auto it = VTableLayoutMap.find(STR("Malloc"));
            fprintf(stderr, "[UE4SS] FMalloc::Malloc first call: offset=0x%x (map has %zu entries)\n",
                    it != VTableLayoutMap.end() ? it->second : 0xDEAD, VTableLayoutMap.size());
        }
#endif
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, Malloc, void*, PARAMS(SIZE_T, uint32), ARGS(Count, Alignment))
    }

    void* FMalloc::TryMalloc(SIZE_T Count, uint32 Alignment)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, TryMalloc, void*, PARAMS(SIZE_T, uint32), ARGS(Count, Alignment))
    }

    void* FMalloc::Realloc(void* Original, SIZE_T Count, uint32 Alignment)
    {
#ifdef __linux__
        static thread_local int s_call_count = 0;
        if (s_call_count < 3) {
            ++s_call_count;
            auto it = VTableLayoutMap.find(STR("Realloc"));
            fprintf(stderr, "[UE4SS] FMalloc::Realloc call #%d: this=%p *GMalloc=%p offset=0x%x orig=%p count=%zu align=%u\n",
                    s_call_count, (void*)this, (void*)(*GMalloc),
                    it != VTableLayoutMap.end() ? it->second : 0xDEAD,
                    Original, (size_t)Count, Alignment);
            fflush(stderr);
        }
#endif
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, Realloc, void*, PARAMS(void*, SIZE_T, uint32), ARGS(Original, Count, Alignment))
    }

    void* FMalloc::TryRealloc(void* Original, SIZE_T Count, uint32 Alignment)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, TryRealloc, void*, PARAMS(void*, SIZE_T, uint32), ARGS(Original, Count, Alignment))
    }

    void FMalloc::Free(void* Original)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, Free, void, PARAMS(void*), ARGS(Original))
    }

    SIZE_T FMalloc::QuantizeSize(SIZE_T Count, uint32 Alignment)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, QuantizeSize, SIZE_T, PARAMS(SIZE_T, uint32), ARGS(Count, Alignment))
    }

    bool FMalloc::GetAllocationSize(void* Original, SIZE_T& SizeOut)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, GetAllocationSize, bool, PARAMS(void*, SIZE_T&), ARGS(Original, SizeOut))
    }

    void FMalloc::Trim(bool bTrimThreadCaches)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, Trim, void, PARAMS(bool), ARGS(bTrimThreadCaches))
    }

    void FMalloc::SetupTLSCachesOnCurrentThread()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, SetupTLSCachesOnCurrentThread, void)
    }

    void FMalloc::ClearAndDisableTLSCachesOnCurrentThread()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, ClearAndDisableTLSCachesOnCurrentThread, void)
    }

    void FMalloc::InitializeStatsMetadata()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, InitializeStatsMetadata, void)
    }

    void FMalloc::UpdateStats()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, UpdateStats, void)
    }

    void FMalloc::GetAllocatorStats(FGenericMemoryStats& out_Stats)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, GetAllocatorStats, void, PARAMS(FGenericMemoryStats&), ARGS(out_Stats))
    }

    void FMalloc::DumpAllocatorStats(class FOutputDevice& Ar)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMalloc, DumpAllocatorStats, void, PARAMS(FOutputDevice&), ARGS(Ar))
    }

    bool FMalloc::IsInternallyThreadSafe() const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, IsInternallyThreadSafe, bool)
    }

    bool FMalloc::ValidateHeap()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, ValidateHeap, bool)
    }

    const TCHAR* FMalloc::GetDescriptiveName()
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(FMalloc, GetDescriptiveName, const TCHAR*)
    }
}
