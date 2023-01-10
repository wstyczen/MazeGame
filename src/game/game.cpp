#include "game/game.hpp"

#include <tuple>

#include "maze/paths.hpp"

namespace game {
using namespace std::chrono;

Game::Game(const Settings& settings)
    : settings_{settings},
      generator_{maze::GeneratorFactory::GetInstance()->GetGenerator(
          settings.generator_type)},
      solver_{
          maze::SolverFactory::GetInstance()->GetSolver(settings.solver_type)},
      maze_{generator_->Get(settings.starting_size), settings.path_type} {
  CalculateLimits();
}

Game::~Game() = default;

void Game::CalculateLimits() {
  const uint16_t minimal_moves_required =
      solver_->Solve(maze_.layout())->size() - 1;
  move_limit_ = GetMaxMoves(settings_.difficulty, minimal_moves_required);
  time_limit_ = GetMaxTimeInSecs(settings_.difficulty, minimal_moves_required);
}

void Game::GenerateNewMaze(const maze::CellSize& maze_size,
                           const maze::PathType& path_type) {
  maze_ = Maze(generator_->Get(maze_size), path_type);
  CalculateLimits();
}

void Game::OnGameFinished() {
  GenerateNewMaze(
      maze_.GetNextCellSize(GetMazeGrowthPerDifficulty(settings_.difficulty)),
      settings_.path_type);
}

const maze::Layout* Game::layout() const {
  return maze_.layout();
}

maze::Cell Game::position() const {
  return maze_.position();
}

uint16_t Game::time_limit() const {
  return time_limit_;
}

uint16_t Game::move_limit() const {
  return move_limit_;
}

uint16_t Game::GetMovesMade() const {
  return maze_.GetMovesMade();
}

bool Game::GoalReached() const {
  return maze_.GoalReached();
}

bool Game::Move(const maze::Direction& direction) {
  return maze_.Move(direction);
}

bool Game::MoveLimitReached() const {
  return GetMovesMade() >= move_limit_;
}

void Game::StartTimer() {
  game_start_time_ = std::chrono::high_resolution_clock::now();
}
double Game::TimeElapsed() const {
  auto now = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<double>(now - game_start_time_).count();
}
bool Game::TimeLimitReached() const {
  return TimeElapsed() >= time_limit_;
}

}  // namespace game
