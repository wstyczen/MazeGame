#ifndef DYNAMIC_SOLID_FIGURE_HPP_
#define DYNAMIC_SOLID_FIGURE_HPP_

#include "graphics/shapes/solid_figure.hpp"

class DynamicSolidFigure : public SolidFigure {
 public:
  using SolidFigure::SolidFigure;
  void move(const glm::vec3& move_vec);
  void turn(const glm::vec3& turn_vec);
  void setPosition(const glm::vec3& new_position);
  void Act() { Perform(); }
  void setPose(const glm::vec3& new_pose);

 protected:
  virtual void Perform(){};
};

#endif
