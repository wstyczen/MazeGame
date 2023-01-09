#include "graphics/shapes/dynamic_solid_figure.hpp"


class ComplexCube : public DynamicSolidFigure {
  public:
    enum FigureState {move_north, move_east, move_south, move_west, steady};
    struct MoveSettings {
      float acceleration;
      float start_velocity;
      int distance;
    };
    ComplexCube(const glm::vec3 &posi,
                const glm::vec3 &pos,
                const glm::vec3 &vertex_color,
                const glm::vec3 &inner_color);
    ComplexCube(const DynamicSolidFigure &cube) :
                DynamicSolidFigure(cube),
                start_position(cube.GetPosition()){};
    void MakeMove(ComplexCube::FigureState direction);
    void Act();
    static DynamicSolidFigure MakeCubeFigure(
                      const GLfloat &side,
                      const glm::vec3 &posi,
                      const glm::vec3 &pos,
                      const glm::vec3 &vertex_color,
                      const glm::vec3 &inner_color);

  private:
    void Roll(const glm::vec2 &turn_vec, GLfloat scale);
    void DiscretizatePosition();
    static constexpr GLfloat size_ = 1;
    const glm::vec3 start_position;
    glm::vec3 ang_vel = {0.0f, 0.0f, 0.0f};
    glm::vec3 lin_vel = {0.0f, 0.0f, 0.0f};
    ComplexCube::FigureState move_state = steady;
    const ComplexCube::MoveSettings move_settings = {0.2f, 2.0f, 2};

};
