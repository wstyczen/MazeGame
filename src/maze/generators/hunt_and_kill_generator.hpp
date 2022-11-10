#ifndef MAZE_HUNT_AND_KILL_GENERATOR_HPP_
#define MAZE_HUNT_AND_KILL_GENERATOR_HPP_

#include "maze/generators/generator.hpp"
#include "maze/unvisited.hpp"

namespace maze {

class HuntAndKillGenerator : public Generator, public Unvisited {
 public:
  ~HuntAndKillGenerator();

  std::unique_ptr<Layout> Get(const CellSize& cell_size) final;

 private:
  HuntAndKillGenerator();

  std::optional<Cell> Hunt(Layout* const layout, const Cell& cell);

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_HUNT_AND_KILL_GENERATOR_HPP_
