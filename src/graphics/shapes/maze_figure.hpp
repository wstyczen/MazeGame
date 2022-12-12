#include "graphics/shapes/dynamic_solid_figure.hpp"


class MazeFigure : public DynamicSolidFigure {
  public:
    enum MoveState {appear, steady};
    struct MoveSettings {
      float acceleration;
      float start_velocity;
    };

  MazeFigure(const std::vector<std::vector<char>> &maze,
                      glm::vec3 lower_color = {1.0f, 1.0f, 1.0f},
                      glm::vec3 upper_color = {0.0f, 0.0f, 0.0f},
                      GLfloat height = 1.0f,
                      glm::vec3 posi = {0.0f, 0.0f, 0.0f},
                      glm::vec3 pos = {0.0f, 0.0f, 0.0f});
  protected:
    glm::vec3 ang_vel = {0.0f, 0.0f, 0.0f};
    glm::vec3 lin_vel = {0.0f, 0.0f, 0.0f};
    MazeFigure::MoveState move_state = steady;
    MazeFigure::MoveSettings move_settings = {0.2f, 2.0f};
    void Perform(){std::cout << "zyje\n";};
};
