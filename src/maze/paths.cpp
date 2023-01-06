#include "maze/paths.hpp"

#include <stdexcept>

namespace maze {

std::pair<Cell, Cell> GetStartAndGoal(const Layout* const layout,
                                      const PathType& path_type) {
  switch (path_type) {
    case PathType::BOTTOM_TO_TOP: {
      return {{layout->bottom_row(), layout->middle_col()},
              {kLayoutFirstCellIndex, layout->middle_col()}};
      break;
    }
    case PathType::BOTTOM_LEFT_TO_TOP_RIGHT: {
      return {{layout->bottom_row(), kLayoutFirstCellIndex},
              {kLayoutFirstCellIndex, layout->rightmost_col()}};
      break;
    }
    case PathType::LEFT_TO_RIGHT: {
      return {{layout->middle_row(), kLayoutFirstCellIndex},
              {layout->middle_row(), layout->rightmost_col()}};
      break;
    }
    case PathType::TOP_LEFT_TO_BOTTOM_RIGHT: {
      return {{kLayoutFirstCellIndex, kLayoutFirstCellIndex},
              {layout->bottom_row(), layout->rightmost_col()}};
      break;
    }
    case PathType::TOP_TO_BOTTOM: {
      return {{kLayoutFirstCellIndex, layout->middle_col()},
              {layout->bottom_row(), layout->middle_col()}};
      break;
    }
    default: {
      throw std::invalid_argument("Invalid value of 'PathType'.");
    }
  }
}

}  // namespace maze
