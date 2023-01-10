#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<iterator>

// #include "graphics/shapes/data_buffers/EBO.hpp"
// #include "graphics/shapes/data_buffers/VBO.hpp"
// #include "graphics/shapes/data_buffers/VAO.hpp"
// #include "graphics/shapes/complex_cube.hpp"
// #include "graphics/shapes/maze_figure.hpp"
#include "graphics/shapes/game_window.hpp"

#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

const unsigned int width(1000), height(1000);
/*
int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
  int x_pos(0), y_pos(0), width2(0), height2(0);
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &x_pos, &y_pos, &width2, &height2);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "MazeGame", NULL, NULL);
  std::cout << x_pos << " " << y_pos << " " << mode->width << " " << mode->height;
	// Error check if the window fails to create
	if (window == NULL)
	{

		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
  glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport((mode->width - mode->height) / 2, -mode->height/15, mode->height, mode->height);
  Shader shaderProgram("default.vert", "default.frag");

  uint16_t maze_size = 10;
  const std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(maze::GeneratorType::RECURSIVE_BACKTRACKING);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get({maze_size, maze_size});

  ComplexCube cube({-maze_size+1, -maze_size+1, -maze_size*3.2}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
  MazeFigure maze_fig(MazeFigure::Layout2VecOfWalls(maze_layout.get()), 1.5f,{-maze_size, -maze_size, -maze_size*3.2});
  std::vector<DynamicSolidFigure*> figures = {&cube, &maze_fig};


	// Generates Shader object using shaders defualt.vert and default.frag
  glEnable(GL_DEPTH_TEST);
  double prevTime = glfwGetTime();
  maze_fig.Appear();
  shaderProgram.Activate();
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double crntTime = glfwGetTime();
    if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::FigureState::move_north);


    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::FigureState::move_south);

    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::FigureState::move_east);
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::FigureState::move_west);
    }

		if (crntTime - prevTime >= 0.02)
		{

      for(auto fig = figures.begin(); fig !=figures.end(); ++fig)
        (*fig)->Act();
      //figure.Turn(glm::vec3{0.0f, 0.5f, 0.0f});
      prevTime = crntTime;

		}
    //cube.Show(shaderProgram.GetId());
    maze_fig.Show(shaderProgram.GetId());
    cube.SolidFigure::Show(shaderProgram.GetId());


		// Tell OpenGL which Shader Program we want to use
		// Draw primitives, number of indices, datatype of indices, index of indices

		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Delete all the objects we've created
  shaderProgram.Delete();
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
*/
int main(){
  maze::CellSize maze_size = {10, 10};
  const std::unique_ptr<maze::Generator> generator =
  maze::GeneratorFactory::GetInstance()->GetGenerator(maze::GeneratorType::RECURSIVE_BACKTRACKING);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get(maze_size);
  GameWindow game(*maze_layout);
  game.LiftMaze();
  while(!game.WindowShouldClose()){
    // Move forward
    if (game.GetKeyState(GLFW_KEY_UP ) == GLFW_PRESS){
      game.MoveCube(ComplexCube::FigureState::move_north);
    }
    // Move backward
    if (game.GetKeyState(GLFW_KEY_DOWN ) == GLFW_PRESS){
      game.MoveCube(ComplexCube::FigureState::move_south);

    }
    // Strafe right
    if (game.GetKeyState(GLFW_KEY_RIGHT ) == GLFW_PRESS){
      game.MoveCube(ComplexCube::FigureState::move_east);
    }
    // Strafe left
    if (game.GetKeyState(GLFW_KEY_LEFT ) == GLFW_PRESS){
      game.MoveCube(ComplexCube::FigureState::move_west);
    }
    game.Show();
    game.Act();
  }

  return 0;
}
