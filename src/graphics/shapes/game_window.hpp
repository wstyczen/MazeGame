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
/**
 * @brief Class that combines figures to create window with visualisation of a MazeGame.
 *
 */
class GameWindow {
 public:
  /**
  * @brief Construct a new Game Window object
  *
  * @param maze maze to be visualised
  * @param cube_position starting position of a cube
  * @param goal destinate position of a cube
  */
  GameWindow(const maze::Layout& maze,
             const maze::Cell& cube_position,
             const maze::Cell& goal);
  /**
   * @brief Updates current state of each figure in window
   */
  void Act();
  /**
   * @brief Displays all figures in window
   *
   */
  void Show() const;
  /**
   * @brief Starts maze Appear() animation
   *
   */
  void LiftMaze();
  /**
   * @brief Starts maze Disappear() animation
   *
   */
  void DropMaze();
  /**
   * @brief Add taken path describing curently visited cells in order to display it
   *
   * @param maze maze in which path was taken
   * @param taken_path taken path
   */
  void AddTakenPath(const maze::Layout& maze,
                    const std::vector<maze::Position>& taken_path);
  /**
   * @brief Deletes taken path so it won't be displayed anymore
   *
   */
  void ResetTakenPath(){if(taken_path_)taken_path_.reset();}
  /**
   * @brief Add current solving path to be displayed
   *
   * @param maze maze which solution is given path
   * @param solution solution path
   */
  void AddSolvingPath(const maze::Layout& maze,
                      const std::vector<maze::Position>& solution);
  /**
   * @brief Deletes solving path so it won't be displayed anymore
   *
   */
  void ResetSolvingPath(){if(solving_path_)solving_path_.reset();}
  /**
   * @brief Deletes destination tile so it won't be displayed anymore
   *
   */
  void ResetDestination(){if(destination_)destination_.reset();}
  /**
   * @brief Checks if cube is moving
   *
   * @return true cube is moving
   * @return false cube is standing still
   */
  bool IsCubeMoving() const;
  /**
   * @brief Waits until cube will finish rolling animaton
   *
   */
  void WaitForCubeMoveToComplete();
  /**
   * @brief Moves Cube in diretion
   *
   * @param direction direction of Cube's move
   * @return true if Cube was standing still till method wasn't used
   * @return false if Cube is currently moving
   */
  bool MoveCube(const ComplexCube::FigureState& direction);
  /**
   * @brief Destroy the Game Window object,
   * makes sure that every figure object and
   * data in buffers related to them are deleted.
   */
  ~GameWindow();
  /**
   * @brief returns value of glfwWindowShouldClose() of window that is displayed
   *
   * @return true if user tried to close window
   * @return false if window should keep being displayed
   */
  bool WindowShouldClose() const { return glfwWindowShouldClose(window_); }
  /**
   * @brief Get the current state of given keyboard key while using window
   *
   * @param key Keyboard key to be checked
   * @return One of `GLFW_PRESS` or `GLFW_RELEASE`.
   */
  int GetKeyState(const int& key) const { return glfwGetKey(window_, key); }
  /**
   * @brief Creates figures in window needed to play a MazeGame
   *
   * @param maze maze to display
   * @param cube_position cube start position
   * @param goal cube destinate position
   */
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
  std::unique_ptr<DynamicSolidFigure> solving_path_;
  std::unique_ptr<DynamicSolidFigure> taken_path_;

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
