#include "kruskals_generator.hpp"

#include "boost/graph/adjacency_list.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace maze {

KruskalsGenerator::KruskalsGenerator() = default;

KruskalsGenerator::~KruskalsGenerator() = default;

std::unique_ptr<Layout>
KruskalsGenerator::Get(const uint16_t& N, const uint16_t& M) {
  auto maze_layout = std::make_unique<Layout>(N, M);

  InitializeEdges(N, M);
  InitializeCellTrees(N, M);

  while (!edges_.empty()) {
    const Edge& edge = edges_.front();
    auto tree_containing_edge_start = std::find_if(
        cell_trees_.begin(), cell_trees_.end(),
        [this, &edge](const std::set<Position>& tree) {
          return tree.contains(edge.from_);
        }
    );
    // if (tree_containing_edge_start == cell_trees_.end())
    //   std::cout << "found";
    assert(tree_containing_edge_start != cell_trees_.end());
    const std::optional<Position> edge_end = edge.To();
    assert(edge_end && "Invalid value passed as direction enum.");

    if (!tree_containing_edge_start->contains(*edge_end)) {
      auto tree_containg_edge_end = std::find_if(
          cell_trees_.begin(), cell_trees_.end(),
          [this, &edge_end](const std::set<Position>& tree) {
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
    const uint16_t& N,
    const uint16_t& M
) {
  cell_trees_.clear();
  cell_trees_.reserve(N * M);
  for (size_t i = 0; i != N; i++)
    for (size_t j = 0; j != M; j++)
      cell_trees_.push_back({Position(i, j)});
}

void KruskalsGenerator::InitializeEdges(const uint16_t& N, const uint16_t& M) {
  edges_.clear();
  for (size_t i = 0; i != N; i++)
    for (size_t j = 0; j != M; j++) {
      if (i > 0)
        edges_.emplace_back(Position(i, j), Direction::NORTH);
      if (j > 0)
        edges_.emplace_back(Position(i, j), Direction::WEST);
    }
  std::random_shuffle(edges_.begin(), edges_.end());
}

}  // namespace maze
