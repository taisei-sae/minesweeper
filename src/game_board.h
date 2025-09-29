#pragma once
#include "src/game_settings.h"

class GameBoard {
  unsigned int rows_, columns_;
  unsigned int cells_reft;

 public:
  GameBoard(Difficulty difficulty);
  void openCell(unsigned int c, unsigned int r);
  bool isGameWon();
};