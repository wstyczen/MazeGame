#include "maze/generators/recursive_backtracking_generator.hpp"

#include <deque>
#include <memory>
#include <set>

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace maze {

RecursiveBacktrackingGenerator::RecursiveBacktrackingGenerator() = default;
RecursiveBacktrackingGenerator::~RecursiveBacktrackingGenerator() = default;

std::unique_ptr<Layout> RecursiveBacktrackingGenerator::Get(
    const CellSize& cell_size
) {
  auto layout = std::make_unique<Layout>(cell_size);
  InitializeUnvisited(layout->size());

  Move(layout.get(), PickRandomUnvisited());

  return std::move(layout);
}

void RecursiveBacktrackingGenerator::Move(
    Layout* const layout,
    const Cell& origin
) {
  std::deque<Direction> randomized_directions = GetRandomizedMoveDirections();

  while (!randomized_directions.empty()) {
    const Edge edge(origin, randomized_directions.front());
    const Cell destination = *edge.To();
    if (layout->IsWithin(destination) && unvisited_.contains(destination)) {
      unvisited_.erase(destination);
      layout->Unblock(edge);
      Move(layout, *edge.To());
    }
    randomized_directions.pop_front();
  }
}

}  // namespace maze
