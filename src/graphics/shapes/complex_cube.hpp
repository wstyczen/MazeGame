#include "graphics/shapes/dynamic_solid_figure.hpp"

#include "maze/utility.hpp"

class ComplexCube : public DynamicSolidFigure {
 public:
  enum MoveState { move_north, move_east, move_south, move_west, steady };
  struct MoveSettings {
    float acceleration;
    float start_velocity;
    float distance;
  };
  ComplexCube(const maze::Cell& starting_position);
  ComplexCube(GLfloat side = 1,
              glm::vec3 vertex_color = {0.0f, 0.0f, 0.0f},
              glm::vec3 inner_color = {1.0f, 1.0f, 1.0f},
              glm::vec3 posi = {0.0f, 0.0f, 0.0f},
              glm::vec3 pos = {0.0f, 0.0f, 0.0f});

  void MakeMove(ComplexCube::MoveState direction);

 protected:
  void Roll(const glm::vec2& turn_vec, GLfloat scale);
  void DiscretizatePosition();
  GLfloat size;
  glm::vec3 start_position;
  glm::vec3 ang_vel = {0.0f, 0.0f, 0.0f};
  glm::vec3 lin_vel = {0.0f, 0.0f, 0.0f};
  ComplexCube::MoveState move_state = steady;
  ComplexCube::MoveSettings move_settings = {0.2f, 2.0f, 1.0f};
  void Perform();
};
