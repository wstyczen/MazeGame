#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

#include "game/game.hpp"
#include "game/settings.hpp"
#include "graphics/shapes/game_window.hpp"

void print_time_and_moves_left(game::Game* game) {
  if (game->TimeLeft() != -1){}
    // std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
    //           << "Time left:\t\t\t" << static_cast<int>(game->TimeLeft())
    //           << "\n"
    //           << "Moves left:\t\t\t" << game->MovesLeft() << "\n"
    //           << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
}

void HandleKeyPress(graphics::GameWindow& game_window, const game::Game* game) {
  if (game_window.GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_north);
  } else if (game_window.GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_south);
  } else if (game_window.GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_east);
  } else if (game_window.GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
    game_window.MoveCube(graphics::ComplexCube::FigureState::move_west);
  } else {
    return;
  }
  game_window.AddTakenPath(*game->layout(), *game->path());
}

int main(int argc, char* argv[]) {
  const game::Settings settings = game::ReadFlags(argc, argv);
  std::cout << settings;
  game::Game::Init(settings);

  game::Game* game = game::Game::GetInstance();
  graphics::GameWindow game_window(*game->layout(), game->position(),
                                   game->goal());
  while (!game_window.WindowShouldClose()) {
    game_window.LiftMaze();
    game->StartTimerIfNotAlreadyRunning();
    // Solving maze instance
    while (game->GetGameState() == game::GameState::UNDECIDED &&
           !game_window.WindowShouldClose()) {
      print_time_and_moves_left(game);
      HandleKeyPress(game_window, game);

      game_window.Show();
      game_window.Act();
    }
    game_window.WaitForCubeMoveToComplete();
    const auto result = game->GetGameState();
    if (result == game::GameState::LOST) {
      using namespace std::chrono_literals;
      game_window.AddSolvingPath(*game->layout(), game->solution());
      game_window.Show();
      std::this_thread::sleep_for(5s);
    }
    game_window.DropMaze();
    // Generate a new maze
    game->OnGameFinished(result);
    // Reset game screen to display new maze
    game_window.InitFigures(*game->layout(), game->position(), game->goal());
  }
  return 0;
}
