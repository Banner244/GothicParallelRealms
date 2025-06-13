cmake_minimum_required(VERSION 3.15)
project(ParallelRealmsServer)

# Aktivieren Sie C++17 oder höher
set(CMAKE_CXX_STANDARD 17)

# Boost Konfiguration
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00) # Windows 10 Target
    set(BOOST_ROOT "C:/Program Files/boost_1_87_0")
    set(BOOST_INCLUDEDIR "${BOOST_ROOT}/boost")
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")
elseif(UNIX)
    set(BOOST_INCLUDEDIR "/usr/include")
    set(BOOST_LIBRARYDIR "/usr/lib")
endif()

find_package(Boost REQUIRED COMPONENTS system)

if(Boost_FOUND)
    message(STATUS "Boost gefunden: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Boost konnte nicht gefunden werden")
endif()

# Automatisch alle .cpp-Dateien aus src/ einbinden
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Automatisch alle .cpp-Dateien aus ../common/ einbinden
file(GLOB_RECURSE COMMON_SOURCES "../common/src/*.cpp")
list(APPEND SOURCES ${COMMON_SOURCES})
include_directories("../common/src/")

# Füge das ausführbare Ziel hinzu
add_executable(${PROJECT_NAME} ${SOURCES})

# Boost einbinden
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
