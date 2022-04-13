/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-autonomous.cpp                                      */
/*    Author:       Chloe Dimmmck                                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Autonomous methods for robot                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// setup
#include "vex.h"
#include "math.h"
#include "robot-config.h"
using namespace vex;

// define variable which notes the change in angle
double change_in_inertial;

// the constant distance whic it takes from end point to mid line
double second_stage_constant = 0.5;

// move forward / back based on rotations
void y_direction(double rot) {
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
  while (1) {
  double average = abs(int(rotationLeft.position(turns) + rotationRight.position(turns)))/2;
    if(average == rot){
      drivemotors.stop(brake);
      break;
    }
    else if(average > rot) {
      drivemotors.spin(reverse);
    }
    else if(average < rot) {
      drivemotors.spin(forward);
    }
  }
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
}

// pivot on oneside of wheel while driving
void wheel_pivot(double ratio, double angel, bool directions, double speed) {
  if(directions == true) {
    if(angel > 0) {
      leftside.setVelocity(speed, percent);
      rightside.setVelocity((speed*ratio), percent);
    }
    else if(angel < 0) {
      rightside.setVelocity(speed, percent);
      leftside.setVelocity((speed*ratio), percent);
    }
  }
  else if(directions == false) {
    if(angel > 0) {
       rightside.setVelocity(-speed, percent);
       leftside.setVelocity(-(speed*ratio), percent);
    }
    else if(angel < 0) {
       leftside.setVelocity(-speed, percent);
       rightside.setVelocity(-(speed*ratio), percent);
    }
  }

  double initAngel = inertial13.orientation(yaw, degrees);
  double currentAngel = initAngel;
  double finalAngel = fmod((initAngel + angel), 360);
  while(currentAngel != finalAngel) {
    currentAngel = inertial13.orientation(yaw, degrees);
    leftside.spin(forward);
    rightside.spin(forward);
  }
  leftside.stop(brake);
  rightside.stop(brake);
}

// center pivot turning
void normal_turning(double deg) {
  double initAngel = inertial13.heading(degrees);
  double currentAngel = initAngel;
  double finalAngel = initAngel + deg;
  if(finalAngel > 360) {
    finalAngel = finalAngel - 360;
  }
  else if(finalAngel < 0) {
    finalAngel = finalAngel + 360;
  }
  while(currentAngel != finalAngel) {
    if(deg > 0) {
      leftside.spin(forward);
      rightside.spin(reverse);
    }
    else if(deg < 0) {
      leftside.spin(reverse);
      rightside.spin(forward);
    }
  }
  leftside.stop(brake);
  rightside.stop(brake);
}

//vision alignment
void goal_align(bool side, vex::vision::signature goal_color) {
  int center = 158;
  double original_inertial = inertial13.heading(degrees);
  if(side == true){
    //forward (vision7)
    // takes "photo" of any yellow objects and locates them
    vision7.takeSnapshot(goal_color);
    if(vision7.largestObject.exists){
      while(vision7.largestObject.centerX > center){
        //turn right
        leftside.spin(forward);
        rightside.spin(reverse);
      }
      while(vision7.largestObject.centerX < center){
        // turn left
        leftside.spin(reverse);
        rightside.spin(forward);
      }
      if(vision7.largestObject.exists == center){
        // brake
        drivemotors.stop(brake);
        change_in_inertial = inertial13.heading(degrees) - original_inertial;
      }
    }
  }
  else if(side == false){
    //reverse (vision5)
    // takes "photo" of any yellow objects and locates them
    vision7.takeSnapshot(goal_color);
    if(vision7.largestObject.exists){
      while(vision7.largestObject.centerX > center){
        //turn right
        leftside.spin(reverse);
        rightside.spin(forward);
      }
      while(vision7.largestObject.centerX < center){
        // turn left
        leftside.spin(forward);
        rightside.spin(reverse);      
      }
      if(vision7.largestObject.exists == center){
        // brake
        drivemotors.stop(brake);
        change_in_inertial = inertial13.heading(degrees) - original_inertial;
      }
    }
  }
}

//distance between goal and bot
double second_stage_goal_distance(){
  return (second_stage_constant/cos(change_in_inertial));
}