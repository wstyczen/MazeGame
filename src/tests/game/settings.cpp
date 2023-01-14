#include "gtest/gtest.h"

#include "game/settings.hpp"

namespace tests {
namespace {

class Settings : public ::testing::Test {};

TEST_F(Settings, GetDefaultFlags) {
  const game::Settings settings = game::GetDefaultFlags();
  ASSERT_EQ(settings.generator_type,
            maze::GeneratorType::RECURSIVE_BACKTRACKING);
  ASSERT_EQ(settings.solver_type, maze::SolverType::A_STAR);
  ASSERT_EQ(settings.path_type, maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
  ASSERT_EQ(settings.difficulty, game::DifficultyLevel::NORMAL);
  ASSERT_EQ(settings.starting_size, maze::CellSize(5, 5));
}

TEST_F(Settings, ReadFlags1) {
  const int argc = 4;
  char* argv[4] = {(char*)"", (char*)"--generator=ellers",
                   (char*)"--path_type=left_to_right", (char*)"--size={3,3}"};
  const game::Settings settings = game::ReadFlags(argc, argv);
  ASSERT_EQ(settings.generator_type, maze::GeneratorType::ELLERS);
  ASSERT_EQ(settings.solver_type, maze::SolverType::A_STAR);
  ASSERT_EQ(settings.path_type, maze::PathType::LEFT_TO_RIGHT);
  ASSERT_EQ(settings.difficulty, game::DifficultyLevel::NORMAL);
  ASSERT_EQ(settings.starting_size, maze::CellSize(3, 3));
}

TEST_F(Settings, ReadFlags2) {
  const int argc = 5;
  char* argv[5] = {(char*)"", (char*)"--generator=SIDEWINDER",
                   (char*)"--size={3, 7}", (char*)"--difficulty=hard",
                   (char*)"--solver=DJIKSTRA"};
  const game::Settings settings = game::ReadFlags(argc, argv);
  ASSERT_EQ(settings.generator_type, maze::GeneratorType::SIDEWINDER);
  ASSERT_EQ(settings.solver_type, maze::SolverType::DJIKSTRA);
  ASSERT_EQ(settings.path_type, maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
  ASSERT_EQ(settings.difficulty, game::DifficultyLevel::HARD);
  ASSERT_EQ(settings.starting_size, maze::CellSize(3, 7));
}

TEST_F(Settings, ReadFlags3) {
  const int argc1 = 4;
  char* argv1[4] = {(char*)"", (char*)"--generator=ellers",
                    (char*)"--path_type=left_two_right", (char*)"--size={3,3}"};
  ASSERT_THROW(game::ReadFlags(argc1, argv1), std::invalid_argument);

  const int argc2 = 5;
  char* argv2[5] = {(char*)"", (char*)"generator=SIDEWINDER",
                    (char*)"--size={3, 7}", (char*)"--difficulty=hard",
                    (char*)"--solver=DJIKSTRA"};
  ASSERT_THROW(game::ReadFlags(argc2, argv2), std::invalid_argument);
}

}  // namespace
}  // namespace tests
