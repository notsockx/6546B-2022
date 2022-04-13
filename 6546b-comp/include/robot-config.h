using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor twobar;
extern signature vision7__SIG_1;
extern signature vision7__SIG_2;
extern signature vision7__SIG_3;
extern signature vision7__SIG_4;
extern signature vision7__SIG_5;
extern signature vision7__SIG_6;
extern signature vision7__SIG_7;
extern vision vision7;
extern rotation rotationRight;
extern rotation rotationLeft;
extern inertial inertial13;
extern gps GPS18;
extern motor intake;
extern digital_out front;
extern digital_out down_clamp;
extern digital_out ring_clamp;
extern digital_out ring_branch;
extern motor Motor16;
extern motor Motor17;
extern rotation rotationBar;
extern motor Motor14;
extern motor Motor15;
extern motor Motor9;
extern motor Motor10;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );