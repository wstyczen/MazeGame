#include "graphics/shapes/dynamic_solid_figure.hpp"




class DynamicStateFigure{
  public:
    //help enum FigureState {};
    DynamicStateFigure(const DynamicSolidFigure &fig): solid_figure_(fig){};
    // help virtual void MakeMove(FigureState *state) = 0;
    virtual void Act() = 0;
    void Show(const GLuint &shader_id) const{solid_figure_.Show(shader_id);}
    void SetProjMatrix(const glm::mat4 &proj_mat){solid_figure_.SetProjMatrix(proj_mat);}
    //FigureState GetFigureState() const {return this->figure_state_;}
    glm::vec3 GetPosition() const {return solid_figure_.GetPosition();}
    glm::vec3 GetPose() const {return solid_figure_.GetPose();}

  protected:

    //FigureState figure_state_;
    DynamicSolidFigure solid_figure_;
    //virtual void MakeMove() = 0;

};
