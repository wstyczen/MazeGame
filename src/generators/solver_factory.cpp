#include "solver_factory.hpp"

#include <memory>

#include "breadth_first_search_solver.hpp"

namespace maze {

SolverFactory* SolverFactory::instance_ = nullptr;

SolverFactory::SolverFactory() = default;
SolverFactory::~SolverFactory() = default;

SolverFactory* SolverFactory::GetInstance() {
  if (!instance_)
    instance_ = new SolverFactory;
  return instance_;
}

std::unique_ptr<Solver> SolverFactory::GetSolver(const SolverType& solver_type
) const {
  switch (solver_type) {
    case SolverType::BREADTH_FIRST_SEARCH:
      return std::unique_ptr<Solver>(new BreadthFirstSearchSolver);
  }
  return nullptr;
}

}  // namespace maze
