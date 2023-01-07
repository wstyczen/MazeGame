#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"
#include "maze/test_run/test_run.hpp"

#include <ctime>
#include <iostream>
#include <memory>

namespace {

[[maybe_unused]] void
GenerateToTerminal(const maze::GeneratorType &generator_type,
                   const maze::SolverType &solver_type,
                   const maze::PathType &path_type,
                   const maze::CellSize &cell_size) {
  const std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(generator_type);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get(cell_size);

  const std::unique_ptr<maze::Solver> solver =
      maze::SolverFactory::GetInstance()->GetSolver(solver_type);
  const std::optional<maze::Path> path =
      solver->Solve(maze_layout.get(), path_type);

  if (path)
    maze_layout->AddPath(*path);
  maze_layout->Show();
}

} // namespace

int main() {
  // Generate a maze and print it to the terminal
  GenerateToTerminal(maze::GeneratorType::GROWING_TREE,
                     maze::SolverType::A_STAR, maze::PathType::LEFT_TO_RIGHT,
                     {67, 67});

  // Run a generation test for a single selected generator
  // maze::GeneratorTestRun(maze::GeneratorType::WILSONS);

  // Run generation test for all generators
  // maze::GeneratorsTestRun();

  return 0;
}
