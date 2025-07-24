cmake_minimum_required(VERSION 3.15)
project(ImageEncoder LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
find_package(CURL REQUIRED)

# Library target
add_library(image_encoder
    src/image_encoder.cpp
)
target_include_directories(image_encoder
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(image_encoder
    PRIVATE CURL::libcurl
)

# Executable target
add_executable(image_encoder_cli
    src/main.cpp
)
target_link_libraries(image_encoder_cli
    PRIVATE image_encoder
)