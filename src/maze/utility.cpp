#include "maze/utility.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <random>
#include <tuple>

namespace maze {

namespace {

Direction GetAsDirection(const Move& move) {
  assert((abs(move.row) == kStep || abs(move.col) == kStep) &&
         "A move is a single step.");
  if (move.row > 0)
    return Direction::DOWN;
  if (move.row < 0)
    return Direction::UP;
  if (move.col > 0)
    return Direction::RIGHT;
  return Direction::LEFT;
}

inline std::mt19937 GetRNG() { return std::mt19937(std::random_device{}()); }
}  // namespace

bool Size::operator==(const Size& other) const {
  return std::tie(rows, cols) == std::tie(other.rows, other.cols);
}
bool Size::operator<(const Size& other) const {
  return std::tie(rows, cols) < std::tie(other.rows, other.cols);
}

std::optional<Cell> Edge::To(const uint16_t& step) const {
  switch (direction) {
    case Direction::UP:
      return Cell(from.row - step, from.col);
    case Direction::RIGHT:
      return Cell(from.row, from.col + step);
    case Direction::DOWN:
      return Cell(from.row + step, from.col);
    case Direction::LEFT:
      return Cell(from.row, from.col - step);
  }
  return std::nullopt;
}

std::deque<Direction> GetValidMoveDirections(MoveValidityCheck validity_check) {
  static const std::deque<Direction> directions = {
      Direction::UP,
      Direction::RIGHT,
      Direction::DOWN,
      Direction::LEFT,
  };
  if (!validity_check)
    return directions;
  std::deque<Direction> valid_directions;
  std::copy_if(directions.begin(), directions.end(),
               std::back_inserter(valid_directions), validity_check);
  return valid_directions;
}

std::deque<Direction> GetRandomizedMoveDirections(
    MoveValidityCheck validity_check) {
  std::deque<Direction> randomized_directions =
      GetValidMoveDirections(validity_check);
  std::shuffle(randomized_directions.begin(), randomized_directions.end(),
               GetRNG());
  return randomized_directions;
}

std::optional<Direction> GetRandomMoveDirection(
    MoveValidityCheck validity_check) {
  auto valid_move_directions = GetValidMoveDirections(validity_check);

  if (valid_move_directions.empty())
    return std::nullopt;

  auto direction_iter = valid_move_directions.begin();
  std::advance(direction_iter,
               GetRandomNumber(valid_move_directions.size() - 1));
  return *direction_iter;
}

Edge Edge::FromTwoCells(const Cell& origin, const Cell& destination) {
  const Move move(destination.row - origin.row, destination.col - origin.col);
  return {origin, GetAsDirection(move)};
}

uint16_t GetRandomNumber(const uint16_t &upper_limit) {
  std::uniform_int_distribution<> dist(0, upper_limit);
  std::mt19937 rng = GetRNG();
  return dist(rng);
}

}  // namespace maze
