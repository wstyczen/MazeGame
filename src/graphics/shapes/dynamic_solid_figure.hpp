#ifndef DYNAMIC_SOLID_FIGURE_HPP_
#define DYNAMIC_SOLID_FIGURE_HPP_

#include "graphics/shapes/solid_figure.hpp"
namespace graphics{


class DynamicSolidFigure : public SolidFigure {
 public:
  using SolidFigure::SolidFigure;

  virtual void Act(){};

 protected:
  void Move(const glm::vec3& move_vec);
  void Turn(const glm::vec3& turn_vec);
  void SetPosition(const glm::vec3& new_position);
  void SetPose(const glm::vec3& new_pose);
};
}
#endif
