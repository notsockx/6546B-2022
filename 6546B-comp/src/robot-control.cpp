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

// -- START OF DRIVETRAIN FUNCTIONS -- //
void ControlDrivetrain() {
  // setup
  double vDrive;
  double vTurn;
  double vTarget;
  
  while(1) {
    // calculate drive velocity by scaling axis 3 to -100% - 100%
    vDrive = Controller1.Axis3.value() * 100/127;
    // calculate turn velocity by scaling axis 4 to -100% - 100%
    vTurn = Controller1.Axis4.value() * 100/127; 
    // vTarget is just hypotenuse of vDrive and vTurn
    vTarget = sqrt(pow(vDrive, 2) + pow(vTurn, 2));

    if(vTarget > 100) { vTarget = 100; }  // set vTaget to 100 if greater than 100

    // get sign of vDrive and apply to vTarget
    vTarget = vTarget * ( int( vDrive ) / abs( int( vDrive )));

    if( vTurn >= 0 ) {
      rightside.spin(fwd, vTarget - vTurn*2, pct);
      leftside.spin(fwd, vTarget, pct);
    }
    else {
      rightside.spin(fwd, vTarget, pct);
      leftside.spin(fwd, vTarget - vTurn*2, pct);
    }
    

    vex::this_thread::sleep_for(10);
  }
}
// -- END OF DRIVETRAIN FUNCTIONS -- //

// -- START OF INTAKE FUNCTIONS -- //
void ToggleIntake() {
  if(intake.isSpinning()) {
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
  ring_clamp.set(!down_clamp.value());
}

void ResetBackclamp() {
  down_clamp.set(true);
  ring_clamp.set(true);
}
// -- END OF BACKCLAMP FUNCTIONS -- //

// -- START OF RINGCLAMP FUNCTIONS -- //
void ToggleRingclamp() {
  ring_branch.set(!ring_branch);  // pretty sure this does the exact same thing
  //bool openBranch = false;
  //int ring_counter = 0;
  //if(Controller1.ButtonA.pressing() == false && ring_counter != 0) {
  //  ring_counter = 0;
  //  openBranch = !openBranch;
  //}
  //else if(Controller1.ButtonA.pressing()) {
  //  ring_counter = 1;
  //}
  //ring_branch.set(!openBranch);
}
// -- END OF RINGCLAMP FUNCTIONS -- //
