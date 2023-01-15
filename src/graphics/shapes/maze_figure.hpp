#ifndef MAZE_FIGURE_HPP_
#define MAZE_FIGURE_HPP_
#include "graphics/shapes/dynamic_solid_figure.hpp"
#include "maze/layout.hpp"

namespace graphics {
/**
 * @brief Contains all needed information to create a shape.
 */
struct FigureVertexData {
  std::vector<GLfloat> vertices;
  std::vector<GLuint> indices;
};
/**
 * @brief Figure in shape of a maze.
 *
 */
class MazeFigure : public DynamicSolidFigure {
 public:
  /**
   * @brief Describes current state of a MazeFigure
   */
  enum FigureState { appear, disappear, steady };
  /**
   * @brief Settings of a MazeFigure that contain information about it's movement
   *
   */
  struct MoveSettings {
    //acceleration of a MazeFigure while moving
    float acceleration;
    //start velocity of a MazeFigure when triggered by Disappear() or Appear() method
    float start_velocity;
  };
  /**
   * @brief Contains all settings desribing apearance and behaviour of a MazeFigure
   *
   */
  struct MazeSettings{
    //height of a MazeFigure
    GLfloat height;
    //Size of a grid on which walls of a maze are placed
    GLfloat cell_size;
    //lenght of base edge of each wall in maze which are cuboids with square base
    GLfloat side_of_a_base;
    //color of MazeFigure, values should be in [0,1]
    glm::vec3 color;
    //shading of a vertical sides of a wall, values should be in [0,1]
    glm::vec2 shading;
    //settings defines movement speed
    MoveSettings move_settings;
  };
  /**
   * @brief Construct a new Maze Figure object
   *
   * @param maze vector of coordinates of walls in maze, around each coordinate wall will be placed
   * @param posi starting position
   * @param pos starting pose
   * @param maze_settings settings of a maze
   */
  MazeFigure(const std::vector<glm::vec2>& maze,
            const glm::vec3 &posi,
            const glm::vec3 &pos,
            const MazeSettings &maze_settings);
  /**
   * @brief Construct a new Maze Figure from DynamicSolidFigure, usable to expand DynamicSolidFigure functionality
   *
   * @param maze_figure figure to enhance
   * @param maze_settings settings of new MazeFigure object
   */
  MazeFigure(const DynamicSolidFigure &maze_figure,
              const MazeSettings &maze_settings);

  /**
   * @brief Triggers MazeFigure to appear
   *
   */
  void Appear();
  /**
   * @brief Triggers MazeFigure to disappear
   *
   */
  void Disappear();
  /**
   * @brief Check if MazeFigure is currently moving
   *
   * @return true if state isn't equal MazeFigure::FigureState::steady
   * @return else false
   */
  bool IsMoving();
  /**
   * @brief Describes MazeFigure's behaviour as state machine depending on move_state_ value. \n
   * States of maze: \n
   * -steady - maze is not moving, \n
   * -appear - maze will lift until it approaches it's beggining position, \n
   * -disappear - maze will lower itself until it disappears \n
   *
   * Speed of movement is described by maze_settings_
   */
  void Act();
  static std::vector<glm::vec2> Path2Vec(const maze::Layout& maze,
                                         const std::vector<maze::Cell> path);
  /*! @brief Converts maze as Layout to a vector of mazes walls coordinates
  @param[in] maze Pointer to a maze being converted.
  @return Vector of coordinates of walls that maze is made of.
  */
  static std::vector<glm::vec2> Layout2VecOfWalls(const maze::Layout* maze);
  /**
   * @brief Creates DynamicSolidFigure as construction of walls placed in given coordinates
   *
   * @param maze_walls coordinates in which walls will be placed.
   * @param wall_model 3D model of a wall described as FigureVertexData object
   * @param posi starting position
   * @param pos starting pose
   * @param cell_size size of a grid on which walls of a maze are placed
   * @return DynamicSolidFigure in shape of a maze
   */
  static DynamicSolidFigure VectorToMapFigure(
      const std::vector<glm::vec2>& maze_walls,
      const FigureVertexData& wall_model,
      const glm::vec3& posi,
      const glm::vec3& pos,
      const GLfloat& cell_size);
  /**
   * @brief Creates FigureVertexData object describing a cuboid with a square base, cuboid has no floor in order to reduce data
   *
   * @param height height of a cuboid
   * @param side_of_a_base side of a square base
   * @param celling_color color of the top side
   * @param wall_shading the way that top color changes towards down
   * @return FigureVertexData describing cuboid
   */
  static FigureVertexData GetWallTemplate(const GLfloat& height,
                                          const GLfloat& side_of_a_base,
                                          const glm::vec3& celling_color,
                                          const glm::vec2& wall_shading);

 protected:
  //settings of a MazeFigure
  MazeSettings maze_settings_;
  //Start position of a MazeFigure
  glm::vec3 start_position_;
  //current velocity of a MazeFigure
  glm::vec3 lin_vel_ = {0.0f, 0.0f, 0.0f};
  //Current state of a MazeFigure
  MazeFigure::FigureState move_state_ = steady;
};
}  // namespace graphics
#endif
