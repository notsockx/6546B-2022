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
    // scale axis 3 + 4 from -100 to 100 to convert to pct
    vDrive = Controller1.Axis3.value() * 100/127;
    vTurn = Controller1.Axis4.value() * 100/127;
    vTarget = sqrt(pow(vDrive, 2) + pow(vTurn, 2));

    if(vDrive > 0) {
      rightside.spin(fwd, (vDrive - vTurn)/2, pct);
      leftside.spin(fwd, (vDrive + vTurn)/2, pct);
    }
    else {
      rightside.spin(fwd, (vDrive + vTurn)/2, pct);
      leftside.spin(fwd, (vDrive - vTurn)/2, pct);
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
    intake.spin(fwd, 40, pct);
  }
}

// -- END OF INTAKE FUNCTIONS -- //

// -- START OF FOURBAR FUNCTIONS -- //
void ControlFourbar() {
  while(true) {
    if(Controller1.ButtonL1.pressing()) {
      fourbar.spin(forward, 70, percent);
    }
    else if(Controller1.ButtonL2.pressing()) {
      fourbar.spin(reverse, 70, percent);
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
      twobar.spin(reverse, 40, percent);
    }
    else if(Controller1.ButtonR2.pressing()) {
      twobar.spin(forward, 40, percent);
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
