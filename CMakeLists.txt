cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0072 NEW)
project(Minesweeper CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(Minesweeper src/main.cpp)

target_link_libraries(Minesweeper
    PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
)
