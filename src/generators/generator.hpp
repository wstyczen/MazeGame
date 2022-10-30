#ifndef MAZE_GENERATOR_HPP_
#define MAZE_GENERATOR_HPP_

#include "layout.hpp"

#include <memory>

namespace maze {

enum class GeneratorType {
  KRUSKALS,
  PRIMS,
  GROWING_TREE,
  RECURSIVE_BACKGTRACKING,
};

class Generator {
 public:
  // virtual ~Generator();
  virtual std::unique_ptr<Layout> Get(const uint16_t& N, const uint16_t& M) = 0;
};

}  // namespace maze

#endif  // MAZE_GENERATOR_HPP_
