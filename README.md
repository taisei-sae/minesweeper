# Minesweeper

[![Build and Test](https://github.com/taisei-sae/minesweeper/actions/workflows/build.yml/badge.svg)](https://github.com/taisei-sae/minesweeper/actions/workflows/build.yml)

A classic Minesweeper game implemented in C++ with OpenGL.

## Features

- Classic Minesweeper gameplay
- Three difficulty levels (Easy, Normal, Hard)
- Flag system to mark suspected bombs
- Automatic cell reveal for zero-bomb cells
- ImGui-based UI console
- OpenGL rendering with color-coded cells

## Controls

- **Left Click**: Open a cell
- **Right Click**: Toggle flag on a cell
- **R Key**: Restart the current game
- **1 Key**: Switch to Easy difficulty
- **2 Key**: Switch to Normal difficulty
- **3 Key**: Switch to Hard difficulty

## For Developers

### Platform Support

This game runs on:
- ✅ **Linux** (Ubuntu 24.04 LTS and compatible distributions)
- ✅ **Windows** (Windows 11 x86_64 and Windows 10)
- ⚠️ **macOS** (Should work but untested)

### Prerequisites

#### Linux (Ubuntu 24.04 LTS)
- VSCode (C/C++ Extension Pack) - optional
- Required libraries:
```bash
sudo apt install -y build-essential cmake libglfw3-dev libglew-dev libimgui-dev libgtest-dev
```

#### Windows 11/10
- **Option 1: Visual Studio** (Recommended)
  - Visual Studio 2019 or later (Community Edition is free)
  - Install "Desktop development with C++" workload

- **Option 2: MinGW-w64**
  - MinGW-w64 + CMake

- **Package Manager: vcpkg** (Recommended for dependencies)
```powershell
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Install dependencies
.\vcpkg install glfw3:x64-windows glew:x64-windows
.\vcpkg install imgui[glfw-binding,opengl3-binding]:x64-windows
.\vcpkg install gtest:x64-windows

# Integrate with CMake
.\vcpkg integrate install
```

See [WINDOWS_BUILD.md](WINDOWS_BUILD.md) for detailed Windows build instructions.

### Build and Run

#### Linux
At project root:
```bash
./build.sh          # Build the project
./build/Minesweeper # Run the game
```

#### Windows
Using CMake with vcpkg:
```powershell
# In project directory
mkdir build
cd build

# Configure
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path-to-vcpkg]/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build . --config Release

# Run
.\Release\Minesweeper.exe
```

Or simply open the project folder in Visual Studio (CMake support included).

### Run Tests

#### Linux
```bash
cd build
ctest
```

#### Windows
```powershell
cd build
ctest -C Release
```
### Coding Rules
#### Style
Basically follows *Google C++ Style Guide*
[https://google.github.io/styleguide/cppguide.html](https://google.github.io/styleguide/cppguide.html)

#### Naming
- file - snake_case
- struct/class - PascalCase
- functions/methods - snake_case
- variables - snake_case (data member must have "_" at the end of its name)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### Third-Party Libraries

This project uses the following open-source libraries:

- **GLFW** - zlib/libpng License
- **Dear ImGui** - MIT License
- **GLEW** - Modified BSD License and MIT License
- **Google Test** - BSD 3-Clause License (development only)

See [THIRD_PARTY_LICENSES.md](THIRD_PARTY_LICENSES.md) for the full license texts of these libraries.

## Acknowledgments

- Thanks to the developers of GLFW, ImGui, GLEW, and Google Test for their excellent libraries.
- This project was created as a learning exercise for C++ and OpenGL programming.
