#include "game_board.h"

#include <cstdlib>

GameBoard::GameBoard(const Difficulty difficulty) {
  game_state_ = GameState::Playing;
  settings_ = get_settings(difficulty);

  // Initialize cells with default constructor
  cells_.resize(settings_.rows * settings_.columns);
  // and put bombs and counts
  deploy_bombs_and_counts();
}

GameState GameBoard::get_game_state() { return game_state_; }

bool GameBoard::is_valid_point(unsigned int row, unsigned int column) {
  return (row >= 0 && row < settings_.rows && column >= 0 &&
          column < settings_.columns);
}

void GameBoard::deploy_bombs_and_counts() {
  const int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  unsigned int bombs_count = 0;
  while (bombs_count < settings_.bombs) {
    // Deploy bomb at random index
    unsigned int index = rand() % cells_.size();
    if (!cells_[index].has_bomb()) {
      cells_[index].set_bomb();
      bombs_count++;

      // Update adjacent cells' bomb counts
      unsigned int row = index / settings_.columns;
      unsigned int col = index % settings_.columns;
      for (const auto& dir : directions) {
        int new_row = static_cast<int>(row) + dir[0];
        int new_col = static_cast<int>(col) + dir[1];
        if (is_valid_point(new_row, new_col)) {
          unsigned int neighbor_index = new_row * settings_.columns + new_col;
          cells_[neighbor_index].increment_count();
        }
      }
    }
  }
}

void GameBoard::open_cell_recursive(unsigned int row, unsigned int column) {
  unsigned int index = settings_.columns * row + column;
  cells_[index].open();

  // Check id the cell is vacant
  if (cells_[index].has_bomb() || cells_[index].get_bomb_count() > 0) {
    return;
  }

  // TODO: Search for adjacent vacant cells
}
