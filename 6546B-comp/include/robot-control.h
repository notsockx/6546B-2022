using namespace vex;

// tasks (run in background)
extern void ControlDrivetrain(void);
extern void UddDrivetrain(void);
extern void SumedhDrivetrain(void);
extern void temp_monitor(void);
// extern void ControlDrivetrain_6M(void);
extern void ControlFourbar(void);
extern void ControlTwobar(void);
extern void TwoStick(void);

// functions (run on button press)
extern void ToggleIntake(void);
extern void ToggleFrontclamp(void);
extern void ToggleBackclamp(void);
extern void ResetBackclamp(void);
