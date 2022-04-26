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
  while(1) {
    Brain.Screen.clearScreen();
    // Motor Temp
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Drivebase average temperature is: ");
    Brain.Screen.print(drivemotors.temperature());
    Brain.Screen.print(" celcius");

    // Individual motors
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Left motor 1: ");
    Brain.Screen.print(Motor14.temperature());

    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("Left motor 2: ");
    Brain.Screen.print(Motor12.temperature());
    
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("Right motor 1: ");
    Brain.Screen.print(Motor10.temperature());

    Brain.Screen.setCursor(5,1);
    Brain.Screen.print("Right motor 2: ");
    Brain.Screen.print(Motor8.temperature());
    
    // Current heading
    Brain.Screen.setCursor(6, 1);
    Brain.Screen.print("Current heading: ");
    Brain.Screen.print(inertial13.heading());

    // Rotation positions
    Brain.Screen.setCursor(7, 1);
    Brain.Screen.print("Left Rotation position: ");
    Brain.Screen.print(rotationLeft.position(turns));

    Brain.Screen.setCursor(8, 1);
    Brain.Screen.print("Right Rotation position: ");
    Brain.Screen.print(rotationRight.position(turns));

    vex::this_thread::sleep_for(100);
  }
}
// -- Redundant functions since functions can't be imported into print statements on the brain -- //
// system average temp
/*
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
*/