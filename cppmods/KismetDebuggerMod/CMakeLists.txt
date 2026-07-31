cmake_minimum_required(VERSION 3.22)
project(KismetDebuggerMod LANGUAGES CXX)

# ue4ss_add_mod() handles cross-platform symbol export, -fvisibility=hidden,
# the linker version script, and -static-libstdc++. See Ue4ssAddMod.cmake
# for the full design rationale.
include(Ue4ssAddMod)

ue4ss_add_mod(KismetDebuggerMod
        src/dllmain.cpp
        src/KismetDebugger.cpp
)

target_link_libraries(KismetDebuggerMod PRIVATE ImGui Unreal String Input)
target_link_libraries(KismetDebuggerMod PRIVATE ImGui Unreal String)
