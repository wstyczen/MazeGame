#include "utility.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <tuple>

namespace maze {

namespace {

Direction GetAsDirection(const Move& move) {
  assert(
      (abs(move.row) == kStep || abs(move.col) == kStep) &&
      "A move is a single step."
  );
  if (move.row > 0)
    return Direction::DOWN;
  if (move.row < 0)
    return Direction::UP;
  if (move.col > 0)
    return Direction::RIGHT;
  return Direction::LEFT;
}

}  // namespace

bool Size::operator==(const Size& other) const {
  return std::tie(rows, cols) == std::tie(other.rows, other.cols);
}
bool Size::operator<(const Size& other) const {
  return std::tie(rows, cols) < std::tie(other.rows, other.cols);
}

std::optional<Position> Edge::To(const uint16_t& step) const {
  switch (direction) {
    case Direction::UP:
      return Position(from.row - step, from.col);
    case Direction::RIGHT:
      return Position(from.row, from.col + step);
    case Direction::DOWN:
      return Position(from.row + step, from.col);
    case Direction::LEFT:
      return Position(from.row, from.col - step);
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
  std::copy_if(
      directions.begin(), directions.end(),
      std::back_inserter(valid_directions), validity_check
  );
  return valid_directions;
}

std::deque<Direction> GetRandomizedMoveDirections(
    MoveValidityCheck validity_check
) {
  std::deque<Direction> randomized_directions =
      GetValidMoveDirections(validity_check);
  std::random_shuffle(
      randomized_directions.begin(), randomized_directions.end()
  );
  return randomized_directions;
}

std::optional<Direction> GetRandomMoveDirection(MoveValidityCheck validity_check
) {
  auto valid_move_directions = GetValidMoveDirections(validity_check);

  if (valid_move_directions.empty())
    return std::nullopt;

  auto direction_iter = valid_move_directions.begin();
  std::advance(direction_iter, std::rand() % valid_move_directions.size());
  return *direction_iter;
}

Edge Edge::FromTwoCells(const Cell& origin, const Cell& destination) {
  const Move move(destination.row - origin.row, destination.col - origin.col);
  return {origin, GetAsDirection(move)};
}

}  // namespace maze
