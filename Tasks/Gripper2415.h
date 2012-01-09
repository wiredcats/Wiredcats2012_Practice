#ifndef GRIPPER2415_H_
#define GRIPPER2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

#define WAIT_FOR_GRIP_INPUT (10)
#define SCORE_RUN_BACK (20)
#define DELAY_GRIP_MOTOR (30)

class Gripper2415 : public Task2415 {
private:
	Global *global;

	CANJaguar *jagGripper;

	DigitalInput *botLS;

	Joystick *stickL, *stickR;

public:
	Gripper2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

	void SyncMotorGrip(float speed);
};

#endif

