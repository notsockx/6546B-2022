using namespace vex;

extern void y_direction(double, double);
extern void wheel_pivot(double, double, bool, double);
extern void normal_turning(double);
extern void goal_align(bool, vex::vision::signature);
extern double second_stage_goal_distance();
extern double rotation_value;
extern void arc_turn_ease(double, double, bool, double);