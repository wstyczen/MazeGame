#include "recursive_backtracking_generator.hpp"

#include <deque>
#include <memory>
#include <set>

#include "layout.hpp"
#include "utility.hpp"

namespace maze {

RecursiveBacktrackingGenerator::RecursiveBacktrackingGenerator() = default;
RecursiveBacktrackingGenerator::~RecursiveBacktrackingGenerator() = default;

std::unique_ptr<Layout> RecursiveBacktrackingGenerator::Get(
    const uint16_t& cells_vertical,
    const uint16_t& cells_horizontal
) {
  auto maze_layout = std::make_unique<Layout>(cells_vertical, cells_horizontal);
  InitializeUnvisited(maze_layout->rows(), maze_layout->cols());

  Move(maze_layout.get(), PickRandomUnvisited());

  return std::move(maze_layout);
}

void RecursiveBacktrackingGenerator::Move(
    Layout* const layout,
    const Position& starting_position
) {
  std::deque<Direction> randomized_directions = GetRandomizedMoveDirections();

  while (!randomized_directions.empty()) {
    const Edge edge = Edge(starting_position, randomized_directions.front());
    const Position destination = *edge.To();
    if (unvisited_.contains(destination) && layout->IsWithin(destination)) {
      unvisited_.erase(destination);
      layout->Unblock(edge);
      Move(layout, *edge.To());
    }
    randomized_directions.pop_front();
  }
}

}  // namespace maze
