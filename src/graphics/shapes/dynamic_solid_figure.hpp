#ifndef DYNAMIC_SOLID_FIGURE_HPP_
#define DYNAMIC_SOLID_FIGURE_HPP_

#include "graphics/shapes/solid_figure.hpp"
namespace graphics{


class DynamicSolidFigure : public SolidFigure {
 public:
  using SolidFigure::SolidFigure;

  /**
   *!@brief Act() method in base class DynamicSolidFigure does nothing,
   created in order to offer consistent interface in inheriting classes
  */
  virtual void Act(){};
  /**
   *!@brief moves DynamicSolidFigure by a given vector, updates current position.
   @param[in] move_vec vector by which figure will be moved.
  */
  void Move(const glm::vec3& move_vec);
  /**
   *!@brief turns DynamicSolidFigure by a given vector, updates current pose.
   @param[in] turn_vec vector {x,y,z} by which figure will be rotated in the following order: \n
  -x over X-axis, \n
  -y over Y-axis, \n
  -z over Z-axis.
  */
  void Turn(const glm::vec3& turn_vec);
  /**
   *!@brief sets DynamicSolidFigure position.
   @param[in] new_position vector describing new position of figure.
  */
  void SetPosition(const glm::vec3& new_position);
  /**
   *!@brief sets DynamicSolidFigure pose.
   @param[in] new_pose vector describing new position of figure.
  */
  void SetPose(const glm::vec3& new_pose);
};
}
#endif
