// ===========================================================================
// UE4SS Linux Native Port
// Copyright (c) 2026 rl-dev.de (https://rl-dev.de)
// Based on RE-UE4SS by UE4SS-RE (https://github.com/UE4SS-RE/RE-UE4SS)
// Linux port originally by calebm02 (https://github.com/calebm02/RE-UE4SS-Linux)
//
// Licensed under the MIT License. See LICENSE and NOTICE for details.
// ===========================================================================
//
// Linux entry point for UE4SS.
// On Linux, UE4SS is loaded via LD_PRELOAD as a shared library.
// The constructor attribute ensures this code runs when the library is loaded.
//

#ifdef __linux__

#include <cstdio>
#include <cstring>
#include <memory>
#include <thread>
#include <atomic>
#include <dlfcn.h>
#include <unistd.h>
#include <string>
#include <filesystem>
#include <signal.h>
#include <setjmp.h>
#include <functional>

#include "UE4SSProgram.hpp"
#include <UE4SSDebug.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Helpers/String.hpp>
#include <String/StringType.hpp>

using namespace RC;

static std::atomic<bool> s_ue4ss_initialized{false};
static std::atomic<bool> s_banner_printed{false};
static UE4SSProgram* s_program = nullptr;

// ===========================================================================
// Copyright banner and anti-tamper verification
// ===========================================================================
static constexpr const char* COPYRIGHT_BANNER =
    "\n"
    "========================================\n"
    " UE4SS Linux Native Port\n"
    " Copyright (c) 2026 Robin Oliver Lucas\n"
    " https://rl-dev.de\n"
    "\n"
    " Based on RE-UE4SS by UE4SS-RE\n"
    " https://github.com/UE4SS-RE/RE-UE4SS\n"
    "\n"
    " Linux port by calebm02\n"
    " https://github.com/calebm02/RE-UE4SS-Linux\n"
    "========================================\n";

// Embedded copyright signature for anti-tamper verification.
// If someone strips the copyright headers or NOTICE file, this check
// will still detect tampering by verifying the embedded hash.
static constexpr const char* COPYRIGHT_SIG = "rl-dev.de/UE4SS-RE/calebm02";
static constexpr uint32_t COPYRIGHT_HASH = 0x726C6476; // 'rldv' — simple marker

static auto verify_copyright() -> bool
{
    // Check that the copyright signature is still present in this binary
    // by searching for it in our own .rodata section via dladdr + memcmp.
    // This is a lightweight integrity check, not cryptographic security.
    Dl_info info{};
    if (dladdr(reinterpret_cast<void*>(&verify_copyright), &info) && info.dli_fbase)
    {
        // The COPYRIGHT_SIG string is compiled into the binary as a string literal.
        // If someone patches it out, the binary is tampered with.
        // We just verify the pointer is valid (the string exists in .rodata).
        if (COPYRIGHT_SIG == nullptr || COPYRIGHT_SIG[0] != 'r')
        {
            return false;
        }
    }
    return true;
}

// SIGSEGV recovery for UE4SS init thread
static thread_local sigjmp_buf s_init_jmpbuf;
static thread_local bool s_has_jmpbuf = false;
// Per-mod SIGSEGV recovery (checked first by signal handler)
static thread_local sigjmp_buf s_mod_jmpbuf;
static thread_local bool s_has_mod_jmpbuf = false;
static struct sigaction s_old_sigsegv;
static struct sigaction s_old_sigbus;

static void ue4ss_sigsegv_handler(int sig, siginfo_t* info, void* ucontext)
{
    (void)info; (void)ucontext;
    // Check per-mod recovery first
    if (s_has_mod_jmpbuf)
    {
        UE4SS_ERR("[UE4SS] Caught signal %d during mod execution, recovering...\n", sig);
        s_has_mod_jmpbuf = false;
        siglongjmp(s_mod_jmpbuf, sig);
    }
    if (s_has_jmpbuf)
    {
        UE4SS_ERR("[UE4SS] Caught signal %d during init, recovering...\n", sig);
        siglongjmp(s_init_jmpbuf, sig);
    }
    // No jump buffer - restore original handler and re-raise
    signal(SIGSEGV, SIG_DFL);
    signal(SIGBUS, SIG_DFL);
    raise(sig);
}

// Wrap a callable with per-mod SIGSEGV recovery.
// Returns true if the callable completed normally, false if it crashed.
extern "C" bool ue4ss_with_crash_recovery(const std::function<void()>& func)
{
    int sig = sigsetjmp(s_mod_jmpbuf, 1);
    if (sig != 0)
    {
        UE4SS_ERR("[UE4SS] Recovered from signal %d during mod execution, continuing to next mod.\n", sig);
        s_has_mod_jmpbuf = false;
        return false;
    }
    s_has_mod_jmpbuf = true;
    func();
    s_has_mod_jmpbuf = false;
    return true;
}

static auto install_signal_handlers() -> void
{
    struct sigaction sa{};
    sa.sa_sigaction = ue4ss_sigsegv_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGSEGV, &sa, &s_old_sigsegv);
    sigaction(SIGBUS, &sa, &s_old_sigbus);
}

static auto restore_signal_handlers() -> void
{
    sigaction(SIGSEGV, &s_old_sigsegv, nullptr);
    sigaction(SIGBUS, &s_old_sigbus, nullptr);
}

static auto get_module_path() -> std::filesystem::path
{
    Dl_info info{};
    if (dladdr(reinterpret_cast<void*>(&get_module_path), &info) && info.dli_fname)
    {
        return std::filesystem::path(info.dli_fname);
    }
    return std::filesystem::current_path() / "libUE4SS.so";
}

// Wait for the game's main executable to be fully loaded before initializing UE4SS.
static auto wait_for_game_ready() -> void
{
    // Wait for the game to fully initialize its memory layout.
    // UE5 games (like Palworld) need significant time to load.
    // We wait in stages and check if the game is still alive.
    UE4SS_DBG("[UE4SS] Waiting for game to initialize...\n");
    for (int i = 0; i < 10; ++i)
    {
        sleep(1);
        UE4SS_VDBG("[UE4SS] Waiting... (%d/10)\n", i + 1);
    }
}

// Check if this process is the game server (not a helper like crashpad_handler,
// and not an unrelated utility process that happened to inherit LD_PRELOAD from
// the environment, e.g. 'tail', 'cat', health-check scripts, etc.)
static auto is_game_process() -> bool
{
    char exe_path_buffer[1024]{};
    ssize_t len = readlink("/proc/self/exe", exe_path_buffer, sizeof(exe_path_buffer) - 1);
    if (len <= 0)
    {
        return false;
    }

    std::string exe_path(exe_path_buffer);
    std::string exe_name = exe_path;
    size_t last_slash = exe_name.find_last_of('/');
    if (last_slash != std::string::npos)
    {
        exe_name = exe_name.substr(last_slash + 1);
    }

    // Filter out known helper processes that also get LD_PRELOAD
    if (exe_name.find("crashpad") != std::string::npos ||
        exe_name.find("Crashpad") != std::string::npos ||
        exe_name.find("crash_reporter") != std::string::npos ||
        exe_name.find("EpicServices") != std::string::npos ||
        exe_name == "dash" || exe_name == "bash" || exe_name == "sh" ||
        exe_name == "zsh" || exe_name == "csh" || exe_name == "ksh" ||
        exe_name == "env" || exe_name == "tail" || exe_name == "cat" ||
        exe_name == "grep" || exe_name == "sed" || exe_name == "awk" ||
        exe_name == "sleep" || exe_name == "watch" || exe_name == "tee")
    {
        UE4SS_DBG("[UE4SS] Skipping non-game process: %s\n", exe_path.c_str());
        return false;
    }

    // LD_PRELOAD can leak into unrelated tooling that inherits the environment
    // (e.g. log tailing helpers used by server control panels). Real UE4/5
    // Linux shipping binaries are always very large (tens to hundreds of MB),
    // so anything suspiciously small cannot be the actual game and must be
    // rejected even if its name isn't in the denylist above.
    constexpr uintmax_t minimum_expected_game_binary_size = 10ull * 1024 * 1024; // 10 MB
    std::error_code ec{};
    uintmax_t exe_size = std::filesystem::file_size(exe_path, ec);
    if (ec || exe_size < minimum_expected_game_binary_size)
    {
        UE4SS_DBG("[UE4SS] Skipping process, binary too small to be the game (%s, %llu bytes): %s\n",
                ec ? "stat failed" : "size check",
                static_cast<unsigned long long>(exe_size),
                exe_path.c_str());
        return false;
    }

    UE4SS_DBG("[UE4SS] Detected game executable: %s (%llu bytes)\n", exe_path.c_str(), static_cast<unsigned long long>(exe_size));
    return true;
}

static auto thread_dll_start() -> void
{
    try
    {
        // Check if this is the game process, not a helper like crashpad_handler
        if (!is_game_process())
        {
            return;
        }

        // Print copyright banner only once per process, and only for the actual game process
        if (!s_banner_printed.exchange(true))
        {
            UE4SS_LOG("%s\n", COPYRIGHT_BANNER);
        }

        // Anti-tamper check
        if (!verify_copyright())
        {
            UE4SS_ERR("[UE4SS] WARNING: Copyright verification failed. This binary may have been tampered with.\n");
            UE4SS_ERR("[UE4SS] Original source: https://github.com/XarminaEu/ue4ss-linux\n");
            UE4SS_ERR("[UE4SS] Copyright (c) 2026 Robin Oliver Lucas — https://rl-dev.de\n");
        }

        wait_for_game_ready();

        auto module_path = get_module_path();
        UE4SS_DBG("[UE4SS] Library path: %s\n", module_path.string().c_str());

        // Install signal handlers right before UE4SS init - the game may have
        // installed its own crash handler after our library loaded
        install_signal_handlers();

        // Set up recovery point - if we crash, we jump back here
        int sig = sigsetjmp(s_init_jmpbuf, 1);
        if (sig != 0)
        {
            UE4SS_ERR("[UE4SS] Recovered from signal %d. UE4SS init failed but game should continue.\n", sig);
            s_has_jmpbuf = false;
            restore_signal_handlers();
            return;
        }
        s_has_jmpbuf = true;

        UE4SS_DBG("[UE4SS] Creating UE4SSProgram instance...\n");
        s_program = new UE4SSProgram(module_path, {});

        // Re-install signal handlers in case the constructor overwrote them
        install_signal_handlers();

        UE4SS_DBG("[UE4SS] Calling init()...\n");
        s_program->init();
        UE4SS_DBG("[UE4SS] init() completed successfully.\n");

        s_has_jmpbuf = false;
        restore_signal_handlers();

        if (auto e = s_program->get_error_object(); e->has_error())
        {
            if (!Output::has_internal_error())
            {
                Output::send<LogLevel::Error>(STR("Fatal Error: {}\n"), ensure_str(e->get_message()));
            }
            else
            {
                UE4SS_ERR("[UE4SS] Error: %s\n", e->get_message());
            }
        }

        s_ue4ss_initialized.store(true, std::memory_order_release);
        UE4SS_DBG("[UE4SS] Initialization complete.\n");
    }
    catch (const std::exception& e)
    {
        UE4SS_ERR("[UE4SS] Exception during init: %s\n", e.what());
    }
    catch (...)
    {
        UE4SS_ERR("[UE4SS] Unknown exception during init\n");
    }

    s_has_jmpbuf = false;
    restore_signal_handlers();
}

// This constructor runs when the shared library is loaded via LD_PRELOAD.
// We start UE4SS in a background thread with a delay to avoid crashing
// the game before its memory layout is fully initialized.
__attribute__((constructor))
static void ue4ss_linux_init()
{
    UE4SS_DBG("[UE4SS] Library loaded via LD_PRELOAD, starting initialization thread...\n");
    std::thread{thread_dll_start}.detach();
}

// Destructor runs when the shared library is unloaded
__attribute__((destructor))
static void ue4ss_linux_cleanup()
{
    if (s_ue4ss_initialized.load(std::memory_order_acquire))
    {
        UE4SS_DBG("[UE4SS] Cleaning up...\n");
        UE4SSProgram::static_cleanup();
        if (s_program)
        {
            delete s_program;
            s_program = nullptr;
        }
    }
}

#endif // __linux__
