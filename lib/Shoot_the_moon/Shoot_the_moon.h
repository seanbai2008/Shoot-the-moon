#ifndef Shoot_the_moon
#define Shoot_the_moon

#include <Arduino.h>

// extern float traj_ref[300];

class motor{
  //maximum steps for the motor to rotate before the rod touches the wall
  const int16_t the_most_leftest_position = 266;
  //maximum steps for the motor to rotate before the rod hit each other
  const int16_t the_most_rightest_position = 399;
  int16_t current_steps = 399;
public:

  void motor_init();
  // the function will leads the rods go to wall
  void make_single_forward_step();
  // the function will leads the rods go to hit each other
  void make_single_backward_step();

  //this function allows user to input how many steps the motor needs to go
  void move(int16_t steps);

  //this function will return the current position of the motor
  uint8_t get_current_position();
  //this function will update the current position of the motor
  void set_current_position();

  // This function will take a value which is the angle between one rod and x-axis
  // and return how much angle the motor should rotate so that the rod can reach
  //that angle
  float angle_to_position(float ref_angle);

};




#endif
