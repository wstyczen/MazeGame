#ifndef MAZE_KRUSKALS_GENERATOR_HPP_
#define MAZE_KRUSKALS_GENERATOR_HPP_

#include <deque>
#include <set>
#include <vector>

// #include "boost/graph/adjacency_list.hpp"

#include "generator.hpp"
#include "utility.hpp"

namespace maze {

class KruskalsGenerator : public Generator {
 public:
  ~KruskalsGenerator();

  std::unique_ptr<Layout>
  Get(const uint16_t& cells_vertical, const uint16_t& cells_horizontal) final;

 private:
  KruskalsGenerator();

  void InitializeCellTrees(
      const uint16_t& cells_vertical,
      const uint16_t& cells_horizontal
  );
  void InitializeEdges(
      const uint16_t& cells_vertical,
      const uint16_t& cells_horizontal
  );

  std::vector<std::set<Position>> cell_trees_;
  std::deque<Edge> edges_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_KRUSKALS_GENERATOR_HPP_
