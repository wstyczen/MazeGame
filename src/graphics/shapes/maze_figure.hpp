#ifndef MAZE_FIGURE_HPP_
#define MAZE_FIGURE_HPP_
#include "graphics/shapes/dynamic_solid_figure.hpp"
#include "maze/layout.hpp"


class MazeFigure : public DynamicSolidFigure {
  public:
    enum FigureState {appear, steady};
    struct MoveSettings {
      float acceleration;
      float start_velocity;
    };

    MazeFigure(const std::vector<glm::vec2> &maze,
                        GLfloat height = 1.5f,
                        glm::vec3 posi = {0.0f, 0.0f, 0.0f},
                        glm::vec3 pos = {0.0f, 0.0f, 0.0f});
    void Appear();
    void Act();
  /*! @brief Converts maze as Layout to a vector of mazes walls coordinates
  @param[in] maze Pointer to a maze being converted.
  @return Vector of coordinates of walls that maze is made of.
  */
    static std::vector<glm::vec2> Layout2VecOfWalls(const maze::Layout* maze);
  protected:
    GLfloat height_;
    glm::vec3 start_position_;
    glm::vec3 ang_vel_ = {0.0f, 0.0f, 0.0f};
    glm::vec3 lin_vel_= {0.0f, 0.0f, 0.0f};
    MazeFigure::FigureState move_state_ = steady;
    MazeFigure::MoveSettings move_settings_ = {0.0f, 0.008f};
};
#endif
