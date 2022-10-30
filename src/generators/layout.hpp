#ifndef MAZE_LAYOUT_HPP_
#define MAZE_LAYOUT_HPP_

#include <stdint.h>
#include <vector>

#include "utility.hpp"

namespace maze {

class Layout {
 public:
  Layout(const uint16_t& N, const uint16_t& M);

  void Unblock(const Edge& edge);
  void Show() const;

  constexpr static char kBlocked = 'B';
  constexpr static char kUnblocked = 'U';
  constexpr static char kEmpty = 'E';

 private:
  std::vector<std::vector<char>> layout_;
};

}  // namespace maze

#endif  // MAZE_LAYOUT_HPP_
