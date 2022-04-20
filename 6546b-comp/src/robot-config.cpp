/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-config.cpp                                          */
/*    Author:       Emilio Orcullo                                            */
/*    Created:      Mon April 11 2022                                         */
/*    Description:  Robot configuration                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

// user defined config
// setup variables, etc.
double fourbarspeed = 100;

// basic vex devices
brain Brain;
controller Controller1 = controller(primary);

// motors
motor FourbarL = motor(PORT1, ratio36_1, true);
motor FourbarR = motor(PORT10, ratio36_1, false);
motor DriveLeft1 = motor(PORT11, ratio6_1, true);
motor DriveLeft2 = motor(PORT12, ratio6_1, false);
motor DriveLeft3 = motor(PORT13, ratio6_1, true);
motor DriveRight1 = motor(PORT20, ratio6_1, false);
motor DriveRight2 = motor(PORT19, ratio6_1, true);
motor DriveRight3 = motor(PORT18, ratio6_1, false);

// motor groups
motor_group fourbar(FourbarL, FourbarR);
motor_group leftside(DriveLeft1, DriveLeft2, DriveLeft3);
motor_group rightside(DriveRight1, DriveRight2, DriveRight3);
motor_group drivemotors(DriveLeft1, DriveLeft2, DriveLeft3, DriveRight1, DriveRight2, DriveRight3);

// digital out
digital_out front = digital_out(Brain.ThreeWirePort.H);
digital_out down_clamp = digital_out(Brain.ThreeWirePort.F);
digital_out ring_clamp = digital_out(Brain.ThreeWirePort.G);
digital_out ring_branch = digital_out(Brain.ThreeWirePort.A);

// sensors
vision vision7 = vision (PORT7, 50);
gps DriveGPS = gps(PORT18, 0.00, 0.00, mm, 180);
rotation rotationRight = rotation(PORT17, false);
rotation rotationLeft = rotation(PORT14, true);
inertial inertial13 = inertial(PORT16);

// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

// init and setup
void vexcodeInit( void ) {
  // start setup
  Brain.Screen.clearScreen();
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);

  // calibrate the GPS
  wait(200, msec);
  DriveGPS.calibrate();
  Brain.Screen.print("Calibrating GPS for Drivetrain");

  // wait for the GPS calibration process to finish
  while (DriveGPS.isCalibrating()) {
    wait(25, msec);
  }

  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}