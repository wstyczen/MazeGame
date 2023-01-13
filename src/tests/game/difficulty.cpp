#include "gtest/gtest.h"

#include "game/difficulty.hpp"

namespace tests {
namespace {

class Difficulty : public ::testing::Test {};

TEST_F(Difficulty, GetMoveLimit) {
  ASSERT_EQ(game::GetMoveLimit(game::DifficultyLevel::EASY, 21), 31);
  ASSERT_EQ(game::GetMoveLimit(game::DifficultyLevel::NORMAL, 21), 26);
  ASSERT_EQ(game::GetMoveLimit(game::DifficultyLevel::HARD, 21), 21);
}

TEST_F(Difficulty, GetTimeLimitInSecs) {
  ASSERT_EQ(game::GetTimeLimitInSecs(game::DifficultyLevel::EASY, 21), 31);
  ASSERT_EQ(game::GetTimeLimitInSecs(game::DifficultyLevel::NORMAL, 21), 26);
  ASSERT_EQ(game::GetTimeLimitInSecs(game::DifficultyLevel::HARD, 21), 21);
}

TEST_F(Difficulty, GetMazeGrowthPerDifficulty) {
  ASSERT_EQ(game::GetMazeGrowthPerDifficulty(game::DifficultyLevel::EASY), 2);
  ASSERT_EQ(game::GetMazeGrowthPerDifficulty(game::DifficultyLevel::NORMAL), 4);
  ASSERT_EQ(game::GetMazeGrowthPerDifficulty(game::DifficultyLevel::HARD), 6);
}

}  // namespace
}  // namespace tests
