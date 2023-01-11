#include "graphics/shapes/complex_cube.hpp"

#include <vector>

#include "game/game.hpp"
#include "maze/utility.hpp"

namespace {

maze::Direction GetAsMazeDirection(ComplexCube::FigureState direction) {
  switch (direction) {
    case ComplexCube::FigureState::move_north:
      return maze::Direction::UP;
    case ComplexCube::FigureState::move_south:
      return maze::Direction::DOWN;
    case ComplexCube::FigureState::move_east:
      return maze::Direction::RIGHT;
    case ComplexCube::FigureState::move_west:
      return maze::Direction::LEFT;
  }
  throw std::invalid_argument("Invalid direction");
}

}  // namespace

ComplexCube::ComplexCube(const glm::vec3& posi,
                         const glm::vec3& pos,
                         const glm::vec3& vertex_color,
                         const glm::vec3& inner_color)
    : DynamicSolidFigure(
          MakeCubeFigure(size_, posi, pos, vertex_color, inner_color)),
      start_position(posi) {}

void ComplexCube::Roll(const glm::vec2& turn_vec, GLfloat scale) {
  float prev_pose_x, prev_pose_y, move_x, move_y, prev_position_z, position_z,
      move_z, pose_x, pose_y;
  prev_pose_x = pose_.x - floor(pose_.x / 90) * 90.0f;
  prev_pose_y = pose_.y - floor(pose_.y / 90) * 90.0f;
  Turn({turn_vec.x, turn_vec.y, 0.0f});
  pose_x = pose_.x - floor(pose_.x / 90) * 90.0f;
  pose_y = pose_.y - floor(pose_.y / 90) * 90.0f;
  if (fabs(prev_pose_x - pose_x) > 2 * fabs(turn_vec.x))
    prev_pose_x = pose_x;
  if (fabs(prev_pose_y - pose_y) > 2 * fabs(turn_vec.y))
    prev_pose_y = pose_y;

  move_x = (cos(float(-pose_y + 135.0f) * 3.1415f / 180.0f) -
            cos(float(-prev_pose_y + 135) * 3.1415 / 180)) *
           scale * size_ / sqrt(2);
  move_y = -(cos(float(-pose_x + 135.0f) * 3.1415f / 180.0f) -
             cos(float(-prev_pose_x + 135) * 3.1415 / 180)) *
           scale * size_ / sqrt(2);
  prev_position_z = fabs(sqrt(3) * cos((prev_pose_y - 45.0f) / 180 * 3.1415) *
                         cos((prev_pose_x - 45.0f) / 180.0f * 3.1415)) /
                    sqrt(2);
  position_z = fabs(sqrt(3) * cos((pose_y - 45.0f) / 180 * 3.1415) *
                    cos((pose_x - 45.0f) / 180.0f * 3.1415)) /
               sqrt(2);
  move_z = position_z - prev_position_z;

  Move(glm::vec3(move_x, move_y, move_z));
}

bool ComplexCube::MakeMove(ComplexCube::FigureState direction) {
  game::Game* game = game::Game::GetInstance();
  if (move_state == steady && game->Move(GetAsMazeDirection(direction))) {
    move_state = direction;
    if (direction == move_north) {
      ang_vel.x = -move_settings.start_velocity;
      Roll({ang_vel.x, 0.0f}, 1.0f);
    } else if (direction == move_south) {
      ang_vel.x = move_settings.start_velocity;
      Roll({ang_vel.x, 0.0f}, 1.0f);
    } else if (direction == move_east) {
      ang_vel.y = move_settings.start_velocity;
      Roll({0.0f, ang_vel.y}, 1.0f);
    } else if (direction == move_west) {
      ang_vel.y = -move_settings.start_velocity;
      Roll({0.0f, ang_vel.y}, 1.0f);
    }
    game->StartTimerIfNotAlreadyRunning();
    return true;
  } else
    return false;
}

void ComplexCube::Act() {
  if (move_state == ComplexCube::FigureState::move_north) {
    if ((pose_.x - floor(pose_.x / 90) * 90.0f) >= -ang_vel.x) {
      Roll({ang_vel.x, 0.0f}, move_settings.distance);
      ang_vel.x -= cos((pose_.x - floor(pose_.x / 90) * 90.0f) * 3.1415 / 180) *
                   move_settings.acceleration;

    } else {
      SetPose({0.0f, 0.0f, 0.0f});
      DiscretizatePosition();
      ang_vel.x = 0.0f;
      move_state = steady;
    }

  } else if (move_state == ComplexCube::FigureState::move_east) {
    if ((pose_.y - floor(pose_.y / 90) * 90.0f) >= ang_vel.y) {
      Roll({0.0f, ang_vel.y}, move_settings.distance);
      ang_vel.y += sin((pose_.y - floor(pose_.y / 90) * 90.0f) * 3.1415 / 180) *
                   move_settings.acceleration;

    } else {
      SetPose({0.0f, 0.0f, 0.0f});
      DiscretizatePosition();
      ang_vel.y = 0.0f;
      move_state = steady;
    }
  } else if (move_state == ComplexCube::FigureState::move_south) {
    if ((pose_.x - floor(pose_.x / 90) * 90.0f) >= ang_vel.x) {
      Roll({ang_vel.x, 0.0f}, move_settings.distance);
      ang_vel.x += sin((pose_.x - floor(pose_.x / 90) * 90.0f) * 3.1415 / 180) *
                   move_settings.acceleration;

    } else {
      SetPose({0.0f, 0.0f, 0.0f});
      DiscretizatePosition();
      ang_vel.x = 0.0f;
      move_state = steady;
    }
  } else if (move_state == ComplexCube::FigureState::move_west) {
    if ((pose_.y - floor(pose_.y / 90) * 90.0f) >= -ang_vel.y) {
      Roll({0.0f, ang_vel.y}, move_settings.distance);
      ang_vel.y -= cos((pose_.y - floor(pose_.y / 90) * 90.0f) * 3.1415 / 180) *
                   move_settings.acceleration;

    } else {
      SetPose({0.0f, 0.0f, 0.0f});
      DiscretizatePosition();
      ang_vel.y = 0.0f;
      move_state = steady;
    }
  }
}

void ComplexCube::DiscretizatePosition() {
  float discrete_x, discrete_y;
  discrete_x = roundf((position_.x - start_position.x) /
                      (move_settings.distance * size_)) *
               (move_settings.distance * size_);
  discrete_y = roundf((position_.y - start_position.y) /
                      (move_settings.distance * size_)) *
               (move_settings.distance * size_);
  SetPosition({start_position.x + discrete_x, start_position.y + discrete_y,
               start_position.z});
}

DynamicSolidFigure ComplexCube::MakeCubeFigure(const GLfloat& side,
                                               const glm::vec3& posi,
                                               const glm::vec3& pos,
                                               const glm::vec3& vertex_color,
                                               const glm::vec3& inner_color) {
  std::vector<GLfloat> vertices{
      //               EACH TWO ROWS REPRESENT ONE VERTEX
      // FRONT SIDE
      -0.5f * side, -0.5f * side, 0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Lower left corner

      -0.5f * side, 0.5f * side, 0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Upper left corner

      0.5f * side, 0.5f * side, 0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Upper right corner

      0.5f * side, -0.5f * side, 0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Lower right corner

      // BACK SIDE
      -0.5f * side, -0.5f * side, -0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Lower left corner

      -0.5f * side, 0.5f * side, -0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Upper left corner

      0.5f * side, 0.5f * side, -0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Upper right corner

      0.5f * side, -0.5f * side, -0.5f * side, vertex_color.x, vertex_color.y,
      vertex_color.z,  // Lower right corner

      // INNER POINTS FOR EACH SIDE
      0.0f * side, 0.0f * side, 0.3f * side, inner_color.x, inner_color.y,
      inner_color.z,  // Dark inner point 1

      -0.3f * side, 0.0f * side, 0.0f * side, inner_color.x, inner_color.y,
      inner_color.z,  // Dark inner point 2

      0.0f * side, 0.0f * side, -0.3f * side, inner_color.x, inner_color.y,
      inner_color.z,  // Dark inner point 3

      0.3f * side, 0.0f * side, 0.0f * side, inner_color.x, inner_color.y,
      inner_color.z,  // Dark inner point 4

      0.0f * side, 0.3f * side, 0.0f * side, inner_color.x, inner_color.y,
      inner_color.z,  // Dark inner point 5

      0.0f * side, -0.3f * side, 0.0f * side, inner_color.x, inner_color.y,
      inner_color.z  // Dark inner point 6
  };

  std::vector<GLuint> indices{

      0, 1, 8,  1, 2, 8,  2, 3, 8,  3, 0, 8,

      0, 1, 9,  1, 5, 9,  5, 4, 9,  4, 0, 9,

      5, 6, 10, 6, 7, 10, 7, 4, 10, 4, 5, 10,

      2, 6, 11, 6, 7, 11, 7, 3, 11, 3, 2, 11,

      1, 5, 12, 5, 6, 12, 6, 2, 12, 2, 1, 12,

      0, 4, 13, 4, 7, 13, 7, 3, 13, 3, 0, 13};
  DynamicSolidFigure cube(vertices, indices, posi, pos);
  return cube;
}
