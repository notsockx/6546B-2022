#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor twobar = motor(PORT6, ratio18_1, false);
/*vex-vision-config:begin*/
vision vision7 = vision (PORT7, 50);
/*vex-vision-config:end*/
rotation rotationRight = rotation(PORT8, false);
rotation rotationLeft = rotation(PORT12, true);
inertial inertial13 = inertial(PORT13);
gps GPS18 = gps(PORT18, 0.00, 0.00, mm, 180);
motor intake = motor(PORT19, ratio6_1, false);
digital_out front = digital_out(Brain.ThreeWirePort.B);
digital_out down_clamp = digital_out(Brain.ThreeWirePort.C);
digital_out ring_clamp = digital_out(Brain.ThreeWirePort.D);
digital_out ring_branch = digital_out(Brain.ThreeWirePort.A);
motor Motor16 = motor(PORT16, ratio36_1, true);
motor Motor17 = motor(PORT17, ratio36_1, false);
rotation rotationBar = rotation(PORT11, false);
motor Motor14 = motor(PORT14, ratio6_1, true);
motor Motor15 = motor(PORT15, ratio6_1, true);
motor Motor9 = motor(PORT9, ratio6_1, false);
motor Motor10 = motor(PORT10, ratio6_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}