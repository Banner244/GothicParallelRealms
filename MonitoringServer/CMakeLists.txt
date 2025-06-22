cmake_minimum_required(VERSION 3.15)
project(MonitoringServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    # Windows 10
    add_definitions(-D_WIN32_WINNT=0x0A00)

    # ASIO-path
    set(ASIO_INCLUDE_DIR "C:/Program Files (x86)/asio-1.34.2/include")
    
    # Crow-path 
    set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/crow-install")
endif()


find_package(Crow REQUIRED)

# Optional
# find_package(OpenSSL REQUIRED)
# find_package(ZLIB REQUIRED)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
    src/*.hpp
)

# inih
set(INIH_SOURCES
    ${CMAKE_SOURCE_DIR}/../common/lib/inih/ini.c
)

# Automatisch alle .cpp-Dateien aus ../common/ einbinden
file(GLOB_RECURSE COMMON_SOURCES "../common/src/*.cpp")
list(APPEND SOURCES ${COMMON_SOURCES})
include_directories("../common/src/")

# --- Executable ---
add_executable(MonitoringServer ${SOURCES} ${INIH_SOURCES})
target_include_directories(MonitoringServer PRIVATE src)

# --- link Libraries  ---
target_link_libraries(MonitoringServer
    PRIVATE
        Crow::Crow
        # OpenSSL::SSL
        # OpenSSL::Crypto
        # ZLIB::ZLIB
)

# install(TARGETS MonitoringServer DESTINATION bin)
