#include "maze/generators/wilsons_generator.hpp"

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace maze {

WilsonsGenerator::WilsonsGenerator() = default;
WilsonsGenerator::~WilsonsGenerator() = default;

std::unique_ptr<Layout> WilsonsGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);
  InitializeUnvisited(layout->size());

  static const std::function<bool(const Cell&, const Direction&)>
      validity_check =
          [this, &layout](const Cell& origin, const Direction& direction) {
            return layout->IsWithin(*Edge(origin, direction).To());
          };

  std::map<Cell, Direction> walk;

  PickRandomUnvisited();  // first cell in the tree
  while (!unvisited_.empty()) {
    // Pick a random cell.
    const Cell starting_cell = PickRandomUnvisited(false);
    // Walk until you encounter a cell already in the tree, saving the most
    // recent move direction for each cell in walk_.
    Cell current_cell = starting_cell;
    while (unvisited_.contains(current_cell)) {
      const Direction random_direction = *GetRandomMoveDirection(
          std::bind(validity_check, current_cell, std::placeholders::_1));
      walk[current_cell] = random_direction;
      current_cell = *Edge(current_cell, random_direction).To();
    }
    const Cell end_cell = current_cell;
    // Recreate the path from walk_ - relying on the saved move
    // directions - and add those cells the maze.
    current_cell = starting_cell;
    while (current_cell != end_cell) {
      unvisited_.erase(current_cell);
      const Edge move(current_cell, walk.at(current_cell));
      layout->Unblock(move);
      current_cell = *move.To();
    }
    // Clear the path and do it again until all the cells have been visited.
    walk.clear();
  }

  return std::move(layout);
}

}  // namespace maze
