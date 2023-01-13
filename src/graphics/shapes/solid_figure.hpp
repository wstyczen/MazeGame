#ifndef SOLID_FIGURE_HPP_
#define SOLID_FIGURE_HPP_

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "graphics/shaders/shader.hpp"
#include "graphics/shapes/data_buffers/EBO.hpp"
#include "graphics/shapes/data_buffers/VAO.hpp"


namespace graphics{

/*! @brief Describes a solid figure that can be displayed in a GLFWwindow.
 */
class SolidFigure {
 public:
  /*! @brief SolidFigure constructor
  * @param[in] vertices array including vertices that creates figure
  * each vertex is described by 6 floats: x, y, z, colorR, colorG, colorB
  * @param[in] vert_size size of vertices array
  * @param[in] indices array including indices that connects vertices into
  triangles
  * each triangle is created by connectring 3 vertices (3 indices needed)
  * @param[in] indi_size size of indices array
  * @param[in] posi position of a figure, {0.0f, 0.0f, 0.0f} by default.
  * @param[in] pos pose of a figure (Euler angle), {0.0f, 0.0f, 0.0f} by
  default.

  */
  SolidFigure(GLfloat* vertices,
              unsigned int vert_size,
              GLuint* indices,
              unsigned int indi_size,
              glm::vec3 posi = {0.0f, 0.0f, 0.0f},
              glm::vec3 pos = {0.0f, 0.0f, 0.0f});
  /*! @brief SolidFigure constructor
   * @param[in] vertices vector including vertices that creates figure
   * each vertex is described by 6 floats: x, y, z, colorR, colorG, colorB
   * @param[in] indices vector including indices that connects vertices into
   * triangles each triangle is created by connectring 3 vertices (3 indices
   * needed)
   * @param[in] posi position of a figure, {0.0f, 0.0f, 0.0f} by default.
   * @param[in] pos pose of a figure (Euler angle), {0.0f, 0.0f, 0.0f} by
   * default.
   */
  SolidFigure(std::vector<GLfloat> vertices,
              std::vector<GLuint> indices,
              const glm::vec3& posi,
              const glm::vec3& pos);
  /*! @brief SolidFigure copy constructor
   * @param[in] original object to copy.
   */
  SolidFigure(const SolidFigure& original);
  /*! @brief Displays figure at current GLFWwindow
   * @param[in] shader_id ID of a Shader object which will be used to display
   * figure
   * */
  void Show(const GLuint& shader_id) const;
  /*! @brief Returns current position of a figure
   */
  glm::vec3 GetPosition() const { return position_; }
  /*! @brief Returns current pose of a figure
   */
  glm::vec3 GetPose() const { return pose_; }
  /*! @brief Sets Projection Matrix.
  Especially needed when GLFWwindow isn't in shape of a square, because it's
  assumed to be.
  *
  * @param[in] proj_mat New projection matrix, the best way to get that matrix
  is using glm::perspective() method.
  */
  void SetProjMatrix(const glm::mat4& proj_mat) { mvp_.proj = proj_mat; }
  glm::mat4 GetProjMatrix() const {return mvp_.proj;}
  /*! @brief SolidFigure destructor
   */
  ~SolidFigure(){};

 protected:
  // Includes matrices that define picture of a figure
  struct MVP {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
  } mvp_;
  std::unique_ptr<VAO> vao_;
  std::unique_ptr<VBO> vbo_;
  std::unique_ptr<EBO> ebo_;
  // Current position of a figure
  glm::vec3 position_;
  // Current pose of a figure
  glm::vec3 pose_;
  /*! @brief Checks if vertices format is appropriate
   * @param[in] vertices vector including vertices that creates figure
   * @param[in] indices vector including indices that connects vertices into
   * triangles
   * @throws std::invalid_argument if any of following is true: @n
   * -color has negative value, @n
   * -lenght of vector isn't divisible by 6, @n
   * -any of indices reffers to vertex with index out of vector.
   */
  // static void CheckDataFormat(const std::vector<GLfloat>& vertices,
  //                             const std::vector<GLuint>& indices){};
};
}
#endif
