#ifndef MAZE_WILSONS_HPP_
#define MAZE_WILSONS_HPP_

#include "maze/generators/generator.hpp"
#include "maze/unvisited.hpp"

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

#endif  // MAZE_WILSONS_HPP_
