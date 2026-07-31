// ===========================================================================
// UE4SS Linux Native Port
// Copyright (c) 2026 BlackBookOfficial
// Based on RE-UE4SS by UE4SS-RE (https://github.com/UE4SS-RE/RE-UE4SS)
// Palworld fork by Yangff
// Linux native port by BlackBookOfficial
//
// Licensed under the MIT License. See LICENSE and NOTICE for details.
// ===========================================================================

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#ifdef TEXT
#undef TEXT
#endif
#else
#include <unistd.h>
#include <dlfcn.h>
#include <funchook.h>
#endif

#include <algorithm>
#include <cstdio>
#include <cwctype>
#include <format>
#include <fstream>
#include <chrono>
#include <functional>
#include <limits>
#include <thread>
#include <unordered_set>
#include <set>
#include <vector>
#include <fmt/chrono.h>
#include <Profiler/Profiler.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <ExceptionHandling.hpp>
#ifdef HAS_GUI
#include <GUI/ConsoleOutputDevice.hpp>
#include <GUI/GUI.hpp>
#include <GUI/LiveView.hpp>
#endif
#include <Helpers/ASM.hpp>
#include <Helpers/Format.hpp>
#include <Helpers/Integer.hpp>
#include <Helpers/String.hpp>
#include <Helpers/Time.hpp>
#include <IniParser/Ini.hpp>
#include <LuaLibrary.hpp>
#include <LuaType/LuaCustomProperty.hpp>
#include <LuaType/LuaUObject.hpp>
#include <Mod/CppMod.hpp>
#include <Mod/LuaMod.hpp>
#include <Mod/Mod.hpp>
#ifdef __linux__
#include <DiscordWebhook.hpp>
#include <link.h>
#include <elf.h>
#include <cstring>
#endif
#include <ObjectDumper/ObjectToString.hpp>
#include <SDKGenerator/Generator.hpp>
#include <SDKGenerator/UEHeaderGenerator.hpp>
#include <SigScanner/SinglePassSigScanner.hpp>
#include <Signatures.hpp>
#include <Unreal/Signatures.hpp>
#include <Timer/ScopedTimer.hpp>
#include <UE4SSProgram.hpp>
#include <UE4SSDebug.hpp>
#include <Unreal/AGameMode.hpp>
#include <Unreal/AGameModeBase.hpp>
#include <Unreal/GameplayStatics.hpp>
#include <Unreal/Searcher/ObjectSearcher.hpp>
#include <Unreal/Core/Templates/Tuple.hpp>
#include <Unreal/UEngine.hpp>
#include <Unreal/TypeChecker.hpp>
#include <Unreal/UActorComponent.hpp>
#include <Unreal/UInterface.hpp>
#include <Unreal/UKismetSystemLibrary.hpp>
#include <Unreal/ULocalPlayer.hpp>
#include <Unreal/UObjectArray.hpp>
#include <Unreal/UPackage.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/UnrealInitializer.hpp>
#include <Unreal/World.hpp>
#include <Unreal/FWorldContext.hpp>
#include <Unreal/Engine/UDataTable.hpp>
#include <Unreal/BitfieldProxy.hpp>
#include <UnrealDef.hpp>

#ifdef _WIN32
#include <polyhook2/PE/IatHook.hpp>
#endif

#include <FilesystemWatcher.hpp>

#ifdef __linux__
extern "C" bool ue4ss_with_crash_recovery(const std::function<void()>& func);
extern "C" bool ue4ss_with_iter_recovery(const std::function<void()>& func);
extern "C" bool ue4ss_with_alloc_recovery(const std::function<void()>& func);
#endif

namespace RC
{
    // Commented out because this system (turn off hotkeys when in-game console is open) it doesn't work properly.
    /*
    struct RC_UE_API FUEDeathListener : public Unreal::FUObjectCreateListener
    {
        static FUEDeathListener UEDeathListener;

        void NotifyUObjectCreated(const Unreal::UObjectBase* object, int32_t index) override {}
        void OnUObjectArrayShutdown() override
        {
            UE4SSProgram::unreal_is_shutting_down = true;
            Unreal::UObjectArray::RemoveUObjectCreateListener(this);
        }
    };
    FUEDeathListener FUEDeathListener::UEDeathListener{};

    auto get_player_controller() -> UObject*
    {
        std::vector<Unreal::UObject*> player_controllers{};
        UObjectGlobals::FindAllOf(STR("PlayerController"), player_controllers);
        if (!player_controllers.empty())
        {
            return player_controllers.back();
        }
        else
        {
            return nullptr;
        }
    }
    //*/

    SettingsManager UE4SSProgram::settings_manager{};

#define OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(StructName)                                                                                                           \
    for (const auto& [name, offset] : Unreal::StructName::MemberOffsets)                                                                                       \
    {                                                                                                                                                          \
        Output::send(STR(#StructName "::{} = 0x{:X}\n"), name, offset);                                                                                        \
    }

    enum class IsCoalesced
    {
        Yes,
        No,
    };
    auto output_all_member_offsets(IsCoalesced is_coalesced) -> void
    {
        Output::send(STR("\n##### MEMBER OFFSETS START ({}) #####\n\n"), is_coalesced == IsCoalesced::No ? STR("MemberVariableLayout") : STR("Coalesced"));
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UObjectBase);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UScriptStruct::ICppStructOps);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UStruct);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UScriptStruct);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UClass);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UEnum);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UFunction);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(USparseDelegateFunction);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UField);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FField);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FNumericProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FObjectPropertyBase);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FStructProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FArrayProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FMapProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FSetProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FBoolProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FByteProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FEnumProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FClassProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FSoftClassProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FDelegateProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FMulticastDelegateProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FInterfaceProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FFieldPathProperty);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FWorldContext);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FOutputDevice);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FArchiveState);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FArchive);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(AActor);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(AGameModeBase);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(AGameMode);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UEngine);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UGameViewportClient);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UPlayer);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(ULocalPlayer);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UWorld);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(UDataTable);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FUObjectItem);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(FUObjectArray);
        OUTPUT_MEMBER_OFFSETS_FOR_STRUCT(TUObjectArray);
        Output::send(STR("\n##### MEMBER OFFSETS END ({}) #####\n\n"), is_coalesced == IsCoalesced::No ? STR("MemberVariableLayout") : STR("Coalesced"));
    }

#ifdef _WIN32
    void* HookedLoadLibraryA(const char* lib_name)
    {
        UE4SSProgram& program = UE4SSProgram::get_program();
        HMODULE lib = PLH::FnCast(program.m_hook_trampoline_load_library_a, &LoadLibraryA)(lib_name);
        program.fire_lib_load_for_cpp_mods(ensure_str(lib_name));
        return lib;
    }

    void* HookedLoadLibraryExA(const char* lib_name, void* file, int32_t flags)
    {
        UE4SSProgram& program = UE4SSProgram::get_program();
        HMODULE lib = PLH::FnCast(program.m_hook_trampoline_load_library_ex_a, &LoadLibraryExA)(lib_name, file, flags);
        program.fire_lib_load_for_cpp_mods(ensure_str(lib_name));
        return lib;
    }

    void* HookedLoadLibraryW(const wchar_t* lib_name)
    {
        UE4SSProgram& program = UE4SSProgram::get_program();
        HMODULE lib = PLH::FnCast(program.m_hook_trampoline_load_library_w, &LoadLibraryW)(lib_name);
        program.fire_lib_load_for_cpp_mods(ToCharTypePtr(lib_name));
        return lib;
    }

    void* HookedLoadLibraryExW(const wchar_t* lib_name, void* file, int32_t flags)
    {
        UE4SSProgram& program = UE4SSProgram::get_program();
        HMODULE lib = PLH::FnCast(program.m_hook_trampoline_load_library_ex_w, &LoadLibraryExW)(lib_name, file, flags);
        program.fire_lib_load_for_cpp_mods(ToCharTypePtr(lib_name));
        return lib;
    }
#endif // _WIN32

#ifndef _WIN32
    void* (*dlopen_hooked)(const char* filename, int flag) = nullptr;

    void* HookedDlopen(const char* filename, int flag)
    {
        void* result = dlopen_hooked(filename, flag);
        if (filename && result)
        {
            UE4SSProgram& program = UE4SSProgram::get_program();
            program.fire_lib_load_for_cpp_mods(ensure_str(filename));
        }
        return result;
    }
#endif

    UE4SSProgram::UE4SSProgram(const std::filesystem::path& moduleFilePath, std::initializer_list<BinaryOptions> options) : MProgram(options)
    {
        ProfilerScope();
        s_program = this;

        try
        {
            UE4SS_DBG( "[UE4SS] Constructor: calling setup_paths()...\n");
            setup_paths(moduleFilePath);
            UE4SS_DBG( "[UE4SS] Constructor: setup_paths() done. root=%s\n", m_root_directory.string().c_str());

            // Auto-create UE4SS-settings.ini with default content if it doesn't exist
            UE4SS_DBG( "[UE4SS] Constructor: checking settings file at %s...\n", m_settings_path_and_file.string().c_str());
            if (!std::filesystem::exists(m_settings_path_and_file))
            {
                UE4SS_DBG( "[UE4SS] Constructor: creating default settings file...\n");
                std::error_code ec;
                std::filesystem::create_directories(m_settings_path_and_file.parent_path(), ec);
                if (ec)
                {
                    UE4SS_DBG( "[UE4SS] Constructor: failed to create directories: %s\n", ec.message().c_str());
                }
                std::ofstream default_settings(m_settings_path_and_file);
                if (default_settings.is_open())
                {
                    default_settings << "[General]\n";
                    default_settings << "EnableHotReloadSystem=true\n";
                    default_settings << "HotReloadKey=R\n";
                    default_settings << "EnableAutoReloadingLuaMods=true\n";
                    default_settings << "UseCache=true\n";
                    default_settings << "InvalidateCacheIfDLLDiffers=true\n";
                    default_settings << "EnableDebugKeyBindings=false\n";
                    default_settings << "SecondsToScanBeforeGivingUp=30\n";
                    default_settings << "bUseUObjectArrayCache=true\n";
                    default_settings << "DoEarlyScan=false\n";
                    default_settings << "bEnableSeachByMemoryAddress=false\n";
                    default_settings << "DefaultExecuteInGameThreadMethod=GameThread\n";
                    default_settings << "DiscordWebhookURL=\n";
                    default_settings << "DebugLogLevel=0\n";
                    default_settings << "[Debug]\n";
                    default_settings << "DebugConsoleEnabled=false\n";
                    default_settings << "SimpleConsoleEnabled=true\n";
                    default_settings << "[Threads]\n";
                    default_settings << "SigScannerNumThreads=-1\n";
                    default_settings << "SigScannerMultithreadingModuleSizeThreshold=104857600\n";
                    default_settings << "[Hooks]\n";
                    default_settings << "HookProcessInternal=true\n";
                    default_settings << "HookProcessLocalScriptFunction=true\n";
                    default_settings << "HookLoadMap=true\n";
                    default_settings << "HookInitGameState=true\n";
                    default_settings << "HookCallFunctionByNameWithArguments=true\n";
                    default_settings << "HookBeginPlay=true\n";
                    default_settings << "HookEndPlay=true\n";
                    default_settings.close();
                    Output::send(STR("Created default settings file: {}\n"), ensure_str(m_settings_path_and_file));
                }
            }

            // Auto-create Mods directory, default mod, and mods.txt early (before init() which may crash)
            {
                auto mods_dir = m_working_directory / "Mods";
                if (!std::filesystem::exists(mods_dir))
                {
                    std::error_code ec;
                    std::filesystem::create_directories(mods_dir, ec);
                    if (!ec)
                    {
                        Output::send(STR("Created mods directory: {}\n"), ensure_str(mods_dir));
                    }
                }

                // Auto-create default UE4SSStatus mod
                auto status_mod_dir = mods_dir / "UE4SSStatus";
                auto status_scripts_dir = status_mod_dir / "scripts";
                if (!std::filesystem::exists(status_scripts_dir))
                {
                    std::error_code ec;
                    std::filesystem::create_directories(status_scripts_dir, ec);
                    if (!ec)
                    {
                        std::ofstream main_lua(status_scripts_dir / "main.lua");
                        if (main_lua.is_open())
                        {
                            main_lua << "-- UE4SSStatus: Shows UE4SS is active\n";
                            main_lua << "-- This mod is auto-generated by UE4SS\n\n";
                            main_lua << "print('[UE4SS] UE4SSStatus mod loaded - UE4SS is active and running!')\n";
                            main_lua << "\n";
                            main_lua << "-- Note: On Linux limited mode, UE hooks (BeginPlay, InitGameState) are not available.\n";
                            main_lua << "-- This mod simply confirms that the Lua mod loader is working.\n";
                            main_lua.close();
                            Output::send(STR("Created default UE4SSStatus mod: {}\n"), ensure_str(status_mod_dir));
                        }
                    }
                }

                auto mods_txt_path = mods_dir / "mods.txt";
                if (!std::filesystem::exists(mods_txt_path))
                {
                    std::ofstream mods_txt(mods_txt_path);
                    if (mods_txt.is_open())
                    {
                        mods_txt << "; Lines starting with ';' are comments\n";
                        mods_txt << "; Add mod folder names here (one per line) to enable them\n";
                        mods_txt << "; Format: ModName : 1 (enabled) or ModName : 0 (disabled)\n";
                        mods_txt << "; Prefix with ';' to disable a mod\n\n";
                        mods_txt << "UE4SSStatus : 1\n";
                        mods_txt.close();
                        Output::send(STR("Created default mods.txt: {}\n"), ensure_str(mods_txt_path));
                    }
                }
                else
                {
                    // Check if UE4SSStatus is already in mods.txt, if not add it
                    bool found_in_txt = false;
                    std::string txt_content;
                    {
                        std::ifstream existing_txt(mods_txt_path);
                        if (existing_txt.is_open())
                        {
                            std::string line;
                            while (std::getline(existing_txt, line))
                            {
                                if (line.find("UE4SSStatus") != std::string::npos)
                                {
                                    found_in_txt = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (!found_in_txt)
                    {
                        std::ofstream append_txt(mods_txt_path, std::ios::app);
                        if (append_txt.is_open())
                        {
                            append_txt << "\nUE4SSStatus : 1\n";
                            append_txt.close();
                            Output::send(STR("Added UE4SSStatus to mods.txt\n"));
                        }
                    }
                }
            }

            UE4SS_DBG( "[UE4SS] Constructor: deserializing settings from %s...\n", m_settings_path_and_file.string().c_str());
            try
            {
                settings_manager.deserialize(m_settings_path_and_file);
                UE4SS_DBG( "[UE4SS] Constructor: settings deserialized.\n");
#ifdef __linux__
                UE4SSDebug::set_debug_level(static_cast<int>(settings_manager.General.DebugLogLevel));
#endif
            }
            catch (std::exception& e)
            {
                create_emergency_console_for_early_error(fmt::format(STR("The IniParser failed to parse: {}"), ensure_str(e.what())));
                return;
            }

            if (settings_manager.EngineVersionOverride.DebugBuild)
            {
                if (Unreal::Version::IsAtLeast(4, 25))
                {
                    Unreal::FUObjectItem::UEP_TotalSize() += sizeof(void*);
                }
            }

            UE4SS_DBG( "[UE4SS] Constructor: checking crash dump settings...\n");
            if (settings_manager.CrashDump.EnableDumping)
            {
                m_crash_dumper.enable();
            }

            m_crash_dumper.set_full_memory_dump(settings_manager.CrashDump.FullMemoryDump);
            UE4SS_DBG( "[UE4SS] Constructor: done.\n");

#ifdef HAS_GUI
            m_debugging_gui.set_gfx_backend(settings_manager.Debug.GraphicsAPI);
#endif

            // Setup the log file
            auto& file_device = Output::set_default_devices<Output::NewFileDevice>();
            file_device.set_file_name_and_path(ensure_str((m_log_directory / m_log_file_name)));

            if (const auto ue4ss_mods_paths_var_raw = std::getenv("UE4SS_MODS_PATHS"); ue4ss_mods_paths_var_raw)
            {
                const auto ue4ss_mods_paths_var = ensure_str(ue4ss_mods_paths_var_raw);
                Output::send(STR("Environment variable 'UE4SS_MODS_PATHS' present, adding 'Mods' path overrides: {}\n"), ue4ss_mods_paths_var);
                const auto paths = parse_semicolon_separated_string(ue4ss_mods_paths_var);
                for (const auto& path : std::ranges::reverse_view(paths))
                {
                    add_mods_directory(std::filesystem::weakly_canonical(path));
                }
            }

            create_simple_console();

            if (settings_manager.Debug.DebugConsoleEnabled)
            {
#ifdef HAS_GUI
                m_console_device = &Output::set_default_devices<Output::ConsoleDevice>();
                m_console_device->set_formatter([](File::StringViewType string) -> File::StringType {
                    return fmt::format(STR("[{}] {}"), get_now_as_string(STR("{:%X}")), string);
                });
                if (settings_manager.Debug.DebugConsoleVisible)
                {
#ifdef HAS_GUI
                    switch (settings_manager.Debug.RenderMode)
                    {
                    case GUI::RenderMode::ExternalThread:
                        m_render_thread = std::jthread{&GUI::gui_thread, &m_debugging_gui};
                        break;
                    case GUI::RenderMode::EngineTick:
                    case GUI::RenderMode::GameViewportClientTick:
                        // The hooked game function will pick up on the window being "open", and start rendering.
                        get_debugging_ui().set_open(true);
                        break;
                    }
#endif
                }
#endif
            }

            // This is experimental code that's here only for future reference
            /*
            Unreal::UnrealInitializer::SetupUnrealModules();

            constexpr const wchar_t* str_to_find = STR("Allocator: %s");
            void* string_address = SinglePassScanner::string_scan(str_to_find, ScanTarget::Core);
            Output::send(STR("\n\nFound string '{}' at {}\n\n"), std::wstring_view{str_to_find}, string_address);
            //*/

            Output::send(STR("Console created\n"));
            Output::send(STR("UE4SS - v{}.{}.{}{}{} - Git SHA #{}\n"),
                         UE4SS_LIB_VERSION_MAJOR,
                         UE4SS_LIB_VERSION_MINOR,
                         UE4SS_LIB_VERSION_HOTFIX,
                         fmt::format(STR("{}"), UE4SS_LIB_VERSION_PRERELEASE == 0 ? STR("") : fmt::format(STR(" PreRelease #{}"), UE4SS_LIB_VERSION_PRERELEASE)),
                         fmt::format(STR("{}"),
                                     UE4SS_LIB_BETA_STARTED == 0
                                             ? STR("")
                                             : (UE4SS_LIB_IS_BETA == 0 ? STR(" Beta #?") : fmt::format(STR(" Beta #{}"), UE4SS_LIB_VERSION_BETA))),
                         ensure_str(UE4SS_LIB_BUILD_GITSHA));

            // Copyright banner in the UE4SS console
            Output::send<LogLevel::Normal>(STR(" Copyright (c) 2026 BlackBookOfficial\n"));
            Output::send<LogLevel::Normal>(STR(" https://github.com/BlackBookOfficial/ue4ss-linux-palworld\n"));
            Output::send<LogLevel::Normal>(STR(" Palworld fork by Yangff\n"));
            Output::send<LogLevel::Normal>(STR(" Linux native port by BlackBookOfficial\n"));
            Output::send<LogLevel::Normal>(STR(" Based on RE-UE4SS by UE4SS-RE\n"));
            Output::send<LogLevel::Normal>(STR("========================================\n"));

            bool use_local_time = true;
#ifdef _WIN32
            if (auto module = GetModuleHandleW(L"ntdll.dll"); module && GetProcAddress(module, "wine_get_version"))
            {
                use_local_time = false;
            }
#endif
            if (use_local_time)
            {
                try
                {
                    Output::send(STR("Timezone: {}\n"), ensure_str(std::chrono::current_zone()->name()));
                }
                catch (std::runtime_error&)
                {
                    Output::send(STR("Timezone: UTC (local disabled due to lack of support (chrono::current_zone() failed))\n"));
                }
            }
            else
            {
                Output::send(STR("Timezone: UTC (local disabled due to wine)\n"));
            }

#ifdef __clang__
#define UE4SS_COMPILER STR("Clang")
#elif defined(__GNUC__)
#define UE4SS_COMPILER STR("GCC")
#else
#define UE4SS_COMPILER STR("MSVC")
#endif

            Output::send(STR("UE4SS Build Configuration: {} ({})\n"), ensure_str(UE4SS_CONFIGURATION), UE4SS_COMPILER);

#ifdef _WIN32
            m_load_library_a_hook = std::make_unique<PLH::IatHook>("kernel32.dll",
                                                                   "LoadLibraryA",
                                                                   std::bit_cast<uint64_t>(&HookedLoadLibraryA),
                                                                   &m_hook_trampoline_load_library_a,
                                                                   L"");
            m_load_library_a_hook->hook();

            m_load_library_ex_a_hook = std::make_unique<PLH::IatHook>("kernel32.dll",
                                                                      "LoadLibraryExA",
                                                                      std::bit_cast<uint64_t>(&HookedLoadLibraryExA),
                                                                      &m_hook_trampoline_load_library_ex_a,
                                                                      L"");
            m_load_library_ex_a_hook->hook();

            m_load_library_w_hook = std::make_unique<PLH::IatHook>("kernel32.dll",
                                                                   "LoadLibraryW",
                                                                   std::bit_cast<uint64_t>(&HookedLoadLibraryW),
                                                                   &m_hook_trampoline_load_library_w,
                                                                   L"");
            m_load_library_w_hook->hook();

            m_load_library_ex_w_hook = std::make_unique<PLH::IatHook>("kernel32.dll",
                                                                      "LoadLibraryExW",
                                                                      std::bit_cast<uint64_t>(&HookedLoadLibraryExW),
                                                                      &m_hook_trampoline_load_library_ex_w,
                                                                      L"");
            m_load_library_ex_w_hook->hook();
#endif // _WIN32
#ifndef _WIN32
            // dlopen hook disabled on Linux — if a C++ mod's dlopen crashes and we
            // siglongjmp out, funchook's trampoline leaves dlopen's internal state
            // corrupted, causing every subsequent dlopen call to SIGSEGV.
            // The hook is only used for fire_lib_load_for_cpp_mods notifications,
            // which are non-essential in limited mode.
            // dlopen_hooked = reinterpret_cast<void* (*)(const char*, int)>(dlsym(RTLD_NEXT, "dlopen"));
            // ... (intentionally disabled)
#endif

            UE4SS_DBG( "[UE4SS] Calling SetupUnrealModules()...\n");
            Unreal::UnrealInitializer::SetupUnrealModules();
            UE4SS_DBG( "[UE4SS] SetupUnrealModules() done.\n");

            UE4SS_DBG( "[UE4SS] Setting up mod directory path...\n");
            setup_mod_directory_path();
            UE4SS_DBG( "[UE4SS] Mod directory path set.\n");

            UE4SS_DBG( "[UE4SS] Setting up mods...\n");
            setup_mods();
            UE4SS_DBG( "[UE4SS] Mods setup done.\n");

            UE4SS_DBG( "[UE4SS] Installing C++ mods...\n");
            install_cpp_mods();
#ifdef __linux__
            // On Linux, defer starting C++ mods until after setup_unreal() has resolved
            // UE function addresses (GUObjectArray, ProcessEvent, etc.). C++ mods like
            // PalSentinel need these addresses in their start_mod() function.
            UE4SS_DBG( "[UE4SS] Deferring C++ mod start until after setup_unreal() on Linux...\n");
#else
            UE4SS_DBG( "[UE4SS] Starting C++ mods...\n");
            start_cpp_mods(IsInitialStartup::Yes);
            UE4SS_DBG( "[UE4SS] C++ mods started.\n");
#endif

            if (m_has_game_specific_config)
            {
                Output::send(STR("Found configuration for game: {}\n"), ensure_str(m_working_directory.filename()));
            }
            else
            {
                Output::send(STR("No specific game configuration found, using default configuration file\n"));
            }

            Output::send(STR("Config: {}\n\n"), ensure_str(m_settings_path_and_file));
            Output::send(STR("root directory: {}\n"), ensure_str(m_root_directory));
            Output::send(STR("working directory: {}\n"), ensure_str(m_working_directory));
            Output::send(STR("game executable directory: {}\n"), ensure_str(m_game_executable_directory));
            Output::send(STR("game executable: {} ({} bytes)\n\n\n"), ensure_str(m_game_path_and_exe_name), std::filesystem::file_size(m_game_path_and_exe_name));
            Output::send(STR("mods directories: \n"));
            for (const auto& [index, mod_directory] : std::ranges::enumerate_view(m_mods_directories))
            {
                Output::send(STR("[{}] {}\n"), index, ensure_str(mod_directory));
            }
            Output::send(STR("\n"));
            Output::send(STR("log directory: {}\n"), ensure_str(m_log_directory));
            Output::send(STR("object dumper directory: {}\n\n\n"), ensure_str(m_object_dumper_output_directory));

#ifdef __linux__
            // Send Discord webhook notification if configured
            if (!settings_manager.General.DiscordWebhookURL.empty())
            {
                std::string webhook_url = to_string(settings_manager.General.DiscordWebhookURL);
                std::string description = "UE4SS has been initialized successfully.\n";
                description += "Game executable: " + to_string(ensure_str(m_game_path_and_exe_name)) + "\n";
                description += "Working directory: " + to_string(ensure_str(m_working_directory)) + "\n";
                description += "Mods directory: " + to_string(ensure_str(m_mods_directories.empty() ? STR("") : m_mods_directories[0])) + "\n";
                description += "UE4SS version: v3.0.1 Beta";
                DiscordWebhook::send_embed(webhook_url, "UE4SS Status", description, 0x00FF00);
                UE4SS_DBG( "[UE4SS] Discord webhook notification sent.\n");
            }
#endif
        }
        catch (std::runtime_error& e)
        {
            // Returns to main from here which checks, displays & handles whether to close the program or not
            // If has_error() returns false that means that set_error was not called
            // In that case we need to copy the exception message to the error buffer before we return to main
            if (!m_error_object->has_error())
            {
                copy_error_into_message(e.what());
            }
            return;
        }
    }

    UE4SSProgram::~UE4SSProgram()
    {
        // Shut down the event loop
        m_processing_events = false;

#ifndef _WIN32
        // Uninstall dlopen hook on Linux
        if (m_dlopen_hook_handle)
        {
            funchook_uninstall(m_dlopen_hook_handle, 0);
            funchook_destroy(m_dlopen_hook_handle);
            m_dlopen_hook_handle = nullptr;
        }
#endif

        // It's possible that main() will destroy the default devices (they are static)
        // However it's also possible that this program object is constructed in a context where main() is not gonna immediately exit
        // Because of that and because the default devices are created in the constructor, it's preferred to explicitly close all default devices in the destructor
        Output::close_all_default_devices();
    }

    auto UE4SSProgram::init() -> void
    {
        ProfilerSetThreadName("UE4SS-InitThread");
        ProfilerScope();

        try
        {
            setup_unreal();

#ifdef __linux__
            // Now that setup_unreal() has resolved UE addresses, start C++ mods
            // (deferred from constructor on Linux to avoid crashes when mods need UE addresses)
            UE4SS_DBG( "[UE4SS] Starting C++ mods (deferred, post setup_unreal)...\n");
            start_cpp_mods(IsInitialStartup::Yes);
            UE4SS_DBG( "[UE4SS] C++ mods started.\n");
#endif

            Output::send(STR("Unreal Engine modules ({}):\n"), SigScannerStaticData::m_is_modular ? STR("modular") : STR("non-modular"));
            auto& main_exe_ptr = SigScannerStaticData::m_modules_info.array[static_cast<size_t>(ScanTarget::MainExe)].lpBaseOfDll;
            for (size_t i = 0; i < static_cast<size_t>(ScanTarget::Max); ++i)
            {
                auto& module = SigScannerStaticData::m_modules_info.array[i];
                // only log modules with unique addresses (non-modular builds have everything in MainExe)
                if (i == static_cast<size_t>(ScanTarget::MainExe) || main_exe_ptr != module.lpBaseOfDll)
                {
                    auto module_name = ensure_str(ScanTargetToString(i));
                    Output::send(STR("{} @ {} size={:#x}\n"), module_name.c_str(), module.lpBaseOfDll, module.SizeOfImage);
                }
            }

            fire_unreal_init_for_cpp_mods();
            setup_unreal_properties();
            UAssetRegistry::SetMaxMemoryUsageDuringAssetLoading(settings_manager.Memory.MaxMemoryUsageDuringAssetLoading);

            share_lua_functions();

            // Only deal with the event loop thread here if the 'Test' constructor doesn't need to be called
#ifndef RUN_TESTS
            // Program is now fully setup
            // Start event loop
            m_event_loop = std::jthread{&UE4SSProgram::update, this};

            // Wait for thread
            // There's a loop inside the thread that only exits when you hit the 'End' key on the keyboard
            // As long as you don't do that the thread will stay open and accept further inputs
            m_event_loop.join();
#endif
        }
        catch (std::runtime_error& e)
        {
            // Returns to main from here which checks, displays & handles whether to close the program or not
            // If has_error() returns false that means that set_error was not called
            // In that case we need to copy the exception message to the error buffer before we return to main
            if (!m_error_object->has_error())
            {
                copy_error_into_message(e.what());
            }
            return;
        }
    }

    auto UE4SSProgram::setup_paths(const std::filesystem::path& moduleFilePath) -> void
    {
        ProfilerScope();
        m_root_directory = moduleFilePath.parent_path();
        m_module_file_path = moduleFilePath;

        // The default working directory is the root directory
        // Can be changed by creating a <GameName> directory in the root directory
        // At that point, the working directory will be "root/<GameName>"
        m_working_directory = m_root_directory;

#ifdef _WIN32
        wchar_t exe_path_buffer[1024];
        GetModuleFileNameW(GetModuleHandle(nullptr), exe_path_buffer, 1023);
        std::filesystem::path game_exe_path = exe_path_buffer;
#else
        char exe_path_buffer[1024];
        ssize_t len = readlink("/proc/self/exe", exe_path_buffer, sizeof(exe_path_buffer) - 1);
        if (len > 0)
        {
            exe_path_buffer[len] = '\0';
        }
        else
        {
            exe_path_buffer[0] = '\0';
        }
        std::filesystem::path game_exe_path = exe_path_buffer;
#endif
        std::filesystem::path game_directory_path = game_exe_path.parent_path();
        m_legacy_root_directory = game_directory_path;

        m_working_directory = m_root_directory;
        m_game_executable_directory = game_directory_path;
        m_settings_path_and_file = m_root_directory;
        m_game_path_and_exe_name = game_exe_path;
        m_object_dumper_output_directory = m_working_directory;

#ifdef _WIN32
        // Allow loading of DLLs from the game directory
        AddDllDirectory(game_exe_path.c_str());
#endif

        std::error_code dir_ec;
        for (const auto& item : std::filesystem::directory_iterator(m_root_directory, dir_ec))
        {
            if (!item.is_directory())
            {
                continue;
            }

            if (item.path().filename() == game_directory_path.parent_path().parent_path().parent_path().filename())
            {
                m_has_game_specific_config = true;
                m_working_directory = item.path();
                m_settings_path_and_file = std::move(item.path());
                m_log_directory = m_working_directory;
                m_object_dumper_output_directory = m_working_directory;
                m_legacy_root_directory = m_legacy_root_directory / item.path();
                break;
            }
        }

        m_log_directory = m_working_directory;
        m_settings_path_and_file.append(m_settings_file_name);

        // Check for legacy locations and update paths accordingly
        if (std::filesystem::exists(m_legacy_root_directory / m_settings_file_name) && !std::filesystem::exists(m_settings_path_and_file))
        {
            m_settings_path_and_file = m_legacy_root_directory / m_settings_file_name;
        }
    }

    auto UE4SSProgram::create_emergency_console_for_early_error(File::StringViewType error_message) -> void
    {
        settings_manager.Debug.SimpleConsoleEnabled = true;
        create_simple_console();
        std::printf("%s\n", to_utf8_string(File::StringType{error_message}).c_str());
    }

    auto UE4SSProgram::setup_mod_directory_path() -> void
    {
        std::filesystem::path default_mods_path{};
        if (!settings_manager.Overrides.ModsFolderPath.empty())
        {
            default_mods_path = settings_manager.Overrides.ModsFolderPath;
        }
        else
        {
            default_mods_path = m_working_directory / "Mods";
        }

        // If no paths were added, check legacy location for fallback
        if (std::filesystem::exists(m_legacy_root_directory / "Mods") && !std::filesystem::exists(default_mods_path))
        {
            default_mods_path = m_legacy_root_directory / "Mods";
        }

        insert_mods_directory(default_mods_path, 0);

        for (const auto& path : m_mods_directories_to_remove)
        {
            std::erase(m_mods_directories, path);
        }
    }

    auto UE4SSProgram::create_simple_console() -> void
    {
        if (settings_manager.Debug.SimpleConsoleEnabled)
        {
            m_debug_console_device = &Output::set_default_devices<Output::DebugConsoleDevice>();
            Output::set_default_log_level<LogLevel::Normal>();
            m_debug_console_device->set_formatter([](File::StringViewType string) -> File::StringType {
                return fmt::format(STR("[{}] {}"), get_now_as_string(STR("{:%X}")), string);
            });

            if (settings_manager.Debug.SimpleConsoleEnabled)
            {
#ifdef _WIN32
                if (AllocConsole())
                {
                    FILE* stdin_filename;
                    FILE* stdout_filename;
                    FILE* stderr_filename;
                    freopen_s(&stdin_filename, "CONIN$", "r", stdin);
                    freopen_s(&stdout_filename, "CONOUT$", "w", stdout);
                    freopen_s(&stderr_filename, "CONOUT$", "w", stderr);
                }
#else
                // On Linux, console is already available when running from terminal
                // No need to allocate a console
#endif
            }
        }
    }

    auto UE4SSProgram::load_unreal_offsets_from_file() -> void
    {
        std::filesystem::path file_path = m_working_directory / "MemberVariableLayout.ini";
        if (std::filesystem::exists(file_path))
        {
            auto file = File::open(file_path);
            if (auto file_contents = file.read_all(); !file_contents.empty())
            {
                Ini::Parser parser;
                parser.parse(file_contents);
                file.close();

                // The following code is auto-generated.
#include <MacroSetter.hpp>

                m_custom_member_variable_layout_loaded = true;
            }
        }
    }

    auto UE4SSProgram::setup_unreal() -> void
    {
        ProfilerScope();
        // Retrieve offsets from the config file
        const StringType offset_overrides_section{STR("OffsetOverrides")};

        load_unreal_offsets_from_file();

        if (m_custom_member_variable_layout_loaded)
        {
            Output::send(STR("MemberVariableLayout.ini loaded\n"));
            output_all_member_offsets(IsCoalesced::No);
        }

        Unreal::UnrealInitializer::Config config;
        config.CachePath = m_root_directory / "cache";
        config.bInvalidateCacheIfSelfChanged = settings_manager.General.InvalidateCacheIfDLLDiffers;
        config.bEnableCache = settings_manager.General.UseCache;
        config.SecondsToScanBeforeGivingUp = settings_manager.General.SecondsToScanBeforeGivingUp;
        config.bUseUObjectArrayCache = settings_manager.General.UseUObjectArrayCache;

        // Retrieve from the config file the number of threads to be used for aob scanning
        {
            // The config system only directly supports signed 64-bit integers
            // I'm using '-1' for the default and then only proceeding with using the value from the config file if it's within the
            // range of an unsigned 32-bit integer (which is what the SinglePassScanner uses)
            // The variables for these settings are default initialized with valid values so no need to set them if the config value
            // was either missing or invalid
            int64_t num_threads_for_scanner_from_config = settings_manager.Threads.SigScannerNumThreads;

            // The scanner is expecting a uint32_t so lets make sure we can safely convert to a uint32_t
            if (num_threads_for_scanner_from_config <= std::numeric_limits<uint32_t>::max() && num_threads_for_scanner_from_config >= 1)
            {
                config.NumScanThreads = static_cast<uint32_t>(num_threads_for_scanner_from_config);
            }
        }

        {
            int64_t multithreading_module_size_threshold_from_config = settings_manager.Threads.SigScannerMultithreadingModuleSizeThreshold;

            if (multithreading_module_size_threshold_from_config <= std::numeric_limits<uint32_t>::max() &&
                multithreading_module_size_threshold_from_config >= std::numeric_limits<uint32_t>::min())
            {
                config.MultithreadingModuleSizeThreshold = static_cast<uint32_t>(multithreading_module_size_threshold_from_config);
            }
        }

        // Version override from ini file
        {
            int64_t major_version = settings_manager.EngineVersionOverride.MajorVersion;
            int64_t minor_version = settings_manager.EngineVersionOverride.MinorVersion;

            if (major_version != -1 && minor_version != -1)
            {
                // clang-format off
                if (major_version < std::numeric_limits<uint32_t>::min() ||
                    major_version > std::numeric_limits<uint32_t>::max() ||
                    minor_version < std::numeric_limits<uint32_t>::min() ||
                    minor_version > std::numeric_limits<uint32_t>::max())
                {
                    throw std::runtime_error{
                            "Was unable to override engine version from ini file; The number in the ini file must be in range of a uint32"};
                }
                // clang-format on

                Unreal::Version::Major = static_cast<uint32_t>(major_version);
                Unreal::Version::Minor = static_cast<uint32_t>(minor_version);

                config.ScanOverrides.version_finder = [&]([[maybe_unused]] auto&, Unreal::Signatures::ScanResult&) {};
            }
        }

        // If any Lua scripts are found, add overrides so that the Lua script can perform the aob scan instead of the Unreal API itself
        setup_lua_scan_overrides(m_working_directory, config);

#ifdef __linux__
        // On Linux, patternsleuth's ps_scan uses Windows-specific AOB patterns that will never match.
        // Provide scan overrides that use dlsym to find functions by symbol name instead.
        // Also set the engine version from settings or fall back to default.
        {
            // Use engine version from UE4SS-settings.ini [EngineVersionOverride] if specified,
            // otherwise default to UE5.1 (Palworld).
            if (settings_manager.EngineVersionOverride.MajorVersion > 0)
            {
                Unreal::Version::Major = static_cast<int32_t>(settings_manager.EngineVersionOverride.MajorVersion);
                Unreal::Version::Minor = static_cast<int32_t>(settings_manager.EngineVersionOverride.MinorVersion);
                UE4SS_DBG( "[UE4SS] Engine version from settings: %d.%d\n", (int)Unreal::Version::Major, (int)Unreal::Version::Minor);
            }
            else
            {
                Unreal::Version::Major = 5;
                Unreal::Version::Minor = 1;
                UE4SS_DBG( "[UE4SS] Engine version default (no override): %d.%d\n", (int)Unreal::Version::Major, (int)Unreal::Version::Minor);
            }
            config.ScanOverrides.version_finder = [&]([[maybe_unused]] auto&, Unreal::Signatures::ScanResult&) {};

            // Try to find functions via dlsym from the main executable.
            // Use RTLD_DEFAULT instead of dlopen(nullptr, ...) because a crashed dlopen
            // (e.g. from a C++ mod constructor) can leave dlopen's internal state corrupted,
            // making subsequent dlopen calls crash.
            auto try_resolve = [&](const char* symbol_name) -> void* {
                void* ptr = dlsym(RTLD_DEFAULT, symbol_name);
                if (ptr) return ptr;

                std::string prefixed = std::string("_") + symbol_name;
                ptr = dlsym(RTLD_DEFAULT, prefixed.c_str());
                return ptr;
            };

            // All overrides are non-fatal — the binary is likely stripped so dlsym won't find symbols.
            // The important thing is that ps_scan returns true (because all config flags are false)
            // so we don't get stuck in the scan retry loop.

            // Override GUObjectArray scan
                config.ScanOverrides.guobjectarray = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("GUObjectArray");
                    if (addr)
                    {
                        Unreal::UObjectArray::SetupGUObjectArrayAddress(addr);
                        scan_result.SuccessMessage.emplace_back(STR("GUObjectArray found via dlsym"));
                        return;
                    }

                    UE4SS_DBG( "[UE4SS] dlsym: GUObjectArray not found (stripped binary?), trying heuristic scan...\n");

                    struct SegmentInfo {
                        uint8_t* start;
                        size_t size;
                        bool writable;
                        bool executable;
                    };

                    // Collect segments only from the main executable (first dl_iterate_phdr entry
                    // with empty dlpi_name, or name matching the game binary), PLUS anonymous
                    // writable regions from /proc/self/maps. The live GUObjectArray is heap-
                    // allocated by the engine and lives in an anonymous mmap region that
                    // dl_iterate_phdr does not enumerate (it only reports file-backed PT_LOAD
                    // segments). Without scanning anonymous writable memory, the heuristic data
                    // scan cannot find the real GUObjectArray.
                    auto collect_main_exe_segments = []() -> std::vector<SegmentInfo> {
                        std::vector<SegmentInfo> segs;
                        std::string main_exe_path;
                        {
                            char buf[1024]{};
                            ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
                            if (len > 0) main_exe_path = std::string(buf, static_cast<size_t>(len));
                        }

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<SegmentInfo>*>(data);
                            const char* name = info->dlpi_name;
                            // Main executable has empty name or matches /proc/self/exe
                            bool is_main = (!name || name[0] == '\0');
                            if (!is_main) {
                                // Check if this shared library is the game binary itself
                                // (some systems report the exe path as the name)
                                std::string nm(name);
                                if (nm.find("PalServer-Linux-Shipping") != std::string::npos)
                                {
                                    is_main = true;
                                }
                            }
                            if (!is_main) return 0;
                            UE4SS_DBG("[UE4SS] collect_main_exe_segments: dlpi_name='%s', dlpi_addr=%p\n",
                                      name ? name : "(null)", (void*)info->dlpi_addr);

                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    bool writable = (phdr->p_flags & PF_W) != 0;
                                    bool executable = (phdr->p_flags & PF_X) != 0;
                                    if (seg_size > 0x100) {
                                        segs->push_back({seg_start, seg_size, writable, executable});
                                    }
                                }
                            }
                            return 0;
                        }, &segs);

                        // Also add anonymous writable regions from /proc/self/maps. These are
                        // heap/anon-mmap areas (no file backing) where the engine allocates
                        // runtime structures like GUObjectArray. dl_iterate_phdr misses these.
                        // Limit to a sane per-region size to avoid scanning enormous mappings.
                        {
                            FILE* maps = fopen("/proc/self/maps", "r");
                            if (maps) {
                                char line[512];
                                while (fgets(line, sizeof(line), maps)) {
                                    // Parse: start-end perms offset dev inode path
                                    uintptr_t start = 0, end = 0;
                                    char perms[8] = {};
                                    if (sscanf(line, "%lx-%lx %7s", &start, &end, perms) != 3) continue;
                                    // Must be writable and not executable
                                    if (!strchr(perms, 'w')) continue;
                                    if (strchr(perms, 'x')) continue;
                                    // Must be anonymous (no file path) — detect by the line having
                                    // no path after the inode field, or path is [heap]/[anon:...]
                                    bool has_path = false;
                                    const char* p = line;
                                    // Skip 5 whitespace-separated fields to reach the path field
                                    for (int f = 0; f < 5 && p; ++f) { p = strchr(p, ' '); if (p) ++p; }
                                    if (p) {
                                        while (*p == ' ') ++p;
                                        if (*p != '\0' && *p != '\n') has_path = true;
                                    }
                                    if (has_path) continue;
                                    size_t size = end - start;
                                    if (size <= 0x100 || size > (size_t)512 * 1024 * 1024) continue;
                                    segs.push_back({reinterpret_cast<uint8_t*>(start), size, true, false});
                                    UE4SS_DBG("[UE4SS] collect_main_exe_segments: added anonymous rw region %p-%p (%zu bytes)\n",
                                              (void*)start, (void*)end, size);
                                }
                                fclose(maps);
                            }
                        }
                        return segs;
                    };

                    // Real is_readable: parse /proc/self/maps once and cache
                    struct MapsRange { uintptr_t start; uintptr_t end; };
                    std::vector<MapsRange> g_maps_ranges;
                    auto load_maps = [&]() {
                        g_maps_ranges.clear();
                        FILE* f = fopen("/proc/self/maps", "r");
                        if (!f) return;
                        char line[512];
                        while (fgets(line, sizeof(line), f)) {
                            uintptr_t start, end;
                            if (sscanf(line, "%lx-%lx", &start, &end) == 2) {
                                g_maps_ranges.push_back({start, end});
                            }
                        }
                        fclose(f);
                    };
                    auto is_readable = [&](uintptr_t addr, size_t len) -> bool {
                        if (addr < 0x10000 || addr > 0x7fffffffffff) return false;
                        uintptr_t end = addr + len;
                        for (const auto& r : g_maps_ranges) {
                            if (addr >= r.start && end <= r.end) return true;
                        }
                        return false;
                    };

                    auto validate_fuobjectarray = [&](uint8_t* candidate) -> bool {
                        // Palworld uses the STOCK UE5.1 FUObjectArray layout (verified against
                        // the community PalworldModding/UsefulFiles MemberVariableLayout.ini).
                        // The layout (ABSOLUTE offsets from FUObjectArray base):
                        //   +0x00 ObjFirstGCIndex (int32)
                        //   +0x04 ObjLastNonGCIndex (int32)
                        //   +0x08 MaxObjectsNotConsideredByGC (int32)
                        //   +0x0C OpenForDisregardForGC (bool)
                        //   +0x10 ObjObjects: TUObjectArray sub-struct starts here.
                        //        Within TUObjectArray (relative to +0x10):
                        //          Objects ptr at +0x00 (abs +0x10)
                        //          PreAllocatedObjects at +0x08 (abs +0x18)
                        //          MaxElements at +0x10 (abs +0x20)
                        //          NumElements at +0x14 (abs +0x24)
                        //          MaxChunks at +0x18 (abs +0x28)
                        //          NumChunks at +0x1C (abs +0x2C)
                        // FUObjectItem total size is 0x18 (24 bytes).
                        int32_t obj_first_gc = *reinterpret_cast<int32_t*>(candidate + 0x00);
                        if (obj_first_gc < 0 || obj_first_gc > 1000000) return false;

                        int32_t obj_last_non_gc = *reinterpret_cast<int32_t*>(candidate + 0x04);
                        if (obj_last_non_gc < 0 || obj_last_non_gc > 1000000) return false;

                        int32_t max_not_gc = *reinterpret_cast<int32_t*>(candidate + 0x08);
                        if (max_not_gc < 0 || max_not_gc > 1000000) return false;

                        uint8_t open_disregard = *reinterpret_cast<uint8_t*>(candidate + 0x0C);
                        if (open_disregard > 1) return false;

                        // ObjObjects.Objects pointer (the chunk array ptr) at absolute +0x10
                        void* objects_ptr = *reinterpret_cast<void**>(candidate + 0x10);
                        if (objects_ptr == nullptr) return false;
                        if (!is_readable(reinterpret_cast<uintptr_t>(objects_ptr), 8)) return false;

                        // NumElements at absolute +0x24 (ObjObjects base 0x10 + TUObjectArray::NumElements 0x14)
                        int32_t num_elements = *reinterpret_cast<int32_t*>(candidate + 0x24);
                        if (num_elements < 1 || num_elements > 10000000) return false;

                        // MaxChunks at absolute +0x28
                        int32_t max_chunks = *reinterpret_cast<int32_t*>(candidate + 0x28);
                        if (max_chunks <= 0 || max_chunks > 10000) return false;

                        // NumChunks at absolute +0x2C
                        int32_t num_chunks = *reinterpret_cast<int32_t*>(candidate + 0x2C);
                        if (num_chunks < 0 || num_chunks > max_chunks) return false;
                        if (num_chunks == 0) return false;
                        // Note: num_chunks may be < max_chunks (the array grows). Don't require equality.

                        if (num_elements > static_cast<int64_t>(num_chunks) * 65536 + 65536) return false;

                        Unreal::FUObjectItem** chunks = *reinterpret_cast<Unreal::FUObjectItem***>(candidate + 0x10);
                        if (chunks == nullptr) return false;
                        if (!is_readable(reinterpret_cast<uintptr_t>(chunks), 8)) return false;

                        void* first_chunk = *reinterpret_cast<void* volatile*>(chunks);
                        if (first_chunk == nullptr) return false;
                        if (!is_readable(reinterpret_cast<uintptr_t>(first_chunk), 64)) return false;

                        // DEFINITIVE discriminator: the real GLOBAL GUObjectArray contains
                        // objects of HUNDREDS of distinct classes (diverse vtables), while
                        // false-positive per-class arrays (Palworld is heavily chunked-array
                        // based) contain objects of only 1-3 classes. Sample 256 FUObjectItems
                        // from chunk[0]; FUObjectItem size is 0x18 (24 bytes). Require both
                        // >= 50 distinct valid UObjects AND >= 10 distinct valid vtables.
                        constexpr int SAMPLE_COUNT = 256;
                        constexpr int ITEM_SIZE = 0x18; // Palworld FUObjectItem is 24 bytes (verified via runtime inspection)
                        if (!is_readable(reinterpret_cast<uintptr_t>(first_chunk), SAMPLE_COUNT * ITEM_SIZE)) return false;
                        std::set<uintptr_t> distinct_valid;
                        std::set<uintptr_t> distinct_vtables;
                        for (int si = 0; si < SAMPLE_COUNT; si++) {
                            void* obj = *reinterpret_cast<void* volatile*>(
                                reinterpret_cast<uint8_t*>(first_chunk) + si * ITEM_SIZE);
                            if (obj == nullptr) continue;
                            uintptr_t obj_addr = reinterpret_cast<uintptr_t>(obj);
                            if (obj_addr < 0x400000 || obj_addr > 0x7fffffffffff) continue;
                            if (!is_readable(obj_addr, 8)) continue;
                            void* vtable_ptr = *reinterpret_cast<void* volatile*>(obj);
                            uintptr_t vt_addr = reinterpret_cast<uintptr_t>(vtable_ptr);
                            if (vt_addr < 0x400000 || vt_addr > 0x7fffffffffff) continue;
                            if (!is_readable(vt_addr, 8)) continue;
                            distinct_valid.insert(obj_addr);
                            distinct_vtables.insert(vt_addr);
                        }
                        // The global GUObjectArray has 1000s of objects across hundreds of
                        // classes. Require >= 50 distinct objects AND >= 10 distinct vtables.
                        // Per-class false positives max out at a few vtables.
                        if (distinct_valid.size() < 50) return false;
                        if (distinct_vtables.size() < 10) return false;

                        return true;
                    };

                    // Deterministic AOB scan: find the engine's AddUObject code pattern.
                    // This is the unique instruction sequence that writes a new UObject into
                    // GUObjectArray. It reveals BOTH the Objects pointer location AND the
                    // FUObjectItem size. The pattern (verified via disassembly on Palworld
                    // v1.0.1) is:
                    //   48 8B 05 ?? ?? ?? ??    mov rax, [rip+disp32]   # load ObjObjects.Objects ptr
                    //   48 C1 E3 04             shl rbx, 4              # index * 16 (ITEM SIZE = 16)
                    //   4C 89 34 18             mov [rax+rbx], r14      # store UObject*
                    //   66 C7 44 18 08 02 00    mov word [rax+rbx+8], 2 # Flags
                    // The `mov rax, [rip+disp32]` target = GUObjectArray.ObjObjects.Objects,
                    // which is at FUObjectArray base + 0x10. So GUObjectArray base = target - 0x10.
                    // This is deterministic: no false positives (the full pattern is unique).
                    auto scan_code_refs = [&](std::vector<SegmentInfo>& segs) -> void* {
                        // Pattern bytes (7 + 3 + 3 + 7 = 20 bytes). The disp32 (4 bytes at offset 3)
                        // is a wildcard.
                        const uint8_t pat[] = {
                            0x48, 0x8B, 0x05, /*disp4 wild*/ 0,0,0,0,   // mov rax,[rip+disp32]
                            0x48, 0xC1, 0xE3, 0x04,                      // shl rbx, 4
                            0x4C, 0x89, 0x34, 0x18,                      // mov [rax+rbx],r14
                            0x66, 0xC7, 0x44, 0x18, 0x08, 0x02, 0x00     // mov word [rax+rbx+8],2
                        };
                        const size_t patlen = sizeof(pat);

                        for (const auto& seg : segs) {
                            if (!seg.executable) continue;
                            if (seg.size < patlen) continue;
                            for (size_t off = 0; off + patlen <= seg.size; off++) {
                                uint8_t* p = seg.start + off;
                                bool match = true;
                                for (size_t i = 0; i < patlen; i++) {
                                    // skip the 4 disp32 bytes (offset 3,4,5,6)
                                    if (i >= 3 && i <= 6) continue;
                                    if (p[i] != pat[i]) { match = false; break; }
                                }
                                if (!match) continue;
                                // Extract the rip-relative target of the `mov rax, [rip+disp32]`.
                                int32_t disp = *reinterpret_cast<int32_t*>(p + 3);
                                // next instruction (after the 7-byte mov) = p + 7
                                uintptr_t objects_field = reinterpret_cast<uintptr_t>(p + 7) + disp;
                                // objects_field = GUObjectArray + 0x10 (ObjObjects.Objects ptr)
                                uint8_t* candidate = reinterpret_cast<uint8_t*>(objects_field) - 0x10;
                                UE4SS_DBG("[UE4SS] AOB scan: AddUObject pattern at %p -> Objects@%p -> GUObjectArray base %p\n",
                                          p, (void*)objects_field, candidate);
                                // This is the DETERMINISTIC result: the AddUObject code pattern is
                                // unique to GUObjectArray access, so the address it references IS the
                                // real GUObjectArray. Return it directly (no heuristic validation —
                                // the validation rejects the real array because FUObjectItem layout
                                // assumptions don't match this build's in-memory state during boot).
                                // Sanity-check only: the Objects pointer must be a valid readable address.
                                void* objects_ptr = *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(objects_field));
                                if (objects_ptr != nullptr &&
                                    reinterpret_cast<uintptr_t>(objects_ptr) > 0x10000 &&
                                    reinterpret_cast<uintptr_t>(objects_ptr) < 0x7fffffffffff) {
                                    UE4SS_DBG("[UE4SS] AOB scan: GUObjectArray confirmed at %p (Objects ptr = %p)\n", candidate, objects_ptr);
                                    return reinterpret_cast<void*>(candidate);
                                }
                                UE4SS_DBG("[UE4SS] AOB scan: candidate at %p has invalid Objects ptr, continuing...\n", candidate);
                            }
                        }
                        return nullptr;
                    };

                    void* found_addr = nullptr;
                    constexpr int MAX_RETRIES = 60;
                    constexpr int RETRY_DELAY_MS = 500;

                    // Addresses that failed the liveness check on a previous attempt.
                    // Skipped on subsequent scans so we don't repeatedly re-test the
                    // same stale false-positive structs.
                    std::set<uintptr_t> rejected_addresses;

                    for (int attempt = 0; attempt < MAX_RETRIES && !found_addr; attempt++)
                    {
                        if (attempt > 0)
                        {
                            UE4SS_DBG( "[UE4SS] Heuristic scan: retry %d/%d (waiting %dms for engine to initialize GUObjectArray)...\n", attempt, MAX_RETRIES, RETRY_DELAY_MS);
                            std::this_thread::sleep_for(std::chrono::milliseconds(RETRY_DELAY_MS));
                        }

                        load_maps();
                        auto segments = collect_main_exe_segments();
                        if (attempt == 0)
                        {
                            UE4SS_DBG( "[UE4SS] Heuristic scan: found %zu segments in main executable\n", segments.size());
                        }

                        // Phase 1: Patternsleuth Linux patterns for GUObjectArray.
                        // On Linux PIE binaries, GUObjectArray (in BSS) is loaded as a 32-bit
                        // immediate via `MOV EDI, imm32` (opcode BF). The two patterns below
                        // are from the patternsleuth library (resolvers/unreal/guobject_array.rs)
                        // and independently identify the same address. This is deterministic:
                        // both patterns must agree.
                        if (!found_addr)
                        {
                            // Pattern 1: 41 39 EE 0F 8E [4 wild] BF [4 capture] 48 8B 74 24 10 E8 [4 wild] E9
                            // Pattern 2: 8B 6F [1 wild] 4C 89 F7 31 F6 E8 [4 wild] 41 39 EF 7E 0D BF [4 capture] 48 89 DE E8
                            const uint8_t p1_start[] = {0x41, 0x39, 0xEE, 0x0F, 0x8E};
                            const uint8_t p1_after[] = {0x48, 0x8B, 0x74, 0x24, 0x10, 0xE8};
                            const uint8_t p2_start[] = {0x8B, 0x6F};
                            const uint8_t p2_mid[] = {0x4C, 0x89, 0xF7, 0x31, 0xF6, 0xE8};
                            const uint8_t p2_after_capture[] = {0x41, 0x39, 0xEF, 0x7E, 0x0D, 0xBF};
                            const uint8_t p2_suffix[] = {0x48, 0x89, 0xDE, 0xE8};

                            std::set<uint32_t> candidates;
                            for (const auto& seg : segments)
                            {
                                if (!seg.executable || seg.size < 30) continue;
                                for (size_t off = 0; off + 30 <= seg.size; off++)
                                {
                                    uint8_t* p = seg.start + off;
                                    // Pattern 1
                                    if (off + 25 <= seg.size &&
                                        memcmp(p, p1_start, 5) == 0 &&
                                        p[9] == 0xBF &&
                                        memcmp(p + 14, p1_after, 6) == 0)
                                    {
                                        uint32_t imm = *reinterpret_cast<uint32_t*>(p + 10);
                                        if (imm >= 0x100000 && imm <= 0xc2e5000)
                                            candidates.insert(imm);
                                    }
                                    // Pattern 2
                                    if (off + 27 <= seg.size &&
                                        memcmp(p, p2_start, 2) == 0 &&
                                        memcmp(p + 3, p2_mid, 6) == 0 &&
                                        memcmp(p + 13, p2_after_capture, 6) == 0 &&
                                        memcmp(p + 23, p2_suffix, 4) == 0)
                                    {
                                        uint32_t imm = *reinterpret_cast<uint32_t*>(p + 19);
                                        if (imm >= 0x100000 && imm <= 0xc2e5000)
                                            candidates.insert(imm);
                                    }
                                }
                            }
                            if (candidates.size() == 1)
                            {
                                uint32_t addr = *candidates.begin();
                                UE4SS_DBG("[UE4SS] Patternsleuth Linux scan: GUObjectArray at 0x%x\n", addr);
                                found_addr = reinterpret_cast<void*>(addr);
                            }
                            else if (candidates.size() > 1)
                            {
                                UE4SS_DBG("[UE4SS] Patternsleuth Linux scan: %zu candidates, ambiguous\n", candidates.size());
                            }
                        }

                        // Phase 2: Data-based scan (fallback: scan writable segments directly)
                        if (!found_addr)
                        {
                            if (attempt == 0)
                            {
                                UE4SS_DBG( "[UE4SS] Heuristic scan: code scan found nothing, trying data scan...\n");
                            }
                            for (const auto& seg : segments)
                            {
                                if (!seg.writable) continue;
                                for (size_t offset = 0; offset + 0xB8 <= seg.size; offset += 8)
                                {
                                    uint8_t* candidate = seg.start + offset;
                                    if (validate_fuobjectarray(candidate))
                                    {
                                        // Skip addresses we already rejected via liveness check.
                                        uintptr_t candidate_key = reinterpret_cast<uintptr_t>(candidate);
                                        if (rejected_addresses.count(candidate_key))
                                        {
                                            continue;
                                        }
                                        // Liveness check: the live GUObjectArray grows continuously as the engine
                                        // runs. For candidates with a LOW count (< 1000), require monotonic
                                        // growth across 3 samples (the array is still bootstrapping). For
                                        // candidates with a HIGH count (>= 1000), the strict 50-distinct-
                                        // UObject validation already discriminates strongly, so we skip the
                                        // growth requirement (the count may be momentarily stable at idle)
                                        // and just re-validate to reject transient/overwritten structs.
                                        int32_t first_count = *reinterpret_cast<int32_t*>(candidate + 0x24);
                                        bool live = true;
                                        if (first_count < 1000)
                                        {
                                            UE4SS_DBG( "[UE4SS] Heuristic scan: candidate at %p (count=%d), running liveness check...\n", candidate, first_count);
                                            live = false;
                                            int32_t prev = first_count;
                                            for (int sample = 0; sample < 3; ++sample)
                                            {
                                                std::this_thread::sleep_for(std::chrono::milliseconds(400));
                                                int32_t cur = *reinterpret_cast<int32_t*>(candidate + 0x24);
                                                if (cur <= prev || cur < 1 || cur > 10000000)
                                                {
                                                    UE4SS_DBG( "[UE4SS] Heuristic scan: candidate at %p failed liveness at sample %d (prev=%d cur=%d)\n", candidate, sample, prev, cur);
                                                    live = false;
                                                    break;
                                                }
                                                prev = cur;
                                                live = true;
                                            }
                                            if (!live)
                                            {
                                                UE4SS_DBG( "[UE4SS] Heuristic scan: rejecting candidate at %p (not monotonically growing, not the live GUObjectArray)\n", candidate);
                                                rejected_addresses.insert(candidate_key);
                                                continue;
                                            }
                                            UE4SS_DBG( "[UE4SS] Heuristic scan: candidate at %p is live (elements grew %d -> %d monotonically)\n", candidate, first_count, prev);
                                        }
                                        // Final re-validation: transient BSS structs can pass the initial
                                        // validate_fuobjectarray but get overwritten by the time we re-check.
                                        if (!validate_fuobjectarray(candidate))
                                        {
                                            UE4SS_DBG( "[UE4SS] Heuristic scan: candidate at %p failed re-validation (transient/overwritten)\n", candidate);
                                            rejected_addresses.insert(candidate_key);
                                            continue;
                                        }
                                        UE4SS_DBG( "[UE4SS] Heuristic scan: accepting candidate at %p (count=%d, passed distinct-UObject validation)\n", candidate, first_count);
                                        found_addr = candidate;
                                        UE4SS_DBG( "[UE4SS] Heuristic scan: FUObjectArray candidate found at %p (segment offset 0x%zx, attempt %d)\n", found_addr, offset, attempt);
                                        break;
                                    }
                                }
                                if (found_addr) break;
                            }
                        }
                    }

                    if (found_addr)
                    {
                        Unreal::UObjectArray::SetupGUObjectArrayAddress(found_addr);
                        scan_result.SuccessMessage.emplace_back(STR("GUObjectArray found via heuristic memory scan"));
                        UE4SS_DBG( "[UE4SS] Heuristic scan: GUObjectArray resolved at %p\n", found_addr);
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] Heuristic scan: GUObjectArray not found after %d attempts\n", MAX_RETRIES);
                    }
                };

                // Override FName::ToString scan
                config.ScanOverrides.fname_to_string = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("FName::ToString");
                    if (!addr) addr = try_resolve("_ZN5FName8ToStringEv");
                    // Try const variant
                    if (!addr) addr = try_resolve("_ZNK5FName8ToStringEv");

                    // AOB-Scan fallback for FName::ToString
                    // FName::ToString on x86_64 typically:
                    //   48 8D 05 ?? ?? ?? ??    lea rax, [rip + offset]  (load FNameEntry or string buffer)
                    //   48 89 ??                mov [rsp+...], rax or similar
                    //   E8 ?? ?? ?? ??          call rel32 (to FString allocation or append)
                    // A simpler approach: search for the pattern that loads the FName comparison index
                    // and calls the name display function.
                    // Pattern: 8B 89 ?? ?? ?? ?? (mov ecx, [rcx+offset] to get ComparisonIndex)
                    // followed by E8 (call) — this is very characteristic of FName::ToString
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: FName::ToString not found, trying AOB scan...\n");

                        struct ExecSegment { uint8_t* start; size_t size; };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    if (seg_size > 0x1000) segs->push_back({seg_start, seg_size});
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        // Pattern: mov ecx, [rcx+0x00]; ... call rel32
                        // FName::ToString reads the ComparisonIndex from the FName (offset 0x00)
                        // 8B 89 00 00 00 00    mov ecx, [rcx+0x0]
                        // But more commonly it's:
                        // 89 88 00 00 00 00    mov [rax+0x0], ecx  (storing index)
                        // Or the function reads from the FName struct and calls FNameEntry::ToString
                        //
                        // Better pattern: look for the lea rax, [rip+?] followed by mov and call
                        // that's typical of ToString implementations.
                        // 48 8B 01              mov rax, [rcx]        (load ComparisonIndex or pointer)
                        // 48 8D 0D ?? ?? ?? ??  lea rcx, [rip+offset] (load FNameEntry table)
                        // E8 ?? ?? ?? ??        call rel32
                        const uint8_t pattern1[] = { 0x48, 0x8B, 0x01, 0x48, 0x8D, 0x0D };
                        const size_t pattern1_len = sizeof(pattern1);

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < pattern1_len + 32) continue;
                            for (size_t offset = 0; offset + pattern1_len + 16 <= seg.size; offset++)
                            {
                                if (memcmp(seg.start + offset, pattern1, pattern1_len) != 0) continue;

                                // Scan backwards for function start
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;
                                for (int back = 0; back < 64 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && candidate[1] == 0x81 && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    { func_start = candidate + 1; break; }
                                }
                                if (!func_start) func_start = pattern_pos;

                                // Validate call target if there's a call after the lea
                                // lea rcx, [rip+offset] is 7 bytes, check if E8 follows within 16 bytes
                                bool has_valid_call = false;
                                for (size_t c = pattern1_len; c < pattern1_len + 16 && offset + c + 5 <= seg.size; c++)
                                {
                                    if (pattern_pos[c] == 0xE8)
                                    {
                                        int32_t rel32 = *reinterpret_cast<int32_t*>(pattern_pos + c + 1);
                                        uint8_t* call_target = pattern_pos + c + 5 + rel32;
                                        uintptr_t call_target_addr = reinterpret_cast<uintptr_t>(call_target);
                                        if (call_target_addr >= 0x10000 && call_target_addr <= 0x7fffffffffff)
                                        {
                                            has_valid_call = true;
                                            break;
                                        }
                                    }
                                }
                                if (!has_valid_call) continue;

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: FName::ToString candidate at %p\n", found_func);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func) addr = found_func;
                        else
                        {
                            UE4SS_DBG("[UE4SS] AOB scan: FName::ToString not found. Using limited-mode fallback.\n");
                        }
                    }

                    if (addr)
                    {
                        Unreal::FName::ToStringInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("FName::ToString found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: FName::ToString not found (stripped binary?)\n");
                    }
                };

                // Override ProcessEvent scan — needed for hooking UObject::ProcessEvent
                // ProcessEvent is critical: all Blueprint function calls (give, tp, spawn, etc.) go through it
                // Signature: void(UObject* this, UFunction* Function, void* Parms)
                // rdi=this, rsi=Function, rdx=Parms
                config.ScanOverrides.process_event = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("UObject::ProcessEvent");
                    if (!addr) addr = try_resolve("_ZN6UObject12ProcessEventEP8UFunctionPv");
                    if (!addr) addr = try_resolve("ProcessEvent");

                    // AOB-Scan fallback for ProcessEvent
                    // Pattern: mov rbx, rdi; test rsi, rsi (48 89 FB 48 85 F6)
                    // This saves the this-pointer in rbx and null-checks the Function parameter.
                    // ProcessEvent always does this null-check early because it dereferences Function.
                    // Followed by a conditional jump (je/jz = 74 XX or 0F 84) for the null case.
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: ProcessEvent not found, trying AOB scan...\n");

                        struct ExecSegment { uint8_t* start; size_t size; };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    if (seg_size > 0x1000) segs->push_back({seg_start, seg_size});
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        // Pattern: mov rbx, rdi; test rsi, rsi (48 89 FB 48 85 F6)
                        // Followed by je (74 XX) or jz (0F 84 XX XX XX XX)
                        const uint8_t pattern[] = { 0x48, 0x89, 0xFB, 0x48, 0x85, 0xF6 };
                        const size_t pattern_len = sizeof(pattern);

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < pattern_len + 32) continue;
                            for (size_t offset = 0; offset + pattern_len + 16 <= seg.size; offset++)
                            {
                                if (memcmp(seg.start + offset, pattern, pattern_len) != 0) continue;

                                // Check for conditional jump after the test (null-check branch)
                                uint8_t* after_pattern = seg.start + offset + pattern_len;
                                bool has_cond_jump = false;
                                if (after_pattern[0] == 0x74 || after_pattern[0] == 0x75) has_cond_jump = true;
                                if (after_pattern[0] == 0x0F && (after_pattern[1] == 0x84 || after_pattern[1] == 0x85)) has_cond_jump = true;
                                if (!has_cond_jump) continue;

                                // Scan backwards for function start
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;
                                for (int back = 0; back < 64 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && candidate[1] == 0x81 && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && candidate[1] == 0x83 && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    { func_start = candidate + 1; break; }
                                }
                                if (!func_start) func_start = pattern_pos;

                                // Validate: look for another call instruction within 256 bytes (ProcessEvent calls sub-functions)
                                bool has_call = false;
                                for (size_t c = pattern_len; c < pattern_len + 256 && offset + c + 5 <= seg.size; c++)
                                {
                                    if (seg.start[offset + c] == 0xE8)
                                    {
                                        int32_t rel32 = *reinterpret_cast<int32_t*>(seg.start + offset + c + 1);
                                        uint8_t* call_target = seg.start + offset + c + 5 + rel32;
                                        uintptr_t call_target_addr = reinterpret_cast<uintptr_t>(call_target);
                                        if (call_target_addr >= 0x10000 && call_target_addr <= 0x7fffffffffff)
                                        { has_call = true; break; }
                                    }
                                }
                                if (!has_call) continue;

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: ProcessEvent candidate at %p\n", found_func);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func) addr = found_func;
                        else UE4SS_DBG("[UE4SS] AOB scan: ProcessEvent not found\n");
                    }

                    if (addr)
                    {
                        Unreal::UObject::ProcessEventInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("ProcessEvent found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: ProcessEvent not found (stripped binary?)\n");
                    }
                };

                // Override GameEngine::Tick scan
                config.ScanOverrides.gameengine_tick = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("UGameEngine::Tick");
                    if (!addr) addr = try_resolve("_ZN11UGameEngine4TickEfd");
                    if (addr)
                    {
                        Unreal::UEngine::TickInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("UGameEngine::Tick found via dlsym"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: UGameEngine::Tick not found (stripped binary?)\n");
                    }
                };

                // Override StaticConstructObject scan
                config.ScanOverrides.static_construct_object = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("StaticConstructObject_Internal");
                    if (!addr) addr = try_resolve("_ZL30StaticConstructObject_Internal");

                    // AOB-Scan fallback for StaticConstructObject_Internal
                    // Signature: (UClass* Class, UObject* InOuter, FName Name, EObjectFlags Flags, ...)
                    // rdi=Class, rsi=InOuter, rdx=Name, rcx=Flags
                    // Typical: large stack frame, saves rdi/rsi/rdx/rcx, calls multiple sub-functions
                    // Pattern: 48 89 54 24 ?? 48 89 4C 24 ??  (mov [rsp+disp8], rdx; mov [rsp+disp8], rcx)
                    // followed by 48 89 84 24 (mov [rsp+disp32], rax) or similar
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: StaticConstructObject not found, trying AOB scan...\n");

                        struct ExecSegment { uint8_t* start; size_t size; };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    if (seg_size > 0x1000) segs->push_back({seg_start, seg_size});
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        // Pattern: mov [rsp+disp8], rdx; mov [rsp+disp8], rcx (48 89 54 24 XX 48 89 4C 24)
                        const uint8_t pattern[] = { 0x48, 0x89, 0x54, 0x24 };
                        const size_t pattern_len = 4;

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < 128) continue;
                            for (size_t offset = 0; offset + 15 <= seg.size; offset++)
                            {
                                if (memcmp(seg.start + offset, pattern, pattern_len) != 0) continue;
                                // Check for mov [rsp+disp8], rcx at offset+5
                                if (memcmp(seg.start + offset + 5, "\x48\x89\x4C\x24", 4) != 0) continue;

                                // Scan backwards for function start
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;
                                for (int back = 0; back < 80 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && candidate[1] == 0x81 && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    { func_start = candidate + 1; break; }
                                }
                                if (!func_start) func_start = pattern_pos;

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: StaticConstructObject candidate at %p\n", found_func);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func) addr = found_func;
                        else UE4SS_DBG("[UE4SS] AOB scan: StaticConstructObject not found\n");
                    }

                    if (addr)
                    {
                        Unreal::UObjectGlobals::SetupStaticConstructObjectInternalAddress(addr);
                        scan_result.SuccessMessage.emplace_back(STR("StaticConstructObject found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: StaticConstructObject not found (stripped binary?)\n");
                    }
                };

                // Override FMemory::Free / GMalloc scan
                // GMalloc is a pointer-to-pointer (FMalloc**): a global variable in .data/.bss
                // that points to a single FMalloc* (the actual allocator instance).
                // Heuristic: find a writable pointer that points to another writable pointer
                // where the second pointer is in a writable segment (the FMalloc instance).
                config.ScanOverrides.fmemory_free = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("GMalloc");

                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: GMalloc not found, trying heuristic scan...\n");

                        struct WritableSeg { uint8_t* start; size_t size; };
                        std::vector<WritableSeg> writable_segments;

                        // Collect writable PT_LOAD segments from the main executable only.
                        // The main exe has dlpi_name="" (empty). Shared libraries have a path.
                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<WritableSeg>*>(data);
                            const char* name = info->dlpi_name;
                            // Skip shared libraries (only process main exe with empty name)
                            if (name && name[0] != '\0') return 0;
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type != PT_LOAD) continue;
                                if (!(phdr->p_flags & PF_W)) continue;
                                uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                size_t seg_size = phdr->p_memsz;
                                if (seg_size > 0x100) segs->push_back({seg_start, seg_size});
                            }
                            return 0;
                        }, &writable_segments);

                        // Also add the anonymous BSS region from /proc/self/maps.
                        // On Linux PIE, BSS is the zero-filled tail of the last PT_LOAD
                        // segment, but /proc/self/maps reports it as a separate anonymous
                        // region. This is where GMalloc lives.
                        {
                            FILE* maps = fopen("/proc/self/maps", "r");
                            if (maps) {
                                char line[512];
                                // Track the exe's last writable file-backed segment end.
                                // BSS starts immediately after it.
                                uintptr_t exe_data_end = 0;
                                // First pass: find the exe's data segment end
                                FILE* maps2 = fopen("/proc/self/maps", "r");
                                if (maps2) {
                                    char line2[512];
                                    while (fgets(line2, sizeof(line2), maps2)) {
                                        if (!strstr(line2, "PalServer")) continue;
                                        if (!strstr(line2, "rw-p")) continue;
                                        uintptr_t s, e;
                                        if (sscanf(line2, "%lx-%lx", &s, &e) == 2) {
                                            if (e > exe_data_end) exe_data_end = e;
                                        }
                                    }
                                    fclose(maps2);
                                }
                                // Second pass: add only the FIRST anonymous writable region
                                // after the exe's data segment (this is BSS)
                                rewind(maps);
                                while (fgets(line, sizeof(line), maps)) {
                                    if (strstr(line, "PalServer")) continue;
                                    uintptr_t start = 0, end = 0;
                                    char perms[8] = {};
                                    if (sscanf(line, "%lx-%lx %7s", &start, &end, perms) != 3) continue;
                                    if (!strchr(perms, 'w') || strchr(perms, 'x')) continue;
                                    // Only the first anonymous region after the exe data segment
                                    if (start < exe_data_end) continue;
                                    size_t size = end - start;
                                    if (size <= 0x100) continue;
                                    UE4SS_DBG("[UE4SS] GMalloc heuristic: BSS region 0x%lx-0x%lx (%zu bytes)\n", (unsigned long)start, (unsigned long)end, size);
                                    writable_segments.push_back({reinterpret_cast<uint8_t*>(start), size});
                                    break; // Only take the first one (BSS)
                                }
                                fclose(maps);
                            }
                        }

                        // Build a set of writable address ranges for validation
                        struct AddrRange { uintptr_t start; uintptr_t end; };
                        std::vector<AddrRange> writable_ranges;
                        for (const auto& seg : writable_segments)
                        {
                            writable_ranges.push_back({reinterpret_cast<uintptr_t>(seg.start),
                                                       reinterpret_cast<uintptr_t>(seg.start) + seg.size});
                        }

                        auto is_writable = [&writable_ranges](uintptr_t ptr) -> bool {
                            for (const auto& range : writable_ranges) {
                                if (ptr >= range.start && ptr < range.end) return true;
                            }
                            return false;
                        };

                        // GMalloc is FMalloc** — a pointer in .data/.bss pointing to a FMalloc*
                        // The FMalloc instance lives on the heap (or in .data/.bss).
                        // Its first field is a vtable pointer pointing into a read-only segment.
                        // The vtable's first few entries are function pointers in the text segment.
                        //
                        // Validation chain:
                        //   GMalloc (in writable seg) -> FMalloc* (anywhere)
                        //   -> *FMalloc (vtable ptr, in read-only seg)
                        //   -> vtable[2] (first real virtual function, in text segment, not a stub)
                        //
                        // We check vtable[2] because in the Itanium ABI, vtable[0] and [1]
                        // are destructors. The first real virtual function (Malloc or similar)
                        // is at index 2.
                        void* found_addr = nullptr;

                        // Build a comprehensive list of ALL readable segments
                        // (RO data, text, heap, BSS, mapped files) from /proc/self/maps.
                        // This is needed because the FMalloc instance lives on the heap
                        // (not in the main exe's segments).
                        struct AccessSeg { uintptr_t start; uintptr_t end; };
                        std::vector<AccessSeg> all_readable;
                        {
                            FILE* maps_all = fopen("/proc/self/maps", "r");
                            if (maps_all) {
                                char line3[512];
                                while (fgets(line3, sizeof(line3), maps_all)) {
                                    uintptr_t s, e;
                                    char perms[8] = {};
                                    if (sscanf(line3, "%lx-%lx %7s", &s, &e, perms) != 3) continue;
                                    if (!strchr(perms, 'r')) continue;
                                    all_readable.push_back({s, e});
                                }
                                fclose(maps_all);
                            }
                        }
                        auto is_accessible = [&all_readable](uintptr_t ptr) -> bool {
                            for (const auto& seg : all_readable) {
                                if (ptr >= seg.start && ptr < seg.end) return true;
                            }
                            return false;
                        };

                        // Scan BSS for the GMalloc (FMalloc**) chain:
                        //   GMalloc -> FMalloc* -> instance -> vtable
                        // We use the vtable no-op pattern (31 C0 C3 at vtable[2]) as a filter.
                        // Note: On Linux, UE4SS uses SystemMalloc for its own containers
                        // (see FMemory::Malloc), so the GMalloc pointer is only needed
                        // for the GMalloc null-check guard, not for actual allocation.
                        for (const auto& seg : writable_segments)
                        {
                            for (size_t offset = 0; offset + 8 <= seg.size; offset += 8)
                            {
                                uintptr_t first_ptr = *reinterpret_cast<uintptr_t*>(seg.start + offset);
                                if (first_ptr < 0x10000 || first_ptr > 0x7fffffffffff) continue;
                                if (!is_accessible(first_ptr)) continue;
                                uintptr_t instance = *reinterpret_cast<uintptr_t*>(first_ptr);
                                if (instance < 0x10000 || instance > 0x7fffffffffff) continue;
                                if (!is_accessible(instance)) continue;
                                uintptr_t vtable = *reinterpret_cast<uintptr_t*>(instance);
                                if (!is_accessible(vtable)) continue;
                                // Quick check: vtable[2] must be no-op (31 C0 C3)
                                uintptr_t fn2 = *reinterpret_cast<uintptr_t*>(vtable + 0x10);
                                if (!is_accessible(fn2)) continue;
                                uint8_t* fb2 = reinterpret_cast<uint8_t*>(fn2);
                                if (fb2[0] != 0x31 || fb2[1] != 0xC0 || fb2[2] != 0xC3) continue;
                                // vtable[3] must be a real function (not a stub)
                                uintptr_t fn3 = *reinterpret_cast<uintptr_t*>(vtable + 0x18);
                                if (!is_accessible(fn3)) continue;
                                uint8_t fb3 = *reinterpret_cast<uint8_t*>(fn3);
                                if (fb3 == 0xE9 || fb3 == 0xCC) continue;
                                found_addr = seg.start + offset;
                                UE4SS_DBG("[UE4SS] Heuristic scan: GMalloc at %p (instance %p, vtable %p)\n",
                                          found_addr, (void*)instance, (void*)vtable);
                                break;
                            }
                            if (found_addr) break;
                        }

                        if (found_addr) addr = found_addr;
                        else UE4SS_DBG("[UE4SS] Heuristic scan: GMalloc not found\n");
                    }

                    if (addr)
                    {
                        Unreal::GMalloc = std::bit_cast<Unreal::FMalloc**>(addr);
                        scan_result.SuccessMessage.emplace_back(STR("GMalloc found via dlsym/heuristic scan"));
#ifdef __linux__
                        // On Linux (Itanium ABI), the FMalloc vtable layout may differ
                        // from the UE4SS default. The default has Malloc at offset 0x10
                        // (vtable[2]), but Palworld's FMallocBinned2 has an extra slot,
                        // making Malloc at offset 0x18 (vtable[3]).
                        // Validate by checking if vtable[2] is a no-op (xor eax,eax; ret)
                        // and vtable[3] is a real function.
                        if (*Unreal::GMalloc)
                        {
                            // GMalloc is FMalloc**. Chain: *GMalloc -> FMalloc* -> instance.
                            // The instance's first field is the vtable.
                            uintptr_t fmalloc_ptr = reinterpret_cast<uintptr_t>(*Unreal::GMalloc);
                            uintptr_t fmalloc_obj = *reinterpret_cast<uintptr_t*>(fmalloc_ptr);
                            uintptr_t vtable = *reinterpret_cast<uintptr_t*>(fmalloc_obj);
                            // Check if vtable[2] (offset 0x10) is a no-op (xor eax,eax; ret = 31 C0 C3)
                            uintptr_t fn_0x10 = *reinterpret_cast<uintptr_t*>(vtable + 0x10);
                            uint8_t* fb = reinterpret_cast<uint8_t*>(fn_0x10);
                            if (fb && fb[0] == 0x31 && fb[1] == 0xC0 && fb[2] == 0xC3)
                            {
                                UE4SS_DBG("[UE4SS] FMalloc vtable: Malloc at 0x10 is no-op, shifting to 0x18\n");
                                Unreal::FMalloc::VTableLayoutMap[STR("Malloc")] = 0x18;
                                Unreal::FMalloc::VTableLayoutMap[STR("TryMalloc")] = 0x20;
                                Unreal::FMalloc::VTableLayoutMap[STR("Realloc")] = 0x28;
                                Unreal::FMalloc::VTableLayoutMap[STR("TryRealloc")] = 0x30;
                                Unreal::FMalloc::VTableLayoutMap[STR("Free")] = 0x38;
                                Unreal::FMalloc::VTableLayoutMap[STR("QuantizeSize")] = 0x40;
                                Unreal::FMalloc::VTableLayoutMap[STR("GetAllocationSize")] = 0x48;
                                Unreal::FMalloc::VTableLayoutMap[STR("Trim")] = 0x50;
                            }
                            else
                            {
                                UE4SS_DBG("[UE4SS] FMalloc vtable: Malloc at 0x10 is a real function (standard layout)\n");
                            }
                        }
#endif
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: GMalloc not found (stripped binary?)\n");
                    }
                };

                // Override FName constructor scan
                config.ScanOverrides.fname_constructor = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("FName::FName");
                    // Try default constructor (no params) — not the one we need but might be useful
                    if (!addr) addr = try_resolve("_ZN5FNameC1Ev");
                    // Try FName(const CharType*, EFindName) — the constructor we actually need
                    // char16_t* variant (UE5 uses CharType = char16_t on Linux)
                    if (!addr) addr = try_resolve("_ZN5FNameC1EPKDsRK10EFindName");
                    if (!addr) addr = try_resolve("_ZN5FNameC2EPKDsRK10EFindName");
                    // wchar_t* variant
                    if (!addr) addr = try_resolve("_ZN5FNameC1EPKwRK10EFindName");
                    if (!addr) addr = try_resolve("_ZN5FNameC2EPKwRK10EFindName");
                    // char8_t* variant (some UE versions)
                    if (!addr) addr = try_resolve("_ZN5FNameC1EPKhRK10EFindName");
                    if (!addr) addr = try_resolve("_ZN5FNameC2EPKhRK10EFindName");
                    // Without EFindName param
                    if (!addr) addr = try_resolve("_ZN5FNameC1EPKDs");
                    if (!addr) addr = try_resolve("_ZN5FNameC2EPKDs");
                    // C2 base constructor variants
                    if (!addr) addr = try_resolve("_ZN5FNameC2Ev");

                    // AOB-Scan fallback: search executable segments for FName constructor pattern
                    // The FName(const CharType*, EFindName) constructor on x86_64 UE5 typically:
                    //   1. Saves registers (push rbp; push rbx; sub rsp, ...)
                    //   2. Moves rsi (CharType*) to rdi or rdx for the string parameter
                    //   3. Calls FName::Init or FNameEntryLookup
                    // We search for the common pattern: mov rdi, rsi; mov esi, edx (or similar)
                    // followed by a call instruction within the first few bytes
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: FName::FName not found, trying AOB scan...\n");

                        struct ExecSegment {
                            uint8_t* start;
                            size_t size;
                        };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            // Scan all executable segments, but skip libraries with high addresses
                            // (only scan the main executable which has low addresses on non-PIE)
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    // Only scan segments in the low address range (main executable, non-PIE)
                                    // This filters out shared libraries which are loaded at high addresses
                                    if (seg_size > 0x1000 && reinterpret_cast<uintptr_t>(seg_start) < 0x100000000ULL) {
                                        segs->push_back({seg_start, seg_size});
                                    }
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        UE4SS_DBG("[UE4SS] AOB scan: %zu executable segments found for FName scan\n", exec_segments.size());
                        for (size_t i = 0; i < exec_segments.size(); i++) {
                            UE4SS_DBG("[UE4SS] AOB scan: seg %zu: start=%p, size=0x%zx\n", i, exec_segments[i].start, exec_segments[i].size);
                        }

                        // Pattern: FName(const CharType*, EFindName) with RVO on x86_64 UE5:
                        //   rdi = hidden return pointer (this/FName*), rsi = CharType*, rdx = EFindName&
                        //   The constructor saves CharType* (rsi) and passes EFindName (rdx) to a sub-call.
                        //   Common pattern: mov rbx, rsi; mov rdi, rdx; call <rel32>
                        //   Bytes: 48 89 F3 48 89 D7 E8
                        //
                        // The OLD pattern (48 89 FB 48 89 F7 E8 = mov rbx,rdi; mov rdi,rsi; call)
                        // matched a 2-arg FName accessor, NOT the constructor.
                        //
                        // We try multiple patterns since compiler optimizations may vary.

                        // Pattern 1: mov rbx, rsi; mov rdi, rdx; call (RVO constructor)
                        const uint8_t pattern1[] = { 0x48, 0x89, 0xF3, 0x48, 0x89, 0xD7, 0xE8 };
                        // Pattern 2: mov rbp, rsi; mov rdi, rdx; call (RVO with rbp)
                        const uint8_t pattern2[] = { 0x48, 0x89, 0xF5, 0x48, 0x89, 0xD7, 0xE8 };
                        // Pattern 3: mov rbx, rsi; mov rsi, rdx; call (pass EFindName as 2nd arg)
                        const uint8_t pattern3[] = { 0x48, 0x89, 0xF3, 0x48, 0x89, 0xD6, 0xE8 };
                        // Pattern 4: mov rdi, rsi; mov rsi, rdx; call (no save, direct pass)
                        const uint8_t pattern4[] = { 0x48, 0x89, 0xF7, 0x48, 0x89, 0xD6, 0xE8 };
                        // Pattern 5 (fallback): mov rbx, rdi; mov rdi, rsi; call (old pattern,
                        // may match accessor but better than nothing on stripped binaries)
                        const uint8_t pattern5[] = { 0x48, 0x89, 0xFB, 0x48, 0x89, 0xF7, 0xE8 };
                        // Pattern 6: mov rdi, rsi; mov rdx, rdx (nop); call — just mov rdi,rsi near a call
                        // Try: 49 89 F0 48 89 F7 E8 (mov r8, rsi; mov rdi, rsi; call) — uncommon but possible
                        const uint8_t pattern6[] = { 0x49, 0x89, 0xF0, 0x48, 0x89, 0xF7, 0xE8 };

                        struct AOBPattern { const uint8_t* bytes; size_t len; const char* name; };
                        AOBPattern patterns[] = {
                            { pattern1, sizeof(pattern1), "mov rbx,rsi; mov rdi,rdx; call" },
                            { pattern2, sizeof(pattern2), "mov rbp,rsi; mov rdi,rdx; call" },
                            { pattern3, sizeof(pattern3), "mov rbx,rsi; mov rsi,rdx; call" },
                            { pattern4, sizeof(pattern4), "mov rdi,rsi; mov rsi,rdx; call" },
                            { pattern5, sizeof(pattern5), "mov rbx,rdi; mov rdi,rsi; call (fallback)" },
                            { pattern6, sizeof(pattern6), "mov r8,rsi; mov rdi,rsi; call" },
                        };
                        // Look for this pattern a few bytes before the actual function start
                        // (after the prologue saves). We scan backwards from the pattern match
                        // to find the function entry point (typically a push rbp or sub rsp).

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < 16 + 64) continue;
                            for (size_t offset = 0; offset + 16 + 32 <= seg.size; offset++)
                            {
                                // Try each pattern
                                int matched_pattern = -1;
                                for (int p = 0; p < 6; p++)
                                {
                                    if (offset + patterns[p].len <= seg.size &&
                                        memcmp(seg.start + offset, patterns[p].bytes, patterns[p].len) == 0)
                                    {
                                        matched_pattern = p;
                                        break;
                                    }
                                }
                                if (matched_pattern < 0) continue;

                                size_t pat_len = patterns[matched_pattern].len;
                                UE4SS_DBG("[UE4SS] AOB scan: pattern '%s' matched at offset %zu (addr %p)\n",
                                          patterns[matched_pattern].name, offset, seg.start + offset);

                                // Found the pattern. Now scan backwards (up to 64 bytes) to find the function start.
                                // Function start is typically marked by:
                                //   - push rbp (0x55) at an aligned boundary
                                //   - sub rsp, imm32 (0x48 0x81 0xEC) at an aligned boundary
                                //   - int3 padding (0xCC) before the function
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;

                                for (int back = 0; back < 64 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    // Check for push rbp (0x55) at 16-byte aligned boundary
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    {
                                        func_start = candidate;
                                        break;
                                    }
                                    // Check for sub rsp, imm32 (0x48 0x81 0xEC) at 16-byte aligned boundary
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && candidate[1] == 0x81 && candidate[2] == 0xEC)
                                    {
                                        func_start = candidate;
                                        break;
                                    }
                                    // Check for int3 padding before function (0xCC followed by non-0xCC)
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    {
                                        func_start = candidate + 1;
                                        break;
                                    }
                                }

                                if (!func_start)
                                {
                                    // Use the pattern position itself as fallback
                                    func_start = pattern_pos;
                                }

                                // Validate: the call target (rel32 after E8) should point within an executable segment
                                // E8 is the last byte of the pattern, so rel32 starts at pattern_pos + pat_len
                                int32_t rel32 = *reinterpret_cast<int32_t*>(pattern_pos + pat_len);
                                uint8_t* call_target = pattern_pos + pat_len + 4 + rel32;
                                uintptr_t call_target_addr = reinterpret_cast<uintptr_t>(call_target);
                                if (call_target_addr < 0x10000 || call_target_addr > 0x7fffffffffff) {
                                    UE4SS_DBG("[UE4SS] AOB scan: call_target %p out of range (rel32=%d, pattern_pos=%p), skipping\n", (void*)call_target, rel32, (void*)pattern_pos);
                                    continue;
                                }

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: FName constructor candidate at %p (pattern: %s, offset %zu)\n", found_func, patterns[matched_pattern].name, offset);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func)
                        {
                            addr = found_func;
                        }
                        else
                        {
                            UE4SS_DBG("[UE4SS] AOB scan: FName constructor not found in executable segments\n");
                        }
                    }

                    if (addr)
                    {
                        Unreal::FName::ConstructorInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("FName::FName found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: FName::FName not found (stripped binary?)\n");
                    }
                };

                // Override GNatives scan
                // GNatives is a global array of function pointers (FNativeFuncPtr*),
                // NOT a function itself. It lives in .data/.bss (writable segment).
                // Each entry is a pointer to a native function in the executable segment.
                // Heuristic: find a contiguous array of at least 64 pointers where all point
                // into executable PT_LOAD segments.
                config.ScanOverrides.gnatives = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("GNatives");

                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: GNatives not found, trying heuristic scan...\n");

                        // Collect executable segment ranges for validation
                        struct ExecRange { uintptr_t start; uintptr_t end; };
                        std::vector<ExecRange> exec_ranges;

                        // Also collect writable segments for scanning
                        struct WritableSeg { uint8_t* start; size_t size; };
                        std::vector<WritableSeg> writable_segments;

                        struct ScanData {
                            std::vector<ExecRange>* exec_ranges;
                            std::vector<WritableSeg>* writable_segments;
                        };
                        ScanData scan_data{&exec_ranges, &writable_segments};

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* sd = static_cast<ScanData*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD) {
                                    uintptr_t seg_start = info->dlpi_addr + phdr->p_vaddr;
                                    uintptr_t seg_end = seg_start + phdr->p_memsz;
                                    if (phdr->p_flags & PF_X) {
                                        sd->exec_ranges->push_back({seg_start, seg_end});
                                    }
                                    if (phdr->p_flags & PF_W) {
                                        if (phdr->p_memsz > 0x100) {
                                            sd->writable_segments->push_back({reinterpret_cast<uint8_t*>(seg_start), phdr->p_memsz});
                                        }
                                    }
                                }
                            }
                            return 0;
                        }, &scan_data);

                        auto is_executable = [&exec_ranges](uintptr_t ptr) -> bool {
                            for (const auto& range : exec_ranges) {
                                if (ptr >= range.start && ptr < range.end) return true;
                            }
                            return false;
                        };

                        // Scan writable segments for a contiguous array of function pointers
                        // GNatives typically has 256+ entries, all pointing to executable code
                        // We look for at least 64 consecutive valid function pointers (8 bytes each)
                        const size_t MIN_ENTRIES = 64;
                        const size_t PTR_SIZE = 8;

                        void* found_addr = nullptr;
                        for (const auto& seg : writable_segments)
                        {
                            if (seg.size < MIN_ENTRIES * PTR_SIZE) continue;
                            size_t consecutive = 0;
                            size_t run_start = 0;

                            for (size_t offset = 0; offset + PTR_SIZE <= seg.size; offset += PTR_SIZE)
                            {
                                uintptr_t ptr_val = *reinterpret_cast<uintptr_t*>(seg.start + offset);
                                if (ptr_val >= 0x10000 && ptr_val <= 0x7fffffffffff && is_executable(ptr_val))
                                {
                                    if (consecutive == 0) run_start = offset;
                                    consecutive++;
                                    if (consecutive >= MIN_ENTRIES)
                                    {
                                        // Found a candidate — return the start of the run
                                        found_addr = seg.start + run_start;
                                        UE4SS_DBG("[UE4SS] Heuristic scan: GNatives candidate at %p (%zu consecutive entries)\n", found_addr, consecutive);
                                        break;
                                    }
                                }
                                else
                                {
                                    consecutive = 0;
                                }
                            }
                            if (found_addr) break;
                        }

                        if (found_addr)
                        {
                            addr = found_addr;
                        }
                        else
                        {
                            UE4SS_DBG("[UE4SS] Heuristic scan: GNatives not found in writable segments\n");
                        }
                    }

                    if (addr)
                    {
                        Unreal::GNatives_Internal = reinterpret_cast<Unreal::FNativeFuncPtr*>(addr);
                        scan_result.SuccessMessage.emplace_back(STR("GNatives found via dlsym/heuristic scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: GNatives not found (stripped binary?)\n");
                    }
                };

                // Override FUObjectHashTables::Get scan — try dlsym, non-fatal if not found
                config.ScanOverrides.fuobject_hash_tables_get = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("FUObjectHashTables::Get");
                    if (!addr) addr = try_resolve("GetObjectHashTables");
                    if (!addr) addr = try_resolve("FUObjectArray::GetObjectHashTables");
                    if (addr)
                    {
                        scan_result.SuccessMessage.emplace_back(STR("FUObjectHashTables::Get found via dlsym"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: FUObjectHashTables::Get not found (non-fatal, stripped binary?)\n");
                    }
                };

                // Override console manager singleton scan — try dlsym, non-fatal if not found
                config.ScanOverrides.console_manager_singleton = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("GConsoleManager");
                    if (!addr) addr = try_resolve("ConsoleManager");
                    if (addr)
                    {
                        scan_result.SuccessMessage.emplace_back(STR("ConsoleManager singleton found via dlsym"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: console_manager_singleton not found (non-fatal, stripped binary?)\n");
                    }
                };

                // Override ProcessInternal scan — needed for BP mod loading (BeginPlay hooks, function calls)
                config.ScanOverrides.process_internal = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("UObject::ProcessInternal");
                    if (!addr) addr = try_resolve("_ZN6UObject15ProcessInternalER5FFrameRPv");
                    if (!addr) addr = try_resolve("ProcessInternal");

                    // AOB-Scan fallback for ProcessInternal
                    // ProcessInternal(UObject* Context, FFrame& Stack, void* RESULT_DECL)
                    // x86_64 calling convention: rdi=Context, rsi=Stack, rdx=RESULT_DECL
                    // Typical prologue saves all three args and sets up a large stack frame:
                    //   55                          push rbp
                    //   41 54/55/56/57              push r12-r15
                    //   53                          push rbx
                    //   48 81 EC ?? ?? ?? ??        sub rsp, imm32 (large frame, usually 0x100+)
                    //   48 89 9C 24 ?? ?? ?? ??     mov [rsp+X], rbx (save Context)
                    //   48 89 B4 24 ?? ?? ?? ??     mov [rsp+X], rsi (save Stack)
                    //   48 89 94 24 ?? ?? ?? ??     mov [rsp+X], rdx (save RESULT_DECL)
                    //
                    // We search for the distinctive pattern of three consecutive
                    // "mov [rsp+disp32], reg" instructions with rdi/rsi/rdx as sources:
                    //   48 89 9C 24 (mov [rsp+disp32], rbx)  — but rbx may not be set yet
                    // More reliable: look for 48 89 94 24 (mov [rsp+disp32], rdx) near the start
                    // followed by 48 89 B4 24 (mov [rsp+disp32], rsi)
                    // Pattern: 48 89 94 24 ?? ?? ?? ?? 48 89 B4 24
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: ProcessInternal not found, trying AOB scan...\n");

                        struct ExecSegment { uint8_t* start; size_t size; };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    if (seg_size > 0x1000) segs->push_back({seg_start, seg_size});
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        // Pattern: mov [rsp+disp32], rdx; mov [rsp+disp32], rsi
                        // 48 89 94 24 XX XX XX XX 48 89 B4 24
                        const uint8_t pattern[] = { 0x48, 0x89, 0x94, 0x24 };
                        const size_t pattern_len = 4;
                        // After the 4-byte pattern + 4-byte displacement, we expect 48 89 B4 24
                        const size_t check_offset = 8; // 4 (pattern) + 4 (disp32) = 8

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < 128) continue;
                            for (size_t offset = 0; offset + check_offset + 4 <= seg.size; offset++)
                            {
                                if (memcmp(seg.start + offset, pattern, pattern_len) != 0) continue;
                                // Check if followed by mov [rsp+disp32], rsi (48 89 B4 24)
                                if (memcmp(seg.start + offset + check_offset, "\x48\x89\xB4\x24", 4) != 0) continue;

                                // Found the pattern. Scan backwards for function start.
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;
                                for (int back = 0; back < 80 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && candidate[1] == 0x81 && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    { func_start = candidate + 1; break; }
                                }
                                if (!func_start) func_start = pattern_pos;

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: ProcessInternal candidate at %p\n", found_func);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func) addr = found_func;
                        else UE4SS_DBG("[UE4SS] AOB scan: ProcessInternal not found\n");
                    }

                    if (addr)
                    {
                        Unreal::UObject::ProcessInternalInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("ProcessInternal found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: ProcessInternal not found (stripped binary?)\n");
                    }
                };

                // Override ProcessLocalScriptFunction scan — needed for BP mod loading
                config.ScanOverrides.process_local_script_function = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("UObject::ProcessLocalScriptFunction");
                    if (!addr) addr = try_resolve("_ZN6UObject26ProcessLocalScriptFunctionER5FFrameRPv");
                    if (!addr) addr = try_resolve("ProcessLocalScriptFunction");

                    // AOB-Scan fallback for ProcessLocalScriptFunction
                    // Same signature as ProcessInternal: (UObject* Context, FFrame& Stack, void* RESULT_DECL)
                    // rdi=Context, rsi=Stack, rdx=RESULT_DECL
                    // ProcessLocalScriptFunction typically has a shorter prologue and immediately
                    // calls ProcessInternal or a related function. It often starts with:
                    //   48 83 EC ??                sub rsp, imm8 (smaller frame)
                    //   48 89 54 24 ??             mov [rsp+X], rdx (save RESULT_DECL)
                    //   48 89 4C 24 ??             mov [rsp+X], rcx (save Context, but rcx not set yet?)
                    // Or with RSP-relative stores using SIB byte:
                    //   48 89 54 24 ??             mov [rsp+disp8], rdx
                    //   48 89 74 24 ??             mov [rsp+disp8], rsi
                    //   E8 ?? ?? ?? ??             call rel32 (to ProcessInternal or similar)
                    //
                    // Pattern: 48 89 54 24 ?? 48 89 74 24 ?? E8
                    // (mov [rsp+disp8], rdx; mov [rsp+disp8], rsi; call rel32)
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: ProcessLocalScriptFunction not found, trying AOB scan...\n");

                        struct ExecSegment { uint8_t* start; size_t size; };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    if (seg_size > 0x1000) segs->push_back({seg_start, seg_size});
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        // Pattern: mov [rsp+disp8], rdx; mov [rsp+disp8], rsi; call rel32
                        // 48 89 54 24 XX 48 89 74 24 XX E8
                        const uint8_t pattern[] = { 0x48, 0x89, 0x54, 0x24 };
                        const size_t pattern_len = 4;
                        // After pattern + 1 (disp8) = 5, then check for 48 89 74 24 at offset 5
                        // After that + 1 (disp8) = 10, then check for E8 at offset 10

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < 64) continue;
                            for (size_t offset = 0; offset + 15 <= seg.size; offset++)
                            {
                                if (memcmp(seg.start + offset, pattern, pattern_len) != 0) continue;
                                // Check for mov [rsp+disp8], rsi at offset+5
                                if (memcmp(seg.start + offset + 5, "\x48\x89\x74\x24", 4) != 0) continue;
                                // Check for call rel32 at offset+10
                                if (seg.start[offset + 10] != 0xE8) continue;

                                // Validate call target
                                int32_t rel32 = *reinterpret_cast<int32_t*>(seg.start + offset + 11);
                                uint8_t* call_target = seg.start + offset + 15 + rel32;
                                uintptr_t call_target_addr = reinterpret_cast<uintptr_t>(call_target);
                                if (call_target_addr < 0x10000 || call_target_addr > 0x7fffffffffff) continue;

                                // Scan backwards for function start
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;
                                for (int back = 0; back < 48 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && (candidate[1] == 0x81 || candidate[1] == 0x83) && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    { func_start = candidate + 1; break; }
                                }
                                if (!func_start) func_start = pattern_pos;

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: ProcessLocalScriptFunction candidate at %p\n", found_func);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func) addr = found_func;
                        else UE4SS_DBG("[UE4SS] AOB scan: ProcessLocalScriptFunction not found\n");
                    }

                    if (addr)
                    {
                        Unreal::UObject::ProcessLocalScriptFunctionInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("ProcessLocalScriptFunction found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: ProcessLocalScriptFunction not found (stripped binary?)\n");
                    }
                };

                // Override CallFunctionByNameWithArguments scan — needed for console commands and BP mod loading
                config.ScanOverrides.call_function_by_name_with_arguments = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult& scan_result) {
                    void* addr = try_resolve("UObject::CallFunctionByNameWithArguments");
                    if (!addr) addr = try_resolve("_ZN6UObject27CallFunctionByNameWithArgumentsEPKTRK18FOutputDeviceP6UObjectb");
                    if (!addr) addr = try_resolve("CallFunctionByNameWithArguments");

                    // AOB-Scan fallback for CallFunctionByNameWithArguments
                    // Signature: (const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCall)
                    // rdi=Str, rsi=Ar, rdx=Executor, rcx=bForceCall
                    // Typical prologue: save Str (rdi) to rbx, move Executor (rdx) to rdi for sub-call
                    //   48 89 FB          mov rbx, rdi    (save Str)
                    //   48 89 FA          mov rdx, rdi    (wrong direction?) 
                    // Actually: mov rbx, rdi; mov rdi, rdx (pass Executor as first arg)
                    //   48 89 FB 48 89 FA  — mov rbx, rdi; mov rdx, rdi (no, rdx->rdi)
                    // More likely: 48 89 FB 48 89 D7 — mov rbx, rdi; mov rdi, rdx
                    if (!addr)
                    {
                        UE4SS_DBG("[UE4SS] dlsym: CallFunctionByNameWithArguments not found, trying AOB scan...\n");

                        struct ExecSegment { uint8_t* start; size_t size; };
                        std::vector<ExecSegment> exec_segments;

                        dl_iterate_phdr([](struct dl_phdr_info* info, size_t, void* data) -> int {
                            auto* segs = static_cast<std::vector<ExecSegment>*>(data);
                            for (int i = 0; i < info->dlpi_phnum; i++) {
                                const ElfW(Phdr)* phdr = &info->dlpi_phdr[i];
                                if (phdr->p_type == PT_LOAD && (phdr->p_flags & PF_X)) {
                                    uint8_t* seg_start = reinterpret_cast<uint8_t*>(info->dlpi_addr + phdr->p_vaddr);
                                    size_t seg_size = phdr->p_memsz;
                                    if (seg_size > 0x1000) segs->push_back({seg_start, seg_size});
                                }
                            }
                            return 0;
                        }, &exec_segments);

                        // Pattern: mov rbx, rdi; mov rdi, rdx (48 89 FB 48 89 D7)
                        // This saves Str (rdi) in rbx and passes Executor (rdx) as first arg to a sub-call
                        const uint8_t pattern[] = { 0x48, 0x89, 0xFB, 0x48, 0x89, 0xD7 };
                        const size_t pattern_len = sizeof(pattern);

                        void* found_func = nullptr;
                        for (const auto& seg : exec_segments)
                        {
                            if (seg.size < pattern_len + 32) continue;
                            for (size_t offset = 0; offset + pattern_len + 16 <= seg.size; offset++)
                            {
                                if (memcmp(seg.start + offset, pattern, pattern_len) != 0) continue;

                                // Check for a call instruction within 16 bytes after the pattern
                                bool has_call = false;
                                for (size_t c = pattern_len; c < pattern_len + 16 && offset + c + 5 <= seg.size; c++)
                                {
                                    if (seg.start[offset + c] == 0xE8)
                                    {
                                        int32_t rel32 = *reinterpret_cast<int32_t*>(seg.start + offset + c + 1);
                                        uint8_t* call_target = seg.start + offset + c + 5 + rel32;
                                        uintptr_t call_target_addr = reinterpret_cast<uintptr_t>(call_target);
                                        if (call_target_addr >= 0x10000 && call_target_addr <= 0x7fffffffffff)
                                        { has_call = true; break; }
                                    }
                                }
                                if (!has_call) continue;

                                // Scan backwards for function start
                                uint8_t* pattern_pos = seg.start + offset;
                                uint8_t* func_start = nullptr;
                                for (int back = 0; back < 48 && pattern_pos - back > seg.start; back++)
                                {
                                    uint8_t* candidate = pattern_pos - back;
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) && *candidate == 0x55)
                                    { func_start = candidate; break; }
                                    if ((reinterpret_cast<uintptr_t>(candidate) % 16 == 0) &&
                                        candidate[0] == 0x48 && (candidate[1] == 0x81 || candidate[1] == 0x83) && candidate[2] == 0xEC)
                                    { func_start = candidate; break; }
                                    if (back > 0 && candidate[0] == 0xCC && candidate[1] != 0xCC)
                                    { func_start = candidate + 1; break; }
                                }
                                if (!func_start) func_start = pattern_pos;

                                found_func = func_start;
                                UE4SS_DBG("[UE4SS] AOB scan: CallFunctionByNameWithArguments candidate at %p\n", found_func);
                                break;
                            }
                            if (found_func) break;
                        }

                        if (found_func) addr = found_func;
                        else UE4SS_DBG("[UE4SS] AOB scan: CallFunctionByNameWithArguments not found\n");
                    }

                    if (addr)
                    {
                        Unreal::UObject::CallFunctionByNameWithArgumentsInternal.assign_address(addr);
                        scan_result.SuccessMessage.emplace_back(STR("CallFunctionByNameWithArguments found via dlsym/AOB scan"));
                    }
                    else
                    {
                        UE4SS_DBG( "[UE4SS] dlsym: CallFunctionByNameWithArguments not found (stripped binary?)\n");
                    }
                };

                // static_find_object: On Linux, StaticFindObject uses slow iteration via GUObjectArray
                // (no native StaticFindObjectFastInternal needed), so no override required.
                // This override is a no-op.
                config.ScanOverrides.static_find_object = [&](std::vector<SignatureContainer>&, Unreal::Signatures::ScanResult&) {
                    // No-op — StaticFindObject_InternalSlow iterates GUObjectArray directly
                };

                // Load manual address overrides from UE4SS_Addresses.ini (for stripped binaries)
                {
                    auto addresses_file = m_working_directory / STR("UE4SS_Addresses.ini");
                    if (std::filesystem::exists(addresses_file))
                    {
                        UE4SS_DBG( "[UE4SS] Loading manual address overrides from UE4SS_Addresses.ini\n");
                        try
                        {
                            auto file = File::open(ensure_str(addresses_file), File::OpenFor::Reading, File::OverwriteExistingFile::No, File::CreateIfNonExistent::No);
                            Ini::Parser parser;
                            parser.parse(file);

                            auto try_get_address = [&](const File::CharType* section_name, const File::CharType* key_name) -> void* {
                                try {
                                    const auto& val = parser.get_string(section_name, key_name);
                                    if (val.empty()) return nullptr;
                                    // Convert File::StringType (u16string on Linux) to std::string for parsing
                                    std::string addr_str;
                                    for (auto ch : val) { addr_str.push_back(static_cast<char>(ch)); }
                                    // Parse as hex address
                                    if (addr_str.starts_with("0x") || addr_str.starts_with("0X")) {
                                        addr_str = addr_str.substr(2);
                                    }
                                    uint64_t addr_val = std::stoull(addr_str, nullptr, 16);
                                    if (addr_val == 0) return nullptr;
                                    return std::bit_cast<void*>(addr_val);
                                } catch (...) {
                                    return nullptr;
                                }
                            };

                            // Apply manual overrides (these take priority over dlsym results)
                            if (void* addr = try_get_address(STR("Addresses"), STR("GUObjectArray")))
                            {
                                Unreal::UObjectArray::SetupGUObjectArrayAddress(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: GUObjectArray = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("FNameToString")))
                            {
                                Unreal::FName::ToStringInternal.assign_address(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: FNameToString = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("FNameConstructor")))
                            {
                                Unreal::FName::ConstructorInternal.assign_address(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: FNameConstructor = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("StaticConstructObject")))
                            {
                                Unreal::UObjectGlobals::SetupStaticConstructObjectInternalAddress(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: StaticConstructObject = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("GMalloc")))
                            {
                                Unreal::GMalloc = std::bit_cast<Unreal::FMalloc**>(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: GMalloc = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("GNatives")))
                            {
                                Unreal::GNatives_Internal = reinterpret_cast<Unreal::FNativeFuncPtr*>(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: GNatives = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("UGameEngineTick")))
                            {
                                Unreal::UEngine::TickInternal.assign_address(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: UGameEngineTick = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("ProcessInternal")))
                            {
                                Unreal::UObject::ProcessInternalInternal.assign_address(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: ProcessInternal = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("ProcessLocalScriptFunction")))
                            {
                                Unreal::UObject::ProcessLocalScriptFunctionInternal.assign_address(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: ProcessLocalScriptFunction = %p\n", addr);
                            }
                            if (void* addr = try_get_address(STR("Addresses"), STR("CallFunctionByNameWithArguments")))
                            {
                                Unreal::UObject::CallFunctionByNameWithArgumentsInternal.assign_address(addr);
                                UE4SS_DBG( "[UE4SS] Manual override: CallFunctionByNameWithArguments = %p\n", addr);
                            }
                        }
                        catch (const std::exception& e)
                        {
                            UE4SS_DBG( "[UE4SS] Error parsing UE4SS_Addresses.ini: %s\n", e.what());
                        }
                    }
                }

            UE4SS_DBG( "[UE4SS] Linux scan overrides configured (UE5.1, dlsym-based)\n");
        }
#endif

        // Virtual function offset overrides
        TRY([&]() {
            ProfilerScopeNamed("loading virtual function offset overrides");
            static File::StringType virtual_function_offset_override_file{ensure_str((m_working_directory / STR("VTableLayout.ini")))};
            if (std::filesystem::exists(virtual_function_offset_override_file))
            {
                auto file =
                        File::open(virtual_function_offset_override_file, File::OpenFor::Reading, File::OverwriteExistingFile::No, File::CreateIfNonExistent::No);
                Ini::Parser parser;
                parser.parse(file);

                Output::send<Color::Blue>(STR("Getting ordered lists from ini file\n"));

                auto calculate_virtual_function_offset = []<typename... BaseSizes>(uint32_t current_index, BaseSizes... base_sizes) -> uint32_t {
                    return current_index == 0 ? 0 : (current_index + (base_sizes + ...)) * 8;
                };

                auto retrieve_vtable_layout_from_ini = [&](const File::StringType& section_name, auto callable) -> uint32_t {
                    auto list = parser.get_ordered_list(section_name);
                    uint32_t vtable_size = list.size() - 1;
                    list.for_each([&](uint32_t index, File::StringType& item) {
                        callable(index, item);
                    });
                    return vtable_size;
                };

                Output::send<Color::Blue>(STR("UObjectBase\n"));
                uint32_t uobjectbase_size = retrieve_vtable_layout_from_ini(STR("UObjectBase"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, 0);
                    Output::send(STR("UObjectBase::{} = 0x{:X}\n"), item, offset);
                    Unreal::UObjectBase::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UObjectBaseUtility\n"));
                uint32_t uobjectbaseutility_size = retrieve_vtable_layout_from_ini(STR("UObjectBaseUtility"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size);
                    Output::send(STR("UObjectBaseUtility::{} = 0x{:X}\n"), item, offset);
                    Unreal::UObjectBaseUtility::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UObject\n"));
                uint32_t uobject_size = retrieve_vtable_layout_from_ini(STR("UObject"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size);
                    Output::send(STR("UObject::{} = 0x{:X}\n"), item, offset);
                    Unreal::UObject::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UField\n"));
                uint32_t ufield_size = retrieve_vtable_layout_from_ini(STR("UField"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size);
                    Output::send(STR("UField::{} = 0x{:X}\n"), item, offset);
                    Unreal::UField::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UEngine\n"));
                uint32_t uengine_size = retrieve_vtable_layout_from_ini(STR("UEngine"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size);
                    Output::send(STR("UEngine::{} = 0x{:X}\n"), item, offset);
                    Unreal::UEngine::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UScriptStruct::ICppStructOps\n"));
                retrieve_vtable_layout_from_ini(STR("UScriptStruct::ICppStructOps"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, 0);
                    Output::send(STR("UScriptStruct::ICppStructOps::{} = 0x{:X}\n"), item, offset);
                    Unreal::UScriptStruct::ICppStructOps::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("FField\n"));
                uint32_t ffield_size = retrieve_vtable_layout_from_ini(STR("FField"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, 0);
                    Output::send(STR("FField::{} = 0x{:X}\n"), item, offset);
                    Unreal::FField::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("FProperty\n"));
                uint32_t fproperty_size = retrieve_vtable_layout_from_ini(STR("FProperty"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset{};
                    if (Unreal::Version::IsBelow(4, 25))
                    {
                        offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size, ufield_size);
                    }
                    else
                    {
                        offset = calculate_virtual_function_offset(index, ffield_size);
                    }
                    Output::send(STR("FProperty::{} = 0x{:X}\n"), item, offset);
                    Unreal::FProperty::VTableLayoutMap.emplace(item, offset);
                });

                // If the engine version is <4.25 then the inheritance is different and we must take that into consideration.
                if (Unreal::Version::IsBelow(4, 25))
                {
                    fproperty_size = uobjectbase_size + uobjectbaseutility_size + uobject_size + ufield_size + fproperty_size;
                }
                else
                {
                    fproperty_size = ffield_size + fproperty_size;
                }

                Output::send<Color::Blue>(STR("FNumericProperty\n"));
                retrieve_vtable_layout_from_ini(STR("FNumericProperty"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, fproperty_size);
                    Output::send(STR("FNumericProperty::{} = 0x{:X}\n"), item, offset);
                    Unreal::FNumericProperty::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("FMulticastDelegateProperty\n"));
                retrieve_vtable_layout_from_ini(STR("FMulticastDelegateProperty"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, fproperty_size);
                    Output::send(STR("FMulticastDelegateProperty::{} = 0x{:X}\n"), item, offset);
                    Unreal::FMulticastDelegateProperty::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("FObjectPropertyBase\n"));
                retrieve_vtable_layout_from_ini(STR("FObjectPropertyBase"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, fproperty_size);
                    Output::send(STR("FObjectPropertyBase::{} = 0x{:X}\n"), item, offset);
                    Unreal::FObjectPropertyBase::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UStruct\n"));
                retrieve_vtable_layout_from_ini(STR("UStruct"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size, ufield_size);
                    Output::send(STR("UStruct::{} = 0x{:X}\n"), item, offset);
                    Unreal::UStruct::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("FOutputDevice\n"));
                retrieve_vtable_layout_from_ini(STR("FOutputDevice"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, 0);
                    Output::send(STR("FOutputDevice::{} = 0x{:X}\n"), item, offset);
                    Unreal::FOutputDevice::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("FMalloc\n"));
                retrieve_vtable_layout_from_ini(STR("FMalloc"), [&](uint32_t index, File::StringType& item) {
                    // We don't support FExec, so we're manually telling it the size.
                    static constexpr uint32_t fexec_size = 1;
                    uint32_t offset = calculate_virtual_function_offset(index, fexec_size);
                    Output::send(STR("FMalloc::{} = 0x{:X}\n"), item, offset);
                    Unreal::FMalloc::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("AActor\n"));
                uint32_t aactor_size = retrieve_vtable_layout_from_ini(STR("AActor"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size);
                    Output::send(STR("AActor::{} = 0x{:X}\n"), item, offset);
                    Unreal::AActor::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("AGameModeBase\n"));
                uint32_t agamemodebase_size = retrieve_vtable_layout_from_ini(STR("AGameModeBase"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size, aactor_size);
                    Output::send(STR("AGameModeBase::{} = 0x{:X}\n"), item, offset);
                    Unreal::AGameModeBase::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("AGameMode\n"));
                retrieve_vtable_layout_from_ini(STR("AGameMode"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index,
                                                                        Unreal::Version::IsAtLeast(4, 14)
                                                                        ? uobjectbase_size,
                                                                        uobjectbaseutility_size,
                                                                        uobject_size,
                                                                        aactor_size,
                                                                        agamemodebase_size
                                                                        : uobjectbase_size,
                                                                        uobjectbaseutility_size,
                                                                        uobject_size,
                                                                        aactor_size);
                    Output::send(STR("AGameMode::{} = 0x{:X}\n"), item, offset);
                    Unreal::AGameMode::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UPlayer\n"));
                uint32_t uplayer_size = retrieve_vtable_layout_from_ini(STR("UPlayer"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size);
                    Output::send(STR("UPlayer::{} = 0x{:X}\n"), item, offset);
                    Unreal::UPlayer::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("ULocalPlayer\n"));
                retrieve_vtable_layout_from_ini(STR("ULocalPlayer"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size, uplayer_size);
                    Output::send(STR("ULocalPlayer::{} = 0x{:X}\n"), item, offset);
                    Unreal::ULocalPlayer::VTableLayoutMap.emplace(item, offset);
                });

                Output::send<Color::Blue>(STR("UDataTable\n"));
                retrieve_vtable_layout_from_ini(STR("UDataTable"), [&](uint32_t index, File::StringType& item) {
                    uint32_t offset = calculate_virtual_function_offset(index, uobjectbase_size, uobjectbaseutility_size, uobject_size, uplayer_size);
                    Output::send(STR("UDataTable::{} = 0x{:X}\n"), item, offset);
                    Unreal::UDataTable::VTableLayoutMap.emplace(item, offset);
                });

                file.close();
            }
        });

        config.bHookProcessInternal = settings_manager.Hooks.HookProcessInternal;
        config.bHookProcessLocalScriptFunction = settings_manager.Hooks.HookProcessLocalScriptFunction;
        config.bHookLoadMap = settings_manager.Hooks.HookLoadMap;
        config.bHookInitGameState = settings_manager.Hooks.HookInitGameState;
        config.bHookCallFunctionByNameWithArguments = settings_manager.Hooks.HookCallFunctionByNameWithArguments;
        config.bHookBeginPlay = settings_manager.Hooks.HookBeginPlay;
        config.bHookEndPlay = settings_manager.Hooks.HookEndPlay;
        config.bHookLocalPlayerExec = settings_manager.Hooks.HookLocalPlayerExec;
        config.bHookAActorTick = settings_manager.Hooks.HookAActorTick;
        config.bHookEngineTick = settings_manager.Hooks.HookEngineTick;
        config.EngineTickResolveMethod = settings_manager.Hooks.EngineTickResolveMethod;
        config.bHookGameViewportClientTick = settings_manager.Hooks.HookGameViewportClientTick;
        config.bHookUObjectProcessEvent = settings_manager.Hooks.HookUObjectProcessEvent;
        config.bHookProcessConsoleExec = settings_manager.Hooks.HookProcessConsoleExec;
        config.bHookUStructLink = settings_manager.Hooks.HookUStructLink;
        config.FExecVTableOffsetInLocalPlayer = settings_manager.Hooks.FExecVTableOffsetInLocalPlayer;
        config.FNameToStringMethod = settings_manager.General.DefaultFNameToStringMethod;
        // Apply Debug Build setting from settings file only for now.
        Unreal::Version::DebugBuild = settings_manager.EngineVersionOverride.DebugBuild;
        Output::send<LogLevel::Warning>(STR("DebugGame Setting Enabled? {}\n"), Unreal::Version::DebugBuild);
        if (settings_manager.General.DoEarlyScan)
        {
            UE4SS_DBG( "[UE4SS] PreInitialize (early scan)...\n");
            Unreal::UnrealInitializer::PreInitialize(config);
            UE4SS_DBG( "[UE4SS] PreInitialize done. Scanning game...\n");
            try
            {
                Unreal::UnrealInitializer::ScanGame();
                UE4SS_DBG( "[UE4SS] ScanGame done.\n");
            }
            catch (std::runtime_error& e)
            {
                UE4SS_DBG( "[UE4SS] ScanGame error (non-fatal): %s\n", e.what());
            }
        }
        cpp_mods_done_loading.store(true);
        cpp_mods_done_loading.notify_one();
        // Continuous scanning, and finish initializing after the game thread is unlocked.
        UE4SS_DBG( "[UE4SS] Calling UnrealInitializer::Initialize()...\n");
        Unreal::UnrealInitializer::Initialize(config);
        UE4SS_DBG( "[UE4SS] UnrealInitializer::Initialize() done.\n");

#ifdef __linux__
        // On Linux, the engine tick hook is never installed by default (needs resolved
        // function addresses), so the RegisterEngineTickPreCallback lambda in on_program_start()
        // that loads Lua mods will never fire. Call the equivalent sequence directly here.
        UE4SS_DBG( "[UE4SS] Linux: loading mods directly (no engine tick hook)...\n");
        TRY([&] {
#ifdef HAS_INPUT
            m_input_handler.init();
            if (!settings_manager.General.InputSource.empty())
            {
                if (m_input_handler.set_input_source(to_string(settings_manager.General.InputSource)))
                {
                    UE4SS_DBG( "[UE4SS] Linux: input source set to: %s\n", m_input_handler.get_current_input_source().c_str());
                }
                else
                {
                    UE4SS_ERR( "[UE4SS] Linux: failed to set input source to: %s\n", to_string(settings_manager.General.InputSource).c_str());
                }
            }
#endif
            LuaMod::m_default_game_thread_method = settings_manager.General.DefaultExecuteInGameThreadMethod;

            UE4SS_DBG( "[UE4SS] Linux: calling install_lua_mods()...\n");
            install_lua_mods();
            UE4SS_DBG( "[UE4SS] Linux: install_lua_mods() done.\n");

            // LuaMod::on_program_start() and fire_program_start_for_cpp_mods() require resolved
            // UE function addresses (GUObjectArray, ProcessInternal, etc.) for hook registration
            // and the UObjectArray delete listener. Only call them if address resolution succeeded
            // (via dlsym on unstripped binaries or manual UE4SS_Addresses.ini overrides).
            if (Unreal::GUObjectArray && Unreal::UObjectArray::GetNumElements() >= 1000)
            {
                UE4SS_DBG( "[UE4SS] Linux: GUObjectArray resolved with %d elements, calling LuaMod::on_program_start() and fire_program_start_for_cpp_mods()...\n",
                          (int)Unreal::UObjectArray::GetNumElements());
                TRY([&] { LuaMod::on_program_start(); });
                TRY([&] { fire_program_start_for_cpp_mods(); });

                UE4SS_DBG( "[UE4SS] Linux: calling start_lua_mods()...\n");
                start_lua_mods();
                UE4SS_DBG( "[UE4SS] Linux: start_lua_mods() done.\n");
            }
            else
            {
                UE4SS_DBG( "[UE4SS] Linux: GUObjectArray has only %d elements (need >= 1000), starting Lua mods without hooks\n",
                          Unreal::GUObjectArray ? (int)Unreal::UObjectArray::GetNumElements() : -1);
                Output::send<LogLevel::Warning>(STR("Linux limited mode: GUObjectArray has only {} elements (need >= 1000). Starting Lua mods without UE hooks. Some mod features may not work.\n"),
                    Unreal::GUObjectArray ? Unreal::UObjectArray::GetNumElements() : 0);
                // Still try to start Lua mods — they may work partially without hooks
                UE4SS_DBG( "[UE4SS] Linux: calling start_lua_mods() (limited mode)...\n");
                TRY([&] { start_lua_mods(); });
                UE4SS_DBG( "[UE4SS] Linux: start_lua_mods() done (limited mode).\n");
            }

            // Skip ObjectDumper::init() in limited mode — it iterates GUObjectArray
            if (Unreal::GUObjectArray && Unreal::UObjectArray::GetNumElements() >= 1000)
            {
                ObjectDumper::init();
            }
            else
            {
                UE4SS_DBG( "[UE4SS] Linux: Skipping ObjectDumper::init() (limited mode)\n");
            }
            if (settings_manager.General.EnableHotReloadSystem)
            {
#ifdef HAS_INPUT
                register_keydown_event(settings_manager.General.HotReloadKey, {Input::ModifierKey::CONTROL}, [&]() {
                    TRY([&] {
                        queue_reinstall_mods();
                    });
                });
#endif
            }
            UE4SS_DBG( "[UE4SS] Linux: Mods loaded.\n");
        });
#endif

#ifdef __linux__
        if (!Unreal::GUObjectArray)
        {
            UE4SS_DBG("[UE4SS] Linux: GUObjectArray not resolved, skipping post-setup_unreal init (output_all_member_offsets, fire_unreal_init, setup_unreal_properties, event loop)\n");
            return;
        }
        if (Unreal::UObjectArray::GetNumElements() < 1000)
        {
            UE4SS_DBG("[UE4SS] Linux: GUObjectArray has only %d elements (need >= 1000), skipping post-setup_unreal init\n",
                      (int)Unreal::UObjectArray::GetNumElements());
            Output::send<LogLevel::Warning>(STR("Linux limited mode: GUObjectArray has only {} elements. Mod functionality will be limited.\n"),
                Unreal::UObjectArray::GetNumElements());
            // Start the event loop so the server keeps running
            UE4SS_DBG("[UE4SS] Linux: Starting event loop (limited mode)...\n");
            m_event_loop = std::jthread{&UE4SSProgram::update, this};
            m_event_loop.join();
            return;
        }
#endif

        output_all_member_offsets(IsCoalesced::Yes);

        bool can_create_custom_events{true};
        if (!UObject::ProcessLocalScriptFunctionInternal.is_ready() && Unreal::Version::IsAtLeast(4, 22))
        {
            can_create_custom_events = false;
            Output::send<LogLevel::Warning>(STR("ProcessLocalScriptFunction is not available, the following features will be unavailable:\n"));
        }
        else if (!UObject::ProcessInternalInternal.is_ready() && Unreal::Version::IsBelow(4, 22))
        {
            can_create_custom_events = false;
            Output::send<LogLevel::Warning>(STR("ProcessInternal is not available, the following features will be unavailable:\n"));
        }
        if (!can_create_custom_events)
        {
            Output::send<LogLevel::Warning>(STR("<Put function here responsible for creating custom UFunctions or events for BPs>\n"));
        }
        if (!Unreal::GNatives_Internal)
        {
            Output::send<LogLevel::Warning>(STR("GNatives not found, you will experience limited hooking functionality in certain scenarios.\n"));
        }
    }

    auto UE4SSProgram::share_lua_functions() -> void
    {
        m_shared_functions.set_script_variable_int32_function = &LuaLibrary::set_script_variable_int32;
        m_shared_functions.set_script_variable_default_data_function = &LuaLibrary::set_script_variable_default_data;
        m_shared_functions.call_script_function_function = &LuaLibrary::call_script_function;
        m_shared_functions.is_ue4ss_initialized_function = &LuaLibrary::is_ue4ss_initialized;
        Output::send(STR("m_shared_functions: {}\n"), static_cast<void*>(&m_shared_functions));
    }

#ifdef HAS_GUI
    static bool s_gui_initialized_for_game_thread{};
    static bool s_gui_initializing_for_game_thread{};
    auto gui_render_thread_tick() -> void
    {
        if (UE4SSProgram::settings_manager.Debug.RenderMode == GUI::RenderMode::ExternalThread)
        {
            return;
        }
        std::lock_guard guard(UE4SSProgram::get_program().m_render_thread_mutex);
        if (UE4SSProgram::get_program().get_debugging_ui().exit_requested())
        {
            UE4SSProgram::get_program().get_debugging_ui().uninitialize();
            s_gui_initialized_for_game_thread = false;
            return;
        }
        if (!UE4SSProgram::get_program().get_debugging_ui().is_open())
        {
            return;
        }
        if (!s_gui_initialized_for_game_thread)
        {
            GUI::gui_thread(std::nullopt, &UE4SSProgram::get_program().get_debugging_ui());
            s_gui_initialized_for_game_thread = true;
        }
        if (s_gui_initializing_for_game_thread)
        {
            s_gui_initializing_for_game_thread = false;
        }
        UE4SSProgram::get_program().get_debugging_ui().main_loop_internal();
    }
#endif

    auto UE4SSProgram::on_program_start() -> void
    {
        ProfilerScope();
        using namespace Unreal;

        // Commented out because this system (turn off hotkeys when in-game console is open) it doesn't work properly.
        /*
        UObjectArray::AddUObjectCreateListener(&FUEDeathListener::UEDeathListener);
        //*/

#ifdef HAS_GUI
        if (settings_manager.Debug.RenderMode == GUI::RenderMode::EngineTick)
        {
            Hook::RegisterEngineTickPostCallback([](auto&,...){gui_render_thread_tick(); }, {false, false, STR("UE4SS"), STR("ImGuiRenderHook")});
        }
        else if (settings_manager.Debug.RenderMode == GUI::RenderMode::GameViewportClientTick)
        {
            Hook::RegisterGameViewportClientTickPostCallback([](auto&,...){gui_render_thread_tick(); }, {false, false, STR("UE4SS"), STR("ImGuiRenderHook")});
        }
#endif

#ifdef HAS_GUI
        if (settings_manager.Debug.DebugConsoleEnabled)
        {
            if (settings_manager.General.UseUObjectArrayCache)
            {
                m_debugging_gui.get_live_view().set_listeners_allowed(true);
            }
            else
            {
                m_debugging_gui.get_live_view().set_listeners_allowed(false);
            }
            register_keydown_event(Input::Key::O, {Input::ModifierKey::CONTROL}, [&]() {
                TRY([&] {
                    std::lock_guard guard(m_render_thread_mutex);
                    if (s_gui_initializing_for_game_thread)
                    {
                        Output::send<LogLevel::Verbose>(STR("Cancelled GUI toggle during GUI initialization.\n"));
                        return;
                    }
                    auto was_gui_open = get_debugging_ui().is_open();
                    stop_render_thread();
                    if (!was_gui_open)
                    {
                        switch (settings_manager.Debug.RenderMode)
                        {
                        case GUI::RenderMode::ExternalThread:
                            m_render_thread = std::jthread{&GUI::gui_thread, &m_debugging_gui};
                            break;
                        case GUI::RenderMode::EngineTick:
                        case GUI::RenderMode::GameViewportClientTick:
                            // The hooked game function will pick up on the window being "open", and start rendering.
                            s_gui_initialized_for_game_thread = false;
                            s_gui_initializing_for_game_thread = true;
                            get_debugging_ui().set_open(true);
                            break;
                        }
                        fire_ui_init_for_cpp_mods();
                    }
                });
            });
        }
#endif

#ifdef TIME_FUNCTION_MACRO_ENABLED
        register_keydown_event(Input::Key::Y, {Input::ModifierKey::CONTROL}, [&]() {
            if (FunctionTimerFrame::s_timer_enabled)
            {
                FunctionTimerFrame::stop_profiling();
                FunctionTimerFrame::dump_profile();
                Output::send(STR("Profiler stopped & dumped\n"));
            }
            else
            {
                FunctionTimerFrame::start_profiling();
                Output::send(STR("Profiler started\n"));
            }
        });
#endif

        TRY([&] {
            ObjectDumper::init();
            if (settings_manager.General.EnableHotReloadSystem)
            {
                register_keydown_event(settings_manager.General.HotReloadKey, {Input::ModifierKey::CONTROL}, [&]() {
                    TRY([&] {
                        queue_reinstall_mods();
                    });
                });
            }
            if ((settings_manager.ObjectDumper.LoadAllAssetsBeforeDumpingObjects || settings_manager.CXXHeaderGenerator.LoadAllAssetsBeforeGeneratingCXXHeaders) &&
                Unreal::Version::IsBelow(4, 17))
            {
                Output::send<LogLevel::Warning>(
                        STR("FAssetData not available in <4.17, ignoring 'LoadAllAssetsBeforeDumpingObjects' & 'LoadAllAssetsBeforeGeneratingCXXHeaders'."));
            }
            else if (!bFAssetDataAvailable)
            {
                Output::send<LogLevel::Warning>(
                        STR("FAssetData not available, ignoring 'LoadAllAssetsBeforeDumpingObjects' & 'LoadAllAssetsBeforeGeneratingCXXHeaders'."));
            }

#ifdef HAS_INPUT
            m_input_handler.init();
            if (!settings_manager.General.InputSource.empty())
            {
                if (m_input_handler.set_input_source(to_string(settings_manager.General.InputSource)))
                {
                    Output::send(STR("Input source set to: {}\n"), to_generic_string(m_input_handler.get_current_input_source()));
                }
                else
                {
                    Output::send<LogLevel::Error>(STR("Failed to set input source to: {}\n"), settings_manager.General.InputSource);
                }
            }
#endif

            // Set default ExecuteInGameThread method from settings
            LuaMod::m_default_game_thread_method = settings_manager.General.DefaultExecuteInGameThreadMethod;

            install_lua_mods();
            LuaMod::on_program_start();
            fire_program_start_for_cpp_mods();
            start_lua_mods();
        });

        if (settings_manager.General.EnableDebugKeyBindings)
        {
            register_keydown_event(Input::Key::NUM_NINE, {Input::ModifierKey::CONTROL}, [&]() {
                generate_uht_compatible_headers();
            });
        }
    }

    auto UE4SSProgram::update() -> void
    {
        ProfilerSetThreadName("UE4SS-UpdateThread");
        m_event_loop_thread_id = std::this_thread::get_id();

#ifdef __linux__
        UE4SS_DBG( "[UE4SS] Linux: skipping on_program_start() (mods already loaded in init())\n");
        // Skip on_program_start() — it calls ObjectDumper::init(), registers engine tick hooks,
        // and re-calls install_lua_mods/LuaMod::on_program_start/start_lua_mods inside a
        // RegisterEngineTickPreCallback lambda. All of these require UE function addresses.
        // Mods were already loaded directly in init().
#else
        on_program_start();
#endif

        FilesystemWatcher filesystem_watcher{};
        if (settings_manager.General.EnableAutoReloadingLuaMods)
        {
            // Watch each mod's scripts/libs directory
            for (const auto& mod : m_mods)
            {
                if (dynamic_cast<CppMod*>(mod.get()))
                {
#ifdef __linux__
                    filesystem_watcher.add_dir(mod->get_path() / "libs");
#else
                    filesystem_watcher.add_dir(mod->get_path() / "dlls");
#endif
                }
                else if (dynamic_cast<LuaMod*>(mod.get()))
                {
                    auto* lua_mod = dynamic_cast<LuaMod*>(mod.get());
                    filesystem_watcher.add_dir(lua_mod->get_scripts_path());
                }
            }
            // Also watch the mods root directories for new mod folders
            for (const auto& mods_dir : m_mods_directories)
            {
                if (std::filesystem::exists(mods_dir))
                {
                    filesystem_watcher.add_dir(mods_dir);
                }
            }

            filesystem_watcher.start_async_polling([&](const std::filesystem::path& watched_dir, bool match_all) {
                ScopedThreadSynchronizer thread_synchronizer{filesystem_watcher.get_thread_state()};
                auto dir_name = watched_dir.filename().string();
                std::transform(dir_name.begin(), dir_name.end(), dir_name.begin(), ::tolower);

                // Check if this is a mods root directory (not a Scripts/libs folder)
                bool is_mods_root = false;
                for (const auto& mods_dir : m_mods_directories)
                {
                    if (watched_dir == mods_dir)
                    {
                        is_mods_root = true;
                        break;
                    }
                }

                if (is_mods_root)
                {
                    // A new mod directory was created in the mods root
                    // Scan for new mods and start them
                    Output::send(STR("Change detected in mods directory, scanning for new mods...\n"));
                    m_pause_events_processing = true;

                    // Remember existing mod names
                    std::vector<std::string> existing_mod_names;
                    for (const auto& mod : m_mods)
                    {
                        existing_mod_names.push_back(to_string(mod->get_name()));
                    }

                    // Scan for new mods
                    for (const auto& sub_directory : std::filesystem::directory_iterator(watched_dir))
                    {
                        if (!sub_directory.is_directory()) continue;

                        auto mod_name = sub_directory.path().stem().string();

                        // Skip if already loaded
                        bool already_exists = false;
                        for (const auto& existing_name : existing_mod_names)
                        {
                            if (existing_name == mod_name)
                            {
                                already_exists = true;
                                break;
                            }
                        }
                        if (already_exists) continue;

                        // Check if it's a Lua or C++ mod
#ifdef __linux__
                        auto has_scripts = [](const std::filesystem::path& p) -> bool {
                            for (const auto& e : std::filesystem::directory_iterator(p))
                            {
                                if (e.is_directory())
                                {
                                    auto n = e.path().filename().string();
                                    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
                                    if (n == "scripts") return true;
                                }
                            }
                            return false;
                        };
                        auto has_libs = [](const std::filesystem::path& p) -> bool {
                            for (const auto& e : std::filesystem::directory_iterator(p))
                            {
                                if (e.is_directory())
                                {
                                    auto n = e.path().filename().string();
                                    std::transform(n.begin(), n.end(), n.begin(), ::tolower);
                                    if (n == "libs") return true;
                                }
                            }
                            return false;
                        };
#else
                        auto has_scripts = [](const std::filesystem::path& p) -> bool {
                            return std::filesystem::exists(p / "Scripts");
                        };
                        auto has_libs = [](const std::filesystem::path& p) -> bool {
                            return std::filesystem::exists(p / "dlls");
                        };
#endif
                        if (has_scripts(sub_directory.path()))
                        {
                            Output::send(STR("New Lua mod detected: '{}', starting...\n"), ensure_str(mod_name));
                            auto new_mod = std::make_unique<LuaMod>(*this, ensure_str(mod_name), ensure_str(sub_directory.path().string()));
                            LuaMod* new_mod_ptr = new_mod.get();
                            m_mods.emplace_back(std::move(new_mod));
                            // Watch the new mod's scripts directory
                            filesystem_watcher.add_dir(new_mod_ptr->get_scripts_path());
                            new_mod_ptr->start_mod();
                        }
                        else if (has_libs(sub_directory.path()))
                        {
                            Output::send(STR("New C++ mod detected: '{}', starting...\n"), ensure_str(mod_name));
                            auto new_mod = std::make_unique<CppMod>(*this, ensure_str(mod_name), ensure_str(sub_directory.path().string()));
                            CppMod* new_mod_ptr = new_mod.get();
                            m_mods.emplace_back(std::move(new_mod));
#ifdef __linux__
                            filesystem_watcher.add_dir(new_mod_ptr->get_path() / "libs");
#else
                            filesystem_watcher.add_dir(new_mod_ptr->get_path() / "dlls");
#endif
                            new_mod_ptr->start_mod();
                        }
                    }
                    m_pause_events_processing = false;
                    return;
                }

                // It's a Scripts or libs directory change
                const auto mod_name = watched_dir.parent_path().filename();
#ifdef __linux__
                const auto is_cpp_mod = String::iequal(dir_name, "libs");
#else
                const auto is_cpp_mod = String::iequal(dir_name, "dlls");
#endif
                if (is_cpp_mod)
                {
                    auto staged_file = watched_dir / mod_name;
#ifdef __linux__
                    staged_file.replace_extension(".so");
#else
                    staged_file.replace_extension(".dll");
#endif
                    if (!std::filesystem::exists(staged_file))
                    {
                        return;
                    }
                    // TODO: Unload the library (uninstall).
                    //       Delete 'main.so'/'main.dll'.
                    //       Rename 'staged_file' to 'main.so'/'main.dll'.
                    //       Load 'main.so'/'main.dll' (install & start).

                    // TODO: To reload C++ mods, we need to add a way to unregister hooks, and then C++ mods need to unregister on they get notified that they're getting unloaded.
                    //       For Lua mods, there's no notification, but we track all the hooks internally, so we can unregister automatically, we just need to
                    //       call Lua::Uninstall, and We must also remove the keybinds like we do in UE4SSProgram::reinstall_mods.
                    //       Unsure about loading and starting mods again.
                }
                else
                {
                    // Lua mod file change — reload the mod
                    auto mod = find_lua_mod_by_name(ensure_str(mod_name), IsInstalled::Yes, IsStarted::Yes);
                    if (!mod)
                    {
                        return;
                    }
                    m_pause_events_processing = true;
                    mod->uninstall();
                    auto& mod_ref = *std::ranges::find_if(m_mods, [&](const std::unique_ptr<Mod>& mod_ptr) {
                        return mod_ptr.get() == mod;
                    });
                    if (!mod_ref)
                    {
                        return;
                    }
                    mod_ref = std::make_unique<LuaMod>(*this, StringType{mod_ref->get_name()}, ensure_str(mod_ref->get_path().string()));
                    m_pause_events_processing = false;
                    Output::send(STR("Auto-reloading Lua mod '{}'\n"), mod_ref->get_name());
                    mod_ref->start_mod();
                }
            });
        }

        Output::send(STR("Event loop start\n"));
        for (m_processing_events = true; m_processing_events;)
        {
            if (m_pause_events_processing || UE4SSProgram::unreal_is_shutting_down)
            {
                continue;
            }

            if (!is_queue_empty())
            {
                ProfilerScopeNamed("event processing");

                static constexpr size_t max_events_executed_per_frame = 5;
                size_t num_events_executed{};
                std::lock_guard<std::mutex> guard(m_event_queue_mutex);
                m_queued_events.erase(std::remove_if(m_queued_events.begin(),
                                                     m_queued_events.end(),
                                                     [&](EventCallable& event) -> bool {
                                                         if (num_events_executed >= max_events_executed_per_frame)
                                                         {
                                                             return false;
                                                         }
                                                         ++num_events_executed;
                                                         event();
                                                         return true;
                                                     }),
                                      m_queued_events.end());
            }

            // Commented out because this system (turn off hotkeys when in-game console is open) it doesn't work properly.
            /*
            auto* player_controller = get_player_controller();
            if (player_controller)
            {
                auto** player = player_controller->GetValuePtrByPropertyName<UObject*>(STR("Player"));
                if (player && *player)
                {
                    auto** viewportclient = (*player)->GetValuePtrByPropertyName<UObject*>(STR("ViewportClient"));
                    if (viewportclient && *viewportclient)
                    {
                        auto** console = (*viewportclient)->GetValuePtrByPropertyName<UObject*>(STR("ViewportConsole"));
                        if (console && *console)
                        {
                            auto* console_state = std::bit_cast<FName*>(static_cast<uint8_t*>((*console)->GetValuePtrByPropertyNameInChain(STR("HistoryBuffer"))) + 0x70);
                            m_input_handler.set_allow_input(console_state && *console_state == Unreal::NAME_None);
                        }
                    }
                }
            }
            //*/
#ifdef HAS_INPUT
            m_input_handler.process_event();
#endif
            {
                ProfilerScopeNamed("mod update processing");

                for (auto& mod : m_mods)
                {
                    if (mod->is_started())
                    {
                        mod->fire_update();
                    }
                }
            }

            if (settings_manager.General.EnableAutoReloadingLuaMods)
            {
                // Process any mod file changes, and wait until done.
                process_sync_request(filesystem_watcher.get_thread_state());
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            ProfilerFrameMark();
        }
        Output::send(STR("Event loop end\n"));
    }

    auto UE4SSProgram::setup_unreal_properties() -> void
    {
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("ObjectProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_objectproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("ClassProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_classproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("Int8Property"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_int8property);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("Int16Property"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_int16property);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("IntProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_intproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("Int64Property"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_int64property);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("ByteProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_byteproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("UInt16Property"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_uint16property);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("UInt32Property"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_uint32property);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("UInt64Property"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_uint64property);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("StructProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_structproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("ArrayProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_arrayproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("SetProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_setproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("MapProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_mapproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("FloatProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_floatproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("DoubleProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_doubleproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("BoolProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_boolproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("EnumProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_enumproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("WeakObjectProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_weakobjectproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("NameProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_nameproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("TextProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_textproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("StrProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_strproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("SoftObjectProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_softobjectproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("SoftClassProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_softobjectproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("InterfaceProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_interfaceproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("DelegateProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_delegateproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("MulticastDelegateProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_multicastdelegateproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("MulticastInlineDelegateProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_multicastdelegateproperty);
        LuaType::StaticState::m_property_value_pushers.emplace(FName(STR("MulticastSparseDelegateProperty"), Unreal::FNAME_Find).GetComparisonIndex(), &LuaType::push_multicastsparsedelegateproperty);
    }

    auto UE4SSProgram::setup_mods() -> void
    {
        ProfilerScope();

        Output::send(STR("Setting up mods...\n"));

        for (const auto& mods_directory : std::ranges::reverse_view(m_mods_directories))
        {
            if (!std::filesystem::exists(mods_directory))
            {
                Output::send<LogLevel::Warning>(STR("Mods directory doesn't exist, skipping: {}\n"), ensure_str(mods_directory));
                continue;
            }

            Output::send(STR("Loading mods from: {}\n"), ensure_str(mods_directory));

            for (const auto& sub_directory : std::filesystem::directory_iterator(mods_directory))
            {
                std::error_code ec;

                // Ignore all non-directories
                if (!sub_directory.is_directory())
                {
                    continue;
                }
                if (ec.value() != 0)
                {
                    set_error("is_directory ran into error %d", ec.value());
                }

                StringType directory_lowercase = ensure_str(sub_directory.path().stem());
                std::transform(directory_lowercase.begin(), directory_lowercase.end(), directory_lowercase.begin(), std::towlower);

                if (directory_lowercase == STR("shared"))
                {
                    // Do stuff when shared libraries have been implemented
                }
                else
                {
                    auto mod_name = ensure_str(sub_directory.path().stem());
#ifdef __linux__
                    auto has_scripts_dir = [](const std::filesystem::path& mod_path) -> bool {
                        for (const auto& entry : std::filesystem::directory_iterator(mod_path))
                        {
                            if (entry.is_directory())
                            {
                                auto name = entry.path().filename().string();
                                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                                if (name == "scripts") return true;
                            }
                        }
                        return false;
                    };
                    auto has_libs_dir = [](const std::filesystem::path& mod_path) -> bool {
                        for (const auto& entry : std::filesystem::directory_iterator(mod_path))
                        {
                            if (entry.is_directory())
                            {
                                auto name = entry.path().filename().string();
                                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                                if (name == "libs") return true;
                            }
                        }
                        return false;
                    };
                    bool is_lua_mod = has_scripts_dir(sub_directory.path());
                    bool is_cpp_mod = has_libs_dir(sub_directory.path());
                    Output::send(STR("Found mod directory: {} (Lua: {}, C++: {})\n"), ensure_str(mod_name), is_lua_mod ? STR("yes") : STR("no"), is_cpp_mod ? STR("yes") : STR("no"));
#else
                    bool is_lua_mod = std::filesystem::exists(sub_directory.path() / "Scripts");
                    bool is_cpp_mod = std::filesystem::exists(sub_directory.path() / "dlls");
#endif
                    // Create the mod but don't install it yet
                    if (!find_mod_by_name<LuaMod>(mod_name) && is_lua_mod)
                        m_mods.emplace_back(std::make_unique<LuaMod>(*this, std::move(mod_name), ensure_str(sub_directory.path())));
                    if (!find_mod_by_name<CppMod>(mod_name) && is_cpp_mod)
                    {
#ifdef __linux__
                        StringType saved_mod_name = mod_name;
                        auto saved_mod_path = ensure_str(sub_directory.path());
                        bool ok = ue4ss_with_crash_recovery([&]() {
                            m_mods.emplace_back(std::make_unique<CppMod>(*this, std::move(saved_mod_name), std::move(saved_mod_path)));
                        });
                        if (!ok)
                        {
                            Output::send<LogLevel::Warning>(STR("C++ mod '{}' crashed during construction (dlopen), skipping.\n"), ensure_str(mod_name));
                        }
#else
                        m_mods.emplace_back(std::make_unique<CppMod>(*this, std::move(mod_name), ensure_str(sub_directory.path())));
#endif
                    }
                }
            }
        }
    }

    template <typename ModType>
    auto install_mods(std::vector<std::unique_ptr<Mod>>& mods) -> void
    {
        ProfilerScope();

        for (auto& mod : mods)
        {
            if (!dynamic_cast<ModType*>(mod.get()))
            {
                continue;
            }

            bool mod_name_is_taken = std::find_if(mods.begin(), mods.end(), [&](auto& elem) {
                                         return elem->get_name() == mod->get_name();
                                     }) == mods.end();

            if (mod_name_is_taken)
            {
                mod->set_installable(false);
                Output::send<LogLevel::Warning>(STR("Mod name '{}' is already in use.\n"), mod->get_name());
                continue;
            }

            if (mod->is_installed())
            {
                Output::send<LogLevel::Warning>(STR("Tried to install a mod that was already installed, Mod: '{}'\n"), mod->get_name());
                continue;
            }

            if (!mod->is_installable())
            {
                Output::send<LogLevel::Warning>(STR("Was unable to install mod '{}' for unknown reasons. Mod is not installable.\n"), mod->get_name());
                continue;
            }

            mod->set_installed(true);
        }
    }

    auto UE4SSProgram::install_cpp_mods() -> void
    {
        install_mods<CppMod>(get_program().m_mods);
    }

    auto UE4SSProgram::install_lua_mods() -> void
    {
        install_mods<LuaMod>(get_program().m_mods);
    }

    auto UE4SSProgram::fire_unreal_init_for_cpp_mods() -> void
    {
        ProfilerScope();
        for (const auto& mod : m_mods)
        {
            if (!dynamic_cast<CppMod*>(mod.get()))
            {
                continue;
            }
            mod->fire_unreal_init();
        }
    }

#ifdef HAS_GUI
    auto UE4SSProgram::fire_ui_init_for_cpp_mods() -> void
    {
        ProfilerScope();
        for (const auto& mod : m_mods)
        {
            if (!dynamic_cast<CppMod*>(mod.get()))
            {
                continue;
            }
            mod->fire_ui_init();
        }
    }
#endif

    auto UE4SSProgram::fire_program_start_for_cpp_mods() -> void
    {
        ProfilerScope();
        for (const auto& mod : m_mods)
        {
            if (!dynamic_cast<CppMod*>(mod.get()))
            {
                continue;
            }
            mod->fire_program_start();
        }
    }

    auto UE4SSProgram::fire_lib_load_for_cpp_mods(StringViewType lib_name) -> void
    {
        for (const auto& mod : m_mods)
        {
            if (auto cpp_mod = dynamic_cast<CppMod*>(mod.get()); cpp_mod)
            {
                cpp_mod->fire_lib_load(lib_name);
            }
        }
    }

    auto UE4SSProgram::fire_on_cpp_mods_loaded_for_cpp_mods() -> void
    {
        for (const auto& mod : m_mods)
        {
            if (auto cpp_mod = dynamic_cast<CppMod*>(mod.get()); cpp_mod)
            {
                cpp_mod->fire_on_cpp_mods_loaded();
            }
        }
    }

    auto UE4SSProgram::unregister_keydown_events_for_lua_mod(LuaMod* mod, AllMods all_mods) -> void
    {
#ifdef HAS_INPUT
        m_input_handler.get_events_safe([&](auto& key_set) {
            std::erase_if(key_set.key_data, [&](auto& item) -> bool {
                auto& [_, key_data] = item;
                std::erase_if(key_data, [&](Input::KeyData& key_data) -> bool {
                    // custom_data == 1: Bind came from Lua, and custom_data2 is a pointer to LuaMod.
                    // custom_data == 2: Bind came from C++, and custom_data2 is a pointer to KeyDownEventData. Must free it.
                    return key_data.custom_data == 1 && (all_mods == AllMods::Yes || static_cast<LuaMod*>(key_data.custom_data2) == mod);
                });
                return key_data.empty();
            });
        });
#endif
    }

    template <typename ModType>
    auto start_mods() -> std::string
    {
        ProfilerScope();

        // Determine which mods.txt file(s) to parse
        std::vector<std::filesystem::path> mods_txt_files_to_parse;

        if (!UE4SSProgram::settings_manager.Overrides.ControllingModsTxt.empty())
        {
            // If a controlling mods.txt is specified, only use that one
            auto controlling_path = UE4SSProgram::get_program().make_compatible_path(UE4SSProgram::settings_manager.Overrides.ControllingModsTxt);
            if (std::filesystem::exists(controlling_path))
            {
                mods_txt_files_to_parse.push_back(controlling_path);
                Output::send(STR("Using controlling mods.txt from: {}\n"), ensure_str(controlling_path));
            }
            else
            {
                Output::send(STR("Warning: Controlling mods.txt not found at: {}\n"), ensure_str(controlling_path));
            }
        }
        else
        {
            // Parse mods.txt from all directories
            for (const auto& mods_directory : std::ranges::reverse_view(UE4SSProgram::get_program().get_mods_directories()))
            {
                if (!std::filesystem::exists(mods_directory))
                {
                    continue;
                }

                auto mods_txt_path = mods_directory / "mods.txt";
                if (std::filesystem::exists(mods_txt_path))
                {
                    mods_txt_files_to_parse.push_back(mods_txt_path);
                }
            }
        }

        // Part #2 runs first: enumerate the mods directory and install + start
        // all mods that have enabled.txt. This installs the mods (creates their
        // objects, calls dlopen for C++ mods) so subsequent name-based lookups
        // will find them. Without this ordering, Part #1's mods.txt lookup
        // would always fail with "not found or not installed" because the mods
        // haven't been installed yet.

        // Process each mods.txt file
        // Part #2: Start all mods that have enabled.txt present in the mod directory.
        // This runs FIRST so the mods are installed (objects created, dlopen done)
        // before Part #1 tries to look them up by name. Without this ordering,
        // Part #1's lookup would always fail with "not found or not installed"
        // because the mods haven't been installed yet.
        for (const auto& mods_directory : UE4SSProgram::get_program().get_mods_directories())
        {
            if (!std::filesystem::exists(mods_directory))
            {
                continue;
            }

            Output::send(STR("Starting mods (from enabled.txt ({}), no defined load order)...\n"), ensure_str(mods_directory));

            for (const auto& mod_directory : std::filesystem::directory_iterator(mods_directory))
            {
                std::error_code ec{};

                if (!mod_directory.is_directory(ec))
                {
                    continue;
                }
                if (ec.value() != 0)
                {
                    return fmt::format("is_directory ran into error {}", ec.value());
                }

                if (!std::filesystem::exists(mod_directory.path() / "enabled.txt", ec))
                {
                    continue;
                }
                if (ec.value() != 0)
                {
                    return fmt::format("exists ran into error {}", ec.value());
                }

                auto mod = UE4SSProgram::find_mod_by_name<ModType>(ensure_str(mod_directory.path().stem()), UE4SSProgram::IsInstalled::Yes);
                if (!dynamic_cast<ModType*>(mod))
                {
                    continue;
                }
                if (!mod)
                {
                    Output::send<LogLevel::Warning>(STR("Found a mod with enabled.txt but mod has not been installed properly.\n"));
                    continue;
                }

                if (mod->is_started())
                {
                    continue;
                }

                Output::send(STR("Mod '{}' has enabled.txt, starting mod.\n"), mod->get_name().data());
#ifdef __linux__
                bool ok = ue4ss_with_crash_recovery([&]() { mod->start_mod(); });
                if (!ok)
                {
                    Output::send<LogLevel::Error>(STR("Mod '{}' crashed during startup (enabled.txt), continuing to next mod.\n"), mod->get_name().data());
                }
#else
                mod->start_mod();
#endif
            }
        }

        // Part #1: Start mods listed in mods.txt that haven't been started yet.
        // Runs AFTER Part #2 so mods are installed and findable by name.
        // The is_started() check skips mods that Part #2 already started.
        for (const auto& enabled_mods_file : mods_txt_files_to_parse)
        {
            if (!std::filesystem::exists(enabled_mods_file))
            {
                Output::send(STR("No mods.txt file found...\n"));
            }
            else
            {
                // 'mods.txt' exists, lets parse it
                Output::send(STR("Starting mods (from mods.txt ({}) load order)...\n"), ensure_str(enabled_mods_file));

                // First, check for BOM using a byte stream
                std::ifstream bom_check(enabled_mods_file, std::ios::binary);
                char bom[3] = {0};
                bom_check.read(bom, 3);
                bool has_bom = (bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF');
                bom_check.close();

#ifdef __linux__
                // On Linux, use narrow stream and convert to wide string
                // wifstream causes SIGSEGV because it tries to read 4-byte wchar_t from ASCII files
                std::ifstream mods_stream_narrow(enabled_mods_file);
                std::string narrow_line;
                while (std::getline(mods_stream_narrow, narrow_line))
                {
                    StringType current_line;
                    for (char c : narrow_line)
                    {
                        current_line.push_back(static_cast<CharType>(static_cast<unsigned char>(c)));
                    }
#else
                // Now open the actual stream
                StreamIType mods_stream{enabled_mods_file};

                // If BOM was detected, skip the first "character" (which will be the BOM interpreted as a wide char)
                if (has_bom)
                {
                    CharType discard;
                    mods_stream.read(&discard, 1);
                }

                StringType current_line;
                while (std::getline(mods_stream, current_line))
                {
#endif
                    // Don't parse any lines with ';'
                    if (current_line.find(STR(";")) != current_line.npos)
                    {
                        continue;
                    }

                    // Don't parse if the line is impossibly short (empty lines for example)
                    if (current_line.size() <= 4)
                    {
                        continue;
                    }

                    // Remove all spaces
                    auto end = std::remove(current_line.begin(), current_line.end(), STR(' '));
                    current_line.erase(end, current_line.end());

                    // Parse the line into something that can be converted into proper data
                    StringType mod_name = explode_by_occurrence(current_line, STR(':'), 1);
                    StringType mod_enabled = explode_by_occurrence(current_line, STR(':'), ExplodeType::FromEnd);

                    auto mod = UE4SSProgram::find_mod_by_name<ModType>(mod_name, UE4SSProgram::IsInstalled::Yes);
                    if (!mod || !dynamic_cast<ModType*>(mod) || mod->is_started())
                    {
                        if (!mod)
                        {
                            Output::send<LogLevel::Warning>(STR("Mod '{}' not found or not installed, skipping.\n"), mod_name);
                        }
                        continue;
                    }

                    if (!mod_enabled.empty() && mod_enabled[0] == STR('1'))
                    {
                        Output::send(STR("Starting {} mod '{}'\n"), std::is_same_v<ModType, LuaMod> ? STR("Lua") : STR("C++"), mod->get_name().data());
#ifdef __linux__
                        bool ok = ue4ss_with_crash_recovery([&]() { mod->start_mod(); });
                        if (!ok)
                        {
                            Output::send<LogLevel::Error>(STR("Mod '{}' crashed during startup, continuing to next mod.\n"), mod->get_name().data());
                        }
#else
                        mod->start_mod();
#endif
                    }
                    else
                    {
                        Output::send(STR("Mod '{}' disabled in mods.txt.\n"), mod_name);
                    }
                }
            }
        }

        return {};
    }

    auto UE4SSProgram::start_lua_mods() -> void
    {
        ProfilerScope();
        auto error_message = start_mods<LuaMod>();
        if (!error_message.empty())
        {
            set_error(error_message.c_str());
        }
    }

    auto UE4SSProgram::start_cpp_mods(IsInitialStartup is_initial_startup) -> void
    {
        ProfilerScope();
        auto error_message = start_mods<CppMod>();
        if (!error_message.empty())
        {
            set_error(error_message.c_str());
        }
        // If this is the initial startup, notify mods that the UI has initialized.
        // This isn't completely accurate since the UI will usually have started a while ago.
        // However, we can't immediately notify mods of this because no mods have been started at that point.
        // We only need to do this for the initial start of UE4SS because after that, more accurate notifications will happen when the UI is closed an reopened.
#ifdef HAS_GUI
        if (is_initial_startup == IsInitialStartup::Yes && m_render_thread.get_id() != std::this_thread::get_id())
        {
            fire_ui_init_for_cpp_mods();
        }
#endif
        fire_on_cpp_mods_loaded_for_cpp_mods();
    }

    auto UE4SSProgram::uninstall_mods() -> void
    {
        ProfilerScope();
        std::vector<CppMod*> cpp_mods{};
        std::vector<LuaMod*> lua_mods{};
        for (auto& mod : m_mods)
        {
            if (auto cpp_mod = dynamic_cast<CppMod*>(mod.get()); cpp_mod)
            {
                cpp_mods.emplace_back(cpp_mod);
            }
            else if (auto lua_mod = dynamic_cast<LuaMod*>(mod.get()); lua_mod)
            {
                lua_mods.emplace_back(lua_mod);
            }
        }

        for (auto& mod : lua_mods)
        {
            // Remove any actions, or we'll get an internal error as the lua ref won't be valid
            mod->uninstall();
        }

        for (auto& mod : cpp_mods)
        {
            if (!mod->is_installable())
            {
                continue;
            }
            mod->uninstall();
        }

        m_mods.clear();
        LuaMod::global_uninstall();
    }

    auto UE4SSProgram::delete_mod(Mod* mod) -> void
    {
        for (auto it = m_mods.begin(); it != m_mods.end();)
        {
            if (it->get() == mod)
            {
                it = m_mods.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
    }

    auto UE4SSProgram::is_program_started() -> bool
    {
        return m_is_program_started;
    }

    auto UE4SSProgram::find_mod_by_id(ModId mod_id) -> Mod*
    {
        if (mod_id == InvalidModId)
        {
            return nullptr;
        }
        for (auto& mod : m_mods)
        {
            if (mod->get_id() == mod_id)
            {
                return mod.get();
            }
        }
        return nullptr;
    }

    auto UE4SSProgram::find_lua_mod_by_id(ModId mod_id) -> LuaMod*
    {
        return dynamic_cast<LuaMod*>(find_mod_by_id(mod_id));
    }

    auto UE4SSProgram::queue_reinstall_mods() -> void
    {
        if (!is_event_loop_thread())
        {
            queue_event([this]() { queue_reinstall_mods(); });
            return;
        }

        ProfilerScope();
        Output::send(STR("Re-installing all mods\n"));

        // Stop processing events while stuff isn't properly setup
        m_pause_events_processing = true;

        uninstall_mods();

        // Remove all custom properties
        // Uncomment when custom properties are working
        LuaType::LuaCustomProperty::StaticStorage::property_list.clear();

        // Reset the Lua callbacks for the global Lua function 'NotifyOnNewObject'
        LuaMod::m_static_construct_object_lua_callbacks.clear();

        // Start processing events again as everything is now properly setup
        // Do this before mods are started or else you won't be able to use the hot-reload key bind if there's an error from Lua
        m_pause_events_processing = false;

        setup_mods();
        start_cpp_mods();
        start_lua_mods();

        if (Unreal::UnrealInitializer::StaticStorage::bIsInitialized)
        {
            fire_unreal_init_for_cpp_mods();
        }

        if (is_program_started())
        {
            fire_program_start_for_cpp_mods();
        }

        Output::send(STR("All mods re-installed\n"));
    }

    auto UE4SSProgram::queue_reinstall_mod(LuaMod* mod) -> void
    {
        if (!mod)
        {
            return;
        }

        if (!is_event_loop_thread())
        {
            queue_event([this, mod]() { queue_reinstall_mod(mod); });
            return;
        }

        // Save mod info before uninstalling
        StringType mod_name = StringType(mod->get_name());
        StringType mod_path = ensure_str(mod->get_path().string());

        Output::send(STR("Reinstalling mod: {}\n"), mod_name);

        // Pause event processing for safety
        m_pause_events_processing = true;

        mod->uninstall();

        // Remove key binds registered by this specific mod
        unregister_keydown_events_for_lua_mod(mod, AllMods::No);

        // Remove the old mod from the list
        delete_mod(mod);
        mod = nullptr;

        // Resume event processing before starting the new mod
        m_pause_events_processing = false;

        // Create a new LuaMod for this mod (same as setup_mods does)
        auto new_mod = std::make_unique<LuaMod>(*this, std::move(mod_name), std::move(mod_path));
        LuaMod* new_mod_ptr = new_mod.get();
        m_mods.emplace_back(std::move(new_mod));

        new_mod_ptr->start_mod();

        Output::send(STR("Mod '{}' reinstalled\n"), new_mod_ptr->get_name());
    }

    auto UE4SSProgram::queue_uninstall_mod(LuaMod* mod) -> void
    {
        if (!mod)
        {
            return;
        }

        if (!is_event_loop_thread())
        {
            queue_event([this, mod]() { queue_uninstall_mod(mod); });
            return;
        }

        StringType mod_name = StringType(mod->get_name());
        Output::send(STR("Uninstalling mod: {}\n"), mod_name);

        // Pause event processing for safety
        m_pause_events_processing = true;

        mod->uninstall();

        // Remove key binds registered by this specific mod
        unregister_keydown_events_for_lua_mod(mod, AllMods::No);

        delete_mod(mod);

        // Resume event processing
        m_pause_events_processing = false;

        Output::send(STR("Mod '{}' uninstalled\n"), mod_name);
    }

    auto UE4SSProgram::queue_reinstall_mod(ModId mod_id) -> void
    {
        if (mod_id == InvalidModId)
        {
            return;
        }

        if (!is_event_loop_thread())
        {
            queue_event([this, mod_id]() { queue_reinstall_mod(mod_id); });
            return;
        }

        // Look up the mod by ID at execution time (safe for queued events)
        if (auto* lua_mod = find_lua_mod_by_id(mod_id))
        {
            queue_reinstall_mod(lua_mod);
        }
        else
        {
            Output::send<LogLevel::Warning>(STR("Could not find mod to reinstall with ID: {}\n"), mod_id);
        }
    }

    auto UE4SSProgram::queue_uninstall_mod(ModId mod_id) -> void
    {
        if (mod_id == InvalidModId)
        {
            return;
        }

        if (!is_event_loop_thread())
        {
            queue_event([this, mod_id]() { queue_uninstall_mod(mod_id); });
            return;
        }

        // Look up the mod by ID at execution time (safe for queued events)
        if (auto* lua_mod = find_lua_mod_by_id(mod_id))
        {
            queue_uninstall_mod(lua_mod);
        }
        else
        {
            Output::send<LogLevel::Warning>(STR("Could not find mod to uninstall with ID: {}\n"), mod_id);
        }
    }

    auto UE4SSProgram::queue_reinstall_mod_by_name(const std::string& mod_name) -> void
    {
        if (!is_event_loop_thread())
        {
            queue_event([this, mod_name]() { queue_reinstall_mod_by_name(mod_name); });
            return;
        }

        // Find the mod by name at execution time (safe for queued events)
        for (auto& mod : m_mods)
        {
            auto* lua_mod = dynamic_cast<LuaMod*>(mod.get());
            if (lua_mod && to_string(lua_mod->get_name()) == mod_name)
            {
                queue_reinstall_mod(lua_mod);
                return;
            }
        }
        Output::send<LogLevel::Warning>(STR("Could not find mod to reinstall: {}\n"), ensure_str(mod_name));
    }

    auto UE4SSProgram::queue_reinstall_mod_by_name(std::string_view mod_name) -> void
    {
        queue_reinstall_mod_by_name(std::string{mod_name});
    }

    auto UE4SSProgram::queue_uninstall_mod_by_name(const std::string& mod_name) -> void
    {
        if (!is_event_loop_thread())
        {
            queue_event([this, mod_name]() { queue_uninstall_mod_by_name(mod_name); });
            return;
        }

        // Find the mod by name at execution time (safe for queued events)
        for (auto& mod : m_mods)
        {
            auto* lua_mod = dynamic_cast<LuaMod*>(mod.get());
            if (lua_mod && to_string(lua_mod->get_name()) == mod_name)
            {
                queue_uninstall_mod(lua_mod);
                return;
            }
        }
        Output::send<LogLevel::Warning>(STR("Could not find mod to uninstall: {}\n"), ensure_str(mod_name));
    }

    auto UE4SSProgram::queue_uninstall_mod_by_name(std::string_view mod_name) -> void
    {
        queue_uninstall_mod_by_name(std::string{mod_name});
    }

    auto UE4SSProgram::queue_start_lua_mod_by_path(const std::filesystem::path& mod_path) -> void
    {
        if (!is_event_loop_thread())
        {
            queue_event([this, mod_path]() { queue_start_lua_mod_by_path(mod_path); });
            return;
        }

        std::string mod_name_str = mod_path.stem().string();

        // Check if mod already exists in m_mods
        for (auto& mod : m_mods)
        {
            auto* lua_mod = dynamic_cast<LuaMod*>(mod.get());
            if (lua_mod && to_string(lua_mod->get_name()) == mod_name_str)
            {
                if (lua_mod->is_started())
                {
                    Output::send<LogLevel::Warning>(STR("Mod '{}' is already running\n"), ensure_str(mod_name_str));
                    return;
                }
                else
                {
                    // Mod exists but is not started - remove it first (its Lua state is invalid)
                    // Then we'll create a fresh one below
                    delete_mod(lua_mod);
                    break;
                }
            }
        }

        // Verify the mod path exists and has a main.lua
        std::filesystem::path scripts_path = mod_path / STR("Scripts");
        std::filesystem::path main_lua = scripts_path / STR("main.lua");
        if (!std::filesystem::exists(main_lua))
        {
            Output::send<LogLevel::Error>(STR("Cannot start mod '{}': main.lua not found\n"), ensure_str(mod_name_str));
            return;
        }

        Output::send(STR("Starting mod: {}\n"), ensure_str(mod_name_str));

        StringType mod_name = ensure_str(mod_name_str);

        auto new_mod = std::make_unique<LuaMod>(*this, std::move(mod_name), ensure_str(std::filesystem::path(mod_path).string()));
        LuaMod* new_mod_ptr = new_mod.get();
        m_mods.emplace_back(std::move(new_mod));

        new_mod_ptr->start_mod();

        Output::send(STR("Mod '{}' started\n"), new_mod_ptr->get_name());
    }

    auto UE4SSProgram::get_module_directory() -> File::StringType
    {
        return ensure_str(m_module_file_path);
    }

    auto UE4SSProgram::get_game_executable_directory() -> File::StringType
    {
        return ensure_str(m_game_executable_directory);
    }

    auto UE4SSProgram::get_working_directory() -> File::StringType
    {
        return ensure_str(m_working_directory);
    }

    auto UE4SSProgram::get_mods_directory() -> File::StringType
    {
        // Return the first (primary) mods directory for backwards compatibility
        return m_mods_directories.empty() ? STR("") : ensure_str(m_mods_directories[0]);
    }

    auto UE4SSProgram::get_mods_directories() -> std::vector<std::filesystem::path>&
    {
        return m_mods_directories;
    }

    auto UE4SSProgram::get_mods_txt_entries() -> std::unordered_map<std::string, bool>
    {
        std::unordered_map<std::string, bool> result;

        std::vector<std::filesystem::path> mods_txt_files;

        if (!settings_manager.Overrides.ControllingModsTxt.empty())
        {
            auto controlling_path = make_compatible_path(settings_manager.Overrides.ControllingModsTxt);
            if (std::filesystem::exists(controlling_path))
            {
                mods_txt_files.push_back(controlling_path);
            }
        }
        else
        {
            for (const auto& mods_directory : std::ranges::reverse_view(m_mods_directories))
            {
                if (!std::filesystem::exists(mods_directory))
                {
                    continue;
                }

                auto mods_txt_path = mods_directory / "mods.txt";
                if (std::filesystem::exists(mods_txt_path))
                {
                    mods_txt_files.push_back(mods_txt_path);
                }
            }
        }

        for (const auto& mods_txt_path : mods_txt_files)
        {
            std::ifstream bom_check(mods_txt_path, std::ios::binary);
            char bom[3] = {0};
            bom_check.read(bom, 3);
            bool has_bom = (bom[0] == '\xEF' && bom[1] == '\xBB' && bom[2] == '\xBF');
            bom_check.close();

            StreamIType mods_stream{mods_txt_path};

            if (has_bom)
            {
                CharType discard;
                mods_stream.read(&discard, 1);
            }

            StringType current_line;
            while (std::getline(mods_stream, current_line))
            {
                if (current_line.find(STR(";")) != current_line.npos)
                {
                    continue;
                }

                if (current_line.size() <= 4)
                {
                    continue;
                }

                auto end = std::remove(current_line.begin(), current_line.end(), STR(' '));
                current_line.erase(end, current_line.end());

                StringType mod_name = explode_by_occurrence(current_line, STR(':'), 1);
                StringType mod_enabled = explode_by_occurrence(current_line, STR(':'), ExplodeType::FromEnd);

                std::string mod_name_str = to_string(mod_name);
                bool enabled = !mod_enabled.empty() && mod_enabled[0] == STR('1');

                if (result.find(mod_name_str) == result.end())
                {
                    result[mod_name_str] = enabled;
                }
            }
        }

        return result;
    }

    auto UE4SSProgram::make_compatible_path(const std::filesystem::path& in_path) const -> std::filesystem::path
    {
        auto path = in_path;
        if (path.is_relative())
        {
            path = m_working_directory / path;
        }
        path = path.lexically_normal().make_preferred();
        path = std::filesystem::weakly_canonical(path);
        return path;
    }

    auto UE4SSProgram::insert_mods_directory(const std::filesystem::path& path, int64_t index) -> void
    {
        m_mods_directories.insert(m_mods_directories.begin() + index, path);
    }

    auto UE4SSProgram::add_mods_directory(const std::filesystem::path& in_path) -> void
    {
        auto path = make_compatible_path(in_path);
        if (const auto it = std::ranges::find(m_mods_directories, path); it != m_mods_directories.end())
        {
            m_mods_directories.erase(it);
        }
        m_mods_directories.emplace_back(std::forward<decltype(path)>(path));
    }

    auto UE4SSProgram::remove_mods_directory(const std::filesystem::path& in_path) -> void
    {
        auto path = make_compatible_path(in_path);
        m_mods_directories_to_remove.emplace_back(std::forward<decltype(path)>(path));
    }

    auto UE4SSProgram::get_legacy_root_directory() -> File::StringType
    {
        return ensure_str(m_legacy_root_directory);
    }

    auto UE4SSProgram::generate_uht_compatible_headers() -> void
    {
        ProfilerScope();
        Output::send(STR("Generating UHT compatible headers...\n"));

        double generator_duration{};
        {
            ScopedTimer generator_timer{&generator_duration};

            const std::filesystem::path DumpRootDirectory = m_working_directory / "UHTHeaderDump";
            UEGenerator::UEHeaderGenerator HeaderGenerator = UEGenerator::UEHeaderGenerator(DumpRootDirectory);
            HeaderGenerator.dump_native_packages();
        }

        Output::send(STR("Generating UHT compatible headers took {} seconds\n"), generator_duration);
    }

    auto UE4SSProgram::generate_cxx_headers(const std::filesystem::path& output_dir) -> void
    {
        ProfilerScope();
        if (settings_manager.CXXHeaderGenerator.LoadAllAssetsBeforeGeneratingCXXHeaders)
        {
            Output::send(STR("Loading all assets...\n"));
            double asset_loading_duration{};
            {
                ProfilerScopeNamed("loading all assets");
                ScopedTimer loading_timer{&asset_loading_duration};

                UAssetRegistry::LoadAllAssets();
            }
            Output::send(STR("Loading all assets took {} seconds\n"), asset_loading_duration);
        }

        double generator_duration;
        {
            ProfilerScopeNamed("unloading all force-loaded assets");
            ScopedTimer generator_timer{&generator_duration};

            UEGenerator::generate_cxx_headers(output_dir);

            Output::send(STR("Unloading all forcefully loaded assets\n"));
        }

        UAssetRegistry::FreeAllForcefullyLoadedAssets();
        Output::send(STR("SDK generated in {} seconds.\n"), generator_duration);
    }

    auto UE4SSProgram::generate_lua_types(const std::filesystem::path& output_dir) -> void
    {
        ProfilerScope();
        if (settings_manager.CXXHeaderGenerator.LoadAllAssetsBeforeGeneratingCXXHeaders)
        {
            Output::send(STR("Loading all assets...\n"));
            double asset_loading_duration{};
            {
                ProfilerScopeNamed("loading all assets");
                ScopedTimer loading_timer{&asset_loading_duration};

                UAssetRegistry::LoadAllAssets();
            }
            Output::send(STR("Loading all assets took {} seconds\n"), asset_loading_duration);
        }

        double generator_duration;
        {
            ProfilerScopeNamed("unloading all force-loaded assets");
            ScopedTimer generator_timer{&generator_duration};

            UEGenerator::generate_lua_types(output_dir);

            Output::send(STR("Unloading all forcefully loaded assets\n"));
        }

        UAssetRegistry::FreeAllForcefullyLoadedAssets();
        Output::send(STR("SDK generated in {} seconds.\n"), generator_duration);
    }

#ifdef HAS_GUI
    auto UE4SSProgram::stop_render_thread() -> void
    {
        if (!get_debugging_ui().is_open())
        {
            return;
        }
        if (settings_manager.Debug.RenderMode == GUI::RenderMode::ExternalThread && m_render_thread.joinable())
        {
            m_render_thread.request_stop();
            m_render_thread.join();
        }
        else
        {
            get_debugging_ui().request_exit();
        }
    }

    auto UE4SSProgram::add_gui_tab(std::shared_ptr<GUI::GUITab> tab) -> void
    {
        m_debugging_gui.add_tab(tab);
    }

    auto UE4SSProgram::remove_gui_tab(std::shared_ptr<GUI::GUITab> tab) -> void
    {
        m_debugging_gui.remove_tab(tab);
    }
#endif

    auto UE4SSProgram::queue_event(EventCallable callable) -> void
    {
        if (!can_process_events())
        {
            return;
        }
        std::lock_guard<std::mutex> guard(m_event_queue_mutex);
        m_queued_events.emplace_back(std::move(callable));
    }

    auto UE4SSProgram::queue_event(LegacyEventCallable callable, void* data) -> void
    {
        queue_event([callable, data]() { callable(data); });
    }

    auto UE4SSProgram::is_queue_empty() -> bool
    {
        // Not locking here because if the worst that could happen as far as I know is that the event loop processes the event slightly late.
        return m_queued_events.empty();
    }

    auto UE4SSProgram::register_keydown_event(Input::Key key, const Input::EventCallbackCallable& callback, uint8_t custom_data, void* custom_data2) -> void
    {
#ifdef HAS_INPUT
        m_input_handler.register_keydown_event(key, callback, custom_data, custom_data2);
#endif
    }

    auto UE4SSProgram::register_keydown_event(Input::Key key,
                                              const Input::Handler::ModifierKeyArray& modifier_keys,
                                              const Input::EventCallbackCallable& callback,
                                              uint8_t custom_data,
                                              void* custom_data2) -> void
    {
#ifdef HAS_INPUT
        m_input_handler.register_keydown_event(key, modifier_keys, callback, custom_data, custom_data2);
#endif
    }

    auto UE4SSProgram::is_keydown_event_registered(Input::Key key) -> bool
    {
#ifdef HAS_INPUT
        return m_input_handler.is_keydown_event_registered(key);
#else
        return false;
#endif
    }

    auto UE4SSProgram::is_keydown_event_registered(Input::Key key, const Input::Handler::ModifierKeyArray& modifier_keys) -> bool
    {
#ifdef HAS_INPUT
        return m_input_handler.is_keydown_event_registered(key, modifier_keys);
#else
        return false;
#endif
    }

    auto UE4SSProgram::get_all_input_events(std::function<void(Input::KeySet&)> callback) -> void
    {
#ifdef HAS_INPUT
        m_input_handler.get_events_safe(callback);
#endif
    }

    auto UE4SSProgram::find_mod_by_name_internal(StringViewType mod_name, IsInstalled is_installed, IsStarted is_started, FMBNI_ExtraPredicate extra_predicate)
            -> Mod*
    {
        auto mod_exists_with_name = std::find_if(get_program().m_mods.begin(), get_program().m_mods.end(), [&](auto& elem) -> bool {
            bool found = true;

            if (!extra_predicate(elem.get()))
            {
                found = false;
            }
            if (mod_name != elem->get_name())
            {
                found = false;
            }
            if (is_installed == IsInstalled::Yes && !elem->is_installable())
            {
                found = false;
            }
            if (is_started == IsStarted::Yes && !elem->is_started())
            {
                found = false;
            }

            return found;
        });

        // clang-format off
        if (mod_exists_with_name == get_program().m_mods.end())
        {
            return nullptr;
        }
        // clang-format on
        else
        {
            return mod_exists_with_name->get();
        }
    }

    auto UE4SSProgram::find_lua_mod_by_name(std::string_view mod_name, UE4SSProgram::IsInstalled installed_only, IsStarted is_started) -> LuaMod*
    {
        return static_cast<LuaMod*>(find_mod_by_name<LuaMod>(mod_name, installed_only, is_started));
    }

    auto UE4SSProgram::find_lua_mod_by_name(StringViewType mod_name, UE4SSProgram::IsInstalled installed_only, IsStarted is_started) -> LuaMod*
    {
        return static_cast<LuaMod*>(find_mod_by_name<LuaMod>(mod_name, installed_only, is_started));
    }

    auto UE4SSProgram::get_object_dumper_output_directory() -> const File::StringType
    {
        return ensure_str(m_object_dumper_output_directory);
    }

    auto UE4SSProgram::dump_uobject(UObject* object,
                                    std::unordered_set<FField*>* in_dumped_fields,
                                    StringType& out_line,
                                    bool is_below_425,
                                    std::unordered_set<UFunction*>* in_dumped_functions) -> void
    {
        bool owns_dumped_fields{};
        auto dumped_fields_ptr = [&] {
            if (in_dumped_fields)
            {
                return in_dumped_fields;
            }
            else
            {
                owns_dumped_fields = true;
                return new std::unordered_set<FField*>{};
            }
        }();
        auto& dumped_fields = *dumped_fields_ptr;

        UObject* typed_obj = static_cast<UObject*>(object);

        static auto delegate_function_class = UObjectGlobals::StaticFindObject<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.DelegateFunction"));
        static auto linker_placeholder_function_class =
                UObjectGlobals::StaticFindObject<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.LinkerPlaceholderFunction"));

        bool is_property = is_below_425 && Unreal::TypeChecker::is_property(typed_obj) &&
                           !typed_obj->HasAnyFlags(static_cast<EObjectFlags>(EObjectFlags::RF_DefaultSubObject | EObjectFlags::RF_ArchetypeObject));
        if (!is_property && (!typed_obj->IsA<UFunction>() || typed_obj->IsA(delegate_function_class) || typed_obj->IsA(linker_placeholder_function_class)))
        {
            if (in_dumped_functions && typed_obj->IsA<UFunction>())
            {
                if (in_dumped_functions->contains(static_cast<UFunction*>(typed_obj)))
                {
                    return;
                }
                else
                {
                    in_dumped_functions->emplace(static_cast<UFunction*>(typed_obj));
                }
            }
            auto typed_class = typed_obj->GetClassPrivate()->HashObject();
            if (ObjectDumper::to_string_exists(typed_class))
            {
                // Call type-specific implementation to dump UObject
                // The type is determined at runtime

                // Dump UObject
                ObjectDumper::get_to_string(typed_class)(object, out_line);
                out_line.append(STR("\n"));

                if (ObjectDumper::to_string_complex_exists(typed_class))
                {
                    // Dump all properties that are directly owned by this UObject (not its UClass)
                    ObjectDumper::get_to_string_complex(typed_class)(object, out_line, [&](void* prop) {
                        if (dumped_fields.contains(static_cast<FField*>(prop)))
                        {
                            return;
                        }

                        ObjectDumper::dump_xproperty(static_cast<FProperty*>(prop), out_line);
                        dumped_fields.emplace(static_cast<FField*>(prop));
                    });
                }
            }
            else
            {
                // A type-specific implementation does not exist so lets call the default implementation for UObjects instead
                ObjectDumper::object_to_string(object, out_line);
                out_line.append(STR("\n"));
            }

            // If the UClass of the UObject has any properties then dump them
            if (typed_obj->IsA<UStruct>())
            {
                for (FProperty* prop : TFieldRange<FProperty>(static_cast<UClass*>(typed_obj), Unreal::EFieldIterationFlags::IncludeDeprecated))
                {
                    if (dumped_fields.contains(prop))
                    {
                        continue;
                    }

                    ObjectDumper::dump_xproperty(prop, out_line);
                    dumped_fields.emplace(prop);
                }
            }

            if (typed_obj->IsA<UStruct>())
            {
                for (UFunction* func : TFieldRange<UFunction>(static_cast<UStruct*>(typed_obj), Unreal::EFieldIterationFlags::None))
                {
                    ObjectDumper::function_to_string(func, out_line, in_dumped_functions);
                }
            }
        }

        if (owns_dumped_fields)
        {
            delete dumped_fields_ptr;
        }
    }

    auto UE4SSProgram::dump_all_objects_and_properties(const File::StringType& output_path_and_file_name) -> void
    {
        /*
        Output::send(STR("Test msg with no fmt args, and no optional arg\n"));
        Output::send(STR("Test msg with no fmt args, and one optional arg [Normal]\n"), LogLevel::Normal);
        Output::send(STR("Test msg with no fmt args, and one optional arg [Verbose]\n"), LogLevel::Verbose);
        Output::send(STR("Test msg with one fmt arg [{}], and one optional arg [Warning]\n"), LogLevel::Warning, 33);
        Output::send(STR("Test msg with two fmt args [{}, {}], and one optional arg [Error]\n"), LogLevel::Error, 33, 44);
        //*/

        // Object & Property Dumper -> START
        if (settings_manager.ObjectDumper.LoadAllAssetsBeforeDumpingObjects)
        {
            Output::send(STR("Loading all assets...\n"));
            double asset_loading_duration{};
            {
                ScopedTimer loading_timer{&asset_loading_duration};

                UAssetRegistry::LoadAllAssets();
            }
            Output::send(STR("Loading all assets took {} seconds\n"), asset_loading_duration);
        }

        double dumper_duration{};
        {
            ScopedTimer dumper_timer{&dumper_duration};

            std::unordered_set<FField*> dumped_fields;
            // There will be tons of dumped fields so lets just reserve tons in order to speed things up a bit
            dumped_fields.reserve(100000);

            // Some delegate functions belong to a class, and are dumped as part of the class.
            // Others are not, and must be dumped as part of GUObjectArray.
            // Both are part of GUObjectArray.
            // We must maintain a list of already dumped functions to avoid dumping the same function multiple times.
            // We can't just use GUObjectArray even though they all exist in there because that would destroy the order in which objects get dumped.
            std::unordered_set<UFunction*> dumped_functions;
            dumped_fields.reserve(10000);

            bool is_below_425 = Unreal::Version::IsBelow(4, 25);

            // The final outputted string shouldn't need be reformatted just to put a new line at the end
            // Instead the object/property implementations should add a new line in the last format that they do
            //
            // Optimizations done:
            // 1. The entire code-base has been changed to use 'wchar_t' instead of 'char'.
            // The effect of this is that there is no need to ever convert between types.
            // There's also no thinking about which type should be used since 'wchar_t' is now the standard for UE4SS.
            // The downside with wchar_t is that all files that get output to will be doubled in size.

            using ObjectDumperOutputDevice = Output::NewFileDevice;
            Output::Targets<ObjectDumperOutputDevice> scoped_dumper_out;
            auto& file_device = scoped_dumper_out.get_device<ObjectDumperOutputDevice>();
            file_device.set_file_name_and_path(output_path_and_file_name);
            file_device.set_formatter([](File::StringViewType string) -> File::StringType {
                return File::StringType{string};
            });

            // Make string & reserve massive amounts of space to hopefully not reach the end of the string and require more
            // dynamic allocations
            StringType out_line;
            out_line.reserve(200000000);

            Output::send(STR("Dumping all objects & properties in GUObjectArray\n"));
            UObjectGlobals::ForEachUObject([&](void* object, [[maybe_unused]] int32_t chunk_index, [[maybe_unused]] int32_t object_index) {
                dump_uobject(static_cast<UObject*>(object), &dumped_fields, out_line, is_below_425, &dumped_functions);
                return LoopAction::Continue;
            });

            // Save to file
            scoped_dumper_out.send(out_line);

            // Reset the dumped_fields set, otherwise no fields will be dumped in subsequent dumps
            dumped_fields.clear();
            Output::send(STR("Done iterating GUObjectArray\n"));
        }

        UAssetRegistry::FreeAllForcefullyLoadedAssets();
        Output::send(STR("Dumping GUObjectArray took {} seconds\n"), dumper_duration);
        // Object & Property Dumper -> END
    }

    auto UE4SSProgram::static_cleanup() -> void
    {
        delete &get_program();

        // Do cleanup of static objects here
        // This function is called right before the library detaches from the game
        // Including when the player hits the 'X' button to exit the game
    }

    auto UE4SSProgram::parse_semicolon_separated_string(const StringType& string) -> std::vector<StringType>
    {
        std::vector<StringType> strings{};
        if (auto end = string.find(STR(';')); end == string.npos)
        {
            // No colon, but we still have content in the variable, so we'll assume this a single path.
            strings.emplace_back(string);
        }
        else
        {
            size_t start = 0;
            while (end != string.npos)
            {
                strings.emplace_back(string.substr(start, end - start));
                start = end + 1; // Adding 1 to skip the colon.
                end = string.find(STR(';'), start);
                if (end == string.npos)
                {
                    // No more colons, but we still content so let's assume that's another path.
                    strings.emplace_back(string.substr(start));
                }
            }
        }
        return strings;
    }
} // namespace RC
