/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
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

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

//functions

void y_direction(double rot) {
  motor_group drivemotors(Motor9, Motor10, Motor14, Motor15);
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
//set veloity = average - degree if velocity = 0, brake.

//functions

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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  //white
  y_direction(0.5);
  twobar.spinFor(forward, 1, turns);
  intake.spin(forward);
  y_direction(2);
  
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
//void intakeOn(bool on) {
    // if(on == true) {
    //   intake.setVelocity(40, percent);
    //   intake.spin(forward);
    // }
    // else if(on == false) {
    //   intake.stop();
    // }
//}

void usercontrol(void) {
  int counter = 0;
  bool pressed = false;
  bool released = false;
  bool on = false;

  bool openBranch = false;
  int ring_counter = 0; 

  motor_group fourbar(Motor16, Motor17);
  intake.setVelocity(40, percent);
  fourbar.setVelocity(70, percent);
  // rotationRight.setPosition(0, degrees);
  motor_group leftside(Motor14, Motor15);
  motor_group rightside(Motor9, Motor10);
  rotationBar.setPosition(0, degrees);
  // User control code here, inside the loop
  while (1) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    // Brain.Screen.print(rotationRight.position(degrees));
    double leftaxisx = Controller1.Axis4.position();
    double leftaxisy = Controller1.Axis3.position();
    double rightaxisx = Controller1.Axis1.position();
    double rightaxisy = Controller1.Axis2.position();

    // double left_hyp = sqrt((leftaxisx * leftaxisx) + (leftaxisy * leftaxisy));
    // double right_hyp = sqrt((rightaxisx * rightaxisx) + (rightaxisy * rightaxisy));
    
    double leftspeed = 0.000488 * abs(leftaxisy) * abs(leftaxisy) * abs(leftaxisy);
    double rightspeed = (sqrt((rightaxisx * rightaxisx) + (rightaxisy * rightaxisy)))/4;
    // double lSpeed = leftaxisy + rightaxisx;
    // double rSpeed = leftaxisy - rightaxisx;


    // leftside.setVelocity(leftspeed, percent);
    // rightside.setVelocity(rightspeed, percent);

    //drivebase
    // if(Controller1.Axis3.position() > 0) {
    //   leftside.spin(forward);
    // }
    // else if(Controller1.Axis3.position() < 0) {
    //   leftside.spin(reverse);
    // }

    // if(Controller1.Axis2.position() > 0) {
    //   rightside.spin(forward);
    // }
    // else if(Controller1.Axis2.position() < 0) {
    //   rightside.spin(reverse);
    // }
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



    //intake
    // Controller1.ButtonRight.released(void(intakeOn) (on = true));

    // if button isn't pressed and counter isn't 0
      // released = true
      // pressed = false
      // counter = - val
    
    // else if button pressed
      // counter = number
      // pressed = true
      // released = false
    
    // else if button isn't pressed
      // nothing

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

    
  //   if(Controller1.ButtonRight.pressing()==true){
  //     pressed = true;
  //     released = false;
  //   }
  //   else if(Controller1.ButtonRight.pressing()==false){
  //     pressed = false;
  //     released = true;
  //   }
    
  //   if (released==true){
  //     if(on == true) {
  //     intake.spin(forward);
  //     released = false;
  //   }
  //   else if(on == false) {
  //     intake.stop();
  //     released = false;
  //   }
  // }
      

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

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
