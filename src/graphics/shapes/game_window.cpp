#include "graphics/shapes/game_window.hpp"

namespace {
glm::vec3 FromTopLeftCorner(const maze::Cell& position) {
  return glm::vec3{position.col, -position.row, 0.0f};
}
}  // namespace

namespace graphics {
GameWindow::GameWindow(const maze::Layout& maze,
                       const maze::Cell& cube_position,
                       const maze::Cell& goal) {
  InitGLFW();
  int xpos, ypos;
  glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos,
                         &display_solution_.width, &display_solution_.height);
  window_ = glfwCreateWindow(display_solution_.width, display_solution_.height,
                             "MazeGame", NULL, NULL);
  glfwMaximizeWindow(window_);
  glfwMakeContextCurrent(window_);
  gladLoadGL();
  glViewport((display_solution_.width - display_solution_.height) / 2, -ypos,
             display_solution_.height, display_solution_.height);
  shader_ = std::make_unique<Shader>();

  InitFigures(maze, cube_position, goal);
  glEnable(GL_DEPTH_TEST);
  shader_->Activate();
  last_action_time = glfwGetTime();
}

void GameWindow::Act() {
  if (glfwGetTime() - last_action_time > 0.01) {
    cube_->Act();
    maze_->Act();
    if (solving_path_)
      solving_path_->Act();
    last_action_time = glfwGetTime();
  }
}
void GameWindow::Show() const {
  glClearColor(Window_settings_.ClearColor[0], Window_settings_.ClearColor[1],
               Window_settings_.ClearColor[2], Window_settings_.ClearColor[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cube_->Show(shader_->GetId());
  maze_->Show(shader_->GetId());
  floor_->Show(shader_->GetId());
  if (solving_path_)
    solving_path_->Show(shader_->GetId());
  destinate_position_->Show(shader_->GetId());
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void GameWindow::WaitForMazeMoveToComplete() {
  while (maze_->IsMoving() && !WindowShouldClose()) {
    Show();
    Act();
  }
}
void GameWindow::LiftMaze() {
  maze_->Appear();
  WaitForMazeMoveToComplete();
}
void GameWindow::DropMaze() {
  maze_->Disappear();
  WaitForMazeMoveToComplete();
}

void GameWindow::ShowSolvingPath() {
  solving_path_->Appear();
  while (solving_path_->IsMoving() && !WindowShouldClose()) {
    solving_path_->Show(shader_->GetId());
    solving_path_->Act();
  }
}

bool GameWindow::MoveCube(const ComplexCube::FigureState& direction) {
  return cube_->MakeMove(direction);
}
bool GameWindow::IsCubeMoving() const {
  return cube_->IsMoving();
}
void GameWindow::WaitForCubeMoveToComplete() {
  while (cube_->IsMoving()) {
    Show();
    Act();
  }
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
glm::vec3 GameWindow::GetMazePosition(const maze::Layout& maze) const {
  const auto& [maze_height, maze_width] = maze.size();
  GLfloat maze_x_pos = -((maze_width - 1.0f) / 2.0f);
  GLfloat maze_y_pos = -((maze_height - 1.0f) / 2.0f);
  GLfloat maze_z_pos =
      -(GetMazeBiggerDimension(maze) * maze_settings_.maze_scale +
        maze_settings_.maze_height);

  return glm::vec3{maze_x_pos, maze_y_pos, maze_z_pos};
}

glm::vec3 GameWindow::GetAsVec(const maze::Layout& maze,
                               const maze::Cell& position) const {
  const auto& [maze_height, maze_width] = maze.size();
  glm::vec3 upper_left_corner =
      maze_position_ + glm::vec3{0.0f, maze_height - 1.0f, 0.0f};
  return upper_left_corner + FromTopLeftCorner(position);
}

GLfloat GameWindow::GetMazeBiggerDimension(const maze::Layout& maze) const {
  return maze.size().cols > maze.size().rows ? maze.size().cols
                                             : maze.size().rows;
}

SolidFigure GameWindow::CreateRectFromCoord(const GLfloat& height,
                                            const GLfloat& width,
                                            const glm::vec3& position,
                                            const glm::vec3& color) const {
  std::vector<GLfloat> vertices = {
      -width / 2.0f, -height / 2.0f, 0.0f, color.x, color.y, color.z,

      -width / 2.0f, height / 2.0f,  0.0f, color.x, color.y, color.z,

      width / 2.0f,  height / 2.0f,  0.0f, color.x, color.y, color.z,

      width / 2.0f,  -height / 2.0f, 0.0f, color.x, color.y, color.z,

  };
  std::vector<GLuint> indices = {0, 1, 2, 0, 3, 2};

  return SolidFigure(vertices, indices, position, glm::vec3{0.0f, 0.0f, 0.0f});
}

void GameWindow::FixRenderingRange(const maze::Layout& maze) {
  GLfloat maze_height = GetMazeBiggerDimension(maze);
  GLfloat rendering_range =
      sqrt((maze_position_.z * maze_position_.z + maze_height * maze_height));
  auto proj_matrix =
      glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, rendering_range);
  maze_->SetProjMatrix(proj_matrix);
  cube_->SetProjMatrix(proj_matrix);
  floor_->SetProjMatrix(proj_matrix);
  destination_->SetProjMatrix(proj_matrix);
}
void GameWindow::InitFigures(const maze::Layout& maze,
                             const maze::Cell& cube_position,
                             const maze::Cell& goal) {
  const auto& [maze_height, maze_width] = maze.size();
  maze_position_ = GetMazePosition(maze);
  glm::vec3 move_map_down(0.0f, maze_position_.z * maze_settings_.move_map_down,
                          0.0f);
  maze_position_ += move_map_down;

  glm::vec3 cube_start_position = GetAsVec(maze, cube_position);
  glm::vec3 maze_pos = {0.0f, 0.0f, 0.0f};
  maze_ = std::make_unique<MazeFigure>(
      MazeFigure::Layout2VecOfWalls(&maze), maze_settings_.maze_height,
      maze_position_, maze_pos, maze_settings_.wall_size,
      maze_settings_.cell_size, maze_settings_.maze_color,
      maze_settings_.shading);
  cube_ = std::make_unique<ComplexCube>(cube_start_position, maze_pos,
                                        cube_settings_.vertex_color,
                                        cube_settings_.inner_color);

  glm::vec3 floor_position =
      glm::vec3{0.0f, 0.0f, -0.5f + maze_position_.z} + move_map_down;
  floor_ = std::make_unique<SolidFigure>(CreateRectFromCoord(
      maze_height, maze_width, floor_position, maze_settings_.floor_color));

  glm::vec3 destination = GetAsVec(maze, goal);
  destination.z =
      floor_->GetPosition().z + 0.01;  // must be a little above floor
  destination_ = std::make_unique<SolidFigure>(CreateRectFromCoord(
      1.0f, 1.0f, destination, glm::vec3{1.0f, 0.4f, 0.0f}));
  // set propper projectrion matrix due to resize rendering space
  FixRenderingRange(maze);
}

void GameWindow::AddSolvingPath(const std::vector<glm::vec2>& path) {
  solving_path_ = std::make_unique<MazeFigure>(
      path, solving_path_settings_.height, maze_->GetPosition(),
      maze_->GetPose(), solving_path_settings_.size_of_a_cube,
      maze_settings_.cell_size, solving_path_settings_.color,
      solving_path_settings_.shading);
}
}  // namespace graphics
