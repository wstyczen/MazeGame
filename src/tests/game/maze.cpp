#include "gtest/gtest.h"

#include "game/maze.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace tests {
namespace {

class Maze : public ::testing::Test {
 protected:
  game::Maze GetMaze(const maze::PathType& path_type) {
    return game::Maze(
        std::make_unique<maze::Layout>(maze::Layout::FromString(layout_str_)),
        path_type);
  }

  void ExpectCorrectMoveBottomLeftToTopRight(game::Maze& maze) {
    ASSERT_FALSE(maze.Move(maze::Direction::LEFT));
    ASSERT_TRUE(maze.Move(maze::Direction::RIGHT));
    ASSERT_TRUE(maze.Move(maze::Direction::RIGHT));
    ASSERT_FALSE(maze.Move(maze::Direction::RIGHT));
    ASSERT_FALSE(maze.Move(maze::Direction::DOWN));
    ASSERT_TRUE(maze.Move(maze::Direction::UP));
    ASSERT_TRUE(maze.Move(maze::Direction::UP));
  }

  const std::string layout_str_ = std::string(
      "#######\n"
      "#     #\n"
      "##### #\n"
      "#   # #\n"
      "### # #\n"
      "#     #\n"
      "#######");
};

TEST_F(Maze, MovesMade) {
  game::Maze maze = game::Maze(maze::GeneratorFactory::GetInstance()
                                   ->GetGenerator(maze::GeneratorType::KRUSKALS)
                                   ->Get(maze::CellSize(11, 11)),
                               maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);
  int move_count = 0;
  for (int i = 0; i != 10; ++i) {
    if (maze.Move(*maze::GetRandomMoveDirection()))
      ++move_count;
  }
  ASSERT_EQ(maze.GetMovesMade(), move_count);
}

TEST_F(Maze, PositionAndGoal) {
  const auto maze1 = GetMaze(maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
  ASSERT_EQ(maze1.position(), maze::Cell(1, 1));
  ASSERT_EQ(maze1.goal(), maze::Cell(5, 5));

  const auto maze2 = GetMaze(maze::PathType::BOTTOM_TO_TOP);
  ASSERT_EQ(maze2.position(), maze::Cell(5, 3));
  ASSERT_EQ(maze2.goal(), maze::Cell(1, 3));

  const auto maze3 = GetMaze(maze::PathType::LEFT_TO_RIGHT);
  ASSERT_EQ(maze3.position(), maze::Cell(3, 1));
  ASSERT_EQ(maze3.goal(), maze::Cell(3, 5));
}

TEST_F(Maze, Move) {
  auto maze = GetMaze(maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);
  ExpectCorrectMoveBottomLeftToTopRight(maze);
}

TEST_F(Maze, GoalReached) {
  auto maze = GetMaze(maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);
  EXPECT_FALSE(maze.GoalReached());
  ExpectCorrectMoveBottomLeftToTopRight(maze);
  EXPECT_TRUE(maze.GoalReached());
}

TEST_F(Maze, PathTaken) {
  auto maze = GetMaze(maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);

  maze::Path starting_path = {{5, 1}};
  EXPECT_EQ(*maze.path(), starting_path);
  maze::Path expected_path = {{5, 1}, {5, 3}, {5, 5}, {3, 5}, {1, 5}};
  ExpectCorrectMoveBottomLeftToTopRight(maze);
  EXPECT_EQ(*maze.path(), expected_path);
}

TEST_F(Maze, GetNextCellSize) {
  auto maze = GetMaze(maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);
  EXPECT_EQ(maze.GetNextCellSize(game::DifficultyLevel::EASY),
            maze::CellSize(5, 5));
  EXPECT_EQ(maze.GetNextCellSize(game::DifficultyLevel::NORMAL),
            maze::CellSize(7, 7));
  EXPECT_EQ(maze.GetNextCellSize(game::DifficultyLevel::HARD),
            maze::CellSize(9, 9));
}

}  // namespace
}  // namespace tests
