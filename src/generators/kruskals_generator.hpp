#ifndef MAZE_KRUSKALS_GENERATOR_HPP_
#define MAZE_KRUSKALS_GENERATOR_HPP_

#include <deque>
#include <set>
#include <vector>

#include "boost/graph/adjacency_list.hpp"

#include "generator.hpp"
#include "generator_factory.hpp"
#include "utility.hpp"

namespace maze {

class KruskalsGenerator : public Generator {
 public:
  ~KruskalsGenerator();

  std::unique_ptr<Layout> Get(
      const uint16_t& tiles_vertical,
      const uint16_t& tiles_horizontal
  ) override;

 private:
  KruskalsGenerator();

  void InitializeCellTrees(
      const uint16_t& tiles_vertical,
      const uint16_t& tiles_horizontal
  );
  void InitializeEdges(
      const uint16_t& tiles_vertical,
      const uint16_t& tiles_horizontal
  );

  std::vector<std::set<Position>> tile_trees_;
  std::deque<Edge> edges_;

  friend class GeneratorFactory;
};

}  // namespace maze

#endif  // MAZE_KRUSKALS_GENERATOR_HPP_
