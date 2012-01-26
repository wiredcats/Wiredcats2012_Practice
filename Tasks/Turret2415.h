#ifndef TURRET2415_H_
#define TURRET2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

#define WAIT_FOR_INPUT (10)

class Turret2415 : public Task2415 {
private:
	Global *global;
	
	CANJaguar *jagTurret;
	
	Joystick *stickR;
		
public:
	Turret2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};

#endif

