// ===========================================================================
// UE4SS C++ Mod API — symbol export macro
//
// Marks a function as a UE4SS mod lifecycle entry point. The UE4SS loader
// resolves these symbols by name (dlsym / GetProcAddress) at mod load time.
// The macro expands to the platform-appropriate symbol-visibility attribute
// so the mod's shared library exports only the canonical UE4SS ABI symbols
// (start_mod, uninstall_mod) and keeps everything else hidden.
//
// Design choices:
//
//   - Source-level mechanism (macro) is the primary export path. The
//     ue4ss_add_mod() CMake function also applies a linker version script
//     as a defense-in-depth fallback for mods that forget the macro.
//     Either mechanism alone is sufficient; both together are robust.
//
//   - -fvisibility=hidden is set by ue4ss_add_mod() on non-Windows targets.
//     This is the modern best practice for shared libraries: hide everything
//     by default, opt specific symbols back in. It prevents the mod from
//     accidentally exporting internal helpers that might collide with the
//     host process or with other mods.
//
//   - -static-libstdc++ is set by ue4ss_add_mod(). This is critical: the
//     mod embeds its own C++ standard library, so it doesn't depend on
//     the host's libstdc++ version. Without this, a mod built with GCC 13
//     (GLIBCXX_3.4.32) will fail to load on a host with GCC 12
//     (GLIBCXX_3.4.30) due to missing symbols, even if the mod never
//     directly uses a C++17/20/23 feature.
//
// Usage:
//
//   #include <UE4SS/mod_api.h>
//   #include <Mod/CppUserModBase.hpp>
//
//   class MyMod : public RC::CppUserModBase { ... };
//
//   // The extern "C" block prevents C++ name mangling so the loader
//   // can find the symbols by their plain names ("start_mod", "uninstall_mod").
//   // Omitting it is a common mistake that causes "symbol not found" at
//   // mod load time.
//   extern "C"
//   {
//       UE4SS_MOD_API RC::CppUserModBase* start_mod()
//       {
//           return new MyMod();
//       }
//
//       UE4SS_MOD_API void uninstall_mod(RC::CppUserModBase* mod)
//       {
//           delete mod;
//       }
//   }
//
// ===========================================================================

#pragma once

// Defensive: if a mod defines its own conflicting export macro, refuse to
// compile rather than silently produce a broken mod.
#ifdef UE4SS_MOD_API
    #error "UE4SS_MOD_API is already defined. Remove the conflicting definition."
#endif

// MSVC and compatible: __declspec(dllexport) places the symbol in the
// DLL's export table. The loader finds it via GetProcAddress.
#if defined(_WIN32) || defined(__CYGWIN__)
    #define UE4SS_MOD_API __declspec(dllexport)

// GCC and Clang on ELF: visibility("default") makes the symbol part of
// the dynamic symbol table even when the default visibility is hidden.
// Requires -fvisibility=hidden (set by ue4ss_add_mod()).
#elif defined(__GNUC__) || defined(__clang__)
    #define UE4SS_MOD_API __attribute__((visibility("default")))

#else
    #error "UE4SS_MOD_API: unsupported compiler. Add a platform branch here."
#endif
