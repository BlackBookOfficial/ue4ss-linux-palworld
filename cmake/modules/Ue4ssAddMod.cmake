# ===========================================================================
# ue4ss_add_mod() — CMake function for building UE4SS C++ mods
#
# Creates a shared library for a UE4SS C++ mod with the correct cross-
# platform symbol-export settings. Mod authors should use this instead of
# add_library() so that symbol visibility, the linker version script, and
# static-libstdc++ linking are all configured consistently.
#
# Usage:
#
#   include(Ue4ssAddMod)
#
#   ue4ss_add_mod(MyMod
#       src/dllmain.cpp
#       src/MyMod.cpp
#   )
#
#   target_include_directories(MyMod PRIVATE "include")
#   target_link_libraries(MyMod PRIVATE some_dependency)
#
# What this function does (on non-Windows targets):
#
#   1. Sets -fvisibility=hidden as the default for all symbols. The
#      UE4SS_MOD_API macro (from <UE4SS/mod_api.h>) opts specific
#      symbols back in to default visibility.
#
#   2. Applies a linker version script that exports only start_mod and
#      uninstall_mod. This is a fallback for mods that don't use the
#      macro; either mechanism alone produces a correct mod .so.
#
#   3. Links the C++ standard library statically (-static-libstdc++
#      -static-libgcc). The mod embeds its own libstdc++ and libgcc,
#      so it doesn't depend on the host's versions. This is the
#      difference between a mod that loads on any Linux box and a mod
#      that only loads on the same distro it was built on.
#
#   4. Makes UE4SS headers available. If the UE4SS target is defined
#      (normal in-tree build), links against it to propagate include
#      directories. If not (standalone build processed before the main
#      project), adds the UE4SS include directory directly using a
#      path computed from this file's own location.
#
# ===========================================================================

include_guard(GLOBAL)

# Cache the absolute path to the version script so the function works
# regardless of which directory the mod's CMakeLists.txt is in.
get_filename_component(_ue4ss_add_mod_dir "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
set(UE4SS_MOD_EXPORTS_MAP "${_ue4ss_add_mod_dir}/ue4ss_mod_exports.map"
    CACHE INTERNAL "UE4SS mod linker version script" FORCE)

function(ue4ss_add_mod target_name)
    add_library(${target_name} SHARED ${ARGN})

    # Make UE4SS headers available. Prefer linking against the target
    # (which propagates PUBLIC include directories); fall back to
    # adding the include path directly if the target isn't defined yet.
    if(TARGET UE4SS)
        target_link_libraries(${target_name} PUBLIC UE4SS)
    else()
        get_filename_component(_ue4ss_mod_cmake_dir "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
        get_filename_component(_ue4ss_mod_root "${_ue4ss_mod_cmake_dir}/../.." ABSOLUTE)
        target_include_directories(${target_name} PRIVATE
            "${_ue4ss_mod_root}/UE4SS/include"
        )
    endif()

    if(NOT WIN32)
        # Default visibility hidden. The UE4SS_MOD_API macro opts
        # start_mod / uninstall_mod back in to default visibility.
        target_compile_options(${target_name} PRIVATE
            -fvisibility=hidden
            -fvisibility-inlines-hidden
        )

        # Fallback: even if the mod forgot the macro, the linker
        # version script still exports the canonical ABI symbols.
        target_link_options(${target_name} PRIVATE
            "-Wl,--version-script=${UE4SS_MOD_EXPORTS_MAP}"
        )

        # Embed the C++ standard library so the mod doesn't depend
        # on the host's libstdc++/libgcc versions. Critical for
        # portability across distros.
        target_link_options(${target_name} PRIVATE
            -static-libstdc++
            -static-libgcc
        )
    endif()

    # Match UE4SS's C++ standard.
    target_compile_features(${target_name} PUBLIC cxx_std_23)

    # UE4SS's mod loader looks for main.so, lib<Name>.so, or <Name>.so.
    # The default CMake target name produces lib<Name>.so which is
    # already in the lookup list, but we set PREFIX explicitly so the
    # output is predictable.
    set_target_properties(${target_name} PROPERTIES
        PREFIX ""
    )
endfunction()
