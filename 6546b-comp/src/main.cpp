/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Chloe Dimmock, Emilio Orcullo                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Team 6546B main competition code                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// twobar               motor         6               
// vision7              vision        7               
// rotationRight        rotation      8               
// rotationLeft         rotation      12              
// inertial13           inertial      13              
// GPS18                gps           18              
// intake          .i,anmrfstkiesaftrv gm vp     motor         19              
// front                digital_out   B               
// down_clamp           digital_out   C               
// ring_clamp           digital_out   D               
// ring_branch          digital_out   A               
// Motor16              motor         16              
// Motor17              motor         17              
// rotationBar          rotation      11              
// Motor14              motor         14              
// Motor15              motor         15              
// Motor9               motor         9               
// Motor10              motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "math.h"
#include "robot-control.h"
#include "robot-autonomous.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // set positions to zero
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
  inertial13.setHeading(0, degrees);

  // reset pneumatics
  ring_clamp.set(false);
  down_clamp.set(false);
  ring_branch.set(false);
}

void autonomous(void) {
  // white route
  intake.spin(forward);
  wait(1, sec);
  // need to test with easing
  y_direction_ease(2.5, 60);
  // need to test easing
  arc_turn_ease(2, 45, true, 70);
  // need to test as new function
  y_direction(-2.5);
  //goal_align(true, YELLOW_GOAL);
}

void usercontrol(void) {
  // start threads
  vex::thread a(ControlDrivetrain);
  //vex::thread a(TwoStick);
  vex::thread b(ControlFourbar);
  vex::thread c(ControlTwobar);

  // set up callbacks for controller buttons
  //Controller1.ButtonUp.pressed(toggleIntakeSpeed);
  Controller1.ButtonRight.pressed(ToggleIntake);
  Controller1.ButtonDown.pressed(ToggleFrontclamp);
  Controller1.ButtonLeft.pressed(ResetBackclamp); 
  //Controller1.ButtonX.pressed();
  Controller1.ButtonA.pressed(ToggleRingclamp);
  Controller1.ButtonB.pressed(ToggleBackclamp);
  Controller1.ButtonY.pressed(ResetBackclamp);

  while (true) {
    vex::this_thread::sleep_for(10);  // dont hog cpu
  }
}

// -- DO NOT CHANGE -- //
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
