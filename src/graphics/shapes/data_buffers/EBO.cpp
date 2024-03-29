//source: https://github.com/VictorGordan/opengl-tutorials.git
#include "graphics/shapes/data_buffers/EBO.hpp"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(GLuint const* indices,const GLsizeiptr &size) {
  glGenBuffers(1, &ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  count = size / sizeof(GLuint);
}

// Binds the EBO
void EBO::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete() {
  glDeleteBuffers(1, &ID);
}

unsigned int EBO::GetCount() {
  return count;
}
