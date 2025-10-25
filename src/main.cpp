#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "game_board.h"
#include "input_handler.h"
#include "renderer.h"
#include "ui_manager.h"

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
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);  // Disable window resizing
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

  // 4. Create game board, renderer, UI manager, and input handler
  GameBoard board{Difficulty::Easy};

  Renderer renderer(window);
  if (!renderer.initialize()) {
    std::cerr << "Failed to initialize renderer" << std::endl;
    glfwTerminate();
    return -1;
  }

  UIManager ui_manager(window);
  if (!ui_manager.initialize()) {
    std::cerr << "Failed to initialize UI manager" << std::endl;
    renderer.cleanup();
    glfwTerminate();
    return -1;
  }

  InputHandler input_handler(window, &board);
  input_handler.setup_callbacks();

  // 5. Main loop
  while (!glfwWindowShouldClose(window)) {
    // Process events
    glfwPollEvents();

    // Render the game board
    renderer.render(board);

    // Render UI
    ui_manager.render(board);

    // Swap buffers
    glfwSwapBuffers(window);
  }

  // 6. Cleanup
  ui_manager.cleanup();
  renderer.cleanup();
  glfwTerminate();
  return 0;
}
