#include "generator_test_run.hpp"

#include <stdint.h>
#include <array>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>

#include "solver_factory.hpp"

namespace maze {

namespace {

constexpr PathType kPathType = PathType::TOP_LEFT_TO_BOTTOM_RIGHT;
constexpr std::array kTestSizes = {
    uint16_t{11},
    uint16_t{33},
    uint16_t{81},
    uint16_t{111},
};

std::vector<std::unique_ptr<Solver>> GetSolvers() {
  std::vector<std::unique_ptr<Solver>> solvers;
  for (int i = static_cast<int>(SolverType::FIRST);
       i != static_cast<int>(SolverType::LAST); i++)
    solvers.push_back(
        SolverFactory::GetInstance()->GetSolver(static_cast<SolverType>(i))
    );
  return solvers;
}

void RunSolvers(const Layout* const layout) {
  static const auto solvers = GetSolvers();

  std::vector<std::optional<Path>> paths;
  for (const auto& solver : solvers)
    paths.push_back(solver->Solve(layout, kPathType));
  assert(
      std::all_of(
          paths.begin(), paths.end(),
          [&paths](const std::optional<Path>& path) {
            return path == paths.at(0);
          }
      ) &&
      "All solvers should find the same shortest path."
  );

  const auto& path = paths.at(0);
  if (path)
    std::cout << "Path:\t\t\t" << path->size() << " moves\n";
  else
    std::cout << "No path found.\n";
}

void Run(Generator* const generator, const uint16_t& size) {
  auto before_generating = std::chrono::high_resolution_clock::now();
  const std::unique_ptr<maze::Layout> maze_layout =
      generator->Get({size, size});
  auto after_generating = std::chrono::high_resolution_clock::now();
  const auto generation_duration = std::chrono::duration<double, std::milli>(
      after_generating - before_generating
  );

  std::cout << std::fixed << std::setprecision(2);
  std::cout << "Size:\t\t\t" << size << "x" << size << "\n";
  std::cout << "Time:\t\t\t" << generation_duration << "\n";
  RunSolvers(maze_layout.get());

  std::cout << "\n";
}

}  // namespace

void GeneratorTestRun(const GeneratorType& generator_type) {
  std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(generator_type);

  std::cout << "=> "
            << GeneratorFactory::GetInstance()->GetGeneratorName(generator_type)
            << ":\n\n";
  for (const uint16_t& size : kTestSizes)
    Run(generator.get(), size);

  std::cout << "\n";
}

void GeneratorsTestRun() {
  for (auto i = static_cast<int>(GeneratorType::FIRST);
       i <= static_cast<int>(GeneratorType::LAST); i++)
    GeneratorTestRun(static_cast<GeneratorType>(i));
}

}  // namespace maze
