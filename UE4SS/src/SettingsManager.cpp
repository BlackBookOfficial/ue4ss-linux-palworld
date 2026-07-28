#include <cstdio>
#include <fstream>
#include <map>
#include <optional>
#include <algorithm>
#include <cctype>
#include <Helpers/String.hpp>
#include <IniParser/Ini.hpp>
#include <SettingsManager.hpp>
#include <UE4SSProgram.hpp>
#include <UE4SSDebug.hpp>

#define REGISTER_STRING_SETTING(member_var, section_name, key)                                                                                                 \
    try                                                                                                                                                        \
    {                                                                                                                                                          \
        (member_var) = parser.get_string(section_name, STR(#key));                                                                                             \
    }                                                                                                                                                          \
    catch (std::exception&)                                                                                                                                    \
    {                                                                                                                                                          \
    }

#define REGISTER_INT64_SETTING(member_var, section_name, key)                                                                                                  \
    try                                                                                                                                                        \
    {                                                                                                                                                          \
        (member_var) = parser.get_int64(section_name, STR(#key));                                                                                              \
    }                                                                                                                                                          \
    catch (std::exception&)                                                                                                                                    \
    {                                                                                                                                                          \
    }

#define REGISTER_BOOL_SETTING(member_var, section_name, key)                                                                                                   \
    try                                                                                                                                                        \
    {                                                                                                                                                          \
        (member_var) = parser.get_bool(section_name, STR(#key));                                                                                               \
    }                                                                                                                                                          \
    catch (std::exception&)                                                                                                                                    \
    {                                                                                                                                                          \
    }

#define REGISTER_FLOAT_SETTING(member_var, section_name, key)                                                                                                  \
    try                                                                                                                                                        \
    {                                                                                                                                                          \
        (member_var) = parser.get_float(section_name, STR(#key));                                                                                              \
    }                                                                                                                                                          \
    catch (std::exception&)                                                                                                                                    \
    {                                                                                                                                                          \
    }

namespace RC
{
    auto SettingsManager::deserialize(std::filesystem::path& file_name) -> void
    {
#ifdef __linux__
        // On Linux, the wide-string INI parser (using u16string + unordered_map) crashes
        // with SIGSEGV due to the game's memory allocator interfering with std::wstring ops.
        // Instead, parse the INI file as narrow strings (std::string) and convert as needed.
        UE4SS_DBG( "[UE4SS] SettingsManager: parsing INI with narrow-string parser on Linux\n");

        // Simple narrow-string INI parser
        std::map<std::string, std::map<std::string, std::string>> ini_sections;
        std::string current_section;

        {
            std::ifstream ini_file(file_name);
            if (ini_file.is_open())
            {
                std::string line;
                while (std::getline(ini_file, line))
                {
                    // Trim trailing \r
                    if (!line.empty() && line.back() == '\r') line.pop_back();
                    // Trim leading/trailing whitespace
                    auto first = line.find_first_not_of(" \t");
                    if (first == std::string::npos) continue;
                    auto last = line.find_last_not_of(" \t");
                    std::string trimmed = line.substr(first, last - first + 1);

                    if (trimmed.empty() || trimmed[0] == ';' || trimmed[0] == '#') continue;

                    if (trimmed[0] == '[' && trimmed.back() == ']')
                    {
                        current_section = trimmed.substr(1, trimmed.size() - 2);
                        continue;
                    }

                    auto eq = trimmed.find('=');
                    if (eq == std::string::npos) continue;
                    std::string key = trimmed.substr(0, eq);
                    std::string val = trimmed.substr(eq + 1);
                    // Trim key and val
                    auto kfirst = key.find_first_not_of(" \t");
                    auto klast = key.find_last_not_of(" \t");
                    if (kfirst != std::string::npos) key = key.substr(kfirst, klast - kfirst + 1);
                    auto vfirst = val.find_first_not_of(" \t");
                    auto vlast = val.find_last_not_of(" \t");
                    if (vfirst != std::string::npos) val = val.substr(vfirst, vlast - vfirst + 1);
                    else val.clear();

                    ini_sections[current_section][key] = val;
                }
                UE4SS_DBG( "[UE4SS] SettingsManager: INI parsed, %zu sections\n", ini_sections.size());
            }
            else
            {
                UE4SS_DBG( "[UE4SS] SettingsManager: could not open INI file: %s, using defaults\n", file_name.string().c_str());
            }
        }

        // Helper lambdas
        auto get_str = [&](const std::string& section, const std::string& key) -> std::optional<std::string> {
            auto sit = ini_sections.find(section);
            if (sit == ini_sections.end()) return std::nullopt;
            auto kit = sit->second.find(key);
            if (kit == sit->second.end()) return std::nullopt;
            return kit->second;
        };
        auto get_bool = [&](const std::string& section, const std::string& key, bool def) -> bool {
            auto v = get_str(section, key);
            if (!v) return def;
            std::string lower = *v;
            std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });
            if (lower == "true" || lower == "1") return true;
            if (lower == "false" || lower == "0") return false;
            return def;
        };
        auto get_int64 = [&](const std::string& section, const std::string& key, int64_t def) -> int64_t {
            auto v = get_str(section, key);
            if (!v) return def;
            try { return std::stoll(*v); } catch (...) { return def; }
        };
        auto get_float = [&](const std::string& section, const std::string& key, float def) -> float {
            auto v = get_str(section, key);
            if (!v) return def;
            try { return std::stof(*v); } catch (...) { return def; }
        };
        auto to_string_type = [](const std::string& s) -> StringType {
            return StringType(s.begin(), s.end());
        };

        // [Overrides]
        if (auto v = get_str("Overrides", "ModsFolderPath")) Overrides.ModsFolderPath = to_string_type(*v);
        if (auto v = get_str("Overrides", "ControllingModsTxt")) Overrides.ControllingModsTxt = to_string_type(*v);

        // [General]
        General.EnableHotReloadSystem = get_bool("General", "EnableHotReloadSystem", true);
        General.EnableAutoReloadingLuaMods = get_bool("General", "EnableAutoReloadingLuaMods", true);
        General.UseCache = get_bool("General", "UseCache", true);
        General.InvalidateCacheIfDLLDiffers = get_bool("General", "InvalidateCacheIfDLLDiffers", true);
        General.EnableDebugKeyBindings = get_bool("General", "EnableDebugKeyBindings", false);
        General.SecondsToScanBeforeGivingUp = get_int64("General", "SecondsToScanBeforeGivingUp", 30);
        General.UseUObjectArrayCache = get_bool("General", "bUseUObjectArrayCache", true);
        General.DoEarlyScan = get_bool("General", "DoEarlyScan", false);
        General.SearchByAddress = get_bool("General", "bEnableSeachByMemoryAddress", false);

        if (auto v = get_str("General", "DefaultExecuteInGameThreadMethod"))
        {
            std::string lower = *v;
            std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });
            if (lower == "processevent") General.DefaultExecuteInGameThreadMethod = GameThreadExecutionMethod::ProcessEvent;
            else General.DefaultExecuteInGameThreadMethod = GameThreadExecutionMethod::EngineTick;
        }
        if (auto v = get_str("General", "DefaultFNameToStringMethod"))
        {
            std::string lower = *v;
            std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });
            if (lower == "conv_nametostring") General.DefaultFNameToStringMethod = Unreal::UnrealInitializer::FNameToStringMethod::Conv_NameToString;
            else General.DefaultFNameToStringMethod = Unreal::UnrealInitializer::FNameToStringMethod::Scan;
        }
        if (auto v = get_str("General", "HotReloadKey"))
        {
            try { General.HotReloadKey = Input::string_to_key(to_string_type(*v)); }
            catch (...) { UE4SS_DBG("[UE4SS] SettingsManager: invalid HotReloadKey value: %s\n", v->c_str()); }
        }
        if (auto v = get_str("General", "InputSource"))
        {
            General.InputSource = to_string_type(*v);
        }
        if (auto v = get_str("General", "DiscordWebhookURL"))
        {
            if (!v->empty()) General.DiscordWebhookURL = to_string_type(*v);
        }
        General.DebugLogLevel = get_int64("General", "DebugLogLevel", 0);

        // [EngineVersionOverride]
        EngineVersionOverride.MajorVersion = get_int64("EngineVersionOverride", "MajorVersion", -1);
        EngineVersionOverride.MinorVersion = get_int64("EngineVersionOverride", "MinorVersion", -1);
        EngineVersionOverride.DebugBuild = get_bool("EngineVersionOverride", "DebugBuild", false);

        // [ObjectDumper]
        ObjectDumper.LoadAllAssetsBeforeDumpingObjects = get_bool("ObjectDumper", "LoadAllAssetsBeforeDumpingObjects", false);
        ObjectDumper.UseModuleOffsets = get_bool("ObjectDumper", "UseModuleOffsets", false);

        // [CXXHeaderGenerator]
        CXXHeaderGenerator.DumpOffsetsAndSizes = get_bool("CXXHeaderGenerator", "DumpOffsetsAndSizes", false);
        CXXHeaderGenerator.KeepMemoryLayout = get_bool("CXXHeaderGenerator", "KeepMemoryLayout", false);
        CXXHeaderGenerator.LoadAllAssetsBeforeGeneratingCXXHeaders = get_bool("CXXHeaderGenerator", "LoadAllAssetsBeforeGeneratingCXXHeaders", false);

        // [UHTHeaderGenerator]
        UHTHeaderGenerator.IgnoreAllCoreEngineModules = get_bool("UHTHeaderGenerator", "IgnoreAllCoreEngineModules", false);
        UHTHeaderGenerator.IgnoreEngineAndCoreUObject = get_bool("UHTHeaderGenerator", "IgnoreEngineAndCoreUObject", true);
        UHTHeaderGenerator.MakeAllFunctionsBlueprintCallable = get_bool("UHTHeaderGenerator", "MakeAllFunctionsBlueprintCallable", false);
        UHTHeaderGenerator.MakeAllPropertyBlueprintsReadWrite = get_bool("UHTHeaderGenerator", "MakeAllPropertyBlueprintsReadWrite", false);
        UHTHeaderGenerator.MakeEnumClassesBlueprintType = get_bool("UHTHeaderGenerator", "MakeEnumClassesBlueprintType", false);
        UHTHeaderGenerator.MakeAllConfigsEngineConfig = get_bool("UHTHeaderGenerator", "MakeAllConfigsEngineConfig", false);

        // [Debug]
        Debug.SimpleConsoleEnabled = get_bool("Debug", "ConsoleEnabled", true);
        Debug.DebugConsoleEnabled = get_bool("Debug", "GuiConsoleEnabled", false);
        Debug.DebugConsoleVisible = get_bool("Debug", "GuiConsoleVisible", false);
        Debug.DebugGUIFontScaling = get_float("Debug", "GuiConsoleFontScaling", 1.0f);

        // [CrashDump]
        CrashDump.EnableDumping = get_bool("CrashDump", "EnableDumping", false);
        CrashDump.FullMemoryDump = get_bool("CrashDump", "FullMemoryDump", false);

        // [Threads]
        Threads.SigScannerNumThreads = get_int64("Threads", "SigScannerNumThreads", -1);
        Threads.SigScannerMultithreadingModuleSizeThreshold = get_int64("Threads", "SigScannerMultithreadingModuleSizeThreshold", 104857600);

        // [Memory]
        Memory.MaxMemoryUsageDuringAssetLoading = get_int64("Memory", "MaxMemoryUsageDuringAssetLoading", 85);

        // [Hooks]
        Hooks.HookProcessInternal = get_bool("Hooks", "HookProcessInternal", true);
        Hooks.HookProcessLocalScriptFunction = get_bool("Hooks", "HookProcessLocalScriptFunction", true);
        Hooks.HookLoadMap = get_bool("Hooks", "HookLoadMap", true);
        Hooks.HookInitGameState = get_bool("Hooks", "HookInitGameState", true);
        Hooks.HookCallFunctionByNameWithArguments = get_bool("Hooks", "HookCallFunctionByNameWithArguments", true);
        Hooks.HookBeginPlay = get_bool("Hooks", "HookBeginPlay", true);
        Hooks.HookEndPlay = get_bool("Hooks", "HookEndPlay", true);
        Hooks.HookLocalPlayerExec = get_bool("Hooks", "HookLocalPlayerExec", true);
        Hooks.HookAActorTick = get_bool("Hooks", "HookAActorTick", false);
        Hooks.HookEngineTick = get_bool("Hooks", "HookEngineTick", true);
        Hooks.HookGameViewportClientTick = get_bool("Hooks", "HookGameViewportClientTick", false);
        Hooks.HookUObjectProcessEvent = get_bool("Hooks", "HookUObjectProcessEvent", false);
        Hooks.HookProcessConsoleExec = get_bool("Hooks", "HookProcessConsoleExec", false);
        Hooks.HookUStructLink = get_bool("Hooks", "HookUStructLink", false);
        Hooks.FExecVTableOffsetInLocalPlayer = get_int64("Hooks", "FExecVTableOffsetInLocalPlayer", 0);

        if (auto v = get_str("Hooks", "EngineTickResolveMethod"))
        {
            std::string lower = *v;
            std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c){ return std::tolower(c); });
            if (lower == "vtable") Hooks.EngineTickResolveMethod = Unreal::UnrealInitializer::FunctionResolveMethod::VTable;
            else Hooks.EngineTickResolveMethod = Unreal::UnrealInitializer::FunctionResolveMethod::Scan;
        }

        UE4SS_DBG( "[UE4SS] SettingsManager: INI parsing complete.\n");
#else
        UE4SS_DBG( "[UE4SS] SettingsManager: opening file %s...\n", file_name.string().c_str());
        auto file = File::open(file_name, File::OpenFor::Reading, File::OverwriteExistingFile::No, File::CreateIfNonExistent::Yes);
        UE4SS_DBG( "[UE4SS] SettingsManager: file opened, parsing...\n");
        Ini::Parser parser;
        parser.parse(file);
        UE4SS_DBG( "[UE4SS] SettingsManager: parse done.\n");
        file.close();
        UE4SS_DBG( "[UE4SS] SettingsManager: file closed.\n");

        constexpr static File::CharType section_overrides[] = STR("Overrides");
        UE4SS_DBG( "[UE4SS] SettingsManager: reading Overrides section...\n");
        try
        {
            REGISTER_STRING_SETTING(Overrides.ModsFolderPath, section_overrides, ModsFolderPath)
        }
        catch (std::exception& e)
        {
            UE4SS_DBG( "[UE4SS] SettingsManager: exception in Overrides: %s\n", e.what());
        }
        UE4SS_DBG( "[UE4SS] SettingsManager: Overrides done.\n");

        auto mods_paths_list = parser.get_list(section_overrides);
        mods_paths_list.for_each(STR("ModsFolderPaths"), [](const StringType& key, const Ini::Value& value) {
            if (key.starts_with(STR('+')))
            {
                UE4SSProgram::get_program().add_mods_directory(value.get_string_value());
            }
            else if (key.starts_with(STR('-')))
            {
                UE4SSProgram::get_program().remove_mods_directory(value.get_string_value());
            }
        });

        REGISTER_STRING_SETTING(Overrides.ControllingModsTxt, section_overrides, ControllingModsTxt)
        UE4SS_DBG( "[UE4SS] SettingsManager: reading General section...\n");

        constexpr static File::CharType section_general[] = STR("General");
        REGISTER_BOOL_SETTING(General.EnableHotReloadSystem, section_general, EnableHotReloadSystem)
        UE4SS_DBG( "[UE4SS] SettingsManager: EnableHotReloadSystem done.\n");
        StringType hot_reload_key{};
        REGISTER_STRING_SETTING(hot_reload_key, section_general, HotReloadKey)
        UE4SS_DBG( "[UE4SS] SettingsManager: HotReloadKey done.\n");
        if (!hot_reload_key.empty())
        {
            try
            {
                General.HotReloadKey = Input::string_to_key(hot_reload_key);
            }
            catch (...)
            {
                throw std::runtime_error{fmt::format("Invalid value for 'General.HotReloadKey': {}\n", to_string(hot_reload_key))};
            }
        }
        REGISTER_BOOL_SETTING(General.EnableAutoReloadingLuaMods, section_general, EnableAutoReloadingLuaMods)
        REGISTER_BOOL_SETTING(General.UseCache, section_general, UseCache)
        REGISTER_BOOL_SETTING(General.InvalidateCacheIfDLLDiffers, section_general, InvalidateCacheIfDLLDiffers)
        REGISTER_BOOL_SETTING(General.EnableDebugKeyBindings, section_general, EnableDebugKeyBindings)
        UE4SS_DBG( "[UE4SS] SettingsManager: reading SecondsToScanBeforeGivingUp...\n");
        REGISTER_INT64_SETTING(General.SecondsToScanBeforeGivingUp, section_general, SecondsToScanBeforeGivingUp)
        UE4SS_DBG( "[UE4SS] SettingsManager: SecondsToScanBeforeGivingUp done.\n");
        REGISTER_BOOL_SETTING(General.UseUObjectArrayCache, section_general, bUseUObjectArrayCache)
        REGISTER_BOOL_SETTING(General.DoEarlyScan, section_general, DoEarlyScan)
        REGISTER_BOOL_SETTING(General.SearchByAddress, section_general, bEnableSeachByMemoryAddress)
        StringType default_exec_method_string{};
        REGISTER_STRING_SETTING(default_exec_method_string, section_general, DefaultExecuteInGameThreadMethod)
        if (String::iequal(default_exec_method_string, STR("ProcessEvent")))
        {
            General.DefaultExecuteInGameThreadMethod = GameThreadExecutionMethod::ProcessEvent;
        }
        else if (String::iequal(default_exec_method_string, STR("EngineTick")))
        {
            General.DefaultExecuteInGameThreadMethod = GameThreadExecutionMethod::EngineTick;
        }
        StringType default_fname_to_string_method{};
        REGISTER_STRING_SETTING(default_fname_to_string_method, section_general, DefaultFNameToStringMethod)
        if (String::iequal(default_fname_to_string_method, STR("Scan")))
        {
            General.DefaultFNameToStringMethod = Unreal::UnrealInitializer::FNameToStringMethod::Scan;
        }
        else if (String::iequal(default_fname_to_string_method, STR("Conv_NameToString")))
        {
            General.DefaultFNameToStringMethod = Unreal::UnrealInitializer::FNameToStringMethod::Conv_NameToString;
        }

        constexpr static File::CharType section_engine_version_override[] = STR("EngineVersionOverride");
        REGISTER_INT64_SETTING(EngineVersionOverride.MajorVersion, section_engine_version_override, MajorVersion)
        REGISTER_INT64_SETTING(EngineVersionOverride.MinorVersion, section_engine_version_override, MinorVersion)
        REGISTER_BOOL_SETTING(EngineVersionOverride.DebugBuild, section_engine_version_override, DebugBuild)

        constexpr static File::CharType section_object_dumper[] = STR("ObjectDumper");
        REGISTER_BOOL_SETTING(ObjectDumper.LoadAllAssetsBeforeDumpingObjects, section_object_dumper, LoadAllAssetsBeforeDumpingObjects)
        REGISTER_BOOL_SETTING(ObjectDumper.UseModuleOffsets, section_object_dumper, UseModuleOffsets)

        constexpr static File::CharType section_cxx_header_generator[] = STR("CXXHeaderGenerator");
        REGISTER_BOOL_SETTING(CXXHeaderGenerator.DumpOffsetsAndSizes, section_cxx_header_generator, DumpOffsetsAndSizes)
        REGISTER_BOOL_SETTING(CXXHeaderGenerator.KeepMemoryLayout, section_cxx_header_generator, KeepMemoryLayout)
        REGISTER_BOOL_SETTING(CXXHeaderGenerator.LoadAllAssetsBeforeGeneratingCXXHeaders, section_cxx_header_generator, LoadAllAssetsBeforeGeneratingCXXHeaders)

        constexpr static File::CharType section_uht_header_generator[] = STR("UHTHeaderGenerator");
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.IgnoreAllCoreEngineModules, section_uht_header_generator, IgnoreAllCoreEngineModules)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.IgnoreEngineAndCoreUObject, section_uht_header_generator, IgnoreEngineAndCoreUObject)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeAllFunctionsBlueprintCallable, section_uht_header_generator, MakeAllFunctionsBlueprintCallable)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeAllPropertyBlueprintsReadWrite, section_uht_header_generator, MakeAllPropertyBlueprintsReadWrite)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeEnumClassesBlueprintType, section_uht_header_generator, MakeEnumClassesBlueprintType)
        REGISTER_BOOL_SETTING(UHTHeaderGenerator.MakeAllConfigsEngineConfig, section_uht_header_generator, MakeAllConfigsEngineConfig)

        constexpr static File::CharType section_debug[] = STR("Debug");
        REGISTER_BOOL_SETTING(Debug.SimpleConsoleEnabled, section_debug, ConsoleEnabled)
        REGISTER_BOOL_SETTING(Debug.DebugConsoleEnabled, section_debug, GuiConsoleEnabled)
        REGISTER_BOOL_SETTING(Debug.DebugConsoleVisible, section_debug, GuiConsoleVisible)
        REGISTER_FLOAT_SETTING(Debug.DebugGUIFontScaling, section_debug, GuiConsoleFontScaling)
#ifdef HAS_GUI
        StringType graphics_api_string{};
        REGISTER_STRING_SETTING(graphics_api_string, section_debug, GraphicsAPI)
        if (String::iequal(graphics_api_string, STR("DX11")) || String::iequal(graphics_api_string, STR("D3D11")))
        {
            Debug.GraphicsAPI = GUI::GfxBackend::DX11;
        }
        else if (String::iequal(graphics_api_string, STR("OpenGL")))
        {
            Debug.GraphicsAPI = GUI::GfxBackend::GLFW3_OpenGL3;
        }
        StringType render_mode_string{};
        REGISTER_STRING_SETTING(render_mode_string, section_debug, RenderMode)
        if (String::iequal(render_mode_string, STR("ExternalThread")))
        {
            Debug.RenderMode = GUI::RenderMode::ExternalThread;
        }
        else if (String::iequal(render_mode_string, STR("EngineTick")))
        {
            Debug.RenderMode = GUI::RenderMode::EngineTick;
        }
        else if (String::iequal(render_mode_string, STR("GameViewportClientTick")))
        {
            Debug.RenderMode = GUI::RenderMode::GameViewportClientTick;
        }
#endif

        constexpr static File::CharType section_crash_dump[] = STR("CrashDump");
        REGISTER_BOOL_SETTING(CrashDump.EnableDumping, section_crash_dump, EnableDumping);
        REGISTER_BOOL_SETTING(CrashDump.FullMemoryDump, section_crash_dump, FullMemoryDump);

        constexpr static File::CharType section_threads[] = STR("Threads");
        REGISTER_INT64_SETTING(Threads.SigScannerNumThreads, section_threads, SigScannerNumThreads)
        REGISTER_INT64_SETTING(Threads.SigScannerMultithreadingModuleSizeThreshold, section_threads, SigScannerMultithreadingModuleSizeThreshold)

        constexpr static File::CharType section_memory[] = STR("Memory");
        REGISTER_INT64_SETTING(Memory.MaxMemoryUsageDuringAssetLoading, section_memory, MaxMemoryUsageDuringAssetLoading)

        constexpr static File::CharType section_hooks[] = STR("Hooks");
        REGISTER_BOOL_SETTING(Hooks.HookProcessInternal, section_hooks, HookProcessInternal)
        REGISTER_BOOL_SETTING(Hooks.HookProcessLocalScriptFunction, section_hooks, HookProcessLocalScriptFunction)
        REGISTER_BOOL_SETTING(Hooks.HookLoadMap, section_hooks, HookLoadMap)
        REGISTER_BOOL_SETTING(Hooks.HookInitGameState, section_hooks, HookInitGameState)
        REGISTER_BOOL_SETTING(Hooks.HookCallFunctionByNameWithArguments, section_hooks, HookCallFunctionByNameWithArguments)
        REGISTER_BOOL_SETTING(Hooks.HookBeginPlay, section_hooks, HookBeginPlay)
        REGISTER_BOOL_SETTING(Hooks.HookEndPlay, section_hooks, HookEndPlay)
        REGISTER_BOOL_SETTING(Hooks.HookLocalPlayerExec, section_hooks, HookLocalPlayerExec)
        REGISTER_BOOL_SETTING(Hooks.HookAActorTick, section_hooks, HookAActorTick)
        REGISTER_BOOL_SETTING(Hooks.HookEngineTick, section_hooks, HookEngineTick)
        StringType engine_tick_resolve_method_string{};
        REGISTER_STRING_SETTING(engine_tick_resolve_method_string, section_hooks, EngineTickResolveMethod)
        if (String::iequal(engine_tick_resolve_method_string, STR("VTable")))
        {
            Hooks.EngineTickResolveMethod = Unreal::UnrealInitializer::FunctionResolveMethod::VTable;
        }
        else if (String::iequal(engine_tick_resolve_method_string, STR("Scan")))
        {
            Hooks.EngineTickResolveMethod = Unreal::UnrealInitializer::FunctionResolveMethod::Scan;
        }
        REGISTER_BOOL_SETTING(Hooks.HookGameViewportClientTick, section_hooks, HookGameViewportClientTick)
        REGISTER_BOOL_SETTING(Hooks.HookUObjectProcessEvent, section_hooks, HookUObjectProcessEvent)
        REGISTER_BOOL_SETTING(Hooks.HookProcessConsoleExec, section_hooks, HookProcessConsoleExec)
        REGISTER_BOOL_SETTING(Hooks.HookUStructLink, section_hooks, HookUStructLink)
        REGISTER_INT64_SETTING(Hooks.FExecVTableOffsetInLocalPlayer, section_hooks, FExecVTableOffsetInLocalPlayer)

        constexpr static File::CharType section_experimental_features[] = STR("ExperimentalFeatures");
#endif // __linux__
    }
} // namespace RC
