#ifndef MAZE_ELLERS_GENERATOR_HPP_
#define MAZE_ELLERS_GENERATOR_HPP_

#include <deque>
#include <list>
#include <unordered_set>
#include <utility>

#include "generator.hpp"
#include "utility.hpp"

namespace maze {

class EllersGenerator : public Generator {
  using RowTrees = std::vector<std::list<CellTree>::iterator>;
  using Row = std::pair<std::vector<Cell>, RowTrees>;

 public:
  ~EllersGenerator();

  std::unique_ptr<Layout> Get(const CellSize& cell_size) final;

 private:
  EllersGenerator();

  Row GetRow(const LayoutSize& layout_size, const uint16_t& row_index);

  void MergeCellsInRow(Layout* const layout, Row& row, bool randomly = true);

  // List does not invalidate iterators / pointers on insertion / removal
  std::list<CellTree> cell_trees_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_ELLERS_GENERATOR_HPP_
