#include "graphics/shapes/dynamic_state_figure.hpp"


class PawnFigure : public DynamicStateFigure {
  public:
    using DynamicStateFigure::DynamicSolidFigure::SolidFigure;
    enum MoveState {north, east, south, west, steady};
    void Act(){MakeMove();}
    void SetMoveState(PawnFigure::MoveState &state){move_state = state;}
    PawnFigure::MoveState GetMoveState(){return move_state;}

  protected:
    PawnFigure::MoveState move_state = PawnFigure::MoveState::steady;
    virtual void MakeMove() = 0;

};
