#include "maze/generators/sidewinder_generator.hpp"

#include <iterator>

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace maze {

namespace {

bool ShouldUnblock() {
  constexpr float kUnblockChance = .5;
  return RollAPercentChance(kUnblockChance * 100);
}

void DoUnblockRight(Layout* const layout, const Cell& cell) {
  layout->Unblock(Edge(cell, Direction::RIGHT));
}

bool MaybeUnblockRight(Layout* const layout, const Cell& cell) {
  if (!ShouldUnblock())
    return false;
  DoUnblockRight(layout, cell);
  return true;
}

void UnblockRandomUp(Layout* const layout, const std::vector<Cell>& group) {
  const Cell picked_cell =
      *std::next(group.begin(), GetRandomNumber(group.size() - 1));
  layout->Unblock(Edge(picked_cell, Direction::UP));
}

}  // namespace

SidewinderGenerator::SidewinderGenerator() = default;
SidewinderGenerator::~SidewinderGenerator() = default;

std::unique_ptr<Layout> SidewinderGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);

  const auto& [rows, cols] = layout->size();

  std::vector<Cell> group;
  for (uint16_t row_index = kLayoutFirstCellIndex; row_index < rows;
       row_index += kStep) {
    for (uint16_t col_index = kLayoutFirstCellIndex; col_index < cols;
         col_index += kStep) {
      group.push_back(Cell{row_index, col_index});
      if (row_index == kLayoutFirstCellIndex) {
        if (col_index != layout->rightmost_col())
          DoUnblockRight(layout.get(), group.back());
        continue;
      }
      if (col_index != layout->rightmost_col() &&
          MaybeUnblockRight(layout.get(), group.back()))
        continue;
      UnblockRandomUp(layout.get(), group);
      group.clear();
    }
    group.clear();
  }

  return layout;
}

}  // namespace maze
