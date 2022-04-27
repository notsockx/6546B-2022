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

// -- START OF MIDDLE GOAL PATHS -- //
void middle_yellow(void) {
  y_direction(1.68, 100);   //move forward
  arc_turn(1/2, 45, true, 60);   //turn to align bot to goal 
  y_direction(2, 100);
  front.set(true);   //clamp down, pick up goal
}

void right_yellow(void) { 
  y_direction(4.2, 100);   //forward
  front.set(true);   //clamp down, pick up yellow goal
}

void left_yellow(void) {
  y_direction(3.8, 100);   //forward
  arc_turn(1/5, -22, true, 60);   //turn to align
  y_direction(1, 60);
  y_direction(3.9, 60);   //forward
  arc_turn(1/3, -29, true, 60);   //turn to align
  front.set(true);   //clamp down, pick up yellow goal
}
// -- END OF MIDDLE GOAL PATHS -- //


// -- START OF RUNS -- //

//right yellow, then right alliance 
void white_run(void) {
  //BEGIN FACING THE MIDDLE RIGHT
  right_yellow();   //earlier function
  y_direction(-0.5, 100);
  arc_turn(1/2, -66, false, 60);   //back up to alliance goal
  y_direction(-1, 100);
  back_goal_pickup();   //pick up alliance goal
}

//left yellow, then left alliance
void blue_run(void) {
  //BEGIN WITH LEFT SIDE OF INTAKE AGAINST THE RIGHT SIDE OF MAT EDGE
  left_yellow();   //earlier function
  wait(20, msec);   //wait to ensure it clmaped properly
  y_direction(-1.5, 60);   //reverse
  arc_turn(1, 90, false, 70);   //spot turn
  y_direction(2, 60);   //reverse into the goal, yass slay.
}

//right alliance, then donuts
void right_winpoint(void) {
  //BEGIN WITH BACK FACING THE RIGHT ALLIANCE GOAL
  y_direction(-1.6, 80);   //drive to the alliance goal
  wait(20, msec);
  back_goal_pickup();   //clamp onto the goal
  intake.spin(forward);
  arc_turn(1, -135, true, 80);   //turn to align with the donut line
  y_direction(0.5, 80);   //spin forward to get donuts
}

//start intake, get donuts, stop intake, get goal, drop donuts into goal.
void left_winpoint(void) {
  //BEGIN WITH INTAKE ALIGNED WITH MAT EDGE
  y_direction(2.5, 100);   //forward to middle line
  arc_turn(1/2, -90, true, 60);   //turn to align with donut flower
  intake.setVelocity(50, rpm);   //slow the intake so donuts stay inside
  intake.spin(forward);   
  y_direction(2.5, 100);   //forward to get the donuts
  intake.stop(brake);   //stop intake, donuts get stuck
  y_direction(-2.7, 100);   //reverse back to original area, go a bit further
  arc_turn(1/2, 15, true, 70);   //turn to align with the goal
  y_direction(-2.6, 100);   //reverse into the goal
  back_goal_pickup();   //pick up the goal
  intake.spin(forward);   //shoot donuts into the goal
}

//start righ, get middle goal then get left alliance goal
void orange_run(void) {
  //START WITH BOT RIGHT EDGE ALIGNED WITH MAT EDGe
  middle_yellow();   //earlier function
  y_direction(-1, 100);   //reverse 
  arc_turn(1, -90, false, 70);   //spot turn, to align with middle donuts (back is supposed to align)
  y_direction(-3, 100);   //reverse into donuts, end up near goal
  //NOT DONEEE AHHHHH
}

// -- END OF RUNS PATHS -- //
