#pragma once

#ifdef __linux__

#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>

#include <Input/KeyDef.hpp>
#include <Input/Common.hpp>
#include <Input/PlatformInputSource.hpp>

namespace RC::Input
{
    // Headless Linux input source that reads raw keypresses directly from the
    // controlling terminal (stdin), when one is attached (isatty(STDIN_FILENO)).
    // Puts the terminal into raw/non-canonical mode so individual keypresses are
    // delivered immediately without requiring Enter, mirroring the behavior of
    // the Windows console input source. Ctrl+<letter> is decoded from the ASCII
    // control codes (0x01-0x1A) that terminals emit for those combinations.
    //
    // If no TTY is attached (e.g. running under a service manager/log redirection
    // without a pty), is_available() returns false and this source is skipped.
    class LinuxTerminalInputSource : public PlatformInputSource
    {
      private:
        bool m_activated{false};
        bool m_termios_saved{false};
        std::atomic_bool m_stop{false};
        std::thread m_reader_thread;
        std::mutex m_queue_mutex;
        std::queue<InputEvent> m_pending_events;
        std::vector<InputEvent> m_input_events{};

      private:
        auto reader_loop() -> void;

      public:
        bool is_available() override;
        bool activate() override;
        bool deactivate() override;
        std::vector<InputEvent>& process_event(Handler* handler) override;

        ~LinuxTerminalInputSource() override;

        int source_priority() override
        {
            return 0;
        }

        const char* get_name() override
        {
            return "LinuxTerminal";
        }
    };
} // namespace RC::Input

#endif // __linux__
