# Building Minesweeper on Windows 11

This document explains how to build and run the Minesweeper game on Windows 11 (x86_64).

## Required Changes Summary

### 1. Platform-Specific Code Issues

The following platform-specific issues need to be addressed:

#### Font Path (Critical)
- **Current**: Hard-coded Linux path `/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf`
- **Location**: `src/ui_manager.cpp:33`
- **Solution**: Use conditional compilation or runtime detection to select font path

### 2. Prerequisites for Windows

#### Build Tools
- **Visual Studio 2019 or later** (Community Edition is free)
  - Install "Desktop development with C++" workload
  - Includes MSVC compiler and CMake
- OR **MinGW-w64** + **CMake**
  - Download from: https://www.mingw-w64.org/
  - CMake: https://cmake.org/download/

#### Libraries
All libraries used are cross-platform, but need to be installed for Windows:

1. **GLFW** (Cross-platform, supports Windows)
   - Download pre-compiled binaries: https://www.glfw.org/download.html
   - Or use vcpkg: `vcpkg install glfw3`

2. **GLEW** (Cross-platform, supports Windows)
   - Download pre-compiled binaries: https://glew.sourceforge.net/
   - Or use vcpkg: `vcpkg install glew`

3. **Dear ImGui** (Cross-platform, header-only mostly)
   - Download from: https://github.com/ocornut/imgui
   - Or use vcpkg: `vcpkg install imgui[glfw-binding,opengl3-binding]`

4. **Google Test** (Development only)
   - Use vcpkg: `vcpkg install gtest`

#### Recommended: Use vcpkg Package Manager
```powershell
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install dependencies
.\vcpkg install glfw3:x64-windows
.\vcpkg install glew:x64-windows
.\vcpkg install imgui[glfw-binding,opengl3-binding]:x64-windows
.\vcpkg install gtest:x64-windows

# Integrate with Visual Studio/CMake
.\vcpkg integrate install
```

### 3. Required Code Changes

#### A. Font Path Handling

**File**: `src/ui_manager.cpp`

Need to add platform-specific font path selection:

```cpp
// Current code (line 33):
const char* font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";

// Proposed change:
#ifdef _WIN32
  // Windows font path
  const char* font_path = "C:\\Windows\\Fonts\\arialbd.ttf";  // Arial Bold
  // Alternative: "C:\\Windows\\Fonts\\tahomabd.ttf" (Tahoma Bold)
#else
  // Linux font path
  const char* font_path = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";
#endif
```

#### B. CMakeLists.txt Updates

**File**: `CMakeLists.txt`

The CMakeLists.txt needs to be updated for better Windows support:

1. **Find packages on Windows** (vcpkg integration):
```cmake
# Add after project()
if(WIN32)
  # Windows-specific settings
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
```

2. **OpenGL finding** (already using find_package, should work):
```cmake
find_package(OpenGL REQUIRED)  # ✓ Already cross-platform
```

3. **GLFW/GLEW/ImGui** with pkg-config alternatives:
```cmake
# Current uses pkg-config (Linux-specific)
# Need to add fallback for Windows:

if(PKG_CONFIG_FOUND)
  pkg_check_modules(GLFW REQUIRED glfw3)
  pkg_check_modules(IMGUI REQUIRED imgui)
else()
  # Fallback to find_package for Windows/vcpkg
  find_package(glfw3 CONFIG REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(imgui CONFIG REQUIRED)
endif()
```

### 4. Build Instructions for Windows

#### Option A: Using Visual Studio with vcpkg

1. Install dependencies with vcpkg (see above)
2. Open project folder in Visual Studio
3. Visual Studio will detect CMakeLists.txt automatically
4. Build and run using Visual Studio's CMake support

#### Option B: Using CMake + MinGW

```powershell
# In project directory
mkdir build
cd build

# Configure (assuming vcpkg is set up)
cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build .

# Run
.\Minesweeper.exe
```

#### Option C: Using CMake + Visual Studio (Command Line)

```powershell
# In project directory
mkdir build
cd build

# Configure for Visual Studio 2022
cmake .. -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build . --config Release

# Run
.\Release\Minesweeper.exe
```

### 5. Potential Runtime Issues on Windows

1. **OpenGL Drivers**: Ensure graphics drivers are up to date
2. **DLL Dependencies**: May need to copy DLLs to executable directory
   - glfw3.dll
   - glew32.dll
   - (Or use static linking)

3. **Window Creation**: GLFW should handle Windows-specific window creation automatically

### 6. Testing Checklist

- [ ] CMake configuration succeeds
- [ ] Project builds without errors
- [ ] Window opens successfully
- [ ] OpenGL rendering works
- [ ] ImGui UI displays correctly
- [ ] Mouse and keyboard input works
- [ ] Font loads successfully
- [ ] Game logic works correctly

### 7. Known Limitations

- Font path is hardcoded and needs manual update for different Windows versions
- No pre-built Windows binaries provided yet
- Requires manual dependency installation

### 8. Future Improvements

1. **Font Handling**:
   - Bundle a font file with the application
   - Or use ImGui's default font (no external file needed)
   - Or implement font search in common Windows font directories

2. **Automated Builds**:
   - Set up GitHub Actions for Windows builds
   - Provide pre-compiled Windows binaries

3. **Installer**:
   - Create Windows installer with all dependencies

## Summary of Required Changes

### Critical (Must Fix):
1. ✅ Font path - Add `#ifdef _WIN32` for Windows font
2. ✅ CMakeLists.txt - Add vcpkg/Windows support

### Important (Should Fix):
3. Update README.md with Windows build instructions
4. Test on actual Windows 11 machine

### Nice to Have:
5. Bundle font file with application
6. Create Windows installer
7. Set up CI/CD for Windows builds

## Estimated Effort

- **Code changes**: 1-2 hours (font path + CMakeLists.txt)
- **Testing setup**: 2-4 hours (install tools, dependencies)
- **First successful build**: 3-6 hours total
- **Polish and documentation**: 1-2 hours

## Conclusion

The game is **mostly cross-platform** already thanks to:
- ✅ GLFW (cross-platform windowing)
- ✅ OpenGL (cross-platform graphics)
- ✅ GLEW (cross-platform OpenGL extension loading)
- ✅ ImGui (cross-platform UI)
- ✅ Standard C++17 (cross-platform language)

Main work needed:
1. Fix font path (5 lines of code)
2. Update CMakeLists.txt for vcpkg (20-30 lines)
3. Test and document

The game should run on Windows with minimal changes!
