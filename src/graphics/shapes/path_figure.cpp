#include "graphics/shapes/path_figure.hpp"

namespace graphics{


FigureVertexData GetCellTemplate(const GLfloat &side_of_a_base, const glm::vec3 &color){
  FigureVertexData figure;
  GLfloat half_of_side = side_of_a_base / 2;
  figure.vertices = {
      -half_of_side, half_of_side, 0.0f, color.x, color.y, color.z,
      half_of_side, half_of_side, 0.0f, color.x, color.y, color.z,
      -half_of_side, -half_of_side, 0.0f, color.x, color.y, color.z,
      half_of_side, -half_of_side, 0.0f, color.x, color.y, color.z
  };
  figure.indices = {
      0, 1, 2,
      1, 2, 3
  };
  return figure;
}

PathFigure::PathFigure(const maze::Layout &maze,
            const glm::vec3 &posi,
             const glm::vec3 &pos,
             const PathSettings &settings){
  path_settings_ = settings;
  position_ = posi;
  pose_ = pos;
  auto path = Layout2Path(maze);
  for(auto &cell : path)
  path_cells_.push_back(std::make_unique<DynamicSolidFigure>(MazeFigure::VectorToMapFigure({cell}, GetCellTemplate(path_settings_.side_of_a_base, path_settings_.color), posi, pos, path_settings_.cell_size)));
}
void PathFigure::Show(const GLuint& shader_id) const{
  // for(auto &cell : path_cells_)
  //   cell->Show(shader_id);
}
void PathFigure::AddCell(const glm::vec2 &coordinates){
    glm::mat4 proj_mat = path_cells_.begin()->get()->GetProjMatrix();
    path_cells_.push_back(std::make_unique<DynamicSolidFigure>(MazeFigure::VectorToMapFigure({coordinates}, GetCellTemplate(path_settings_.side_of_a_base, path_settings_.color), position_, pose_, 0.0f)));
    path_cells_.rbegin()->get()->SetProjMatrix(proj_mat);

}
void PathFigure::UpdatePath(const glm::vec2 &coordinates){
  GLfloat intermediate_x = round((coordinates.x + path_cells_.rbegin()->get()->GetPosition().x) / 2  * path_settings_.cell_size) / path_settings_.cell_size;
  GLfloat intermediate_y = round((coordinates.y + path_cells_.rbegin()->get()->GetPosition().y) / 2  * path_settings_.cell_size) / path_settings_.cell_size;
  glm::vec2 intermediate_coordinate = {intermediate_x, intermediate_y};
  bool is_intermediate_already = false;
  bool is_final_already = false;
  for(auto &cell : path_cells_){
    if(cell->GetPosition().x == intermediate_x && cell->GetPosition().y == intermediate_y) is_intermediate_already = true;
    if(cell->GetPosition().x == coordinates.x&& cell->GetPosition().y == coordinates.y) is_intermediate_already = true;
  }
  glm::mat4 proj_mat = path_cells_.begin()->get()->GetProjMatrix();
  if(!is_final_already)AddCell(coordinates * path_settings_.cell_size);
  if(!is_intermediate_already) AddCell(intermediate_coordinate * path_settings_.cell_size);

}

void PathFigure::SetProjMatrix(const glm::mat4 &proj_mat){
  for(auto &cell : path_cells_)
    cell->SetProjMatrix(proj_mat);
}

std::vector<glm::vec2> PathFigure::Layout2Path(const maze::Layout &maze) {
  std::vector<glm::vec2> maze_walls;
  const auto& [map_height, map_width] = maze.size();
  for (uint16_t row = 0; row != map_height; ++row) {
    for (uint16_t column = 0; column != map_width; ++column) {
      if (!maze.IsBlocked({row, column})) {
        maze_walls.push_back({column, map_height - 1 - row});
      }
    }
  }
  return maze_walls;
}

}
