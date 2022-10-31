#include "solver.hpp"

#include <cassert>

#include "layout.hpp"
#include "utility.hpp"

namespace maze {

Solver::~Solver() = default;

std::optional<Path>
Solver::Solve(const Layout* const layout, const PathType path_type) {
  switch (path_type) {
    case PathType::BOTTOM_TO_TOP: {
      return Solve(
          layout, {layout->bottom_row(), layout->middle_col()},
          {kFirstTileIndex, layout->middle_col()}
      );
      break;
    }
    case PathType::BOTTOM_LEFT_TO_TOP_RIGHT: {
      return Solve(
          layout, {layout->bottom_row(), kFirstTileIndex},
          {kFirstTileIndex, layout->rightmost_col()}
      );
      break;
    }
    case PathType::LEFT_TO_RIGHT: {
      return Solve(
          layout, {layout->middle_row(), kFirstTileIndex},
          {layout->middle_row(), layout->rightmost_col()}
      );
      break;
    }
    case PathType::TOP_LEFT_TO_BOTTOM_RIGHT: {
      return Solve(
          layout, {kFirstTileIndex, kFirstTileIndex},
          {layout->bottom_row(), layout->rightmost_col()}
      );
      break;
    }
    case PathType::TOP_TO_BOTTOM: {
      return Solve(
          layout, {kFirstTileIndex, layout->middle_col()},
          {layout->bottom_row(), layout->middle_col()}
      );
      break;
    }
    default: {
      assert(0 && "Invalid PathType value passed to Solver.");
      return std::nullopt;
    }
  }
}

void Solver::SetParameters(
    const Layout* const layout,
    const Position& start,
    const Position& goal
) {
  layout_ = layout;
  start_ = start;
  goal_ = goal;
}

}  // namespace maze
