#include"graphics/shapes/solid_figure.hpp"


SolidFigure::SolidFigure(GLfloat *vertices,unsigned int vert_size, GLuint *indices, unsigned int indi_size,
                         glm::vec3 posi, glm::vec3 pos){

    position = posi;
    pose = pos;
    vao = std::unique_ptr<VAO>(new VAO());
    vao->Bind();
    vbo = std::unique_ptr<VBO>(new VBO(vertices, vert_size));
    ebo = std::unique_ptr<EBO>(new EBO(indices, indi_size));
    vao->LinkAttrib(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void *)0);
    vao->LinkAttrib(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    mvp.model = glm::mat4(1.0f);
    mvp.proj = glm::mat4(1.0f);
    mvp.view = glm::mat4(1.0f);
    //delete that later
    mvp.model = glm::rotate(mvp.model, glm::radians(pos.x), glm::vec3(1.0f, 0.0f, 0.0f));
    mvp.model = mvp.model * glm::rotate(mvp.model, glm::radians(pos.y), glm::vec3(0.0f, 1.0f, 0.0f));
    mvp.model = mvp.model * glm::rotate(mvp.model, glm::radians(pos.z), glm::vec3(0.0f, 0.0f, 1.0f));
    mvp.view = glm::translate(mvp.view, posi);
	mvp.proj = glm::perspective(glm::radians(45.0f), (float)(800/800), 0.1f, 100.0f);
}

void SolidFigure::show(const GLuint &shader_id) {
    int modelLoc = glGetUniformLocation(shader_id, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mvp.model));
    int viewLoc = glGetUniformLocation(shader_id, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mvp.view));
    int projLoc = glGetUniformLocation(shader_id, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mvp.proj));
    vao->Bind();
    glDrawElements(GL_TRIANGLES, ebo->GetCount(), GL_UNSIGNED_INT, 0);

}
SolidFigure::~SolidFigure() {
  vao->Unbind();
  vbo->Unbind();
  ebo->Unbind();
}




