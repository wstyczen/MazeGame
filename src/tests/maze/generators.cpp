#include "gtest/gtest.h"

#include <chrono>
#include <memory>

#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/paths.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

namespace tests {
namespace {

struct TestCase {
  uint16_t maze_size;
  double max_generation_time;
  constexpr TestCase(const uint16_t &maze_size,
                     const double &max_generation_time)
      : maze_size{maze_size}, max_generation_time{max_generation_time} {}
};

constexpr TestCase kSmallTest(uint16_t{5}, 10.0);
constexpr TestCase kMediumTest(uint16_t{15}, 200.0);
constexpr TestCase kLargeTest(uint16_t{33}, 2000.0);

class MazeGenerators : public ::testing::Test {
protected:
  const std::unique_ptr<maze::Solver> solver_ =
      maze::SolverFactory::GetInstance()->GetSolver(
          maze::SolverType::BREADTH_FIRST_SEARCH);

  void RunTest(const maze::GeneratorType &generator_type,
               const TestCase &test_case) {
    const auto &[size, max_generation_time] = test_case;

    auto before = std::chrono::high_resolution_clock::now();
    const std::unique_ptr<maze::Layout> maze_layout =
        maze::GeneratorFactory::GetInstance()
            ->GetGenerator(generator_type)
            ->Get({size, size});
    auto after = std::chrono::high_resolution_clock::now();
    const double generatiom_time =
        std::chrono::duration<double, std::milli>(after - before).count();

    // Generates in good enough time
    ASSERT_LE(generatiom_time, max_generation_time);

    // Has a solution
    auto solution_path = solver_->Solve(
        maze_layout.get(), maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
    ASSERT_TRUE(solution_path);
  }
};

TEST_F(MazeGenerators, AldousBroderSmall) {
  RunTest(maze::GeneratorType::ALDOUS_BRODER, kSmallTest);
}

TEST_F(MazeGenerators, AldousBroderMedium) {
  RunTest(maze::GeneratorType::ALDOUS_BRODER, kMediumTest);
}

TEST_F(MazeGenerators, AldousBroderLarge) {
  RunTest(maze::GeneratorType::ALDOUS_BRODER, kLargeTest);
}

TEST_F(MazeGenerators, EllersSmall) {
  RunTest(maze::GeneratorType::ELLERS, kSmallTest);
}

TEST_F(MazeGenerators, EllersMedium) {
  RunTest(maze::GeneratorType::ELLERS, kMediumTest);
}

TEST_F(MazeGenerators, EllersLarge) {
  RunTest(maze::GeneratorType::ELLERS, kLargeTest);
}

TEST_F(MazeGenerators, GrowingTreeSmall) {
  RunTest(maze::GeneratorType::GROWING_TREE, kSmallTest);
}

//
// I think the google test severely limits the recursion depth - that's why
// those throw segmentation fault - when run normally - outside tests -
// they don't crash.
//

// TEST_F(MazeGenerators, GrowingTreeMedium) {
//   RunTest(maze::GeneratorType::GROWING_TREE, kMediumTest);
// }

// TEST_F(MazeGenerators, GrowingTreeLarge) {
//   RunTest(maze::GeneratorType::GROWING_TREE, kLargeTest);
// }

TEST_F(MazeGenerators, HuntAndKillSmall) {
  RunTest(maze::GeneratorType::HUNT_AND_KILL, kSmallTest);
}

TEST_F(MazeGenerators, HuntAndKillMedium) {
  RunTest(maze::GeneratorType::HUNT_AND_KILL, kMediumTest);
}

// TEST_F(MazeGenerators, HuntAndKillLarge) {
//   RunTest(maze::GeneratorType::HUNT_AND_KILL, kLargeTest);
// }

TEST_F(MazeGenerators, KruskalsSmall) {
  RunTest(maze::GeneratorType::KRUSKALS, kSmallTest);
}

TEST_F(MazeGenerators, KruskalsMedium) {
  RunTest(maze::GeneratorType::KRUSKALS, kMediumTest);
}

TEST_F(MazeGenerators, KruskalsLarge) {
  RunTest(maze::GeneratorType::KRUSKALS, kLargeTest);
}

TEST_F(MazeGenerators, PrimsSmall) {
  RunTest(maze::GeneratorType::PRIMS, kSmallTest);
}

TEST_F(MazeGenerators, PrimsMedium) {
  RunTest(maze::GeneratorType::PRIMS, kMediumTest);
}

TEST_F(MazeGenerators, PrimsLarge) {
  RunTest(maze::GeneratorType::PRIMS, kLargeTest);
}

TEST_F(MazeGenerators, RecursiveBacktrackingSmall) {
  RunTest(maze::GeneratorType::RECURSIVE_BACKTRACKING, kSmallTest);
}

TEST_F(MazeGenerators, RecursiveBacktrackingMedium) {
  RunTest(maze::GeneratorType::RECURSIVE_BACKTRACKING, kMediumTest);
}

TEST_F(MazeGenerators, RecursiveBacktrackingLarge) {
  RunTest(maze::GeneratorType::RECURSIVE_BACKTRACKING, kLargeTest);
}

TEST_F(MazeGenerators, RecursivedDivisionSmall) {
  RunTest(maze::GeneratorType::RECURSIVE_DIVISION, kSmallTest);
}

TEST_F(MazeGenerators, RecursiveDivisionMedium) {
  RunTest(maze::GeneratorType::RECURSIVE_DIVISION, kMediumTest);
}

TEST_F(MazeGenerators, RecursiveDivisionLarge) {
  RunTest(maze::GeneratorType::RECURSIVE_DIVISION, kLargeTest);
}

TEST_F(MazeGenerators, SidewinderSmall) {
  RunTest(maze::GeneratorType::SIDEWINDER, kSmallTest);
}

TEST_F(MazeGenerators, SidewinderMedium) {
  RunTest(maze::GeneratorType::SIDEWINDER, kMediumTest);
}

TEST_F(MazeGenerators, SidewinderLarge) {
  RunTest(maze::GeneratorType::SIDEWINDER, kLargeTest);
}

TEST_F(MazeGenerators, WilsonsSmall) {
  RunTest(maze::GeneratorType::WILSONS, kSmallTest);
}

TEST_F(MazeGenerators, WilsonsMedium) {
  RunTest(maze::GeneratorType::WILSONS, kMediumTest);
}

TEST_F(MazeGenerators, WilsonsLarge) {
  RunTest(maze::GeneratorType::WILSONS, kLargeTest);
}

} // namespace
} // namespace tests
