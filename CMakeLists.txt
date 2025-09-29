cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0072 NEW)

project(Minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GTest CONFIG REQUIRED)

add_executable(Minesweeper
    src/main.cpp
    src/game_board.cpp
)

target_include_directories(Minesweeper PUBLIC src)

target_link_libraries(Minesweeper
    PRIVATE
        ${OPENGL_LIBRARIES}
        GLEW::GLEW
        ${GLFW_LIBRARIES}
)


# Tests ----------------------------------------------------------
add_executable(Minesweeper_Tests
    # src/tests/test_board_logic.cpp
    src/game_board.cpp
)

target_link_libraries(Minesweeper_Tests
    PRIVATE
        GTest::gtest_main
)

# CTestにテストを登録
include(CTest)
add_test(NAME run_minesweeper_tests COMMAND Minesweeper_Tests)
