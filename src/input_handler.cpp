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
  glfwSetKeyCallback(window_, key_callback);
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

void InputHandler::key_callback(GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
  // Get InputHandler instance from window user pointer
  InputHandler* handler =
      static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
  if (handler) {
    handler->handle_key(key, scancode, action, mods);
  }
}

std::tuple<unsigned int, unsigned int> InputHandler::get_clicked_cell() {
  double xpos, ypos;
  glfwGetCursorPos(window_, &xpos, &ypos);

  int width, height;
  glfwGetWindowSize(window_, &width, &height);

  unsigned int rows = board_->get_rows();
  unsigned int cols = board_->get_columns();

  unsigned int col = static_cast<unsigned int>((xpos / width) * cols);
  unsigned int row = static_cast<unsigned int>((ypos / height) * rows);

  return std::make_tuple(row, col);
}

void InputHandler::handle_mouse_button(int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
    // Get mouse position
    unsigned int row, col;
    std::tie(row, col) = get_clicked_cell();

    // Open the cell
    bool game_continues = board_->open_cell(row, col);
    if (!game_continues) {
      GameState state = board_->get_game_state();
      if (state == GameState::Cleared) {
        std::cout << "Congratulations! You cleared the game!" << std::endl;
      } else if (state == GameState::GameOver) {
        std::cout << "Game Over! You hit a bomb!" << std::endl;
      }
    }
  } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    // Right-click handling (e.g., flagging a cell) can be added here
    unsigned int row, col;
    std::tie(row, col) = get_clicked_cell();
    board_->toggle_flag(row, col);
  }
}

void InputHandler::handle_key(int key, int scancode, int action, int mods) {
  // Press 'R' to restart the game
  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    board_->reset();
    std::cout << "Game restarted! Press 'R' to restart again." << std::endl;
  }
}
