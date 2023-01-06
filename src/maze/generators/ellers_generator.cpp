#include "maze/generators/ellers_generator.hpp"

#include <cassert>
#include <iterator>

#include "maze/layout.hpp"

namespace maze {

namespace {

using RowTrees = std::vector<std::list<CellTree>::iterator>;
using Row = std::pair<std::vector<Cell>, RowTrees>;

enum class JoinType {
  HORIZONTAL,
  VERTICAL,
};

bool ShouldJoin(const JoinType join_type) {
  // This algorithm allows for adjusting the bias - if the chance of horizontal
  // join is higher than the vertical then there will be a more horizontal path
  // generated, similarily for the opposite ratio.
  constexpr float kHorizontalJoinChance = .55;
  constexpr float kVerticalJoinChance = .45;
  const float join_chance = join_type == JoinType::HORIZONTAL
                                ? kHorizontalJoinChance
                                : kVerticalJoinChance;
  return RollAPercentChance(join_chance * 100);
}

}  // namespace

EllersGenerator::EllersGenerator() = default;
EllersGenerator::~EllersGenerator() = default;
std::unique_ptr<Layout> EllersGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);

  Row previous_row;
  for (uint16_t row_index = kLayoutFirstCellIndex;
       row_index < layout->size().rows; row_index += kStep) {
    Row row = GetRow(layout->size(), row_index);

    // For first row just merge adjacent cell randomly
    if (row_index == kLayoutFirstCellIndex) {
      MergeCellsInRow(layout.get(), row);
      previous_row = std::move(row);
      continue;
    }

    // Try to merge previous row's cells with new row's, while ensuring at least
    // one cell from each tree is selected
    auto& [cells, trees] = previous_row;
    auto& [downward_cells, downward_trees] = row;
    std::unordered_map<CellTree*, std::optional<std::vector<Cell*>>>
        not_connected_trees;
    for (uint16_t i = 0; i != trees.size(); i++) {
      auto &downward_tree = downward_trees.at(i), &tree = trees.at(i);
      auto &cell = cells.at(i), &downward_cell = downward_cells.at(i);

      if (downward_tree == tree)
        continue;
      if (!ShouldJoin(JoinType::VERTICAL)) {
        if (not_connected_trees.contains(&*tree)) {
          if (!not_connected_trees.at(&*tree))
            continue;  // Tree already merged
          not_connected_trees.at(&*tree)->push_back(&cell);
        } else
          not_connected_trees[&*tree] = {&cell};
        continue;
      }

      tree->insert(downward_tree->begin(), downward_tree->end());
      cell_trees_.erase(downward_tree);
      downward_tree = tree;

      layout->Unblock(Edge::FromTwoCells(cell, downward_cell));

      not_connected_trees.insert_or_assign(&*tree, std::nullopt);
    }

    // Select a random cell to merge downwards for trees that did not have
    // any cells merged randomly
    for (auto& [tree, cells] : not_connected_trees) {
      if (!cells)
        continue;

      Cell* picked_cell = cells->at(GetRandomNumber(cells->size() - 1));

      uint16_t downward_cell_index = picked_cell->col / kStep;
      auto& downward_cell = downward_cells.at(downward_cell_index);
      auto& downward_tree = downward_trees.at(downward_cell_index);

      tree->insert(downward_tree->begin(), downward_tree->end());
      cell_trees_.erase(downward_tree);
      downward_tree = std::find(cell_trees_.begin(), cell_trees_.end(), *tree);

      layout->Unblock(Edge::FromTwoCells(*picked_cell, downward_cell));
    }

    // At last row remove the randomness of merging adjacent cells - always
    // merge if the two are in different trees
    if (row_index == layout->bottom_row()) {
      MergeCellsInRow(layout.get(), row, false);
      break;
    }

    MergeCellsInRow(layout.get(), row);

    previous_row = std::move(row);
  }

  return layout;
}

Row EllersGenerator::GetRow(const LayoutSize& layout_size,
                            const uint16_t& row_index) {
  assert(row_index > 0 && row_index < layout_size.rows &&
         row_index % kStep != 0);
  std::vector<Cell> cells;
  RowTrees trees;

  for (int col_index = kLayoutFirstCellIndex; col_index < layout_size.cols;
       col_index += kStep) {
    Cell cell(row_index, col_index);
    cell_trees_.push_back({cell});

    cells.push_back(cell);
    trees.push_back(std::next(cell_trees_.end(), -1));
  }
  return {cells, trees};
}

void EllersGenerator::MergeCellsInRow(Layout* const layout,
                                      Row& row,
                                      bool randomly) {
  auto& [cells, trees] = row;
  for (uint16_t i = 0; i != cells.size() - 1; i++) {
    auto &first_tree = trees.at(i), second_tree = trees.at(i + 1);
    // Decide randomly to join adjacent cells if they aren't already part of
    // the same tree
    if (first_tree == second_tree)
      continue;
    if (randomly && !ShouldJoin(JoinType::HORIZONTAL))
      continue;

    // Merge second tree into the first
    first_tree->insert(second_tree->begin(), second_tree->end());
    // Replace all references to merged tree
    std::replace(trees.begin(), trees.end(), second_tree, first_tree);

    // Remove the wall between those two cells
    auto &first_cell = cells.at(i), &second_cell = cells.at(i + 1);
    layout->Unblock(Edge::FromTwoCells(first_cell, second_cell));
  }
}

}  // namespace maze
