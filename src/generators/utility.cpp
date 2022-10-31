#include "utility.hpp"

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

}  // namespace maze
