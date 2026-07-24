#pragma once

#include <string>
#include <String/StringType.hpp>

namespace RC
{
    class DiscordWebhook
    {
      public:
        // Send a message with an embed to a Discord webhook URL
        // Returns true on success, false on failure
        static auto send_embed(const std::string& webhook_url, const std::string& title, const std::string& description, int color = 0x00FF00) -> bool;
        
        // Send a simple text message to a Discord webhook URL
        static auto send_message(const std::string& webhook_url, const std::string& message) -> bool;
    };
} // namespace RC
