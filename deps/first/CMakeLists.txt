# First party dependencies -> START
add_subdirectory("ArgsParser")
add_subdirectory("ASMHelper")
add_subdirectory("Constructs")
add_subdirectory("String")
add_subdirectory("DynamicOutput")
add_subdirectory("File")
add_subdirectory("Function")
add_subdirectory("Helpers")
add_subdirectory("IniParser")
add_subdirectory("Input")
add_subdirectory("JSON")
# Compile Lua as C++ so that C++ exceptions can safely propagate through Lua C API frames.
# Without this, any C++ exception thrown inside a Lua callback (e.g. from FName::ToString)
# results in undefined behavior and typically a SIGSEGV crash on Linux.
set(LUA_COMPILE_AS_CPP ON CACHE BOOL "Compile Lua as C++ instead of C" FORCE)
add_subdirectory("LuaMadeSimple")
add_subdirectory("LuaRaw")
add_subdirectory("MProgram")
add_subdirectory("ParserBase")
add_subdirectory("ScopedTimer")
add_subdirectory("SinglePassSigScanner")
add_subdirectory("Unreal")
add_subdirectory("Profiler")

# Add our Rust components for IDE visibility
if(DEFINED ENABLE_IDE_SOURCE_VISIBILITY AND ENABLE_IDE_SOURCE_VISIBILITY)
    # We only need to include patternsleuth_bind directly for IDE visibility
    # Both patternsleuth and patternsleuth_bind IDE visibility are handled there
    # The actual build is still handled by Corrosion
    #add_subdirectory("patternsleuth_bind")
endif()
# First party dependencies -> END

# Organize generic Rust targets into deps/rust
# Uses organize_targets() from cmake/modules/IDEOrganization.cmake
organize_targets("^cargo-clean$|^cargo-prebuild$" "deps/rust")
