# UE4SS Linux Native Port - Changelog

## v3.0.2 - Bug Fixes (2026-07-19)

### Bug Fixes
- **FText crash fix**: Fixed SIGSEGV in `setup_lua_classes_internal` caused by `FText::StaticSize_Private` being uninitialized on Linux (set to `sizeof(FText)` as fallback)
- **FilesystemWatcher path fix**: Fixed empty paths being passed to `inotify_add_watch` due to `u16string_view` to `filesystem::path` conversion issues — now uses `mod->get_path()` directly
- **FilesystemWatcher inotify fd leak**: Fixed inotify file descriptor being overwritten on each path — now creates fd only once and reuses for all watches
- **FilesystemWatcher poll fix**: Removed unnecessary STDIN polling that consumed server input; replaced `std::exit(EXIT_FAILURE)` with graceful error handling
- **Case sensitivity fix**: Use lowercase `scripts` directory on Linux (case-sensitive filesystems)
- **Per-mod crash recovery**: SIGSEGV in one mod no longer prevents subsequent mods from loading — each mod is wrapped in `sigsetjmp`/`siglongjmp` recovery

### Improvements
- Added granular stderr logging during mod startup on Linux for debugging
- Settings manager uses hardcoded defaults on Linux when INI file is not present

---

## v3.0.1 - Linux Native Build (2026-07-18)

### Features
- **Linux Native Build**: UE4SS now compiles natively on Linux (GCC 15 / Clang)
- **LD_PRELOAD Entry Point**: Linux entry point via `__attribute__((constructor))` for LD_PRELOAD
- **Headless Mode**: GUI and input systems can be disabled via CMake options (`UE4SS_GUI_ENABLED=OFF`, `UE4SS_INPUT_ENABLED=OFF`)
- **Cross-Platform Abstraction**: New `PlatformCompat.hpp` for cross-platform abstractions
- **POSIX File Implementation**: Full `LinuxFile.cpp` implementation with POSIX file operations
- **Linux CrashDumper**: Ported to Linux signal handlers + backtrace
- **Linux CppMod**: Ported to `dlopen`/`dlsym`/`dlclose`
- **Linux SigScanner**: Ported to direct memory scanning (without VirtualQuery)
- **GitHub Actions CI**: Linux CI workflow for gcc + clang (Debug + Shipping)

### Bug Fixes
- `to_wstring` now returns `std::u16string` when `FORCE_U16` is defined (instead of `std::wstring`)
- Fixed `wstring_convert` template parameters for `char16_t` element type
- Fixed `LuaMadeSimple` template instantiation for GCC (`long int` handling)
- Fixed `std::stoi` in `MacroSetter.hpp` for `u16string` conversion
- Fixed `basic_ifstream<char16_t>` BOM skip with `read()` instead of `get()` (not available for `char16_t`)
- Replaced MSVC-specific functions (`printf_s` -> `std::printf`, `strncpy_s` -> `strncpy`)
- Replaced `to_address` on function pointers with `reinterpret_cast<uintptr_t>`
- Enabled `CMAKE_POSITION_INDEPENDENT_CODE` globally for static libraries linked into shared libraries
- Filtered Windows-only source files on Linux
- Changed `wchar_t` to `CharType` / `StringType` for Linux compatibility
- Changed `std::filesystem::path` to `StringType` for `LuaMod` constructor calls
- `SysError.cpp`: Changed `std::wregex` to `std::basic_regex<CharType>` for `char16_t`

### Build System
- `CMakeLists.txt`: Global `-fPIC` enablement
- `ProjectConfig.cmake`: Added Linux64 platform type
- `UE4SS/CMakeLists.txt`: Conditional Windows-only dependencies, `dl`/`pthread` for Linux
- `deps/third/CMakeLists.txt`: GLFW/glad/ImGui/PolyHook/raw_pdb conditional on WIN32
- `File/CMakeLists.txt`: Platform-specific source files
- `CompilerOptions`: Fixed `gnu.cmake` (removed `-fms-extensions`), `clang.cmake` (`gcodeview` Windows-only)

### Known Limitations
- GUI is disabled in the Linux build (headless mode)
- UEPseudo submodule requires Epic Games GitHub org access
- C++ mods must be compiled as `.so` (not `.dll`)
