#pragma once

#ifdef UE4SS_PROFILERS

#include <atomic>
#include <chrono>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>

#include <Unreal/Common.hpp>

namespace RC::Unreal
{
    class UFunction;
    class UObject;

    // Forward declare the hook function
    auto RC_UE_API HookProcessEvent() -> void;

    // Stats for a single captured ProcessEvent call
    struct ProcessEventCallStats
    {
        std::string FunctionName{};
        uint64_t TotalTimeNs{0};
        uint64_t PreCallbacksTimeNs{0};
        uint64_t PostCallbacksTimeNs{0};
        uint64_t OriginalFunctionTimeNs{0};
    };

    // Aggregate stats for ProcessEvent hook
    struct ProcessEventAggregateStats
    {
        std::atomic<uint64_t> CallCount{0};
        std::atomic<uint64_t> TotalTimeNs{0};
        std::atomic<uint64_t> PreCallbacksTimeNs{0};
        std::atomic<uint64_t> PostCallbacksTimeNs{0};
        std::atomic<uint64_t> OriginalFunctionTimeNs{0};

        void Reset()
        {
            CallCount.store(0, std::memory_order_relaxed);
            TotalTimeNs.store(0, std::memory_order_relaxed);
            PreCallbacksTimeNs.store(0, std::memory_order_relaxed);
            PostCallbacksTimeNs.store(0, std::memory_order_relaxed);
            OriginalFunctionTimeNs.store(0, std::memory_order_relaxed);
        }

        // Average times in microseconds
        double AvgTotalTimeUs() const
        {
            auto count = CallCount.load(std::memory_order_relaxed);
            return count > 0 ? (TotalTimeNs.load(std::memory_order_relaxed) / 1000.0) / count : 0.0;
        }
        double AvgPreCallbacksTimeUs() const
        {
            auto count = CallCount.load(std::memory_order_relaxed);
            return count > 0 ? (PreCallbacksTimeNs.load(std::memory_order_relaxed) / 1000.0) / count : 0.0;
        }
        double AvgPostCallbacksTimeUs() const
        {
            auto count = CallCount.load(std::memory_order_relaxed);
            return count > 0 ? (PostCallbacksTimeNs.load(std::memory_order_relaxed) / 1000.0) / count : 0.0;
        }
        double AvgOriginalFunctionTimeUs() const
        {
            auto count = CallCount.load(std::memory_order_relaxed);
            return count > 0 ? (OriginalFunctionTimeNs.load(std::memory_order_relaxed) / 1000.0) / count : 0.0;
        }

        // Total times in milliseconds
        double TotalTimeMs() const { return TotalTimeNs.load(std::memory_order_relaxed) / 1000000.0; }
        double TotalPreCallbacksTimeMs() const { return PreCallbacksTimeNs.load(std::memory_order_relaxed) / 1000000.0; }
        double TotalPostCallbacksTimeMs() const { return PostCallbacksTimeNs.load(std::memory_order_relaxed) / 1000000.0; }
        double TotalOriginalFunctionTimeMs() const { return OriginalFunctionTimeNs.load(std::memory_order_relaxed) / 1000000.0; }
    };

    // Global profiler for ProcessEvent hook
    struct RC_UE_API ProcessEventProfiler
    {
        static constexpr size_t MaxCapturedCalls = 100;

        // Enable/disable profiling
        static inline std::atomic<bool> bProfilingEnabled{false};

        // Enable/disable capture of individual calls
        static inline std::atomic<bool> bCaptureEnabled{false};

        // Aggregate stats
        static inline ProcessEventAggregateStats AggregateStats{};

        // Captured individual calls (protected by mutex)
        static inline std::mutex CapturedCallsMutex{};
        static inline std::deque<ProcessEventCallStats> CapturedCalls{};

        static void EnableProfiling(bool enable)
        {
            if (enable)
            {
                // Ensure the ProcessEvent hook is installed so we can profile it
                HookProcessEvent();
            }
            bProfilingEnabled.store(enable, std::memory_order_release);
        }

        static bool IsProfilingEnabled()
        {
            return bProfilingEnabled.load(std::memory_order_acquire);
        }

        static void EnableCapture(bool enable)
        {
            bCaptureEnabled.store(enable, std::memory_order_release);
        }

        static bool IsCaptureEnabled()
        {
            return bCaptureEnabled.load(std::memory_order_acquire);
        }

        static void ResetStats()
        {
            AggregateStats.Reset();
        }

        static void ClearCapturedCalls()
        {
            std::lock_guard<std::mutex> lock(CapturedCallsMutex);
            CapturedCalls.clear();
        }

        static void AddCapturedCall(ProcessEventCallStats&& stats)
        {
            std::lock_guard<std::mutex> lock(CapturedCallsMutex);
            if (CapturedCalls.size() >= MaxCapturedCalls)
            {
                CapturedCalls.pop_front();
            }
            CapturedCalls.push_back(std::move(stats));
        }

        // Record a completed call
        static void RecordCall(uint64_t totalNs, uint64_t preCallbacksNs, uint64_t postCallbacksNs, uint64_t originalNs)
        {
            AggregateStats.CallCount.fetch_add(1, std::memory_order_relaxed);
            AggregateStats.TotalTimeNs.fetch_add(totalNs, std::memory_order_relaxed);
            AggregateStats.PreCallbacksTimeNs.fetch_add(preCallbacksNs, std::memory_order_relaxed);
            AggregateStats.PostCallbacksTimeNs.fetch_add(postCallbacksNs, std::memory_order_relaxed);
            AggregateStats.OriginalFunctionTimeNs.fetch_add(originalNs, std::memory_order_relaxed);
        }

        // Generate timestamped filename
        static std::string GenerateTimestampedFilename(const std::string& prefix = "processevent_profile")
        {
            auto now = std::chrono::system_clock::now();
            auto time_t_now = std::chrono::system_clock::to_time_t(now);
            auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

            std::tm tm_buf{};
#ifdef _WIN32
            localtime_s(&tm_buf, &time_t_now);
#else
            localtime_r(&time_t_now, &tm_buf);
#endif

            std::ostringstream oss;
            oss << prefix << "_"
                << std::put_time(&tm_buf, "%Y%m%d_%H%M%S")
                << "_" << std::setfill('0') << std::setw(3) << ms.count()
                << ".txt";
            return oss.str();
        }

        // Dump all stats to a file
        static bool DumpStatsToFile(const std::filesystem::path& directory)
        {
            std::filesystem::create_directories(directory);
            auto filepath = directory / GenerateTimestampedFilename();

            std::ofstream file(filepath);
            if (!file.is_open())
            {
                return false;
            }

            auto now = std::chrono::system_clock::now();
            auto time_t_now = std::chrono::system_clock::to_time_t(now);

            file << "=== ProcessEvent Hook Profiler Dump ===" << std::endl;
#ifdef _WIN32
            char time_buf[26];
            ctime_s(time_buf, sizeof(time_buf), &time_t_now);
            file << "Timestamp: " << time_buf;
#else
            file << "Timestamp: " << std::ctime(&time_t_now);
#endif
            file << "Profiling Enabled: " << (IsProfilingEnabled() ? "Yes" : "No") << std::endl;
            file << "Capture Enabled: " << (IsCaptureEnabled() ? "Yes" : "No") << std::endl;
            file << std::endl;

            // Aggregate stats
            file << "=== Aggregate Stats ===" << std::endl;
            file << std::fixed << std::setprecision(3);
            file << "Total Calls: " << AggregateStats.CallCount.load(std::memory_order_relaxed) << std::endl;
            file << std::endl;
            file << "Total Time:" << std::endl;
            file << "  Avg:   " << AggregateStats.AvgTotalTimeUs() << " us" << std::endl;
            file << "  Total: " << AggregateStats.TotalTimeMs() << " ms" << std::endl;
            file << "Pre Callbacks:" << std::endl;
            file << "  Avg:   " << AggregateStats.AvgPreCallbacksTimeUs() << " us" << std::endl;
            file << "  Total: " << AggregateStats.TotalPreCallbacksTimeMs() << " ms" << std::endl;
            file << "Original Function:" << std::endl;
            file << "  Avg:   " << AggregateStats.AvgOriginalFunctionTimeUs() << " us" << std::endl;
            file << "  Total: " << AggregateStats.TotalOriginalFunctionTimeMs() << " ms" << std::endl;
            file << "Post Callbacks:" << std::endl;
            file << "  Avg:   " << AggregateStats.AvgPostCallbacksTimeUs() << " us" << std::endl;
            file << "  Total: " << AggregateStats.TotalPostCallbacksTimeMs() << " ms" << std::endl;
            file << std::endl;

            // Captured calls
            file << "=== Captured Calls ===" << std::endl;
            {
                std::lock_guard<std::mutex> lock(CapturedCallsMutex);
                file << "Count: " << CapturedCalls.size() << " (max " << MaxCapturedCalls << ")" << std::endl;
                file << std::endl;

                if (!CapturedCalls.empty())
                {
                    file << std::left << std::setw(50) << "Function"
                         << std::right << std::setw(15) << "Total (us)"
                         << std::setw(15) << "Pre CB (us)"
                         << std::setw(15) << "Original (us)"
                         << std::setw(15) << "Post CB (us)"
                         << std::endl;
                    file << std::string(110, '-') << std::endl;

                    for (const auto& call : CapturedCalls)
                    {
                        file << std::left << std::setw(50) << call.FunctionName
                             << std::right << std::setw(15) << std::fixed << std::setprecision(3) << (call.TotalTimeNs / 1000.0)
                             << std::setw(15) << (call.PreCallbacksTimeNs / 1000.0)
                             << std::setw(15) << (call.OriginalFunctionTimeNs / 1000.0)
                             << std::setw(15) << (call.PostCallbacksTimeNs / 1000.0)
                             << std::endl;
                    }
                }
            }

            file << std::endl;
            file << "=== End of Dump ===" << std::endl;
            file.close();

            return true;
        }
    };

} // namespace RC::Unreal

#endif // UE4SS_PROFILERS
