#include "wilsons_generator.hpp"

#include "layout.hpp"
#include "utility.hpp"

namespace maze {

WilsonsGenerator::WilsonsGenerator() = default;
WilsonsGenerator::~WilsonsGenerator() = default;

std::unique_ptr<Layout> WilsonsGenerator::Get(
    const uint16_t& vertical_cells,
    const uint16_t& horizontal_cells
) {
  auto maze_layout = std::make_unique<Layout>(vertical_cells, horizontal_cells);
  InitializeUnvisited(maze_layout->rows(), maze_layout->rows());

  static const std::function<bool(const Position&, const Direction&)>
      validity_check =
          [this, &maze_layout](
              const Position& origin, const Direction& direction
          ) { return maze_layout->IsWithin(*Edge(origin, direction).To()); };

  std::map<Position, Direction> walk;

  PickRandomUnvisited();  // first cell in the tree
  while (!unvisited_.empty()) {
    // Pick a random cell.
    const Position starting_cell = PickRandomUnvisited(false);
    // Walk until you encounter a cell already in the tree, saving the most
    // recent move direction for each cell in walk_.
    Position cell = starting_cell;
    while (unvisited_.contains(cell)) {
      const Direction random_direction = *GetRandomMoveDirection(
          std::bind(validity_check, cell, std::placeholders::_1)
      );
      walk[cell] = random_direction;
      cell = *Edge(cell, random_direction).To();
    }
    const Position end_cell = cell;
    // Recreate the path from walk_ - relying on the saved move
    // directions - and add those cells the maze.
    cell = starting_cell;
    while (cell != end_cell) {
      unvisited_.erase(cell);
      const Edge move(cell, walk.at(cell));
      maze_layout->Unblock(move);
      cell = *move.To();
    }
    // Clear the path and do it again until all the cells have been visited.
    walk.clear();
  }

  return std::move(maze_layout);
}

}  // namespace maze
