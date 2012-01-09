#ifndef LIFT2415_H_
#define LIFT2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

#define LIFT2415_JAGLIFTA_PORT (5)
#define LIFT2415_JAGLIFTB_PORT (2)
#define LIFT2415_JAGLIFTC_PORT (6)

#define LIFT2415_ENCODER_TOP_LOW_VALUE (1350)
#define LIFT2415_ENCODER_MID_LOW_VALUE (400)
#define LIFT2415_ENCODER_BOT_LOW_VALUE (0)
#define LIFT2415_ENCODER_TOP_HGH_VALUE (1630)
#define LIFT2415_ENCODER_MID_HGH_VALUE (550)
#define LIFT2415_ENCODER_BOT_HGH_VALUE (0)

const float LIFT2415_LOW_LIFT_SPEED = 0.9;
const float LIFT2415_MAX_LIFT_SPEED_UP = 1.0;
const float LIFT2415_MAX_LIFT_SPEED_DOWN = 0.70;
#define LIFT2415_DELTARAMP (450)

const float LIFT2415_SCORE_DROP_SPEED = 0.3;

#define WAIT_FOR_INPUT (20)
#define RUN_RAMP (30)
#define SCORE_DROP_LIFT (40)
#define MOVE_TO_AUTO_POSITION (50)
#define MOVE_TO_GROUND_POSITION (60)

const float LIFT2415_MANUAL_SPEED_UP = 1.0;
const float LIFT2415_MANUAL_SPEED_DOWN = 0.75;

class Lift2415 : public Task2415 {
private:
	Global *global;

	CANJaguar *jagLiftA, *jagLiftB, *jagLiftC;
	Encoder *encoder;

	Joystick *stickL, *stickR, *stickFA, *stickFB;

public:
	Lift2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
	
	void SyncMotorLift(float speed);
	bool PositionButtonPressed();
	float RampMotor(float x, float initial, float goal, float lowSpeed, float maxSpeed, float deltaValue);
};

#endif

