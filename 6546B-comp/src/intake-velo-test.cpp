/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       intake-velp-test.cpp                                      */
/*    Author:       Chloe Dimmmck, Diren Gomez                                */
/*    Created:      Thu Sep 26 2017                                           */
/*    Description:  Auton runs yay                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "math.h"
#include "robot-config.h"
#include "robot-control.h"
using namespace vex;

void velo_test(int drivespeed){
  for(int velo = 45; velo > 0; velo = velo - 5){
    drivemotors.setVelocity(drivespeed, pct);
    intake.setVelocity(velo, pct);
    waitUntil(rotationLeft.position(turns));
    drivemotors.stop(brake);
    wait(45, seconds);

    // print statements
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Drive speed is: ");
    Brain.Screen.print(drivespeed);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("Intake speed is: ");
    Brain.Screen.print(velo);
  }
}