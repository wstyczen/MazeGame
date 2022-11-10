#include "maze/generators/prims_generator.hpp"

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace maze {

namespace {

Edge PickRandomEdgeFromFrontier(Frontier& frontier) {
  // Pick destination
  auto frontier_iter = frontier.begin();
  std::advance(frontier_iter, GetRandomNumber(frontier.size() - 1));
  const Cell destination = frontier_iter->first;
  // Pick origin
  std::vector<Cell>& valid_origins = frontier_iter->second;
  auto origin_iter = valid_origins.begin();
  std::advance(origin_iter, GetRandomNumber(valid_origins.size() - 1));
  Cell origin = *origin_iter;

  const Edge edge = Edge::FromTwoCells(origin, destination);
  frontier.erase(frontier_iter);
  return edge;
}

}  // namespace

PrimsGenerator::PrimsGenerator() = default;

PrimsGenerator::~PrimsGenerator() = default;

std::unique_ptr<Layout> PrimsGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);

  InitializeUnvisited(layout->size());

  static const MoveGeneralValidityCheck validity_check =
      [this, &layout](const Cell& origin, const Direction& direction) {
        const Cell destination = *Edge(origin, direction).To();
        return layout->IsWithin(destination) &&
               unvisited_.contains(destination);
      };

  Cell cell = PickRandomUnvisited();

  while (!unvisited_.empty()) {
    for (const Direction& direction : GetValidMoveDirections(
             std::bind(validity_check, cell, std::placeholders::_1))) {
      const Cell destination = *Edge(cell, direction).To();
      if (frontier_.contains(destination))
        frontier_.at(destination).push_back(cell);
      else
        frontier_[destination] = {cell};
    }
    const Edge edge = PickRandomEdgeFromFrontier(frontier_);
    layout->Unblock(edge);
    cell = *edge.To();
    unvisited_.erase(cell);
  }

  return std::move(layout);
}

}  // namespace maze
