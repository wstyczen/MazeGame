#ifndef MAZE_UNVISITED_HPP_
#define MAZE_UNVISITED_HPP_

#include <unordered_set>

#include "utility.hpp"

namespace maze {

class Unvisited {
 protected:
  Unvisited();
  virtual ~Unvisited();
  Position PickRandomUnvisited(bool erase = true);
  void
  InitializeUnvisited(const uint16_t& layout_rows, const uint16_t& layout_cols);
  std::unordered_set<Position> unvisited_;
};

}  // namespace maze

#endif  // MAZE_UNVISITED_HPP_
