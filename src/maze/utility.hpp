#ifndef MAZE_UTILITY_HPP_
#define MAZE_UTILITY_HPP_

#include <stdint.h>
#include <deque>
#include <functional>
#include <optional>
#include <random>
#include <tuple>
#include <unordered_set>
#include <vector>

namespace maze {

namespace {}  // namespace

constexpr uint16_t kHalfStep = 1;
constexpr uint16_t kStep = 2;
constexpr uint16_t kLayoutFirstCellIndex = 1;

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
  static Edge FromTwoCells(const Cell& origin, const Cell& destination);
};

using CellTree = std::unordered_set<Cell>;
using Path = std::vector<Cell>;

struct Size {
  const uint16_t rows, cols;
  bool operator==(const Size& other) const;
  bool operator<(const Size& other) const;
  Size& operator=(const Size& other);
};

using CellSize = Size;
using LayoutSize = Size;

using MoveGeneralValidityCheck =
    std::function<bool(const Cell&, const Direction&)>;
using MoveValidityCheck = std::function<bool(const Direction& direction)>;

std::deque<Direction> GetValidMoveDirections(
    MoveValidityCheck validity_check = nullptr);

std::deque<Direction> GetRandomizedMoveDirections(
    MoveValidityCheck validity_check = nullptr);

std::optional<Direction> GetRandomMoveDirection(
    MoveValidityCheck validity_check = nullptr);

std::mt19937 GetRNG();

uint16_t GetRandomNumber(const uint16_t& upper_limit);

bool RollAPercentChance(const uint16_t& percent_success_chance);

}  // namespace maze

template <>
struct std::hash<maze::Position> {
  std::size_t operator()(maze::Position const& position) const noexcept {
    const auto& [y, x] = position;
    return (y << 8) ^ x;
  }
};

#endif  // MAZE_UTILITY_HPP_
