/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       auton_run.cpp                                             */
/*    Author:       Chloe Dimmmck, Diren Gomez                                */
/*    Created:      Thu Sep 26 2018                                           */
/*    Description:  Auton runs yay                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "math.h"
#include "robot-config.h"
#include "robot-autonomous.h"
using namespace vex;

// -- START OF GOAL PATHS -- //
void middle_yellow(void) {
  y_direction(1.68, 60);   //move forward
  arc_turn(1/2, 45, true, 60);   //turn to align bot to goal 
  front.set(true);   //clamp down, pick up goal
}

void right_yellow(void) { 
  y_direction(4.18, 60);   //forward
  front.set(true);   //clamp down, pick up yellow goal
}

void left_yellow(void) {
  y_direction(3.8, 60);   //forward
  arc_turn(1/5, -22, true, 60);   //turn to align
  y_direction(1, 60);
  front.set(true);   //clamp down, pick up yellow goal
}
// -- END OF GOAL PATHS -- //


// -- START OF RUNS -- //
void white_run(void) {
  right_yellow();   //earlier function
  arc_turn_ease(2/2.5, 24, false, 60);   //back up to blue goal
  back_claw_pickup();   //pick up blue goal
}

void blue_run(void) {
  left_yellow();   //earlier function
  wait(20, msec);   //wait to ensure it clmaped properly
  y_direction(-1.5, 60);   //reverse
  normal_turning(25, 45);   //spot turn
}
// -- END OF RUNS PATHS -- //
