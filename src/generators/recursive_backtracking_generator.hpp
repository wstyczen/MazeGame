#ifndef MAZE_RECURSIVE_BACKTRACKING_GENERATOR_HPP_
#define MAZE_RECURSIVE_BACKTRACKING_GENERATOR_HPP_

#include <memory>
#include <set>

#include "generator.hpp"
#include "layout.hpp"
#include "utility.hpp"

namespace maze {

class RecursiveBacktrackingGenerator : public Generator {
 public:
  virtual std::unique_ptr<Layout> Get(
      const uint16_t& cells_vertical,
      const uint16_t& cells_horizontal
  ) override;
  ~RecursiveBacktrackingGenerator();

 private:
  RecursiveBacktrackingGenerator();

  void
  InitializeCells(const uint16_t& layout_rows, const uint16_t& layout_cols);

  void Move(Layout* const layout, const Position& position);

  std::set<Position> unvisited_cells_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_RECURSIVE_BACKTRACKING_GENERATOR_HPP_
