# LISNR

A cross-platform C++ library + executable using libcurl (via vcpkg) for HTTP requests.

## Prerequisites

- Git  
- CMake ≥ 3.15  
- A C++17-capable compiler (MSVC on Windows, GCC/Clang on Linux/macOS)  
- PowerShell (Windows) or bash (macOS/Linux)
- vcpkg (for dependency management)  

## vcpkg Setup

1. **Clone and bootstrap vcpkg** (once per machine or per-repo):

```
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat      # Windows
   # or ./bootstrap-vcpkg.sh   # macOS/Linux
```

2. Install Curl
# In your vcpkg folder:
./vcpkg install curl

3. (Optional) Integrate with VS globally:
.\vcpkg.exe integrate install

## Building the Project
# Remove old build cache (if any)
```
# Windows PowerShell
if (Test-Path build) { Remove-Item -Recurse -Force build }
# Linux/macOS bash
[ -d build ] && rm -rf build

# Configure (Windows example)
cmake -S . -B build -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake" -DIMAGE_ENCODER_BUILD_SHARED=ON

# Or on macOS/Linux
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake" \
  -DIMAGE_ENCODER_BUILD_SHARED=ON

# Build
cmake --build build --config Release
```

## Running the CLI Executable

```
# Windows (Debug build)
.\build\Debug\image_encoder_cli.exe "https://example.com/image.png" encoded.txt

# Linux/macOS
./build/image_encoder_cli "https://example.com/image.png" encoded.txt
```

## Use as Shared Linked Library

```
cd build/Release
.\use_image_encoder.exe
```