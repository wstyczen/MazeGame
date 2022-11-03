#ifndef MAZE_GENERATOR_HPP_
#define MAZE_GENERATOR_HPP_

#include <memory>

#include "utility.hpp"

namespace maze {

class Layout;

class Generator {
 public:
  virtual ~Generator(){};
  virtual std::unique_ptr<Layout> Get(const CellSize& cell_size) = 0;
};

}  // namespace maze

#endif  // MAZE_GENERATOR_HPP_
