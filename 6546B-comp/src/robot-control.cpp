/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-control.cpp                                         */
/*    Author:       Chloe Dimmmck, Emilio Orcullo                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Driver control methods for robot                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// setup
#include "vex.h"
#include "math.h"
#include "robot-config.h"
using namespace vex;

// -- START OF TEMP MONITOR -- //
void temp_monitor(){
  while (1) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print(drivemotors.temperature(celsius));

    vex::this_thread::sleep_for(100);
  }
}
// -- END OF TEMP MOITOR -- //

// -- START OF DRIVETRAIN FUNCTIONS -- //
void UddDrivetrain() {
  // setup
  double x;
  double y;
  double velo;
  double bottom_out = 5;

  leftside.setStopping(coast);
  rightside.setStopping(coast);
  
  // left joystick controls angle robot goes towards
  // right joystick up-down controls robot speed
  while(1) {
    x = Controller1.Axis4.position() / 127.0;
    y = Controller1.Axis3.position() / 127.0;
    velo = (Controller1.Axis2.value() + 127 + bottom_out) / 127;
    // double approaching_x = abs(Controller1.Axis3.position())/ 127 + 25;

    x = Controller1.Axis4.value() * 100/127;
    y = Controller1.Axis3.value() * 100/127;

    leftside.spin(fwd, ((x+y) * velo), pct);
    rightside.spin(fwd, ((x-y) * velo), pct);
  
    // grab joystick positions
    // theta calc
    /*
    double x_pos = Controller1.Axis4.value() * 100 / 127;
    double y_pos = Controller1.Axis4.value() * 100 / 127;

    velo = (Controller1.Axis2.value() + 5) / 127 ;

    if( (x_pos >= 0) && (y_pos > 0)){
      leftside.spin(fwd, 100 * velo, pct);
      rightside.spin(fwd, 100 * velo * y_pos, pct);
      Brain.Screen.print("1");
    } 
    else if( (x_pos >= 0) && (y_pos < 0)){
      leftside.spin(reverse, 100 * velo, pct);
      rightside.spin(reverse, 100 * velo * y_pos, pct);
      Brain.Screen.print("2");
    } 
    else if( (x_pos < 0) && (y_pos > 0)){
      leftside.spin(fwd, 100 * velo * y_pos, pct);
      rightside.spin(fwd, 100 * velo, pct);
      Brain.Screen.print("3");
    } 
    else if( (x_pos < 0) && (y_pos < 0)){
      leftside.spin(reverse, 100 * velo * y_pos, pct);
      rightside.spin(reverse, 100 * velo, pct);
      Brain.Screen.print("4");
    } 
    */
    /*
    x = Controller1.Axis4.value() * 100/127;
    y = Controller1.Axis3.value() * 100/127;

    leftside.spin(fwd, (x+y)/2, pct);
    rightside.spin(reverse, (x-y)/2, pct);
    */
    
    // // calculate theta
    // if( x == 0 ) { theta = 0; }
    // if(x<0) { theta = M_PI/2 + atan2(y,x); }
    // else { theta = M_PI/2 - atan2(y,x); }

    // // left joystick magnitude for speed
    // v = sqrt(pow(x, 2) + pow(y, 2));
    // if(v > 100) { v = 100; }
    
    // // right joystick for speed
    // //v = Controller1.Axis1.value() * 100 / 127;

    // if( x >= 0 ) {
    //   leftside.spin(fwd, v, pct);
    //   rightside.spin(fwd, (-2*v)/(M_PI) * theta + v, pct);
    // }
    // else {
    //   leftside.spin(fwd, (2*v)/(M_PI) * theta + v, pct);
    //   rightside.spin(fwd, v, pct);
    // }
    
    vex::this_thread::sleep_for(100);
  }
}
// -- END OF DRIVETRAIN FUNCTIONS -- //

void ControlDrivetrain() {
  // setup
  double x;
  double y;

  leftside.setStopping(coast);
  rightside.setStopping(coast);
  
  // left joystick controls angle robot goes towards
  // right joystick up-down controls robot speed
  while(1) {
    // grab joystick positions
    x = Controller1.Axis4.value() * 100/127;
    y = Controller1.Axis3.value() * 100/127;

    leftside.spin(fwd, (x+y)/2, pct);
    rightside.spin(fwd, (x-y)/2, pct);

    // // calculate theta
    // if( x == 0 ) { theta = 0; }
    // if(x<0) { theta = M_PI/2 + atan2(y,x); }
    // else { theta = M_PI/2 - atan2(y,x); }

    // // left joystick magnitude for speed
    // v = sqrt(pow(x, 2) + pow(y, 2));
    // if(v > 100) { v = 100; }
    
    // // right joystick for speed
    // //v = Controller1.Axis1.value() * 100 / 127;

    // if( x >= 0 ) {
    //   leftside.spin(fwd, v, pct);
    //   rightside.spin(fwd, (-2*v)/(M_PI) * theta + v, pct);
    // }
    // else {
    //   leftside.spin(fwd, (2*v)/(M_PI) * theta + v, pct);
    //   rightside.spin(fwd, v, pct);
    // }
    
    vex::this_thread::sleep_for(100);
  }
}

void SumedhDrivetrain() {
  // setup
  double x;
  double y;

  leftside.setStopping(coast);
  rightside.setStopping(coast);
  
  // left joystick controls angle robot goes towards
  // right joystick up-down controls robot speed
  while(1) {
    // grab joystick positions
    x = Controller1.Axis4.value() * 100/127;
    y = Controller1.Axis2.value() * 100/127;

    leftside.spin(fwd, (x+y)/2, pct);
    rightside.spin(fwd, (x-y)/2, pct);

    // // calculate theta
    // if( x == 0 ) { theta = 0; }
    // if(x<0) { theta = M_PI/2 + atan2(y,x); }
    // else { theta = M_PI/2 - atan2(y,x); }

    // // left joystick magnitude for speed
    // v = sqrt(pow(x, 2) + pow(y, 2));
    // if(v > 100) { v = 100; }
    
    // // right joystick for speed
    // //v = Controller1.Axis1.value() * 100 / 127;

    // if( x >= 0 ) {
    //   leftside.spin(fwd, v, pct);
    //   rightside.spin(fwd, (-2*v)/(M_PI) * theta + v, pct);
    // }
    // else {
    //   leftside.spin(fwd, (2*v)/(M_PI) * theta + v, pct);
    //   rightside.spin(fwd, v, pct);
    // }
    
    vex::this_thread::sleep_for(100);
  }
}
// -- END OF DRIVETRAIN FUNCTIONS -- //

// -- START OF 6 Motor FUNCTIONS -- //
/*
void ControlDrivetrain_6M() {
  // setup
  double x;
  double y;
  double v;
  double theta;

  leftside_6M.setStopping(coast);
  rightside_6M.setStopping(coast);
  
  // left joystick controls angle robot goes towards
  // right joystick up-down controls robot speed
  while(1) {
    x = Controller1.Axis4.value() * 100 / 127;
    y = Controller1.Axis3.value() * 100 / 127;

    rightside_6M.spin(reverse, (x - y)/2, pct);
    leftside_6M.spin(fwd, (x + y)/2, pct);
    vex::this_thread::sleep_for(10);
  }
}
*/
// -- END OF 6 Motor FUNCTIONS -- //


// -- START OF TWOSTICK DRIVE -- //
void TwoStick() {
  while(true) {
    double leftaxisy = Controller1.Axis3.position();
    double rightaxisy = Controller1.Axis2.position();
      
    double leftspeed = 0.000488 * abs(leftaxisy) * abs(leftaxisy) * abs(leftaxisy);
    double rightspeed = 0.000488 * abs(rightaxisy * rightaxisy * rightaxisy); 
    leftside.setVelocity(leftspeed, percent);
    rightside.setVelocity(rightspeed, percent);
    if(leftaxisy > 0) {
      leftside.spin(forward);
    }
    else if(leftaxisy < 0) {
      leftside.spin(reverse);
    }
    if(rightaxisy > 0) {
      rightside.spin(forward);
    }
    else if(rightaxisy < 0) {
      rightside.spin(reverse);
    }

    if(Controller1.Axis1.position() == 0 && leftaxisy == 0 && rightaxisy == 0 && Controller1.Axis4.position() == 0) {
      drivemotors.stop(brake);
    }
  }
  vex::this_thread::sleep_for(10);
 }
// -- END OF TWOSTICK DRIVE -- //

// -- START OF INTAKE FUNCTIONS -- //
void ToggleIntake() {
  if(intake.velocity(pct) != 0) {
    intake.stop(coast);
  }
  else {
    intake.spin(fwd, intakespeed, pct);
  }
}

// -- END OF INTAKE FUNCTIONS -- //

// -- START OF FOURBAR FUNCTIONS -- //
void ControlFourbar() {
  while(true) {
    if(Controller1.ButtonL1.pressing()) {
      fourbar.spin(forward, fourbarspeed, percent);
    }
    else if(Controller1.ButtonL2.pressing()) {
      fourbar.spin(reverse, fourbarspeed, percent);
    }
    else {
      fourbar.stop(hold);
      //fourbar.setPosition(217, degrees);
    }
    vex::this_thread::sleep_for(10);
  }
}
// -- END OF FOURBAR FUNCTIONS -- //

// -- START OF TWOBAR FUNCTIONS -- //
void ControlTwobar() {
  while(true) {
    if(Controller1.ButtonR1.pressing()) {
      twobar.spin(reverse, twobarspeed, percent);
    }
    else if(Controller1.ButtonR2.pressing()) {
      twobar.spin(forward, twobarspeed, percent);
    }
    else {
      twobar.stop(hold);
    }
    vex::this_thread::sleep_for(10);
  }
}
// -- END OF TWOBAR FUNCTIONS -- //

// -- START OF FRONTCLAMP FUNCTIONS -- //
void ToggleFrontclamp() {
  front.set(!front.value());  // set front clamp to opposite current state
}
// -- END OF FRONTCLAMP FUNCTIONS -- //

// -- START OF BACKCLAMP FUNCTIONS -- //
void ToggleBackclamp() {
  // modified to just be X button
  // i asked uddalak in discord vc lol
  down_clamp.set(!down_clamp.value());
  wait(200, msec);
  ring_clamp.set(!ring_clamp.value());
}

void ResetBackclamp() {
  down_clamp.set(true);
  ring_clamp.set(true);
}
// -- END OF BACKCLAMP FUNCTIONS -- //