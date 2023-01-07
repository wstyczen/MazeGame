#include "gtest/gtest.h"

#include "maze/utility.hpp"

namespace tests {
namespace {

class MazeUtility : public ::testing::Test {};

TEST_F(MazeUtility, InitPosition) {
  maze::Position pos = {1, 2};
  EXPECT_EQ(pos.row, 1);
  EXPECT_EQ(pos.col, 2);
}

TEST_F(MazeUtility, PositionEquality) {
  maze::Position p1 = {1, 2};
  maze::Position p2 = {1, 2};
  maze::Position p3 = {2, 2};
  EXPECT_EQ(p1, p2);
  EXPECT_NE(p1, p3);
}

TEST_F(MazeUtility, PositionLessThan) {
  maze::Position p1 = {1, 2};
  maze::Position p2 = {1, 2};
  maze::Position p3 = {5, 2};
  maze::Position p4 = {5, 1};
  maze::Position p5 = {5, 3};
  EXPECT_FALSE(p1 < p2);
  EXPECT_TRUE(p1 < p3);
  EXPECT_FALSE(p3 < p4);
  EXPECT_TRUE(p3 < p5);
}

TEST_F(MazeUtility, InitEdge) {
  maze::Edge edge = {{1, 1}, maze::Direction::DOWN};
  EXPECT_EQ(edge.from, maze::Cell(1, 1));
  EXPECT_EQ(edge.direction, maze::Direction::DOWN);
}

TEST_F(MazeUtility, EdgeTo) {
  maze::Edge e1 = {{1, 1}, maze::Direction::DOWN};
  EXPECT_TRUE(e1.To());
  EXPECT_EQ(*e1.To(), maze::Cell(3, 1));
  maze::Edge e2 = {{5, 7}, maze::Direction::LEFT};
  EXPECT_TRUE(e2.To());
  EXPECT_EQ(*e2.To(), maze::Cell(5, 5));
}

TEST_F(MazeUtility, EdgeFromTwoCells) {
  auto e1 = maze::Edge::FromTwoCells({1, 1}, {3, 1});
  EXPECT_EQ(e1.direction, maze::Direction::DOWN);
  EXPECT_EQ(e1.from, maze::Cell(1, 1));
  auto e2 = maze::Edge::FromTwoCells({5, 7}, {5, 5});
  EXPECT_EQ(e2.direction, maze::Direction::LEFT);
  EXPECT_EQ(e2.from, maze::Cell(5, 7));
}

TEST_F(MazeUtility, Size) {
  maze::Size size = {7, 9};
  EXPECT_EQ(size.rows, 7);
  EXPECT_EQ(size.cols, 9);
  EXPECT_EQ(size, maze::Size(7, 9));
}

TEST_F(MazeUtility, MoveValidityCheck) {
  static const maze::MoveGeneralValidityCheck check =
      [](const maze::Cell &origin, const maze::Direction &direction) {
        return origin.row != 3 && direction != maze::Direction::RIGHT;
      };

  auto valid_move_directions_1 = maze::GetValidMoveDirections(
      std::bind(check, maze::Cell(3, 1), std::placeholders::_1));
  EXPECT_EQ(valid_move_directions_1.size(), 0);
  auto valid_move_directions_2 = maze::GetValidMoveDirections(
      std::bind(check, maze::Cell(2, 1), std::placeholders::_1));
  EXPECT_EQ(valid_move_directions_2.size(), 3);
}

} // namespace
} // namespace tests
