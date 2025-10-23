#include "game_board.h"

GameBoard::GameBoard(const Difficulty difficulty) {
  settings_ = get_settings(difficulty);
  grid_.resize(settings_.rows * settings_.columns);
}

void GameBoard::deploy_bombs() {
  // To be implemented
}
