#include <cmath>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include "game/game.hpp"
#include "game/settings.hpp"
#include "graphics/shapes/game_window.hpp"
#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

void print_time_and_moves_left(game::Game* game) {
  std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
            << "Time left:\t\t\t" << game->TimeLeft() << "\n"
            << "Moves left:\t\t\t" << game->MovesLeft() << "\n"
            << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
}

void HandleKeyPress(GameWindow& game_window) {
  // Move forward
  if (game_window.GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
    game_window.MoveCube(ComplexCube::FigureState::move_north);
  }
  // Move backward
  if (game_window.GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
    game_window.MoveCube(ComplexCube::FigureState::move_south);
  }
  // Strafe right
  if (game_window.GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
    game_window.MoveCube(ComplexCube::FigureState::move_east);
  }
  // Strafe left
  if (game_window.GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
    game_window.MoveCube(ComplexCube::FigureState::move_west);
  }
}

int main(int argc, char* argv[]) {
  game::Game::Init(game::ReadFlags(argc, argv));
  game::Game* game = game::Game::GetInstance();

  GameWindow game_window(*game->layout(), game->position());
  game_window.LiftMaze();
  while (!game_window.WindowShouldClose()) {
    // Solving maze instance
    while (game->GetGameState() == game::GameState::UNDECIDED) {
      print_time_and_moves_left(game);

      HandleKeyPress(game_window);

      game_window.Show();
      game_window.Act();
    }
    game_window.WaitForCubeMoveToComplete();
    game_window.DropMaze();
    // Generate a new maze
    const auto result = game->GetGameState();
    game->OnGameFinished(result);
    // Reset game screen to display new maze
  }
  return 0;
}
