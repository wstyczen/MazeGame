#ifndef MAZE_SOLVER_FACTORY_HPP_
#define MAZE_SOLVER_FACTORY_HPP_

#include <memory>

#include "solver.hpp"

namespace maze {

enum class SolverType {
  FIRST,
  A_STAR = FIRST,
  BREADTH_FIRST_SEARCH,
  DJIKSTRA,
  LAST = DJIKSTRA,
};

class SolverFactory {
 public:
  static SolverFactory* GetInstance();

  std::string GetSolverName(const SolverType& solver_type) const;
  std::unique_ptr<Solver> GetSolver(const SolverType& solver_type) const;

 private:
  SolverFactory();
  ~SolverFactory();
  static SolverFactory* instance_;
};

}  // namespace maze

#endif  // MAZE_SOLVER_FACTORY_HPP_
