#define NOMINMAX

#include <filesystem>
#include <cstdio>
#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <DynamicOutput/DynamicOutput.hpp>
#include <Helpers/SysError.hpp>
#include <Helpers/String.hpp>
#include <Mod/CppMod.hpp>

namespace RC
{
    CppMod::CppMod(UE4SSProgram& program, StringType&& mod_name, StringType&& mod_path) : Mod(program, std::move(mod_name), std::move(mod_path))
    {
#ifdef _WIN32
        m_libs_path = m_mod_path / STR("dlls");
#else
        m_libs_path = m_mod_path / STR("libs");
#endif

        if (!std::filesystem::exists(m_libs_path))
        {
            Output::send<LogLevel::Warning>(STR("Could not find the libraries folder for mod {}\n"), m_mod_name);
            set_installable(false);
            return;
        }

#ifdef _WIN32
        auto lib_path = m_libs_path / STR("main.dll");
        if (!std::filesystem::exists(lib_path))
        {
            lib_path = m_libs_path / fmt::format(STR("{}.dll"), mod_name);

            if (!std::filesystem::exists(lib_path))
            {
                Output::send<LogLevel::Warning>(STR("Failed to load C++ mod {}, dlls folder must contain either main.dll or {}\n"),
                                                m_mod_name, ensure_str(lib_path.filename()));
                set_installable(false);
                return;
            }
        }
#else
        auto lib_path = m_libs_path / STR("main.so");
        if (!std::filesystem::exists(lib_path))
        {
            lib_path = m_libs_path / fmt::format(STR("lib{}.so"), mod_name);

            if (!std::filesystem::exists(lib_path))
            {
                lib_path = m_libs_path / fmt::format(STR("{}.so"), mod_name);

                if (!std::filesystem::exists(lib_path))
                {
                    Output::send<LogLevel::Warning>(STR("Failed to load C++ mod {}, libs folder must contain either main.so or lib{}.so\n"),
                                                    m_mod_name, m_mod_name);
                    set_installable(false);
                    return;
                }
            }
        }
#endif

        m_lib_filename = ensure_str(lib_path.filename());

#ifdef _WIN32
        // Add mods libraries directory to search path for dynamic/shared linked libraries in mods
        m_libs_path_cookie = AddDllDirectory(m_libs_path.c_str());
        m_main_lib_module = LoadLibraryExW(lib_path.c_str(), NULL, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);

        if (!m_main_lib_module)
        {
            Output::send<LogLevel::Warning>(STR("Failed to load library <{}> for mod {}, error: {}\n"),
                                            ensure_str(lib_path), m_mod_name, SysError(GetLastError()).c_str());
            set_installable(false);
            return;
        }

        m_start_mod_func = reinterpret_cast<start_type>(GetProcAddress(m_main_lib_module, "start_mod"));
        m_uninstall_mod_func = reinterpret_cast<uninstall_type>(GetProcAddress(m_main_lib_module, "uninstall_mod"));
#else
        auto lib_path_utf8 = lib_path.string();
        m_main_lib_module = dlopen(lib_path_utf8.c_str(), RTLD_LAZY | RTLD_GLOBAL);

        if (!m_main_lib_module)
        {
            const char* err = dlerror();
            Output::send<LogLevel::Warning>(STR("Failed to load library <{}> for mod {}, error: {}\n"),
                                            ensure_str(lib_path), m_mod_name, ensure_str(err ? err : "unknown"));
            set_installable(false);
            return;
        }

        m_start_mod_func = reinterpret_cast<start_type>(dlsym(m_main_lib_module, "start_mod"));
        m_uninstall_mod_func = reinterpret_cast<uninstall_type>(dlsym(m_main_lib_module, "uninstall_mod"));
#endif

        if (!m_start_mod_func || !m_uninstall_mod_func)
        {
            Output::send<LogLevel::Warning>(STR("Failed to find exported mod lifecycle functions for mod {}\n"), m_mod_name);

#ifdef _WIN32
            FreeLibrary(m_main_lib_module);
#else
            dlclose(m_main_lib_module);
#endif
            m_main_lib_module = nullptr;

            set_installable(false);
            return;
        }
    }

    auto CppMod::start_mod() -> void
    {
        try
        {
            m_mod = m_start_mod_func();
            m_is_started = m_mod != nullptr;
        }
        catch (std::exception& e)
        {
            if (!Output::has_internal_error())
            {
                Output::send<LogLevel::Warning>(STR("Failed to load library <{}> for mod {}, because: {}\n"),
                                                ensure_str((m_libs_path / m_lib_filename)),
                                                m_mod_name,
                                                ensure_str(e.what()));
            }
            else
            {
                std::printf("Internal Error: %s\n", e.what());
            }
        }
    }

    auto CppMod::uninstall() -> void
    {
        Output::send(STR("Stopping C++ mod '{}' for uninstall\n"), m_mod_name);
        if (m_mod && m_uninstall_mod_func)
        {
            m_uninstall_mod_func(m_mod);
        }
    }

    auto CppMod::fire_on_lua_start(StringViewType mod_name,
                                   LuaMadeSimple::Lua& lua,
                                   LuaMadeSimple::Lua& main_lua,
                                   LuaMadeSimple::Lua& async_lua,
                                   LuaMadeSimple::Lua* hook_lua) -> void
    {
        if (m_mod)
        {
            // Call new API
            m_mod->on_lua_start(mod_name, lua, main_lua, async_lua, hook_lua);

            // Call old deprecated API for backwards compatibility
            std::vector<LuaMadeSimple::Lua*> hook_luas;
            if (hook_lua)
            {
                hook_luas.push_back(hook_lua);
            }
            m_mod->on_lua_start(mod_name, lua, main_lua, async_lua, hook_luas);
        }
    }

    auto CppMod::fire_on_lua_start(LuaMadeSimple::Lua& lua,
                                   LuaMadeSimple::Lua& main_lua,
                                   LuaMadeSimple::Lua& async_lua,
                                   LuaMadeSimple::Lua* hook_lua) -> void
    {
        if (m_mod)
        {
            // Call new API
            m_mod->on_lua_start(lua, main_lua, async_lua, hook_lua);

            // Call old deprecated API for backwards compatibility
            std::vector<LuaMadeSimple::Lua*> hook_luas;
            if (hook_lua)
            {
                hook_luas.push_back(hook_lua);
            }
            m_mod->on_lua_start(lua, main_lua, async_lua, hook_luas);
        }
    }

    auto CppMod::fire_on_lua_stop(StringViewType mod_name,
                                  LuaMadeSimple::Lua& lua,
                                  LuaMadeSimple::Lua& main_lua,
                                  LuaMadeSimple::Lua& async_lua,
                                  LuaMadeSimple::Lua* hook_lua) -> void
    {
        if (m_mod)
        {
            // Call new API
            m_mod->on_lua_stop(mod_name, lua, main_lua, async_lua, hook_lua);

            // Call old deprecated API for backwards compatibility
            std::vector<LuaMadeSimple::Lua*> hook_luas;
            if (hook_lua)
            {
                hook_luas.push_back(hook_lua);
            }
            m_mod->on_lua_stop(mod_name, lua, main_lua, async_lua, hook_luas);
        }
    }

    auto CppMod::fire_on_lua_stop(LuaMadeSimple::Lua& lua, LuaMadeSimple::Lua& main_lua, LuaMadeSimple::Lua& async_lua, LuaMadeSimple::Lua* hook_lua) -> void
    {
        if (m_mod)
        {
            // Call new API
            m_mod->on_lua_stop(lua, main_lua, async_lua, hook_lua);

            // Call old deprecated API for backwards compatibility
            std::vector<LuaMadeSimple::Lua*> hook_luas;
            if (hook_lua)
            {
                hook_luas.push_back(hook_lua);
            }
            m_mod->on_lua_stop(lua, main_lua, async_lua, hook_luas);
        }
    }

    auto CppMod::fire_unreal_init() -> void
    {
        if (m_mod)
        {
            m_mod->on_unreal_init();
        }
    }

    auto CppMod::fire_ui_init() -> void
    {
        if (m_mod)
        {
            m_mod->on_ui_init();
        }
    }

    auto CppMod::fire_program_start() -> void
    {
        if (m_mod)
        {
            m_mod->on_program_start();
        }
    }

    auto CppMod::fire_update() -> void
    {
        if (m_mod)
        {
            m_mod->on_update();
        }
    }

    auto CppMod::fire_lib_load(StringViewType lib_name) -> void
    {
        if (m_mod)
        {
            m_mod->on_lib_load(lib_name);
        }
    }

    auto CppMod::fire_on_cpp_mods_loaded() -> void
    {
        if (m_mod)
        {
            m_mod->on_cpp_mods_loaded();
        }
    }

    CppMod::~CppMod()
    {
        if (m_main_lib_module)
        {
#ifdef _WIN32
            FreeLibrary(m_main_lib_module);
            RemoveDllDirectory(m_libs_path_cookie);
#else
            dlclose(m_main_lib_module);
#endif
        }
    }
} // namespace RC
