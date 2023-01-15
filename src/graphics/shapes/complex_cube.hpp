#ifndef COMPLEX_CUBE_HPP_
#define COMPLEX_CUBE_HPP_
#include "graphics/shapes/dynamic_solid_figure.hpp"

namespace graphics{

//Multiply by value in order to convert degrees into radians
#define DEG2RAD (3.1415f / 180.0f)
//floors value to 90
#define FLOORto90(angle) ((floor(angle / 90.0f)) * 90.0f)

class ComplexCube : public DynamicSolidFigure {
 public:
  enum FigureState { move_north, move_east, move_south, move_west, steady };
  struct MoveSettings {
    float acceleration;
    float start_velocity;
    unsigned int distance;
  };
  /**
   * @brief Constructor of a ComplexCube object
   *
   * @param posi starting position of a cube
   * @param pos starting pose of a cube
   * @param vertex_color color of outer vertices
   * @param inner_color color of details
   * @param cube_size size of a cube
   * @param move_settings settings of a cube
   * @throws std::invalid_argument if size isn't positive value
   * @throws std::invalid_argument if settings are not passing ComplexCube::CheckMoveSettings test.
   */
  ComplexCube(const glm::vec3& posi,
              const glm::vec3& pos,
              const glm::vec3& vertex_color,
              const glm::vec3& inner_color,
              const GLfloat &cube_size,
              const MoveSettings &move_settings);
  /**
   * @brief Provides information about ComplexCube internal state
   *
   * @return true if cube is currently moving
   * @return false if cube move_state_ equals ComplexCube::FigureState::steady
   */
  bool IsMoving() const;
  /**
   * @brief Triggers ComplexCube to move in specified direction.
   *
   * @param direction specifies the direction of move
   * @return true if ComplexCube started moving,
   * @return false if ComplexCube is already moving.
   */
  bool MakeMove(ComplexCube::FigureState direction);
  /**
   *!@brief Checks if move_settings are correct.
   @param[in] move_settings struct containing settings of the ComplexCube.
   @returns true if settings are correct, \n
   @returns false if any of the following: \n
   - acceleration or start_velocity are negative values, \n
   - both acceleration and start_velocity are equal 0, \n
   - distance isn't positive value.
  */
  static bool CheckMoveSettings(const MoveSettings &move_settings);

  /**
   * @brief Describes ComplexCube's behaviour as state machine depending on move_state_ value. \n
   * States of cube: \n
   * -steady - cube is not moving, \n
   * -move_north - cube will roll north direction untill it falls over next side, \n
   * -move_south - cube will roll south direction untill it falls over next side, \n
   * -move_west - cube will roll west direction untill it falls over next side, \n
   * -move_east - cube will roll east direction untill it falls over next side \n
   *
   * Speed of moves is described by move_settings_
   */
  void Act();
  /**
   *!@brief Creates DynamidSolidFigure in shape of cube with some detailing.
   @param[in] side size of a cube
   @param[in] posi position of a cube
   @param[in] pos pose of a cube
   @param[in] vertex_color color of a outside vertices in cube
   @param[in] inner_color color of a details in cube
   @throws std::invalid_argument if side isn't positive value
  */
  static DynamicSolidFigure MakeCubeFigure(const GLfloat& side,
                                           const glm::vec3& posi,
                                           const glm::vec3& pos,
                                           const glm::vec3& vertex_color,
                                           const glm::vec3& inner_color);

 private:
  /**
   *!@brief Rolls ComplexCube like is was lying down at flat surface.
   @param[in] turn_vec vector of angles by which cube will be rotated.
   @throws std::invalid_argument if absolute value of any angle is greater than 15 deg.
  */
  void Roll(const glm::vec2& turn_vec, GLfloat scale);

  /**
   *!@brief Rounds ComplexCube's position to closest grid node which starts at beggining cube's position.
   Grid size is equal to move_settings_.distance
  */
  void DiscretizatePosition();
  //Size of cube figure
  const GLfloat size_;
  //Position given in constructor.
  const glm::vec3 start_position_;
  //current angular speed.
  glm::vec3 ang_vel = {0.0f, 0.0f, 0.0f};
  //glm::vec3 lin_vel = {0.0f, 0.0f, 0.0f};
  //Defines the state of figure on which depends its behaviour descibed by Act() method.
  ComplexCube::FigureState move_state_ = steady;
  //Settings of cube that devines it's move speed and distance
  const ComplexCube::MoveSettings move_settings_;

};

}
#endif
