cmake_minimum_required(VERSION 3.22)

set(TARGET Unreal)
project(${TARGET})

option(UE4SS_${TARGET}_BUILD_SHARED "Build as a shared lib" OFF)
option(UE_HOOK_TEST "Enable unit tests for hook system" OFF)

file(GLOB_RECURSE SOURCES src/**.cpp)
file(GLOB_RECURSE GENERATED_SOURCES generated_src/**.cpp)

if(NOT WIN32)
    list(FILTER SOURCES EXCLUDE REGEX "/Microsoft/")
    list(FILTER SOURCES EXCLUDE REGEX "/Windows/")
endif()

set(${TARGET}_Sources
        ${SOURCES}
        ${GENERATED_SOURCES}
        )

string(REGEX REPLACE "(.)([A-Z])" "\\1_\\2" MODULE_NAME ${TARGET})
string(TOUPPER ${MODULE_NAME} MODULE_NAME)

if (UE4SS_${TARGET}_BUILD_SHARED)
    message("Project: ${TARGET} (SHARED)")
    add_library(${TARGET} SHARED ${${TARGET}_Sources})
else ()
    message("Project: ${TARGET} (STATIC)")
    add_library(${TARGET} ${${TARGET}_Sources})
endif ()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${TARGET} PRIVATE 
        -Wno-unused-variable
        -Wno-unused-parameter
        -Wno-unused-function
        -Wno-unused-but-set-variable
        -Wno-unknown-pragmas # Consider removing and fixing issues
        -Wno-switch
        -Wno-unused-private-field # Consider removing and fixing issues
        -Wno-changes-meaning # GCC 15: member variables with same name as their type
    )
endif()

# Enabling c++23 support
target_compile_features(${TARGET} PUBLIC cxx_std_23)

target_compile_definitions(${TARGET} PRIVATE
    RC_${MODULE_NAME}_EXPORTS
    $<$<NOT:$<BOOL:${UE4SS_${TARGET}_BUILD_SHARED}>>:
        RC_${MODULE_NAME}_BUILD_STATIC>)

if (NOT ${UE4SS_${TARGET}_BUILD_SHARED})
    target_compile_definitions(${TARGET} PRIVATE
            RC_ASM_HELPER_BUILD_STATIC
            RC_FILE_BUILD_STATIC
            RC_DYNAMIC_OUTPUT_BUILD_STATIC
            RC_SINGLE_PASS_SIG_SCANNER_BUILD_STATIC
    )
endif ()

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/generated_include ${CMAKE_CURRENT_SOURCE_DIR}/include/Unreal ${CMAKE_CURRENT_SOURCE_DIR}/include/Unreal/Core)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/generated_include)

file(GLOB_RECURSE UE4SS_HEADERS include/**.hpp generated_include/**.hpp)
target_sources(${TARGET} PUBLIC
    FILE_SET unreal_headers TYPE HEADERS
    BASE_DIRS include generated_include
    FILES ${UE4SS_HEADERS})
get_property("TARGET_SOURCE_FILES" TARGET "${TARGET}" PROPERTY SOURCES)
source_group(TREE "${CMAKE_CURRENT_LIST_DIR}" FILES ${TARGET_SOURCE_FILES} ${UE4SS_HEADERS})

if(${UE4SS_${TARGET}_BUILD_SHARED} EQUAL 0)
    target_compile_definitions(${TARGET} PUBLIC ZYDIS_STATIC_DEFINE ZYCORE_STATIC_DEFINE)
endif()


target_link_libraries(${TARGET} PUBLIC fmt File DynamicOutput SinglePassSigScanner Constructs Helpers Function)
if(WIN32)
    target_link_libraries(${TARGET} PUBLIC PolyHook_2 ASMHelper)
else()
    target_link_libraries(${TARGET} PUBLIC ASMHelper funchook)
    # Ensure funchook headers are findable even if funchook target doesn't propagate include dirs
    if(DEFINED funchook_SOURCE_DIR)
        target_include_directories(${TARGET} PUBLIC ${funchook_SOURCE_DIR}/include)
    endif()
endif()

# Add natvis file for Visual Studio debugging (works with MSVC and clang-cl)
if(MSVC OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
    target_sources(${TARGET} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/UEPseudo.natvis>
    )
endif()

if(UE_HOOK_TEST)
    target_compile_definitions(${TARGET} PUBLIC UE_HOOK_TEST)
endif ()
