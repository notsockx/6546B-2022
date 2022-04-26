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
// intake               motor         19              
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
<<<<<<< HEAD
#include "auton-run.h"
#include "brain-debug.h"
=======
>>>>>>> parent of 45b826a (auton)

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
  drivemotors.setVelocity(50, percent);
  
  ring_clamp.set(false);
  down_clamp.set(true);
}

void autonomous(void) {
<<<<<<< HEAD
  blue_run();
=======

  //snag middle goal

>>>>>>> parent of 45b826a (auton)
}

void usercontrol(void) {
  intake.setVelocity(40, percent);
  intake.spin(forward);
  // start threads
  // vex::thread a(ControlDrivetrain);
  vex::thread a(UddDrivetrain);
  // vex::thread a(SumedhDrivetrain);
  // vex::thread a(TwoStick);
  //vex::thread a(ControlDrivetrain_6M);
  vex::thread b(ControlFourbar);
  // vex::thread c(ControlTwobar);
  vex::thread c(debug_screen);

  // set up callbacks for controller buttons
  //Controller1.ButtonUp.pressed(toggleIntakeSpeed);
  Controller1.ButtonRight.pressed(ToggleIntake);
  Controller1.ButtonDown.pressed(ToggleFrontclamp);
  Controller1.ButtonLeft.pressed(ResetBackclamp); 
  //Controller1.ButtonX.pressed();
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
