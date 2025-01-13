cmake_minimum_required(VERSION 3.14)
project(MyDLL)

# C++ Standard setzen
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MinHook Pfad relativ zum CMake-Projektverzeichnis
set(MINHOOK_DIR ${CMAKE_SOURCE_DIR}/MinHook)

# Suche alle .cpp-Dateien im aktuellen Verzeichnis
file(GLOB SOURCES "src/*.cpp")
file(GLOB MODELS_SOURCES "src/Models/*.cpp")
file(GLOB LOGIC_SOURCES "src/Logic/*.cpp")
file(GLOB WRAPPER_SOURCES "src/Wrapper/*.cpp")
file(GLOB NETWORK_SOURCES "src/Network/*.cpp")

# Dear ImGui Quellen und Header definieren
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_dx11.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp
)

# MinHook Quellen und Bibliotheken
set(MINHOOK_LIB ${MINHOOK_DIR}/libMinHook.x86.lib)

# C-Runtime explizit festlegen
# Für Debug müssen wir die statische Debug C-Runtime verwenden
# Für Release die statische C-Runtime

# Debug
#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MTd")  # Statische C-Runtime für Debug
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT /NODEFAULTLIB:LIBCMTD")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT /NODEFAULTLIB:LIBCMTD")
#elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")  # Statische C-Runtime für Release
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT")
#    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT")
#endif()

# Bibliothek erstellen (DLL)
add_library(MyDLL SHARED ${SOURCES} ${IMGUI_SOURCES} ${MODELS_SOURCES} ${LOGIC_SOURCES} ${WRAPPER_SOURCES} ${NETWORK_SOURCES})

# Include-Verzeichnisse hinzufügen
target_include_directories(MyDLL PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_BACKENDS_DIR}
    ${MINHOOK_DIR}  # MinHook Header hinzufügen
)

# Linke notwendige Bibliotheken für Dear ImGui und MinHook
target_link_libraries(MyDLL d3d11 dxgi dxguid ${MINHOOK_LIB})  # MinHook Bibliothek verlinken
