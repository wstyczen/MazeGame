#include "graphics/shapes/dynamic_solid_figure.hpp"

class ComplexCube : public DynamicSolidFigure {
 public:
  ComplexCube(const GLfloat side = 1,
                    const glm::vec3 vertex_color = {0.0f, 0.0f, 0.0f},
                    const glm::vec3 inner_color = {1.0f, 1.0f, 1.0f},
                    const glm::vec3 posi = {0.0f, 0.0f, 0.0f},
                    const glm::vec3 pos = {0.0f, 0.0f, 0.0f});
  void Roll(const glm::vec2 &turn_vec, GLfloat scale);
 protected:
  GLfloat size;
};
