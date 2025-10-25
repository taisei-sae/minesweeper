#ifndef GAME_SETTINGS_H_
#define GAME_SETTINGS_H_

enum class Difficulty { Easy, Normal, Hard };

struct GameSettings {
 public:
  Difficulty difficulty;
  unsigned int rows;
  unsigned int columns;
  unsigned int bombs;

  static GameSettings from_difficulty(Difficulty difficulty) {
    switch (difficulty) {
      case Difficulty::Easy:
        return GameSettings{difficulty, 9, 9, 10};
      case Difficulty::Normal:
        return GameSettings{difficulty, 13, 13, 25};
      case Difficulty::Hard:
        return GameSettings{difficulty, 17, 17, 60};
      default:  // Fallback to Normal
        return GameSettings{difficulty, 13, 13, 25};
    }
  }
};

// UI configuration constants
namespace UIConfig {
// Height of the console bar in pixels
// float because it will be converted to NDC
constexpr float kConsoleBarHeight = 60.0f;
}  // namespace UIConfig

#endif  // GAME_SETTINGS_H_
