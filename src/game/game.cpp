#include "game/game.hpp"

#include <tuple>

#include "game/settings.hpp"
#include "maze/paths.hpp"

namespace game {

namespace {

double GetTimeElapsed(
    std::chrono::time_point<std::chrono::high_resolution_clock> time) {
  return std::chrono::duration<double>(
             std::chrono::high_resolution_clock::now() - time)
      .count();
}

}  // namespace

Game* Game::instance_ = nullptr;

Game::Game(const Settings& settings)
    : settings_{settings},
      generator_{maze::GeneratorFactory::GetInstance()->GetGenerator(
          settings.generator_type)},
      solver_{
          maze::SolverFactory::GetInstance()->GetSolver(settings.solver_type)},
      maze_{generator_->Get(settings.starting_size), settings.path_type},
      mazes_completed_{} {
  CalculateLimits();
}

Game::~Game() = default;

void Game::Init(const Settings& settings) {
  if (!instance_) {
    instance_ = new Game(settings);
  }
}
Game* Game::GetInstance() {
  if (!instance_) {
    instance_ = new Game(GetDefaultFlags());
  }
  return instance_;
}

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

GameState Game::GetGameState() const {
  if (GoalReached())
    return GameState::WON;
  if (MoveLimitReached() || TimeLimitReached())
    return GameState::LOST;
  return GameState::UNDECIDED;
}

void Game::OnGameFinished(const GameState& game_result) {
  if (game_result == GameState::WON) {
    GenerateNewMaze(
        maze_.GetNextCellSize(GetMazeGrowthPerDifficulty(settings_.difficulty)),
        settings_.path_type);
    ++mazes_completed_;
    return;
  }
  if (game_result == GameState::LOST) {
    GenerateNewMaze(settings_.starting_size, settings_.path_type);
    mazes_completed_ = 0;
    return;
  }
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
uint16_t Game::MovesLeft() const {
  return move_limit_ - maze_.GetMovesMade();
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

void Game::StartTimerIfNotAlreadyRunning() {
  if (!game_start_time_)
    game_start_time_ = std::chrono::high_resolution_clock::now();
}
double Game::TimeLeft() const {
  if (!game_start_time_)
    return -1;
  return static_cast<double>(time_limit_) - GetTimeElapsed(*game_start_time_);
}
bool Game::TimeLimitReached() const {
  return game_start_time_ && TimeLeft() <= 0;
}

}  // namespace game
