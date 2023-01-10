#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include "graphics/shapes/game_window.hpp"

#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

int main() {
  GameWindow game(maze::GeneratorType::ELLERS, 15);
  while (!game.Close()) {
    if (game.GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_north);
    }
    if (game.GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_south);
    }
    if (game.GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_east);
    }
    if (game.GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_west);
    }
    game.Show();
    game.Act();
  }

  return 0;
}
