enum class Difficulty { Easy, Normal, Hard };

struct GameSettings {
  unsigned int rows, columns;
  unsigned int bombs;
};

static GameSettings getSettings(Difficulty difficulty) {
  switch (difficulty) {
    case Difficulty::Easy:
      return GameSettings{9, 9, 10};
    case Difficulty::Normal:
      return GameSettings{16, 16, 25};
    case Difficulty::Hard:
      return GameSettings{25, 25, 60};
    default:
      return GameSettings{16, 16, 25};
  }
}
