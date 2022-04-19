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
double intakespeed = 40;
double fourbarspeed = 70;
double twobarspeed = 40;


// basic vex devices
brain Brain;
controller Controller1 = controller(primary);

// motors
motor twobar = motor(PORT6, ratio18_1, false);
motor intake = motor(PORT19, ratio6_1, false);
motor Motor16 = motor(PORT16, ratio36_1, true);
motor Motor17 = motor(PORT17, ratio36_1, false);
motor Motor14 = motor(PORT14, ratio6_1, true);
motor Motor15 = motor(PORT15, ratio6_1, true);
motor Motor9 = motor(PORT9, ratio6_1, true);
motor Motor10 = motor(PORT10, ratio6_1, true);
motor Motor9F = motor(PORT9, ratio6_1, false);
motor Motor10F = motor(PORT10, ratio6_1, false);

// motor groups
motor_group fourbar(Motor16, Motor17);
motor_group leftside(Motor14, Motor15);
motor_group rightside(Motor9, Motor10);
motor_group rightside_old(Motor9F, Motor10F);
motor_group drivemotors(Motor9, Motor10, Motor14, Motor15);
motor_group drivemotors_old(Motor9F, Motor10F, Motor14, Motor15);

// digital out
digital_out front = digital_out(Brain.ThreeWirePort.B);
digital_out down_clamp = digital_out(Brain.ThreeWirePort.C);
digital_out ring_clamp = digital_out(Brain.ThreeWirePort.D);
digital_out ring_branch = digital_out(Brain.ThreeWirePort.A);

// sensors
vision vision7 = vision (PORT7, 50);
vision vision5 = vision (PORT5, 50);
gps DriveGPS = gps(PORT18, 0.00, 0.00, mm, 180);
rotation rotationRight = rotation(PORT8, false);
rotation rotationLeft = rotation(PORT12, true);
inertial inertial13 = inertial(PORT13);
rotation rotationBar = rotation(PORT11, false);

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


//compat for 6 motor
/*
motor Motor20_6M = motor(PORT20, ratio6_1, false);
motor Motor19_6M = motor(PORT19, ratio6_1, true);
motor Motor18_6M = motor(PORT18, ratio6_1, false);

motor Motor13_6M = motor(PORT13, ratio6_1, true);
motor Motor12_6M = motor(PORT12, ratio6_1, false);
motor Motor11_6M = motor(PORT11, ratio6_1, true);

// drivetrain
motor_group drivemotor_6M(Motor20_6M, Motor19_6M, Motor18_6M, Motor13_6M, Motor12_6M, Motor11_6M);
motor_group rightside_6M(Motor20_6M, Motor19_6M, Motor18_6M);
motor_group leftside_6M(Motor13_6M, Motor12_6M, Motor11_6M);
*/

//left side 20, 19, 18 (19 is reverse)
//right side 11, 12, 13 (12 is reverse)
// interial in 16
// 14 is L rotational and 17 is R rotational
