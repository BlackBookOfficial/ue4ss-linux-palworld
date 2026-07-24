#pragma once
#ifdef UE_HOOK_TEST

#include <atomic>
#include <algorithm>
#include <cstdint>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <latch>
#include <bit>

using namespace RC;
using namespace RC::Unreal::Hook;
using namespace RC::Unreal::Hook::Internal;

struct TestInstance {
    virtual ~TestInstance() = default;
    TestInstance(StringViewType name) : name(name) {}

    virtual bool Run() = 0;
    void OutputErrorMessage(StringViewType msg) {
        Output::send<LogLevel::Error>(STR("[{}] {}\n"), name, msg);
    }

    StringViewType name;
};

class TestController {
    using Test = std::shared_ptr<TestInstance>;
public:
    bool StartTests() {
        auto PassedUnitTests = DoUnitTests();
        if (!PassedUnitTests) return false;
        Output::send(STR("Passed unit tests, doing integration tests in 3 seconds..."));
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return DoIntegrationTests();
    }

    static std::shared_ptr<TestController> GetInstance() {
        static std::shared_ptr<TestController> singleton = std::make_shared<TestController>();
        return singleton;
    }

    void InvokeVoid(int value) { void_holder.Target(value); }
    bool InvokeNonVoid(int value) { return nv_holder.Target(value); }

    void RegisterUnitTest(Test test) { unit_tests.push_back(test); }
    void RegisterIntegrationTest(Test test) { integration_tests.push_back(test); }
private:
    bool DoUnitTests() {
        size_t successful = 0;
        size_t total = unit_tests.size();
        bool any_failed = false;
        for(auto& test: unit_tests) {
            Output::send<LogLevel::Verbose>(STR("Starting unit test {}\n"), test->name);
            if(test->Run()) {
                Output::send<LogLevel::Verbose>(STR("Unit test {} passed, unit tests are {}% complete!\n"), test->name, (size_t)((++successful / (double)total) * 100));
                continue;
            }
            Output::send<LogLevel::Error>(STR("Unit test {} failed!\n"), test->name);
            any_failed = true;
        }

        Output::send<LogLevel::Verbose>(STR("Unit test complete, {} / {} passed!\n"), successful, total);

        return !any_failed;
    }

    bool DoIntegrationTests() {
        size_t successful = 0;
        size_t total = integration_tests.size();
        bool any_failed = false;
        for(auto& test: integration_tests) {
            Output::send<LogLevel::Verbose>(STR("Starting integration test {}\n"), test->name);
            if(test->Run()) {
                Output::send<LogLevel::Verbose>(STR("Integration test {} passed, unit tests are {}% complete!\n"), test->name, (size_t)((++successful / (double)total) * 100));
                continue;
            }
            Output::send<LogLevel::Error>(STR("Integration test {} failed!\n"), test->name);
            any_failed = true;
        }

        Output::send<LogLevel::Verbose>(STR("Integration test complete, {} / {} passed!\n"), successful, total);

        return !any_failed;
    }

    std::vector<Test> unit_tests{};

    std::vector<Test> integration_tests{};

    FTestVoidDetourHolder void_holder;
    FTestNonVoidDetourHolder nv_holder;
};

auto RC::Unreal::StartTests() -> bool
{
    return TestController::GetInstance()->StartTests();
}

#define DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Name, LAMBDA_EXPR)                       \
    struct TestClass##Name : TestInstance {                                  \
        TestClass##Name() : TestInstance(STR(#Name)) {}                      \
        bool Run() override { try { return (LAMBDA_EXPR)(); } catch(std::exception& ex) { OutputErrorMessage(ensure_str(ex.what())); return false;  } }                      \
    };                                                                       \
    bool InitializedTestClass##Name = ([](){ TestController::GetInstance()->RegisterUnitTest(std::make_shared<TestClass##Name>()); return true; })();

#define DEFINE_INT_TEST_INSTANCE_LAMBDA(Name, LAMBDA_EXPR) \
    struct TestClass##Name : TestInstance { \
        TestClass##Name() : TestInstance(STR(#Name)) {} \
        bool Run() override { try { return (LAMBDA_EXPR)(); } catch(std::exception& ex) { OutputErrorMessage(ensure_str(ex.what())); return false;  } } \
    }; \
    bool InitializedTestClass##Name = ([](){ TestController::GetInstance()->RegisterIntegrationTest(std::make_shared<TestClass##Name>()); return true; })();

#define TI_ASSERT(cond, msg_literal)                                         \
    do {                                                                     \
        if(!(cond)) {                                                        \
            OutputErrorMessage(STR(msg_literal));                             \
            return false;                                                    \
        }                                                                    \
    } while(0)

#define TI_ASSERT_MSG(cond, msg_literal, exec)                                         \
    do {                                                                     \
        if(!(cond)) {                                                        \
            OutputErrorMessage(STR(msg_literal));                             \
            exec\
        }                                                                    \
    } while(0)

#define INVOKE_VOID(val) TestController::GetInstance()->InvokeVoid(val)
#define INVOKE_NVOID(val) TestController::GetInstance()->InvokeNonVoid(val)

#pragma region Unit Tests

namespace
{
    template<typename DetourT>
    static void ResetDetourToBuiltinsOnly(DetourT* det)
    {
        // Mark every non-builtin callback invalid, then force a GC prune.
        auto mark = [](const auto& vec)
        {
            for (const auto& cb : *vec)
            {
                if (cb && cb->Id != 0)
                {
                    cb->Invalidate();
                    cb->WaitForExecutorsToFinish();
                }
            }
        };

        mark(det->PreHookCallbacks.load(std::memory_order_acquire));
        mark(det->PostHookCallbacks.load(std::memory_order_acquire));

        det->bDirty.store(true, std::memory_order_release);
        det->CollectGarbage();
    }

    template<typename DetourT>
    static size_t PreSize(DetourT* det)
    {
        return det->PreHookCallbacks.load(std::memory_order_acquire)->size();
    }

    template<typename DetourT>
    static size_t PostSize(DetourT* det)
    {
        return det->PostHookCallbacks.load(std::memory_order_acquire)->size();
    }

    static FCallbackOptions Opt(bool once, const TCHAR* HookName)
    {
        FCallbackOptions o{};
        o.bOnce = once;
        o.OwnerModName = STR("UT");
        o.HookName = HookName;
        return o;
    }
}

// ------------------------------------------------------------
// DetourInstance: Add/Remove/CollectGarbage basic behavior
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_AddRemoveCollect_NonVoid, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    TI_ASSERT(PreSize(det) == 0, "Expected no prehooks at start for NonVoidTest");
    TI_ASSERT(PostSize(det) == 0, "Expected no posthooks at start for NonVoidTest");

    std::atomic_int pre_calls{0};
    std::atomic_int post_calls{0};

    auto id_pre = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int) { pre_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Pre, Opt(false, STR("Pre"))
    );
    auto id_post = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int) { post_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Post, Opt(false, STR("Post"))
    );

    TI_ASSERT(id_pre != ERROR_ID, "AddCallback returned ERROR_ID for prehook");
    TI_ASSERT(id_post != ERROR_ID, "AddCallback returned ERROR_ID for posthook");
    TI_ASSERT(PreSize(det) == 1, "Expected 1 prehook after AddCallback");
    TI_ASSERT(PostSize(det) == 1, "Expected 1 posthook after AddCallback");

    bool rv = INVOKE_NVOID(123);
    TI_ASSERT(rv == true, "Expected original NonVoid Target to return true");
    TI_ASSERT(pre_calls.load() == 1, "Expected prehook to run exactly once");
    TI_ASSERT(post_calls.load() == 1, "Expected posthook to run exactly once");

    TI_ASSERT(UnregisterCallback(id_pre), "UnregisterCallback failed for prehook");
    TI_ASSERT(det->IsDirty(), "Detour should be dirty after removing a hook");

    pre_calls.store(0);
    post_calls.store(0);

    rv = INVOKE_NVOID(456);
    TI_ASSERT(rv == true, "Original should still run and return true after prehook removal");
    TI_ASSERT(pre_calls.load() == 0, "Removed prehook should not execute (should be skipped immediately)");
    TI_ASSERT(post_calls.load() == 1, "Posthook should still execute");

    TI_ASSERT(det->CollectGarbage() == true, "CollectGarbage should return true when it prunes after dirty removal");
    TI_ASSERT(det->IsDirty() == false, "Detour should not be dirty after CollectGarbage clears it");
    TI_ASSERT(PreSize(det) == 0, "Prehook vector should be empty after GC");
    TI_ASSERT(PostSize(det) == 1, "Posthook vector should still contain 1 after GC");

    TI_ASSERT(UnregisterCallback(id_post), "UnregisterCallback failed for posthook");
    TI_ASSERT(det->CollectGarbage() == true, "CollectGarbage should prune after removing posthook");
    TI_ASSERT(PostSize(det) == 0, "Posthook vector should be empty after GC");

    // Calling GC again when clean should be a no-op.
    TI_ASSERT(det->CollectGarbage() == false, "CollectGarbage should return false when not dirty");

    return true;
}));

// ------------------------------------------------------------
// Once callbacks: self-invalidate and mark dirty; GC prunes them
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_OnceCallback_CallsExactlyOnce, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int once_calls{0};

    auto once_id = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int) { once_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Pre, Opt(true, STR("OncePre"))
    );

    TI_ASSERT(once_id != ERROR_ID, "AddCallback returned ERROR_ID for once prehook");
    TI_ASSERT(PreSize(det) == 1, "Expected 1 prehook after adding once hook");

    (void)INVOKE_NVOID(1);
    (void)INVOKE_NVOID(2);
    (void)INVOKE_NVOID(3);

    TI_ASSERT(once_calls.load() == 1, "Once prehook must execute exactly once across multiple invocations");
    TI_ASSERT(det->IsDirty(), "Once hook should mark detour dirty after firing");

    TI_ASSERT(det->CollectGarbage() == true, "CollectGarbage should prune the invalidated once hook");
    TI_ASSERT(PreSize(det) == 0, "Prehook vector should be empty after pruning once hook");

    // Unregistering once_id after it's already invalidated may return true or false depending on timing,
    // but it should never crash. We'll just call it to ensure it doesn't explode.
    (void)UnregisterCallback(once_id);

    return true;
}));

// ------------------------------------------------------------
// PreventOriginalFunctionCall: default return + override return
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_PreventOriginal_ReturnSemantics, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    // 1) Prevent original, no override -> returns default-constructed bool (false)
    auto id_block = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int) { info.PreventOriginalFunctionCall(); },
        EHookType::Pre, Opt(false, STR("BlockOriginal"))
    );
    TI_ASSERT(id_block != ERROR_ID, "Failed to add BlockOriginal hook");

    bool rv = INVOKE_NVOID(10);
    TI_ASSERT(rv == false, "Preventing original with no override should return default bool=false");

    TI_ASSERT(UnregisterCallback(id_block), "Failed to unregister BlockOriginal hook");
    TI_ASSERT(det->CollectGarbage() == true, "GC should prune after removing BlockOriginal");

    // 2) Prevent original + override -> returns override
    auto id_block_override = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            info.PreventOriginalFunctionCall();
            (void)info.TrySetReturnValue(true);
        },
        EHookType::Pre, Opt(false, STR("BlockAndOverride"))
    );
    TI_ASSERT(id_block_override != ERROR_ID, "Failed to add BlockAndOverride hook");

    rv = INVOKE_NVOID(11);
    TI_ASSERT(rv == true, "Preventing original + overriding return should return override");

    TI_ASSERT(UnregisterCallback(id_block_override), "Failed to unregister BlockAndOverride hook");
    TI_ASSERT(det->CollectGarbage() == true, "GC should prune after removing BlockAndOverride");

    return true;
}));

// ------------------------------------------------------------
// Return override precedence: first setter wins
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_ReturnOverride_Precedence, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_bool second_set_succeeded{false};
    std::atomic_int pre_calls{0};

    auto id_first = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            pre_calls.fetch_add(1, std::memory_order_relaxed);
            bool ok = info.TrySetReturnValue(false);
            // first setter should succeed
            if (!ok) { /* don't TI_ASSERT here; just record and fail after */ }
        },
        EHookType::Pre, Opt(false, STR("FirstSetter"))
    );

    auto id_second = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            pre_calls.fetch_add(1, std::memory_order_relaxed);
            bool ok = info.TrySetReturnValue(true);
            second_set_succeeded.store(ok, std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("SecondSetter"))
    );

    TI_ASSERT(id_first != ERROR_ID && id_second != ERROR_ID, "Failed to add setter hooks");
    TI_ASSERT(PreSize(det) == 2, "Expected 2 prehooks");

    // Original returns true normally, but first override forces false.
    bool rv = INVOKE_NVOID(99);
    TI_ASSERT(rv == false, "First return override must win (expected false)");
    TI_ASSERT(pre_calls.load() == 2, "Both prehooks should have executed");
    TI_ASSERT(second_set_succeeded.load() == false, "Second setter must fail because first setter takes precedence");

    UnregisterCallback(id_first);
    UnregisterCallback(id_second);
    det->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// Exceptions inside callbacks: auto-invalidate + no repeat
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_ExceptionInCallback_Invalidates, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int throws{0};

    auto id_throw = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int)
        {
            throws.fetch_add(1, std::memory_order_relaxed);
            throw std::runtime_error("boom");
        },
        EHookType::Pre, Opt(false, STR("Thrower"))
    );

    TI_ASSERT(id_throw != ERROR_ID, "Failed to add throwing hook");

    // First invoke: hook throws, DetourInstance catches and invalidates it.
    (void)INVOKE_NVOID(1);
    TI_ASSERT(throws.load() == 1, "Throwing hook should have run once");
    TI_ASSERT(det->IsDirty(), "Detour should be dirty after invalidating throwing hook");

    // Second invoke: throwing hook should be skipped now (still present but invalid until GC).
    (void)INVOKE_NVOID(2);
    TI_ASSERT(throws.load() == 1, "Throwing hook should not run again after being invalidated");

    // GC should prune it out.
    TI_ASSERT(det->CollectGarbage() == true, "GC should prune invalidated throwing hook");
    TI_ASSERT(PreSize(det) == 0, "Throwing hook should be removed from prehook vector after GC");

    // Unregistering the old Id should fail now (it no longer exists in the vector).
    TI_ASSERT(UnregisterCallback(id_throw) == false, "UnregisterCallback should fail after GC prunes the callback");

    return true;
}));

// ------------------------------------------------------------
// ICallbackIterationData rules: GetCallbackId only valid in-callback
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackIterationData_GetCallbackId_Scope, ([this]() -> bool
{
    // Outside of hook execution, callback-scoped APIs must throw.
    {
        TCallbackIterationData<bool> info{ STR("UTDetour") };
        bool threw = false;
        try { (void)info.CommonImpl.GetCallbackId(); }
        catch (...) { threw = true; }
        TI_ASSERT(threw, "Expected GetCallbackId to throw outside hook execution (NonVoid)");
    }
    {
        TCallbackIterationData<void> info{ STR("UTDetour") };
        bool threw = false;
        try { (void)info.CommonImpl.GetCallbackId(); }
        catch (...) { threw = true; }
        TI_ASSERT(threw, "Expected GetCallbackId to throw outside hook execution (Void)");
    }

    // Inside execution, it must reflect the currently executing callback's Id.
    auto* det_nv = GetDetourInstance<EDetourTarget::NonVoidTest>();
    auto* det_vv = GetDetourInstance<EDetourTarget::VoidTest>();
    ResetDetourToBuiltinsOnly(det_nv);
    ResetDetourToBuiltinsOnly(det_vv);

    std::atomic<GlobalCallbackId> seen_nv{ ERROR_ID };
    std::atomic<GlobalCallbackId> seen_vv{ ERROR_ID };

    auto id_nv = det_nv->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            seen_nv.store(info.CommonImpl.GetCallbackId(), std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("GetId_NV"))
    );

    auto id_vv = det_vv->AddCallback(
        [&](auto& info, FTestVoidDetourHolder*, int)
        {
            seen_vv.store(info.CommonImpl.GetCallbackId(), std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("GetId_VV"))
    );

    TI_ASSERT(id_nv != ERROR_ID && id_vv != ERROR_ID, "Failed to register GetCallbackId tests");

    (void)INVOKE_NVOID(1);
    INVOKE_VOID(1);

    TI_ASSERT(seen_nv.load(std::memory_order_relaxed) == id_nv, "NonVoid: GetCallbackId inside callback must match returned Id");
    TI_ASSERT(seen_vv.load(std::memory_order_relaxed) == id_vv, "Void: GetCallbackId inside callback must match returned Id");

    (void)UnregisterCallback(id_nv);
    (void)UnregisterCallback(id_vv);
    det_nv->CollectGarbage();
    det_vv->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// RemoveCallback wrong-detour defensive path (direct call)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_RemoveCallback_WrongDetour, ([this]() -> bool
{
    auto* nv = GetDetourInstance<EDetourTarget::NonVoidTest>();
    auto* vv = GetDetourInstance<EDetourTarget::VoidTest>();
    ResetDetourToBuiltinsOnly(nv);
    ResetDetourToBuiltinsOnly(vv);

    auto id = nv->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int) {},
        EHookType::Pre, Opt(false, STR("NVHook"))
    );
    TI_ASSERT(id != ERROR_ID, "Failed to add NVHook");

    // Calling RemoveCallback on the wrong detour instance must fail (ID belongs to NonVoidTest).
    TI_ASSERT(vv->RemoveCallback(id) == false, "RemoveCallback on wrong detour should fail");

    UnregisterCallback(id);
    nv->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: Collect (all) + sliced + exception safety
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_Collect_Behavior, ([this]() -> bool
{
    auto gc = FCallbackGarbageCollector::GetInstance();

    // Baseline size so our indexing is stable even if other tests add links.
    const size_t base = gc->Links.load(std::memory_order_acquire)->size();

    std::atomic_int a{0}, b{0}, c{0};
    std::atomic_int threw{0};

    gc->AddLink([&]() -> bool { a.fetch_add(1, std::memory_order_relaxed); return false; });
    gc->AddLink([&]() -> bool { b.fetch_add(1, std::memory_order_relaxed); return true;  });
    gc->AddLink([&]() -> bool { c.fetch_add(1, std::memory_order_relaxed); return true;  });
    gc->AddLink([&]() -> bool { threw.fetch_add(1, std::memory_order_relaxed); throw std::runtime_error("gc link boom"); });

    // 1) Collect all links: each should run exactly once in that pass.
    gc->Collect(0, 0);
    TI_ASSERT(a.load() == 1, "Expected link A to run once in Collect(all)");
    TI_ASSERT(b.load() == 1, "Expected link B to run once in Collect(all)");
    TI_ASSERT(c.load() == 1, "Expected link C to run once in Collect(all)");
    TI_ASSERT(threw.load() == 1, "Expected throwing link to run once in Collect(all) (exception is caught)");

    // 2) Sliced collection starting at our first inserted link index.
    //    We expect to stop after first "true" return (that should be link B in our sequence).
    const size_t size_after = gc->Links.load(std::memory_order_acquire)->size();
    TI_ASSERT(size_after >= base + 4, "Expected links to have been appended");

    a.store(0); b.store(0); c.store(0); threw.store(0);

    unsigned long next = gc->Collect(static_cast<unsigned long>(base), 1);
    // In this pass: it should call A (false), then B (true) and stop.
    TI_ASSERT(a.load() == 1, "Sliced: expected A to run once");
    TI_ASSERT(b.load() == 1, "Sliced: expected B to run once and satisfy collection");
    TI_ASSERT(c.load() == 0, "Sliced: expected C to NOT run yet");
    // Thrower might or might not run depending on where it sits relative to stop; in our appended order it's after C,
    // so it should not run in this first sliced pass.
    TI_ASSERT(threw.load() == 0, "Sliced: expected thrower not to run before stopping at first collected=true");

    // next should be the index after the link that returned true (B). Our appended layout:
    // base+0:A, base+1:B, base+2:C, base+3:thrower
    TI_ASSERT(next == ((base + 2) % size_after), "Sliced: next index should advance past the collected=true link");

    // Next sliced pass starting at 'next': should hit C (true) and stop immediately.
    a.store(0); b.store(0); c.store(0); threw.store(0);

    unsigned long next2 = gc->Collect(next, 1);
    TI_ASSERT(c.load() == 1, "Second sliced: expected C to run once and satisfy collection");
    TI_ASSERT(a.load() == 0 && b.load() == 0, "Second sliced: A/B should not run when starting at C");

    // next2 should now be index after C -> base+3 (thrower)
    TI_ASSERT(next2 == ((base + 3) % size_after), "Second sliced: next index should advance past C");

    // Third sliced pass starting at thrower: should catch exception and keep going until it collects 1 true (wraps to B).
    a.store(0); b.store(0); c.store(0); threw.store(0);

    unsigned long next3 = gc->Collect(next2, 1);
    TI_ASSERT(threw.load() == 1, "Third sliced: expected thrower to run once (exception caught)");
    // It will proceed until it finds a true (B or C depending on wrap); B is encountered before C in our appended sequence.
    TI_ASSERT(b.load() == 1, "Third sliced: expected B to be the first true after thrower + wrap");
    (void)next3; // not asserting further index; depends on full list composition if other links exist.

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: AddLink is copy-on-write (atomic shared_ptr swap)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_AddLink_CopyOnWrite, ([this]() -> bool
{
    auto gc = FCallbackGarbageCollector::GetInstance();

    auto before = gc->Links.load(std::memory_order_acquire);
    const size_t base = before->size();

	std::atomic_int hits{0};
	// Return true so a sliced collect can stop immediately after invoking this link.
	gc->AddLink([&]() -> bool { hits.fetch_add(1, std::memory_order_relaxed); return true; });

    auto after = gc->Links.load(std::memory_order_acquire);

    TI_ASSERT(before.get() != after.get(), "Expected AddLink to publish a new link vector (copy-on-write)");
    TI_ASSERT(before->size() == base, "Expected old link vector size to remain unchanged after AddLink");
    TI_ASSERT(after->size() == base + 1, "Expected new link vector to have exactly one additional entry");

	// Prove the new link is callable without relying on or triggering other links.
	gc->Collect(static_cast<unsigned long>(base), 1);
	TI_ASSERT(hits.load() == 1, "Expected newly added link to have been invoked exactly once");

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: StartIdx is bounded by modulo LinkCount
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_Collect_StartIdxModulo, ([this]() -> bool
{
    auto gc = FCallbackGarbageCollector::GetInstance();
    const size_t base = gc->Links.load(std::memory_order_acquire)->size();

    std::atomic_int hits{0};
    gc->AddLink([&]() -> bool { hits.fetch_add(1, std::memory_order_relaxed); return true; });

    const size_t link_count = gc->Links.load(std::memory_order_acquire)->size();
    TI_ASSERT(link_count >= base + 1, "Expected link appended");

    const unsigned long idx = static_cast<unsigned long>(base);
    const unsigned long start = idx + static_cast<unsigned long>(link_count) * 7UL; // guaranteed to modulo back to idx

    (void)gc->Collect(start, 1);
    TI_ASSERT(hits.load() == 1, "Expected modulo-bounded StartIdx to start at our link and invoke it once");

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: Start/Stop thread control (thread is off during tests by design)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_Thread_StartStop, ([this]() -> bool
{
    auto gc = FCallbackGarbageCollector::GetInstance();

    // In the test harness, GC should not already be running.
    TI_ASSERT(gc->StopGCThread() == false, "Expected StopGCThread to return false when thread is not running");

    TI_ASSERT(gc->StartGCThread() == true, "Expected StartGCThread to succeed");
    TI_ASSERT(gc->StartGCThread() == false, "Expected StartGCThread to fail when already running");

    // Stop immediately. Depending on scheduling, this might be instant or might wait up to HOOK_GC_INTERVAL_SECONDS.
    TI_ASSERT(gc->StopGCThread() == true, "Expected StopGCThread to succeed after starting");
    TI_ASSERT(gc->StopGCThread() == false, "Expected StopGCThread to return false after already stopped");

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: gc_fn interval gating (EngineTick callback)
// ------------------------------------------------------------
//DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_EngineTickInterval, ([this]() -> bool
//{
//    auto gc = FCallbackGarbageCollector::GetInstance();
//
//    // Capture base index so we can force gc to start at our link.
//    const size_t base = gc->Links.load(std::memory_order_acquire)->size();
//
//    std::atomic_int gc_hits{0};
//    gc->AddLink([&]() -> bool { gc_hits.fetch_add(1, std::memory_order_relaxed); return true; });
//
//    // Force deterministic behavior for this test.
//    gc->time_since_last_gc = 0.0f;
//    gc->last_index = static_cast<unsigned long>(base);
//
//    TCallbackIterationData<void> dummy_info{ STR("EngineTick") };
//
//    // Below threshold: should not run Collect, so our link should not be hit.
//    gc->gc_fn(dummy_info, nullptr, HOOK_GC_INTERVAL_SECONDS - 0.1f, false);
//    TI_ASSERT(gc_hits.load() == 0, "gc_fn should not run GC before interval elapses");
//
//    // Cross threshold: should run exactly one "true" link (HOOK_GC_LINKS_PER_ITERATION == 1).
//    gc->gc_fn(dummy_info, nullptr, 0.2f, false);
//    TI_ASSERT(gc_hits.load() == 1, "gc_fn should run exactly one GC link after interval elapses");
//    TI_ASSERT(gc->time_since_last_gc == 0.0f, "gc_fn should reset time_since_last_gc after running");
//
//    return true;
//}));

// ------------------------------------------------------------
// UnregisterCallback: default branch on invalid detour bits
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(UnregisterHook_InvalidDetour_DefaultBranch, ([this]() -> bool
{
    // Combine two detour bits so it cannot match any single switch case.
    GlobalCallbackId bogus =
        static_cast<GlobalCallbackId>(EDetourTarget::NonVoidTest) |
        static_cast<GlobalCallbackId>(EDetourTarget::VoidTest) |
        0x1234; // add some "raw Id" noise

    TI_ASSERT(UnregisterCallback(bogus) == false, "Expected UnregisterCallback to fail for invalid combined detour bits");
    return true;
}));

// ------------------------------------------------------------
// DetourInstance: RemoveCallback returns false when ID not found (no dirty flip)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_RemoveCallback_NotFound, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    TI_ASSERT(det->IsDirty() == false, "Detour should start clean");

    GlobalCallbackId missing = static_cast<GlobalCallbackId>(EDetourTarget::NonVoidTest) | 0x999999;
    TI_ASSERT(det->RemoveCallback(missing) == false, "RemoveCallback should fail when ID is not present");

    // If your implementation guarantees "not found" doesn't dirty the detour, keep this:
    TI_ASSERT(det->IsDirty() == false, "Detour should remain clean after RemoveCallback(not found)");

    return true;
}));

// ------------------------------------------------------------
// Post hook: can override original return value
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_PostHook_CanOverrideReturn, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    auto id_post = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            // Original returns true; force false from post.
            (void)info.TrySetReturnValue(false);
        },
        EHookType::Post, Opt(false, STR("PostOverride"))
    );

    TI_ASSERT(id_post != ERROR_ID, "Failed to add post override hook");

    bool rv = INVOKE_NVOID(42);
    TI_ASSERT(rv == false, "Post hook should be able to override return value to false");

    UnregisterCallback(id_post);
    det->CollectGarbage();
    return true;
}));

// ------------------------------------------------------------
// Prevent original: decide whether post hooks still run (spec test)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_PreventOriginal_PostStillRuns, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int post_calls{0};

    auto id_pre = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int) { info.PreventOriginalFunctionCall(); },
        EHookType::Pre, Opt(false, STR("BlockOriginal"))
    );

    auto id_post = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int) { post_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Post, Opt(false, STR("PostAfterBlock"))
    );

    TI_ASSERT(id_pre != ERROR_ID && id_post != ERROR_ID, "Failed to add hooks");

    (void)INVOKE_NVOID(1);

    // If your desired semantics is "post always runs", keep this:
    TI_ASSERT(post_calls.load() == 1, "Post hook should run even if original is prevented");

    UnregisterCallback(id_pre);
    UnregisterCallback(id_post);
    det->CollectGarbage();
    return true;
}));

// ------------------------------------------------------------
// Void detour: basic pre/post + exception invalidation
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_Void_Basic_And_ExceptionInvalidates, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::VoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int pre_calls{0};
    std::atomic_int post_calls{0};
    std::atomic_int throw_calls{0};

    auto id_pre = det->AddCallback(
        [&](auto&, FTestVoidDetourHolder*, int) { pre_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Pre, Opt(false, STR("VoidPre"))
    );

    auto id_post = det->AddCallback(
        [&](auto&, FTestVoidDetourHolder*, int) { post_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Post, Opt(false, STR("VoidPost"))
    );

    auto id_throw = det->AddCallback(
        [&](auto&, FTestVoidDetourHolder*, int)
        {
            throw_calls.fetch_add(1, std::memory_order_relaxed);
            throw std::runtime_error("void boom");
        },
        EHookType::Pre, Opt(false, STR("VoidThrower"))
    );

    TI_ASSERT(id_pre != ERROR_ID && id_post != ERROR_ID && id_throw != ERROR_ID, "Failed to add void hooks");

    INVOKE_VOID(1);
    INVOKE_VOID(2);

    TI_ASSERT(pre_calls.load() >= 2, "Void pre hook should run on each invoke");
    TI_ASSERT(post_calls.load() >= 2, "Void post hook should run on each invoke");
    TI_ASSERT(throw_calls.load() == 1, "Throwing void hook should be invalidated after first throw");

    TI_ASSERT(det->IsDirty(), "Void detour should be dirty after invalidating throwing hook");
    TI_ASSERT(det->CollectGarbage() == true, "Void detour GC should prune invalidated thrower");

    // After GC, unregister should fail.
    TI_ASSERT(UnregisterCallback(id_throw) == false, "UnregisterCallback should fail after GC prunes the thrower");

    UnregisterCallback(id_pre);
    UnregisterCallback(id_post);
    det->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: Collect multiple trues in one call
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_Collect_MultipleTrues, ([this]() -> bool
{
    auto gc = FCallbackGarbageCollector::GetInstance();
    const size_t base = gc->Links.load(std::memory_order_acquire)->size();

    std::atomic_int f1{0}, t1{0}, f2{0}, t2{0};

    gc->AddLink([&]() -> bool { f1++; return false; });
    gc->AddLink([&]() -> bool { t1++; return true;  });
    gc->AddLink([&]() -> bool { f2++; return false; });
    gc->AddLink([&]() -> bool { t2++; return true;  });

    const size_t size_after = gc->Links.load(std::memory_order_acquire)->size();
    TI_ASSERT(size_after >= base + 4, "Expected links appended");

    unsigned long next = gc->Collect((unsigned long)base, 2);

    // Should walk: false, true(1), false, true(2) then stop.
    TI_ASSERT(f1.load() == 1, "Expected first false link to run once");
    TI_ASSERT(t1.load() == 1, "Expected first true link to run once");
    TI_ASSERT(f2.load() == 1, "Expected second false link to run once");
    TI_ASSERT(t2.load() == 1, "Expected second true link to run once");

    // After collecting the 2nd true at base+3, next should be base+4 modulo size.
    TI_ASSERT(next == ((base + 4) % size_after), "Expected next to advance past the 2nd collected=true link");
    return true;
}));

// ------------------------------------------------------------
// Post hook can override return value (when pre doesn't set)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_PostOverride_ReturnValue, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_bool first_set_ok{false};
    std::atomic_bool second_set_ok{true};
	std::atomic_bool saw_setter_ptr_in_second{false};
    std::atomic<GlobalCallbackId> first_setter_id{ ERROR_ID };
    std::atomic<GlobalCallbackId> seen_setter_id_in_second{ ERROR_ID };

    // Post A: set return and record who set it.
    auto id_a = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            first_setter_id.store(info.CommonImpl.GetCallbackId(), std::memory_order_relaxed);
            first_set_ok.store(info.TrySetReturnValue(false), std::memory_order_relaxed);
        },
        EHookType::Post, Opt(false, STR("PostOverride_FirstSetter"))
    );

    // Post B: must fail to override, and must observe that the setter is still A.
    auto id_b = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            second_set_ok.store(info.TrySetReturnValue(true), std::memory_order_relaxed);
			// ReturnOverrideSetter is intentionally a raw pointer to metadata (new impl detail).
			saw_setter_ptr_in_second.store(info.ReturnOverrideSetter != nullptr, std::memory_order_relaxed);
			if (info.ReturnOverrideSetter)
			{
				seen_setter_id_in_second.store(info.ReturnOverrideSetter->Id, std::memory_order_relaxed);
			}
        },
        EHookType::Post, Opt(false, STR("PostOverride_SecondSetter"))
    );

    TI_ASSERT(id_a != ERROR_ID && id_b != ERROR_ID, "Failed to register PostOverride tests");

    bool rv = INVOKE_NVOID(123);
    TI_ASSERT(rv == false, "Expected return=false from first post override");
    TI_ASSERT(first_set_ok.load() == true, "Expected first TrySetReturnValue to succeed");
    TI_ASSERT(second_set_ok.load() == false, "Expected second TrySetReturnValue to fail (set-once semantics)");
	TI_ASSERT(saw_setter_ptr_in_second.load() == true, "Expected ReturnOverrideSetter to be non-null in second callback");
    TI_ASSERT(seen_setter_id_in_second.load() == first_setter_id.load(), "Expected ReturnOverrideSetter to point at first setter");

    (void)UnregisterCallback(id_a);
    (void)UnregisterCallback(id_b);
    det->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// Return override precedence across phases: pre sets, post cannot change it
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_ReturnOverride_PreVsPostPrecedence, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int pre_calls{0};
    std::atomic_int post_calls{0};

    std::atomic_bool pre_set_succeeded{false};
    std::atomic_bool post_set_succeeded{true};

    auto id_pre = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int) -> void
        {
            pre_calls.fetch_add(1, std::memory_order_relaxed);
            pre_set_succeeded.store(info.TrySetReturnValue(false), std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("PreSetter"))
    );

    auto id_post = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int) -> void
        {
            post_calls.fetch_add(1, std::memory_order_relaxed);
            post_set_succeeded.store(info.TrySetReturnValue(true), std::memory_order_relaxed);
        },
        EHookType::Post, Opt(false, STR("PostSetter"))
    );

    TI_ASSERT(id_pre != ERROR_ID && id_post != ERROR_ID, "Failed to add PreSetter/PostSetter hooks");
    TI_ASSERT(PreSize(det) == 1 && PostSize(det) == 1, "Expected 1 prehook and 1 posthook");

    bool rv = INVOKE_NVOID(77);

    TI_ASSERT(pre_calls.load() == 1, "PreSetter should run once");
    TI_ASSERT(post_calls.load() == 1, "PostSetter should run once");
    TI_ASSERT(pre_set_succeeded.load() == true, "Pre override should succeed (first setter)");
    TI_ASSERT(rv == false, "Pre override must win across phases");
    TI_ASSERT(post_set_succeeded.load() == false, "Post setter must fail because return already set in pre");

    UnregisterCallback(id_pre);
    UnregisterCallback(id_post);
    det->CollectGarbage();

    return true;
}));


// ------------------------------------------------------------
// Once callback in POST: executes exactly once then prunes
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_OnceCallback_Post_CallsExactlyOnce, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int once_calls{0};

    auto once_id = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int)
        {
            once_calls.fetch_add(1, std::memory_order_relaxed);
        },
        EHookType::Post, Opt(true, STR("OncePost"))
    );

    TI_ASSERT(once_id != ERROR_ID, "AddCallback returned ERROR_ID for once posthook");
    TI_ASSERT(PostSize(det) == 1, "Expected 1 posthook after adding once posthook");

    (void)INVOKE_NVOID(1);
    (void)INVOKE_NVOID(2);
    (void)INVOKE_NVOID(3);

    TI_ASSERT(once_calls.load() == 1, "Once posthook must execute exactly once across multiple invocations");
    TI_ASSERT(det->IsDirty(), "Once posthook should mark detour dirty after firing");

    TI_ASSERT(det->CollectGarbage() == true, "CollectGarbage should prune the invalidated once posthook");
    TI_ASSERT(PostSize(det) == 0, "Posthook vector should be empty after pruning once posthook");

    (void)UnregisterCallback(once_id); // should not crash

    return true;
}));

// ------------------------------------------------------------
// Invalid callback skip path: manually mark invalid and verify it never runs
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_InvalidCallback_SkippedAndPruned, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int calls{0};

    auto id = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int)
        {
            calls.fetch_add(1, std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("ManualInvalid"))
    );

    TI_ASSERT(id != ERROR_ID, "Failed to add ManualInvalid hook");
    TI_ASSERT(PreSize(det) == 1, "Expected 1 prehook after adding ManualInvalid");

    // Flip invalid *without* unregistering: exercises "skip invalid callback" in the hot path.
    auto vec = det->PreHookCallbacks.load(std::memory_order_acquire);
    TI_ASSERT(vec->size() == 1, "Expected prehook vector size to be 1");
    (*vec)[0]->Invalidate();

    (void)INVOKE_NVOID(42);
    TI_ASSERT(calls.load() == 0, "Manually invalidated hook should be skipped (not executed)");

    // Force GC prune (since we invalidated manually, we must mark dirty ourselves).
    det->bDirty.store(true, std::memory_order_release);
    TI_ASSERT(det->CollectGarbage() == true, "GC should prune manually invalidated hook");
    TI_ASSERT(PreSize(det) == 0, "Prehooks should be empty after pruning manually invalidated hook");

    return true;
}));

// ------------------------------------------------------------
// FCallbackGarbageCollector: sliced collect that must gather 2 trues
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(CallbackGarbageCollector_Collect_TwoTrues, ([this]() -> bool
{
    auto gc = FCallbackGarbageCollector::GetInstance();

    const size_t base = gc->Links.load(std::memory_order_acquire)->size();

    std::atomic_int a{0}, b{0}, c{0}, d{0};

    gc->AddLink([&]() -> bool { a.fetch_add(1, std::memory_order_relaxed); return false; });
    gc->AddLink([&]() -> bool { b.fetch_add(1, std::memory_order_relaxed); return true;  });
    gc->AddLink([&]() -> bool { c.fetch_add(1, std::memory_order_relaxed); return true;  });
    gc->AddLink([&]() -> bool { d.fetch_add(1, std::memory_order_relaxed); return false; });

    const size_t size_after = gc->Links.load(std::memory_order_acquire)->size();
    TI_ASSERT(size_after >= base + 4, "Expected links to have been appended (TwoTrues test)");

    unsigned long next = gc->Collect(static_cast<unsigned long>(base), 2);

    // Should run A, then B(true #1), then C(true #2) and stop (D should not run).
    TI_ASSERT(a.load() == 1, "TwoTrues: expected A to run once");
    TI_ASSERT(b.load() == 1, "TwoTrues: expected B to run once");
    TI_ASSERT(c.load() == 1, "TwoTrues: expected C to run once");
    TI_ASSERT(d.load() == 0, "TwoTrues: expected D to NOT run (stop after collecting 2 trues)");

    // next should advance past C -> base+3
    TI_ASSERT(next == ((base + 3) % size_after), "TwoTrues: next index should advance past second collected=true");

    return true;
}));

// ------------------------------------------------------------
// All callbacks always run (NonVoid): even if PreventOriginal is called and a callback throws,
// later callbacks in the same pass must still run. Also validates "thrower is skipped" on next invoke.
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_AllCallbacksAlwaysRun_NonVoid, ([this]() -> bool
{
    // Updated semantics: a throwing callback invalidates itself and aborts the remainder of the *current* pass,
    // but does not prevent original execution nor later phases. Next invocation skips the invalid callback.
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int pre1{0}, pre2_throw{0}, pre3{0};
    std::atomic_int post1{0}, post2{0};

    std::atomic_bool post_saw_original_true_first{false};
    std::atomic_bool post_saw_resolved_true_first{false};
    std::atomic_bool post_saw_resolved_false_second{false};

    auto id_pre1 = det->AddCallback(
        [&](auto& /*info*/, FTestNonVoidDetourHolder*, int)
        {
            pre1.fetch_add(1, std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("AllRun_NV_Pre1"))
    );

    auto id_pre2 = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int)
        {
            pre2_throw.fetch_add(1, std::memory_order_relaxed);
            throw std::runtime_error("AllRun nonvoid boom");
        },
        EHookType::Pre, Opt(false, STR("AllRun_NV_Pre2_Throw"))
    );

    // This callback is *after* the thrower and should not run on the first invoke, but should run on the second.
    auto id_pre3 = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            pre3.fetch_add(1, std::memory_order_relaxed);
            // Override return without preventing original; original should still run and set OriginalFunctionCallResult=true.
            (void)info.TrySetReturnValue(false);
        },
        EHookType::Pre, Opt(false, STR("AllRun_NV_Pre3_SetRV"))
    );

    auto id_post1 = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            post1.fetch_add(1, std::memory_order_relaxed);
            if (post1.load() == 1)
            {
                post_saw_original_true_first.store(info.GetOriginalFunctionCallResult() == true, std::memory_order_relaxed);
                post_saw_resolved_true_first.store(info.GetCurrentResolvedReturnValue() == true, std::memory_order_relaxed);
            }
            else
            {
                post_saw_resolved_false_second.store(info.GetCurrentResolvedReturnValue() == false, std::memory_order_relaxed);
            }
        },
        EHookType::Post, Opt(false, STR("AllRun_NV_Post1"))
    );

    auto id_post2 = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int)
        {
            post2.fetch_add(1, std::memory_order_relaxed);
        },
        EHookType::Post, Opt(false, STR("AllRun_NV_Post2"))
    );

    TI_ASSERT(id_pre1 != ERROR_ID && id_pre2 != ERROR_ID && id_pre3 != ERROR_ID && id_post1 != ERROR_ID && id_post2 != ERROR_ID,
              "AllRun NonVoid: failed to add hooks");

    // Invocation 1: Pre2 throws, so Pre3 does NOT run. Original still runs. Resolved return stays original=true.
    bool rv = INVOKE_NVOID(123);
    TI_ASSERT(rv == true, "AllRun NonVoid: expected return=true (Pre3 didn't run, original did)");
    TI_ASSERT(pre1.load() == 1, "AllRun NonVoid: Pre1 must run");
    TI_ASSERT(pre2_throw.load() == 1, "AllRun NonVoid: Pre2 must run once and throw");
    TI_ASSERT(pre3.load() == 0, "AllRun NonVoid: Pre3 must NOT run in same pass after throw");
    TI_ASSERT(post1.load() == 1 && post2.load() == 1, "AllRun NonVoid: post hooks must run even if a prehook throws");
    TI_ASSERT(post_saw_original_true_first.load() == true, "AllRun NonVoid: post must see original result=true");
    TI_ASSERT(post_saw_resolved_true_first.load() == true, "AllRun NonVoid: resolved return should be original=true on first invoke");

    // Invocation 2: Pre2 is invalidated and skipped, so Pre3 runs and overrides return to false.
    rv = INVOKE_NVOID(456);
    TI_ASSERT(rv == false, "AllRun NonVoid: expected return=false due to Pre3 override on second invoke");
    TI_ASSERT(pre1.load() == 2, "AllRun NonVoid: Pre1 must run again");
    TI_ASSERT(pre2_throw.load() == 1, "AllRun NonVoid: thrower must NOT run again after invalidation");
    TI_ASSERT(pre3.load() == 1, "AllRun NonVoid: Pre3 must run on second invoke");
    TI_ASSERT(post1.load() == 2 && post2.load() == 2, "AllRun NonVoid: post hooks must run again");
    TI_ASSERT(post_saw_resolved_false_second.load() == true, "AllRun NonVoid: post must see resolved return=false on second invoke");

    (void)UnregisterCallback(id_pre1);
    (void)UnregisterCallback(id_pre2);
    (void)UnregisterCallback(id_pre3);
    (void)UnregisterCallback(id_post1);
    (void)UnregisterCallback(id_post2);
    det->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// All callbacks always run (Void specialization): same guarantees as NonVoid,
// exception aborts the remainder of that phase + "thrower skipped next time".
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_AllCallbacksAlwaysRun_Void, ([this]() -> bool
{
    // Same story as NonVoid: throwing callback aborts the remainder of the current pass,
    // but post hooks still run and the thrower is skipped on subsequent invocations.
    auto* det = GetDetourInstance<EDetourTarget::VoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int pre1{0}, pre2_throw{0}, pre3{0};
    std::atomic_int post1{0}, post2{0};
    std::atomic_bool pre3_saw_prevent{false};
    std::atomic_bool post_saw_prevent_first{false};

    auto id_pre1 = det->AddCallback(
        [&](auto& info, FTestVoidDetourHolder*, int)
        {
            pre1.fetch_add(1, std::memory_order_relaxed);
            info.PreventOriginalFunctionCall();
        },
        EHookType::Pre, Opt(false, STR("AllRun_VV_Pre1_Block"))
    );

    auto id_pre2 = det->AddCallback(
        [&](auto&, FTestVoidDetourHolder*, int)
        {
            pre2_throw.fetch_add(1, std::memory_order_relaxed);
            throw std::runtime_error("AllRun void boom");
        },
        EHookType::Pre, Opt(false, STR("AllRun_VV_Pre2_Throw"))
    );

    // After the thrower.
    auto id_pre3 = det->AddCallback(
        [&](auto& info, FTestVoidDetourHolder*, int)
        {
            pre3.fetch_add(1, std::memory_order_relaxed);
            pre3_saw_prevent.store(info.OriginalFunctionCallPrevented(), std::memory_order_relaxed);
        },
        EHookType::Pre, Opt(false, STR("AllRun_VV_Pre3_Observe"))
    );

    auto id_post1 = det->AddCallback(
        [&](auto& info, FTestVoidDetourHolder*, int)
        {
            post1.fetch_add(1, std::memory_order_relaxed);
            if (post1.load() == 1)
            {
                post_saw_prevent_first.store(info.OriginalFunctionCallPrevented(), std::memory_order_relaxed);
            }
        },
        EHookType::Post, Opt(false, STR("AllRun_VV_Post1"))
    );

    auto id_post2 = det->AddCallback(
        [&](auto&, FTestVoidDetourHolder*, int)
        {
            post2.fetch_add(1, std::memory_order_relaxed);
        },
        EHookType::Post, Opt(false, STR("AllRun_VV_Post2"))
    );

    TI_ASSERT(id_pre1 != ERROR_ID && id_pre2 != ERROR_ID && id_pre3 != ERROR_ID && id_post1 != ERROR_ID && id_post2 != ERROR_ID,
              "AllRun Void: failed to add hooks");

    // Invocation 1: Pre2 throws, so Pre3 does NOT run. Post hooks still run and observe the prevent flag.
    INVOKE_VOID(1);
    TI_ASSERT(pre1.load() == 1, "AllRun Void: Pre1 must run");
    TI_ASSERT(pre2_throw.load() == 1, "AllRun Void: Pre2 must run once and throw");
    TI_ASSERT(pre3.load() == 0, "AllRun Void: Pre3 must NOT run in same pass after throw");
    TI_ASSERT(post1.load() == 1 && post2.load() == 1, "AllRun Void: post hooks must run even if a prehook throws");
    TI_ASSERT(post_saw_prevent_first.load() == true, "AllRun Void: post should see OriginalFunctionCallPrevented=true");

    // Invocation 2: thrower skipped, so Pre3 runs and sees prevent flag set by Pre1.
    INVOKE_VOID(2);
    TI_ASSERT(pre1.load() == 2, "AllRun Void: Pre1 must run again");
    TI_ASSERT(pre2_throw.load() == 1, "AllRun Void: thrower must NOT run again after invalidation");
    TI_ASSERT(pre3.load() == 1, "AllRun Void: Pre3 must run on second invoke");
    TI_ASSERT(pre3_saw_prevent.load() == true, "AllRun Void: Pre3 should see OriginalFunctionCallPrevented=true");
    TI_ASSERT(post1.load() == 2 && post2.load() == 2, "AllRun Void: post hooks must run again");

    (void)UnregisterCallback(id_pre1);
    (void)UnregisterCallback(id_pre2);
    (void)UnregisterCallback(id_pre3);
    (void)UnregisterCallback(id_post1);
    (void)UnregisterCallback(id_post2);
    det->CollectGarbage();

    return true;
}));

// ------------------------------------------------------------
// UnregisterCallback: tiny routing + default-failure path
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(UnregisterHook_Basics, ([this]() -> bool
{
    // NonVoid
    {
        auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
        ResetDetourToBuiltinsOnly(det);

        auto id = det->AddCallback(
            [&](auto&, FTestNonVoidDetourHolder*, int) {},
            EHookType::Pre, Opt(false, STR("Unregister_NV"))
        );
        TI_ASSERT(id != ERROR_ID, "UnregisterHook_Basics: failed to add NonVoid hook");

        TI_ASSERT(UnregisterCallback(id) == true, "UnregisterHook_Basics: UnregisterCallback should succeed for NonVoid Id");
        TI_ASSERT(det->IsDirty(), "UnregisterHook_Basics: detour should be dirty after UnregisterCallback");
        TI_ASSERT(det->CollectGarbage() == true, "UnregisterHook_Basics: GC should prune removed NonVoid hook");
        TI_ASSERT(PreSize(det) == 0, "UnregisterHook_Basics: NonVoid prehook vector should be empty after GC");
    }

    // Void
    {
        auto* det = GetDetourInstance<EDetourTarget::VoidTest>();
        ResetDetourToBuiltinsOnly(det);

        auto id = det->AddCallback(
            [&](auto&, FTestVoidDetourHolder*, int) {},
            EHookType::Pre, Opt(false, STR("Unregister_V"))
        );
        TI_ASSERT(id != ERROR_ID, "UnregisterHook_Basics: failed to add Void hook");

        TI_ASSERT(UnregisterCallback(id) == true, "UnregisterHook_Basics: UnregisterCallback should succeed for Void Id");
        TI_ASSERT(det->IsDirty(), "UnregisterHook_Basics: void detour should be dirty after UnregisterCallback");
        TI_ASSERT(det->CollectGarbage() == true, "UnregisterHook_Basics: GC should prune removed Void hook");
        TI_ASSERT(PreSize(det) == 0, "UnregisterHook_Basics: Void prehook vector should be empty after GC");
    }

    // Default/failure path: Id=0 should not map to any detour
    TI_ASSERT(UnregisterCallback(0) == false, "UnregisterHook_Basics: UnregisterCallback(0) should fail (default branch)");

    return true;
}));

// ------------------------------------------------------------
// Readonly ordering: NonVoid (clean + dirty AddCallback paths)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_ReadonlyOrdering_NonVoid, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::mutex m;
    std::vector<int> order;
    order.reserve(16);

    auto push = [&](int v)
    {
        std::lock_guard<std::mutex> _{m};
        order.push_back(v);
    };

    auto optR1 = Opt(false, STR("R1")); optR1.bReadonly = true;
    auto optN1 = Opt(false, STR("N1")); // non-readonly
    auto optR2 = Opt(false, STR("R2")); optR2.bReadonly = true;
    auto optN2 = Opt(false, STR("N2"));
    auto optN3 = Opt(false, STR("N3"));
    auto optR3 = Opt(false, STR("R3")); optR3.bReadonly = true;

    // Intentionally add in a "weird" order to ensure insertion rules are enforced.
    auto id_r1 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(101); }, EHookType::Pre, optR1);
    auto id_n1 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(1);   }, EHookType::Pre, optN1);
    auto id_r2 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(102); }, EHookType::Pre, optR2);
    auto id_n2 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(2);   }, EHookType::Pre, optN2);
    auto id_n3 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(3);   }, EHookType::Pre, optN3);
    auto id_r3 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(103); }, EHookType::Pre, optR3);

    TI_ASSERT(id_r1 != ERROR_ID && id_n1 != ERROR_ID && id_r2 != ERROR_ID &&
              id_n2 != ERROR_ID && id_n3 != ERROR_ID && id_r3 != ERROR_ID,
              "Failed to add one or more hooks");

    // Clean path expected execution: non-readonly in add order (N1,N2,N3), then readonly in add order (R1,R2,R3).
    order.clear();
    (void)INVOKE_NVOID(1);

    TI_ASSERT(order.size() == 6, "Expected exactly 6 callbacks to run (clean path)");
    TI_ASSERT(order[0] == 1,   "Order mismatch: expected N1 first");
    TI_ASSERT(order[1] == 2,   "Order mismatch: expected N2 second");
    TI_ASSERT(order[2] == 3,   "Order mismatch: expected N3 third");
    TI_ASSERT(order[3] == 101, "Order mismatch: expected R1 fourth");
    TI_ASSERT(order[4] == 102, "Order mismatch: expected R2 fifth");
    TI_ASSERT(order[5] == 103, "Order mismatch: expected R3 sixth");

    // Force dirty path: invalidate N1 (don't GC yet), then add more hooks.
    TI_ASSERT(UnregisterCallback(id_n1), "Failed to unregister N1 (to force dirty path)");

    auto optN4 = Opt(false, STR("N4"));
    auto optR4 = Opt(false, STR("R4")); optR4.bReadonly = true;

    auto id_n4 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(4);   }, EHookType::Pre, optN4);
    auto id_r4 = det->AddCallback([&](auto&, FTestNonVoidDetourHolder*, int){ push(104); }, EHookType::Pre, optR4);

    TI_ASSERT(id_n4 != ERROR_ID && id_r4 != ERROR_ID, "Failed to add N4/R4 hooks while dirty");

    // Dirty path expected: N1 pruned, N2,N3 keep order, N4 appended after them (still before readonly),
    // then readonly R1,R2,R3 keep order, then R4 last.
    order.clear();
    (void)INVOKE_NVOID(2);

    TI_ASSERT(order.size() == 7, "Expected exactly 7 callbacks to run (dirty path, N1 pruned)");
    TI_ASSERT(order[0] == 2,   "Dirty order mismatch: expected N2 first");
    TI_ASSERT(order[1] == 3,   "Dirty order mismatch: expected N3 second");
    TI_ASSERT(order[2] == 4,   "Dirty order mismatch: expected N4 third");
    TI_ASSERT(order[3] == 101, "Dirty order mismatch: expected R1 fourth");
    TI_ASSERT(order[4] == 102, "Dirty order mismatch: expected R2 fifth");
    TI_ASSERT(order[5] == 103, "Dirty order mismatch: expected R3 sixth");
    TI_ASSERT(order[6] == 104, "Dirty order mismatch: expected R4 seventh");

    // Cleanup: unregister remaining hooks + prune.
    (void)UnregisterCallback(id_r1);
    (void)UnregisterCallback(id_r2);
    (void)UnregisterCallback(id_r3);
    (void)UnregisterCallback(id_n2);
    (void)UnregisterCallback(id_n3);
    (void)UnregisterCallback(id_n4);
    (void)UnregisterCallback(id_r4);
    det->CollectGarbage();

    ResetDetourToBuiltinsOnly(det);
    return true;
}));

// ------------------------------------------------------------
// Readonly immutability: readonly callback cannot mutate ICallbackIterationData (NonVoid)
// - PreventOriginalFunctionCall + TrySetReturnValue from readonly must not affect behavior
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_Readonly_CannotMutateIterationData_NonVoid, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int mutable_pre_calls{0};
    std::atomic_int readonly_pre_calls{0};
    std::atomic_bool readonly_tryset_ok{true};
    std::atomic_bool post_saw_original_result{false};

    // A normal (mutable) prehook so we also prove readonly runs after non-readonly.
    auto id_mut_pre = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int){ mutable_pre_calls.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Pre, Opt(false, STR("MutablePre"))
    );
    TI_ASSERT(id_mut_pre != ERROR_ID, "Failed to add MutablePre hook");

    // Readonly prehook attempts to mutate the iteration data.
    auto ro_opts = Opt(false, STR("ReadonlyPre"));
    ro_opts.bReadonly = true;

    auto id_ro_pre = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            readonly_pre_calls.fetch_add(1, std::memory_order_relaxed);

            // These are non-const mutators; readonly must not be able to change behavior.
            info.PreventOriginalFunctionCall();
            bool ok = info.TrySetReturnValue(false);
            readonly_tryset_ok.store(ok, std::memory_order_relaxed);
        },
        EHookType::Pre, ro_opts
    );
    TI_ASSERT(id_ro_pre != ERROR_ID, "Failed to add ReadonlyPre hook");

    // Posthook to confirm the original function actually ran.
    auto id_post = det->AddCallback(
        [&](auto& info, FTestNonVoidDetourHolder*, int)
        {
            post_saw_original_result.store(info.GetOriginalFunctionCallResult(), std::memory_order_relaxed);
        },
        EHookType::Post, Opt(false, STR("PostObserver"))
    );
    TI_ASSERT(id_post != ERROR_ID, "Failed to add PostObserver hook");

    bool rv = INVOKE_NVOID(123);

    TI_ASSERT(mutable_pre_calls.load() == 1, "Expected mutable prehook to run once");
    TI_ASSERT(readonly_pre_calls.load() == 1, "Expected readonly prehook to run once");
    TI_ASSERT(readonly_tryset_ok.load() == false, "Readonly TrySetReturnValue must not succeed");
    TI_ASSERT(post_saw_original_result.load() == true, "Readonly PreventOriginalFunctionCall must not prevent original execution");
    TI_ASSERT(rv == true, "Readonly attempts must not change return value; expected original return=true");

    // Cleanup
    (void)UnregisterCallback(id_mut_pre);
    (void)UnregisterCallback(id_ro_pre);
    (void)UnregisterCallback(id_post);
    det->CollectGarbage();

    ResetDetourToBuiltinsOnly(det);
    return true;
}));

// ------------------------------------------------------------
// Readonly ordering: Void specialization (clean + dirty AddCallback paths)
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(Detour_ReadonlyOrdering_Void, ([this]() -> bool
{
    auto* det = GetDetourInstance<EDetourTarget::VoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::mutex m;
    std::vector<int> order;
    order.reserve(16);

    auto push = [&](int v)
    {
        std::lock_guard<std::mutex> _{m};
        order.push_back(v);
    };

    auto optR1 = Opt(false, STR("R1")); optR1.bReadonly = true;
    auto optN1 = Opt(false, STR("N1"));
    auto optR2 = Opt(false, STR("R2")); optR2.bReadonly = true;
    auto optN2 = Opt(false, STR("N2"));
    auto optN3 = Opt(false, STR("N3"));
    auto optR3 = Opt(false, STR("R3")); optR3.bReadonly = true;

    auto id_r1 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(101); }, EHookType::Pre, optR1);
    auto id_n1 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(1);   }, EHookType::Pre, optN1);
    auto id_r2 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(102); }, EHookType::Pre, optR2);
    auto id_n2 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(2);   }, EHookType::Pre, optN2);
    auto id_n3 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(3);   }, EHookType::Pre, optN3);
    auto id_r3 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(103); }, EHookType::Pre, optR3);

    TI_ASSERT(id_r1 != ERROR_ID && id_n1 != ERROR_ID && id_r2 != ERROR_ID &&
              id_n2 != ERROR_ID && id_n3 != ERROR_ID && id_r3 != ERROR_ID,
              "Failed to add one or more void hooks");

    order.clear();
    INVOKE_VOID(1);

    TI_ASSERT(order.size() == 6, "Expected exactly 6 callbacks to run (void clean path)");
    TI_ASSERT(order[0] == 1,   "Void order mismatch: expected N1 first");
    TI_ASSERT(order[1] == 2,   "Void order mismatch: expected N2 second");
    TI_ASSERT(order[2] == 3,   "Void order mismatch: expected N3 third");
    TI_ASSERT(order[3] == 101, "Void order mismatch: expected R1 fourth");
    TI_ASSERT(order[4] == 102, "Void order mismatch: expected R2 fifth");
    TI_ASSERT(order[5] == 103, "Void order mismatch: expected R3 sixth");

    // Dirty path: unregister N1 then add N4 + R4.
    TI_ASSERT(UnregisterCallback(id_n1), "Failed to unregister void N1 (to force dirty path)");

    auto optN4 = Opt(false, STR("N4"));
    auto optR4 = Opt(false, STR("R4")); optR4.bReadonly = true;

    auto id_n4 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(4);   }, EHookType::Pre, optN4);
    auto id_r4 = det->AddCallback([&](auto&, FTestVoidDetourHolder*, int){ push(104); }, EHookType::Pre, optR4);

    TI_ASSERT(id_n4 != ERROR_ID && id_r4 != ERROR_ID, "Failed to add void N4/R4 hooks while dirty");

    order.clear();
    INVOKE_VOID(2);

    TI_ASSERT(order.size() == 7, "Expected exactly 7 callbacks to run (void dirty path, N1 pruned)");
    TI_ASSERT(order[0] == 2,   "Void dirty order mismatch: expected N2 first");
    TI_ASSERT(order[1] == 3,   "Void dirty order mismatch: expected N3 second");
    TI_ASSERT(order[2] == 4,   "Void dirty order mismatch: expected N4 third");
    TI_ASSERT(order[3] == 101, "Void dirty order mismatch: expected R1 fourth");
    TI_ASSERT(order[4] == 102, "Void dirty order mismatch: expected R2 fifth");
    TI_ASSERT(order[5] == 103, "Void dirty order mismatch: expected R3 sixth");
    TI_ASSERT(order[6] == 104, "Void dirty order mismatch: expected R4 seventh");

    // Cleanup
    (void)UnregisterCallback(id_r1);
    (void)UnregisterCallback(id_r2);
    (void)UnregisterCallback(id_r3);
    (void)UnregisterCallback(id_n2);
    (void)UnregisterCallback(id_n3);
    (void)UnregisterCallback(id_n4);
    (void)UnregisterCallback(id_r4);
    det->CollectGarbage();

    ResetDetourToBuiltinsOnly(det);
    return true;
}));

// ------------------------------------------------------------
// Tiny UnregisterCallback test: invalid Id + readonly hook Id
// ------------------------------------------------------------
DEFINE_UNIT_TEST_INSTANCE_LAMBDA(UnregisterHook_ReadonlyAndInvalidId, ([this]() -> bool
{
    TI_ASSERT(UnregisterCallback(0) == false, "UnregisterCallback(0) should fail (invalid Id)");

    auto* det = GetDetourInstance<EDetourTarget::NonVoidTest>();
    ResetDetourToBuiltinsOnly(det);

    std::atomic_int hits{0};

    auto ro_opts = Opt(false, STR("ReadonlyHit"));
    ro_opts.bReadonly = true;

    auto id = det->AddCallback(
        [&](auto&, FTestNonVoidDetourHolder*, int){ hits.fetch_add(1, std::memory_order_relaxed); },
        EHookType::Pre, ro_opts
    );
    TI_ASSERT(id != ERROR_ID, "Failed to add readonly hook");

    TI_ASSERT(UnregisterCallback(id) == true, "UnregisterCallback should succeed for a valid readonly hook Id");

    // Should be skipped immediately even before GC.
    (void)INVOKE_NVOID(5);
    TI_ASSERT(hits.load() == 0, "Unregistered hook must not execute");

    TI_ASSERT(det->CollectGarbage() == true, "GC should prune after unregistering readonly hook");

    TI_ASSERT(UnregisterCallback(id) == false, "UnregisterCallback should fail after GC prunes the callback");

    ResetDetourToBuiltinsOnly(det);
    return true;
}));

#pragma endregion

#pragma region Integration Tests

#define INT_START std::latch cb_latch{1}; bool success = true
#define INT_END cb_latch.wait(); return success;
#define INT_EXEC_FAIL success = false; cb_latch.count_down(); return;
#define INT_PASS cb_latch.count_down();
#define INT_ASSERT_OBJECT(cmp, msg) { bool test = false; RC::Unreal::UObjectGlobals::ForEachUObject([this, & cmp, &test](Unreal::UObject* obj, ...){ if(obj == (cmp)) { test = true; return LoopAction::Break; } return LoopAction::Continue; }); TI_ASSERT_MSG(test, msg, INT_EXEC_FAIL); }

DEFINE_INT_TEST_INSTANCE_LAMBDA(ProcessEvent_Int, ([this]() -> bool {
    INT_START;

    RegisterProcessEventPostCallback([&](auto& info, Unreal::UObject* context, Unreal::UFunction* function, void* params) {
        TI_ASSERT_MSG(context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        TI_ASSERT_MSG(function, "Function was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(context, "Context is not a UObject!");
        INT_ASSERT_OBJECT(function, "Function is not a UObject!");
        INT_PASS;
    },{true, true, STR("IntegrationTest"), STR("ProcessEvent_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(SCO_Int, ([this]() -> bool {
    INT_START;

    RegisterStaticConstructObjectPostCallback([&](auto& info, const Unreal::FStaticConstructObjectParameters& params) {
        TI_ASSERT_MSG(params.Class, "Params.Class was nullptr! Are params aligned?", INT_EXEC_FAIL);
        //TI_ASSERT_MSG(params.Outer, "Params.Outer was nullptr! Are params aligned?", INT_EXEC_FAIL);
        TI_ASSERT_MSG(params.Name.ToString().size(), "Name was empty! Are params aligned?", INT_EXEC_FAIL);
        //TI_ASSERT_MSG(params.InstanceGraph, "Params.InstanceGraph was nullptr! Are params aligned?", INT_EXEC_FAIL);
        // The other fields of FStaticConstructObjectParameters aren't verifiable
        auto cls = params.Class;
        auto outer = params.Outer;
        INT_ASSERT_OBJECT(cls, "Params.Class is not a UObject!");
        //INT_ASSERT_OBJECT(outer, "Params.Outer is not a UObject!");

        Unreal::UObject* rval = info.GetCurrentResolvedReturnValue();
        TI_ASSERT_MSG(rval, "Return value was nullptr! Is it being set right?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(rval, "Return value is not a known object! Is it being constructed outside of the game context?");
        INT_PASS;
    },{true, true, STR("IntegrationTest"), STR("SCO_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(ProcessInternal_Int, ([this]() -> bool {
    INT_START;

    RegisterProcessInternalPreCallback([&](auto& info, Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL) -> void {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");

        // if Stack.Object() is a valid object, it's likely that the rest of FFrame is well-formed, though this isn't to test FFrame.
        auto& obj_ref = Stack.Object();
        TI_ASSERT_MSG(obj_ref, "Stack.Object() was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(obj_ref, "Stack.Object() is not a known object!");

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("ProcessInternal_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(ProcessLocalScriptFunction_Int, ([this]() -> bool {
    INT_START;

    RegisterProcessLocalScriptFunctionPreCallback([&](auto& info, Unreal::UObject* Context, Unreal::FFrame& Stack, void* RESULT_DECL) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");

        // if Stack.Object() is a valid object, it's likely that the rest of FFrame is well-formed, though this isn't to test FFrame.
        auto& obj_ref = Stack.Object();
        TI_ASSERT_MSG(obj_ref, "Stack.Object() was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(obj_ref, "Stack.Object() is not a known object!");

        INT_PASS;
    },{true, true, STR("IntegrationTest"), STR("ProcessLocalScriptFunction_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(LoadMap_Int, ([this]() -> bool {
    INT_START;

    RegisterLoadMapPreCallback([&](auto& info, Unreal::UEngine* Context, Unreal::FWorldContext& WorldContext, Unreal::FURL URL, Unreal::UPendingNetGame* PendingGame, Unreal::FString& Error) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::UEngine>(Context), "Context was not UEngine!", INT_EXEC_FAIL);

        TI_ASSERT_MSG(URL.Map.Len(), "URL Map was empty! FURL is possibly malformed!", INT_EXEC_FAIL);

        //TI_ASSERT_MSG(PendingGame, "PendingGame was nullptr! Are params aligned?", INT_EXEC_FAIL);
        //auto game = std::bit_cast<Unreal::UObject*>(PendingGame);
        //INT_ASSERT_OBJECT(game, "PendingGame is not a UObject!");

        INT_PASS;
    },{true, true, STR("IntegrationTest"), STR("LoadMap_INT")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(EngineTick_Int, ([this]() -> bool {
    INT_START;

    RegisterEngineTickPreCallback([&](auto& info, Unreal::UEngine* Context, float DeltaSeconds, bool bIdleMode) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::UEngine>(Context), "Context was not UEngine!", INT_EXEC_FAIL);

        INT_PASS;
    },{true, true, STR("IntegrationTest"), STR("EngineTick_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(InitGameState_Int, ([this]() -> bool {
    INT_START;

    RegisterInitGameStatePreCallback([&](auto& info, Unreal::AGameModeBase* Context) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::AGameModeBase>(Context), "Context was not AGameModeBase!", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("InitGameState_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(BeginPlay_Int, ([this]() -> bool {
    INT_START;

    RegisterBeginPlayPreCallback([&](auto& info, Unreal::AActor* Context) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::AActor>(Context), "Context was not AActor!", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("BeginPlay_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(EndPlay_Int, ([this]() -> bool {
    INT_START;

    RegisterEndPlayPreCallback([&](auto& info, Unreal::AActor* Context, Unreal::EEndPlayReason EndPlayReason) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::AActor>(Context), "Context was not AActor!", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("EndPlay_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(AActorTick_Int, ([this]() -> bool {
    INT_START;

    RegisterAActorTickPreCallback([&](auto& info, Unreal::AActor* Context, float DeltaSeconds) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::AActor>(Context), "Context was not AActor!", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("AActorTick_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(GameViewportClientTick_Int, ([this]() -> bool {
    INT_START;

    RegisterGameViewportClientTickPreCallback([&](auto& info, Unreal::UGameViewportClient* Context, float DeltaSeconds) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::UGameViewportClient>(Context), "Context was not UGameViewportClient!", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("GameViewportClientTick_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(ULocalPlayerExec_Int, ([this]() -> bool {
    INT_START;

    RegisterULocalPlayerExecPreCallback([&](auto& info, Unreal::ULocalPlayer* Context, Unreal::UWorld* InWorld, const TCHAR* Cmd, Unreal::FOutputDevice& Ar) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        TI_ASSERT_MSG(Unreal::Cast<Unreal::ULocalPlayer>(Context), "Context was not ULocalPlayer!", INT_EXEC_FAIL);

        TI_ASSERT_MSG(InWorld, "InWorld was nullptr! Are params aligned?", INT_EXEC_FAIL);

        auto str = std::wstring_view(Cmd);
        TI_ASSERT_MSG(str.size(), "Cmd was empty, was it captured correctly?", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("ULocalPlayerExec_Int")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(ProcessConsoleExec_Int, ([this]() -> bool {
    INT_START;
    OutputErrorMessage(STR("Enter a valid console command to run this test, like 'ReloadGlobalShaders'. An invalid command will fail the test!"));
    RegisterProcessConsoleExecGlobalPreCallback([&](auto& info, Unreal::UObject* Context, const TCHAR* Cmd, Unreal::FOutputDevice& Ar, Unreal::UObject* Executor) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        TI_ASSERT_MSG(Cmd, "Cmd was nullptr! Are params aligned?", INT_EXEC_FAIL);
        //TI_ASSERT_MSG(Executor, "Executor was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");
        //INT_ASSERT_OBJECT(Executor, "Context is not a UObject!");

        auto str = std::wstring_view(Cmd);
        TI_ASSERT_MSG(str.size(), "Cmd was empty, was it captured correctly?", INT_EXEC_FAIL);
        INT_PASS;
    },{true, true, STR("IntegrationTest"), STR("ProcessConsoleExec")});

    INT_END;
}));

DEFINE_INT_TEST_INSTANCE_LAMBDA(CFBNWA_Int, ([this]() -> bool {
    INT_START;

    RegisterCallFunctionByNameWithArgumentsPreCallback([&](auto& info, Unreal::UObject* Context, const TCHAR* Str, Unreal::FOutputDevice& Ar, Unreal::UObject* Executor, bool bForceCallWithNonExec) {
        TI_ASSERT_MSG(Context, "Context was nullptr! Are params aligned?", INT_EXEC_FAIL);
        INT_ASSERT_OBJECT(Context, "Context is not a UObject!");

        //TI_ASSERT_MSG(Executor, "Executor was nullptr! Are params aligned?", INT_EXEC_FAIL);
        //INT_ASSERT_OBJECT(Executor, "Executor is not a UObject!");

        auto str = std::wstring_view(Str);
        TI_ASSERT_MSG(str.size(), "Cmd was empty, was it captured correctly?", INT_EXEC_FAIL);

        INT_PASS;
    }, {true, true, STR("IntegrationTest"), STR("CFBNWA_Int")});

    INT_END;
}));

#pragma endregion


#undef INT_EXEC_FAIL
#undef INT_START
#undef INT_END
#undef DEFINE_UNIT_TEST_INSTANCE_LAMBDA


#undef DEFINE_TEST_INSTANCE_LAMBDA
#undef TI_ASSERT
#undef INVOKE_VOID
#undef INVOKE_NVOID
#endif