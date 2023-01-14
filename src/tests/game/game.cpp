#include "gtest/gtest.h"

#include <chrono>

#include "game/game.hpp"
#include "game/maze.hpp"
#include "game/settings.hpp"
#include "maze/layout.hpp"
#include "maze/utility.hpp"

namespace tests {
namespace {

class Game : public ::testing::Test {
 protected:
  const std::string layout_str_ = std::string(
      "#######\n"
      "#     #\n"
      "##### #\n"
      "#   # #\n"
      "### # #\n"
      "#     #\n"
      "#######");

  game::Game* GetGame(game::Settings settings = game::GetDefaultFlags()) {
    settings.starting_size = maze::CellSize(3, 3);
    game::Game::NewInstance(settings);
    game::Game* game = game::Game::GetInstance();
    auto maze = game::Maze(
        std::make_unique<maze::Layout>(maze::Layout::FromString(layout_str_)),
        maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT);
    game->Test_SetMaze(maze);
    return game;
  }

  void MoveDirectlyFromTopLeftToBottomRight(game::Game* game) {
    ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
    ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
    ASSERT_TRUE(game->Move(maze::Direction::DOWN));
    ASSERT_TRUE(game->Move(maze::Direction::DOWN));
  }
};

TEST_F(Game, MovesMade) {
  game::Game* game = GetGame();
  ASSERT_FALSE(game->Move(maze::Direction::DOWN));
  ASSERT_EQ(game->GetMovesMade(), 0);
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_EQ(game->GetMovesMade(), 1);
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_EQ(game->GetMovesMade(), 2);
  ASSERT_TRUE(game->Move(maze::Direction::DOWN));
}

TEST_F(Game, MovesLeft) {
  game::Game* game = GetGame();
  ASSERT_EQ(game->MovesLeft(), 5);

  ASSERT_FALSE(game->Move(maze::Direction::DOWN));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_EQ(game->MovesLeft(), 4);
}

TEST_F(Game, MoveLimitReached) {
  game::Game* game = GetGame();
  ASSERT_EQ(game->MovesLeft(), 5);
  ASSERT_FALSE(game->MoveLimitReached());

  ASSERT_FALSE(game->Move(maze::Direction::UP));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_TRUE(game->Move(maze::Direction::LEFT));
  ASSERT_TRUE(game->Move(maze::Direction::LEFT));
  ASSERT_FALSE(game->MoveLimitReached());

  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_TRUE(game->MoveLimitReached());
}

TEST_F(Game, Solution) {
  game::Game* game = GetGame();
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  maze::Path solution = {{1, 3}, {1, 5}, {3, 5}, {5, 5}};
  maze::Path got_solution = game->solution();
  ASSERT_EQ(game->solution(), solution);
}

TEST_F(Game, GameStateWin) {
  game::Game* game = GetGame();
  ASSERT_EQ(game->GetGameState(), game::GameState::UNDECIDED);
  MoveDirectlyFromTopLeftToBottomRight(game);
  ASSERT_TRUE(game->GoalReached());
  ASSERT_EQ(game->GetGameState(), game::GameState::WON);
}

TEST_F(Game, GameStateLose) {
  game::Game* game = GetGame();
  ASSERT_EQ(game->GetGameState(), game::GameState::UNDECIDED);
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_TRUE(game->Move(maze::Direction::LEFT));
  ASSERT_TRUE(game->Move(maze::Direction::LEFT));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));
  ASSERT_FALSE(game->GoalReached());
  ASSERT_EQ(game->GetGameState(), game::GameState::LOST);
}

TEST_F(Game, OnGameWon) {
  game::Game* game = GetGame();

  ASSERT_EQ(game->mazes_completed(), 0);
  ASSERT_EQ(game->layout()->cell_size(), maze::CellSize(3, 3));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));

  ASSERT_EQ(game->position(), maze::Cell(1, 3));
  ASSERT_EQ(game->goal(), maze::Cell(5, 5));
  ASSERT_EQ(game->GetMovesMade(), 1);

  game->OnGameFinished(game::GameState::WON);

  ASSERT_EQ(game->mazes_completed(), 1);
  ASSERT_EQ(game->layout()->cell_size(), maze::CellSize(7, 7));
  ASSERT_EQ(game->position(), maze::Cell(1, 1));
  ASSERT_EQ(game->goal(), maze::Cell(13, 13));
  ASSERT_EQ(game->GetMovesMade(), 0);
}

TEST_F(Game, OnGameLost) {
  game::Game* game = GetGame();

  ASSERT_EQ(game->mazes_completed(), 0);
  ASSERT_EQ(game->layout()->cell_size(), maze::CellSize(3, 3));
  ASSERT_TRUE(game->Move(maze::Direction::RIGHT));

  ASSERT_EQ(game->position(), maze::Cell(1, 3));
  ASSERT_EQ(game->goal(), maze::Cell(5, 5));
  ASSERT_EQ(game->GetMovesMade(), 1);

  game->OnGameFinished(game::GameState::LOST);

  ASSERT_EQ(game->mazes_completed(), 0);
  ASSERT_EQ(game->layout()->cell_size(), maze::CellSize(3, 3));
  ASSERT_EQ(game->position(), maze::Cell(1, 1));
  ASSERT_EQ(game->goal(), maze::Cell(5, 5));
  ASSERT_EQ(game->GetMovesMade(), 0);
}

}  // namespace
}  // namespace tests
