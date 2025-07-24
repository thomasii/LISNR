cmake_minimum_required(VERSION 3.15)
project(ImageEncoder LANGUAGES C CXX)

# Option for shared vs static build
option(IMAGE_ENCODER_BUILD_SHARED "Build image_encoder as shared (DLL/.so) library" ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
find_package(CURL REQUIRED)

# Library target: shared or static
if(IMAGE_ENCODER_BUILD_SHARED)
    add_library(image_encoder SHARED src/image_encoder.cpp)
else()
    add_library(image_encoder src/image_encoder.cpp)
endif()

target_include_directories(image_encoder
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(image_encoder
    PRIVATE CURL::libcurl
)

# Export symbols on Windows DLL
if(WIN32 AND IMAGE_ENCODER_BUILD_SHARED)
    target_compile_definitions(image_encoder PRIVATE IMAGE_ENCODER_EXPORTS)
endif()

# CLI executable
add_executable(image_encoder_cli src/main.cpp)
target_link_libraries(image_encoder_cli PRIVATE image_encoder)

# Test application linking against the library
add_executable(use_image_encoder tests/use_image_encoder.cpp)
target_link_libraries(use_image_encoder PRIVATE image_encoder)

enable_testing()
add_test(NAME RunUseApp COMMAND use_image_encoder)