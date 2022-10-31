#ifndef MAZE_PRIMS_GENERATOR_HPP_
#define MAZE_PRIMS_GENERATOR_HPP_

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "generator.hpp"
#include "unvisited.hpp"
#include "utility.hpp"

namespace maze {

using Frontier = std::map<Position, std::vector<Position>>;

class PrimsGenerator : public Generator, public Unvisited {
 public:
  ~PrimsGenerator();
  std::unique_ptr<Layout>
  Get(const uint16_t& cells_vertical, const uint16_t& cells_horizontal) final;

 private:
  PrimsGenerator();

  Frontier frontier_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_PRIMS_GENERATOR_HPP_
