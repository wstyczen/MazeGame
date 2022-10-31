#ifndef MAZE_RECURSIVE_BACKTRACKING_GENERATOR_HPP_
#define MAZE_RECURSIVE_BACKTRACKING_GENERATOR_HPP_

#include <memory>
#include <set>

#include "generator.hpp"
#include "layout.hpp"
#include "unvisited.hpp"
#include "utility.hpp"

namespace maze {

class RecursiveBacktrackingGenerator : public Generator, public Unvisited {
 public:
  virtual std::unique_ptr<Layout>
  Get(const uint16_t& cells_vertical, const uint16_t& cells_horizontal) final;
  ~RecursiveBacktrackingGenerator();

 private:
  RecursiveBacktrackingGenerator();

  void Move(Layout* const layout, const Position& position);

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_RECURSIVE_BACKTRACKING_GENERATOR_HPP_
