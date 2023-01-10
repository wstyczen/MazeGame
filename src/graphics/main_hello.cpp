#include <cmath>
#include <filesystem>
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
  maze::CellSize maze_size = {11, 11};
  const std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(
          maze::GeneratorType::RECURSIVE_BACKTRACKING);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get(maze_size);
  GameWindow game(*maze_layout);
  game.LiftMaze();
  while (!game.WindowShouldClose()) {
    // Move forward
    if (game.GetKeyState(GLFW_KEY_UP) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_north);
    }
    // Move backward
    if (game.GetKeyState(GLFW_KEY_DOWN) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_south);
    }
    // Strafe right
    if (game.GetKeyState(GLFW_KEY_RIGHT) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_east);
    }
    // Strafe left
    if (game.GetKeyState(GLFW_KEY_LEFT) == GLFW_PRESS) {
      game.MoveCube(ComplexCube::FigureState::move_west);
    }
    game.Show();
    game.Act();
  }

  return 0;
}
