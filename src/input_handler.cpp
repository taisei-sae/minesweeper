#include "input_handler.h"

#include <iostream>

InputHandler::InputHandler(GLFWwindow* window, GameBoard* board)
    : window_(window), board_(board) {}

InputHandler::~InputHandler() {
  // Clear callbacks
  glfwSetMouseButtonCallback(window_, nullptr);
}

void InputHandler::setup_callbacks() {
  // Store 'this' pointer in window user pointer for callback access
  glfwSetWindowUserPointer(window_, this);

  // Set GLFW callbacks
  glfwSetMouseButtonCallback(window_, mouse_button_callback);
}

void InputHandler::mouse_button_callback(GLFWwindow* window, int button,
                                          int action, int mods) {
  // Get InputHandler instance from window user pointer
  InputHandler* handler =
      static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
  if (handler) {
    handler->handle_mouse_button(button, action, mods);
  }
}

void InputHandler::handle_mouse_button(int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(window_, &xpos, &ypos);

    // Get window size
    int width, height;
    glfwGetWindowSize(window_, &width, &height);

    // Convert screen coordinates to grid coordinates
    unsigned int rows = board_->get_rows();
    unsigned int cols = board_->get_columns();

    unsigned int col = static_cast<unsigned int>((xpos / width) * cols);
    unsigned int row = static_cast<unsigned int>((ypos / height) * rows);

    // Open the cell
    if (col < cols && row < rows) {
      bool game_continues = board_->open_cell(row, col);
      if (!game_continues) {
        std::cout << "Game Over! You hit a bomb!" << std::endl;
      }
    }
  }
}
