#include "graphics/shapes/dynamic_solid_figure.hpp"
#include "maze/layout.hpp"


class MazeFigure : public DynamicSolidFigure {
  public:
    enum FigureState {appear, steady};
    struct MoveSettings {
      float acceleration;
      float start_velocity;
    };

    MazeFigure(const maze::Layout* maze,
                        GLfloat height = 1.5f,
                        glm::vec3 posi = {0.0f, 0.0f, 0.0f},
                        glm::vec3 pos = {0.0f, 0.0f, 0.0f});
    void Appear();
    void Act();
  protected:
    GLfloat height_;
    glm::vec3 start_position_;
    glm::vec3 ang_vel_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 lin_vel_= {0.0f, 0.0f, 0.0f};
    MazeFigure::FigureState move_state_ = steady;
    MazeFigure::MoveSettings move_settings_ = {0.0f, 0.008f};
};
