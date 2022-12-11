#include "graphics/shapes/solid_figure.hpp"



class DynamicSolidFigure : public SolidFigure {
  public:
    void Act(){Perform();}
    using SolidFigure::SolidFigure;
    void move(const glm::vec3 &move_vec);
    void turn(const glm::vec3 &turn_vec);
    void setPosition(const glm::vec3 &new_position);
    void setPose(const glm::vec3 &new_pose);
  protected:
    virtual void Perform() = 0;
};
