#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <chrono>
#include <memory>

#include "game/difficulty.hpp"
#include "game/maze.hpp"
#include "game/settings.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver_factory.hpp"
#include "maze/utility.hpp"

namespace game {

class Game {
 public:
  Game(const Settings& settings);
  ~Game();

  const maze::Layout* layout() const;
  maze::Cell position() const;
  uint16_t time_limit() const;
  uint16_t move_limit() const;

  bool GoalReached() const;
  bool Move(const maze::Direction& direction);

  uint16_t GetMovesMade() const;
  bool MoveLimitReached() const;

  void StartTimer();
  double TimeElapsed() const;
  bool TimeLimitReached() const;

  void OnGameFinished();

 private:
  void GenerateNewMaze(const maze::CellSize& maze_size,
                       const maze::PathType& path_type);
  void CalculateLimits();

  Settings settings_;
  std::unique_ptr<maze::Generator> generator_;
  std::unique_ptr<maze::Solver> solver_;

  game::Maze maze_;

  uint16_t move_limit_;
  uint16_t time_limit_;

  std::chrono::time_point<std::chrono::high_resolution_clock> game_start_time_;
  uint16_t mazes_completed_;
};

}  // namespace game

#endif  // GAME_GAME_HPP_
