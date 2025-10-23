#include "game_board.h"

#include <cstdlib>

GameBoard::GameBoard(const Difficulty difficulty) {
  settings_ = get_settings(difficulty);
  // Initialize cells with default constructor
  cells_.resize(settings_.rows * settings_.columns);
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
        if (new_row >= 0 && new_row < static_cast<int>(settings_.rows) &&
            new_col >= 0 && new_col < static_cast<int>(settings_.columns)) {
          unsigned int neighbor_index = new_row * settings_.columns + new_col;
          cells_[neighbor_index].increment_count();
        }
      }
    }
  }
}
