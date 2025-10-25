# minesweeper

A game, you know.

## For Developpers (It's me! Just in case that I forget)

### Prerequisites
- Ubuntu 24.04LTS
- VSCode (C/C++ Extention Pack)
- and libraries:
```bash
sudo apt install -y build-essential cmake libglfw3-dev libglew-dev libgtest-dev
```
### Build and Run
At project root,
```bash
./build.sh # build
./build/MineSweeper # Run
```
### Coding Rules
#### Style
Basically ses *Google C++ Style Guide*
[https://google.github.io/styleguide/cppguide.html](https://google.github.io/styleguide/cppguide.html) 

#### Naming
- file - snake_case
- struct/class - PascalCase
- functions/methods - snake_case
- variables - snake_case (data member must have "_" at the end of its name)
