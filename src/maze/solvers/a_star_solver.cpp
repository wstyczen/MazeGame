#include "maze/solvers/a_star_solver.hpp"

#include <queue>

namespace maze {

namespace {

uint16_t h(const Cell& cell, const Cell& goal) {
  // Return manhattan distance between current cell and goal
  return abs(cell.row - goal.row) / 2 + abs(cell.col - goal.col) / 2;
}

}  // namespace

AStarSolver::AStarSolver() = default;
AStarSolver::~AStarSolver() = default;

std::optional<Path> AStarSolver::Solve(const Layout* const layout,
                                       const Cell& start,
                                       const Cell& goal) {
  SetParameters(layout, start, goal);
  g_values_.clear();

  auto f = [this, &goal](const Cell& cell) {
    return g_values_.at(cell) + h(cell, goal);
  };
  auto compare_f = [&f](const Cell& first, const Cell& second) {
    // so that the smallest f is at the top
    return f(first) > f(second);
  };
  std::priority_queue<Cell, std::vector<Cell>, decltype(compare_f)> cell_queue(
      compare_f);

  MoveGeneralValidityCheck move_validity_check_ =
      [this](const Cell& origin, const Direction& direction) {
        Edge move(origin, direction);
        return layout_->CanMove(move) && !g_values_.contains(*move.To());
      };

  g_values_[start] = 0;
  cell_queue.push(start);

  while (!cell_queue.empty()) {
    Cell cell = cell_queue.top();
    cell_queue.pop();
    for (const Direction& direction : GetValidMoveDirections(
             std::bind(move_validity_check_, cell, std::placeholders::_1))) {
      Cell destination = *Edge(cell, direction).To();
      g_values_[destination] = g_values_.at(cell) + 1;
      cell_queue.push(destination);
      predecessors_[destination] = cell;
      if (destination == goal)
        return RecreatePath(goal);
    }
  }

  return std::nullopt;
}

}  // namespace maze
