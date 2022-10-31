#ifndef MAZE_SOLVER_FACTORY_HPP_
#define MAZE_SOLVER_FACTORY_HPP_

#include <memory>

#include "solver.hpp"

namespace maze {

enum class SolverType {
  BREADTH_FIRST_SEARCH,
};

class SolverFactory {
 public:
  static SolverFactory* GetInstance();

  std::unique_ptr<Solver> GetSolver(const SolverType& solver_type) const;

 private:
  SolverFactory();
  ~SolverFactory();
  static SolverFactory* instance_;
};

}  // namespace maze

#endif  // MAZE_SOLVER_FACTORY_HPP_
