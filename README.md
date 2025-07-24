# LISNR

A cross-platform C++ library + executable using libcurl (via vcpkg) for HTTP requests.

## Prerequisites

- Git  
- CMake ≥ 3.15  
- A C++17-capable compiler (MSVC on Windows, GCC/Clang on Linux/macOS)  
- PowerShell (Windows) or bash (macOS/Linux)  

## vcpkg Setup

1. **Clone and bootstrap vcpkg** (once per machine or per-repo):

   ```powershell
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat      # Windows
   # or ./bootstrap-vcpkg.sh   # macOS/Linux

2. Install Curl
# In your vcpkg folder:
.\vcpkg.exe install curl:x64-windows

3. (Optional) Integrate with VS globally:
.\vcpkg.exe integrate install

## Building the Project
# Remove old build cache (if any)
Remove-Item -Recurse -Force build

# Configure
cmake -S . -B build `
  -G "Visual Studio 17 2022" `
  -DCMAKE_TOOLCHAIN_FILE="C:/Users/thoma/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Build

# Windows
cmake --build build --config Debug

# On Mac/Linux
cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE="$HOME/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build build