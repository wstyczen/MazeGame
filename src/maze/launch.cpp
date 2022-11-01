#include "generator.hpp"
#include "generator_factory.hpp"
#include "generator_test_run.hpp"
#include "layout.hpp"
#include "solver.hpp"
#include "solver_factory.hpp"

#include <ctime>
#include <iostream>
#include <memory>

namespace {

void GenerateToTerminal(
    const maze::GeneratorType& generator_type,
    const maze::SolverType& solver_type,
    const maze::PathType& path_type,
    const uint16_t& vertical_cells,
    const uint16_t& horizontal_cells
) {
  std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(generator_type);
  const std::unique_ptr<maze::Layout> maze_layout =
      generator->Get(vertical_cells, horizontal_cells);

  std::unique_ptr<maze::Solver> solver =
      maze::SolverFactory::GetInstance()->GetSolver(solver_type);
  std::optional<maze::Path> path = solver->Solve(maze_layout.get(), path_type);

  if (path)
    maze_layout->AddPath(*path);
  maze_layout->Show();
}

}  // namespace

int main() {
  std::srand(std::time(0));  // use current time as seed for random generators

  // Generate a maze and print it to the terminal
  // GenerateToTerminal(
  //     maze::GeneratorType::KRUSKALS, maze::SolverType::BREADTH_FIRST_SEARCH,
  //     maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT, 11, 17
  // );

  // Run a generation test for a particular generator
  // maze::GeneatorTestRun(maze::GeneratorType::KRUSKALS);

  // Run generation test for all generators
  maze::GeneratorsTestRun();

  return 0;
}
