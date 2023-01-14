#include "graphics/shapes/maze_figure.hpp"

namespace graphics{

FigureVertexData GetCellTemplate(const GLfloat &side_of_a_base, const glm::vec3 &color);


class PathFigure {
 public:
  struct PathSettings{
    GLfloat cell_size;
    GLfloat side_of_a_base;
    glm::vec3 color;
  };
  PathFigure(const maze::Layout& maze,
            const glm::vec3 &posi,
             const glm::vec3 &pos,
             const PathSettings &settings);
  void Show(const GLuint& shader_id) const;
  void AddCell(const glm::vec2 &coordinates);
  void UpdatePath(const glm::vec2 &coordinates);
  void SetProjMatrix(const glm::mat4 &proj_mat);
  static std::vector<glm::vec2> Layout2Path(const maze::Layout &maze);

 private:
  glm::vec3 position_;
  glm::vec3 pose_;
  PathSettings path_settings_;
  std::vector<std::unique_ptr<DynamicSolidFigure>> path_cells_ = {};
};

}
