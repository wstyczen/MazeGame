#ifndef EBO_CLASS_HPP_
#define EBO_CLASS_HPP_

#include <glad/glad.h>

class EBO {
 public:
  // ID reference of Elements Buffer Object
  GLuint ID;
  unsigned int count;
  // Constructor that generates a Elements Buffer Object and links it to indices
  EBO(GLuint const* indices, const GLsizeiptr &size);

  // Binds the EBO
  void Bind();
  // Unbinds the EBO
  void Unbind();
  // Deletes the EBO
  void Delete();
  unsigned int GetCount();
  ~EBO(){Unbind(); Delete();}
};

#endif
