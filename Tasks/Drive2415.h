#ifndef DRIVE2415_H_
#define DRIVE2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

#define GO_STRAIGHT (10)
#define TURN_SOFT_RIGHT_TO_LINE (20)
#define TURN_SOFT_LEFT_TO_LINE (30)
#define TURN_HARD_RIGHT_TO_LINE (40)
#define TURN_HARD_LEFT_TO_LINE (50)
#define STOP_BOT (60)
#define MOVE_BACK (70)

const float AUTO_STRAIGHT_SPEED = 0.7;
const float AUTO_TURN_SPEED = 0.5;

class Drive2415 : public Task2415 {
private:
	Global *global;

	CANJaguar *jagLeftU, *jagLeftD, *jagRightU, *jagRightD;
	Solenoid *solA, *solB;

	Relay *lightsA, *lightsB;

	Joystick *stickL, *stickR;

	Gyro *gyro;

public:
	Drive2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};

#endif

