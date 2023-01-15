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
  maze::Path GetExpectedSolution(const uint16_t& size,
                                 const maze::PathType& path_type) {
    if (path_type == maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT) {
      if (size == 3)
        return {{1, 1}, {1, 3}, {1, 5}, {3, 5}, {5, 5}};
      if (size == 5)
        return {{1, 1},  {1, 3},  {3, 3},  {3, 1},  {5, 1}, {5, 3},  {5, 5},
                {3, 5},  {1, 5},  {1, 7},  {3, 7},  {3, 9}, {3, 11}, {3, 13},
                {5, 13}, {5, 11}, {7, 11}, {7, 13}, {9, 13}};
      throw std::invalid_argument("Invalid maze size for this test: '" +
                                  std::to_string(size) + "'");
    }
    if (path_type == maze::PathType::LEFT_TO_RIGHT) {
      if (size == 3)
        return {{3, 1}, {3, 3}, {5, 3}, {5, 5}, {3, 5}};
      if (size == 5)
        return {{5, 1}, {5, 3}, {5, 5},  {3, 5},  {1, 5}, {1, 7},
                {3, 7}, {3, 9}, {3, 11}, {3, 13}, {5, 13}};
      throw std::invalid_argument("Invalid maze size for this test: '" +
                                  std::to_string(size) + "'");
    }
    throw std::invalid_argument("Invalid path type for this test.");
  }
  void ExpectCorrectSolution(
      const std::optional<maze::Path> calculated_solution,
      const maze::Path& expected_solution) {
    ASSERT_TRUE(calculated_solution);
    EXPECT_EQ(calculated_solution->size(), expected_solution.size());
    EXPECT_EQ(*calculated_solution, expected_solution);
  }
  void ExpectCorrect3x3Solution(maze::Solver* solver,
                                const maze::PathType& path_type) {
    ExpectCorrectSolution(solver->Solve(&layout3x3_, path_type),
                          GetExpectedSolution(3, path_type));
  }
  void ExpectCorrect5x7Solution(maze::Solver* solver,
                                const maze::PathType& path_type) {
    ExpectCorrectSolution(solver->Solve(&layout5x7_, path_type),
                          GetExpectedSolution(5, path_type));
  }

  const maze::Layout layout3x3_ = maze::Layout::FromString(
      "#######\n"
      "#     #\n"
      "##### #\n"
      "#   # #\n"
      "### # #\n"
      "#     #\n"
      "#######");
  const maze::Layout layout5x7_ = maze::Layout::FromString(
      "###############\n"
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

  const std::unique_ptr<maze::Solver> bfs_solver =
      maze::SolverFactory::GetInstance()->GetSolver(
          maze::SolverType::BREADTH_FIRST_SEARCH);
  const std::unique_ptr<maze::Solver> djikstra_solver =
      maze::SolverFactory::GetInstance()->GetSolver(maze::SolverType::DJIKSTRA);
  const std::unique_ptr<maze::Solver> a_star_solver =
      maze::SolverFactory::GetInstance()->GetSolver(maze::SolverType::A_STAR);
};

TEST_F(MazeSolvers, BreadthFirstSearch3x3_TopLeftToBottomRight) {
  ExpectCorrect3x3Solution(bfs_solver.get(),
                           maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, BreadthFirstSearch3x3_LeftToRight) {
  ExpectCorrect3x3Solution(bfs_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, BreadthFirstSearch5x7_TopLeftToBottomRight) {
  ExpectCorrect5x7Solution(bfs_solver.get(),
                           maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, BreadthFirstSearch5x7_LeftToRight) {
  ExpectCorrect5x7Solution(bfs_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, Djikstra3x3_TopLeftToBottomRight) {
  ExpectCorrect3x3Solution(djikstra_solver.get(),
                           maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, Djikstra3x3_LeftToRight) {
  ExpectCorrect3x3Solution(djikstra_solver.get(),
                           maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, Djikstra5x7_TopLeftToBottomRight) {
  ExpectCorrect5x7Solution(djikstra_solver.get(),
                           maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, Djikstra5x7_LeftToRight) {
  ExpectCorrect5x7Solution(djikstra_solver.get(),
                           maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, AStar3x3_TopLeftToBottomRight) {
  ExpectCorrect3x3Solution(a_star_solver.get(),
                           maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, AStar3x3_LeftToRight) {
  ExpectCorrect3x3Solution(a_star_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

TEST_F(MazeSolvers, AStar5x7_TopLeftToBottomRight) {
  ExpectCorrect5x7Solution(a_star_solver.get(),
                           maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
}
TEST_F(MazeSolvers, AStar5x7_LeftToRight) {
  ExpectCorrect5x7Solution(a_star_solver.get(), maze::PathType::LEFT_TO_RIGHT);
}

}  // namespace
}  // namespace tests
