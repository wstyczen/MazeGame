#ifndef MAZE_KRUSKALS_GENERATOR_HPP_
#define MAZE_KRUSKALS_GENERATOR_HPP_

#include <deque>
#include <unordered_set>
#include <vector>

#include "generator.hpp"
#include "utility.hpp"

namespace maze {

class Layout;

class KruskalsGenerator : public Generator {
 public:
  ~KruskalsGenerator();

  std::unique_ptr<Layout> Get(const CellSize& cell_size) final;

 private:
  KruskalsGenerator();

  void InitializeCellTrees(const LayoutSize& layout_size);
  void InitializeEdges(const LayoutSize& layout_size);

  std::vector<CellTree> cell_trees_;
  std::deque<Edge> edges_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_KRUSKALS_GENERATOR_HPP_
