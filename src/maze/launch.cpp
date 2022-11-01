#include "generator.hpp"
#include "generator_factory.hpp"
#include "layout.hpp"
#include "solver.hpp"
#include "solver_factory.hpp"

#include <ctime>
#include <iostream>
#include <memory>

int main() {
  std::srand(std::time(0));  // use current time as seed for random generators

  std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(
          maze::GeneratorType::GROWING_TREE
      );
  // const std::unique_ptr<maze::Layout> maze_layout = generator->Get(17, 33);
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
