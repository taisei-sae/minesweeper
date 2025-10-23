#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>

#include "cell.h"
#include "game_settings.h"

enum class GameState { Playing, GameOver, Cleared };

class GameBoard {
 public:
  /// Constructor
  GameBoard(Difficulty difficulty);

  /// Get the current game state
  GameState get_game_state();

  /// Click and open a cell at (row, column)
  /// Returns true if the game should continue, false if game over
  bool open_cell(unsigned int row, unsigned int column);

 private:
  GameState game_state_;
  GameSettings settings_;
  std::vector<Cell> cells_;

  bool is_valid_point(unsigned int row, unsigned int column);
  void deploy_bombs_and_counts();
  void open_cell_recursive(unsigned int row, unsigned int column);
};

#endif
