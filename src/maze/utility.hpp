#ifndef MAZE_UTILITY_HPP_
#define MAZE_UTILITY_HPP_

#include <stdint.h>
#include <deque>
#include <functional>
#include <optional>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace maze {

namespace {}  // namespace

constexpr uint16_t kHalfStep = 1;
constexpr uint16_t kStep = 2;
constexpr uint16_t kFirstCellIndex = 1;

enum class Direction {
  UP,
  RIGHT,
  DOWN,
  LEFT,
};

template <typename T>
struct Pair {
  T row, col;
  bool operator<(const Pair& other) const {
    return std::tie(row, col) < std::tie(other.row, other.col);
  }
  bool operator==(const Pair& other) const {
    return std::tie(row, col) == std::tie(other.row, other.col);
  }
};

using Move = Pair<int16_t>;
using Position = Pair<uint16_t>;
using Cell = Pair<uint16_t>;

struct Edge {
  Cell from;
  Direction direction;
  std::optional<Cell> To(const uint16_t& step = kStep) const;
};

using CellTree = std::unordered_set<Cell>;
using Path = std::vector<Cell>;

struct Size {
  const uint16_t rows, cols;
  bool operator==(const Size& other) const;
  bool operator<(const Size& other) const;
};

using CellSize = Size;
using LayoutSize = Size;

using MoveValidityCheck = std::function<bool(const Direction& direction)>;

std::deque<Direction> GetMoveDirections();

std::deque<Direction> GetValidMoveDirections(
    MoveValidityCheck validity_check = nullptr
);

std::deque<Direction> GetRandomizedMoveDirections(
    MoveValidityCheck validity_check = nullptr
);

std::optional<Direction> GetRandomMoveDirection(
    MoveValidityCheck validity_check = nullptr
);

Direction GetAsDirection(const Move& move);

}  // namespace maze

template <>
struct std::hash<maze::Position> {
  std::size_t operator()(maze::Position const& position) const noexcept {
    auto [y, x] = position;
    return (y << 8) ^ x;
  }
};

#endif  // MAZE_UTILITY_HPP_