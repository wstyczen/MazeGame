#include "prims_generator.hpp"

namespace maze {

namespace {

Edge PickRandomEdgeFromFrontier(Frontier& frontier) {
  // Pick destination
  auto frontier_iter = frontier.begin();
  std::advance(frontier_iter, std::rand() % frontier.size());
  const Position destination = frontier_iter->first;
  // Pick origin
  std::vector<Position>& origins = frontier_iter->second;
  auto origin_iter = origins.begin();
  std::advance(origin_iter, std::rand() % origins.size());
  Position origin = *origin_iter;

  const Edge edge(
      origin, GetAsDirection(
                  static_cast<int16_t>(destination.y) - origin.y,
                  static_cast<int16_t>(destination.x) - origin.x
              )
  );
  frontier.erase(frontier_iter);
  return edge;
}

}  // namespace

PrimsGenerator::PrimsGenerator() = default;

PrimsGenerator::~PrimsGenerator() = default;

std::unique_ptr<Layout> PrimsGenerator::Get(
    const uint16_t& cells_vertical,
    const uint16_t& cells_horizontal
) {
  auto maze_layout = std::make_unique<Layout>(cells_vertical, cells_horizontal);

  static const std::function<bool(const Position&, const Direction&)>
      validity_check = [this, &maze_layout](
                           const Position& origin, const Direction& direction
                       ) {
        const Position destination = *Edge(origin, direction).To();
        return maze_layout->IsWithin(destination) &&
               unvisited_.contains(destination);
      };

  InitializeUnvisited(maze_layout->rows(), maze_layout->cols());
  Position position = PickRandom();

  while (!unvisited_.empty()) {
    for (const Direction& direction : GetValidMoveDirections(
             std::bind(validity_check, position, std::placeholders::_1)
         )) {
      const Position destination = *Edge(position, direction).To();
      if (frontier_.contains(destination))
        frontier_.at(destination).push_back(position);
      else
        frontier_[destination] = {position};
    }
    const Edge edge = PickRandomEdgeFromFrontier(frontier_);
    maze_layout->Unblock(edge);
    position = *edge.To();
    unvisited_.erase(position);
  }

  return std::move(maze_layout);
}

}  // namespace maze
