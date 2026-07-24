#pragma once

// Linux implementation of PolyHook2 interface using funchook
// Provides the same API as PLH::x64Detour but uses funchook internally

#ifndef _WIN32

#include <cstdint>
#include <bit>
#include <funchook.h>

namespace PLH
{
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

    template<typename DestType, typename SrcType>
    inline DestType FnCast(SrcType src, DestType fallback)
    {
        if (src == 0) return fallback;
        return std::bit_cast<DestType>(src);
    }
}

#endif
