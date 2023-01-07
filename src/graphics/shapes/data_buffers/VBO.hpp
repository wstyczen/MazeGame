#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <list>

class VBO {
 public:
  struct Vertex {
    glm::vec3 coordinates;
    glm::vec3 color;
  };
  // Reference ID of the Vertex Buffer Object
  GLuint ID;
  // Constructor that generates a Vertex Buffer Object and links it to vertices
  VBO(GLfloat* vertices, GLsizeiptr size);
  // VBO(const std::list<Vertex> &vertices);
  //  Binds the VBO
  void Bind();
  // Unbinds the VBO
  void Unbind();
  // Deletes the VBO
  void Delete();
};
#endif
