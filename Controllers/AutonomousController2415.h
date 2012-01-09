#ifndef AUTONOMOUSCONTROLLER2415_H_
#define AUTONOMOUSCONTROLLER2415_H_

#include "WPILib.h"

#include "../Tasks/Drive2415.h"
#include "../Tasks/Lift2415.h"
#include "ScoreController.h"

#include "../Task2415.h"
#include "../Global.h"

#define FOLLOW_LINE (10)
#define TURN_SOFT_TO_LINE (20)
#define TURN_HARD_TO_LINE (30)
#define LIFT_ELEVATOR (40)
#define MOVE_TO_AUTO_POSITION (50)
#define AUTO_SCORE_AUTO (60)
#define CHILL (70)
#define STOP_BOT_AUTO (80)
#define MOVE_BACKWARDS (90)
#define FORWARD (100)
#define RELEASE (110)
#define BRING_ARM_DOWN (120)
#define MOVE_BACK_TWO (130)
#define ARM_DOWN (140)

const float AUTO2415_SOFT_TURN_PERIOD = 1.0;

class AutonomousController2415 : public Task2415 {
private:
	Global *global;

	DigitalInput *psLeft, *psMid, *psRight;

	Timer *turnTimer, *stopTimer, *backTimer, *forTimer, *gripTimer, *hardTimer;

	Task2415 *drive, *lift, *scoreController, *gripper, *arm;

public:
	AutonomousController2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};
#endif

