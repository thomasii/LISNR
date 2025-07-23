cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(LISNR VERSION 1.0 LANGUAGES CXX)

# —————————————————————————————
# 1. Compiler settings
# —————————————————————————————
set(CMAKE_CXX_STANDARD            17)
set(CMAKE_CXX_STANDARD_REQUIRED   ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (MSVC)
  # disable incremental linking on all executables & DLLs
  set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /INCREMENTAL:NO")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /INCREMENTAL:NO")
endif()

# —————————————————————————————
# 2. Shared‐library target (image fetch + encode)
# —————————————————————————————
add_library(LISNR_shared SHARED
  src/image_encoder.cpp
)

# Export IE_API symbols when building the DLL
target_compile_definitions(LISNR_shared
  PRIVATE IMAGE_ENCODER_EXPORTS
)

# Public include path for consumers
target_include_directories(LISNR_shared
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Name the shared library “LISNR” on disk
set_target_properties(LISNR_shared PROPERTIES
  OUTPUT_NAME ${PROJECT_NAME}
  VERSION     ${PROJECT_VERSION}
  SOVERSION   ${PROJECT_VERSION_MAJOR}
)

# —————————————————————————————
# 3. Executable target (CLI)
# —————————————————————————————
add_executable(LISNR
  src/main.cpp
)

# Link the CLI against the shared library
target_link_libraries(LISNR
  PRIVATE LISNR_shared
)

# —————————————————————————————
# 4. Install rules
# —————————————————————————————
install(
  TARGETS
    LISNR_shared
    LISNR
  RUNTIME DESTINATION bin       # .exe or Linux/OSX binaries
  LIBRARY DESTINATION lib       # .so, .dylib, or .dll
  ARCHIVE DESTINATION lib       # .a or .lib
)

install(
  DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)
