#include "growing_tree_generator.hpp"

#include <functional>

#include "utility.hpp"

namespace maze {

GrowingTreeGenerator::GrowingTreeGenerator() = default;
GrowingTreeGenerator::~GrowingTreeGenerator() = default;

std::unique_ptr<Layout> GrowingTreeGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);

  InitializeUnvisited(layout->size());

  static const std::function<bool(const Cell&, const Direction&)>
      validity_check =
          [this, &layout](const Cell& origin, const Direction& direction) {
            const Cell destination = *Edge(origin, direction).To();
            return unvisited_.contains(destination) &&
                   layout->IsWithin(destination);
          };

  path_.push_back(PickRandomUnvisited());

  Cell cell;
  while (!unvisited_.empty()) {
    cell = path_.back();
    std::optional<Direction> move_direction = GetRandomMoveDirection(
        std::bind(validity_check, cell, std::placeholders::_1)
    );
    if (!move_direction) {
      path_.pop_back();
      continue;
    }
    const Edge move(cell, *move_direction);
    layout->Unblock(move);
    const Cell destination = *move.To();
    unvisited_.erase(destination);
    path_.push_back(destination);
  }

  return std::move(layout);
}

}  // namespace maze
