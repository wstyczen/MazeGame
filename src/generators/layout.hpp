#ifndef MAZE_LAYOUT_HPP_
#define MAZE_LAYOUT_HPP_

#include <stdint.h>
#include <vector>

#include "utility.hpp"

namespace maze {

class Layout {
 public:
  Layout(const uint16_t& N, const uint16_t& M);

  uint16_t rows() const;
  uint16_t cols() const;
  uint16_t middle_row() const;
  uint16_t bottom_row() const;
  uint16_t middle_col() const;
  uint16_t rightmost_col() const;

  bool IsWithin(const Position& position) const;
  bool IsBlocked(const Position& position) const;
  bool CanMove(const Edge& edge) const;

  void Unblock(const Edge& edge);
  void AddPath(const Path& path);
  void Show() const;

  constexpr static char kBlocked = 'B';
  constexpr static char kUnblocked = 'U';
  constexpr static char kEmpty = 'E';
  constexpr static char kPath = 'P';

 private:
  const uint16_t rows_, cols_;
  std::vector<std::vector<char>> layout_;
};

}  // namespace maze

#endif  // MAZE_LAYOUT_HPP_
