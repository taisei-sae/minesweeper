#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#include <GLFW/glfw3.h>

#include "game_board.h"

struct ImFont;  // Forward declaration

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
  bool initialized_;
  ImFont* large_font_;  // Large font for game overlay numbers

  // Render numbers and symbols overlay on game board
  void render_game_overlay(const GameBoard& board, int display_w,
                           int display_h);
};

#endif  // UI_MANAGER_H_
