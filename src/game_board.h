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
  std::vector<Cell> grid_;

  void deploy_bombs();
};

#endif
