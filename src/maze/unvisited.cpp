#include "unvisited.hpp"

#include <cstdlib>

namespace maze {

Unvisited::Unvisited() = default;
Unvisited::~Unvisited() = default;

void Unvisited::InitializeUnvisited(
    const uint16_t& layout_rows,
    const uint16_t& layout_cols
) {
  unvisited_.clear();
  for (size_t i = kFirstCellIndex; i < layout_rows; i += kStep)
    for (size_t j = kFirstCellIndex; j < layout_cols; j += kStep)
      unvisited_.emplace(i, j);
}

Position Unvisited::PickRandomUnvisited(bool erase) {
  auto iter = unvisited_.begin();
  std::advance(iter, std::rand() % unvisited_.size());

  const Position picked = *iter;
  if (erase)
    unvisited_.erase(iter);

  return picked;
}

}  // namespace maze
