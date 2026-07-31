#include <string>

#include <GUI/GUITab.hpp>
#include <Mod/CppUserModBase.hpp>
#include <UE4SSProgram.hpp>
#include <KismetDebugger.hpp>

class KismetDebuggerMod : public RC::CppUserModBase
{
private:
    RC::GUI::KismetDebuggerMod::Debugger m_debugger{};

public:
    KismetDebuggerMod() : CppUserModBase()
    {
        ModName = STR("KismetDebugger");
        ModVersion = STR("1.0");
        ModDescription = STR("Debugging interface for kismet bytecode");
        ModAuthors = STR("truman");

        register_tab(STR("Kismet Debugger"), [](CppUserModBase* mod) {
            UE4SS_ENABLE_IMGUI()
            dynamic_cast<KismetDebuggerMod*>(mod)->m_debugger.render();
        });
    }

    ~KismetDebuggerMod() override = default;
};

// The UE4SS_MOD_API macro (from <UE4SS/mod_api.h>) handles the
// platform-specific symbol export. On Windows it expands to
// __declspec(dllexport); on Linux to __attribute__((visibility("default"))).
// The extern "C" block prevents C++ name mangling so the loader can
// find the symbols by their plain names. The linker version script
// applied by ue4ss_add_mod() is a defense-in-depth fallback.
#include <UE4SS/mod_api.h>

extern "C"
{
    UE4SS_MOD_API RC::CppUserModBase* start_mod()
    {
        return new KismetDebuggerMod();
    }

    UE4SS_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}

