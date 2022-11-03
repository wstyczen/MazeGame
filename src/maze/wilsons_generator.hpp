#ifndef MAZE_WILSONS_GENERATOR_HPP_
#define MAZE_WILSONS_GENERATOR_HPP_

#include "generator.hpp"
#include "unvisited.hpp"

#include <map>
#include <memory>

namespace maze {

class WilsonsGenerator : public Generator, public Unvisited {
 public:
  ~WilsonsGenerator();
  std::unique_ptr<Layout> Get(const CellSize& cell_size);

 private:
  WilsonsGenerator();

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_WILSONS_GENERATOR_HPP_
