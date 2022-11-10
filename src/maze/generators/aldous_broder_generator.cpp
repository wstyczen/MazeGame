#include "maze/generators/aldous_broder_generator.hpp"

#include "maze/layout.hpp"

namespace maze {

AldousBroderGenerator::AldousBroderGenerator() = default;

AldousBroderGenerator::~AldousBroderGenerator() = default;

std::unique_ptr<Layout> AldousBroderGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);

  InitializeUnvisited(layout->size());

  static const MoveGeneralValidityCheck validity_check =
      [this, &layout](const Cell& origin, const Direction& direction) {
        return layout->IsWithin(*Edge(origin, direction).To());
      };

  Cell cell = PickRandomUnvisited();
  // Choose any cell - visited or not - and travel through until all cells have
  // been visited
  while (!unvisited_.empty()) {
    const Edge move(cell, *GetRandomMoveDirection(std::bind(
                              validity_check, cell, std::placeholders::_1)));
    const Cell destination = *move.To();
    if (unvisited_.contains(destination)) {
      layout->Unblock(move);
      unvisited_.erase(destination);
    }
    cell = destination;
  }

  return std::move(layout);
}

}  // namespace maze
