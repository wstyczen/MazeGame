#include "maze/solvers/predecessors.hpp"

namespace maze {

std::optional<Path> Predecessors::RecreatePath(const Cell& goal) {
  if (!predecessors_.contains(goal))
    return std::nullopt;

  Path path{goal};
  Cell predecessor = goal;
  while (predecessors_.contains(predecessor)) {
    predecessor = predecessors_.at(predecessor);
    path.push_back(predecessor);
  }
  std::reverse(path.begin(), path.end());
  return path;
}

}  // namespace maze
