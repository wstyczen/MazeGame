#include "graphics/shapes/maze_figure.hpp"




DynamicSolidFigure VectorToMapFigureConvert(const std::vector<std::vector<char>> &maze, glm::vec3 lower_color, glm::vec3 upper_color, GLfloat height, glm::vec3 posi, glm::vec3 pos){
  std::vector<glm::vec2> maze_walls;
  size_t map_height = maze.size();
  size_t map_width = maze[0].size();
  for(size_t row = 0; row != map_height; ++row){
    if(maze[row].size() != map_width){
      //exception
      std::cout << "Wrong map Format \n";
    }
    for(size_t column = 0; column != map_width; ++column){
      if(maze[row][column] == 'w')
        maze_walls.push_back({column, row});

    }
  }


  std::vector<std::vector<float>> vertices_coordinates{
    {-0.5f, -0.5f, -0.5f},         //0
    {-0.5f, -0.5f, height - 0.5f}, //1
    { 0.5f, -0.5f, height - 0.5f}, //2
    { 0.5f, -0.5f, -0.5f},         //3
    {-0.5f,  0.5f, -0.5f}, //4
    {-0.5f,  0.5f, height - 0.5f}, //5
    { 0.5f,  0.5f, height - 0.5f}, //6
    { 0.5f,  0.5f, -0.5f}  //7
  };
  std::vector<GLuint> indices_coordinates{
    0, 1, 2, 0, 2, 3, //front
    4, 5, 6, 4, 6, 7, //back
    0, 4, 5, 0, 5, 1, //left
    3, 7, 6, 3, 6, 2, //right
    1, 2, 6, 1, 6, 5, //upper
    0, 7, 3, 0, 7, 4  //lower
  };


  std::vector<GLuint> indices_coordinates2{

    0, 1,  8,  1, 2,  8,  2,
    3, 8,  3,  0, 8,

    0, 1,  9,  1, 5,  9,  5,
    4, 9,  4,  0, 9,

    5, 6,  10, 6, 7,  10, 7,
    4, 10, 4,  5, 10,

    2, 6,  11, 6, 7,  11, 7,
    3, 11, 3,  2, 11,

    1, 5,  12, 5, 6,  12, 6,
    2, 12, 2,  1, 12,

    0, 4,  13, 4, 7,  13, 7,
    3, 13, 3,  0, 13

  };

  std::vector<std::vector<float>> vertices_coordinates2{
    //               COORDINATES
    {-0.5f, -0.5f, height - 0.5f},
    {-0.5f, 0.5f,  height - 0.5f},
    {0.5f,  0.5f,  height - 0.5f},
    {0.5f,  -0.5f, height - 0.5f},
    {-0.5f, -0.5f, -0.5f},
    {-0.5f, 0.5f,  -0.5f},
    {0.5f,  0.5f,  -0.5f},
    {0.5f,  -0.5f, -0.5f},
    {0.0f,  0.0f,  0.3f}, //inner
    {-0.3f, 0.0f,  0.0f},
    {0.0f,  0.0f,  -0.3f},
    {0.3f,  0.0f,  0.0f},
    {0.0f,  0.3f,  0.0f},
    {0.0f,  -0.3f, 0.0f}
  };

  GLfloat vertices[maze_walls.size() * 8 * 6];
  GLuint indices[maze_walls.size() * 36];
  for(size_t wall = 0; wall != maze_walls.size(); ++wall){
    for(char n = 0; n != 8; ++n){
      glm::vec3 color = upper_color;
      if(vertices_coordinates[n][2] == -0.5) color = lower_color;
      vertices[wall * 48 + n * 6] = maze_walls[wall].x + vertices_coordinates[n][0];
      vertices[wall * 48 + n * 6 + 1] = maze_walls[wall].y + vertices_coordinates[n][1];
      vertices[wall * 48 + n * 6 + 2] = vertices_coordinates[n][2];
      vertices[wall * 48 + n * 6 + 3] = color.x;
      vertices[wall * 48 + n * 6 + 4] = color.y;
      vertices[wall * 48 + n * 6 + 5] = color.z;
    }
    for(char m = 0; m != 36; ++m ){
      indices[wall * 36 + m] = indices_coordinates[m] + wall * 8;
    }
  }
  std::cout << " SIZE: " << maze_walls.size() << " " << (sizeof(vertices) / 4)<< " " << (sizeof(indices) / 4)<< std::endl;
  for(int i = 0; i < maze_walls.size(); ++i){
    for(int j = 0; j < 6; ++j){
      for(int k = 0; k < 6; ++k ){
        std::cout << indices[i*36 + j*6 + k] << " ";
      }
      std::cout << std::endl;
    }

      std::cout << std::endl;
  }
  for(int i = 0; i < maze_walls.size(); ++i){
    for(int j = 0; j < 8; ++j){
      std::cout << vertices[i * 8 + j * 6] << " " << vertices[j * 8 + j*6 + 1 ] << " " << vertices[i * 8 + j*6 + 2];
      std::cout << std::endl;
    }

      std::cout << std::endl;
  }

  DynamicSolidFigure maze_figure(vertices, sizeof(vertices), indices, sizeof(indices),  posi, pos);
  return maze_figure;
}

MazeFigure::MazeFigure(const std::vector<std::vector<char>> &maze, glm::vec3 lower_color, glm::vec3 upper_color, GLfloat height, glm::vec3 posi, glm::vec3 pos)
    : DynamicSolidFigure(VectorToMapFigureConvert(maze, lower_color, upper_color, height, posi, pos)){



}
