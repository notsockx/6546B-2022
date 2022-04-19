/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       robot-autonomous.cpp                                      */
/*    Author:       Chloe Dimmmck                                             */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Autonomous methods for robot                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// setup
#include "vex.h"
#include "math.h"
#include "robot-config.h"
using namespace vex;

// define variable which notes the change in angle
double change_in_inertial;

// the constant distance whic it takes from end point to mid line
double second_stage_constant = 1.68;


//printing value of drivebase rotation sensors
double rotation_value = (rotationLeft.position(turns) + rotationRight.position(turns))/2;

// move forward / back based on rotations
void y_direction(double rot) {
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
  if(rot > 0){
    drivemotors.spin(fwd);
    waitUntil( ( ( abs(rotationLeft.position(turns)) + abs(rotationRight.position(turns)) ) / 2 ) >= rot);
    drivemotors.stop(brake);
  }
  else{
    drivemotors.spin(reverse);
    waitUntil( -( ( abs(rotationLeft.position(turns)) + abs(rotationRight.position(turns)) ) / 2 ) <= rot);
    drivemotors.stop(brake);
  }
}


// move forward / back based on velocity
void y_direction_ease(double rot, double initVelo) {
  rotationLeft.setPosition(0, turns);
  rotationRight.setPosition(0, turns);
  while (1) {
  double average = abs(int(rotationLeft.position(turns) + rotationRight.position(turns)))/2;
  double velo = (initVelo*((rot - average)/rot) + 30);
  if(velo >=100){velo = 100;}
  drivemotors.setVelocity(velo, percent);
    if(velo <= 35){
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

// pivot on oneside with easing
void arc_turn_ease(double ratio, double angel, bool directionss, double speed){
  angel = -angel;
  double initAngel = inertial13.orientation(yaw, degrees);
  double currentAngel = initAngel;
  double finalAngel = fmod((initAngel + angel), 360);
  speed = speed + 30;
  if(directionss == true){
    //fwd
    if(angel > 0){
      // right
      while(speed >= 35) {
        leftside.spin(fwd, speed, pct);
        rightside_old.spin(fwd, speed * ratio, pct);
        speed = speed * ((finalAngel - currentAngel)/finalAngel) + 30;
        if(speed >= 100) {
          speed = 100;
        }
      }
    }
    else{
      // left
      while(speed >= 35) {
        leftside.spin(fwd, speed * ratio, pct);
        rightside_old.spin(fwd, speed, pct);
        speed = speed * ((finalAngel - currentAngel)/finalAngel) + 30;
        if(speed >= 100) {
          speed = 100;
        }
      }
    }
  }
  else{
    // back
    if(angel > 0){
      // right
      while(speed >= 35) {
        leftside.spin(reverse, speed * ratio, pct);
        rightside.spin(reverse, speed, pct);
        speed = speed * ((finalAngel - currentAngel)/finalAngel) + 30;
        if(speed >= 100) {
          speed = 100;
        }
      }
    }
    else{
      // left
      while(speed >= 35) {
        leftside.spin(reverse, speed, pct);
        rightside.spin(reverse, speed * ratio, pct);
        speed = speed * ((finalAngel - currentAngel)/finalAngel) + 30;
        if(speed >= 100) {
          speed = 100;
        }
      }
    }
  }
  drivemotors.stop(brake);
}

void arc_turning_v2(double ratio, double angel, bool directions, double speed){
  angel = -angel;
  if (directions == true){
    // forward
  }

  if(directions == true) {
    if(angel > 0) {
      leftside.setVelocity(speed, percent);
      rightside.setVelocity((speed*ratio), percent);
    }
    else if(angel < 0) {
      rightside.setVelocity(speed, percent);
      leftside.setVelocity((speed*ratio), percent);
    }
  }
  else if(directions == false) {
    if(angel > 0) {
       rightside.setVelocity(-speed, percent);
       leftside.setVelocity(-(speed*ratio), percent);
    }
    else if(angel < 0) {
       leftside.setVelocity(-speed, percent);
       rightside.setVelocity(-(speed*ratio), percent);
    }
  }
  double initAngel = inertial13.orientation(yaw, degrees);
  double currentAngel = initAngel;
  double finalAngel = fmod((initAngel + angel), 360);

}


// pivot on oneside of wheel while driving
void arc_turn(double ratio, double angel, bool directions, double speed) {
  angel = -angel;
  if(directions == true) {
    if(angel > 0) {
      leftside.setVelocity(speed, percent);
      rightside.setVelocity((speed*ratio), percent);
    }
    else if(angel < 0) {
      rightside.setVelocity(speed, percent);
      leftside.setVelocity((speed*ratio), percent);
    }
  }
  else if(directions == false) {
    if(angel > 0) {
       rightside.setVelocity(-speed, percent);
       leftside.setVelocity(-(speed*ratio), percent);
    }
    else if(angel < 0) {
       leftside.setVelocity(-speed, percent);
       rightside.setVelocity(-(speed*ratio), percent);
    }
  }

  double initAngel = inertial13.orientation(yaw, degrees);
  double currentAngel = initAngel;
  double finalAngel = fmod((initAngel + angel), 360);
  while(currentAngel != finalAngel) {
    currentAngel = inertial13.orientation(yaw, degrees);
    if(initAngel > finalAngel) {
      leftside.spin(forward);
      rightside.spin(forward);
      if(currentAngel <= finalAngel) {
        drivemotors.stop(brake);
      }
    }
    else if(initAngel < finalAngel) {
      leftside.spin(forward);
      rightside.spin(reverse);
      if(currentAngel >= finalAngel) {
        drivemotors.stop(brake);
      }
    }
    else if(currentAngel == finalAngel) {
      break;
    }
  }
}

// center pivot turning
// void norm_turn(double deg){
//   double initAngel = inertial13.heading(degrees);
//   double currentAngel = initAngel;
//   double finalAngel = fmod(initAngel + deg + 360, 360);
// }

void normal_turning(double deg) {
  double initAngel = inertial13.heading(degrees);
  double currentAngel = initAngel;
  double finalAngel = fmod(abs(initAngel + deg + 360), 360);
  while(currentAngel != finalAngel) {
    currentAngel = inertial13.heading(degrees);
    //double velo = abs(finalAngel - currentAngel);
    if(initAngel > finalAngel) {
      leftside.spin(forward);
      rightside.spin(reverse);
      if(currentAngel <= finalAngel) {
        drivemotors.stop(brake);
        break;
      }
    }
    else if(initAngel < finalAngel) {
      leftside.spin(reverse);
      rightside.spin(forward);
      if(currentAngel >= finalAngel) {
        drivemotors.stop(brake);
        break;
      }
    }
  }
}

//vision alignment
void goal_align(bool side, vex::vision::signature goal_color) {
  int center = 158;
  double original_inertial = inertial13.heading(degrees);
  if(side == true){
    //forward (vision7)
    // takes "photo" of any yellow objects and locates them
    vision7.takeSnapshot(goal_color);
    if(vision7.largestObject.exists){
      while(vision7.largestObject.centerX > center){
        //turn right
        leftside.spin(forward);
        rightside.spin(reverse);
      }
      while(vision7.largestObject.centerX < center){
        // turn left
        leftside.spin(reverse);
        rightside.spin(forward);
      }
      if(vision7.largestObject.exists == center){
        // brake
        drivemotors.stop(brake);
        change_in_inertial = inertial13.heading(degrees) - original_inertial;
      }
    }
  }
  else if(side == false){
    //reverse (vision5)
    // takes "photo" of any yellow objects and locates them
    vision7.takeSnapshot(goal_color);
    if(vision7.largestObject.exists){
      while(vision7.largestObject.centerX > center){
        //turn right
        leftside.spin(reverse);
        rightside.spin(forward);
      }
      while(vision7.largestObject.centerX < center){
        // turn left
        leftside.spin(forward);
        rightside.spin(reverse);      
      }
      if(vision7.largestObject.exists == center){
        // brake
        drivemotors.stop(brake);
        change_in_inertial = inertial13.heading(degrees) - original_inertial;
      }
    }
  }
}

//distance between goal and bot
double second_stage_goal_distance(){
  return (second_stage_constant/cos(change_in_inertial));
}

// -- START OF FRONTCLAMP FUNCTIONS -- //
// void front_clamp_up() {
//   front.set(/*up*/);  // set front clamp to opposite current state
// }
// void front_clamp_down() {
//   front.set(/*down*/);  // set front clamp to opposite current state
// }
// -- END OF FRONTCLAMP FUNCTIONS -- //

// -- START OF BACKCLAMP FUNCTIONS -- //
void back_goal_pickup(){
  down_clamp.set(true);
  wait(200, msec);
  ring_clamp.set(false);
}

void back_goal_drop(){
  ring_clamp.set(true);
  wait(200, msec);
  down_clamp.set(false);
}
// -- END OF BACKCLAMP FUNCTIONS -- //