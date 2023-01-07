#include "gtest/gtest.h"

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace tests {
namespace {

class MazeLayout : public ::testing::Test {};

TEST_F(MazeLayout, InitLayout) {
  auto layout = maze::Layout({7, 9});
  EXPECT_EQ(layout.size(), maze::LayoutSize(15, 19));
  EXPECT_EQ(layout.middle_row(), 7);
  EXPECT_EQ(layout.middle_col(), 9);
  EXPECT_EQ(layout.bottom_row(), 13);
  EXPECT_EQ(layout.rightmost_col(), 17);
}

TEST_F(MazeLayout, IsWithin) {
  auto layout = maze::Layout({3, 3});
  EXPECT_TRUE(layout.IsWithin({6, 6}));
  EXPECT_FALSE(layout.IsWithin({6, 7}));
}

TEST_F(MazeLayout, IsACell) {
  auto layout = maze::Layout({3, 3});
  EXPECT_TRUE(layout.IsACell({3, 3}));
  EXPECT_FALSE(layout.IsACell({3, 4}));
}

TEST_F(MazeLayout, IsBlocked) {
  auto layout_grid = maze::Layout({7, 9});
  EXPECT_TRUE(layout_grid.IsBlocked(maze::Cell(1, 2)));
  auto layout_empty = maze::Layout({7, 9}, maze::Layout::Base::EMPTY);
  EXPECT_FALSE(layout_empty.IsBlocked(maze::Cell(1, 2)));
}

TEST_F(MazeLayout, CanMove) {
  auto layout_grid = maze::Layout({7, 9});
  EXPECT_FALSE(
      layout_grid.CanMove(maze::Edge(maze::Cell(1, 1), maze::Direction::DOWN)));
  auto layout_empty = maze::Layout({7, 9}, maze::Layout::Base::EMPTY);
  EXPECT_TRUE(layout_empty.CanMove(
      maze::Edge(maze::Cell(1, 1), maze::Direction::DOWN)));
}

TEST_F(MazeLayout, Unblock) {
  auto layout_grid = maze::Layout({7, 9});
  layout_grid.Unblock({{1, 1}, maze::Direction::DOWN});
  EXPECT_FALSE(layout_grid.IsBlocked(maze::Cell(2, 1)));
  EXPECT_TRUE(
      layout_grid.CanMove(maze::Edge(maze::Cell(1, 1), maze::Direction::DOWN)));
  layout_grid.Unblock(maze::Cell(1, 2));
  EXPECT_FALSE(layout_grid.IsBlocked(maze::Cell(1, 2)));
  EXPECT_TRUE(layout_grid.CanMove(
      maze::Edge(maze::Cell(1, 1), maze::Direction::RIGHT)));
}

TEST_F(MazeLayout, Block) {
  auto layout_empty = maze::Layout({7, 9}, maze::Layout::Base::EMPTY);
  layout_empty.Block(maze::Cell(2, 1));
  EXPECT_TRUE(layout_empty.IsBlocked(maze::Cell(2, 1)));
  EXPECT_FALSE(layout_empty.CanMove(
      maze::Edge(maze::Cell(1, 1), maze::Direction::DOWN)));
}

} // namespace
} // namespace tests
