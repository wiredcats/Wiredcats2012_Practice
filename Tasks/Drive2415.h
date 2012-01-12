#ifndef DRIVE2415_H_
#define DRIVE2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

#define NORMAL_JOYSTICK (10)
#define GO_STRAIGHT (20)
#define MOVE_BACK (30)
#define STOP_BOT (40)

const float STRAIGHT_SPEED = 0.35;

class Drive2415 : public Task2415 {
private:
	Global *global;

	CANJaguar *jagLeftU, *jagLeftD, *jagRightU, *jagRightD;

	Joystick *stickL, *stickR;

public:
	Drive2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};

#endif

