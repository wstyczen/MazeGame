#ifndef MAZE_BREADTH_FIRST_SEARCH_SOLVER_HPP_
#define MAZE_BREADTH_FIRST_SEARCH_SOLVER_HPP_

#include <optional>

#include "layout.hpp"
#include "solver.hpp"
#include "utility.hpp"

namespace maze {

class BreadthFirstSearchSolver : public Solver {
 public:
  ~BreadthFirstSearchSolver();

  std::optional<Path> Solve(
      const Layout* const layout,
      const Cell& start,
      const Cell& goal
  ) override;

 private:
  BreadthFirstSearchSolver();

  friend class SolverFactory;
};

}  // namespace maze

#endif  // MAZE_BREADTH_FIRST_SEARCH_SOLVER_HPP_
