#include "gtest/gtest.h"

#include "maze/layout.hpp"
#include "maze/paths.hpp"

namespace tests {
namespace {

class MazePaths : public ::testing::Test {};

TEST_F(MazePaths, BottomToTop) {
  auto layout = maze::Layout({7, 9});
  auto [start, goal] =
      maze::GetStartAndGoal(&layout, maze::PathType::BOTTOM_TO_TOP);
  EXPECT_EQ(start, maze::Cell(13, 9));
  EXPECT_EQ(goal, maze::Cell(1, 9));
}

TEST_F(MazePaths, BottomLeftToTopRight) {
  auto layout = maze::Layout({7, 9});
  auto [start, goal] =
      maze::GetStartAndGoal(&layout, maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);
  EXPECT_EQ(start, maze::Cell(13, 1));
  EXPECT_EQ(goal, maze::Cell(1, 17));
}

TEST_F(MazePaths, LeftToRight) {
  auto layout = maze::Layout({7, 9});
  auto [start, goal] =
      maze::GetStartAndGoal(&layout, maze::PathType::LEFT_TO_RIGHT);
  EXPECT_EQ(start, maze::Cell(7, 1));
  EXPECT_EQ(goal, maze::Cell(7, 17));
}

TEST_F(MazePaths, TopLeftToBottomRight) {
  auto layout = maze::Layout({7, 9});
  auto [start, goal] =
      maze::GetStartAndGoal(&layout, maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
  EXPECT_EQ(start, maze::Cell(1, 1));
  EXPECT_EQ(goal, maze::Cell(13, 17));
}

TEST_F(MazePaths, TopToBottom) {
  auto layout = maze::Layout({7, 9});
  auto [start, goal] =
      maze::GetStartAndGoal(&layout, maze::PathType::TOP_TO_BOTTOM);
  EXPECT_EQ(start, maze::Cell(1, 9));
  EXPECT_EQ(goal, maze::Cell(13, 9));
}

} // namespace
} // namespace tests
