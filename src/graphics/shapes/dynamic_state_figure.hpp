#include "graphics/shapes/dynamic_solid_figure.hpp"




class DynamicStateFigure : public DynamicSolidFigure {
  public:
    using DynamicSolidFigure::DynamicSolidFigure;
    enum FigureState {in_move, steady};
    //void Act(){MakeMove();}
    void SetFigureState(DynamicStateFigure::FigureState &state){figure_state = state;}
    DynamicStateFigure::FigureState GetFigureState(){return figure_state;}

  protected:
    DynamicStateFigure::FigureState figure_state = DynamicStateFigure::FigureState::steady;
    //virtual void MakeMove() = 0;

};
