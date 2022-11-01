#include "growing_tree_generator.hpp"

#include <functional>

#include "utility.hpp"

namespace maze {

GrowingTreeGenerator::GrowingTreeGenerator() = default;
GrowingTreeGenerator::~GrowingTreeGenerator() = default;

std::unique_ptr<Layout> GrowingTreeGenerator::Get(
    const uint16_t& vertical_cells,
    const uint16_t& horizontal_cells
) {
  auto maze_layout = std::make_unique<Layout>(vertical_cells, horizontal_cells);

  InitializeUnvisited(maze_layout->rows(), maze_layout->cols());

  std::function<bool(const Position&, const Direction&)> validity_check =
      [this, &maze_layout](const Position& origin, const Direction& direction) {
        const Position destination = *Edge(origin, direction).To();
        return unvisited_.contains(destination) &&
               maze_layout->IsWithin(destination);
      };

  path_.push_back(PickRandom());

  Position position;
  while (!unvisited_.empty()) {
    position = path_.back();
    std::optional<Direction> move_direction = GetRandomMoveDirection(
        std::bind(validity_check, position, std::placeholders::_1)
    );
    if (!move_direction) {
      path_.pop_back();
      continue;
    }
    const Edge move(position, *move_direction);
    maze_layout->Unblock(move);
    const Position destination = *move.To();
    unvisited_.erase(destination);
    path_.push_back(destination);
  }

  return std::move(maze_layout);
}

}  // namespace maze
