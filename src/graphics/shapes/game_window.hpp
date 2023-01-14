#ifndef GAME_WINDOW_HPP_
#define GAME_WINDOW_HPP_
#include "graphics/shapes/complex_cube.hpp"
#include "graphics/shapes/maze_figure.hpp"
#include "graphics/shapes/path_figure.hpp"

#include "game/game.hpp"
#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"
namespace graphics {

class GameWindow {
 public:
  GameWindow(const maze::Layout& maze,
             const maze::Cell& cube_position,
             const maze::Cell& goal);
  void Act();
  void Show() const;
  void LiftMaze();
  void DropMaze();

  void AddTakenPath(const maze::Layout& maze,
                    const std::vector<maze::Position>& solution);
  void DropTakenPath();
  void ResetTakenPath();
  void AddSolvingPath(const maze::Layout& maze,
                      const std::vector<maze::Position>& solution);
  void DropSolvingPath();
  void ResetSolvingPath();

  bool IsCubeMoving() const;
  void WaitForCubeMoveToComplete();
  bool MoveCube(const ComplexCube::FigureState& direction);
  ~GameWindow();
  bool WindowShouldClose() const { return glfwWindowShouldClose(window_); }
  int GetKeyState(const int& key) const { return glfwGetKey(window_, key); }
  void InitFigures(const maze::Layout& maze,
                   const maze::Cell& cube_position,
                   const maze::Cell& goal);

 private:
  void WaitForMazeMoveToComplete();
  void InitGLFW();
  glm::vec3 GetMazePosition(const maze::Layout& maze) const;
  glm::vec3 GetAsVec(const maze::Layout& maze,
                     const maze::Cell& position) const;
  GLfloat GetMazeBiggerDimension(const maze::Layout& maze) const;
  SolidFigure CreateRectFromCoord(const GLfloat& height,
                                  const GLfloat& width,
                                  const glm::vec3& position,
                                  const glm::vec3& color) const;
  void FixRenderingRange(const maze::Layout& maze);

  std::unique_ptr<Shader> shader_;
  struct DisplaySolution {
    int width;
    int height;
  } display_solution_;
  GLFWwindow* window_;
  std::unique_ptr<MazeFigure> maze_;
  std::unique_ptr<ComplexCube> cube_;
  std::unique_ptr<SolidFigure> floor_;
  std::unique_ptr<SolidFigure> destination_;
  std::unique_ptr<MazeFigure> solving_path_;
  std::unique_ptr<MazeFigure> taken_path_;
  std::unique_ptr<PathFigure> path_;

  double last_action_time;

  const struct MazeSettings {
    MazeFigure::MazeSettings maze_settings;
    GLfloat maze_scale;
    glm::vec3 floor_color;
    GLfloat move_map_down;
  } maze_settings_ = {{1.5f, 1.0f, 0.95, {0.8, 0.8, 0.8}, {0.7, 0.1}, {0.0f, 0.0001f}},
                      1.5f, {0.1f, 0.1f, 0.0f}, 0.03f};
  const struct CubeSettings {
    ComplexCube::MoveSettings move_settings;
    glm::vec3 vertex_color;
    glm::vec3 inner_color;
    GLfloat cube_size;
  } cube_settings_ = {{0.2f, 2.0f, 2}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 1.0f};
  const struct WindowSettings {
    std::vector<float> ClearColor;
  } Window_settings_ = {{0.07f, 0.13f, 0.17f, 0.5f}};
  glm::vec3 maze_position_;

  const struct PathSettings {
    GLfloat height;
    GLfloat size_of_a_cube;
    glm::vec3 color_a;
    glm::vec3 color_b;
  } path_settings_ = {0.5f, 0.8f, glm::vec3{1.0f, 0.1f, 0.1f}, glm::vec3{0.0f, 1.0f, 0.1f}};
  PathFigure::PathSettings test_settings_ = {1.0f, 0.7f, {1.0f, 0.0f, 0.3f}};
};

}  // namespace graphics
#endif
