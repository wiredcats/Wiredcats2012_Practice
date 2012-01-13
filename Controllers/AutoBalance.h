#ifndef AUTOBALANCE_H_
#define AUDTOBALANCE_H_

#include "WPILib.h"

#include "../Tasks/Drive2415.h"

#include "../Task2415.h"
#include "../Global.h"

#define WAIT_FOR_INPUT (10)
#define BALANCE_LOOP (20)
#define BACKDRIVE (30)
#define STOP (40)

const float MARGIN_OF_ERROR = 8.0;
const float BACKDRIVE_PERIOD = 0.45;

class AutoBalance2415 : public Task2415 {
private:
	Global *global;

	Task2415 *drive;
	
	Gyro *gyro;
	
	Timer *backdriveTimer;
	
	Joystick *stickFB, *stickL, *stickR;

public:
	AutoBalance2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
	bool CheckIfBalanced(float angle);
};

#endif

