#ifndef GAME_DIFFICULTY_HPP_
#define GAME_DIFFICULTY_HPP_

#include <chrono>
#include <memory>

namespace game {

enum class DifficultyLevel {
  EASY,
  NORMAL,
  HARD,
};

// Move limit per difficult is calculated based on the minimum moves required to
// finish the maze.
// HARD - the player has to come up with the optimal solution - requiring
// the fewest moves.
// NORMAL - allows for 50% more moves than the minimum.
// EASY - allows for twice as much moves moves.
uint16_t GetMaxMoves(const DifficultyLevel& difficulty,
                     const uint16_t& minimal_moves_required);

// Time is calculated based on the minimum moves required to complete the maze.
// HARD - allows for 1s per move.
// NORMAL - allows for 1.5s per move.
// EASY - allows for 2.0 s per move.
uint16_t GetMaxTimeInSecs(const DifficultyLevel& difficulty,
                          const uint16_t& minimal_moves_required);

uint16_t GetMazeGrowthPerDifficulty(const DifficultyLevel& difficulty);

}  // namespace game

#endif  // GAME_DIFFICULTY_HPP_
