using namespace vex;
using signature = vision::signature;

// user variables
extern double fourbarspeed;

// basic vex devices
extern brain Brain;
extern controller Controller1;

// motor groups
extern motor_group fourbar;
extern motor_group leftside;
extern motor_group rightside;
extern motor_group drivemotors;

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