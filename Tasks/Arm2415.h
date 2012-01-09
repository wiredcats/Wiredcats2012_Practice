#ifndef ARM2415_H_
#define ARM2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

const float ARM2415_POT_HIGH_VALUE = 0.8;
const float ARM2415_POT_LOW_VALUE = 2.2;

const float ARM2415_DELTARAMP = 0.1;

const float ARM2415_LOW_SPEED = 0.4;
const float ARM2415_MAX_SPEED = 0.9;

const float ARM2415_SCORE_FALL_SPEED = 0.4;

#define WAIT_FOR_ARM_INPUT (20)
#define RUN_ARM_RAMP (30)
#define SCORE_FALL_TO_NEUTRAL_ARM (40)
#define BACKDRIVE (50)

class Arm2415 : public Task2415 {
private:
	Global *global;
	
	CANJaguar *jagArm;

	Joystick *stickL, *stickFB;
	
	AnalogChannel *pot;
public:
	Arm2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
	float RampMotor(float x, float initial, float goal, float lowSpeed, float maxSpeed, float deltaValue);

	void SyncMotorArm(float speed);
};

#endif

