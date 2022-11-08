#ifndef MAZE_A_STAR_SOLVER_HPP_
#define MAZE_A_STAR_SOLVER_HPP_

#include "maze/predecessors.hpp"
#include "maze/solvers/solver.hpp"

#include <unordered_map>

namespace maze {

class AStarSolver : public Solver, public Predecessors {
 public:
  ~AStarSolver();

  std::optional<Path> Solve(const Layout* const layout,
                            const Cell& start,
                            const Cell& goal) final;

 private:
  AStarSolver();

  std::unordered_map<Cell, uint16_t> g_values_;

  friend class SolverFactory;
};

}  // namespace maze

#endif  // MAZE_A_STAR_SOLVER_HPP_
