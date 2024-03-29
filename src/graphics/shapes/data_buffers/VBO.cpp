//source: https://github.com/VictorGordan/opengl-tutorials.git
#include "graphics/shapes/data_buffers/VBO.hpp"

// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat const* vertices, const GLsizeiptr &size) {
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ARRAY_BUFFER, ID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
/*
VBO::VBO(const std::list<Vertex> &vertices) {
  GLfloat vert_array[6];

}
*/
// Binds the VBO
void VBO::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

// Unbinds the VBO
void VBO::Unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Deletes the VBO
void VBO::Delete() {
  glDeleteBuffers(1, &ID);
}
