#include "utility.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace maze {

bool Position::operator<(const Position& other) const {
  if (y < other.y)
    return true;
  else if (y > other.y)
    return false;
  return x < other.x;
}

bool Position::operator==(const Position& other) const {
  return std::tie(x, y) == std::tie(other.x, other.y);
}

std::optional<Position> Edge::To(const uint16_t& step) const {
  switch (direction) {
    case Direction::UP:
      return Position(from.y - step, from.x);
    case Direction::RIGHT:
      return Position(from.y, from.x + step);
    case Direction::DOWN:
      return Position(from.y + step, from.x);
    case Direction::LEFT:
      return Position(from.y, from.x - step);
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

Direction GetAsDirection(const int16_t& dy, const int16_t& dx) {
  assert((abs(dy) == kStep || abs(dx) == kStep) && "A move is a single step.");
  if (dy > 0)
    return Direction::DOWN;
  if (dy < 0)
    return Direction::UP;
  if (dx > 0)
    return Direction::RIGHT;
  return Direction::LEFT;
}

}  // namespace maze
