#include <Helpers/Casting.hpp>

#ifdef _WIN32
#define WINDOWS
#define NOMINMAX
#include "Windows.h"
#else
#include <unistd.h>
#include <sys/mman.h>
#include <cstdint>
#endif

namespace RC::Helper::Casting
{

#ifdef WINDOWS
    auto check_readable(void* handle, void* src_ptr) -> bool
    {
        uintptr_t is_valid_ptr_buffer;
        size_t bytes_read;

        return ReadProcessMemory(*reinterpret_cast<HANDLE*>(handle), src_ptr, &is_valid_ptr_buffer, 0x8, &bytes_read) != 0;
    }
#else
    auto check_readable(void* handle, void* src_ptr) -> bool
    {
        // On Linux, use msync to check if a page is mapped/readable
        // This is a lightweight check - it doesn't guarantee readability but catches unmapped pages
        uintptr_t page_addr = reinterpret_cast<uintptr_t>(src_ptr) & ~(sysconf(_SC_PAGESIZE) - 1);
        return msync(reinterpret_cast<void*>(page_addr), sysconf(_SC_PAGESIZE), MS_ASYNC) == 0;
    }
#endif

} // namespace RC::Helper::Casting
