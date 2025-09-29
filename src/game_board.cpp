#include "game_board.h"

GameBoard::GameBoard(const Difficulty difficulty) {
  GameSettings const settings = get_settings(difficulty);
  rows_ = settings.rows;
  columns_ = settings.columns;
  non_bomb_count_ = settings.columns * settings.rows - settings.bombs;
  grid_.resize(settings.rows * settings.columns);
}
