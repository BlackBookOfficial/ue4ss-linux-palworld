cmake_minimum_required(VERSION 3.22)
project(EventViewerMod LANGUAGES CXX)

# Fetch the concurrentqueue header-only library used by the event viewer.
include(FetchContent)
FetchContent_Declare(
        concurrentqueue
        GIT_REPOSITORY https://github.com/cameron314/concurrentqueue.git
        GIT_TAG c68072129c8a5b4025122ca5a0c82ab14b30cb03
)
FetchContent_MakeAvailable(concurrentqueue)

# ue4ss_add_mod() handles cross-platform symbol export, -fvisibility=hidden,
# the linker version script, and -static-libstdc++. See Ue4ssAddMod.cmake
# for the full design rationale.
include(Ue4ssAddMod)

ue4ss_add_mod(EventViewerMod
        src/dllmain.cpp
        src/EventViewer.cpp
        src/Middleware.cpp
        src/Client.cpp
        src/Structs.cpp
        src/StringPool.cpp
        src/EntryCallStackRenderer.cpp
        src/FilterCountRenderer.cpp
)
target_link_libraries(EventViewerMod PRIVATE concurrentqueue String Unreal Input)
target_include_directories(EventViewerMod PRIVATE "include")
target_link_libraries(EventViewerMod PRIVATE ImGui)
