cmake_minimum_required(VERSION 3.22)

set(TARGET proxy_generator)
project(${TARGET})

add_executable(${TARGET} "main.cpp")
target_link_libraries(${TARGET} PRIVATE Constructs File)
if(WIN32)
    target_link_libraries(${TARGET} PRIVATE imagehlp)
endif()
target_compile_definitions(${TARGET} PRIVATE RC_FILE_BUILD_STATIC)

# Directly set folder for proxy_generator to Programs/proxy
set_target_properties(${TARGET} PROPERTIES FOLDER "Programs/proxy")

# proxy subdirectory uses MASM ASM and .rc resources (Windows-only)
if(WIN32)
    add_subdirectory("proxy")
endif()
