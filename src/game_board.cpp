#include "game_board.h"

#include <random>

GameBoard::GameBoard(const Difficulty difficulty) {
  game_state_ = GameState::Playing;
  settings_ = get_settings(difficulty);

  // Initialize cells with default constructor
  cells_.resize(settings_.rows * settings_.columns);
  // and put bombs and counts
  deploy_bombs_and_counts();
}

GameState GameBoard::get_game_state() const { return game_state_; }

bool GameBoard::is_valid_point(unsigned int row, unsigned int column) {
  return (row >= 0 && row < settings_.rows && column >= 0 &&
          column < settings_.columns);
}

void GameBoard::deploy_bombs_and_counts() {
  const int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  // Use modern C++ random number generation
  std::random_device rd;   // Non-deterministic random seed
  std::mt19937 gen(rd());  // Mersenne Twister engine
  std::uniform_int_distribution<unsigned int> dist(0, cells_.size() - 1);

  unsigned int bombs_count = 0;
  while (bombs_count < settings_.bombs) {
    // Deploy bomb at random index
    unsigned int index = dist(gen);
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

bool GameBoard::open_cell(unsigned int row, unsigned int column) {
  // Check if game is already over
  if (game_state_ != GameState::Playing) {
    return false;
  }

  // Check if position is valid
  if (!is_valid_point(row, column)) {
    return true;  // Invalid click, but game continues
  }

  unsigned int index = row * settings_.columns + column;
  Cell& cell = cells_[index];

  // Check if cell is already open
  if (cell.is_open()) {
    return true;  // Already open, nothing to do
  }

  // Check if cell has a flag (cannot open flagged cells)
  if (cell.has_flag()) {
    return true;  // Flagged, don't open
  }

  // Open the cell
  cell.open();

  // Check if it's a bomb
  if (cell.has_bomb()) {
    game_state_ = GameState::GameOver;
    return false;  // Game over!
  }

  // If cell has no adjacent bombs, recursively open neighbors
  if (cell.get_bomb_count() == 0) {
    open_cell_recursive(row, column);
  }

  // Check if game is cleared (all non-bomb cells are open)
  if (check_game_cleared()) {
    game_state_ = GameState::Cleared;
    return false;  // Game cleared!
  }

  return true;  // Game continues
}

void GameBoard::open_cell_recursive(unsigned int row, unsigned int column) {
  // Directions: 8 adjacent cells
  const int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                                {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  for (const auto& dir : directions) {
    int new_row = static_cast<int>(row) + dir[0];
    int new_col = static_cast<int>(column) + dir[1];

    // Check if position is valid
    if (!is_valid_point(new_row, new_col)) {
      continue;
    }

    unsigned int index = new_row * settings_.columns + new_col;
    Cell& cell = cells_[index];

    // Skip if already open or has bomb
    if (cell.is_open() || cell.has_bomb()) {
      continue;
    }

    // Open the cell
    cell.open();

    // If this cell also has no adjacent bombs, recursively open its neighbors
    if (cell.get_bomb_count() == 0) {
      open_cell_recursive(new_row, new_col);
    }
  }
}

void GameBoard::toggle_flag(unsigned int row, unsigned int column) {
  // Check if position is valid
  if (!is_valid_point(row, column)) {
    return;  // Invalid position
  }

  unsigned int index = row * settings_.columns + column;
  Cell& cell = cells_[index];

  // Toggle the flag on the cell
  cell.toggle_flag();
}

bool GameBoard::check_game_cleared() {
  for (const auto& cell : cells_) {
    // If there's a non-bomb cell that is not open, game is not cleared
    if (!cell.has_bomb() && !cell.is_open()) {
      return false;
    }
  }
  // All non-bomb cells are open
  return true;
}

void GameBoard::reset() {
  // Reset game state
  game_state_ = GameState::Playing;

  // Clear all cells (resize will call default constructor)
  cells_.clear();
  cells_.resize(settings_.rows * settings_.columns);

  // Deploy new bombs and recalculate counts
  deploy_bombs_and_counts();
}
