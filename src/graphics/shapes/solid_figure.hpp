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

/*! @brief Describes a solid figure that can be displayed in a GLFWwindow.
 */
class SolidFigure {
 public:
  SolidFigure(GLfloat* vertices,
              unsigned int vert_size,
              GLuint* indices,
              unsigned int indi_size,
              glm::vec3 posi = {0.0f, 0.0f, 0.0f},
              glm::vec3 pos = {0.0f, 0.0f, 0.0f});

  SolidFigure(const std::vector<GLfloat>& vertices,
              const std::vector<GLuint>& indices,
              const glm::vec3& posi,
              const glm::vec3& pos);

  SolidFigure(const SolidFigure& original);
  void Show(const GLuint& shader_id) const;
  glm::vec3 GetPosition() const { return position_; }
  glm::vec3 GetPose() const { return pose_; }
  void SetProjMatrix(const glm::mat4& proj_mat) { mvp_.proj = proj_mat; }
  ~SolidFigure(){};

 protected:
  struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
  } mvp_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  std::unique_ptr<EBO> ebo_;
  glm::vec3 position_;
  glm::vec3 pose_;

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
