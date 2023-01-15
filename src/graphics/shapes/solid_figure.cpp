#include "graphics/shapes/solid_figure.hpp"

namespace graphics{


SolidFigure::SolidFigure(const std::vector<GLfloat> &vertices,
                         const std::vector<GLuint> &indices,
                         const glm::vec3& posi,
                         const glm::vec3& pos) {
  CheckVerticesData(vertices, indices);
  const size_t vert_size = vertices.size();
  const size_t indi_size = indices.size();
  GLfloat vertices_array[vert_size];
  std::copy(vertices.cbegin(), vertices.cend(), vertices_array);
  GLuint indices_array[indi_size];
  std::copy(indices.cbegin(), indices.cend(), indices_array);

  position_ = posi;
  pose_ = pos;
  vao_ = std::make_shared<VAO>();
  vao_->Bind();
  vbo_ = std::shared_ptr<VBO>(new VBO(vertices_array, vertices.size() * sizeof(GLfloat))); //WHY CANT I USE std::make_shared here?
  ebo_ = std::shared_ptr<EBO>(new EBO(indices_array, indices.size() * sizeof(GLuint)));
  vao_->LinkAttrib(*vbo_, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void*)(3 * sizeof(float)));
  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();

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
