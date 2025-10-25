#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#include <GLFW/glfw3.h>

#include "game_board.h"

class UIManager {
 public:
  UIManager(GLFWwindow* window);
  ~UIManager();

  // Initialize ImGui
  bool initialize();

  // Render UI for the current frame
  void render(const GameBoard& board);

  // Cleanup ImGui resources
  void cleanup();

 private:
  GLFWwindow* window_;
};

#endif  // UI_MANAGER_H_
