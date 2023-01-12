#include <cmath>
#include <iostream>

#include "game/game.hpp"
#include "game/settings.hpp"
#include "graphics/shapes/game_window.hpp"

void print_time_and_moves_left(game::Game* game) {
  if (game->TimeLeft() != -1)
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
              << "Time left:\t\t\t" << static_cast<int>(game->TimeLeft())
              << "\n"
              << "Moves left:\t\t\t" << game->MovesLeft() << "\n"
              << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
}

void HandleKeyPress(graphics::GameWindow& game_window) {
  // Move forward
  if (game_window.GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_north);
  }
  // Move backward
  if (game_window.GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_south);
  }
  // Strafe right
  if (game_window.GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_east);
  }
  // Strafe left
  if (game_window.GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_west);
  }
}

int main(int argc, char* argv[]) {
  const game::Settings settings = game::ReadFlags(argc, argv);
  std::cout << settings;
  game::Game::Init(settings);

  game::Game* game = game::Game::GetInstance();
  GameWindow game_window(*game->layout(), game->position(), game->goal());
  while (!game_window.WindowShouldClose()) {
    game_window.LiftMaze();
    // Solving maze instance
    while (game->GetGameState() == game::GameState::UNDECIDED &&
           !game_window.WindowShouldClose()) {
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
    game_window.InitFigures(*game->layout(), game->position(), game->goal());
  }
  return 0;
}
