#ifndef GAME_WINDOW_HPP_
#define GAME_WINDOW_HPP_
#include "graphics/shapes/complex_cube.hpp"
#include "graphics/shapes/maze_figure.hpp"

#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

class GameWindow {
 public:
  GameWindow(const maze::Layout& maze);
  void Act();
  void Show();
  void LiftMaze();
  bool MoveCube(const ComplexCube::FigureState& direction);
  ~GameWindow();
  bool WindowShouldClose() const { return glfwWindowShouldClose(window_); }
  int GetKeyState(const int& key) const { return glfwGetKey(window_, key); }

 private:
  std::unique_ptr<Shader> shader_;
  std::pair<unsigned int, unsigned int> display_solution_;
  GLFWwindow* window_;
  std::unique_ptr<MazeFigure> maze_;
  std::unique_ptr<ComplexCube> cube_;
  std::unique_ptr<SolidFigure> floor_;
  double last_action_time;
  void InitGLFW();
  void InitFigures(const maze::Layout& maze);

  const struct MazeSettings {
    float maze_height;
    float maze_scale;
    glm::vec3 floor_color;
  } maze_settings_ = {1.5f, 3.0f, {0.1f, 0.1f, 0.0f}};
  const struct CubeSettings {
    glm::vec3 vertex_color;
    glm::vec3 inner_color;
  } cube_settings_ = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
  const struct WindowSettings {
    std::vector<float> ClearColor;
  } Window_settings_ = {{0.07f, 0.13f, 0.17f, 0.5f}};
};
#endif
