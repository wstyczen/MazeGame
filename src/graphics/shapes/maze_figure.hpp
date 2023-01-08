#include "game/maze.hpp"
#include "graphics/shapes/dynamic_solid_figure.hpp"

class MazeFigure : public DynamicSolidFigure {
 public:
  enum MoveState { appear, steady };
  struct MoveSettings {
    float acceleration;
    float start_velocity;
  };

  MazeFigure(const maze::Layout* const layout,
             GLfloat height = 1.0f,
             glm::vec3 posi = {0.0f, 0.0f, 0.0f},
             glm::vec3 pos = {0.0f, 0.0f, 0.0f});
  void Appear();

 protected:
  GLfloat height_;
  glm::vec3 start_position_;
  glm::vec3 ang_vel_ = {0.0f, 0.0f, 0.0f};
  glm::vec3 lin_vel_ = {0.0f, 0.0f, 0.0f};
  MazeFigure::MoveState move_state_ = steady;
  MazeFigure::MoveSettings move_settings_ = {0.0f, 0.008f};
  void Perform();
};
