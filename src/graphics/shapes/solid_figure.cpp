#include "graphics/shapes/solid_figure.hpp"

namespace graphics{


SolidFigure::SolidFigure(const std::vector<GLfloat> &vertices,
                         const std::vector<GLuint> &indices,
                         const glm::vec3& position,
                         const glm::vec3& pose) {
  //check if vertices and indices data is correct
  CheckVerticesData(vertices, indices);
  position_ = position;
  pose_ = pose;
  //Create VAO, VBO, EBO objects
  vao_ = std::make_shared<VAO>();
  vao_->Bind();
  vbo_ = std::make_shared<VBO>(vertices.data(), vertices.size() * sizeof(GLfloat));
  ebo_ = std::make_shared<EBO>(indices.data(), indices.size() * sizeof(GLuint));
  vao_->LinkAttrib(*vbo_, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void*)(3 * sizeof(float)));
  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();

  //Sets MVP matrices based on given position and pose
  mvp_.model = glm::rotate(glm::mat4(1.0f), glm::radians(pose_.x),
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.y),
                           glm::vec3(0.0f, 1.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.z),
                           glm::vec3(0.0f, 0.0f, 1.0f));
  mvp_.view = glm::translate(glm::mat4(1.0f), position_);
  mvp_.proj =
      glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}

void SolidFigure::Show(const GLuint& shader_id) const {
  int modelLoc = glGetUniformLocation(shader_id, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvp_.model));
  int viewLoc = glGetUniformLocation(shader_id, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mvp_.view));
  int projLoc = glGetUniformLocation(shader_id, "proj");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mvp_.proj));
  vao_->Bind();
  glDrawElements(GL_TRIANGLES, ebo_->GetCount(), GL_UNSIGNED_INT, 0);
}

void SolidFigure::CheckVerticesData(const std::vector<GLfloat> &vertices,
                      const std::vector<GLuint> &indices){

  if(vertices.size() % 6 || indices.size() % 3)throw std::invalid_argument("Invalid argument: array size must be multiple of: vertex-6, index-3");
  for(auto &index : indices)if(index > vertices.size() / 6)throw std::invalid_argument("Invalid argument: each index must refer to a vertex");
}

}
