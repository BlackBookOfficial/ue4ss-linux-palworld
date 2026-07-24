#pragma once
#include <functional>
#include <memory>
#include <atomic>
#include <mutex>
#include <vector>
#include <thread>

#include <DynamicOutput/DynamicOutput.hpp>
#include <Helpers/String.hpp>
#include <Unreal/Hooks/Internal/Common.hpp>
#include <Unreal/Hooks/Hooks.hpp>

#pragma push_macro("ensure")
#undef ensure

namespace RC::Unreal::Hook::Internal {

    inline static constexpr unsigned long HOOK_GC_INTERVAL_SECONDS = 3;
    inline static constexpr unsigned long HOOK_GC_LINKS_PER_ITERATION = 1;

    class FCallbackGarbageCollector {
    public:
        // Should invoke a detour's CollectGarbage function, added in by a detour in ActivateHook.
        // Return true if callbacks were cleaned up, false otherwise (the return value of CollectGarbage). 
        using FGarbageCollectionInvoker = std::function<bool()>;
    public:
        void AddLink(FGarbageCollectionInvoker Link) {
            std::lock_guard Guard(LinkWriteMutex);
            auto OldLinks = Links.load(std::memory_order_acquire);
            auto NewLinks = std::make_shared<FLinkVector>(*OldLinks);
            NewLinks->emplace_back(std::move(Link));
            Links.store(NewLinks, std::memory_order_release);
        }

        // Executes garbage collection invokers from StartIdx until MaxGcInvokers invokers have done something or all invokers have been attempted.
        // If MaxGcInvokers = 0, then all links are executed (all detours get a GC pass).
        // Returns the next StartIdx when calling again, if doing so regularly. StartIdx does not have to match the previously returned StartIdx.
        unsigned long Collect(const unsigned long StartIdx = 0, const unsigned long MaxGcInvokers = 0) {
            auto CurrentLinks = Links.load(std::memory_order_acquire);
            const size_t LinkCount = CurrentLinks->size();
            if (!LinkCount) return 0;

            auto SafeInvoke = [&](const FGarbageCollectionInvoker& LinkFn) -> bool {
                try {
                    return LinkFn();
                } catch (const std::exception& Exception) {
                    Output::send<LogLevel::Error>(STR("[FCallbackGarbageCollector] Threw exception: {}\n"), ensure_str(Exception.what()));
                    return false;
                } catch (...) {
                    Output::send<LogLevel::Error>(STR("[FCallbackGarbageCollector] Threw non-standard exception\n"));
                    return false;
                }
            };

            if (MaxGcInvokers == 0) {
                for (const auto& LinkFn : *CurrentLinks) {
                    SafeInvoke(LinkFn); // keep going even if one link is cursed
                }
                Output::send<LogLevel::Verbose>(STR("[FCallbackGarbageCollector] Forcefully freed invalid callbacks!\n"));
                return 0;
            }

            const size_t StartBounded = StartIdx % LinkCount;
            size_t CurrentIdx = StartBounded;
            size_t Collected = 0;

            do {
                if (SafeInvoke((*CurrentLinks)[CurrentIdx])) {
                    Output::send<LogLevel::Verbose>(STR("[FCallbackGarbageCollector] Freed invalid callbacks!\n"));
                    if (++Collected == MaxGcInvokers) {
                        return (CurrentIdx + 1) % LinkCount;
                    }
                }
                CurrentIdx = (CurrentIdx + 1) % LinkCount;
            } while (CurrentIdx != StartBounded);

            return StartBounded;
        }

        bool StartGCThread() {
            if(GcThread.joinable()) return false;

            GcThread = std::jthread([this](std::stop_token StopToken){
                unsigned long LastIndexCollected = 0;

                while(true) {
                    if(StopToken.stop_requested()) {
                        return;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(HOOK_GC_INTERVAL_SECONDS));
                    LastIndexCollected = Collect(LastIndexCollected, HOOK_GC_LINKS_PER_ITERATION);
                }
            });

            return true;
        }

        bool StopGCThread() {
            if(!GcThread.joinable()) return false;
            if(!GcThread.request_stop()) return false;
            GcThread.join();
            return true;
        }

    public:
        static std::shared_ptr<FCallbackGarbageCollector> GetInstance() {
            static std::shared_ptr<FCallbackGarbageCollector> Singleton { new FCallbackGarbageCollector() };
            return Singleton;
        }
    UE_HOOK_PRIVATE:
        FCallbackGarbageCollector() = default;

    UE_HOOK_PRIVATE:
        using FLinkVector = std::vector<FGarbageCollectionInvoker>;
        using FMutableLinkVectorPtr = std::shared_ptr<FLinkVector>;
        using FImmutableLinkVectorPtr = std::shared_ptr<const FLinkVector>;

        // keep thread lock free since it's more reads than writes, even though detours may be added at different times/from different threads
        std::mutex LinkWriteMutex;
        std::atomic<FImmutableLinkVectorPtr> Links = std::make_shared<const FLinkVector>();

        std::jthread GcThread;
    };
}

#pragma pop_macro("ensure")