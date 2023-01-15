#include "graphics/shapes/dynamic_solid_figure.hpp"

namespace graphics{


void DynamicSolidFigure::Move(const glm::vec3& move_vec) {
  position_ += move_vec;
  mvp_.view = glm::translate(mvp_.view, move_vec);
}

void DynamicSolidFigure::Turn(const glm::vec3& turn_vec) {
  pose_+= turn_vec;
  mvp_.model = glm::rotate(mvp_.model, glm::radians(turn_vec.x),
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(turn_vec.y),
                           glm::vec3(0.0f, 1.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(turn_vec.z),
                           glm::vec3(0.0f, 0.0f, 1.0f));
}

void DynamicSolidFigure::SetPosition(const glm::vec3& new_position) {
  position_ = new_position;
  //Translate matrix describing {0.0f, 0.0f, 0.0f} position
  mvp_.view = glm::translate(glm::mat4(1.0f), position_);
}

void DynamicSolidFigure::SetPose(const glm::vec3& new_pose) {
  pose_ = new_pose;
  //model matrix is calculated from empty one describing {0.0f, 0.0f, 0.0f} pose.
  mvp_.model = glm::rotate(glm::mat4(1.0f), glm::radians(pose_.x),
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.y),
                           glm::vec3(0.0f, 1.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.z),
                           glm::vec3(0.0f, 0.0f, 1.0f));
}

}
