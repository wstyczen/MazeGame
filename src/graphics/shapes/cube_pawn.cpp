#include "graphics/shapes/cube_pawn.hpp"



void CubePawn::MakeMove(FigureState *state){
  if(figure_state_ == steady){
  figure_state_ = *state;
  if (*state == move_north){
    ang_vel.x = -move_settings.start_velocity;
    Roll({ang_vel.x, 0.0f}, 1.0f);
  } else if (*state == move_south){
    ang_vel.x = move_settings.start_velocity;
    Roll({ang_vel.x, 0.0f}, 1.0f);
  }  else if (*state == move_east){
    ang_vel.y = move_settings.start_velocity;
    Roll({0.0f, ang_vel.y}, 1.0f);
  } else if (*state == move_west){
    ang_vel.y = -move_settings.start_velocity;
    Roll({0.0f, ang_vel.y}, 1.0f);
  }
  }
}
