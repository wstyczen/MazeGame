#include "graphics/shapes/dynamic_solid_figure.hpp"


class ComplexCube : public DynamicSolidFigure {
  public:
    enum MoveDirection {move_north, move_east, move_south, move_west, steady};
    struct MoveSettings {
      float acceleration;
      float start_velocity;
    };
    ComplexCube(const GLfloat side = 1,
                      const glm::vec3 vertex_color = {0.0f, 0.0f, 0.0f},
                      const glm::vec3 inner_color = {1.0f, 1.0f, 1.0f},
                      const glm::vec3 posi = {0.0f, 0.0f, 0.0f},
                      const glm::vec3 pos = {0.0f, 0.0f, 0.0f});
    void MakeMove(ComplexCube::MoveDirection direction);

  protected:
    void Roll(const glm::vec3 &turn_vec, GLfloat scale);
    GLfloat size;
    glm::vec3 start_position;
    glm::vec3 ang_vel = {0.0f, 0.0f, 0.0f};
    glm::vec3 lin_vel = {0.0f, 0.0f, 0.0f};
    ComplexCube::MoveDirection move_state = steady;
    ComplexCube::MoveSettings move_settings = {0.2f, 2.0f};
    void Perform();
};
