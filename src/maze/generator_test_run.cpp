#include "generator_test_run.hpp"

#include <stdint.h>
#include <array>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "solver_factory.hpp"

namespace maze {

namespace {

constexpr SolverType kSolverType = SolverType::BREADTH_FIRST_SEARCH;
constexpr PathType kPathType = PathType::TOP_LEFT_TO_BOTTOM_RIGHT;
constexpr std::array kTestSizes = {
    uint16_t{11},
    uint16_t{33},
    uint16_t{81},
    uint16_t{111},
};

void Run(
    Generator* const generator,
    Solver* const solver,
    const uint16_t& size
) {
  auto before_generating = std::chrono::high_resolution_clock::now();
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get(size, size);
  auto after_generating = std::chrono::high_resolution_clock::now();
  const auto generation_duration = std::chrono::duration<double, std::milli>(
      after_generating - before_generating
  );

  std::optional<maze::Path> path = solver->Solve(maze_layout.get(), kPathType);

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Size:\t\t\t" << size << "x" << size << "\n";
  std::cout << "Time:\t\t\t" << generation_duration << "\n";
  if (path)
    std::cout << "Path:\t\t\t" << path->size() << " moves\n";
  else
    std::cout << "No path found.\n";

  std::cout << "\n";
}

}  // namespace

void GeneratorTestRun(const GeneratorType& generator_type) {
  std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(generator_type);
  std::unique_ptr<maze::Solver> solver =
      maze::SolverFactory::GetInstance()->GetSolver(kSolverType);

  std::cout << "=> "
            << GeneratorFactory::GetInstance()->GetGeneratorName(generator_type)
            << ":\n\n";
  for (const uint16_t& size : kTestSizes)
    Run(generator.get(), solver.get(), size);

  std::cout << "\n";
}

void GeneratorsTestRun() {
  for (auto i = static_cast<int>(GeneratorType::FIRST);
       i <= static_cast<int>(GeneratorType::LAST); i++)
    GeneratorTestRun(static_cast<GeneratorType>(i));
}

}  // namespace maze
