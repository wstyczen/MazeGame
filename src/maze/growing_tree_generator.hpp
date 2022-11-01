#ifndef MAZE_GROWING_TREE_GENERATOR_HPP_
#define MAZE_GROWING_TREE_GENERATOR_HPP_

#include <memory>
#include <vector>

#include "generator.hpp"
#include "layout.hpp"
#include "unvisited.hpp"

namespace maze {

class GeneratorFactory;

class GrowingTreeGenerator : public Generator, public Unvisited {
 public:
  ~GrowingTreeGenerator();
  std::unique_ptr<Layout>
  Get(const uint16_t& vertical_cells, const uint16_t& horizontal_cells) final;

 private:
  GrowingTreeGenerator();

  std::vector<Position> path_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_GROWING_TREE_GENERATOR_HPP_
