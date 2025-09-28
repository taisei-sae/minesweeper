class GameBoard {
 public:
  void openCell(unsigned int c, unsigned int r);
  bool isGameWon();

 private:
  unsigned int rows;
  unsigned int columns;
  unsigned int cells_reft;
};