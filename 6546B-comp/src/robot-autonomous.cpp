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

// please include comments on your code
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


