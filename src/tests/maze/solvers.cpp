#include "gtest/gtest.h"

#include <memory>

#include "maze/layout.hpp"
#include "maze/paths.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

namespace tests {
namespace {

class MazeSolvers : public ::testing::Test {
protected:
  void ExpectCorrect3x3Solutions(maze::Solver *solver,
                                 const maze::PathType &path_type) {
    EXPECT_EQ(solver->Solve(&layout3x3, path_type)->size(),
              path_type == maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT
                  ? k3x3MinMoves_TopLeftToBottomRight
                  : k3x3MinMoves_LeftToRight);
  }
  void ExpectCorrect5x7Solutions(maze::Solver *solver,
                                 const maze::PathType &path_type) {
    EXPECT_EQ(solver->Solve(&layout5x7, path_type)->size(),
              path_type == maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT
                  ? k5x7MinMoves_TopLeftToBottomRight
                  : k5x7MinMoves_LeftToRight);
  }

  const maze::Layout layout3x3 = maze::Layout::FromString("#######\n"
                                                          "#     #\n"
                                                          "##### #\n"
                                                          "#   # #\n"
                                                          "### # #\n"
                                                          "#     #\n"
                                                          "#######");
  const int k3x3MinMoves_TopLeftToBottomRight = 5;
  const int k3x3MinMoves_LeftToRight = 5;
  const maze::Layout layout5x7 = maze::Layout::FromString("###############\n"
                                                          "#   #         #\n"
                                                          "### # # #######\n"
                                                          "#   # #       #\n"
                                                          "# ### ####### #\n"
                                                          "#         #   #\n"
                                                          "# ######### ###\n"
                                                          "#   #     #   #\n"
                                                          "### # ### ### #\n"
                                                          "#   # #       #\n"
                                                          "###############");
  const int k5x7MinMoves_TopLeftToBottomRight = 19;
  const int k5x7MinMoves_LeftToRight = 11;

  const std::unique_ptr<maze::Solver> bfs_solver =
      maze::SolverFactory::GetInstance()->GetSolver(
          maze::SolverType::BREADTH_FIRST_SEARCH);
  const std::unique_ptr<maze::Solver> djikstra_solver =
      maze::SolverFactory::GetInstance()->GetSolver(maze::SolverType::DJIKSTRA);
  const std::unique_ptr<maze::Solver> a_star_solver =
      maze::SolverFactory::GetInstance()->GetSolver(maze::SolverType::A_STAR);
};

TEST_F(MazeSolvers, BreadthFirstSearch3x3_TopLeftToBottomRight) {
  ExpectCorrect3x3Solutions(bfs_solver.get(),
                            maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, BreadthFirstSearch3x3_LeftToRight) {
  ExpectCorrect3x3Solutions(bfs_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, BreadthFirstSearch5x7_TopLeftToBottomRight) {
  ExpectCorrect5x7Solutions(bfs_solver.get(),
                            maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, BreadthFirstSearch5x7_LeftToRight) {
  ExpectCorrect5x7Solutions(bfs_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, Djikstra3x3_TopLeftToBottomRight) {
  ExpectCorrect3x3Solutions(djikstra_solver.get(),
                            maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, Djikstra3x3_LeftToRight) {
  ExpectCorrect3x3Solutions(djikstra_solver.get(),
                            maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, Djikstra5x7_TopLeftToBottomRight) {
  ExpectCorrect5x7Solutions(djikstra_solver.get(),
                            maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, Djikstra5x7_LeftToRight) {
  ExpectCorrect5x7Solutions(djikstra_solver.get(),
                            maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, AStar3x3_TopLeftToBottomRight) {
  ExpectCorrect3x3Solutions(a_star_solver.get(),
                            maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, AStar3x3_LeftToRight) {
  ExpectCorrect3x3Solutions(a_star_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, AStar5x7_TopLeftToBottomRight) {
  ExpectCorrect5x7Solutions(a_star_solver.get(),
                            maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, AStar5x7_LeftToRight) {
  ExpectCorrect5x7Solutions(a_star_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

} // namespace
} // namespace tests
