cmake_minimum_required(VERSION 3.14)
project(MyDLL)

# C++ Standard setzen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# |--------------------------Network shit----------------------------| # 

if(POLICY CMP0144)
    cmake_policy(SET CMP0144 NEW)
endif()
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD) # Für Kompatibilität mit dem alten FindBoost-Modul
endif()


if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00) # config for win 10
    # Boost konfigurieren
    set(BOOST_ROOT "C:/Program Files/boost_1_87_0")
    set(BOOST_INCLUDEDIR "${BOOST_ROOT}/boost")
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")
elseif(UNIX)
    # Linux-spezifische Einstellungen
    set(BOOST_INCLUDEDIR "/usr/include")
    set(BOOST_LIBRARYDIR "/usr/lib")
endif()


find_package(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND)
    message(STATUS "Boost gefunden: ${Boost_VERSION}")
    message(STATUS "Boost Include-Verzeichnis: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost Bibliotheken: ${Boost_LIBRARIES}")
else()
    message(FATAL_ERROR "Boost konnte nicht gefunden werden")
endif()




# |------------------------------------------------------------------| # 




# MinHook Pfad relativ zum CMake-Projektverzeichnis
set(MINHOOK_DIR ${CMAKE_SOURCE_DIR}/MinHook)

# Suche alle .cpp-Dateien im aktuellen Verzeichnis
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE COMMON_SOURCES "common/src/*.cpp")

list(APPEND SOURCES ${COMMON_SOURCES})
include_directories("common/src/")


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
add_library(MyDLL SHARED ${SOURCES} ${IMGUI_SOURCES})

# Include-Verzeichnisse hinzufügen
target_include_directories(MyDLL PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_BACKENDS_DIR}
    ${MINHOOK_DIR}  # MinHook Header hinzufügen
    ${Boost_INCLUDE_DIRS}
)

# Linke notwendige Bibliotheken für Dear ImGui und MinHook
target_link_libraries(MyDLL d3d11 dxgi dxguid ${MINHOOK_LIB} ${Boost_LIBRARIES})  # MinHook Bibliothek verlinken
