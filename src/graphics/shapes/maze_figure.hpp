#ifndef MAZE_FIGURE_HPP_
#define MAZE_FIGURE_HPP_
#include "graphics/shapes/dynamic_solid_figure.hpp"
#include "maze/layout.hpp"

namespace graphics{

struct FigureVertexData{
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
  };

FigureVertexData GetCellTemplate(const GLfloat &side_of_a_base, const glm::vec3 &color);

std::vector<glm::vec2> Path2Vec2(const maze::Layout* maze,
                                 const std::vector<maze::Cell> path);

class MazeFigure : public DynamicSolidFigure {
 public:
  enum FigureState { appear, disappear, steady };
  struct MoveSettings {
    float acceleration;
    float start_velocity;
  };


  MazeFigure(const std::vector<glm::vec2>& maze,
             GLfloat height,
             glm::vec3 posi,
             glm::vec3 pos,
             GLfloat side_of_a_base);

  MazeFigure(const std::vector<glm::vec2>& maze,
             GLfloat height,
             glm::vec3 posi,
             glm::vec3 pos,
             GLfloat side_of_a_base,
             GLfloat cell_size);


  void Appear();
  void Disappear();
  bool IsMoving();
  void Act();
  /*! @brief Converts maze as Layout to a vector of mazes walls coordinates
  @param[in] maze Pointer to a maze being converted.
  @return Vector of coordinates of walls that maze is made of.
  */
  static std::vector<glm::vec2> Layout2VecOfWalls(const maze::Layout* maze);
  // static DynamicSolidFigure VectorToMapFigure(
  //     const std::vector<glm::vec2>& maze_walls,
  //     GLfloat height,
  //     glm::vec3 posi,
  //     glm::vec3 pos,
  //     GLfloat side_of_a_base);
  static DynamicSolidFigure VectorToMapFigure(
    const std::vector<glm::vec2>& maze_walls,
      const FigureVertexData &wall_model,
      const glm::vec3 &posi,
      const glm::vec3 &pos,
      const GLfloat &side_of_a_base
  );

  static FigureVertexData GetWallTemplate(const GLfloat &height, const GLfloat &side_of_a_base, const glm::vec3 &celling_color, const glm::vec2 &wall_shading);

 protected:
  GLfloat height_;
  glm::vec3 start_position_;
  glm::vec3 ang_vel_ = {0.0f, 0.0f, 0.0f};
  glm::vec3 lin_vel_ = {0.0f, 0.0f, 0.0f};
  MazeFigure::FigureState move_state_ = steady;
  MazeFigure::MoveSettings move_settings_ = {0.0f, 0.008f};
};
}
#endif


