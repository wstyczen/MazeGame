#include "unvisited.hpp"

#include <cstdlib>

namespace maze {

Unvisited::Unvisited() = default;
Unvisited::~Unvisited() = default;

void Unvisited::InitializeUnvisited(const LayoutSize& layout_size) {
  unvisited_.clear();
  for (size_t i = kFirstCellIndex; i < layout_size.rows; i += kStep)
    for (size_t j = kFirstCellIndex; j < layout_size.cols; j += kStep)
      unvisited_.emplace(i, j);
}

Cell Unvisited::PickRandomUnvisited(bool erase) {
  auto iter = unvisited_.begin();
  std::advance(iter, std::rand() % unvisited_.size());

  const Cell picked = *iter;
  if (erase)
    unvisited_.erase(iter);

  return picked;
}

}  // namespace maze
