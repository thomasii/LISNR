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

3. Configure VC Package Windows
```
$env:VCPKG_ROOT = "C:\Users\User\vcpkg"
$env:PATH = "$env:VCPKG_ROOT;$env:PATH"
```
# verify vcpkg path
(Get-Command vcpkg.exe).Path 

# Force vc package to use your Curl
vcpkg.exe install curl:x64-windows --vcpkg-root=C:\Users\User\vcpkg

# Inside root of project dir
Remove-Item -Recurse -Force build
vcpkg.exe install

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
```
# Build exe
cmake --build build --config Debug

## Running the CLI Executable

```
# Windows (Debug build)
.\build\Debug\image_encoder_cli.exe "https://cdn.pixabay.com/photo/2025/07/12/10/04/reinebringen-9710168_1280.jpg" encoded.txt


# Linux/macOS
./build/image_encoder_cli "https://cdn.pixabay.com/photo/2025/07/12/10/04/reinebringen-9710168_1280.jpg" encoded.txt
```

## Use as Shared Linked Library

```
cd build/Debug
.\use_image_encoder.exe
```