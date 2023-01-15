#include "game/difficulty.hpp"

namespace game {

uint16_t GetMoveLimit(const DifficultyLevel& difficulty,
                      const uint16_t& minimal_moves_required) {
  switch (difficulty) {
    case DifficultyLevel::EASY:
      return 1.5 * minimal_moves_required;
    case DifficultyLevel::NORMAL:
      return static_cast<uint16_t>(1.25 * minimal_moves_required);
    case DifficultyLevel::HARD:
      return minimal_moves_required;
    default:
      throw std::invalid_argument("Invalid DifficultyLevel");
  }
}
uint16_t GetTimeLimitInSecs(const DifficultyLevel& difficulty,
                            const uint16_t& minimal_moves_required) {
  switch (difficulty) {
    case DifficultyLevel::EASY:
      return 1.5 * minimal_moves_required;
    case DifficultyLevel::NORMAL:
      return static_cast<uint16_t>(1.25 * minimal_moves_required);
    case DifficultyLevel::HARD:
      return minimal_moves_required;
    default:
      throw std::invalid_argument("Invalid DifficultyLevel");
  }
}

uint16_t GetMazeGrowthPerDifficulty(const DifficultyLevel& difficulty) {
  switch (difficulty) {
    case DifficultyLevel::EASY:
      return 2;
    case DifficultyLevel::NORMAL:
      return 4;
    case DifficultyLevel::HARD:
      return 6;
    default:
      throw std::invalid_argument("Invalid DifficultyLevel");
  }
}

}  // namespace game
