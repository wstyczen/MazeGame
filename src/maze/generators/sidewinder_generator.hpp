#ifndef MAZE_SIDEWINDER_GENERATOR_HPP_
#define MAZE_SIDEWINDER_GENERATOR_HPP_

#include "maze/generators/generator.hpp"

namespace maze {

class SidewinderGenerator : public Generator {
 public:
  ~SidewinderGenerator();

  std::unique_ptr<Layout> Get(const CellSize& cell_size) final;

 private:
  SidewinderGenerator();

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_SIDEWINDER_GENERATOR_HPP_
