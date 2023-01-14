#include "graphics/shapes/maze_figure.hpp"

#include <set>

namespace graphics {


std::vector<glm::vec2> MazeFigure::Layout2VecOfWalls(const maze::Layout* maze) {
  std::vector<glm::vec2> maze_walls;
  const auto& [map_height, map_width] = maze->size();
  for (uint16_t row = 0; row != map_height; ++row) {
    for (uint16_t column = 0; column != map_width; ++column) {
      if (maze->IsBlocked({row, column})) {
        maze_walls.push_back({column, map_height - 1 - row});
      }
    }
  }
  return maze_walls;
}

std::vector<glm::vec2> MazeFigure::Path2Vec(
    const maze::Layout& maze,
    const std::vector<maze::Cell> path) {
  const auto& [maze_height, maze_width] = maze.size();
  std::vector<glm::vec2> as_vec_2;
  const maze::Cell* previous = nullptr;
  for (const maze::Cell& cell : path) {
    if (!previous) {
      as_vec_2.push_back({cell.col, maze_height - 1 - cell.row});
      previous = &cell;
      continue;
    }
    maze::Edge edge = maze::Edge::FromTwoCells(*previous, cell);
    const maze::Cell halfway = *edge.To(1);
    as_vec_2.push_back({halfway.col, maze_height - 1 - halfway.row});
    as_vec_2.push_back({cell.col, maze_height - 1 - cell.row});
    previous = &cell;
  }
  // Remove duplicates
  auto comparison = [](glm::vec2 v1, glm::vec2 v2) {
    if (v1[0] < v2[0])
      return true;
    if (v1[0] == v2[0] && v1[1] < v2[1])
      return true;
    return false;
  };
  std::set<glm::vec2, decltype(comparison)> as_set(as_vec_2.begin(),
                                                   as_vec_2.end(), comparison);
  as_vec_2.assign(as_set.begin(), as_set.end());

  return as_vec_2;
}

DynamicSolidFigure MazeFigure::VectorToMapFigure(
    const std::vector<glm::vec2>& maze_walls,
    const FigureVertexData& wall_model,
    const glm::vec3& posi,
    const glm::vec3& pos,
    const GLfloat& cell_size) {
  const uint32_t vert_size = maze_walls.size() * wall_model.vertices.size();
  const uint32_t indi_size = maze_walls.size() * wall_model.indices.size();
  std::vector<GLfloat> vertices_data(vert_size);
  std::vector<GLuint> indices_data(indi_size);
  for (size_t wall = 0; wall != maze_walls.size(); ++wall) {
    for (size_t vertex = 0; vertex < wall_model.vertices.size(); vertex += 6) {
      vertices_data[wall * wall_model.vertices.size() + vertex] =
          wall_model.vertices[vertex] + cell_size * maze_walls[wall].x;
      vertices_data[wall * wall_model.vertices.size() + vertex + 1] =
          wall_model.vertices[vertex + 1] + cell_size * maze_walls[wall].y;
      vertices_data[wall * wall_model.vertices.size() + vertex + 2] =
          wall_model.vertices[vertex + 2];
      vertices_data[wall * wall_model.vertices.size() + vertex + 3] =
          wall_model.vertices[vertex + 3];
      vertices_data[wall * wall_model.vertices.size() + vertex + 4] =
          wall_model.vertices[vertex + 4];
      vertices_data[wall * wall_model.vertices.size() + vertex + 5] =
          wall_model.vertices[vertex + 5];
    }
    for (size_t index = 0; index != wall_model.indices.size(); ++index) {
      indices_data[wall * wall_model.indices.size() + index] =
          wall_model.indices[index] + wall * wall_model.vertices.size() / 6;
    }
  }
  DynamicSolidFigure figure(vertices_data, indices_data, posi, pos);
  return figure;
}

FigureVertexData MazeFigure::GetWallTemplate(const GLfloat& height,
                                             const GLfloat& side_of_a_base,
                                             const glm::vec3& celling_color,
                                             const glm::vec2& wall_shading) {
  const GLfloat half_of_side = side_of_a_base / 2.0f;
  const glm::vec3 upper_color = celling_color * wall_shading.x;
  const glm::vec3 lower_color = celling_color * wall_shading.y;

  FigureVertexData figure{};
  figure.vertices = {
      // celing
      -half_of_side,
      half_of_side,
      height - half_of_side,
      celling_color.x,
      celling_color.y,
      celling_color.z,
      half_of_side,
      half_of_side,
      height - half_of_side,
      celling_color.x,
      celling_color.y,
      celling_color.z,
      -half_of_side,
      -half_of_side,
      height - half_of_side,
      celling_color.x,
      celling_color.y,
      celling_color.z,
      half_of_side,
      -half_of_side,
      height - half_of_side,
      celling_color.x,
      celling_color.y,
      celling_color.z,
      // upper square
      -half_of_side,
      half_of_side,
      height - half_of_side,
      upper_color.x,
      upper_color.y,
      upper_color.z,
      half_of_side,
      half_of_side,
      height - half_of_side,
      upper_color.x,
      upper_color.y,
      upper_color.z,
      -half_of_side,
      -half_of_side,
      height - half_of_side,
      upper_color.x,
      upper_color.y,
      upper_color.z,
      half_of_side,
      -half_of_side,
      height - half_of_side,
      upper_color.x,
      upper_color.y,
      upper_color.z,
      // lower square
      -half_of_side,
      half_of_side,
      -half_of_side,
      lower_color.x,
      lower_color.y,
      lower_color.z,
      half_of_side,
      half_of_side,
      -half_of_side,
      lower_color.x,
      lower_color.y,
      lower_color.z,
      -half_of_side,
      -half_of_side,
      -half_of_side,
      lower_color.x,
      lower_color.y,
      lower_color.z,
      half_of_side,
      -half_of_side,
      -half_of_side,
      lower_color.x,
      lower_color.y,
      lower_color.z,
  };

  figure.indices = {
      // the way that vertices need to be connected to create rectangle

      0, 1,  2,  1,
      2, 3,

      6, 7,  10, 11,
      7, 10,

      6, 4,  10, 8,
      4, 10,

      4, 5,  8,  9,
      5, 8,

      7, 5,  11, 9,
      5, 11

  };
  return figure;
}


MazeFigure::MazeFigure(const std::vector<glm::vec2>& maze,
              const glm::vec3 &posi,
              const glm::vec3 &pos,
              const MazeSettings &maze_settings)
  : DynamicSolidFigure(VectorToMapFigure(maze,
      GetWallTemplate(maze_settings.height, maze_settings.side_of_a_base,
        maze_settings.color, maze_settings.shading),
      posi, pos, maze_settings.cell_size)), maze_settings_(maze_settings){
  start_position_ = posi;
}

MazeFigure::MazeFigure(const DynamicSolidFigure &maze_figure,
              const MazeSettings &maze_settings)
  : DynamicSolidFigure(maze_figure), maze_settings_(maze_settings){
  start_position_ = maze_figure.GetPosition();
}

void MazeFigure::Appear() {
  Move(glm::vec3({0.0f, 0.0f, -maze_settings_.height *(1+maze_settings_.cell_size)}));
  move_state_ = appear;
  lin_vel_.z = maze_settings_.move_settings.start_velocity;
}

void MazeFigure::Disappear() {
  move_state_ = disappear;
  lin_vel_.z = -maze_settings_.move_settings.start_velocity;
}

bool MazeFigure::IsMoving() {
  return move_state_ != steady;
}

void MazeFigure::Act() {
  if (move_state_ == appear) {
    if (position_.z <= start_position_.z) {
      lin_vel_.z += maze_settings_.move_settings.start_velocity ;
      Move(glm::vec3{0.0f, 0.0f, lin_vel_.z* maze_settings_.height});
    } else {
      move_state_ = steady;
      SetPosition(glm::vec3{position_.x, position_.y, start_position_.z});
    }
  }
  if (move_state_ == disappear) {
    if (position_.z >= start_position_.z -maze_settings_.height *(1+maze_settings_.cell_size)) {
      lin_vel_.z -= maze_settings_.move_settings.start_velocity;
      Move(glm::vec3{0.0f, 0.0f, lin_vel_.z* maze_settings_.height});
    } else {
      move_state_ = steady;
      SetPosition(glm::vec3{position_.x, position_.y, start_position_.z});
    }
  }
}

}  // namespace graphics
