#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <chrono>
#include <memory>

#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver_factory.hpp"
#include "maze/utility.hpp"

namespace game {
class Game {
 public:
  Game(const maze::GeneratorType& generator_type,
       const maze::SolverType& solver_type,
       const maze::PathType& path_type,
       const maze::CellSize& cell_size);
  ~Game();

  const maze::Layout* layout();

  void SetMoveLimit(const uint16_t& move_limit);
  uint16_t GetMovesMade();
  bool MoveLimitReached();

  void SetTimeLimit(const uint16_t& seconds);
  void StartTimer();
  std::chrono::seconds TimeElapsed();
  bool TimeExceeded();

  bool Move(const maze::Direction& direction);

 private:
  std::unique_ptr<maze::Generator> generator_;
  std::unique_ptr<maze::Solver> solver_;
  maze::PathType path_type_;

  std::unique_ptr<maze::Layout> layout_;
  maze::Cell goal_;

  maze::Cell position_;
  maze::Path visited_;
  uint16_t move_limit_;

  std::chrono::high_resolution_clock::time_point game_start_timestamp_;
  std::chrono::seconds time_limit_;
};

}  // namespace game

#endif  // GAME_GAME_HPP_
