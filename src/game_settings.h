#ifndef GAME_SETTINGS_H_
#define GAME_SETTINGS_H_

enum class Difficulty { Easy, Normal, Hard };

struct GameSettings {
  unsigned int rows;
  unsigned int columns;
  unsigned int bombs;
};

static GameSettings get_settings(Difficulty difficulty) {
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

// UI configuration constants
namespace UIConfig {
constexpr float kConsoleBarHeight =
    60.0f;  // Height of the console bar in pixels
}  // namespace UIConfig

#endif  // GAME_SETTINGS_H_
