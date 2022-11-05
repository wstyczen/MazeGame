#include "kruskals_generator.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "layout.hpp"
#include "utility.hpp"

namespace maze {

KruskalsGenerator::KruskalsGenerator() = default;

KruskalsGenerator::~KruskalsGenerator() = default;

std::unique_ptr<Layout> KruskalsGenerator::Get(const CellSize& cell_size) {
  auto layout = std::make_unique<Layout>(cell_size);

  InitializeEdges(layout->size());
  InitializeCellTrees(layout->size());

  while (!edges_.empty()) {
    const Edge& edge = edges_.front();
    auto tree_containing_edge_start = std::find_if(
        cell_trees_.begin(), cell_trees_.end(),
        [this, &edge](const CellTree& tree) { return tree.contains(edge.from); }
    );
    assert(tree_containing_edge_start != cell_trees_.end());
    const std::optional<Position> edge_end = edge.To();
    assert(edge_end && "Invalid direction selected");

    if (!tree_containing_edge_start->contains(*edge_end)) {
      auto tree_containing_edge_end = std::find_if(
          cell_trees_.begin(), cell_trees_.end(),
          [this, &edge_end](const CellTree& tree) {
            return tree.contains(*edge_end);
          }
      );
      tree_containing_edge_start->insert(
          tree_containing_edge_end->begin(), tree_containing_edge_end->end()
      );
      cell_trees_.erase(tree_containing_edge_end);
      layout->Unblock(edge);
    }

    edges_.pop_front();
  }
  return std::move(layout);
}

void KruskalsGenerator::InitializeCellTrees(const LayoutSize& layout_size) {
  const auto& [layout_rows, layout_cols] = layout_size;
  cell_trees_.clear();
  cell_trees_.reserve(layout_rows * layout_cols);
  for (size_t i = kLayoutFirstCellIndex; i < layout_rows; i += kStep)
    for (size_t j = kLayoutFirstCellIndex; j < layout_cols; j += kStep)
      cell_trees_.push_back({Cell(i, j)});
}

void KruskalsGenerator::InitializeEdges(const LayoutSize& layout_size) {
  edges_.clear();
  const auto& [layout_rows, layout_cols] = layout_size;
  for (size_t i = kLayoutFirstCellIndex; i < layout_rows; i += kStep)
    for (size_t j = kLayoutFirstCellIndex; j < layout_cols; j += kStep) {
      if (i > kLayoutFirstCellIndex)
        edges_.emplace_back(Cell(i, j), Direction::UP);
      if (j > kLayoutFirstCellIndex)
        edges_.emplace_back(Cell(i, j), Direction::LEFT);
    }
  std::random_shuffle(edges_.begin(), edges_.end());
}

}  // namespace maze
