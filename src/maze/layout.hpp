#ifndef MAZE_LAYOUT_HPP_
#define MAZE_LAYOUT_HPP_

#include <stdint.h>
#include <vector>

#include "maze/utility.hpp"

namespace maze {

class Layout {
 public:
  enum class Base {
    GRID,
    EMPTY,
  };

  Layout(const CellSize& cell_size, const Base& layout_base = Base::GRID);

  LayoutSize size() const;
  uint16_t middle_row() const;
  uint16_t bottom_row() const;
  uint16_t middle_col() const;
  uint16_t rightmost_col() const;

  bool IsWithin(const Position& position) const;
  bool IsBlocked(const Position& position) const;
  bool IsACell(const Position& position) const;
  bool CanMove(const Edge& edge) const;

  void Unblock(const Edge& edge);
  void Unblock(const Position& position);
  void Block(const Position& position);

  void AddPath(const Path& path);

  void Show() const;

  constexpr static char kCell = 'C';
  constexpr static char kWall = 'W';
  constexpr static char kDoor = 'D';
  constexpr static char kPath = 'P';
  constexpr static char kLocation = 'X';

 private:
  const LayoutSize size_;
  std::vector<std::vector<char>> layout_;
};

}  // namespace maze

#endif  // MAZE_LAYOUT_HPP_
