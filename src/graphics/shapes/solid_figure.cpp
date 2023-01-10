#include "graphics/shapes/solid_figure.hpp"

SolidFigure::SolidFigure(GLfloat* vertices,
                         unsigned int vert_size,
                         GLuint* indices,
                         unsigned int indi_size,
                         glm::vec3 posi,
                         glm::vec3 pos) {
  position_ = posi;
  pose_ = pos;
  vao_ = std::unique_ptr<VAO>(new VAO());
  vao_->Bind();
  vbo_ = std::unique_ptr<VBO>(new VBO(vertices, vert_size));
  ebo_ = std::unique_ptr<EBO>(new EBO(indices, indi_size));
  vao_->LinkAttrib(*vbo_, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void*)(3 * sizeof(float)));
  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();
  mvp_.model = glm::mat4(1.0f);
  mvp_.proj = glm::mat4(1.0f);
  mvp_.view = glm::mat4(1.0f);
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.x),
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.y),
                           glm::vec3(0.0f, 1.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.z),
                           glm::vec3(0.0f, 0.0f, 1.0f));
  mvp_.view = glm::translate(mvp_.view, position_);
  mvp_.proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
}

SolidFigure::SolidFigure(const std::vector<GLfloat>& vertices,
                         const std::vector<GLuint>& indices,
                         const glm::vec3& posi,
                         const glm::vec3& pos) {
  GLfloat vertices_array[vertices.size()];
  std::copy(vertices.cbegin(), vertices.cend(), vertices_array);
  GLuint indices_array[indices.size()];
  std::copy(indices.cbegin(), indices.cend(), indices_array);

  position_ = posi;
  pose_ = pos;
  vao_ = std::unique_ptr<VAO>(new VAO());
  vao_->Bind();
  vbo_ = std::unique_ptr<VBO>(
      new VBO(vertices_array, vertices.size() * sizeof(GLfloat)));
  ebo_ = std::unique_ptr<EBO>(
      new EBO(indices_array, indices.size() * sizeof(GLuint)));
  vao_->LinkAttrib(*vbo_, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void*)(3 * sizeof(float)));
  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();

  mvp_.model = glm::mat4(1.0f);
  mvp_.proj = glm::mat4(1.0f);
  mvp_.view = glm::mat4(1.0f);
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.x),
                           glm::vec3(1.0f, 0.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.y),
                           glm::vec3(0.0f, 1.0f, 0.0f));
  mvp_.model = glm::rotate(mvp_.model, glm::radians(pose_.z),
                           glm::vec3(0.0f, 0.0f, 1.0f));
  mvp_.view = glm::translate(mvp_.view, position_);
  mvp_.proj =
      glm::perspective(glm::radians(45.0f), (float)(800 / 800), 0.1f, 100.0f);
}

SolidFigure::SolidFigure(const SolidFigure& original) {
  position_ = original.position_;
  pose_ = original.pose_;
  vao_ = std::unique_ptr<VAO>(new VAO(*original.vao_));
  vao_->Bind();
  vbo_ = std::unique_ptr<VBO>(new VBO(*original.vbo_));
  ebo_ = std::unique_ptr<EBO>(new EBO(*original.ebo_));
  vao_->LinkAttrib(*vbo_, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
  vao_->LinkAttrib(*vbo_, 1, 3, GL_FLOAT, 6 * sizeof(float),
                   (void*)(3 * sizeof(float)));
  vao_->Unbind();
  vbo_->Unbind();
  ebo_->Unbind();
  mvp_ = original.mvp_;
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
