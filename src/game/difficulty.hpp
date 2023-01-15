#ifndef GAME_DIFFICULTY_HPP_
#define GAME_DIFFICULTY_HPP_

#include <chrono>
#include <memory>

namespace game {

enum class DifficultyLevel {
  FIRST,
  EASY = FIRST,
  NORMAL,
  HARD,
  LAST = HARD,
};

// Move limit per difficult is calculated based on the minimum moves required to
// finish the maze.
// HARD - the player has to come up with the optimal solution - requiring
// the fewest moves.
// NORMAL - allows for 25% more moves than the minimum.
// EASY - allows for 50% more moves.
uint16_t GetMoveLimit(const DifficultyLevel& difficulty,
                      const uint16_t& minimal_moves_required);

// Time is calculated based on the minimum moves required to complete the maze.
// HARD - allows for 1s per move.
// NORMAL - allows for 1.25s per move.
// EASY - allows for 1.5 s per move.
uint16_t GetTimeLimitInSecs(const DifficultyLevel& difficulty,
                            const uint16_t& minimal_moves_required);

uint16_t GetMazeGrowthPerDifficulty(const DifficultyLevel& difficulty);

}  // namespace game

#endif  // GAME_DIFFICULTY_HPP_
