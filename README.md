# Minesweeper

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
- **1 Key**: Switch to Easy difficulty (9x9, 10 bombs)
- **2 Key**: Switch to Normal difficulty (16x16, 25 bombs)
- **3 Key**: Switch to Hard difficulty (25x25, 60 bombs)

## For Developpers (It's me! Just in case that I forget)

### Prerequisites
- Ubuntu 24.04 LTS (or compatible Linux distribution)
- VSCode (C/C++ Extension Pack) - optional
- Required libraries:
```bash
sudo apt install -y build-essential cmake libglfw3-dev libglew-dev libimgui-dev libgtest-dev
```

### Build and Run
At project root:
```bash
./build.sh          # Build the project
./build/Minesweeper # Run the game
```

### Run Tests
```bash
cd build
ctest
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
