#ifndef GAME_MAZE_STATE_HPP_
#define GAME_MAZE_STATE_HPP_

#include <chrono>
#include <memory>

#include "maze/layout.hpp"
#include "maze/paths.hpp"
#include "maze/utility.hpp"

namespace game {

class Maze {
 public:
  Maze(std::unique_ptr<maze::Layout> layout, const maze::PathType& path_type);
  Maze(Maze&& maze) noexcept;
  Maze& operator=(Maze&& other);
  ~Maze();

  const maze::Layout* layout() const;
  const maze::Path* path() const;
  maze::Cell position() const;
  maze::Cell goal() const;

  uint16_t GetMovesMade() const;
  maze::CellSize GetNextCellSize(const uint16_t& increment) const;

  bool Move(const maze::Direction& direction);
  bool GoalReached() const;

 private:
  std::unique_ptr<maze::Layout> layout_;
  maze::Path path_taken_;

  maze::Cell position_;
  maze::Cell goal_;
};

}  // namespace game

#endif  // GAME_MAZE_STATE_HPP_
