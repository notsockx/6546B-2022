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
#include "robot-config.h"
using namespace vex;

// -- START OF DRIVETRAIN FUNCTIONS -- //
void ControlDrivetrain() {
  // setup
  double x;
  double y;
  double v;
  double theta;
  
  while(1) {
    // grab joystick positions
    x = Controller1.Axis4.value();
    y = Controller1.Axis3.value();

    // calculate theta
    if(x == 0) { theta = 0; }
    else if(x < 0) { theta = M_PI/2 + atan2,y,x); }
    theta = M_PI/2 - atan2(y,x);

    // calculate target velocity
    v = sqrt(pow(x, 2) + pow(y, 2));

    // scale velocity down so range is 0 - 100
    if(v > 100) { v = 100; }

    // check if velocity needs to be positive or negative
    if(y<0) { v = -v; }

    // right stick as velocity
    //v = Controller1.Axis2.value() * 100./127.;

    // set motor speed
    if(x >= 0 ) {  // if turning right
      leftside.spin(fwd, v, pct);
      rightside.spin(fwd, (-2*v)/(M_PI) * theta + v, pct);
    }
    else {  // if turning left
      leftside.spin(fwd, (2*v)/(M_PI) * theta + v, pct);
      rightside.spin(fwd, v, pct);
    }
    vex::this_thread::sleep_for(100);
  }
}
// -- END OF DRIVETRAIN FUNCTIONS -- //

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
  ring_clamp.set(down_clamp.value());
}

void ResetBackclamp() {
  down_clamp.set(true);
  ring_clamp.set(true);
}
// -- END OF BACKCLAMP FUNCTIONS -- //

// -- START OF RINGCLAMP FUNCTIONS -- //
void ToggleRingclamp() {
  ring_branch.set(!ring_branch);
}
// -- END OF RINGCLAMP FUNCTIONS -- //
