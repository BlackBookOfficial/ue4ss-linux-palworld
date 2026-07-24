#pragma once

#include <vector>

#ifdef _WIN32
#include <Unreal/Core/Windows/MinimalWindowsApi.hpp>
#else
// On Linux, HMODULE is just void*
using HMODULE = void*;
#endif

#include <Mod/CppUserModBase.hpp>
#include <Mod/Mod.hpp>

#include <String/StringType.hpp>

namespace RC
{
    namespace LuaMadeSimple
    {
        class Lua;
    }

    class CppMod : public Mod
    {
      private:
        typedef CppUserModBase* (*start_type)();
        typedef void (*uninstall_type)(CppUserModBase*);

      private:
        StringType m_lib_filename{};
        std::filesystem::path m_libs_path;

#ifdef _WIN32
        Unreal::Windows::HMODULE m_main_lib_module = NULL;
#else
        void* m_main_lib_module = nullptr;
#endif
        void* m_libs_path_cookie = nullptr;
        start_type m_start_mod_func = nullptr;
        uninstall_type m_uninstall_mod_func = nullptr;

        CppUserModBase* m_mod = nullptr;

      public:
        CppMod(UE4SSProgram&, StringType&& mod_name, StringType&& mod_path);
        CppMod(CppMod&) = delete;
        CppMod(CppMod&&) = delete;
        ~CppMod() override;

      public:
        auto start_mod() -> void override;
        auto uninstall() -> void override;

        auto fire_on_lua_start(StringViewType mod_name,
                               LuaMadeSimple::Lua& lua,
                               LuaMadeSimple::Lua& main_lua,
                               LuaMadeSimple::Lua& async_lua,
                               LuaMadeSimple::Lua* hook_lua) -> void;

        auto fire_on_lua_start(LuaMadeSimple::Lua& lua, LuaMadeSimple::Lua& main_lua, LuaMadeSimple::Lua& async_lua, LuaMadeSimple::Lua* hook_lua) -> void;

        auto fire_on_lua_stop(StringViewType mod_name,
                              LuaMadeSimple::Lua& lua,
                              LuaMadeSimple::Lua& main_lua,
                              LuaMadeSimple::Lua& async_lua,
                              LuaMadeSimple::Lua* hook_lua) -> void;

        auto fire_on_lua_stop(LuaMadeSimple::Lua& lua, LuaMadeSimple::Lua& main_lua, LuaMadeSimple::Lua& async_lua, LuaMadeSimple::Lua* hook_lua) -> void;

        auto fire_unreal_init() -> void override;
        auto fire_ui_init() -> void override;
        auto fire_program_start() -> void override;
        auto fire_update() -> void override;
        auto fire_lib_load(StringViewType lib_name) -> void;
        auto fire_on_cpp_mods_loaded() -> void;
    };
} // namespace RC
