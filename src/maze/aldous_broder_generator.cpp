#include "aldous_broder_generator.hpp"

#include "layout.hpp"

namespace maze {

AldousBroderGenerator::AldousBroderGenerator() = default;

AldousBroderGenerator::~AldousBroderGenerator() = default;

std::unique_ptr<Layout> AldousBroderGenerator::Get(
    const uint16_t& cells_vertical,
    const uint16_t& cells_horizontal
) {
  auto maze_layout = std::make_unique<Layout>(cells_vertical, cells_horizontal);
  InitializeUnvisited(maze_layout->rows(), maze_layout->rows());

  static const std::function<bool(const Position&, const Direction&)>
      validity_check =
          [this, &maze_layout](
              const Position& origin, const Direction& direction
          ) { return maze_layout->IsWithin(*Edge(origin, direction).To()); };

  Position position = PickRandom();
  // Choose any cell - visited or not - and travel through until all cells have
  // been visited
  while (!unvisited_.empty()) {
    const Edge move(
        position, *GetRandomMoveDirection(
                      std::bind(validity_check, position, std::placeholders::_1)
                  )
    );
    const Position destination = *move.To();
    if (unvisited_.contains(destination)) {
      maze_layout->Unblock(move);
      unvisited_.erase(destination);
    }
    position = destination;
  }

  return std::move(maze_layout);
}

}  // namespace maze
