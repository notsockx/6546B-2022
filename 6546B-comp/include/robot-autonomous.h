using namespace vex;

// -- START OF CONSTANTS -- //
extern double second_stage_goal_distance();
extern double rotation_value;
// -- END OF CONSTANTS -- //

// -- START OF MOVEMENT -- //
extern void y_direction(double);
extern void y_direction_ease(double, double);
// -- END OF BACKCLAMP FUNCTIONS -- //

// -- START OF WHEEL PIVOT -- //
extern void wheel_pivot(double, double, bool, double);
// -- END OF WHEEL PIVOT -- //

// -- START OF NORMAL TURNING -- //
extern void normal_turning(double);
// -- END OF NORMAL TURNING -- //

// -- START OF VISION SENSOR SHENAIGAINS -- //
extern void goal_align(bool, vex::vision::signature);
// -- END OF VISION SENSOR SHENAIGAINS -- //

// -- START OF ARC TURN -- //
extern void arc_turn_ease(double, double, bool, double);
extern void arc_turn(double, double, bool, double);
// -- END OF ARC TURN -- //