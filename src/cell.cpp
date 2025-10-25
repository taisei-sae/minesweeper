#include "cell.h"

bool Cell::is_open() const { return is_open_; }

void Cell::open() { is_open_ = true; }

bool Cell::has_bomb() const { return has_bomb_; }

void Cell::set_bomb() { has_bomb_ = true; }

unsigned int Cell::get_bomb_count() const { return bomb_count_; }

void Cell::set_count(unsigned int i) { bomb_count_ = i; }

void Cell::increment_count() { bomb_count_++; }
