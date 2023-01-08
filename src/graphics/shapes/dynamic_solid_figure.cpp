#include "graphics/shapes/dynamic_solid_figure.hpp"

void DynamicSolidFigure::move(const glm::vec3& move_vec) {
  glm::vec3 new_position = position + move_vec;
  setPosition(new_position);
}

void DynamicSolidFigure::turn(const glm::vec3& turn_vec) {
  glm::vec3 new_pose = pose + turn_vec;
  setPose(new_pose);
}

void DynamicSolidFigure::setPosition(const glm::vec3& new_position) {
  position = new_position;
  mvp.view = glm::mat4(1.0f);
  mvp.view = glm::translate(mvp.view, position);
}

void DynamicSolidFigure::setPose(const glm::vec3& new_pose) {
  pose = new_pose;
  pose = glm::vec3(pose.x - floor((pose.x / 360)) * 360.0f,
                   pose.y - floor((pose.y / 360)) * 360.0f,
                   pose.z - floor(pose.z / 360) * 360.0f);
  mvp.model = glm::mat4(1.0f);
  mvp.model =
      glm::rotate(mvp.model, glm::radians(pose.x), glm::vec3(1.0f, 0.0f, 0.0f));
  mvp.model =
      glm::rotate(mvp.model, glm::radians(pose.y), glm::vec3(0.0f, 1.0f, 0.0f));
  mvp.model =
      glm::rotate(mvp.model, glm::radians(pose.z), glm::vec3(0.0f, 0.0f, 1.0f));
}
