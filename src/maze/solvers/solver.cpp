#include "solver.hpp"

#include <cassert>

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace maze {

Solver::~Solver() = default;

std::optional<Path> Solver::Solve(const Layout* const layout,
                                  const PathType path_type) {
  const auto& [start, goal] = GetStartAndGoal(layout, path_type);
  return Solve(layout, start, goal);
}

void Solver::SetParameters(const Layout* const layout,
                           const Cell& start,
                           const Cell& goal) {
  layout_ = layout;
  start_ = start;
  goal_ = goal;
}

}  // namespace maze
