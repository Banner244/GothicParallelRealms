cmake_minimum_required(VERSION 3.15)
project(ParallelRealmsServer)

# Aktivieren Sie C++17 oder höher, falls erforderlich
set(CMAKE_CXX_STANDARD 17)

# Setze Policy CMP0144, um Uppercase-Variablen wie BOOST_ROOT korrekt zu behandeln
if(POLICY CMP0144)
    cmake_policy(SET CMP0144 NEW)
endif()
if(POLICY CMP0167)
    cmake_policy(SET CMP0167 OLD) # Für Kompatibilität mit dem alten FindBoost-Modul
endif()

# Plattformabhängige Konfiguration
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

# Füge das ausführbare Ziel hinzu
add_executable(${PROJECT_NAME} src/main.cpp)

# Boost-Header und -Bibliotheken einbinden
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
