#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

#include "graphics/shapes/complex_cube.hpp"
#include "graphics/shapes/data_buffers/EBO.hpp"
#include "graphics/shapes/data_buffers/VAO.hpp"
#include "graphics/shapes/data_buffers/VBO.hpp"
#include "graphics/shapes/maze_figure.hpp"

#include "game/difficulty.hpp"
#include "game/game.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/paths.hpp"
#include "maze/solvers/solver_factory.hpp"

const unsigned int width(1000), height(1000);

namespace {

enum class GameState {
  UNDECIDED,
  LOST,
  WON,
};

GameState GetGameState(const game::Game& game) {
  if (game.GoalReached())
    return GameState::WON;
  if (game.MoveLimitReached() || game.TimeLimitReached())
    return GameState::LOST;
  return GameState::UNDECIDED;
}

}  // namespace

int main() {
  // Initialize GLFW
  glfwInit();
  // Tell GLFW what version of OpenGL we are using
  // In this case we are using OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Tell GLFW we are using the CORE profile
  // So that means we only have the modern functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
  GLFWwindow* window = glfwCreateWindow(width, height, "MazeGame", NULL, NULL);
  glfwMaximizeWindow(window);
  // Error check if the window fails to create
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  // Introduce the window into the current context
  glfwMakeContextCurrent(window);
  // Load GLAD so it configures OpenGL
  gladLoadGL();
  // Specify the viewport of OpenGL in the Window
  // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
  glViewport(0, 0, width, height);

  Shader shaderProgram(".//graphics//shaders//default.vert",
                       ".//graphics//shaders//default.frag");

  const uint16_t maze_size = 15;
  game::Game game(maze::GeneratorType::GROWING_TREE, maze::SolverType::A_STAR,
                  maze::PathType::TOP_LEFT_TO_BOTTOM_RIGHT,
                  game::DifficultyLevel::HARD, {maze_size, maze_size});
  const struct MazeSettings {
    float maze_height;
    float maze_scale;
  } maze_settings_ = {1.5f, 3.0f};
  const struct CubeSettings {
    glm::vec3 vertex_color;
    glm::vec3 inner_color;
  } cube_settings_ = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
  glm::vec3 cube_start_position = {-maze_size + 1, -maze_size + 1,
                                   -maze_size * maze_settings_.maze_scale};
  ComplexCube cube({cube_start_position,
                    {0.0f, 0.0f, 0.0f},
                    cube_settings_.vertex_color,
                    cube_settings_.inner_color});
  glm::vec3 maze_start_position = {-maze_size, -maze_size,
                                   -maze_size * maze_settings_.maze_scale};

  MazeFigure maze_fig(MazeFigure::Layout2VecOfWalls(game.layout()),
                      maze_settings_.maze_height, maze_start_position);

  // Generates Shader object using shaders defualt.vert and default.frag
  glEnable(GL_DEPTH_TEST);
  double prevTime = glfwGetTime();
  maze_fig.Appear();

  // Find a good place to put it
  game.StartTimer();

  while (!glfwWindowShouldClose(window) &&
         GetGameState(game) == GameState::UNDECIDED) {
    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram.Activate();
    // glm::vec3 angle(0.01f, 0.0f, 0.0f);
    double crntTime = glfwGetTime();
    // cube.MoveAnimation(ComplexCube::MoveDirection::north);
    //  if(crntTime - floor(crntTime / 5) * 5.0f < 0.05f){
    //      cube.MakeMove(ComplexCube::MoveDirection::move_east);
    //  }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      cube.MakeMove(ComplexCube::FigureState::move_north);
      game.Move(maze::Direction::UP);
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      cube.MakeMove(ComplexCube::FigureState::move_south);
      game.Move(maze::Direction::DOWN);
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      cube.MakeMove(ComplexCube::FigureState::move_east);
      game.Move(maze::Direction::RIGHT);
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      cube.MakeMove(ComplexCube::FigureState::move_west);
      game.Move(maze::Direction::LEFT);
    }

    if (crntTime - prevTime >= 1 / 60) {
      cube.Act();
      maze_fig.Act();
      cube.Show(shaderProgram.GetId());
      maze_fig.Show(shaderProgram.GetId());
      prevTime = crntTime;
    }

    glfwSwapBuffers(window);
    // Take care of all GLFW events
    glfwPollEvents();
  }

  // Delete all the objects we've created
  shaderProgram.Delete();
  glfwDestroyWindow(window);
  // Terminate GLFW before ending the program
  glfwTerminate();
  return 0;
}
