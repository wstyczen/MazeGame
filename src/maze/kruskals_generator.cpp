#include "kruskals_generator.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace maze {

KruskalsGenerator::KruskalsGenerator() = default;

KruskalsGenerator::~KruskalsGenerator() = default;

std::unique_ptr<Layout> KruskalsGenerator::Get(
    const uint16_t& cells_vertical,
    const uint16_t& cells_horizontal
) {
  auto maze_layout = std::make_unique<Layout>(cells_vertical, cells_horizontal);

  InitializeEdges(maze_layout->rows(), maze_layout->cols());
  InitializeCellTrees(maze_layout->rows(), maze_layout->cols());

  while (!edges_.empty()) {
    const Edge& edge = edges_.front();
    auto tree_containing_edge_start = std::find_if(
        cell_trees_.begin(), cell_trees_.end(),
        [this, &edge](const std::unordered_set<Position>& tree) {
          return tree.contains(edge.from);
        }
    );
    assert(tree_containing_edge_start != cell_trees_.end());
    const std::optional<Position> edge_end = edge.To();
    assert(edge_end && "Invalid Direction enum passed to Edge instance.");

    if (!tree_containing_edge_start->contains(*edge_end)) {
      auto tree_containg_edge_end = std::find_if(
          cell_trees_.begin(), cell_trees_.end(),
          [this, &edge_end](const std::unordered_set<Position>& tree) {
            return tree.contains(*edge_end);
          }
      );
      tree_containing_edge_start->insert(
          tree_containg_edge_end->begin(), tree_containg_edge_end->end()
      );
      cell_trees_.erase(tree_containg_edge_end);
      maze_layout->Unblock(edge);
    }

    edges_.pop_front();
  }
  return std::move(maze_layout);
}

void KruskalsGenerator::InitializeCellTrees(
    const uint16_t& layout_rows,
    const uint16_t& layout_cols
) {
  cell_trees_.clear();
  cell_trees_.reserve(layout_rows * layout_cols);
  for (size_t i = kFirstCellIndex; i < layout_rows; i += kStep)
    for (size_t j = kFirstCellIndex; j < layout_cols; j += kStep)
      cell_trees_.push_back({Position(i, j)});
}

void KruskalsGenerator::InitializeEdges(
    const uint16_t& layout_rows,
    const uint16_t& layout_cols
) {
  edges_.clear();
  for (size_t i = kFirstCellIndex; i < layout_rows; i += kStep)
    for (size_t j = kFirstCellIndex; j < layout_cols; j += kStep) {
      if (i > kFirstCellIndex)
        edges_.emplace_back(Position(i, j), Direction::UP);
      if (j > kFirstCellIndex)
        edges_.emplace_back(Position(i, j), Direction::LEFT);
    }
  std::random_shuffle(edges_.begin(), edges_.end());
}

}  // namespace maze
