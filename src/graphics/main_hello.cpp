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

int main(int argc, char* argv[]) {
  game::Game game(game::ReadFlags(argc, argv));

  GameWindow game_window(*game.layout(), game.position());
  game_window.LiftMaze();
  while (!game_window.WindowShouldClose()) {
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
    game_window.Show();
    game_window.Act();
  }

  return 0;
}
