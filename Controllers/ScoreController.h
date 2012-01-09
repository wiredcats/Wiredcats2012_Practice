#ifndef SCORECONTROLLER2415_H_
#define SCORECONTROLLER2415_H_

#include "WPILib.h"

#include "../Tasks/Arm2415.h"
#include "../Tasks/Gripper2415.h"
#include "../Tasks/Lift2415.h"

#include "../Task2415.h"
#include "../Global.h"

#define WAIT_FOR_SCORE_INPUT (10)
#define ARM_JUMPSTART (20)
#define DEPLOY_TUBE (30)
#define DELAY_GRIPPER (40)
#define AUTO_SCORE (50)

#define SCORE_FALL_TO_NEUTRAL (40)

const float ARM_JUMPSTART_PERIOD = 0.1;
const float DEPLOY_TUBE_PERIOD = 0.3;
const float GRIP_DELAY_PERIOD = 0.8;
const float PERCENT_DAVID_GAYNESS = 100.0;

class ScoreController2415 : public Task2415 {
private:
	Global *global;

	Task2415 *lift, *grip, *arm;

	Timer *armJumpstartTimer, *deployTimer, *gripDelayTimer;

	Joystick *stickFB, *stickL, *stickR;

public:
	ScoreController2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};

#endif

