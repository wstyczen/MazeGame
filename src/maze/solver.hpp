#ifndef MAZE_SOLVER_HPP_
#define MAZE_SOLVER_HPP_

#include "layout.hpp"
#include "utility.hpp"

#include <optional>
#include <vector>

namespace maze {

enum class PathType {
  BOTTOM_TO_TOP,
  BOTTOM_LEFT_TO_TOP_RIGHT,
  LEFT_TO_RIGHT,
  TOP_LEFT_TO_BOTTOM_RIGHT,
  TOP_TO_BOTTOM,
};

class Solver {
 public:
  virtual ~Solver();
  virtual std::optional<Path> Solve(
      const Layout* const layout,
      const Position& start,
      const Position& goal
  ) = 0;
  std::optional<Path> Solve(
      const Layout* const layout,
      const PathType path_type = PathType::TOP_LEFT_TO_BOTTOM_RIGHT
  );

 protected:
  void SetParameters(
      const Layout* const layout,
      const Position& start,
      const Position& goal
  );

  const Layout* layout_;
  Position start_;
  Position goal_;
};

}  // namespace maze

#endif  // MAZE_SOLVER_HPP_
