#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<iterator>

#include "graphics/hellocmake.h"
#include "graphics/shapes/data_buffers/EBO.hpp"
#include "graphics/shapes/data_buffers/VBO.hpp"
#include "graphics/shapes/data_buffers/VAO.hpp"
#include "graphics/shapes/complex_cube.hpp"
#include "graphics/shapes/maze_figure.hpp"

#include "maze/generators/generator.hpp"
#include "maze/generators/generator_factory.hpp"
#include "maze/layout.hpp"
#include "maze/solvers/solver.hpp"
#include "maze/solvers/solver_factory.hpp"

const unsigned int width(1000), height(1000);

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
	GLFWwindow* window = glfwCreateWindow(width, height, "MazeGame", NULL, NULL);
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
	glViewport(0, 0, width, height);

  const std::unique_ptr<maze::Generator> generator =
      maze::GeneratorFactory::GetInstance()->GetGenerator(maze::GeneratorType::RECURSIVE_BACKTRACKING);
  const std::unique_ptr<maze::Layout> maze_layout = generator->Get({15, 15});

  // std::vector<std::vector<char>> maze = {
  //   {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
  //   {'w', ' ', 'w', ' ', 'w', 'w', ' ', ' ', 'w'},
  //   {'w', ' ', 'w', ' ', ' ', 'w', 'w', ' ', 'w'},
  //   {'w', ' ', 'w', 'w', ' ', 'w', 'w', ' ', 'w'},
  //   {'w', ' ', ' ', 'w', ' ', 'w', 'w', ' ', 'w'},
  //   {'w', ' ', 'w', 'w', ' ', 'w', 'w', ' ', 'w'},
  //   {'w', ' ', 'w', ' ', ' ', ' ', ' ', ' ', 'w'},
  //   {'w', ' ', ' ', ' ', 'w', 'w', 'w', 'w', 'w'},
  //   {'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'}
  // };

  Shader shaderProgram("default.vert", "default.frag");
  ComplexCube cube(1, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {-5.0f, 2.0f, -40.0f}, {0.0f, 0.0f, 0.0f});
  MazeFigure maze_fig(maze_layout.get(), 1.5f,{-15.0f, -15.0f, -40.0f});
	// Generates Shader object using shaders defualt.vert and default.frag
  glEnable(GL_DEPTH_TEST);
  double prevTime = glfwGetTime();
  maze_fig.Appear();
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram.Activate();
    //glm::vec3 angle(0.01f, 0.0f, 0.0f);
    double crntTime = glfwGetTime();
    //cube.MoveAnimation(ComplexCube::MoveDirection::north);
    // if(crntTime - floor(crntTime / 5) * 5.0f < 0.05f){
    //     cube.MakeMove(ComplexCube::MoveDirection::move_east);
    // }
    if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::MoveState::move_north);
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::MoveState::move_south);
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::MoveState::move_east);
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS){
      cube.MakeMove(ComplexCube::MoveState::move_west);
    }

		if (crntTime - prevTime >= 1/60)
		{
      //angle += -0.01f;
			//figure.turn(glm::vec3{1.0f, 1.0f, 1.0f});
      //cube.Roll({-1.0f, 0.0f}, 1.0f);
      cube.Act();
      maze_fig.Act();
      //maze_fig.turn({1.1f, 1.2f, 1.1f});
      //std::cout << cube.getPosition().z << std::endl;
      //std::cout << c.x << " "<< c.y << " " << c.z << "GIT\n";
      //std::cout << cube.getPose().x <<" " <<floor(cube.getPose().x / 90) * 90 << std::endl;
      //std::cout << crntTime << std::endl;
      maze_fig.show(shaderProgram.GetId());
      cube.show(shaderProgram.GetId());
      prevTime = crntTime;

		}

      //figure.show(shaderProgram.GetId());
      //figure2.show(shaderProgram.GetId());


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
