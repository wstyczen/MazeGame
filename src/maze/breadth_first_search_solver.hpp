#ifndef MAZE_BREADTH_FIRST_SEARCH_SOLVER_HPP_
#define MAZE_BREADTH_FIRST_SEARCH_SOLVER_HPP_

#include <optional>

#include "solver.hpp"
#include "layout.hpp"
#include "utility.hpp"

namespace maze {

class BreadthFirstSearchSolver : public Solver {
 public:
  ~BreadthFirstSearchSolver();

  std::optional<Path> Solve(
      const Layout* const layout,
      const Position& start,
      const Position& goal
  ) override;

 private:
  BreadthFirstSearchSolver();

  friend class SolverFactory;
};

}  // namespace maze

#endif  // MAZE_BREADTH_FIRST_SEARCH_SOLVER_HPP_
