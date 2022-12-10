#include "graphics/shapes/complex_cube.hpp"
#include <vector>

ComplexCube::ComplexCube(GLfloat side,glm::vec3 vertex_color, glm::vec3 inner_color,glm::vec3 posi, glm::vec3 pos
                                    )
    : DynamicSolidFigure(new GLfloat[] {
          //               COORDINATES
          -0.5f * side, -0.5f * side, 0.5f * side,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Lower left corner
          -0.5f * side, 0.5f * side,  0.5f * side,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Upper left corner
          0.5f * side,  0.5f * side,  0.5f * side,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Upper right corner
          0.5f * side,  -0.5f * side, 0.5f * side,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Lower right corner

          -0.5f * side, -0.5f * side, -0.5f,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Lower left corner
          -0.5f * side, 0.5f * side,  -0.5f,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Upper left corner
          0.5f * side,  0.5f * side,  -0.5f,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Upper right corner
          0.5f * side,  -0.5f * side, -0.5f,
              vertex_color.x,      vertex_color.y,      vertex_color.z,  // Lower right corner

          0.0f * side,  0.0f * side,  0.3f * side,
              inner_color.x,      inner_color.y,      inner_color.z,  // Dark inner point 1
          -0.3f * side, 0.0f * side,  0.0f * side,
              inner_color.x,      inner_color.y,      inner_color.z,  // Dark inner point 2
          0.0f * side,  0.0f * side,  -0.3f * side,
              inner_color.x,      inner_color.y,      inner_color.z,  // Dark inner point 3
          0.3f * side,  0.0f * side,  0.0f * side,
              inner_color.x,      inner_color.y,      inner_color.z,  // Dark inner point 4
          0.0f * side,  0.3f * side,  0.0f * side,
              inner_color.x,      inner_color.y,      inner_color.z,  // Dark inner point 5
          0.0f * side,  -0.3f * side, 0.0f * side,
              inner_color.x,      inner_color.y,      inner_color.z  // Dark inner point 6

      },
          336,
          new GLuint[]{

              0, 1,  8,  1, 2,  8,  2,
              3, 8,  3,  0, 8,

              0, 1,  9,  1, 5,  9,  5,
              4, 9,  4,  0, 9,

              5, 6,  10, 6, 7,  10, 7,
              4, 10, 4,  5, 10,

              2, 6,  11, 6, 7,  11, 7,
              3, 11, 3,  2, 11,

              1, 5,  12, 5, 6,  12, 6,
              2, 12, 2,  1, 12,

              0, 4,  13, 4, 7,  13, 7,
              3, 13, 3,  0, 13

          }, 288, posi, pos) {
  size = side;
}






void ComplexCube::Roll(const glm::vec2& turn_vec, GLfloat scale) {
    float prev_pose_x, prev_pose_y, move_x, move_y, prev_position_z, position_z, move_z(0), pose_x, pose_y;
    prev_pose_x = pose.x - floor(pose.x / 90) * 90.0f;
    prev_pose_y = pose.y - floor(pose.y / 90) * 90.0f;
    turn(glm::vec3(turn_vec.x, turn_vec.y, 0.0f));
    pose_x = pose.x - floor(pose.x / 90) * 90.0f;
    pose_y = pose.y - floor(pose.y / 90) * 90.0f;
    if (fabs(prev_pose_x - pose_x) > 2 * fabs(turn_vec.x)) prev_pose_x = pose_x;
    if (fabs(prev_pose_y - pose_y) > 2 * fabs(turn_vec.y)) prev_pose_y = pose_y;

    move_x = (cos(float(-pose_y + 135.0f) * 3.1415f / 180.0f) - cos(float(-prev_pose_y + 135) * 3.1415 / 180)) * scale*size / sqrt(2);
    move_y = -(cos(float(-pose_x + 135.0f) * 3.1415f / 180.0f) - cos(float(-prev_pose_x + 135) * 3.1415 / 180)) * scale*size /sqrt(2);
    prev_position_z = fabs(sqrt(3) * cos((prev_pose_y - 45.0f) / 180 * 3.1415) * cos((prev_pose_x - 45.0f) / 180.0f * 3.1415)) / sqrt(2);
    position_z = fabs(sqrt(3) * cos((pose_y - 45.0f) / 180 * 3.1415) * cos((pose_x - 45.0f) / 180.0f * 3.1415)) / sqrt(2);
    move_z = position_z - prev_position_z;

    move(glm::vec3(move_x, move_y, move_z) * scale);

}
