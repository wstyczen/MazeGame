#include "solver_factory.hpp"

#include <cassert>
#include <memory>

#include "maze/solvers/a_star_solver.hpp"
#include "maze/solvers/breadth_first_search_solver.hpp"
#include "maze/solvers/djikstra_solver.hpp"

namespace maze {

SolverFactory* SolverFactory::instance_ = nullptr;

SolverFactory::SolverFactory() = default;
SolverFactory::~SolverFactory() = default;

SolverFactory* SolverFactory::GetInstance() {
  if (!instance_)
    instance_ = new SolverFactory;
  return instance_;
}

std::string SolverFactory::GetSolverName(const SolverType& solver_type) const {
  switch (solver_type) {
    case SolverType::A_STAR:
      return "A*";
    case SolverType::BREADTH_FIRST_SEARCH:
      return "Breadth First Search";
    case SolverType::DJIKSTRA:
      return "Djikstra's";
  }
  assert(0 && "No such solver type.");
  return "";
}

std::unique_ptr<Solver> SolverFactory::GetSolver(const SolverType& solver_type
) const {
  switch (solver_type) {
    case SolverType::A_STAR:
      return std::unique_ptr<Solver>(new AStarSolver);
    case SolverType::BREADTH_FIRST_SEARCH:
      return std::unique_ptr<Solver>(new BreadthFirstSearchSolver);
    case SolverType::DJIKSTRA:
      return std::unique_ptr<Solver>(new DjikstraSolver);
  }
  return nullptr;
}

}  // namespace maze
