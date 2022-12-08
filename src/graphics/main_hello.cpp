#include "graphics/hellocmake.h"
#include "graphics/shapes/data_buffers/EBO.hpp"
#include "graphics/shapes/data_buffers/VBO.hpp"
#include "graphics/shapes/data_buffers/VAO.hpp"
#include "graphics/shapes/solid_figure.hpp"
#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<iterator>


const unsigned int width(1000), height(1000);

// Vertices coordinates
GLfloat vertices[] =
{ //               COORDINATES
	-0.5f,  -0.5f, 0.5f,     0.8f, 0.3f,  0.02f,	// Lower left corner
	-0.5f,  0.5f, 0.5f,     0.8f, 0.3f,  0.02f,	// Upper left corner
	 0.5f,  0.5f, 0.5f,     0.8f, 0.3f,  0.02f,	// Upper right corner
	 0.5f,  -0.5f, 0.5f,     0.8f, 0.3f,  0.02f,	// Lower right corner

	-0.5f,  -0.5f, -0.5f,    0.8f, 0.3f,  0.02f,	// Lower left corner
	-0.5f,  0.5f, -0.5f,    0.8f, 0.3f,  0.02f,	// Upper left corner
	 0.5f,  0.5f, -0.5f,    0.8f, 0.3f,  0.02f,	// Upper right corner
	 0.5f,  -0.5f, -0.5f,    0.8f, 0.3f,  0.02f,	// Lower right corner

	 0.0f,  0.0f, 0.3f,		0.1f, 0.02f, 0.02f,// Dark inner point 1
	-0.3f,  0.0f, 0.0f,		0.1f, 0.02f, 0.02f,	// Dark inner point 2
	 0.0f,  0.0f, -0.3f,	0.1f, 0.02f, 0.02f,// Dark inner point 3
	 0.3f,  0.0f, 0.0f,		0.1f, 0.02f, 0.02f,	// Dark inner point 4
	 0.0f,  0.3f, 0.0f,		0.1f, 0.02f, 0.02f,	// Dark inner point 5
	 0.0f,  -0.3f, 0.0f,	0.1f, 0.02f, 0.02f	// Dark inner point 6

};

GLuint indices[] =
{

	0, 1, 8,
	1, 2, 8,
	2, 3, 8,
	3, 0, 8,

	0, 1, 9,
	1, 5, 9,
	5, 4, 9,
	4, 0, 9,

	5, 6, 10,
	6, 7, 10,
	7, 4, 10,
	4, 5, 10,

	2, 6, 11,
	6, 7, 11,
	7, 3, 11,
	3, 2, 11,

	1, 5, 12,
	5, 6, 12,
	6, 2, 12,
	2, 1, 12,

	0, 4, 13,
	4, 7, 13,
	7, 3, 13,
	3, 0, 13

};


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
  std::list<std::vector<GLfloat>> vector;
  vector.push_back(std::vector<GLfloat>{1, 2, 3});
  vector.push_back(std::vector<GLfloat>{4, 5, 6});
  vector.push_back(std::vector<GLfloat>{7, 8, 9});
	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "HelloOpenGL", NULL, NULL);
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
  // std::ifstream myfile;
  // myfile.open ("graphics/shaders/default.vert", std::ios::binary);
  // std::string s;
  // getline(myfile, s);
  // std::cout << s << "\n\n\n\n dupaaaaa";
 Shader shaderProgram("default.vert", "default.frag");
 SolidFigure figure(vertices, sizeof(vertices), indices, sizeof(indices), {0.0f, 0.0f, -10.0f}, {0.0f, 0.0f, 0.0f});
	// Generates Shader object using shaders defualt.vert and default.frag
  for(std::list<std::vector<GLfloat>>::iterator i = vector.begin(); i != vector.end(); i++){
    std::vector<GLfloat> a = *i;
    std::cout<< a[0]<<", "<< a[1] << ", " << a[2]<<std::endl;
  }
  glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 0.5f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderProgram.Activate();
    figure.show(shaderProgram.GetId());

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
