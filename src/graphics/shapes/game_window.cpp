#include "graphics/shapes/game_window.hpp"

GameWindow::GameWindow(const maze::Layout& maze) {
  InitGLFW();
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  display_solution_ = std::make_pair(mode->width, mode->height);
  window_ = glfwCreateWindow(mode->width, mode->height, "MazeGame", NULL, NULL);
  glfwMakeContextCurrent(window_);
  gladLoadGL();
  glViewport((mode->width - mode->height) / 2, -mode->height / 15, mode->height,
             mode->height);
  shader_ = std::make_unique<Shader>();

  InitFigures(maze);

  glEnable(GL_DEPTH_TEST);
  shader_->Activate();
  last_action_time = glfwGetTime();
}

void GameWindow::Act() {
  if (glfwGetTime() - last_action_time > 0.01) {
    cube_->Act();
    maze_->Act();
    last_action_time = glfwGetTime();
  }
}
void GameWindow::Show() {
  glClearColor(Window_settings_.ClearColor[0], Window_settings_.ClearColor[1],
               Window_settings_.ClearColor[2], Window_settings_.ClearColor[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cube_->Show(shader_->GetId());
  maze_->Show(shader_->GetId());
  floor_->Show(shader_->GetId());
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void GameWindow::LiftMaze() {
  maze_->Appear();
}
bool GameWindow::MoveCube(const ComplexCube::FigureState& direction) {
  return cube_->MakeMove(direction);
}

GameWindow::~GameWindow() {
  shader_->Delete();
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void GameWindow::InitGLFW() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
}

void GameWindow::InitFigures(const maze::Layout& maze) {
  uint16_t maze_width = (maze.size().cols - 1) / 2;
  uint16_t maze_height = (maze.size().rows - 1) / 2;
  GLfloat floor_width = maze_width;
  GLfloat floor_height = maze_height;
  glm::vec3 maze_start_position = {-maze_width, -maze_height,
                                   -maze_height * maze_settings_.maze_scale};
  glm::vec3 cube_start_position = {-maze_width + 1, -maze_height + 1,
                                   -maze_height * maze_settings_.maze_scale};
  maze_ = std::make_unique<MazeFigure>(
      MazeFigure{MazeFigure::Layout2VecOfWalls(&maze),
                 maze_settings_.maze_height, maze_start_position});
  cube_ =
      std::make_unique<ComplexCube>(ComplexCube{cube_start_position,
                                                {0.0f, 0.0f, 0.0f},
                                                cube_settings_.vertex_color,
                                                cube_settings_.inner_color});

  GLfloat wall_thickness = 1;
  std::vector<GLfloat> floor_vertices = {
      -(floor_width + wall_thickness / 2), -(floor_height + wall_thickness / 2),
      maze_start_position.z - 0.5f,        maze_settings_.floor_color.x,
      maze_settings_.floor_color.y,        maze_settings_.floor_color.z,

      -(floor_width + wall_thickness / 2), (floor_height + wall_thickness / 2),
      maze_start_position.z - 0.5f,        maze_settings_.floor_color.x,
      maze_settings_.floor_color.y,        maze_settings_.floor_color.z,

      (floor_width + wall_thickness / 2),  (floor_height + wall_thickness / 2),
      maze_start_position.z - 0.5f,        maze_settings_.floor_color.x,
      maze_settings_.floor_color.y,        maze_settings_.floor_color.z,

      (floor_width + wall_thickness / 2),  -(floor_height + wall_thickness / 2),
      maze_start_position.z - 0.5f,        maze_settings_.floor_color.x,
      maze_settings_.floor_color.y,        maze_settings_.floor_color.z,

  };
  std::vector<GLuint> floor_indices = {0, 1, 2, 0, 3, 2};
  floor_ = std::make_unique<SolidFigure>(floor_vertices, floor_indices,
                                         glm::vec3{0.0f, 0.0f, 0.0f},
                                         glm::vec3{0.0f, 0.0f, 0.0f});
}
