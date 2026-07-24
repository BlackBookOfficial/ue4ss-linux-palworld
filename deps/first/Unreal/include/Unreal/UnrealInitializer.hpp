#pragma once

#include "Constructs/Generator.hpp"


#include <cstdint>
#include <functional>
#include <filesystem>
#include <thread>

#include <File/File.hpp>
#include <SigScanner/SinglePassSigScanner.hpp>

#include <Unreal/Common.hpp>
#include <Unreal/UObjectGlobals.hpp>

namespace RC
{
    class SignatureContainer;

    namespace Unreal::Signatures
    {
        struct ScanResult;
    }
}

namespace RC::Unreal::UnrealInitializer
{
    // Method for resolving function addresses for hooks
    enum class FunctionResolveMethod
    {
        Scan,    // Use PatternSleuth AOB scan (fallback to VTable if scan fails)
        VTable,  // Use vtable lookup (fallback to Scan if vtable lookup fails)
    };

    // Method for converting FName to string
    enum class FNameToStringMethod
    {
        Scan,                 // Use PatternSleuth AOB scan (fallback to Conv_NameToString)
        Conv_NameToString,    // Use KismetStringLibrary::Conv_NameToString (no fallback)
    };

    struct ScanOverrides
    {
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> guobjectarray;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> static_find_object;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> version_finder;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> fname_to_string;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> fname_constructor;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> fmemory_free;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> process_event;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> static_construct_object;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> fuobject_hash_tables_get;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> gnatives;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> console_manager_singleton;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> process_local_script_function;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> process_internal;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> call_function_by_name_with_arguments;
        std::function<void(std::vector<SignatureContainer>&, Signatures::ScanResult&)> gameengine_tick;

    };

    // Struct to be passed to the 'initialize' function
    // Should always have valid default values
    struct Config
    {
    public:
        uint32_t NumScanThreads{8};
        uint32_t MultithreadingModuleSizeThreshold{0x1000000};

        // Functions to be called if you want to override one or more scans
        ScanOverrides ScanOverrides{};

        int64_t SecondsToScanBeforeGivingUp{30};

        // Cache settings
        // Path to cache files, used to bypass aob scanning when the module hasn't changed from the last time it was scanned
        // If empty, this default will be used: <GameExeDirectory>/cache
        std::filesystem::path CachePath{};
        bool bEnableCache{false};
        bool bInvalidateCacheIfSelfChanged{true};
        SinglePassScanner::ScanMethod ScanMethod{SinglePassScanner::ScanMethod::StdFind};

        // If false, will not use UObject create/delete listeners in GUObjectArray.
        bool bUseUObjectArrayCache{true};

        // Which functions to hook.
        bool bHookProcessInternal{false};
        bool bHookProcessLocalScriptFunction{false};
        bool bHookLoadMap{false};
        bool bHookEngineTick{false};
        FunctionResolveMethod EngineTickResolveMethod{FunctionResolveMethod::Scan};
        bool bHookInitGameState{false};
        bool bHookCallFunctionByNameWithArguments{false};
        bool bHookBeginPlay{false};
        bool bHookEndPlay{false};
        bool bHookLocalPlayerExec{false};
        bool bHookAActorTick{false};
        bool bHookGameViewportClientTick{false};
        bool bHookUObjectProcessEvent{false};
        bool bHookProcessConsoleExec{false};
        bool bHookUStructLink{false};

        uint8_t FExecVTableOffsetInLocalPlayer{0x28};

        bool bIsForcedPreScan{false};
        FNameToStringMethod FNameToStringMethod{FNameToStringMethod::Scan};
    };

    struct CacheInfo
    {
        File::Handle GameExeFile;
        bool bShouldUseCache;
        bool bShouldSerializeCache;
    };

    struct StaticStorage
    {
        static std::filesystem::path GameExe;
        RC_UE_API static bool bIsInitialized;
        RC_UE_API static bool bVersionedContainerIsInitialized;
        RC_UE_API static Config GlobalConfig;
        RC_UE_API static bool bPreInitCompleted;
        RC_UE_API static bool bScanFullyCompleted;
        RC_UE_API static std::atomic_bool FNameVerificationStatus;
        RC_UE_API static std::atomic_bool FNameVerificationStartedUnhooking;
    };

    // Returns the address of a symbol exported by any of loaded modules.
    auto RC_UE_API LoadExport(StringViewType Name) -> void*;
    auto RC_UE_API LoadExport(std::string_view Name) -> void*;

    // Initializing the Unreal module requires calling 'Initialize()'.
    // You can do a scan ahead of initialization by calling 'PreInitialize()' followed by 'ScanGame()' before calling 'Initialize()'.
    // Note that 'ScanGame' will throw if an AOB isn't found, so you'll need to use try/catch if you don't want to crash.
    // If you need to discover the game and engine modules ahead of initialization, you can call 'SetupUnrealModules'.
    auto RC_UE_API SetupUnrealModules() -> void;
    auto RC_UE_API InitializeVersionedContainer() -> void;
    auto RC_UE_API PreInitialize(const Config&) -> void;
    auto RC_UE_API Initialize(const Config&) -> void;
    auto RC_UE_API ScanGame() -> void;
    auto RC_UE_API VerifyFNameConstructor(void* AddressOverride = nullptr) -> void;
}

namespace RC::Unreal
{
    auto RC_UE_API GetGameThreadId() -> std::thread::id;
    auto RC_UE_API IsInGameThread() -> bool;
    auto RC_UE_API IsGameThreadInitialized() noexcept -> bool;

    // Doesn't check whether the game thread id has been initialized yet, and doesn't throw.
    // Useful for performance sensitive areas where exceptions can be expensive.
    // Will act as if called outside the game thread if the game thread id hasn't been initialized yet regardless if called from the game thread.
    auto RC_UE_API GetGameThreadIdRaw() noexcept -> std::thread::id;
    auto RC_UE_API IsInGameThreadRaw() noexcept -> bool;
}
