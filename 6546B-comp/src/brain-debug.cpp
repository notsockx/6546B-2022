/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_run.cpp                                             */
/*    Author:       Chloe Dimmmck, Diren Gomez                                */
/*    Created:      Thu Sep 26 2018                                           */
/*    Description:  Auton runs yay                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "math.h"
#include "robot-config.h"
using namespace vex;

// function to print to screen
void debug_screen(){

}

// system average temp
double avg_motor_temp(){
  return drivemotors.temperature();
}

// individual motors temp
double indv_motor_temp(int motor_num){
  // motor nums can be either 14, 12, 18, 10
  if (motor_num == 10){
    return Motor10.temperature();
  }
  else if (motor_num == 12){
    return Motor12.temperature();
  }
  else if (motor_num == 14){
    return Motor14.temperature();
  }
  else if (motor_num == 18){
    return Motor18.temperature();
  }
  else{
    return 0;
  }
}

// rotation of the robot
double current_rotation(){
  return inertial13.heading();
}

// number of turns on left
double l_distance(){
  return rotationLeft.position(turns);
}

// number of turns on right
double r_distance(){
  return rotationRight.position(turns);
}