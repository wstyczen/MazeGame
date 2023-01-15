#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <utility>

#include "game/game.hpp"
#include "game/settings.hpp"
#include "graphics/shapes/game_window.hpp"

void print_time_and_moves_left(game::Game* game) {
  struct TimeAndMoves {
    int seconds_left;
    uint16_t moves_left;
    bool operator==(const TimeAndMoves& other) {
      return seconds_left == other.seconds_left &&
             moves_left == other.moves_left;
    }
  };
  static TimeAndMoves current, previous = {-1, 0};
  current = {static_cast<int>(game->TimeLeft()), game->MovesLeft()};
  if (current.seconds_left != -1 && current != previous) {
    std::cout << "--------------------------------------------------\n"
              << "Time left:\t\t\t" << current.seconds_left << "\n"
              << "Moves left:\t\t\t" << current.moves_left << "\n"
              << "--------------------------------------------------\n";
  }
  previous = current;
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
