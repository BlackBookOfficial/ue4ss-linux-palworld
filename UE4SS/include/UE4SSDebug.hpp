#pragma once

#include <cstdio>
#include <cstdlib>

// Global debug logging control for UE4SS on Linux.
// Controlled by:
//   1. UE4SS-settings.ini -> [General] DebugLogLevel = 0|1|2
//   2. UE4SS_DEBUG environment variable (fallback if config not set)
//
// Levels:
//   0 = default — only mod output and errors/warnings
//   1 = debug   — init steps, dlsym results, mod loading info
//   2 = verbose — very verbose (wait steps, etc.)

namespace UE4SSDebug
{
    inline int& debug_level_ref()
    {
        static int level = []() {
            const char* env = getenv("UE4SS_DEBUG");
            if (env) return atoi(env);
            return 0;
        }();
        return level;
    }

    inline int get_debug_level()
    {
        return debug_level_ref();
    }

    inline void set_debug_level(int level)
    {
        debug_level_ref() = level;
    }
}

// UE4SS_LOG: Always printed (important messages, mod output)
#define UE4SS_LOG(...) fprintf(stderr, __VA_ARGS__)

// UE4SS_DBG: Only printed when debug level >= 1
#define UE4SS_DBG(...) do { if (UE4SSDebug::get_debug_level() >= 1) { fprintf(stderr, __VA_ARGS__); } } while(0)

// UE4SS_VDBG: Only printed when debug level >= 2 (very verbose)
#define UE4SS_VDBG(...) do { if (UE4SSDebug::get_debug_level() >= 2) { fprintf(stderr, __VA_ARGS__); } } while(0)

// UE4SS_ERR: Always printed (errors)
#define UE4SS_ERR(...) fprintf(stderr, __VA_ARGS__)
