#ifndef MAZE_DJIKSTRA_SOLVER_HPP_
#define MAZE_DJIKSTRA_SOLVER_HPP_

#include <queue>
#include <unordered_map>
#include <vector>

#include "predecessors.hpp"
#include "solver.hpp"
#include "unvisited.hpp"

namespace maze {

namespace djikstra {

using Distance = std::pair<uint16_t, Cell>;

}

class DjikstraSolver : public Solver, public Predecessors {
 public:
  ~DjikstraSolver();

  std::optional<Path>
  Solve(const Layout* const layout, const Cell& start, const Cell& goal) final;

 private:
  DjikstraSolver();

  void InitializeDistances();
  bool ProcessUnvisitedWithShortestDistance();

  std::unordered_map<Cell, uint16_t> distances_;
  std::priority_queue<
      djikstra::Distance,
      std::vector<djikstra::Distance>,
      std::greater<djikstra::Distance>>
      minimum_distance_queue_;
  std::function<bool(const Cell&, const Direction&)> move_validity_check_;

  static const uint16_t max_distance;

  friend class SolverFactory;
};

}  // namespace maze

#endif  // MAZE_DJIKSTRA_SOLVER_HPP_
