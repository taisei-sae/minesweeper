#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>

#include "cell.h"
#include "game_settings.h"

enum class GameState { Playing, GameOver, Cleared };

class GameBoard {
 public:
  // Constructor
  GameBoard();

  // Get the current game state
  GameState get_game_state() const;

  // Left click and open a cell at (row, column)
  // Returns true if the game should continue, false if game over
  bool open_cell(unsigned int row, unsigned int column);

  // Right click to toggle flag on a cell at (row, column)
  void toggle_flag(unsigned int row, unsigned int column);

  // Reset the game (restart)
  void reset();

  // Change difficulty and reset the game
  void change_difficulty(Difficulty difficulty);

  // Getters for rendering
  unsigned int get_rows() const { return settings_.rows; }
  unsigned int get_columns() const { return settings_.columns; }
  const Cell& get_cell(unsigned int row, unsigned int col) const {
    return cells_[row * settings_.columns + col];
  }
  Difficulty get_difficulty() const { return settings_.difficulty; }

 private:
  GameState game_state_;
  GameSettings settings_;
  std::vector<Cell> cells_;

  bool is_valid_point(unsigned int row, unsigned int column);
  void deploy_bombs_and_counts();
  void open_cell_recursive(unsigned int row, unsigned int column);
  bool check_game_cleared();
};

#endif  // GAME_BOARD_H_
