using namespace vex;
using signature = vision::signature;

// user variables
extern double intakespeed;
extern double fourbarspeed;
extern double twobarspeed;

// basic vex devices
extern brain Brain;
extern controller Controller1;

// motors
extern motor twobar;
extern motor intake;
extern motor Motor16;
extern motor Motor17;
extern motor Motor14;
extern motor Motor15;
extern motor Motor9;
extern motor Motor10;

// motor groups
extern motor_group fourbar;
extern motor_group leftside;
extern motor_group rightside;
extern motor_group drivemotors;
extern motor_group drivemotors_old;
extern motor_group rightside_old;

// digital out
extern digital_out front;
extern digital_out down_clamp;
extern digital_out ring_clamp;
extern digital_out ring_branch;

// sensors
extern vision vision7;
extern gps DriveGPS;
extern rotation rotationRight;
extern rotation rotationLeft;
extern inertial inertial13;
extern rotation rotationBar;

// functions
void vexcodeInit( void );

//6 Motor compat
/*
extern motor_group drivemotor_6M;
extern motor_group leftside_6M;
extern motor_group rightside_6M;
*/