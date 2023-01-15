#include "hunt_and_kill_generator.hpp"

#include "maze/layout.hpp"

namespace maze {

HuntAndKillGenerator::HuntAndKillGenerator() = default;
HuntAndKillGenerator::~HuntAndKillGenerator() = default;

std::unique_ptr<Layout> HuntAndKillGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);
  InitializeUnvisited(layout->size());

  const MoveGeneralValidityCheck validity_check =
      [this, &layout](const Cell& origin, const Direction& direction) {
        const Cell destination = *Edge(origin, direction).To();
        return layout->IsWithin(destination) &&
               unvisited_.contains(destination);
      };

  // Pick random starting cell
  Cell cell = PickRandomUnvisited();

  while (!unvisited_.empty()) {
    // Traverse the grid by picking a random adjacent unvisited cell
    std::optional<Direction> direction = GetRandomMoveDirection(
        std::bind(validity_check, cell, std::placeholders::_1));

    // If current cell has no unvisited neighbours enter the 'hunt mode' - scan
    // the grid for an unvisited cell that is adjacent to a visited cell.
    // If found connect the selected cell to the visited neighbour and restart
    // the traversal from there.
    if (!direction) {
      std::optional<Cell> new_cell = Hunt(layout.get());
      if (!new_cell)
        break;
      cell = *new_cell;
      continue;
    }

    // Move to the adjacent unvisited cell in the picked direction, unblocking
    // the path.
    Edge edge(cell, *direction);
    Cell destination = *edge.To();
    layout->Unblock(edge);
    unvisited_.erase(destination);
    cell = destination;
  }

  return layout;
}

std::optional<Cell> HuntAndKillGenerator::Hunt(Layout* const layout) {
  static const MoveGeneralValidityCheck is_within_validity_check =
      [this, &layout](const Cell& origin, const Direction& direction) {
        return layout->IsWithin(*Edge(origin, direction).To());
      };

  for (uint16_t row_index = kLayoutFirstCellIndex;
       row_index <= layout->rightmost_col(); row_index += kStep)
    for (uint16_t col_index = kLayoutFirstCellIndex;
         col_index <= layout->bottom_row(); col_index += kStep) {
      const Cell cell(row_index, col_index);
      if (!unvisited_.contains(cell))
        continue;
      for (const Direction& direction : GetValidMoveDirections(std::bind(
               is_within_validity_check, cell, std::placeholders::_1))) {
        const Edge edge(cell, direction);
        if (!unvisited_.contains(*edge.To())) {
          layout->Unblock(edge);
          unvisited_.erase(cell);
          return cell;
        }
      }
    }
  return std::nullopt;
}

}  // namespace maze
