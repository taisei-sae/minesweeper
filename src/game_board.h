#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

#include <vector>

#include "game_settings.h"

class Cell {
 public:
  //  default constructor
  Cell() : is_open_(false), has_bomb_(false), bomb_count_(0) {};

  bool is_open() { return this->is_open_; }
  void open() { this->is_open_ = true; };
  bool has_bomb() { return this->has_bomb_; }
  void set_bomb() { this->has_bomb_ = true; };
  unsigned int get_bomb_count() { return this->bomb_count_; }
  void set_count(unsigned int i) { this->bomb_count_ = i; };

 private:
  bool is_open_;
  bool has_bomb_;
  unsigned int bomb_count_;
};

class GameBoard {
 public:
  // Constructor
  GameBoard(Difficulty difficulty);

 private:
  unsigned int rows_, columns_;
  unsigned int non_bomb_count_;
  std::vector<Cell> grid_;

  void deploy_bombs();
};

#endif
