#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "game_board.h"
#include "input_handler.h"
#include "renderer.h"

int main() {
  // 1. Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }

  // 2. Create a window
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(800, 800, "MineSweeper", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // Activate OpenGL context
  glfwMakeContextCurrent(window);

  // 3. Initialize GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "Failed to initialize GLEW" << std::endl;
    glfwTerminate();
    return -1;
  }

  // 4. Create game board, renderer, and input handler
  GameBoard board{Difficulty::Easy};
  Renderer renderer;
  if (!renderer.initialize()) {
    std::cerr << "Failed to initialize renderer" << std::endl;
    glfwTerminate();
    return -1;
  }

  InputHandler input_handler(window, &board);
  input_handler.setup_callbacks();

  // 5. Main loop
  while (!glfwWindowShouldClose(window)) {
    // Render the game board
    renderer.render(board);

    // Swap buffers
    glfwSwapBuffers(window);

    // Process events
    glfwPollEvents();
  }

  // 6. Cleanup
  renderer.cleanup();
  glfwTerminate();
  return 0;
}
