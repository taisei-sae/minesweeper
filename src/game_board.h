#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>

#include "cell.h"
#include "game_settings.h"

class GameBoard {
 public:
  // Constructor
  GameBoard(Difficulty difficulty);

 private:
  GameSettings settings_;
  std::vector<Cell> cells_;

  void deploy_bombs_and_counts();
};

#endif
