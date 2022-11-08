#ifndef MAZE_PREDECESSORS_HPP_
#define MAZE_PREDECESSORS_HPP_

#include <unordered_map>

#include "maze/utility.hpp"

namespace maze {

class Predecessors {
 protected:
  std::optional<Path> RecreatePath(const Cell& start, const Cell& goal);
  std::unordered_map<Cell, Cell> predecessors_;
};

}  // namespace maze

#endif  // MAZE_PREDECESSORS_HPP_
