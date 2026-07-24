#include <chrono>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <sstream>

#include <Helpers/Time.hpp>

#if _WIN32
#define NOMINMAX
#include <Windows.h>
#ifdef TEXT
#undef TEXT
#endif
#endif

namespace RC
{
    auto get_now_as_string(StringViewType format) -> StringType
    {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf{};
#ifdef _WIN32
        localtime_s(&tm_buf, &now_c);
#else
        localtime_r(&now_c, &tm_buf);
#endif

        // Convert UE4SS-style format ({:%Y-%m-%d %H:%M:%S}) to strftime format
        std::string fmt_str(format.begin(), format.end());
        // Strip {:% and trailing } to get strftime format
        size_t colon = fmt_str.find(":%");
        if (colon != std::string::npos) {
            fmt_str = fmt_str.substr(colon + 2);
            if (!fmt_str.empty() && fmt_str.back() == '}') fmt_str.pop_back();
        }

        char buf[256];
        std::strftime(buf, sizeof(buf), fmt_str.c_str(), &tm_buf);

#ifdef _WIN32
        std::wstring wbuf(buf, buf + strlen(buf));
        return wbuf;
#else
        return std::u16string(buf, buf + strlen(buf));
#endif
    }
} // namespace RC