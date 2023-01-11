#include "graphics/shapes/maze_figure.hpp"

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

std::vector<glm::vec2> Path2Vec2(const maze::Layout* maze,
                                 const std::vector<maze::Cell> path) {
  const auto& [maze_height, maze_width] = maze->size();
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
  return as_vec_2;
}

DynamicSolidFigure MazeFigure::VectorToMapFigureConvert(
    const std::vector<glm::vec2>& maze_walls,
    GLfloat height,
    glm::vec3 posi,
    glm::vec3 pos,
    GLfloat side_of_a_base) {
  // const GLfloat side_of_a_base = 1.0f;  // should be same as side of a cube
  //  Pawn!
  const GLfloat half_of_side = side_of_a_base / 2.0f;
  const glm::vec3 celing_color{0.8f, 0.8f, 0.8f};  // Color of celing in maze
  const glm::vec3 south_color{0.6f, 0.6f, 0.6f};   // Color of south walls in
                                                   // maze
  const glm::vec3 north_color{0.6f, 0.6f, 0.6f};   // Color of north walls in
                                                   // maze
  const glm::vec3 west_color{0.6f, 0.6f, 0.6f};  // Color of west walls in maze
  const glm::vec3 east_color{0.6f, 0.6f, 0.6f};  // Color of east walls in maze
  const std::vector<glm::vec3> pallette{
      celing_color, south_color, north_color, west_color,
      east_color};  // defines color for each cubes side
  const std::vector<float> shadings{
      1.0f, 0.1f, 0.1f, 0.1f,
      0.1f};  // descrbies the level of shading for each cubes side

  // const std::vector<glm::vec2> maze_walls = Layout2VecOfWalls(maze);//vector
  // of walls coordinates

  /*Describes order in which vertices need to be connected to create rectangle*/
  const std::vector<GLuint> indices_template{
      // the way that vertices need to be connected to create rectangle

      0, 1, 2, 1,
      2, 3

  };
  /*Describes vertices of a wall in a maze*/
  const std::vector<std::vector<float>> vertices_template{
      //               COORDINATES
      // IMPORTANT!
      // Base of Maze need to start below 0 level. Precisely at the same 'z' as
      // cube pawn (ComplexCube class),
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
      {half_of_side, half_of_side, -half_of_side}

  };
  /*Number of vertices in each maze wall*/
  const size_t maze_wall_verices_size = vertices_template.size() * 6;
  /*Number of indices that connects vertices in each maze wall*/
  const size_t maze_wall_indices_size = indices_template.size() * 5;
  const uint32_t vert_size = maze_walls.size() * maze_wall_verices_size;
  /*Size of vertex array is desribed by:
   -number of walls in maze,
   -number of vertices in each wall block (in this case 20, 4 for each side),
   -each vertex is described by 6 floats: coordinates and color.*/
  GLfloat vertices[vert_size];

  const uint32_t indi_size = maze_walls.size() * maze_wall_indices_size;
  /*Size of array is described by number of walls in maze.
  Each wall is made of 5 rectangle walls.
  To create rectangle there are 6 indices needed. Rectangle is made
  of two triangles, each triangle contains 3 vertices which are connected by
  indices.*/
  GLuint indices[indi_size];

  for (size_t wall = 0; wall != maze_walls.size(); ++wall) {
    // filling vertices array
    for (char n = 0; n != 5; ++n)       // for each rectangle in a wall
      for (char m = 0; m != 4; ++m) {   // for each vertex of a rectangle
        glm::vec3 color = pallette[n];  // load color for a current wall
        if (m >= 2)
          color =
              color *
              shadings[n];  // apply darker color only for vertices near floor
        vertices[wall * maze_wall_verices_size + n * 24 + m * 6] =
            roundf((maze_walls[wall].x * side_of_a_base +
                    vertices_template[n * 4 + m][0]) /
                   half_of_side) *
            half_of_side;
        vertices[wall * maze_wall_verices_size + n * 24 + m * 6 + 1] =
            roundf((maze_walls[wall].y * side_of_a_base +
                    vertices_template[n * 4 + m][1]) /
                   half_of_side) *
            half_of_side;
        vertices[wall * maze_wall_verices_size + n * 24 + m * 6 + 2] =
            roundf((vertices_template[n * 4 + m][2]) * 2) / 2;
        vertices[wall * maze_wall_verices_size + n * 24 + m * 6 + 3] = color.x;
        vertices[wall * maze_wall_verices_size + n * 24 + m * 6 + 4] = color.y;
        vertices[wall * maze_wall_verices_size + n * 24 + m * 6 + 5] = color.z;
      }
    // filling indices array
    for (char n = 0; n != 5; ++n)
      for (char m = 0; m != 6; ++m)
        indices[wall * 30 + n * 6 + m] =
            wall * 20 + n * 4 + indices_template[m];
  }
  DynamicSolidFigure maze_figure(vertices, sizeof(vertices), indices,
                                 sizeof(indices), posi, pos);
  return maze_figure;
}

MazeFigure::MazeFigure(const std::vector<glm::vec2>& maze,
                       GLfloat height,
                       glm::vec3 posi,
                       glm::vec3 pos)
    : DynamicSolidFigure(VectorToMapFigureConvert(maze, height, posi, pos)) {
  height_ = height;
  start_position_ = posi;
}

void MazeFigure::Appear() {
  Move(glm::vec3({0.0f, 0.0f, -height_ * 1.5f}));
  move_state_ = appear;
  lin_vel_.z = move_settings_.start_velocity;
}

void MazeFigure::Disappear() {
  move_state_ = disappear;
  lin_vel_.z = -move_settings_.start_velocity;
}

bool MazeFigure::IsMoving() {
  return move_state_ != steady;
}

void MazeFigure::Act() {
  if (move_state_ == appear) {
    if (position_.z <= start_position_.z) {
      lin_vel_.z += move_settings_.acceleration;
      Move(glm::vec3{0.0f, 0.0f, lin_vel_.z});
    } else {
      move_state_ = steady;
      SetPosition(glm::vec3{position_.x, position_.y, start_position_.z});
    }
  }
  if (move_state_ == disappear) {
    if (position_.z >= start_position_.z - height_ * 1.5f) {
      lin_vel_.z -= move_settings_.acceleration;
      Move(glm::vec3{0.0f, 0.0f, lin_vel_.z});
    } else {
      move_state_ = steady;
      SetPosition(glm::vec3{position_.x, position_.y, start_position_.z});
    }
  }
}
