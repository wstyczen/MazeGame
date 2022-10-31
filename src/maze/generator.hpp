#ifndef MAZE_GENERATOR_HPP_
#define MAZE_GENERATOR_HPP_

#include "layout.hpp"

#include <memory>

namespace maze {

class Generator {
 public:
  virtual ~Generator(){};
  virtual std::unique_ptr<Layout>
  Get(const uint16_t& cells_vertical, const uint16_t& cells_horizontal) = 0;
};

}  // namespace maze

#endif  // MAZE_GENERATOR_HPP_
