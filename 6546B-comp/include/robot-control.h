using namespace vex;

// tasks (run in background)
extern void ControlDrivetrain(void);
extern void ControlFourbar(void);
extern void ControlTwobar(void);

// functions (run on button press)
extern void ToggleIntake(void);
extern void ToggleFrontclamp(void);
extern void ToggleBackclamp(void);
extern void ResetBackclamp(void);
extern void ToggleRingclamp(void);