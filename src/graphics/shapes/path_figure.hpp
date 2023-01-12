#include "graphics/shapes/solid_figure.hpp"

namespace graphics{

class PathFigure {
 public:
  PathFigure();
  void Show();
  void AddCell(const glm::vec2 &coordinates);
 private:
  std::vector<std::unique_ptr<SolidFigure>> path_cells_;

};

}
