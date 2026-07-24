// ===========================================================================
// UE4SS Linux Native Port
// Copyright (c) 2024-2026 rl-dev.de (https://rl-dev.de)
// Based on RE-UE4SS by UE4SS-RE (https://github.com/UE4SS-RE/RE-UE4SS)
// Linux port originally by calebm02 (https://github.com/calebm02/RE-UE4SS-Linux)
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

    static auto linux_crash_handler(int sig) -> void
    {
        // Get the working directory
        StringType working_dir;
        try
        {
            working_dir = StringType{UE4SSProgram::get_program().get_working_directory()};
        }
        catch (...)
        {
            working_dir = STR(".");
        }

        auto now_str = get_now_as_string(STR("{:%Y_%m_%d_%H_%M_%S}"));
        auto crash_path_str = fmt::format(STR("{}/crash_{}.txt"), working_dir, now_str);
        auto crash_path_utf8 = to_string(crash_path_str);

        int fd = open(crash_path_utf8.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd >= 0)
        {
            const char* header = "=== UE4SS Crash Report ===\n";
            ssize_t wr = write(fd, header, strlen(header));
            (void)wr;

            const char* sig_name = sig == SIGSEGV ? "SIGSEGV" : sig == SIGABRT ? "SIGABRT" : sig == SIGFPE ? "SIGFPE" : sig == SIGILL ? "SIGILL" : "UNKNOWN";
            char sig_buf[256];
            int sig_len = snprintf(sig_buf, sizeof(sig_buf), "Signal: %d (%s)\n\n", sig, sig_name);
            wr = write(fd, sig_buf, sig_len);
            (void)wr;

            // Backtrace
            void* bt_buffer[64];
            int bt_size = backtrace(bt_buffer, 64);
            const char* bt_header = "\nBacktrace:\n";
            wr = write(fd, bt_header, strlen(bt_header));
            (void)wr;
            backtrace_symbols_fd(bt_buffer, bt_size, fd);

            close(fd);

            UE4SS_DBG( "UE4SS: Crash report written to: %s\n", crash_path_utf8.c_str());
        }
        else
        {
            UE4SS_DBG( "UE4SS: Failed to write crash report\n");
        }

        // Re-raise the signal to get default behavior (core dump etc)
        signal(sig, SIG_DFL);
        raise(sig);
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
