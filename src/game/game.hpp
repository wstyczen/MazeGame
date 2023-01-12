#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include <chrono>
#include <memory>
#include <optional>

#include "game/difficulty.hpp"
#include "game/maze.hpp"
#include "game/settings.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver_factory.hpp"
#include "maze/utility.hpp"

namespace game {

enum class GameState {
  UNDECIDED,
  LOST,
  WON,
};

class Game {
 public:
  ~Game();
  static void Init(const Settings& settings);
  static Game* GetInstance();

  const maze::Layout* layout() const;
  maze::Cell position() const;
  maze::Cell goal() const;
  const maze::Path* path() const;
  maze::Path solution() const;
  uint16_t time_limit() const;
  uint16_t move_limit() const;

  bool GoalReached() const;
  bool Move(const maze::Direction& direction);

  uint16_t GetMovesMade() const;
  uint16_t MovesLeft() const;
  bool MoveLimitReached() const;

  void StartTimerIfNotAlreadyRunning();
  double TimeLeft() const;
  bool TimeLimitReached() const;

  GameState GetGameState() const;
  void OnGameFinished(const GameState& game_result);

 private:
  Game(const Settings& settings);
  void GenerateNewMaze(const maze::CellSize& maze_size,
                       const maze::PathType& path_type);
  void CalculateLimits();

  Settings settings_;
  std::unique_ptr<maze::Generator> generator_;
  std::unique_ptr<maze::Solver> solver_;

  game::Maze maze_;

  uint16_t move_limit_;
  uint16_t time_limit_;

  std::optional<std::chrono::time_point<std::chrono::high_resolution_clock>>
      game_start_time_;
  uint16_t mazes_completed_;

  static Game* instance_;
};

}  // namespace game

#endif  // GAME_GAME_HPP_
