#ifndef MAZE_UTILITY_HPP_
#define MAZE_UTILITY_HPP_

#include <stdint.h>
#include <optional>
#include <tuple>

#include <boost/json.hpp>

enum class Direction {
  NORTH,
  EAST,
  SOUTH,
  WEST,
};

struct Position {
  uint16_t y, x;
  bool operator<(const Position& other) const {
    if (y < other.y)
      return true;
    else if (y > other.y)
      return false;
    return x < other.x;
  }
  bool operator==(const Position& other) const {
    return std::tie(x, y) == std::tie(other.x, other.y);
  }
};

struct Edge {
  Position from_;
  Direction direction_;
  std::optional<Position> To() const {
    switch (direction_) {
      case Direction::NORTH:
        return Position(from_.y - 1, from_.x);
      case Direction::EAST:
        return Position(from_.y, from_.x + 1);
      case Direction::SOUTH:
        return Position(from_.y + 1, from_.x);
      case Direction::WEST:
        return Position(from_.y, from_.x - 1);
      default:
        return std::nullopt;
    }
  }
};

#endif  // MAZE_UTILITY_HPP_
