cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES C CXX)

# Tell CMake to use vcpkg’s toolchain
set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

# Require curl
find_package(CURL REQUIRED)

# Example: your library
add_library(mylib src/mylib.cpp)
target_link_libraries(mylib PRIVATE CURL::libcurl)

# Example: your executable
add_executable(myexe src/main.cpp)
target_link_libraries(myexe PRIVATE mylib)