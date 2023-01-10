#include <glad/glad.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string get_file_contents(const char* filename);

class Shader {
 public:
  // Reference ID of the Shader Program

  // Constructor that build the Shader Program from 2 different shaders
  Shader();
  GLuint const GetId() { return ID; }
  // Activates the Shader Program
  void Activate();
  // Deletes the Shader Program
  void Delete();

 private:
  // Checks if the different Shaders have compiled properly
  GLuint ID;
  void compileErrors(unsigned int shader, const char* type);
};
