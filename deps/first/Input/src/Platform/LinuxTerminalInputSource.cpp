#ifdef __linux__

#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <termios.h>

#include <Input/Handler.hpp>
#include <Input/Platform/LinuxTerminalInputSource.hpp>

namespace RC::Input
{
    static termios s_original_termios{};

    bool LinuxTerminalInputSource::is_available()
    {
        return isatty(STDIN_FILENO) != 0;
    }

    bool LinuxTerminalInputSource::activate()
    {
        if (m_activated)
        {
            return true;
        }

        if (!is_available())
        {
            return false;
        }

        if (tcgetattr(STDIN_FILENO, &s_original_termios) == 0)
        {
            termios raw = s_original_termios;
            // Disable canonical mode (line buffering) and local echo, but keep ISIG
            // enabled so Ctrl+C/Ctrl+\ still generate their normal signals.
            raw.c_lflag &= ~(ICANON | ECHO);
            raw.c_cc[VMIN] = 1;
            raw.c_cc[VTIME] = 0;
            if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == 0)
            {
                m_termios_saved = true;
            }
        }

        m_stop.store(false);
        m_activated = true;
        m_reader_thread = std::thread{&LinuxTerminalInputSource::reader_loop, this};
        return true;
    }

    bool LinuxTerminalInputSource::deactivate()
    {
        if (!m_activated)
        {
            return true;
        }

        m_stop.store(true);
        m_activated = false;

        if (m_reader_thread.joinable())
        {
            // The reader thread is blocked on read(); it will only notice m_stop
            // once new input arrives or the fd is closed. We detach instead of
            // joining to avoid hanging shutdown on a server with no active TTY input.
            m_reader_thread.detach();
        }

        if (m_termios_saved)
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &s_original_termios);
            m_termios_saved = false;
        }

        return true;
    }

    auto LinuxTerminalInputSource::reader_loop() -> void
    {
        unsigned char byte{};
        while (!m_stop.load())
        {
            ssize_t n = read(STDIN_FILENO, &byte, 1);
            if (n <= 0)
            {
                if (n < 0 && (errno == EINTR))
                {
                    continue;
                }
                break;
            }

            if (m_stop.load())
            {
                break;
            }

            Key key{};
            ModifierKeys modifiers{};
            bool recognized = true;

            if (byte == 0x08 || byte == 0x09 || byte == 0x0D || byte == 0x1B)
            {
                // BACKSPACE, TAB, RETURN, ESCAPE - literal control keys, no modifier.
                key = static_cast<Key>(byte);
            }
            else if (byte >= 0x01 && byte <= 0x1A)
            {
                // Ctrl+<letter> - terminals send control codes 0x01-0x1A for Ctrl+A..Ctrl+Z.
                key = static_cast<Key>(byte + 0x40);
                modifiers |= ModifierKey::CONTROL;
            }
            else if (byte >= 'a' && byte <= 'z')
            {
                key = static_cast<Key>(byte - 0x20); // uppercase to match VK-style codes
            }
            else if ((byte >= '0' && byte <= '9') || byte == ' ')
            {
                key = static_cast<Key>(byte);
            }
            else
            {
                recognized = false;
            }

            if (recognized)
            {
                std::lock_guard lock(m_queue_mutex);
                m_pending_events.push(InputEvent{key, modifiers});
            }
        }
    }

    std::vector<InputEvent>& LinuxTerminalInputSource::process_event(Handler* handler)
    {
        m_input_events.clear();

        if (!m_activated || !handler->get_allow_input())
        {
            std::lock_guard lock(m_queue_mutex);
            while (!m_pending_events.empty()) m_pending_events.pop();
            return m_input_events;
        }

        std::lock_guard lock(m_queue_mutex);
        while (!m_pending_events.empty())
        {
            m_input_events.emplace_back(m_pending_events.front());
            m_pending_events.pop();
        }
        return m_input_events;
    }

    LinuxTerminalInputSource::~LinuxTerminalInputSource()
    {
        deactivate();
    }
} // namespace RC::Input

#endif // __linux__
