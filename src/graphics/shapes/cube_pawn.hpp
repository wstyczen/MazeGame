#include "graphics/shapes/dynamic_state_figure.hpp"

class CubePawn : public DynamicStateFigure {
  public:
    enum FigureState {move_north, move_east, move_south, move_west, steady};
    struct MoveSettings {
      float acceleration;
      float start_velocity;
      float distance;
    };
    // CubePawn(const GLfloat &side,
    //                   const glm::vec3 &posi,
    //                   const glm::vec3 &pos,
    //                   glm::vec3 vertex_color,
    //                   glm::vec3 inner_color);
    CubePawn(const DynamicSolidFigure &cube): DynamicStateFigure(cube), start_position(cube.GetPosition()), size_(1){figure_state_ = steady;};

    virtual void MakeMove(FigureState *state);
    void Act(){std::cout << "dupa";}
    // static DynamicSolidFigure MakeCubeFigure(GLfloat side,
    //                   const glm::vec3 &vertex_color,
    //                   const glm::vec3 &inner_color,
    //                   const glm::vec3 &posi,
    //                   const glm::vec3 &pos);

  protected:
    void Roll(const glm::vec2 &turn_vec, GLfloat scale){};
    void DiscretizatePosition(){};
    GLfloat size_;
    FigureState figure_state_;

    glm::vec3 start_position;
    glm::vec3 ang_vel = {0.0f, 0.0f, 0.0f};
    glm::vec3 lin_vel = {0.0f, 0.0f, 0.0f};
    MoveSettings move_settings = {0.2f, 2.0f, 1.0f};

};
