#ifdef __linux__
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

#include <DiscordWebhook.hpp>
#include <UE4SSDebug.hpp>

namespace RC
{
    static auto url_escape_json(const std::string& s) -> std::string
    {
        std::string out;
        out.reserve(s.size() + 10);
        for (char c : s)
        {
            switch (c)
            {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20)
                {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned char>(c));
                    out += buf;
                }
                else
                {
                    out += c;
                }
                break;
            }
        }
        return out;
    }

    static auto curl_post(const std::string& url, const std::string& json_body) -> bool
    {
        std::string cmd = "curl -s -o /dev/null -w '%{http_code}' -X POST -H 'Content-Type: application/json' -d '";
        // Escape single quotes in JSON for shell
        for (char c : json_body)
        {
            if (c == '\'')
            {
                cmd += "'\\''";
            }
            else
            {
                cmd += c;
            }
        }
        cmd += "' '";
        cmd += url;
        cmd += "' 2>/dev/null";

        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe)
        {
            UE4SS_DBG( "[UE4SS] DiscordWebhook: failed to run curl\n");
            return false;
        }

        char buf[16];
        std::string result;
        while (fgets(buf, sizeof(buf), pipe))
        {
            result += buf;
        }
        pclose(pipe);

        // curl outputs the HTTP status code
        if (result.empty())
        {
            UE4SS_DBG( "[UE4SS] DiscordWebhook: no response from curl\n");
            return false;
        }

        // Check for 2xx status
        if (result[0] == '2')
        {
            return true;
        }

        UE4SS_DBG( "[UE4SS] DiscordWebhook: HTTP status %s\n", result.c_str());
        return false;
    }

    auto DiscordWebhook::send_embed(const std::string& webhook_url, const std::string& title, const std::string& description, int color) -> bool
    {
        if (webhook_url.empty())
        {
            return false;
        }

        std::string json = "{\"embeds\":[{\"title\":\"";
        json += url_escape_json(title);
        json += "\",\"description\":\"";
        json += url_escape_json(description);
        json += "\",\"color\":";
        json += std::to_string(color);
        json += "}]}";

        return curl_post(webhook_url, json);
    }

    auto DiscordWebhook::send_message(const std::string& webhook_url, const std::string& message) -> bool
    {
        if (webhook_url.empty())
        {
            return false;
        }

        std::string json = "{\"content\":\"";
        json += url_escape_json(message);
        json += "\"}";

        return curl_post(webhook_url, json);
    }
} // namespace RC

#endif // __linux__
