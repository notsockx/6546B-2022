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
#include "robot-config.h"

using namespace vex;

competition Competition;

void y_direction(double rot) {
 
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
  while (1) {
  double average = abs(rotationLeft.position(turns) + rotationRight.position(turns))/2;
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

void pre_auton(void) {
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
  ring_clamp.set(false);
  down_clamp.set(false);
  ring_branch.set(false);
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  //white
  y_direction(0.5);
  twobar.spinFor(forward, 1, turns);
  intake.spin(forward);
  y_direction(2);
}

void usercontrol(void) {
  int counter = 0;
  bool pressed = false;
  bool released = false;
  bool on = false;

  bool openBranch = false;
  int ring_counter = 0; 

  
  intake.setVelocity(40, percent);
  fourbar.setVelocity(70, percent);
  // rotationRight.setPosition(0, degrees);
  
  rotationBar.setPosition(0, degrees);
  // User control code here, inside the loop
  while (1) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    double leftaxisx = Controller1.Axis4.position();
    double leftaxisy = Controller1.Axis3.position();
    double rightaxisx = Controller1.Axis1.position();
    double rightaxisy = Controller1.Axis2.position();
    
    double leftspeed = 0.000488 * abs(leftaxisy) * abs(leftaxisy) * abs(leftaxisy);
    double rightspeed = (sqrt((rightaxisx * rightaxisx) + (rightaxisy * rightaxisy)))/4;
  
    if(leftaxisy != 0) {
      leftside.setVelocity(leftspeed, percent);
      rightside.setVelocity(leftspeed,percent);
      if(leftaxisy > 0) {
        leftside.spin(forward);
        rightside.spin(forward);
      }
      else if(leftaxisy < 0) {
        leftside.spin(reverse);
        rightside.spin(reverse);
      }
    }
    if(rightaxisx != 0) {
      leftside.setVelocity(rightspeed, percent);
      rightside.setVelocity(rightspeed,percent);
      if(rightaxisx > 0) {
      leftside.spin(forward);
      rightside.spin(reverse);
     }
     else if(rightaxisx < 0) {
      leftside.spin(reverse);
      rightside.spin(forward);
    }
    }
  
    else if(rightaxisx < 0) {
      leftside.spin(reverse);
      rightside.spin(forward);
    }

    if(Controller1.Axis2.position() == 0  && Controller1.Axis1.position() == 0 && Controller1.Axis3.position() == 0 && Controller1.Axis4.position() == 0) {
      rightside.stop(brake);
      leftside.stop(brake);
    }

    if(Controller1.ButtonRight.pressing() == false && counter != 0) {
      released = true;
      pressed = false;
      counter = 0;
      if(on == true) {
        on = false;
      }
      else if(on == false) {
        on = true;
      }
    }
    else if(Controller1.ButtonRight.pressing()) {
      counter = 1;
      pressed = true;
      released = false;
    }
    
    if(on == false) {
      intake.stop();
    }
    else if(on == true) {
      intake.setVelocity(40, percent);
      intake.spin(forward);
    }

    //4bar
    if(Controller1.ButtonL1.pressing()) {
      fourbar.spin(forward);
    }
    else if(Controller1.ButtonL2.pressing()) {
      fourbar.spin(reverse);
    }
    else {
      fourbar.stop(brake);
      //fourbar.setPosition(217, degrees);
    }

    //2bar
    twobar.setVelocity(40, percent);
    if(Controller1.ButtonR1.pressing()) {
      twobar.spin(reverse);
    }
    else if(Controller1.ButtonR2.pressing()) {
      twobar.spin(forward);
    }
    else {
      twobar.stop(brake);
    }

    //frontclamp
    if(Controller1.ButtonUp.pressing()) {
      front.set(true);
    }
    else if(Controller1.ButtonDown.pressing()) {
      front.set(false);
    }

    //backclamp
    if(Controller1.ButtonB.pressing()) {
      down_clamp.set(false);
      wait(500, msec);
      ring_clamp.set(true);
    }
    else if(Controller1.ButtonX.pressing()) {
      ring_clamp.set(false);
      wait(300, msec);
      down_clamp.set(true);
    }
  
    //ringstick
    if(Controller1.ButtonA.pressing() == false && ring_counter != 0) {
      ring_counter = 0;
      if(openBranch == false) {
        openBranch = true;
      }
      else if(openBranch == true) {
        openBranch = false;
      }
    }
    else if(Controller1.ButtonA.pressing()) {
      ring_counter = 1;
    }
    if(openBranch == false) {
        ring_branch.set(false);
      }
      else if(openBranch == true) {
        ring_branch.set(true);
      }

    //ringclamp intke position
    if(Controller1.ButtonLeft.pressing()) {
      down_clamp.set(true);
      ring_clamp.set(true);
    }

    //rotationbar
    if(Controller1.ButtonY.pressing()) {
      double movement = (-1*rotationBar.position(degrees)) + 5;
      if(movement > 5) {
        fourbar.spinFor(forward, movement, degrees);
        fourbar.stop(brake);
      }
      else if(movement < 5) {
        fourbar.spinFor(reverse, abs(movement), degrees);
        fourbar.stop(brake);
      }
    }

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
