#include "recursive_division_generator.hpp"

#include "maze/layout.hpp"

namespace maze {
RecursiveDivisionGenerator::RecursiveDivisionGenerator() = default;
RecursiveDivisionGenerator::~RecursiveDivisionGenerator() = default;

std::unique_ptr<Layout> RecursiveDivisionGenerator::Get(
    const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size, Layout::Base::EMPTY);

  Divide(
      layout.get(), RecursiveDivisionGenerator::DivisionDirection::HORIZONTAL,
      {kLayoutFirstCellIndex, static_cast<uint16_t>(layout->rightmost_col())},
      {kLayoutFirstCellIndex, static_cast<uint16_t>(layout->bottom_row())});

  return layout;
}

RecursiveDivisionGenerator::DivisionDirection
RecursiveDivisionGenerator::GetRandomDivisionDirection() {
  return RollAPercentChance(50)
             ? RecursiveDivisionGenerator::DivisionDirection::VERTICAL
             : RecursiveDivisionGenerator::DivisionDirection::HORIZONTAL;
}

void RecursiveDivisionGenerator::Divide(
    Layout* const layout,
    const RecursiveDivisionGenerator::DivisionDirection& division_direction,
    const RecursiveDivisionGenerator::Limits& horizontal_limits,
    const RecursiveDivisionGenerator::Limits& vertical_limits) {
  switch (division_direction) {
    case RecursiveDivisionGenerator::DivisionDirection::HORIZONTAL: {
      const uint16_t division_row = vertical_limits.PickRandom();
      const std::vector<uint16_t> wall_cols = horizontal_limits.GetWall();
      for (const uint16_t& col : wall_cols)
        layout->Block({division_row, col});
      if (division_row - 1 > vertical_limits.low)
        Divide(layout, RecursiveDivisionGenerator::DivisionDirection::VERTICAL,
               horizontal_limits,
               {vertical_limits.low, static_cast<uint16_t>(division_row - 1)});
      if (division_row + 1 < vertical_limits.high)
        Divide(layout, RecursiveDivisionGenerator::DivisionDirection::VERTICAL,
               horizontal_limits,
               {static_cast<uint16_t>(division_row + 1), vertical_limits.high});
      break;
    }
    case RecursiveDivisionGenerator::DivisionDirection::VERTICAL: {
      const uint16_t division_col = horizontal_limits.PickRandom();
      const std::vector<uint16_t> wall_rows = vertical_limits.GetWall();
      for (const uint16_t& row : wall_rows)
        layout->Block({row, division_col});
      if (division_col - 1 > horizontal_limits.low)
        Divide(layout,
               RecursiveDivisionGenerator::DivisionDirection::HORIZONTAL,
               {horizontal_limits.low, static_cast<uint16_t>(division_col - 1)},
               vertical_limits);
      if (division_col + 1 < horizontal_limits.high)
        Divide(
            layout, RecursiveDivisionGenerator::DivisionDirection::HORIZONTAL,
            {static_cast<uint16_t>(division_col + 1), horizontal_limits.high},
            vertical_limits);
      break;
    }
  }
}

}  // namespace maze
