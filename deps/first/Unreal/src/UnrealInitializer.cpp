#include <stdexcept>
#include <format>
#include <thread>
#include <chrono>
#include <string>
#include <unistd.h>

#include <Helpers/Casting.hpp>
#include <SigScanner/SinglePassSigScanner.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Unreal/UnrealInitializer.hpp>
#include <Unreal/NameTypes.hpp>
#include <Unreal/VersionedContainer/Container.hpp>
#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <Unreal/Signatures.hpp>
#include <Unreal/Hooks.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/UEngine.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/FMemory.hpp>
#include <Unreal/FAssetData.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/AGameModeBase.hpp>
#include <Unreal/ULocalPlayer.hpp>
#include <Unreal/Searcher/ObjectSearcher.hpp>
#include <Unreal/ClassListener.hpp>
#include <Unreal/UGameViewportClient.hpp>
#include <Zydis/Zydis.h>
#include <ASMHelper/ASMHelper.hpp>
#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#include <Psapi.h>
#endif
#ifndef _WIN32
#include <link.h>
#include <dlfcn.h>
#endif
#include <Helpers/String.hpp>
#include <Helpers/SysError.hpp>

#include <Unreal/Hooks/Internal/ProcessEventProfiler.hpp>
#include <Unreal/Hooks/Internal/DetourInstance.hpp>
#include <Unreal/Hooks/Internal/DetourSubclasses.hpp>

namespace RC::Unreal::UnrealInitializer
{
    std::filesystem::path StaticStorage::GameExe;
    bool StaticStorage::bIsInitialized{false};
    bool StaticStorage::bVersionedContainerIsInitialized{false};
    Config StaticStorage::GlobalConfig{};
    bool StaticStorage::bPreInitCompleted{};
    bool StaticStorage::bScanFullyCompleted{};
    std::atomic_bool StaticStorage::FNameVerificationStatus{false};
    std::atomic_bool StaticStorage::FNameVerificationStartedUnhooking{false};

    // These globals are explicitly not defined in a header file.
    // This is to force access via getter to catch if/when the game thread id is being used before it's been set.
    std::thread::id GGameThreadId{};
    bool GGameThreadIdInitialized{};

    auto HookedEngineTick(Hook::TCallbackIterationData<void>&, UEngine*, float, bool) -> void
    {
        if (GGameThreadId == std::thread::id{})
        {
            GGameThreadId = std::this_thread::get_id();
            GGameThreadIdInitialized = GGameThreadId != std::thread::id{};
            if (!GGameThreadIdInitialized)
            {
                Output::send<LogLevel::Error>(STR("Unable to retrieve ID of game thread\n"));
            }
        }
    }

    auto LoadExport(StringViewType Name) -> void*
    {
#ifdef _WIN32
        void* symbol{};
        for (const auto& module_info : SigScannerStaticData::m_modules_info.array)
        {
            symbol = std::bit_cast<void*>(GetProcAddress(static_cast<HMODULE>(module_info.lpBaseOfDll), to_string(Name).c_str()));
            if (symbol)
            {
                break;
            }
        }
        return symbol;
#else
        return dlsym(RTLD_DEFAULT, to_string(Name).c_str());
#endif
    }

    auto LoadExport(std::string_view Name) -> void*
    {
        return LoadExport(ensure_str(Name));
    }

    auto SetupUnrealModules() -> void
    {
#ifdef _WIN32
        // Setup all modules for the aob scanner
        MODULEINFO ModuleInfo;
        K32GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &ModuleInfo, sizeof(MODULEINFO));
        SigScannerStaticData::m_modules_info[ScanTarget::MainExe] = ModuleInfo;

        HMODULE Modules[1024];
        DWORD BytesRequired;

        if (K32EnumProcessModules(GetCurrentProcess(), Modules, sizeof(Modules), &BytesRequired) == 0)
        {
            throw std::runtime_error{fmt::format("Was unable to enumerate game modules. Error: {}",
                                                 to_string(SysError(GetLastError())).c_str())};
        }

        // Default all modules to be the same as MainExe
        // This is because most UE4 games only have the MainExe module
        for (size_t i = 0; i < static_cast<size_t>(ScanTarget::Max); ++i)
        {
            SigScannerStaticData::m_modules_info.array[i] = ModuleInfo;
        }

        // Check for modules and save the module info if they exist
        for (auto i = 0; i < BytesRequired / sizeof(HMODULE); ++i)
        {
            char ModuleRawName[MAX_PATH];
            // TODO: Fix an occasional error: "Call to K32GetModuleBaseNameA failed. Error Code: 6 (ERROR_INVALID_HANDLE)"
            if (K32GetModuleBaseNameA(GetCurrentProcess(), Modules[i], ModuleRawName, sizeof(ModuleRawName) / sizeof(char)) == 0)
            {
                continue;
            }

            std::string ModuleName{ModuleRawName};

            for (size_t i2 = 0; i2 < static_cast<size_t>(ScanTarget::Max); ++i2)
            {
                std::string ModuleToFind{"-"};
                ModuleToFind.append(ScanTargetToString(i2));
                ModuleToFind.append("-Win64-Shipping.dll");

                size_t Occurrence = ModuleName.find(ModuleToFind);
                if (Occurrence != ModuleName.npos)
                {
                    if (!SigScannerStaticData::m_is_modular) { SigScannerStaticData::m_is_modular = true; }

                    K32GetModuleInformation(GetCurrentProcess(), Modules[i], &SigScannerStaticData::m_modules_info[static_cast<ScanTarget>(i2)], sizeof(MODULEINFO));
                }
            }
        }
#else
        // Linux: Use dl_iterate_phdr to enumerate loaded shared libraries
        struct PhdrCallbackData
        {
            std::array<WIN_MODULEINFO, static_cast<size_t>(ScanTarget::Max)>* modules_info;
            bool* is_modular;
        };

        auto phdr_callback = [](struct dl_phdr_info* info, size_t /*size*/, void* data) -> int {
            auto* cb_data = static_cast<PhdrCallbackData*>(data);
            const char* name = info->dlpi_name;

            // Skip empty names (the main executable on some systems)
            if (!name || name[0] == '\0')
            {
                // This is likely the main executable
                // Calculate total load size from PT_LOAD segments
                unsigned long total_size = 0;
                for (int i = 0; i < info->dlpi_phnum; ++i)
                {
                    if (info->dlpi_phdr[i].p_type == PT_LOAD)
                    {
                        unsigned long seg_end = info->dlpi_phdr[i].p_vaddr + info->dlpi_phdr[i].p_memsz;
                        if (seg_end > total_size)
                        {
                            total_size = seg_end;
                        }
                    }
                }
                MODULEINFO main_module{};
                main_module.lpBaseOfDll = reinterpret_cast<void*>(info->dlpi_addr);
                main_module.SizeOfImage = total_size;
                main_module.EntryPoint = nullptr;

                // Set all scan targets to the main executable (non-modular default)
                for (size_t i = 0; i < static_cast<size_t>(ScanTarget::Max); ++i)
                {
                    (*cb_data->modules_info)[i] = main_module;
                }
                return 0;
            }

            // Check if this shared library matches any scan target
            std::string module_name{name};
            // Extract just the filename
            size_t last_slash = module_name.find_last_of('/');
            if (last_slash != std::string::npos)
            {
                module_name = module_name.substr(last_slash + 1);
            }

            for (size_t i = 0; i < static_cast<size_t>(ScanTarget::Max); ++i)
            {
                std::string target_name = ScanTargetToString(static_cast<ScanTarget>(i));
                // Linux UE4 module naming: lib<Module>-Linux-Shipping.so or lib<Module>.so
                std::string to_find1 = "-" + target_name + "-Linux";
                std::string to_find2 = "lib" + target_name;

                if (module_name.find(to_find1) != std::string::npos ||
                    module_name.find(to_find2) != std::string::npos)
                {
                    if (!*cb_data->is_modular) { *cb_data->is_modular = true; }

                    // Calculate total load size from PT_LOAD segments
                    unsigned long total_size = 0;
                    for (int j = 0; j < info->dlpi_phnum; ++j)
                    {
                        if (info->dlpi_phdr[j].p_type == PT_LOAD)
                        {
                            unsigned long seg_end = info->dlpi_phdr[j].p_vaddr + info->dlpi_phdr[j].p_memsz;
                            if (seg_end > total_size)
                            {
                                total_size = seg_end;
                            }
                        }
                    }

                    MODULEINFO module_info{};
                    module_info.lpBaseOfDll = reinterpret_cast<void*>(info->dlpi_addr);
                    module_info.SizeOfImage = total_size;
                    module_info.EntryPoint = nullptr;

                    (*cb_data->modules_info)[i] = module_info;
                }
            }

            return 0;
        };

        PhdrCallbackData cb_data{
            &SigScannerStaticData::m_modules_info.array,
            &SigScannerStaticData::m_is_modular
        };

        dl_iterate_phdr(phdr_callback, &cb_data);

        // Verify that the main exe was found
        if (SigScannerStaticData::m_modules_info[ScanTarget::MainExe].lpBaseOfDll == nullptr)
        {
            // Fallback: use /proc/self/maps to find the main executable
            FILE* maps = fopen("/proc/self/maps", "r");
            if (maps)
            {
                char line[512];
                unsigned long main_start = 0;
                unsigned long main_end = 0;
                char perms[8];
                char pathname[256];

                while (fgets(line, sizeof(line), maps))
                {
                    // Parse: address perms offset dev inode pathname
                    if (sscanf(line, "%lx-%lx %7s %*x %*x:%*x %*d %255s", &main_start, &main_end, perms, pathname) == 4)
                    {
                        // Look for the main executable (no pathname or pathname containing the exe name)
                        if (pathname[0] == '\0' || strstr(pathname, "Pal") != nullptr || strstr(pathname, "Game") != nullptr)
                        {
                            if (main_start != 0)
                            {
                                MODULEINFO main_module{};
                                main_module.lpBaseOfDll = reinterpret_cast<void*>(main_start);
                                main_module.SizeOfImage = main_end - main_start;
                                main_module.EntryPoint = nullptr;

                                for (size_t i = 0; i < static_cast<size_t>(ScanTarget::Max); ++i)
                                {
                                    (*cb_data.modules_info)[i] = main_module;
                                }
                                break;
                            }
                        }
                    }
                }
                fclose(maps);
            }
        }

        // Log what we found
        auto& main_exe = SigScannerStaticData::m_modules_info[ScanTarget::MainExe];
        if (main_exe.lpBaseOfDll != nullptr)
        {
            Output::send(STR("MainExe module: base={}, size={}\n"),
                         reinterpret_cast<void*>(main_exe.lpBaseOfDll),
                         main_exe.SizeOfImage);
        }
        else
        {
            Output::send<LogLevel::Warning>(STR("Warning: Could not find any game modules on Linux\n"));
        }
#endif
    }

    auto InitializeVersionedContainer() -> void
    {
        Container::SetDerivedBaseObjects();
        Container::UnrealVirtualVC->set_virtual_offsets();
        StaticStorage::bVersionedContainerIsInitialized = true;
    }

    auto static PostInitialize(const Config& UnrealConfig) -> void
    {
        if (!GMalloc)
        {
            throw std::runtime_error{"UnrealInitializer::PostInitialize: GMalloc is uninitialized."};
        }

        Output::send(STR("Post-initialization: GMalloc: {} -> {}\n"), (void*)GMalloc, (void*)*GMalloc);

        // FAssetData was not reflected before 4.17
        // We'll need to manually add FAssetData for every engine version eventually
        if (Version::IsAtLeast(4, 17))
        {
            if (FAssetData::FAssetDataAssumedStaticSize < FAssetData::StaticSize())
            {
                Output::send<LogLevel::Error>(STR("Tell a developer: FAssetData::StaticSize is too small to hold the entire struct. Assumed Size: {}; Found size: {}\n"), FAssetData::FAssetDataAssumedStaticSize, FAssetData::StaticSize());
            }
            bFAssetDataAvailable = true;
        }

        if (UnrealConfig.bUseUObjectArrayCache)
        {
            // Construct searcher pools
            AllSearcherPools.emplace(HashSearcherKey<UClass, AnySuperStruct>(), std::make_unique<ObjectSearcherPool<UClass, AnySuperStruct>>());
            AllSearcherPools.emplace(HashSearcherKey<UClass, AActor>(), std::make_unique<ObjectSearcherPool<UClass, AActor>>());
            AllSearcherPools.emplace(HashSearcherKey<AActor, AnySuperStruct>(), std::make_unique<ObjectSearcherPool<AActor, AnySuperStruct>>());

            // Populate searcher pools
            UObjectGlobals::ForEachUObject([](UObject* Object, ...) {
                auto* ObjectItem = Object->GetObjectItem();

                if (Object->IsA<UClass>())
                {
                    std::lock_guard<std::mutex> AnyPoolLock(ObjectSearcherPool<UClass, AnySuperStruct>::PoolMutex);
                    ObjectSearcherPool<UClass, AnySuperStruct>::Add(ObjectItem);

                    if (static_cast<UClass*>(Object)->IsChildOf<AActor>())
                    {
                        std::lock_guard<std::mutex> ActorPoolLock(ObjectSearcherPool<UClass, AActor>::PoolMutex);
                        ObjectSearcherPool<UClass, AActor>::Add(ObjectItem);
                    }
                }

                if (Object->IsA<AActor>())
                {
                    std::lock_guard<std::mutex> ActorInstPoolLock(ObjectSearcherPool<AActor, AnySuperStruct>::PoolMutex);
                    ObjectSearcherPool<AActor, AnySuperStruct>::Add(ObjectItem);
                }

                return LoopAction::Continue;
            });

            Output::send(STR("Adding GUObjectArray listeners\n"));
            UObjectArray::AddUObjectCreateListener(&FClassCreateListener::ClassCreateListener);
            UObjectArray::AddUObjectDeleteListener(&FClassDeleteListener::ClassDeleteListener);
        }

        StaticStorage::bIsInitialized = true;

    #ifdef UE_HOOK_TEST
        std::thread test_thread([](){
            Output::send(STR("Starting tests in 10 seconds\n"));
            std::this_thread::sleep_for(std::chrono::seconds(10));
            auto result = StartTests();
            Output::send<LogLevel::Verbose>(result ? STR("All tests passed!") : STR("Not all tests passed!"));
        });
        test_thread.detach();
    #else
        Output::send(STR("Starting callback garbage collector!"));
        Hook::StartCallbackGarbageCollector();
    #endif

        Hook::RegisterStaticConstructObjectPostCallback([](auto& data, auto& params) {
            if (UnrealInitializer::StaticStorage::bIsInitialized) {
                UObject* object = data.GetCurrentResolvedReturnValue();
                if(!object)
                {
                    Output::send<LogLevel::Warning>(STR("[{}.{}.{}] StaticConstructObject is set to return nullptr, not adding to ObjectSearcherPool!"),
                                                    STR("UE4SS"), STR("StaticConstructObject"), STR("ObjectSearcherPoolHook"));
                    return;
                }
                if (object->IsA<AActor>())
                {
                    std::lock_guard<std::mutex> ActorInstPoolLock(ObjectSearcherPool<AActor, AnySuperStruct>::PoolMutex);
                    ObjectSearcherPool<AActor, AnySuperStruct>::Add(object->GetObjectItem());
                }
            }
        }, {false, true, STR("UE4SS"), STR("ObjectSearcherPoolHook")});
    }

    struct PsScanConfig
    {
        bool g_uobject_array{};
        bool fname_tostring_fstring{};
        bool fname_ctor_wchar{};
        bool gmalloc{};
        bool static_construct_object_internal{};
        bool ftext_fstring{};
        bool engine_version{};
        bool fuobject_hash_tables_get{};
        bool gnatives{};
        bool console_manager_singleton{};
        bool gameengine_tick{};
    };

    struct PsCtx
    {
        void (*default_)(CharType* msg);
        void (*normal)(CharType* msg);
        void (*verbose)(CharType* msg);
        void (*warning)(CharType* msg);
        void (*error)(CharType* msg);
        PsScanConfig config{};
    };

    struct PsEngineVersion
    {
        uint16_t major{};
        uint16_t minor{};
    };

    struct PsScanResults
    {
        void* g_uobject_array{};
        void* fname_tostring_fstring{};
        void* fname_ctor_wchar{};
        void* gmalloc{};
        void* static_construct_object_internal{};
        void* ftext_fstring{};
        PsEngineVersion engine_version{};
        void* fuobject_hash_tables_get{};
        void* gnatives{};
        void* console_manager_singleton{};
        void* gameengine_tick{};
    };

    extern "C" {
        bool ps_scan(PsCtx& ctx, PsScanResults& results);
    }

    auto ScanGame() -> void
    {
        enum class OutputErrorsByThrowing { Yes, No };
        enum class ErrorsOnly { Yes, No };

        size_t scan_count{};

        const auto& UnrealConfig = StaticStorage::GlobalConfig;
        PsScanConfig config{};
        config.g_uobject_array = !UnrealConfig.ScanOverrides.guobjectarray;
        config.fname_tostring_fstring = !UnrealConfig.ScanOverrides.fname_to_string;
        config.fname_ctor_wchar = !UnrealConfig.ScanOverrides.fname_constructor;
        config.gmalloc = !UnrealConfig.ScanOverrides.fmemory_free;
        config.static_construct_object_internal = !UnrealConfig.ScanOverrides.static_construct_object;
        config.engine_version = !UnrealConfig.ScanOverrides.version_finder;
        config.fuobject_hash_tables_get = !UnrealConfig.ScanOverrides.fuobject_hash_tables_get;
        config.gnatives = !UnrealConfig.ScanOverrides.gnatives;
        config.console_manager_singleton = !UnrealConfig.ScanOverrides.console_manager_singleton;
        config.gameengine_tick = !UnrealConfig.ScanOverrides.gameengine_tick;
        // ftext_fstring has no ScanOverride field, so we explicitly set it to false
        // to ensure ps_scan is skipped when all other overrides are set
        config.ftext_fstring = false;

        PsCtx ctx {
            [](CharType* msg){ Output::send<LogLevel::Default>(STR("[PS] {}\n"), msg); },
            [](CharType* msg){ Output::send<LogLevel::Normal>(STR("[PS] {}\n"), msg); },
            [](CharType* msg){ Output::send<LogLevel::Verbose>(STR("[PS] {}\n"), msg); },
            [](CharType* msg){ Output::send<LogLevel::Warning>(STR("[PS] {}\n"), msg); },
            [](CharType* msg){ Output::send<LogLevel::Error>(STR("[PS] {}\n"), msg); },
            config,
        };

        PsScanResults results{};

        auto start = std::chrono::steady_clock::now();
        while (true)
        {
            Output::send<LogLevel::Verbose>(STR("PS Scan attempt {} (Phase {})\n"), scan_count + 1, UnrealConfig.bIsForcedPreScan ? 1 : 2);

#ifdef __linux__
            // On Linux, ps_scan (patternsleuth) uses Windows-specific AOB patterns
            // that will never match the Linux binary. If all scan overrides are set
            // (all config flags false), skip ps_scan entirely.
            if (!config.g_uobject_array && !config.fname_tostring_fstring &&
                !config.fname_ctor_wchar && !config.gmalloc &&
                !config.static_construct_object_internal && !config.ftext_fstring &&
                !config.engine_version && !config.fuobject_hash_tables_get &&
                !config.gnatives && !config.console_manager_singleton &&
                !config.gameengine_tick)
            {
                Output::send<LogLevel::Default>(STR("PS scan skipped (all overrides set, Linux)\n"));
                break;
            }
#endif

            if (ps_scan(ctx, results))
            {
                // All of the requested resolvers were found so break and continue
                Output::send<LogLevel::Default>(STR("PS scan successful\n"));
                break;
            }

            if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() > UnrealConfig.SecondsToScanBeforeGivingUp)
            {
                throw std::runtime_error{"PS scan timed out"};
            }
            ++scan_count;

            // Sleep between scan attempts to avoid tight-loop spamming and CPU pegging
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        auto OutputResult = [](Signatures::ScanResult& ScanResult, OutputErrorsByThrowing OutputErrorsByThrowing = OutputErrorsByThrowing::No, ErrorsOnly ErrorsOnly = ErrorsOnly::No) {
            if (ScanResult.Status == Signatures::ScanStatus::Failed)
            {
                std::string AllErrors{"AOB scans could not be completed because of the following reasons:\n"};
                std::string FatalErrors{};
                std::string NonFatalErrors{};
                for (const auto& Error : ScanResult.Errors)
                {
                    if (Error.bIsFatal)
                    {
                        FatalErrors.append(Error.Message + "\n\n");
                    }
                    else
                    {
                        NonFatalErrors.append(Error.Message + "\n\n");
                    }
                }

                AllErrors.append(FatalErrors);
                AllErrors.append(NonFatalErrors);

                if (!FatalErrors.empty() && OutputErrorsByThrowing == OutputErrorsByThrowing::Yes)
                {
                    throw std::runtime_error{AllErrors};
                }
                else
                {
                    Output::send(ensure_str(AllErrors));
                }
            }

            if (ErrorsOnly == ErrorsOnly::No)
            {
                for (const auto& SuccessMessage : ScanResult.SuccessMessage)
                {
                    Output::send(SuccessMessage);
                }

                for (const auto& InfoMessage : ScanResult.InfoMessages)
                {
                    Output::send(STR("Info: {}"), InfoMessage);
                }
            }
        };

        SinglePassScanner::m_scan_method = UnrealConfig.ScanMethod;
        auto DoScan = [&](auto ScannerFunction) {
            Signatures::ScanResult ScanResult{};
            size_t scan_count{};
            auto start = std::chrono::steady_clock::now();
            while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start).count() < UnrealConfig.SecondsToScanBeforeGivingUp)
            {
                Output::send<LogLevel::Verbose>(STR("Lua Scan attempt {} (Phase {})\n"), scan_count + 1, UnrealConfig.bIsForcedPreScan ? 1 : 2);

                ScanResult = ScannerFunction(UnrealConfig);
                OutputResult(ScanResult);

                bool bHasFatalError{};
                for (const auto& Error : ScanResult.Errors)
                {
                    if (Error.bIsFatal)
                    {
                        bHasFatalError = true;
                        break;
                    }
                }
                if (!bHasFatalError) { break; }
                ++scan_count;
                if (UnrealConfig.bIsForcedPreScan && scan_count > 0)
                {
                    break;
                }

                // Sleep between scan attempts to avoid tight-loop spamming
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            OutputResult(ScanResult, OutputErrorsByThrowing::Yes, ErrorsOnly::Yes);
        };

#ifdef __linux__
        // On Linux, ps_scan and DoScan are skipped (Windows-specific AOB patterns / empty container crash).
        // Call ScanOverrides directly to resolve functions via dlsym and heuristic scans.
        // Without this, GUObjectArray and all other addresses remain null and UE4SS enters "limited mode".
        {
            Signatures::ScanResult override_result;
            std::vector<SignatureContainer> empty_containers;

            Output::send(STR("ScanGame: calling ScanOverrides directly on Linux...\n"));

            // First pass overrides
            if (UnrealConfig.ScanOverrides.version_finder)
                UnrealConfig.ScanOverrides.version_finder(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.fname_to_string)
                UnrealConfig.ScanOverrides.fname_to_string(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.static_construct_object)
                UnrealConfig.ScanOverrides.static_construct_object(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.gameengine_tick)
                UnrealConfig.ScanOverrides.gameengine_tick(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.static_find_object)
                UnrealConfig.ScanOverrides.static_find_object(empty_containers, override_result);

            // Second pass overrides
            if (UnrealConfig.ScanOverrides.fname_constructor)
                UnrealConfig.ScanOverrides.fname_constructor(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.guobjectarray)
                UnrealConfig.ScanOverrides.guobjectarray(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.fmemory_free)
                UnrealConfig.ScanOverrides.fmemory_free(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.gnatives)
                UnrealConfig.ScanOverrides.gnatives(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.fuobject_hash_tables_get)
                UnrealConfig.ScanOverrides.fuobject_hash_tables_get(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.console_manager_singleton)
                UnrealConfig.ScanOverrides.console_manager_singleton(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.process_local_script_function)
                UnrealConfig.ScanOverrides.process_local_script_function(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.process_internal)
                UnrealConfig.ScanOverrides.process_internal(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.call_function_by_name_with_arguments)
                UnrealConfig.ScanOverrides.call_function_by_name_with_arguments(empty_containers, override_result);
            if (UnrealConfig.ScanOverrides.process_event)
                UnrealConfig.ScanOverrides.process_event(empty_containers, override_result);

            for (const auto& msg : override_result.SuccessMessage)
            {
                Output::send(msg);
            }
            Output::send(STR("ScanGame: ScanOverrides completed on Linux.\n"));
        }
#endif

        // First pass
        {
            if (ctx.config.engine_version)
            {
                Version::Major = results.engine_version.major;
                Version::Minor = results.engine_version.minor;
            }
            if (ctx.config.fname_tostring_fstring)
            {
                FName::ToStringInternal.assign_address(results.fname_tostring_fstring);
            }
            if (ctx.config.static_construct_object_internal)
            {
                UObjectGlobals::SetupStaticConstructObjectInternalAddress(results.static_construct_object_internal);
            }
            if (ctx.config.gameengine_tick)
            {
                UEngine::TickInternal.assign_address(results.gameengine_tick);
            }

            // If there are any overrides in the first pass then scan for them
            // engine_version omitted from this check as is not actually a scan and sets the version directly from the config
            if (!ctx.config.fname_tostring_fstring ||
                !ctx.config.static_construct_object_internal ||
                !ctx.config.gameengine_tick)
            {
#ifdef __linux__
                Output::send(STR("ScanGame: skipping first pass DoScan on Linux (overrides set)\n"));
#else
                Output::send<LogLevel::Default>(STR("Running first pass of Lua override scans\n"));
                DoScan(&Signatures::ScanForGameFunctionsAndData);
#endif
            }
        }

#ifdef __linux__
        Output::send(STR("ScanGame: calling InitializeVersionedContainer()...\n"));
#endif
        InitializeVersionedContainer();
#ifdef __linux__
        Output::send(STR("ScanGame: InitializeVersionedContainer() done.\n"));
        // Palworld-specific vtable override.
        //
        // Palworld's UE5.1 build has an extra virtual function slot in the UObject
        // vtable between OverridePerObjectConfigSection (0x258) and ProcessEvent.
        // The extra slot (at 0x260) is an empty stub (ret; int3). This shifts
        // ProcessEvent, GetFunctionCallspace, CallRemoteFunction, and
        // ProcessConsoleExec each by +8 bytes.
        //
        // This is NOT an engine-wide Itanium ABI difference — other UObject virtuals
        // (PostLoad, BeginDestroy, FinishDestroy) are at the standard offsets.
        // It is a Pocketpair engine modification.
        //
        // Evidence:
        // - vtable[0x260] = ret;int3 (empty stub) — should be ProcessEvent
        // - vtable[0x268] = push rbp; mov rsp,rbp (real function) — verified as
        //   ProcessEvent via GDB call: Conv_NameToString(0x1f8) returns "Actor"
        // - vtable[0x280] = jmp (real function) — ProcessConsoleExec
        // - PostLoad(0xA0), BeginDestroy(0xB0), FinishDestroy(0xC0) are at
        //   standard offsets (no shift), confirming this is local to the
        //   ProcessEvent region.
        //
        // Gate: only apply if the game binary is PalServer-Linux-Shipping.
        {
            char exe_path[4096];
            ssize_t exe_len = readlink("/proc/self/exe", exe_path, sizeof(exe_path) - 1);
            bool is_palworld = (exe_len > 0 && 
                std::string(exe_path).find("PalServer") != std::string::npos);
            if (is_palworld)
            {
                // UObject vtable: extra slot between OverridePerObjectConfigSection
                // and ProcessEvent shifts ProcessEvent and subsequent virtuals by +8.
                UObject::VTableLayoutMap[STR("ProcessEvent")] = 0x268;
                UObject::VTableLayoutMap[STR("GetFunctionCallspace")] = 0x270;
                UObject::VTableLayoutMap[STR("CallRemoteFunction")] = 0x278;
                UObject::VTableLayoutMap[STR("ProcessConsoleExec")] = 0x280;

                // FProperty vtable: same pattern — extra slot between
                // InstanceSubobjects (0x140) and GetMinAlignment (0x148),
                // shifting GetMinAlignment and subsequent virtuals by +8.
                // Verified at runtime: vtable[0x148] = ret;int3 (stub),
                // vtable[0x150] = real function returning alignment (4, 8, etc.).
                FProperty::VTableLayoutMap[STR("GetMinAlignment")] = 0x150;
                FProperty::VTableLayoutMap[STR("ContainsObjectReference")] = 0x158;
                FProperty::VTableLayoutMap[STR("EmitReferenceInfo")] = 0x160;
                FProperty::VTableLayoutMap[STR("SameType")] = 0x168;

                Output::send(STR("Palworld vtable override: UObject ProcessEvent=0x268, FProperty GetMinAlignment=0x150\n"));
            }
        }
#endif

        // Second pass
        {
            if (ctx.config.fname_ctor_wchar)
            {
                FName::ConstructorInternal.assign_address(results.fname_ctor_wchar);
            }
            if (ctx.config.gmalloc)
            {
                GMalloc = std::bit_cast<FMalloc**>(results.gmalloc);
            }
            if (ctx.config.g_uobject_array)
            {
                UObjectArray::SetupGUObjectArrayAddress(results.g_uobject_array);
            }
            if (ctx.config.gnatives)
            {
                GNatives_Internal = reinterpret_cast<FNativeFuncPtr*>(results.gnatives);
            }

            // If there are any overrides in the second pass then scan for them
            if (!ctx.config.fname_ctor_wchar ||
                !ctx.config.gmalloc ||
                !ctx.config.g_uobject_array ||
                !ctx.config.ftext_fstring ||
                !ctx.config.gnatives)
            {
#ifdef __linux__
                Output::send(STR("ScanGame: skipping second pass DoScan on Linux (overrides set)\n"));
#else
                Output::send<LogLevel::Default>(STR("Running second pass of Lua override scans\n"));
                DoScan(&Signatures::ScanForGUObjectArray);
#endif
            }
        }

#ifdef __linux__
        Output::send(STR("ScanGame: setting bScanFullyCompleted = true.\n"));
#endif
        StaticStorage::bScanFullyCompleted = true;
    }

    auto VerifyFNameConstructor(void* AddressOverride) -> void
    {
        if (AddressOverride)
        {
            FName::ConstructorInternal.assign_temp_address(AddressOverride);
        }

        // To ensure we don't use the FName constructor too early, hook it until something uses it.
        Output::send(STR("Verifying FName constructor...\n"));
        static Hook::GlobalCallbackId FNameConstructedHookId{};
        FNameConstructedHookId = Hook::RegisterFNameConstructorPostCallback([](const auto&, const CharType* String, EFindName) {
            if (!StaticStorage::FNameVerificationStartedUnhooking.load(std::memory_order_acquire))
            {
                StaticStorage::FNameVerificationStartedUnhooking.store(true, std::memory_order_release);
                Hook::RegisterEngineTickPreCallback([](Hook::TCallbackIterationData<void>&, UEngine*, float, bool) {
                    Hook::Internal::GetDetourInstance<Hook::Internal::EDetourTarget::FNameConstructor>()->RemoveCallback(FNameConstructedHookId);
                    Hook::Internal::GetDetourInstance<Hook::Internal::EDetourTarget::FNameConstructor>()->DeactivateHook();
                    StaticStorage::FNameVerificationStartedUnhooking.store(false, std::memory_order_release);
                }, {true, false, STR("UE4SS"), STR("FNameConstructorUnhooker")});
            }
            StaticStorage::FNameVerificationStatus.store(true, std::memory_order_release);
            StaticStorage::FNameVerificationStatus.notify_all();
        }, {false, true, STR("UE4SS"), STR("FNameConstructorVerificationHook")});
        // Wait with timeout — on stripped Linux binaries, the AOB-scanned FName
        // constructor address may be wrong, causing the hook to never fire.
        {
            auto wait_start = std::chrono::steady_clock::now();
            while (!StaticStorage::FNameVerificationStatus.load(std::memory_order_acquire))
            {
                if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wait_start).count() > 15)
                {
                    Output::send<LogLevel::Warning>(STR("Timeout verifying FName constructor (hook never fired). Continuing with unverified FName address.\n"));
                    // Remove the hook since it's not firing
                    Hook::Internal::GetDetourInstance<Hook::Internal::EDetourTarget::FNameConstructor>()->RemoveCallback(FNameConstructedHookId);
                    Hook::Internal::GetDetourInstance<Hook::Internal::EDetourTarget::FNameConstructor>()->DeactivateHook();
                    // The AOB scan likely matched the wrong function (the verification hook
                    // never fired, meaning this address is not the real FName constructor).
                    // Reset it so callers fall back to the limited-mode FName path instead of
                    // calling a wrong address and crashing (signal 11) during StaticFindObject.
                    FName::ConstructorInternal.reset_address();
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
        if (StaticStorage::FNameVerificationStatus.load(std::memory_order_acquire))
        {
            Output::send(STR("FName constructor verified at 0x{:016X}\n"), std::bit_cast<uintptr_t>(FName::ConstructorInternal.get_function_address()));
        }

        if (AddressOverride)
        {
            FName::ConstructorInternal.reset_address();
        }
    }

    auto PreInitialize(const Config& UnrealConfig) -> void
    {
        StaticStorage::GlobalConfig = UnrealConfig;
        // Assume it's always a forced pre-scan, and let the caller override otherwise.
        StaticStorage::GlobalConfig.bIsForcedPreScan = true;
        SinglePassScanner::m_num_threads = UnrealConfig.NumScanThreads;
        SinglePassScanner::m_multithreading_module_size_threshold = UnrealConfig.MultithreadingModuleSizeThreshold;

        SetupUnrealModules();

        StaticStorage::bPreInitCompleted = true;
    }

    auto Initialize(const Config& In_UnrealConfig) -> void
    {
        if (!StaticStorage::bPreInitCompleted)
        {
            PreInitialize(In_UnrealConfig);
        }

        StaticStorage::GlobalConfig.bIsForcedPreScan = false;
        const auto& UnrealConfig = StaticStorage::GlobalConfig;

        if (!StaticStorage::bScanFullyCompleted)
        {
#ifdef __linux__
            Output::send(STR("Initialize: calling ScanGame()...\n"));
#endif
            ScanGame();
#ifdef __linux__
            Output::send(STR("Initialize: ScanGame() done.\n"));
#endif
        }

#ifdef __linux__
        // On Linux, check if GUObjectArray was found (via dlsym or manual override).
        // If it was, we can proceed with post-scan init (object finding, hooks, etc.).
        // If not, skip everything since all post-scan init requires GUObjectArray.
        if (!Unreal::GUObjectArray)
        {
            Output::send(STR("Initialize: GUObjectArray not found, skipping post-scan init (stripped binary)\n"));
            StaticStorage::bIsInitialized = true;
            Output::send(STR("Using engine version: {}.{}\n"), Version::Major, Version::Minor);
            Output::send<LogLevel::Warning>(STR("Linux limited mode: UE function addresses not resolved (stripped binary). Mod functionality will be limited.\n"));
            return;
        }
        Output::send(STR("Initialize: GUObjectArray found, proceeding with full post-scan init\n"));
#endif
#ifdef __linux__
        // Palworld's optimized Clang/LTO build has no standalone FName(string,
        // EFindName) constructor symbol — the AOB scan matches a wrong address and
        // the verification hook never fires, stalling init. Instead, wire
        // ConstructorInternal to a native backend that delegates to the engine's
        // own find-or-add name lookup (located via a deterministic signature).
        // This provides the string->ComparisonIndex primitive that StaticFindObject
        // needs to resolve KismetStringLibrary -> Conv_NameToString.
        if (PalworldNameProvider::LocateEngineFindName())
        {
            FName::ConstructorInternal.assign_address(PalworldNameProvider::FindName);
            Output::send(STR("FName constructor wired to native Palworld name provider (engine find-or-add at 0x{:016X})\n"),
                         std::bit_cast<uintptr_t>(PalworldNameProvider::LocateEngineFindName()));
            StaticStorage::FNameVerificationStatus.store(true, std::memory_order_release);
        }
        else
        {
            Output::send<LogLevel::Warning>(STR("Palworld native name provider not located; falling back to AOB/verify path\n"));
        }
#endif
        if (!StaticStorage::FNameVerificationStatus.load(std::memory_order_acquire))
        {
            VerifyFNameConstructor();
        }

        Output::send(STR("Using engine version: {}.{}\n"), Version::Major, Version::Minor);

        if (Version::IsDebug())
        {
            if (Version::IsAtLeast(4, 25))
            {
                Output::send(STR("Adding 0x{:X} bytes to the size of FUObjectItem due to game being debug build.\n"), sizeof(void*));
                FUObjectItem::UEP_TotalSize() += sizeof(void*);
            }
        }

        // Delay until enough elements have been constructed by the engine to the point where we know we can start constructing FNames.
        Output::send(STR("Waiting for object construction...\n"));
        {
            auto wait_start = std::chrono::steady_clock::now();
#ifdef __linux__
            // On Linux, UE4SS loads via LD_PRELOAD at process start, before the engine
            // has populated GUObjectArray. The heuristic scan finds the correct address,
            // but at this point the array is nearly empty (a handful of objects). We must
            // wait for the engine to finish its own initialization and populate the array,
            // otherwise every downstream call (StaticFindObject, hook installation, mod
            // Lua code that touches UObjects) crashes or aborts (SIGSEGV/SIGABRT).
            //
            // Use the same 1000-element threshold the rest of this function uses to
            // decide between full and "limited" mode, so we only enter limited mode if
            // the engine genuinely never initializes (e.g. wrong GUObjectArray address).
            const int32_t min_elements = 1000;
            const int timeout_seconds = 120;
#else
            const int32_t min_elements = 10000;
            const int timeout_seconds = 60;
#endif
            while (UObjectArray::GetNumElements() < min_elements)
            {
                if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wait_start).count() > timeout_seconds)
                {
                    Output::send<LogLevel::Warning>(STR("Timeout waiting for object construction ({} elements). Continuing with limited FName support.\n"), UObjectArray::GetNumElements());
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
#ifdef __linux__
                auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wait_start).count();
                if (elapsed % 10 == 0 && elapsed > 0)
                {
                    Output::send(STR("Waiting for object construction: {} elements (elapsed {}s)\n"), UObjectArray::GetNumElements(), elapsed);
                }
#endif
            }
        }
#ifdef __linux__
        // If GUObjectArray has 0 elements after waiting, the heuristic scan found
        // the wrong address. Skip PostInitialize to avoid crashing on object iteration.
        if (UObjectArray::GetNumElements() == 0)
        {
            Output::send(STR("Initialize: GUObjectArray has 0 elements (wrong address?), skipping PostInitialize\n"));
            Output::send<LogLevel::Warning>(STR("Linux limited mode: GUObjectArray address appears invalid (0 elements). Mod functionality will be limited.\n"));
            StaticStorage::bIsInitialized = true;
            return;
        }
#endif
        // We're assuming that KismetStringLibrary, KismetStringLibrary.Conv_NameToString, and the KismetStringLibrary CDO exists.
        // We will lock here forever if that's not the case.
        // Consider adding a limit to how long we can wait.
        Output::send(STR("Locating KismetSystemLibrary...\n"));
        UClass* KismetStringLibrary{};
#ifdef __linux__
        // On Linux with stripped binaries, StaticFindObject may crash if GUObjectArray
        // has very few elements (engine not fully initialized). Skip and use fallback.
        if (UObjectArray::GetNumElements() >= 1000)
        {
#endif
        {
            auto wait_start = std::chrono::steady_clock::now();
            while (!KismetStringLibrary)
            {
                KismetStringLibrary = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalNoToStringFromStrings({STR("/Script/Engine"), STR("KismetStringLibrary")}));
#ifdef __linux__
                Output::send(STR("KSL lookup: result={}\n"), (void*)KismetStringLibrary);
#endif
                if (!KismetStringLibrary)
                {
                    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wait_start).count() > 30)
                    {
                        Output::send<LogLevel::Warning>(STR("Timeout locating KismetStringLibrary. FName::ToString via Conv_NameToString will not be available.\n"));
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
#ifdef __linux__
        }
        else
        {
            Output::send(STR("Skipping KismetStringLibrary lookup (GUObjectArray has only {} elements)\n"), UObjectArray::GetNumElements());
        }
#endif
        // For some games, it's found in GUObjectArray, and in other games, it's found in the function linked list.
        Output::send(STR("Locating KismetSystemLibrary:Conv_NameToString...\n"));
        {
            auto wait_start = std::chrono::steady_clock::now();
            while (!FName::Conv_NameToStringInternal && KismetStringLibrary)
            {
#ifdef __linux__
                Output::send(STR("Looking for Conv_NameToString via GetFunctionByName...\n"));
#endif
                FName::Conv_NameToStringInternal = KismetStringLibrary->GetFunctionByName(FName(STR("Conv_NameToString"), FNAME_Find));
#ifdef __linux__
                Output::send(STR("GetFunctionByName result: {}\n"), (void*)FName::Conv_NameToStringInternal);
#endif
                if (!FName::Conv_NameToStringInternal)
                {
                    FName::Conv_NameToStringInternal = static_cast<UFunction*>(UObjectGlobals::StaticFindObject_InternalNoToStringFromStrings({STR("/Script/Engine"), STR("KismetStringLibrary"), STR("Conv_NameToString")}));
#ifdef __linux__
                    Output::send(STR("StaticFindObject fallback result: {}\n"), (void*)FName::Conv_NameToStringInternal);
#endif
                }
                if (!FName::Conv_NameToStringInternal)
                {
                    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wait_start).count() > 30)
                    {
                        Output::send<LogLevel::Warning>(STR("Timeout locating Conv_NameToString. FName::ToString will use fallback.\n"));
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }
        Output::send(STR("Locating KismetSystemLibrary CDO...\n"));
        {
            auto wait_start = std::chrono::steady_clock::now();
            while (!FName::KismetStringLibraryCDO && KismetStringLibrary)
            {
#ifdef __linux__
                Output::send(STR("Calling GetClassDefaultObject() on KSL...\n"));
#endif
                FName::KismetStringLibraryCDO = KismetStringLibrary->GetClassDefaultObject();
#ifdef __linux__
                Output::send(STR("CDO result: {}\n"), (void*)FName::KismetStringLibraryCDO);
#endif
                if (!FName::KismetStringLibraryCDO)
                {
                    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - wait_start).count() > 30)
                    {
                        Output::send<LogLevel::Warning>(STR("Timeout locating KismetStringLibrary CDO. Continuing without it.\n"));
                        break;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
        }

#ifdef __linux__
        Output::send(STR("KSL setup complete: KSL={} Conv={} CDO={} NumElements={}\n"), (void*)KismetStringLibrary, (void*)FName::Conv_NameToStringInternal, (void*)FName::KismetStringLibraryCDO, UObjectArray::GetNumElements());
#endif

#ifdef __linux__
        // On Linux with stripped binaries, if GUObjectArray has very few elements,
        // the engine hasn't fully initialized and object iteration will crash.
        // Skip the remaining PostInitialize (required objects, hooks) and continue
        // with limited functionality. Lua mods can still start without hooks.
        if (UObjectArray::GetNumElements() < 1000)
        {
            Output::send<LogLevel::Warning>(STR("Linux limited mode: GUObjectArray has only {} elements. Hooks and required object checks skipped. Mods will have limited functionality.\n"), UObjectArray::GetNumElements());
            StaticStorage::bIsInitialized = true;
            return;
        }
#endif

        // Objects that are required to exist before we can continue
        Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("Class")});
        Hook::AddRequiredObject({STR("/Script/CoreUObject")});
        Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("Struct")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("Pawn")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("Character")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("Actor")});
        Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("Vector")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("Default__DefaultPawn")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("HitResult")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("Default__MaterialExpression")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("ActorComponent")});
        Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("OrientedBox")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("MovementComponent")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("HUD")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("PlayerController")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("PlayerCameraManager")});
        Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("EInterpCurveMode")});
        Hook::AddRequiredObject({STR("/Script/Engine"), STR("ENetRole")});
        Hook::AddRequiredObject({STR("/Script/MovieScene"), STR("MovieSceneEditorData")});
        Hook::AddRequiredObject({STR("/Script/UMG"), STR("Widget")});
        Hook::AddRequiredObject({STR("/Script/UMG"), STR("ComboBoxString")});
        Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("Interface")});
        if (Version::IsBelow(5, 4))
        {
            Hook::AddRequiredObject({STR("/Script/CoreUObject"), STR("DynamicClass")});
        }

        if (!Hook::AllRequiredObjectsConstructed())
        {
            for (int32_t i = 0; i < 2000 && !Hook::StaticStorage::bAllRequiredObjectsConstructed; ++i)
            {
                // The control variable for this loop is controlled from the game thread in a
                // hook created in the function call right above this loop

                if (Hook::StaticStorage::RequiredObjectsForInit.empty()) { break; }
                for (auto& RequiredObject : Hook::StaticStorage::RequiredObjectsForInit)
                {
                    if (Hook::StaticStorage::NumRequiredObjectsConstructed >= Hook::StaticStorage::RequiredObjectsForInit.size())
                    {
                        Hook::StaticStorage::bAllRequiredObjectsConstructed = true;
                        break;
                    }

                    if (RequiredObject.ObjectConstructed) { continue; }

                    UObject* required_object_ptr = UObjectGlobals::StaticFindObject_InternalNoToStringFromNames(RequiredObject.ObjectNameParts);
                    if (required_object_ptr)
                    {
                        RequiredObject.ObjectConstructed = true;
                        ++Hook::StaticStorage::NumRequiredObjectsConstructed;
                        Output::send(STR("Constructed [{} / {}]: {}\n"), Hook::StaticStorage::NumRequiredObjectsConstructed, Hook::StaticStorage::RequiredObjectsForInit.size(), RequiredObject.ObjectNameParts.back().ToString());
                    }
                }

                // Sleeping here will prevent this loop from getting optimized away
                // It will also prevent unnecessarily high CPU usage
                std::this_thread::sleep_for(std::chrono::milliseconds(250));
            }
        }

        auto GetInstanceFromClass = [](const TCHAR* ClassName, const TCHAR* FallbackCDO) {
            auto Instance = UObjectGlobals::FindFirstOf(ClassName);
            if (!Instance)
            {
                Instance = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, FallbackCDO);
            }
            return Instance;
        };

        auto* Object = static_cast<UObject*>(nullptr);
#ifdef __linux__
        // Try the real lookup. Default__Object is the CDO of UObject and is needed to
        // resolve ProcessEvent. ForEachUObject has per-iteration SIGSEGV recovery,
        // so stale pointers are skipped rather than crashing the process.
        Object = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Default__Object"));
#endif
        if (!Object)
        {
            Output::send<LogLevel::Warning>(STR("Post-initialization: Was unable to find 'CoreUObject.Default__Object' to use to retrieve the address of ProcessEvent. ProcessEvent hook will not be available.\n"));
        }

        auto* Struct = static_cast<UObject*>(nullptr);
#ifdef __linux__
        Struct = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Default__Struct"));
#endif
        if (!Struct)
        {
            Output::send<LogLevel::Warning>(STR("Post-initialization: Was unable to find 'CoreUObject.Default__Struct' to use to retrieve the address of SetSuperStruct. UStruct::Link hook will not be available.\n"));
        }

        auto* GameEngine = GetInstanceFromClass(STR("GameEngine"), STR("/Script/Engine.Default__GameEngine"));
        if (!GameEngine)
        {
            Output::send<LogLevel::Warning>(STR("Post-initialization: Was unable to find 'Engine.Default__GameEngine' to use to retrieve the address of LoadMap. LoadMap and EngineTick hooks will not be available.\n"));
        }

        // Some UE versions don't use GameModeBase (i.e: 4.13), so we must check both.
        // We can't just use GameMode for all games, because games that use GameModeBase often inherit directly from it instead of GameMode.
        auto* GameMode = GetInstanceFromClass(STR("GameModeBase"), STR("/Script/Engine.Default__GameModeBase"));
        if (!GameMode)
        {
            GameMode = GetInstanceFromClass(STR("GameMode"), STR("/Script/Engine.Default__GameMode"));
            if (!GameMode)
            {
                Output::send<LogLevel::Warning>(STR("Post-initialization: Was unable to find 'Engine.Default__GameModeBase' or 'Engine.Default__GameMode' to use to retrieve the address of InitGameState. InitGameState hook will not be available.\n"));
            }
        }

        auto* Actor = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.Default__Actor"));
        if (!Actor)
        {
            Output::send<LogLevel::Warning>(STR("Post-initialization: Was unable to find 'Engine.Default__Actor' to use to retrieve the address of BeginPlay. BeginPlay and EndPlay hooks will not be available.\n"));
        }

        auto* GameViewportClient = GetInstanceFromClass(STR("GameViewportClient"), STR("/Script/Engine.Default__GameViewportClient"));
        if (!GameViewportClient)
        {
            Output::send<LogLevel::Warning>(STR("Post-initialization: Was unable to find 'Engine.Default__GameViewportClient' to use to retrieve the address of UGameViewportClient::Tick"));
            StaticStorage::GlobalConfig.bHookGameViewportClientTick = false;
        }

        if (UnrealConfig.bHookLoadMap && GameEngine)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(UEngine, LoadMap, GameEngine); func_address)
            {
                Output::send(STR("GameEngine::LoadMap address {}\n"), func_address);
                UEngine::LoadMapInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookEngineTick && GameEngine)
        {
            auto vtable_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(UEngine, Tick, GameEngine);
            auto scan_address = UEngine::TickInternal.get_function_address();

            Output::send(STR("GameEngine::Tick address (vtable: {}; scan: {})\n"), vtable_address, scan_address);

            if (vtable_address && scan_address && vtable_address != scan_address)
            {
                Output::send<LogLevel::Warning>(STR("WARNING: VTable and scan addresses differ for UGameEngine::Tick. Potentially customized vtables.\n"));
                Output::send<LogLevel::Warning>(STR("GameEngine: {} {}\n"), static_cast<void*>(GameEngine), GameEngine->GetFullName());
                Output::send<LogLevel::Warning>(STR("VTable entries:\n"));

                if (const auto it = UEngine::VTableLayoutMap.find(STR("Tick")); it == UEngine::VTableLayoutMap.end())
                {
                    Output::send<LogLevel::Error>(STR("Unable to find 'Tick' in UEngine VTable, cannot display values relative to Tick offset in vtable.\n"));
                }
                else
                {
                    const auto TickOffset = it->second;
                    for (int32_t Count = -8; Count <= 8; ++Count)
                    {
                        auto Offset = TickOffset + Count * sizeof(void*);
                        auto VTable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(GameEngine));
                        auto EntryPtr = std::bit_cast<uintptr_t>(VTable + Offset);
                        auto Entry = RESOLVE_JMP(*std::bit_cast<void**>(EntryPtr));
                        auto Line = fmt::format(STR("{}{}: {}\n"), Count > 0 ? STR("+") : STR(""), Count == 0 ? STR("S0") : fmt::format(STR("{}"), Count), Entry);
                        if (Entry == scan_address)
                        {
                            Output::send<Color::Green>(STR("{}"), Line);
                        }
                        else
                        {
                            Output::send(STR("{}"), Line);
                        }
                    }
                }
            }

            if (UnrealConfig.EngineTickResolveMethod == FunctionResolveMethod::Scan)
            {
                // Prefer scan, fallback to vtable
                if (scan_address)
                {
                    Output::send(STR("Using scan address for GameEngine::Tick\n"));
                    UEngine::TickInternal.assign_address(scan_address);
                }
                else if (vtable_address)
                {
                    Output::send(STR("Scan failed, falling back to vtable address for GameEngine::Tick\n"));
                    UEngine::TickInternal.assign_address(vtable_address);
                }
            }
            else // FunctionResolveMethod::VTable
            {
                // Prefer vtable, fallback to scan
                if (vtable_address)
                {
                    Output::send(STR("Using vtable address for GameEngine::Tick\n"));
                    UEngine::TickInternal.assign_address(vtable_address);
                }
                else if (scan_address)
                {
                    Output::send(STR("VTable lookup failed, falling back to scan address for GameEngine::Tick\n"));
                    UEngine::TickInternal.assign_address(scan_address);
                }
            }
            Hook::RegisterEngineTickPreCallback(HookedEngineTick, {true, false, STR("UE4SS"), STR("GameThreadInitializer")});
        }
        if (UnrealConfig.bHookInitGameState && GameMode)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(AGameModeBase, InitGameState, GameMode); func_address)
            {
                Output::send(STR("GameModeBase::InitGameState address {}\n"), func_address);
                AGameModeBase::InitGameStateInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookBeginPlay && Actor)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(AActor, BeginPlay, Actor); func_address)
            {
                Output::send(STR("AActor::BeginPlay address {}\n"), func_address);
                AActor::BeginPlayInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookEndPlay && Actor)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(AActor, EndPlay, Actor); func_address)
            {
                Output::send(STR("AActor::EndPlay address {}\n"), func_address);
                AActor::EndPlayInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookAActorTick && Actor)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(AActor, Tick, Actor); func_address)
            {
                Output::send(STR("AActor::Tick address {}\n"), func_address);
                AActor::TickInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookGameViewportClientTick && GameViewportClient)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(UGameViewportClient, Tick, GameViewportClient); func_address)
            {
                Output::send(STR("GameViewportClient::Tick address {}\n"), func_address);
                UGameViewportClient::TickInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookUObjectProcessEvent && Object)
        {
            if (auto func_address = OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(UObject, ProcessEvent, Object); func_address)
            {
                Output::send(STR("ProcessEvent address {}\n"), func_address);
                UObject::ProcessEventInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookProcessConsoleExec && Object)
        {
            if (auto func_address = GET_ADDRESS_OF_UNREAL_VIRTUAL(UObject, ProcessConsoleExec, Object); func_address)
            {
                Output::send(STR("ProcessConsoleExec address {}\n"), func_address);
                UObject::ProcessConsoleExecInternal.assign_address(func_address);
            }
        }
        if (UnrealConfig.bHookUStructLink && Struct)
        {
            if (auto func_address = GET_ADDRESS_OF_UNREAL_VIRTUAL(UStruct, Link, Struct); func_address)
            {
                Output::send(STR("UStruct::Link address {}\n"), func_address);
                UStruct::LinkInternal.assign_address(func_address);
            }
        }

        TypeChecker::store_all_object_names();

        Output::send(STR("Constructed {} of {} objects\n"), Hook::StaticStorage::NumRequiredObjectsConstructed, Hook::StaticStorage::RequiredObjectsForInit.size());
        if (!Hook::StaticStorage::bAllRequiredObjectsConstructed)
        {
            Output::send<LogLevel::Warning>(STR("Warning: The following required objects were never constructed (continuing in limited mode):\n"));
            for (const auto& RequiredObject : Hook::StaticStorage::RequiredObjectsForInit)
            {
                if (RequiredObject.ObjectConstructed) { continue; }
                Output::send<LogLevel::Warning>(STR("  MISSING: {}\n"), RequiredObject.ObjectNameParts.back().ToString());
            }
        }

#ifdef __linux__
        Output::send(STR("Calling store_all_object_types()...\n"));
#endif
        if (!TypeChecker::store_all_object_types())
        {
            Output::send<LogLevel::Warning>(STR("Warning: TypeChecker was unable to find some or all of the required core objects (continuing in limited mode)\n"));
        }
#ifdef __linux__
        Output::send(STR("store_all_object_types() completed\n"));
#endif

        if (UnrealConfig.bHookProcessInternal || UnrealConfig.bHookProcessLocalScriptFunction)
        {
#ifdef __linux__
            // On Linux, StaticFindObject uses GetFullName() which requires ProcessEvent
            // (not available on stripped binary). Skip this lookup to avoid crash.
            Output::send<LogLevel::Warning>(STR("Linux: Skipping ExecuteUbergraph lookup. ProcessInternal hook not available.\n"));
#else
            auto ExecuteUbergraphFunction = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR("/Script/CoreUObject.Object:ExecuteUbergraph"));
            if (!ExecuteUbergraphFunction)
            {
                Output::send<LogLevel::Warning>(STR("Warning: Was unable to locate ProcessInternal because '/Script/CoreUObject.Object:ExecuteUbergraph' wasn't found in GUObjectArray. ProcessInternal hook will not be available.\n"));
            }
            else
            {
            auto ProcessInternal = ExecuteUbergraphFunction->GetFuncPtr();
            ProcessInternal = std::bit_cast<decltype(ProcessInternal)>(RESOLVE_JMP(std::bit_cast<void*>(ProcessInternal)));
            // Only assign ProcessInternalInternal if no override exists, allowing Lua override to take precedence
            if (!UnrealConfig.ScanOverrides.process_internal)
            {
                UObject::ProcessInternalInternal.assign_address(ProcessInternal);
                // Log ProcessInternal address only for built-in detection
                Output::send(STR("ProcessInternal address: {}\n"), std::bit_cast<void*>(ProcessInternal));
            }

            // Skip ProcessLocalScriptFunction detection if override exists, preserving built-in logic otherwise
            if (!UnrealConfig.ScanOverrides.process_local_script_function && Version::IsAtLeast(4, 22))
            {
                // Use the final ProcessInternal address (overridden or built-in) for disassembly
                auto process_internal_addr = UObject::ProcessInternalInternal.get_function_address();
                if (!process_internal_addr)
                {
                    Output::send(STR("Error: ProcessInternal address is null, cannot compute ProcessLocalScriptFunction\n"));
                }
                else
                {
                    int CallCount{};
                    auto Data = std::bit_cast<ZyanU8*>(process_internal_addr);
                    ZydisDecoder Decoder;
                    ZydisDecoderInit(&Decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
                    ZyanU64 RuntimeAddress = std::bit_cast<ZyanU64>(process_internal_addr);
                    ZyanUSize Offset = 0;
                    const ZyanUSize NumBytesToDecode = 164;
                    ZydisDecodedInstruction Instruction;
                    ZydisDecodedOperand Operands[10]{};
                    while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&Decoder, Data + Offset, NumBytesToDecode - Offset, &Instruction, Operands)))
                    {
                        if (Instruction.mnemonic == ZYDIS_MNEMONIC_CALL)
                        {
                            ++CallCount;
                        }
                        if (CallCount == 3)
                        {
                            auto FunctionPtr = ASM::resolve_function_address_from_potential_jmp(std::bit_cast<void*>(RuntimeAddress));
                            if (FunctionPtr)
                            {
                                UObject::ProcessLocalScriptFunctionInternal.assign_address(FunctionPtr);
                                // Log ProcessLocalScriptFunction address only for built-in detection
                                Output::send(STR("ProcessLocalScriptFunction address: {}\n"), static_cast<void*>(FunctionPtr));
                            }
                            break;
                        }
                        Offset += Instruction.length;
                        RuntimeAddress += Instruction.length;
                    }
                }
            }
            } // end else (ExecuteUbergraphFunction found)
#endif
        }

        Output::send<LogLevel::Verbose>(STR("UnrealConfig.FExecVTableOffsetInLocalPlayer: {:X}\n"), UnrealConfig.FExecVTableOffsetInLocalPlayer);

#ifdef __linux__
        Output::send(STR("About to skip PostInitialize...\n"));
#endif
#ifdef __linux__
        // On Linux, PostInitialize calls ForEachUObject with a callback that does
        // virtual calls (IsA<UClass>, IsChildOf<AActor>) on each object. Stale
        // pointers from GC-freed objects cause SIGSEGV. Since hooks don't work
        // on the stripped binary, skip PostInitialize and proceed to mod loading.
        Output::send<LogLevel::Warning>(STR("Linux: Skipping PostInitialize (object searcher pool population) to avoid stale-pointer crashes.\n"));
        StaticStorage::bIsInitialized = true;
#else
        PostInitialize(UnrealConfig);
#endif
    }
}

namespace RC::Unreal
{
    auto GetGameThreadId() -> std::thread::id
    {
        if (!UnrealInitializer::GGameThreadIdInitialized)
        {
            throw std::runtime_error{"GetGameThreadId called too early, not yet initialized by UGameEngine::Tick"};
        }
        return UnrealInitializer::GGameThreadId;
    }

    auto IsInGameThread() -> bool
    {
        return std::this_thread::get_id() == GetGameThreadId();
    }

    auto IsGameThreadInitialized() noexcept-> bool
    {
        return UnrealInitializer::GGameThreadIdInitialized;
    }

    auto GetGameThreadIdRaw() noexcept -> std::thread::id
    {
        if (!UnrealInitializer::GGameThreadIdInitialized)
        {
            return {};
        }
        return UnrealInitializer::GGameThreadId;
    }

    auto IsInGameThreadRaw() noexcept -> bool
    {
        return IsGameThreadInitialized() && std::this_thread::get_id() == GetGameThreadId();
    }
}
