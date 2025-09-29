#include <GLFW/glfw3.h>
#include <game_board.h>

#include <iostream>

int main() {
  // Initialization
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // Create a window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow *window = glfwCreateWindow(800, 600, "MineSweeper", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // activate an GLFW context of the created window in this thread
  glfwMakeContextCurrent(window);

  GameBoard board = GameBoard{Difficulty::Easy};

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);

    // Process window event (like key inputs) here
    glfwPollEvents();
  }

  // Termination
  glfwTerminate();
  return 0;
}
