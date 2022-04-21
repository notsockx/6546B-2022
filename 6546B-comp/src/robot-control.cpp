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
  /* 
  INTRODUCTION:
  This version of drivebase code first works by
  getting user input from the left joystick in order 
  to calculate the desired angle the driver wants
  the robot to drive in. The right joystick is then 
  used to set how fast the drivebase moves in 
  the specified direction.
  */

  // initialize variables
  int x;       // x position of right stick
  int y;       // y position of left stick
  double theta;   // drivebase desired heading
  double v;       // drivebase 'velocity' (not really though)
  double vLeft;   // left motor velocity
  double vRight;  // right motor velocity
  
  // set motor brake type
  leftside.setStopping(coast);
  rightside.setStopping(coast);

  while(1) {
    // clear screen
    Brain.Screen.clearScreen();

    // get left joystick position
    x = Controller1.Axis4.position();
    y = Controller1.Axis3.position();

    // get target velocity
    v = Controller1.Axis2.position() * 0.5 + 50;
    //v =  sqrt( pow( x, 2 ) + pow( y, 2 ));
    //if( v > 100 ) { v = 100; }

    // calculate target heading
    theta = atan2(x,y);

    // calculate drivebase velocity
    if (x==0 && y==0) { vLeft = 0; vRight = 0; }
    else if(  Controller1.Axis3.position() >= 0 ) {  // positive velocities
      if(theta >= 0) {  // quadrant 1 of joystick
        vLeft = v;
        vRight = (-2*v/M_PI_2) * theta + v;
        // print quadrant
        Brain.Screen.setCursor(5, 1);
        Brain.Screen.print("Q: 1");
      }
      else {  // quadrant 2 of joystick
        vLeft = (2*v/M_PI_2) * theta + v;
        vRight = v;
        Brain.Screen.setCursor(5, 1);
        Brain.Screen.print("Q: 2");
      }
    }
    else {  // negative velocities
      if(theta < 0) {  // quadrant 3 of joystick
        vLeft = -v;
        vRight = (2*v/M_PI_2) * (theta+M_PI_2) + v;
        Brain.Screen.setCursor(5, 1);
        Brain.Screen.print("Q: 3");
      }
      else {  // quadrant 4 of joystick
        vLeft = (-2*v/M_PI_2) * (theta-M_PI_2) + v;
        vRight = -v;
        Brain.Screen.setCursor(5, 1);
        Brain.Screen.print("Q: 4");
      }
    }

    // spin drivetrain motors
    leftside.spin(fwd, vLeft, pct);
    rightside.spin(fwd, vRight, pct);
    
    // debug
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Input");
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print("v:");
    Brain.Screen.setCursor(2, 4);
    Brain.Screen.print(v);
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.print("<:");
    Brain.Screen.setCursor(3, 4);
    Brain.Screen.print(theta*180/M_PI);
    Brain.Screen.setCursor(4, 1);
    Brain.Screen.print("<:");
    Brain.Screen.setCursor(4, 4);
    Brain.Screen.print(theta);

    Brain.Screen.setCursor(1, 11);
    Brain.Screen.print("Expected");
    Brain.Screen.setCursor(2, 11);
    Brain.Screen.print("Left:");
    Brain.Screen.setCursor(2, 17);
    Brain.Screen.print((y+x)/2);
    Brain.Screen.setCursor(3, 11);
    Brain.Screen.print("Rght:");
    Brain.Screen.setCursor(3, 17);
    Brain.Screen.print((y-x)/2);
    Brain.Screen.setCursor(4, 11);
    Brain.Screen.print("L/R:");
    Brain.Screen.setCursor(4, 17);
    Brain.Screen.print((y+x)/(y-x));

    Brain.Screen.setCursor(1, 22);
    Brain.Screen.print("Method");
    Brain.Screen.setCursor(2, 22);
    Brain.Screen.print("Left:");
    Brain.Screen.setCursor(2, 28);
    Brain.Screen.print(vLeft);
    Brain.Screen.setCursor(3, 22);
    Brain.Screen.print("Rght:");
    Brain.Screen.setCursor(3, 28);
    Brain.Screen.print(vRight);
    Brain.Screen.setCursor(4, 22);
    Brain.Screen.print("L/R:");
    Brain.Screen.setCursor(4, 28);
    Brain.Screen.print(vRight/vLeft);
    
    vex::this_thread::sleep_for(10);
  }
}
// -- END OF DRIVETRAIN FUNCTIONS -- //

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
    }
    vex::this_thread::sleep_for(100);
  }
}
// -- END OF FOURBAR FUNCTIONS -- //

// -- START OF FRONTCLAMP FUNCTIONS -- //
void ToggleFrontclamp() {
  front.set(!front.value());  // set front clamp to opposite current state
}
// -- END OF FRONTCLAMP FUNCTIONS -- //

// -- START OF BACKCLAMP FUNCTIONS -- //
void ToggleBackclamp() {
  down_clamp.set(!down_clamp.value());
  ring_clamp.set(down_clamp.value());
}

void ResetBackclamp() {
  down_clamp.set(false);
  ring_clamp.set(false);
}
// -- END OF BACKCLAMP FUNCTIONS -- //
