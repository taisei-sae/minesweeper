#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <GLFW/glfw3.h>

#include <tuple>

#include "game_board.h"

class InputHandler {
 public:
  InputHandler(GLFWwindow* window, GameBoard* board);
  ~InputHandler();

  // Setup input callbacks
  void setup_callbacks();

 private:
  GLFWwindow* window_;
  GameBoard* board_;

  // Static callback functions (required by GLFW C API)
  static void mouse_button_callback(GLFWwindow* window, int button, int action,
                                    int mods);
  static void key_callback(GLFWwindow* window, int key, int scancode,
                          int action, int mods);

  // Instance method to get clicked cell coordinates
  std::tuple<unsigned int, unsigned int> get_clicked_cell();

  // Instance method for handling mouse button events
  void handle_mouse_button(int button, int action, int mods);

  // Instance method for handling keyboard events
  void handle_key(int key, int scancode, int action, int mods);
};

#endif  // INPUT_HANDLER_H_
