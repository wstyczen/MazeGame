#include "djikstra_solver.hpp"

#include <functional>
#include <limits>
#include <utility>

namespace maze {

const uint16_t DjikstraSolver::max_distance =
    std::numeric_limits<uint16_t>::max();

DjikstraSolver::DjikstraSolver() = default;
DjikstraSolver::~DjikstraSolver() = default;

std::optional<Path> DjikstraSolver::Solve(
    const Layout* const layout,
    const Cell& start,
    const Cell& goal
) {
  SetParameters(layout, start, goal);
  predecessors_.clear();
  InitializeDistances();
  minimum_distance_queue_ = {};

  move_validity_check_ = [this](
                             const Cell& origin, const Direction& direction
                         ) {
    Edge move = Edge(origin, direction);
    return layout_->CanMove(move) && distances_.at(*move.To()) == max_distance;
  };

  distances_[start] = 0;
  minimum_distance_queue_.push({0, start});

  while (!minimum_distance_queue_.empty()) {
    if (ProcessUnvisitedWithShortestDistance())
      break;
  }

  return RecreatePath(start, goal);
}

void DjikstraSolver::InitializeDistances() {
  distances_.clear();
  const auto& [rows, cols] = layout_->size();
  for (uint16_t row = kLayoutFirstCellIndex; row < rows; row += kStep)
    for (uint16_t col = kLayoutFirstCellIndex; col < cols; col += kStep)
      distances_[{row, col}] = max_distance;
}

bool DjikstraSolver::ProcessUnvisitedWithShortestDistance() {
  const auto [distance, cell] = minimum_distance_queue_.top();
  minimum_distance_queue_.pop();

  // A simplified version of djikstra's algorithm - since all edges have the
  // same weight there is no need to compare with previous distance - the first
  // time reached will always be the shortest path

  for (const Direction& direction : GetValidMoveDirections(
           std::bind(move_validity_check_, cell, std::placeholders::_1)
       )) {
    Cell destination = *Edge(cell, direction).To();
    const uint16_t new_distance = distance + 1;

    distances_[destination] = new_distance;
    minimum_distance_queue_.push({new_distance, destination});
    predecessors_[destination] = cell;

    if (destination == goal_)
      return true;
  }

  return false;
}

}  // namespace maze
