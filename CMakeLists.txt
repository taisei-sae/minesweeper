cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW)

project(Minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-specific settings
if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Find packages - support both pkg-config (Linux) and find_package (Windows/vcpkg)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Try pkg-config first (Linux), fallback to find_package (Windows)
if(WIN32)
  # Windows: use find_package directly (vcpkg)
  find_package(glfw3 CONFIG REQUIRED)
  find_package(imgui CONFIG REQUIRED)
  # Set variables to match pkg-config style for compatibility
  set(GLFW_LIBRARIES glfw)
  set(IMGUI_LIBRARIES imgui::imgui)
else()
  # Linux: use pkg-config
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GLFW REQUIRED glfw3)
  pkg_check_modules(IMGUI REQUIRED imgui)
endif()

add_executable(Minesweeper
    src/main.cpp
    src/game_board.cpp
    src/cell.cpp
    src/renderer.cpp
    src/input_handler.cpp
    src/ui_manager.cpp
)

target_include_directories(Minesweeper PUBLIC src)

target_include_directories(Minesweeper PRIVATE ${IMGUI_INCLUDE_DIRS})

target_link_libraries(Minesweeper
    PRIVATE
        ${OPENGL_LIBRARIES}
        GLEW::GLEW
        ${GLFW_LIBRARIES}
        ${IMGUI_LIBRARIES}
)


# Tests ----------------------------------------------------------
add_executable(Minesweeper_Tests
    # src/tests/test_board_logic.cpp
    src/game_board.cpp
    src/cell.cpp
)

target_link_libraries(Minesweeper_Tests
    PRIVATE
        GTest::gtest_main
)

# CTestにテストを登録
include(CTest)
add_test(NAME run_minesweeper_tests COMMAND Minesweeper_Tests)
