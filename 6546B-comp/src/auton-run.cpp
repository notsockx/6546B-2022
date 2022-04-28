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
/*
paths we have so far:
white path (start right of field, get right alliance and neutral goal)
blue path (start on left of field, get left alliance and neutral goal)
left winpoint (start left, pull goal away from original place, spin intake)
right winpoint (start right, pull right goal away from og place, spin intake)
orange run (start right, get middle goal, get left allinace goal)
pink run (start right, get middle goal, get right alliance goal)
*/


// -- START OF MIDDLE GOAL PATHS -- //
void middle_yellow(void) {
  y_direction(1.68, 100);   //move forward
  arc_turn(1/2, 45, true, 70);   //turn to align bot to goal 
  y_direction(2, 100);
  front.set(true);   //clamp down, pick up goal
}

void right_yellow(void) { 
  y_direction(4.17, 100);   //forward
  front.set(true);   //clamp down, pick up yellow goal
}

void left_yellow(void) {
  auto_align(3.8, 100);   //forward
  arc_turn(1/5, -22, true, 70);   //turn to align
  y_direction(1, 60);
  y_direction(3.9, 60);   //forward
  arc_turn(1/3, -29, true, 70);   //turn to align
  front.set(true);   //clamp down, pick up yellow goal
}
// -- END OF MIDDLE GOAL PATHS -- //






// -- START OF RUNS -- //
//right yellow, then right alliance 
void white_run(void) {
  //BEGIN FACING THE MIDDLE RIGHT
  right_yellow();   //earlier function
  y_direction(-1, 100);
  arc_turn(1/2, 34, true, 60);   //turn to align with goal
  wait(26, msec);
  drivemotors.stop(coast);
  y_direction(-2.5, 100);   //reverse into goal
  back_goal_pickup();   //pick up alliance goal
  wait(100, msec);   //ensure goal is picekd up
  y_direction(1, 100);   //forward to get goal out of alliance line
  arc_turn(1, -20, true, 60);   //turn to face the donuts
  fourbar.spinFor(forward, 0.5, turns);   //lift the lift to get the donuts
  intake.setVelocity(175, rpm);   //speed for donuts
  intake.spin(forward);   //take the donuts
  y_direction(1, 100);   //get the donuts slay
}

//left yellow, then left alliance
void blue_run(void) {
  //BEGIN WITH LEFT SIDE OF INTAKE AGAINST THE RIGHT SIDE OF MAT EDGE
  left_yellow();   //earlier function
  wait(20, msec);   //wait to ensure it clmaped properly
  y_direction(-1.5, 60);   //reverse
  arc_turn(-1, 90, false, 70);   //spot turn
  y_direction(2, 60);   //reverse into the goal, yass slay.
  back_goal_pickup();   //pick the goal up
  intake.setVelocity(175, percent);
  intake.spin(forward);   //spin the preload
  arc_turn(1/2, -90, true, 70);   //turn around (just in case it gets us a winpoint)
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

//start right, get middle goal then get left alliance goal
void orange_run(void) {
  //START WITH BOT RIGHT EDGE ALIGNED WITH MAT EDGe
  middle_yellow();   //earlier function
  y_direction(-1, 100);   //reverse 
  arc_turn(-1, -90, false, 70);   //spot turn, to align with middle donuts (back is supposed to align)
  y_direction(-3, 100);   //reverse into donuts, end up near goal
  //NOT DONEEE AHHHHH
}

//start on the right, get the middle goal, then get the right alliance goal 
void pink_run(void) {
  middle_yellow();   //earlier function
  y_direction(-2, 100);   //reverse to get away from opponent
  arc_turn(1/2, 70, true, 80);   //turn to align with right alliance goal
  y_direction(-2, 100);   //reverse into the goal
  back_goal_pickup();   //pick up the goal
  wait(200, msec);
  y_direction(1.4, 100);   //forward, to get away from alliange line
  intake.setVelocity(175, rpm);
  intake.spin(forward);   //get the pre-load donuts into goal base.
}
// -- END OF RUNS PATHS -- //
