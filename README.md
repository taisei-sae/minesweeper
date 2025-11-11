# Minesweeper

[![Build and Test](https://github.com/taisei-sae/minesweeper/actions/workflows/build.yml/badge.svg)](https://github.com/taisei-sae/minesweeper/actions/workflows/build.yml)

A classic Minesweeper game implemented in C++ with OpenGL.

## For Developers

### Platform Support

-  Linux (Ubuntu 24.04 LTS and compatible distributions)


### Prerequisites

```bash
sudo apt install -y build-essential cmake libglfw3-dev libglew-dev libimgui-dev libgtest-dev
```


### Build and Run

#### Linux
At project root:
```bash
./build.sh          # Build the project
./build/Minesweeper # Run the game
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
