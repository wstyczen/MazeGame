#ifndef MAZE_UTILITY_HPP_
#define MAZE_UTILITY_HPP_

#include <stdint.h>
#include <deque>
#include <functional>
#include <optional>
#include <set>
#include <tuple>
#include <vector>

namespace maze {

constexpr uint16_t kHalfStep = 1;
constexpr uint16_t kStep = 2;
constexpr uint16_t kFirstCellIndex = 1;

enum class Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

struct Position {
  uint16_t y, x;
  bool operator<(const Position& other) const;
  bool operator==(const Position& other) const;
};

struct Edge {
  Position from;
  Direction direction;
  std::optional<Position> To(const uint16_t& step = kStep) const;
};

using Path = std::vector<Position>;

using MoveValidityCheck = std::function<bool(const Direction& direction)>;

std::deque<Direction> GetValidMoveDirections(
    MoveValidityCheck validity_check = nullptr
);

std::deque<Direction> GetRandomizedMoveDirections(
    MoveValidityCheck validity_check = nullptr
);

std::optional<Direction> GetRandomMoveDirection(
    MoveValidityCheck validity_check = nullptr
);

Direction GetAsDirection(const int16_t& dy, const int16_t& dx);

}  // namespace maze

#endif  // MAZE_UTILITY_HPP_
