// EventViewerMod: mod entry point.
//
// The actual mod logic lives in EventViewer.cpp. This file exists to
// expose the two functions the UE4SS loader resolves by name:
//   - start_mod:     called once when the mod is loaded; returns the
//                    mod instance.
//   - uninstall_mod: called once when the mod is being unloaded; the
//                    mod is responsible for cleaning up its state.
//
// The UE4SS_MOD_API macro (from <UE4SS/mod_api.h>) handles the
// platform-specific symbol export. On Windows it expands to
// __declspec(dllexport); on Linux to __attribute__((visibility("default"))).
// The extern "C" block prevents C++ name mangling so the loader can
// find the symbols by their plain names.
//
// As a defense-in-depth fallback, the mod's CMakeLists.txt applies a
// linker version script (via ue4ss_add_mod) that exports start_mod and
// uninstall_mod by name even if this macro were missing.

#include <UE4SS/mod_api.h>

#include <EventViewer.hpp>

extern "C"
{
    UE4SS_MOD_API RC::CppUserModBase* start_mod()
    {
        return new EventViewerMod::EventViewerMod();
    }

    UE4SS_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
    {
        delete mod;
    }
}
