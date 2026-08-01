// ===========================================================================
// UE4SS Linux Native Port
// Copyright (c) 2026 BlackBookOfficial
// Based on RE-UE4SS by UE4SS-RE (https://github.com/UE4SS-RE/RE-UE4SS)
// Palworld fork by Yangff
// Linux native port by BlackBookOfficial
//
// Licensed under the MIT License. See LICENSE and NOTICE for details.
// ===========================================================================

#include <CrashDumper.hpp>
#include <string>
#include <format>
#include <bit>
#include <UE4SSProgram.hpp>
#include <UE4SSDebug.hpp>

#ifdef _WIN32
#include <Unreal/Core/Windows/WindowsHWrapper.hpp>
#include <polyhook2/PE/IatHook.hpp>
#include <dbghelp.h>
#endif

#include <Helpers/SysError.hpp>
#include <Helpers/Time.hpp>
#include <String/StringType.hpp>

#ifdef __linux__
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <ctime>
#endif

namespace fs = std::filesystem;

using std::chrono::seconds;
using std::chrono::system_clock;
using std::chrono::time_point_cast;

namespace RC
{
#ifdef _WIN32
    const int DumpType =
            MiniDumpNormal | MiniDumpWithThreadInfo | MiniDumpWithIndirectlyReferencedMemory | MiniDumpWithModuleHeaders | MiniDumpWithAvxXStateContext;

    static bool FullMemoryDump = false;

    LONG WINAPI ExceptionHandler(_EXCEPTION_POINTERS* exception_pointers)
    {
        StringType dump_path = fmt::format(STR("{}\\crash_{}.dmp"), StringType{UE4SSProgram::get_program().get_working_directory()}, get_now_as_string(STR("{:%Y_%m_%d_%H_%M_%S}")));

        const HANDLE file =
                CreateFileW(FromCharTypePtr<wchar_t>(dump_path.c_str()), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if (file == INVALID_HANDLE_VALUE)
        {
            const StringType message = fmt::format(STR("Failed to create crashdump file, reason: {}"), SysError(GetLastError()).c_str());
            MessageBoxW(NULL, FromCharTypePtr<wchar_t>(message.c_str()), L"Fatal Error!", MB_OK);
            return EXCEPTION_CONTINUE_SEARCH;
        }

        _MINIDUMP_EXCEPTION_INFORMATION exception_information{};
        exception_information.ThreadId = GetCurrentThreadId();
        exception_information.ExceptionPointers = exception_pointers;
        exception_information.ClientPointers = NULL;

        const int additional_dump_flags = FullMemoryDump ? MiniDumpWithFullMemory | MiniDumpIgnoreInaccessibleMemory : 0;
        bool ok = MiniDumpWriteDump(GetCurrentProcess(),
                                    GetCurrentProcessId(),
                                    file,
                                    static_cast<MINIDUMP_TYPE>(DumpType | additional_dump_flags),
                                    &exception_information,
                                    NULL,
                                    NULL);
        CloseHandle(file);

        if (!ok)
        {
            const StringType message = fmt::format(STR("Failed to write crashdump file, reason: {}"), SysError(GetLastError()).c_str());
            MessageBoxW(NULL, FromCharTypePtr<wchar_t>(message.c_str()), L"Fatal Error!", MB_OK);
            return EXCEPTION_CONTINUE_SEARCH;
        }

        const StringType message = fmt::format(STR("Crashdump written to: {}"), dump_path);
        MessageBoxW(NULL, FromCharTypePtr<wchar_t>(message.c_str()), L"Fatal Error!", MB_OK);

        return EXCEPTION_EXECUTE_HANDLER;
    }

    LPTOP_LEVEL_EXCEPTION_FILTER WINAPI HookedSetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER filter)
    {
        return nullptr;
    }
#endif // _WIN32

#ifdef __linux__
    static bool FullMemoryDump = false;

    // Working directory captured ONCE at enable(): get_working_directory() allocates,
    // so it must not run inside the crash handler — the allocator may be corrupted or
    // locked there. Captured BEFORE the signal handlers are installed so the handler
    // can never observe a partially-assigned string (the handler only reads c_str(),
    // no allocation).
    static std::string s_crash_dir;

    static auto linux_crash_handler(int sig) -> void
    {
        // Report writer designed to keep working when the allocator/locks are broken:
        // no allocation, no stdio, no C++ runtime calls. The previous implementation
        // used fmt::format / std::string / get_now_as_string / UE4SS_DBG inside the
        // handler — all of which allocate and lock. When the crash IS heap corruption
        // (or the allocator is already wedged), those calls deadlock the game thread
        // INSIDE the handler, so the re-raise never runs and the process survives
        // wedged — the observed "signal 0 + empty report + surviving game thread"
        // signature from the Palworld wedge saga.
        //
        // Async-safety note (strict POSIX): open/write/close/time/fork/_exit/kill are
        // POSIX async-signal-safe. snprintf/backtrace/backtrace_symbols_fd are not on
        // the POSIX list, but glibc documents backtrace_symbols_fd as safe in signal
        // handlers (no malloc), and snprintf on a stack buffer performs no locking in
        // practice — the fork()-writer bounds the worst case: if the child wedges in
        // the handler, the parent has already returned and re-raised.

        // fork()-writer: the parent re-raises immediately, so the game thread can
        // never wedge in the handler even if the writer itself hangs. The child
        // inherits the crashed state but only uses async-signal-safe syscalls.
        pid_t pid = fork();
        if (pid == 0)
        {
            // Child: write the report, then _exit — never return into the crash frame.
            char path[1024];
            int path_len = snprintf(path, sizeof(path), "%s/crash_%lld.txt",
                                    s_crash_dir.c_str(), static_cast<long long>(time(nullptr)));
            if (path_len < 0 || static_cast<size_t>(path_len) >= sizeof(path))
            {
                _exit(1);
            }

            // O_CLOEXEC: don't leak the fd into later children.
            int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
            if (fd < 0)
            {
                static constexpr char err[] = "UE4SS: Failed to write crash report\n";
                ssize_t wr = write(STDERR_FILENO, err, sizeof(err) - 1);
                (void)wr;
                _exit(1);
            }

            static constexpr char header[] = "=== UE4SS Crash Report ===\n";
            ssize_t wr = write(fd, header, sizeof(header) - 1);
            (void)wr;

            const char* sig_name = sig == SIGSEGV ? "SIGSEGV" : sig == SIGABRT ? "SIGABRT" : sig == SIGFPE ? "SIGFPE" : sig == SIGILL ? "SIGILL" : "UNKNOWN";
            char sig_buf[256];
            int sig_len = snprintf(sig_buf, sizeof(sig_buf), "Signal: %d (%s)\n\n", sig, sig_name);
            wr = write(fd, sig_buf, sig_len);
            (void)wr;

            // backtrace_symbols_fd is glibc-documented safe in signal handlers (writes
            // directly to fd, no malloc).
            void* bt_buffer[64];
            int bt_size = backtrace(bt_buffer, 64);
            static constexpr char bt_header[] = "\nBacktrace:\n";
            wr = write(fd, bt_header, sizeof(bt_header) - 1);
            (void)wr;
            backtrace_symbols_fd(bt_buffer, bt_size, fd);

            close(fd);
            _exit(0);
        }

        // Parent (or fork failed): re-raise the signal to get default behavior
        // (core dump etc). kill() is POSIX async-signal-safe (raise() is not).
        // With fork() the game thread is already safe; without it, best effort only.
        signal(sig, SIG_DFL);
        kill(getpid(), sig);
    }
#endif // __linux__

    CrashDumper::CrashDumper()
    {
    }

    CrashDumper::~CrashDumper()
    {
#ifdef _WIN32
        m_set_unhandled_exception_filter_hook->unHook();
        SetUnhandledExceptionFilter(reinterpret_cast<LPTOP_LEVEL_EXCEPTION_FILTER>(m_previous_exception_filter));
#endif
    }

    void CrashDumper::enable()
    {
#ifdef _WIN32
        SetErrorMode(SEM_FAILCRITICALERRORS);
        m_previous_exception_filter = SetUnhandledExceptionFilter(ExceptionHandler);

        m_set_unhandled_exception_filter_hook = std::make_unique<PLH::IatHook>("kernel32.dll",
                                                                               "SetUnhandledExceptionFilter",
                                                                               std::bit_cast<uint64_t>(&HookedSetUnhandledExceptionFilter),
                                                                               &m_hook_trampoline_set_unhandled_exception_filter_hook,
                                                                               L"");
        m_set_unhandled_exception_filter_hook->hook();
#else
        struct sigaction sa{};
        sa.sa_handler = linux_crash_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;

        // Capture the crash output directory BEFORE installing the handlers: a crash
        // between sigaction() and the capture would otherwise enter the handler with
        // a partially-assigned s_crash_dir (and allocation is fine before the handler
        // is live).
        try
        {
            s_crash_dir = to_string(StringType{UE4SSProgram::get_program().get_working_directory()});
        }
        catch (...)
        {
            s_crash_dir = ".";
        }

        sigaction(SIGSEGV, &sa, nullptr);
        sigaction(SIGABRT, &sa, nullptr);
        sigaction(SIGFPE, &sa, nullptr);
        sigaction(SIGILL, &sa, nullptr);
#endif
        this->enabled = true;
    }

    void CrashDumper::set_full_memory_dump(bool enabled)
    {
        FullMemoryDump = enabled;
    }

} // namespace RC
