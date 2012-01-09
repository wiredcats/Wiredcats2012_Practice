#ifndef DEPLOYMENT2415_H_
#define DEPLOYMENT2415_H_

#include "WPILib.h"
#include "../Task2415.h"
#include "../Global.h"

class Deployment2415 : public Task2415 {
private:
	Global *global;
	Solenoid *swingArmA, *swingArmB, *shootMinibotA, *shootMinibotB;
	Joystick *stickFB;

public:
	Deployment2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};

#endif

