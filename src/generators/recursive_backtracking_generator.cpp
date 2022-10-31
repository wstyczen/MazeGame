#include "recursive_backtracking_generator.hpp"

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <memory>
#include <set>

#include "layout.hpp"
#include "utility.hpp"

namespace maze {

using Directions = std::deque<Direction>;

namespace {

Directions GetRandomizedDirections() {
  static const Directions directions = {
      Direction::UP,
      Direction::RIGHT,
      Direction::DOWN,
      Direction::LEFT,
  };
  Directions random_directions = directions;
  std::random_shuffle(random_directions.begin(), random_directions.end());
  return random_directions;
}

Position PickRandom(std::set<Position>& positions) {
  auto iter = positions.begin();
  std::advance(iter, std::rand() % positions.size());

  const Position picked = *iter;
  positions.erase(iter);

  return picked;
}

}  // namespace

RecursiveBacktrackingGenerator::RecursiveBacktrackingGenerator() = default;
RecursiveBacktrackingGenerator::~RecursiveBacktrackingGenerator() = default;

std::unique_ptr<Layout> RecursiveBacktrackingGenerator::Get(
    const uint16_t& cells_vertical,
    const uint16_t& cells_horizontal
) {
  auto maze_layout = std::make_unique<Layout>(cells_vertical, cells_horizontal);
  InitializeCells(maze_layout->rows(), maze_layout->cols());

  Move(maze_layout.get(), PickRandom(unvisited_cells_));

  return std::move(maze_layout);
}

void RecursiveBacktrackingGenerator::Move(
    Layout* const layout,
    const Position& starting_position
) {
  Directions randomized_directions = GetRandomizedDirections();
  while (!randomized_directions.empty()) {
    const Edge edge = Edge(starting_position, randomized_directions.front());
    const Position destination = *edge.To();
    if (unvisited_cells_.contains(destination) &&
        layout->IsWithin(destination)) {
      unvisited_cells_.erase(destination);
      layout->Unblock(edge);
      Move(layout, *edge.To());
    }
    randomized_directions.pop_front();
  }
}

void RecursiveBacktrackingGenerator::InitializeCells(
    const uint16_t& layout_rows,
    const uint16_t& layout_cols
) {
  unvisited_cells_.clear();
  for (size_t i = kFirstCellIndex; i < layout_rows; i += kStep)
    for (size_t j = kFirstCellIndex; j < layout_cols; j += kStep)
      unvisited_cells_.emplace(i, j);
}

}  // namespace maze
