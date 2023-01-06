#ifndef MAZE_SOLVER_HPP_
#define MAZE_SOLVER_HPP_

#include "maze/layout.hpp"
#include "maze/paths.hpp"
#include "maze/utility.hpp"

#include <optional>
#include <vector>

namespace maze {

class Solver {
 public:
  virtual ~Solver();
  virtual std::optional<Path> Solve(const Layout* const layout,
                                    const Cell& start,
                                    const Cell& goal) = 0;
  std::optional<Path> Solve(
      const Layout* const layout,
      const PathType path_type = PathType::TOP_LEFT_TO_BOTTOM_RIGHT);

 protected:
  void SetParameters(const Layout* const layout,
                     const Cell& start,
                     const Cell& goal);

  const Layout* layout_;
  Cell start_;
  Cell goal_;
};

}  // namespace maze

#endif  // MAZE_SOLVER_HPP_
