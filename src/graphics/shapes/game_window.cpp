#include "graphics/shapes/game_window.hpp"


GameWindow::GameWindow(const maze::GeneratorType &generator_type, const uint16_t &maze_size){

  Init();
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  display_solution_ = std::make_pair(mode->width, mode->height);
  window_ = glfwCreateWindow(mode->width, mode->height, "MazeGame", NULL, NULL);
  glfwMakeContextCurrent(window_);
	gladLoadGL();
	glViewport((mode->width - mode->height) / 2, -mode->height/15, mode->height, mode->height);
  shader_ = std::make_unique<Shader>("default.vert", "default.frag");

  glm::vec3 maze_start_position = {-maze_size, -maze_size, -maze_size*maze_settings_.maze_scale};
  glm::vec3 cube_start_position = {-maze_size +1, -maze_size +1, -maze_size*maze_settings_.maze_scale};
  const std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(generator_type);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get({maze_size, maze_size});
  maze_ = std::make_unique<MazeFigure>(MazeFigure{MazeFigure::Layout2VecOfWalls(maze_layout.get()), maze_settings_.maze_height, maze_start_position});
  cube_ = std::make_unique<ComplexCube>(ComplexCube{cube_start_position, {0.0f, 0.0f, 0.0f}, cube_settings_.vertex_color, cube_settings_.inner_color});
  glEnable(GL_DEPTH_TEST);
  shader_->Activate();
  last_action_time = glfwGetTime();
}


void GameWindow::Act(){
  if(glfwGetTime() - last_action_time > 0.01){
    cube_->Act();
    maze_->Act();
    last_action_time = glfwGetTime();
  }
}
void GameWindow::Show(){
  glClearColor(Window_settings_.ClearColor[0],
              Window_settings_.ClearColor[1],
              Window_settings_.ClearColor[2],
              Window_settings_.ClearColor[3]);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  cube_->Show(shader_->GetId());
  maze_->Show(shader_->GetId());
  glfwSwapBuffers(window_);
  glfwPollEvents();
}

void GameWindow::LiftMaze(){
  maze_->Appear();
}
void GameWindow::MoveCube(const ComplexCube::FigureState &direction){
  cube_->MakeMove(direction);
}

GameWindow::~GameWindow(){
  shader_->Delete();
  glfwDestroyWindow(window_);
  glfwTerminate();
}

void GameWindow::Init(){
  glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);



}




