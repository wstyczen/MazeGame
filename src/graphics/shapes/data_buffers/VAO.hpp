//source: https://github.com/VictorGordan/opengl-tutorials.git
#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "graphics/shapes/data_buffers/VBO.hpp"

class VAO {
 public:
  // ID reference for the Vertex Array Object
  GLuint ID;
  // Constructor that generates a VAO ID
  VAO();

  // Links a VBO Attribute such as a position or color to the VAO
  void LinkAttrib(VBO& VBO,
                  GLuint layout,
                  GLuint numComponents,
                  GLenum type,
                  GLsizeiptr stride,
                  void* offset);
  // Binds the VAO
  void Bind();
  // Unbinds the VAO
  void Unbind();
  // Deletes the VAO
  void Delete();
  ~VAO(){Unbind(); Delete();}
};

#endif
