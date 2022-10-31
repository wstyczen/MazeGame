#include "kruskals_generator.hpp"

#include "boost/graph/adjacency_list.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace maze {

KruskalsGenerator::KruskalsGenerator() = default;

KruskalsGenerator::~KruskalsGenerator() = default;

std::unique_ptr<Layout> KruskalsGenerator::Get(
    const uint16_t& tiles_vertical,
    const uint16_t& tiles_horizontal
) {
  auto maze_layout = std::make_unique<Layout>(tiles_vertical, tiles_horizontal);

  InitializeEdges(maze_layout->rows(), maze_layout->cols());
  InitializeCellTrees(maze_layout->rows(), maze_layout->cols());

  while (!edges_.empty()) {
    const Edge& edge = edges_.front();
    auto tree_containing_edge_start = std::find_if(
        tile_trees_.begin(), tile_trees_.end(),
        [this, &edge](const std::set<Position>& tree) {
          return tree.contains(edge.from);
        }
    );
    assert(tree_containing_edge_start != tile_trees_.end());
    const std::optional<Position> edge_end = edge.To();
    assert(edge_end && "Invalid Direction enum passed to Edge instance.");

    if (!tree_containing_edge_start->contains(*edge_end)) {
      auto tree_containg_edge_end = std::find_if(
          tile_trees_.begin(), tile_trees_.end(),
          [this, &edge_end](const std::set<Position>& tree) {
            return tree.contains(*edge_end);
          }
      );
      tree_containing_edge_start->insert(
          tree_containg_edge_end->begin(), tree_containg_edge_end->end()
      );
      tile_trees_.erase(tree_containg_edge_end);
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
  tile_trees_.clear();
  tile_trees_.reserve(layout_rows * layout_cols);
  for (size_t i = kFirstTileIndex; i < layout_rows; i += kStep)
    for (size_t j = kFirstTileIndex; j < layout_cols; j += kStep)
      tile_trees_.push_back({Position(i, j)});
}

void KruskalsGenerator::InitializeEdges(
    const uint16_t& layout_rows,
    const uint16_t& layout_cols
) {
  edges_.clear();
  for (size_t i = kFirstTileIndex; i < layout_rows; i += kStep)
    for (size_t j = kFirstTileIndex; j < layout_cols; j += kStep) {
      if (i > kFirstTileIndex)
        edges_.emplace_back(Position(i, j), Direction::UP);
      if (j > kFirstTileIndex)
        edges_.emplace_back(Position(i, j), Direction::LEFT);
    }
  std::random_shuffle(edges_.begin(), edges_.end());
}

}  // namespace maze
