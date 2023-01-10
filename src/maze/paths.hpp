#ifndef MAZE_PATHS_HPP_
#define MAZE_PATHS_HPP_

#include <utility>

#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace maze {

enum class PathType {
  FIRST,
  BOTTOM_TO_TOP = FIRST,
  BOTTOM_LEFT_TO_TOP_RIGHT,
  LEFT_TO_RIGHT,
  TOP_LEFT_TO_BOTTOM_RIGHT,
  TOP_TO_BOTTOM,
  LAST = TOP_TO_BOTTOM,
};

std::pair<Cell, Cell> GetStartAndGoal(const Layout* const layout,
                                      const PathType& path_type);

}  // namespace maze

#endif  // MAZE_PATHS_HPP_
