#ifndef CELL_H_
#define CELL_H_

class Cell {
 public:
  // default constructor
  Cell() : is_open_(false), has_bomb_(false), bomb_count_(0) {};

  bool is_open() const;
  void open();
  bool has_bomb() const;
  void set_bomb();
  unsigned int get_bomb_count() const;
  void set_count(unsigned int i);
  void increment_count();

 private:
  bool is_open_;
  bool has_bomb_;
  unsigned int bomb_count_;
};
#endif  // CELL_H_
