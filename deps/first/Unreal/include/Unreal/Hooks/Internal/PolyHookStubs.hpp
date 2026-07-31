#pragma once

// Linux implementation of PolyHook2 interface using funchook
// Provides the same API as PLH::x64Detour but uses funchook internally

#ifndef _WIN32

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <bit>
#include <unistd.h>
#include <funchook.h>

namespace PLH
{
    // Forward declaration of the helper used by x64Detour::hook().
    // Defined below the class so it can call into the same header
    // without introducing a new translation unit.
    inline bool is_address_readable(uint64_t address) noexcept;

    class x64Detour
    {
    public:
        x64Detour(uint64_t fnAddress, uint64_t fnCallback, uint64_t* trampoline)
            : m_target(fnAddress)
            , m_callback(fnCallback)
            , m_trampoline(trampoline)
            , m_funchook(funchook_create())
        {
        }

        ~x64Detour()
        {
            if (m_funchook)
            {
                funchook_destroy(m_funchook);
                m_funchook = nullptr;
            }
        }

        x64Detour(const x64Detour&) = delete;
        x64Detour& operator=(const x64Detour&) = delete;

        bool hook()
        {
            if (!m_funchook || m_is_hooked) return m_is_hooked;

            // Validate hook target before passing to funchook. funchook's
            // internal disassembler (distorm) will dereference whatever
            // address we give it; a null pointer here causes a SIGSEGV
            // inside distorm_decompose64 that the signal handler can't
            // safely recover from. The crash is intermittent because
            // it depends on whether the caller computed the address from
            // a valid virtual-table slot or a stale pointer.
            if (m_target == 0 || !is_address_readable(m_target))
            {
                return false;
            }

            void* target = std::bit_cast<void*>(m_target);
            int rv = funchook_prepare(m_funchook, &target, std::bit_cast<void*>(m_callback));
            if (rv != FUNCHOOK_ERROR_SUCCESS)
            {
                return false;
            }
            *m_trampoline = std::bit_cast<uint64_t>(target);

            rv = funchook_install(m_funchook, 0);
            if (rv != FUNCHOOK_ERROR_SUCCESS)
            {
                return false;
            }
            m_is_hooked = true;
            return true;
        }

        bool unHook()
        {
            if (!m_funchook || !m_is_hooked) return !m_is_hooked;

            int rv = funchook_uninstall(m_funchook, 0);
            m_is_hooked = false;
            return rv == FUNCHOOK_ERROR_SUCCESS;
        }

        bool isHooked() const { return m_is_hooked; }

        uint64_t getOriginal() const { return *m_trampoline; }

    private:
        uint64_t m_target;
        uint64_t m_callback;
        uint64_t* m_trampoline;
        funchook_t* m_funchook;
        bool m_is_hooked = false;
    };

    // Check whether an address falls in a mapped readable region of the
    // current process. Used by x64Detour::hook() to reject bad hook
    // targets before funchook's disassembler dereferences them.
    //
    // /proc/self/maps is read once per second and cached. Hook install
    // is not a hot path, but the maps file can be ~50 KB on a heavily
    // loaded game process so we don't want to re-read it per call.
    // The O(n) scan over mapped regions is cheap relative to the maps
    // file read.
    inline bool is_address_readable(uint64_t address) noexcept
    {
        static char maps_buffer[64 * 1024];
        static uint64_t maps_ts = 0;
        struct timespec now{};
        clock_gettime(CLOCK_MONOTONIC, &now);
        uint64_t now_ns = static_cast<uint64_t>(now.tv_sec) * 1000000000ULL + static_cast<uint64_t>(now.tv_nsec);
        if (now_ns - maps_ts > 1000000000ULL)
        {
            // Use std::ifstream rather than raw open()/read() to avoid
            // namespace conflicts with RC::File::open which is pulled
            // in by other UE4SS headers. The ifstream is slower than
            // a raw syscall but this path only runs once per second.
            std::FILE* fp = std::fopen("/proc/self/maps", "r");
            if (fp)
            {
                size_t n = std::fread(maps_buffer, 1, sizeof(maps_buffer) - 1, fp);
                std::fclose(fp);
                if (n > 0)
                {
                    maps_buffer[n] = '\0';
                    maps_ts = now_ns;
                }
            }
        }

        const char* p = maps_buffer;
        const char* end = p + std::strlen(maps_buffer);
        while (p < end)
        {
            const char* eol = static_cast<const char*>(std::memchr(p, '\n', end - p));
            if (!eol) eol = end;

            // Format: "start-end perms offset dev inode pathname"
            const char* dash = static_cast<const char*>(std::memchr(p, '-', eol - p));
            if (!dash || dash >= eol)
            {
                p = eol + 1;
                continue;
            }

            // Parse hex start and end (simple parser, no base prefix)
            uint64_t lo = 0, hi = 0;
            for (const char* c = p; c < dash; ++c)
            {
                char ch = *c;
                if (ch >= '0' && ch <= '9') lo = (lo << 4) | (ch - '0');
                else if (ch >= 'a' && ch <= 'f') lo = (lo << 4) | (ch - 'a' + 10);
                else if (ch >= 'A' && ch <= 'F') lo = (lo << 4) | (ch - 'A' + 10);
            }
            for (const char* c = dash + 1; c < eol; ++c)
            {
                char ch = *c;
                if (ch >= '0' && ch <= '9') hi = (hi << 4) | (ch - '0');
                else if (ch >= 'a' && ch <= 'f') hi = (hi << 4) | (ch - 'a' + 10);
                else if (ch >= 'A' && ch <= 'F') hi = (hi << 4) | (ch - 'A' + 10);
                else break; // hit the space after the end address
            }

            if (address >= lo && address < hi)
            {
                // Found the region. The perms field starts after the
                // space following the end address. Look for " r" at
                // that position.
                for (const char* c = dash + 1; c < eol; ++c)
                {
                    if (*c == ' ' && c + 4 <= eol)
                    {
                        // Perms is 4 chars: r, w, x, p/s
                        return c[1] == 'r';
                    }
                }
                // Couldn't parse perms — be conservative and allow.
                return true;
            }

            p = eol + 1;
        }
        return false;
    }

    template<typename DestType, typename SrcType>
    inline DestType FnCast(SrcType src, DestType fallback)
    {
        if (src == 0) return fallback;
        return std::bit_cast<DestType>(src);
    }
}

#endif
