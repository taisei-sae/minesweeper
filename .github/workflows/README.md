# GitHub Actions Workflows

This directory contains CI/CD workflows for the Minesweeper project.

## build.yml

The main build and test workflow that runs on every push and pull request.

### Jobs

1. **build-linux** - Ubuntu latest
   - Installs dependencies via apt
   - Builds the project with CMake
   - Runs tests with CTest
   - Uploads Linux binary as artifact

2. **build-windows** - Windows latest
   - Sets up vcpkg
   - Installs dependencies (GLFW, GLEW, ImGui, GoogleTest)
   - Builds the project with CMake
   - Runs tests with CTest
   - Uploads Windows executable as artifact

3. **build-summary**
   - Summarizes all build results
   - Fails if any platform build fails

**Note**: macOS build is not currently included in CI. macOS support is untested.

### Triggers

- Push to `main`, `master`, or `develop` branches
- Pull requests to `main`, `master`, or `develop` branches
- Manual workflow dispatch

### Artifacts

Build artifacts are retained for 7 days and can be downloaded from the Actions tab:
- `minesweeper-linux` - Linux executable
- `minesweeper-windows` - Windows executable (.exe)

### Status Badge

The build status badge is displayed in the main README.md:

```markdown
[![Build and Test](https://github.com/taisei-sae/minesweeper/actions/workflows/build.yml/badge.svg)](https://github.com/taisei-sae/minesweeper/actions/workflows/build.yml)
```

## Troubleshooting

### Windows build fails with pkgconfig download errors (404)
**Problem**: vcpkg tries to download pkgconfig from MSYS2 mirrors and gets 404 errors

**Solution**: Updated CMakeLists.txt to skip pkg-config on Windows and use find_package directly
- Windows uses vcpkg's CONFIG mode for package finding
- Linux continues to use pkg-config as normal
- This avoids the pkgconfig dependency issue on Windows

### Linux build fails with missing packages
- Check that all package names are correct for Ubuntu's apt repository
- Package names may change between Ubuntu versions

## Local Testing

You can test the workflow locally using [act](https://github.com/nektos/act):

```bash
# Install act
# On Ubuntu: snap install act
# On macOS: brew install act

# Run all jobs
act

# Run specific job
act -j build-linux
act -j build-windows
```

Note: Windows jobs may not work properly with act due to platform limitations.
