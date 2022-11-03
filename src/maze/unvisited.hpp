#ifndef MAZE_UNVISITED_HPP_
#define MAZE_UNVISITED_HPP_

#include <unordered_set>

#include "utility.hpp"

namespace maze {

class Unvisited {
 protected:
  Unvisited();
  virtual ~Unvisited();
  Cell PickRandomUnvisited(bool erase = true);
  void InitializeUnvisited(const LayoutSize& layout_size);
  std::unordered_set<Cell> unvisited_;
};

}  // namespace maze

#endif  // MAZE_UNVISITED_HPP_
