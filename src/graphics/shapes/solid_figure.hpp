#ifndef SOLID_FIGURE_HPP_
#define SOLID_FIGURE_HPP_

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "graphics/shaders/shader.hpp"
#include "graphics/shapes/data_buffers/EBO.hpp"
#include "graphics/shapes/data_buffers/VAO.hpp"

class SolidFigure {
 public:
  SolidFigure(GLfloat* vertices,
              unsigned int vert_size,
              GLuint* indices,
              unsigned int indi_size,
              glm::vec3 posi = {0.0f, 0.0f, 0.0f},
              glm::vec3 pos = {0.0f, 0.0f, 0.0f});

  SolidFigure(const SolidFigure& original);
  void show(const GLuint& sharer_id);
  glm::vec3 getPosition() { return position; };
  glm::vec3 getPose() { return pose; };
  ~SolidFigure(){};

 protected:
  struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
  } mvp;
  std::unique_ptr<VAO> vao;
  std::unique_ptr<VBO> vbo;
  std::unique_ptr<EBO> ebo;
  glm::vec3 position;
  glm::vec3 pose;
};

#endif
