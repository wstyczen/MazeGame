#include "generators/breadth_first_search_solver.hpp"
#include "generators/generator.hpp"
#include "generators/generator_factory.hpp"
#include "generators/kruskals_generator.hpp"
#include "generators/layout.hpp"
#include "generators/solver.hpp"
#include "generators/solver_factory.hpp"

#include <ctime>
#include <iostream>
#include <memory>

int main() {
  std::srand(std::time(0));  // use current time as seed for random generators

  std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(
          maze::GeneratorType::RECURSIVE_BACKGTRACKING
      );
  // const std::unique_ptr<maz e::Layout> maze_layout = generator->Get(17, 33);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get(11, 11);

  std::unique_ptr<maze::Solver> bfs =
      maze::SolverFactory::GetInstance()->GetSolver(
          maze::SolverType::BREADTH_FIRST_SEARCH
      );
  std::optional<maze::Path> path =
      bfs->Solve(maze_layout.get(), maze::PathType::BOTTOM_LEFT_TO_TOP_RIGHT);
  maze_layout->AddPath(*path);

  maze_layout->Show();

  return 0;
}
