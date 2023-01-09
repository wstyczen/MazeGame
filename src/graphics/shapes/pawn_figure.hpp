#include "graphics/shapes/dynamic_state_figure.hpp"

class PawnFigure {
 public:
  enum FigureState { north, east, south, west, steady };
  void Act() { MakeMove(); }
  void SetMoveState(PawnFigure::FigureState& state) { move_state = state; }
  PawnFigure::FigureState GetMoveState() { return move_state; }

 protected:
  PawnFigure::FigureState move_state = PawnFigure::FigureState::steady;
  virtual void MakeMove() = 0;

 protected:
  PawnFigure::MoveState move_state = PawnFigure::MoveState::steady;
  virtual void MakeMove() = 0;
};
