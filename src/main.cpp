#include <GLFW/glfw3.h>

#include <iostream>

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // use core profile to avoid deprecated functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
  GLFWwindow *window = glfwCreateWindow(800, 600, "MineSweeper", NULL, NULL);
  if (!window) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // activate an GLFW context of the created window in this thread
  glfwMakeContextCurrent(window);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwSwapBuffers(window);

    // Process window event (like key inputs) here
    glfwPollEvents();
  }
  glfwTerminate();
}