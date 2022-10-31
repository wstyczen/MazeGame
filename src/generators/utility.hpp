#ifndef MAZE_UTILITY_HPP_
#define MAZE_UTILITY_HPP_

#include <stdint.h>
#include <optional>
#include <tuple>
#include <vector>

namespace maze {

constexpr uint16_t kHalfStep = 1;
constexpr uint16_t kStep = 2;
constexpr uint16_t kFirstTileIndex = 1;

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

}  // namespace maze

#endif  // MAZE_UTILITY_HPP_
