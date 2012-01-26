#ifndef AUTOTRACKER2415_H_
#define AUTOTRACKER2415_H_

#include "WPILib.h"
#include "../DashboardDataFormat.h"

#include "../Tasks/Turret2415.h"

#include "../Task2415.h"
#include "../Global.h"

class AutoTracker2415 : public Task2415 {
private:
	Global *global;
	
	Task2415 *turret;
	
	Joystick *stickFB, *stickL, *stickR;

public:
	AutoTracker2415(void);
	
	virtual int Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);
};

#endif
