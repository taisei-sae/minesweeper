#include "src/game_board.h"

GameBoard::GameBoard(Difficulty difficulty) {
  GameSettings settings = getSettings(difficulty);
}

bool GameBoard::isGameWon() { return this->cells_reft == 0; }