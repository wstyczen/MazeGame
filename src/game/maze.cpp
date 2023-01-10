#include "game/maze.hpp"

#include <tuple>

#include "maze/paths.hpp"

namespace game {
using namespace std::chrono;

Maze::Maze(std::unique_ptr<maze::Layout> layout,
           const maze::PathType& path_type)
    : layout_{std::move(layout)} {
  std::tie(position_, goal_) = GetStartAndGoal(layout_.get(), path_type);
  path_taken_.push_back(position_);
}

Maze::Maze(Maze&& other) noexcept
    : layout_{std::move(other.layout_)},
      path_taken_{std::move(other.path_taken_)},
      position_{std::move(other.position_)},
      goal_{std::move(other.goal_)} {}

Maze& Maze::operator=(Maze&& other) {
  layout_ = std::move(other.layout_);
  path_taken_ = std::move(other.path_taken_);
  position_ = std::move(other.position_);
  goal_ = std::move(other.goal_);
  return *this;
}

Maze::~Maze() = default;

const maze::Layout* Maze::layout() const {
  return layout_.get();
}

const maze::Path* Maze::path() const {
  return &path_taken_;
}

maze::Cell Maze::position() const {
  return position_;
}

uint16_t Maze::GetMovesMade() const {
  return path_taken_.size() - 1;
}

maze::CellSize Maze::GetNextCellSize(const uint16_t& increment) const {
  const auto& [rows, cols] = layout_->size();
  return {static_cast<uint16_t>(rows + increment),
          static_cast<uint16_t>(cols + increment)};
}

bool Maze::Move(const maze::Direction& direction) {
  maze::Edge move(position_, direction);
  if (!layout_->CanMove(move))
    return false;
  position_ = *move.To();
  path_taken_.push_back(position_);
  return true;
}

bool Maze::GoalReached() const {
  return position_ == goal_;
}

}  // namespace game
