#include "graphics/shapes/maze_figure.hpp"

DynamicSolidFigure VectorToMapFigureConvert(const maze::Layout* const layout,
                                            GLfloat height,
                                            glm::vec3 posi,
                                            glm::vec3 pos) {
  GLfloat side_of_a_base = 1.0f;  // should be same as side of a cube Pawn!
  GLfloat half_of_side = side_of_a_base / 2.0f;
  glm::vec3 celing_color{0.8f, 0.8f,
                         0.8f};  // Colors for each side of single maze block
  glm::vec3 south_color{0.6f, 0.6f, 0.6f};
  glm::vec3 north_color{0.6f, 0.6f, 0.6f};
  glm::vec3 west_color{0.6f, 0.6f, 0.6f};
  glm::vec3 east_color{0.6f, 0.6f, 0.6f};
  std::vector<glm::vec3> pallette{celing_color, south_color, north_color,
                                  west_color, east_color};
  std::vector<float> shadings{
      1.0f, 0.1f, 0.1f, 0.1f,
      0.1f};  // describes the level of shading for each side

  std::vector<glm::vec2> maze_walls;
  const auto& [map_height, map_width] = layout->size();
  for (uint16_t row = 0; row != map_height; ++row) {
    for (uint16_t column = 0; column != map_width; ++column) {
      if (layout->IsBlocked({row, column}))
        maze_walls.push_back({column, row});
    }
  }

  std::vector<GLuint> indices_coordinates2{
      0, 1, 2,
      1, 2, 3  // the way that vertices need to be connected to create rectangle
  };

  std::vector<std::vector<float>> vertices_coordinates2{
      //               COORDINATES
      // IMPORTANT!
      // Base of Maze need to start below 0 level. Precisely at the same 'z' as
      // cube,
      // thats why whole figure is moved half_of_side down.

      // celing
      {-half_of_side, half_of_side, height - half_of_side},
      {half_of_side, half_of_side, height - half_of_side},
      {-half_of_side, -half_of_side, height - half_of_side},
      {half_of_side, -half_of_side, height - half_of_side},
      // south
      {-half_of_side, -half_of_side, height - half_of_side},
      {half_of_side, -half_of_side, height - half_of_side},
      {-half_of_side, -half_of_side, -half_of_side},
      {half_of_side, -half_of_side, -half_of_side},
      // north
      {-half_of_side, half_of_side, height - half_of_side},
      {half_of_side, half_of_side, height - half_of_side},
      {-half_of_side, half_of_side, -half_of_side},
      {half_of_side, half_of_side, -half_of_side},
      // west
      {-half_of_side, -half_of_side, height - half_of_side},
      {-half_of_side, half_of_side, height - half_of_side},
      {-half_of_side, -half_of_side, -half_of_side},
      {-half_of_side, half_of_side, -half_of_side},
      // east
      {half_of_side, -half_of_side, height - half_of_side},
      {half_of_side, half_of_side, height - half_of_side},
      {half_of_side, -half_of_side, -half_of_side},
      {half_of_side, half_of_side, -half_of_side}};

  GLfloat vertices[maze_walls.size() * 20 * 6];
  GLuint indices[maze_walls.size() * 30];
  /*each block of maze is made of 5 rectangles,
 each rectangle has 4 vertices,
 each vertex is described by 6 floats.
 Every rectangle need is made of two triangles -> 3 indices each*/
  for (size_t wall = 0; wall != maze_walls.size(); ++wall) {
    // filling vertices array
    for (char n = 0; n != 5; ++n)
      for (char m = 0; m != 4; ++m) {
        glm::vec3 color = pallette[n];
        if (m >= 2)
          color = color * shadings[n];
        vertices[wall * 120 + n * 24 + m * 6] =
            roundf((maze_walls[wall].x + vertices_coordinates2[n * 4 + m][0]) *
                   2) /
            2;
        vertices[wall * 120 + n * 24 + m * 6 + 1] =
            roundf((maze_walls[wall].y + vertices_coordinates2[n * 4 + m][1]) *
                   2) /
            2;
        vertices[wall * 120 + n * 24 + m * 6 + 2] =
            roundf((vertices_coordinates2[n * 4 + m][2]) * 2) / 2;
        vertices[wall * 120 + n * 24 + m * 6 + 3] = color.x;
        vertices[wall * 120 + n * 24 + m * 6 + 4] = color.y;
        vertices[wall * 120 + n * 24 + m * 6 + 5] = color.z;
      }
    // filling indices array
    for (char n = 0; n != 5; ++n)
      for (char m = 0; m != 6; ++m)
        indices[wall * 30 + n * 6 + m] =
            wall * 20 + n * 4 + indices_coordinates2[m];
  }
  DynamicSolidFigure maze_figure(vertices, sizeof(vertices), indices,
                                 sizeof(indices), posi, pos);
  return maze_figure;
}

MazeFigure::MazeFigure(const maze::Layout* const layout,
                       GLfloat height,
                       glm::vec3 posi,
                       glm::vec3 pos)
    : DynamicSolidFigure(VectorToMapFigureConvert(layout, height, posi, pos)) {
  height_ = height;
  start_position_ = posi;
}

void MazeFigure::Appear() {
  move(glm::vec3({0.0f, 0.0f, -height_}));
  move_state_ = appear;
  lin_vel_.z = move_settings_.start_velocity;
}

void MazeFigure::Perform() {
  if (move_state_ == appear) {
    if (position.z <= start_position_.z) {
      lin_vel_.z += move_settings_.acceleration;
      move(glm::vec3{0.0f, 0.0f, lin_vel_.z});
    } else {
      move_state_ = steady;
      setPosition(glm::vec3{position.x, position.y, start_position_.z});
    }
  }
}
