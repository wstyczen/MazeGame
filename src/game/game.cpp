#include "game/game.hpp"

#include <tuple>

#include "maze/paths.hpp"

namespace game {
using namespace std::chrono;

Game::Game(const maze::GeneratorType& generator_type,
           const maze::SolverType& solver_type,
           const maze::PathType& path_type,
           const maze::CellSize& cell_size)
    : generator_{maze::GeneratorFactory::GetInstance()->GetGenerator(
          generator_type)},
      solver_{maze::SolverFactory::GetInstance()->GetSolver(solver_type)},
      path_type_{path_type},
      layout_{generator_->Get(cell_size)} {
  std::tie(position_, goal_) = GetStartAndGoal(layout_.get(), path_type);
  visited_.push_back(position_);
}

Game::~Game() = default;

const maze::Layout* Game::layout() {
  return layout_.get();
}

void Game::SetMoveLimit(const uint16_t& move_limit) {
  move_limit_ = move_limit;
}

uint16_t Game::GetMovesMade() {
  return visited_.size() - 1;
}

bool Game::MoveLimitReached() {
  return GetMovesMade() >= move_limit_;
}

void Game::SetTimeLimit(const uint16_t& time_in_seconds) {
  time_limit_ = seconds(time_in_seconds);
}

void Game::StartTimer() {
  game_start_timestamp_ = high_resolution_clock::now();
}

std::chrono::seconds Game::TimeElapsed() {
  auto now = high_resolution_clock::now();
  return duration_cast<seconds>(now - game_start_timestamp_);
}

bool Game::TimeExceeded() {
  return TimeElapsed() > time_limit_;
}

bool Game::Move(const maze::Direction& direction) {
  maze::Edge move(position_, direction);
  if (!layout_->CanMove(move))
    return false;
  position_ = *move.To();
  visited_.push_back(position_);
  return true;
}

}  // namespace game
