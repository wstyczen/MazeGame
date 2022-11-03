#include "breadth_first_search_solver.hpp"

#include <algorithm>
#include <map>
#include <optional>
#include <queue>
#include <set>
#include <unordered_set>
#include <vector>

#include "utility.hpp"

namespace maze {

BreadthFirstSearchSolver::BreadthFirstSearchSolver() = default;
BreadthFirstSearchSolver::~BreadthFirstSearchSolver() = default;

std::optional<Path> BreadthFirstSearchSolver::Solve(
    const Layout* const layout,
    const Cell& start,
    const Cell& goal
) {
  static const auto directions = GetValidMoveDirections();

  SetParameters(layout, start, goal);

  std::queue<Cell> to_visit;
  std::unordered_set<Cell> visited;
  std::map<Cell, Cell> predecessors;

  visited.insert(start);
  to_visit.push(start);

  while (!to_visit.empty()) {
    const Cell& position = to_visit.front();
    visited.insert(position);
    for (const Direction& direction : directions) {
      const Edge edge(position, direction);
      if (!layout->CanMove(edge))
        continue;
      const Cell adjacent_position = *edge.To();
      if (visited.contains(adjacent_position))
        continue;
      predecessors[adjacent_position] = position;
      if (adjacent_position == goal)
        break;
      to_visit.push(adjacent_position);
    }
    to_visit.pop();
  }

  if (!predecessors.contains(goal))
    return std::nullopt;

  Path path{goal};
  Cell predecessor = goal;
  while (predecessors.contains(predecessor)) {
    predecessor = predecessors.at(predecessor);
    path.push_back(predecessor);
  }
  std::reverse(path.begin(), path.end());

  return path;
}

}  // namespace maze