#ifndef WIREDCATS2415_H_
#define WIREDCATS2415_H_

#include "WPILib.h"
#include "Task2415.h"
#include "Global.h"

class Wiredcats2415 : public SimpleRobot {
private:

public:
	Wiredcats2415(void);
	
	void Autonomous();
	void OperatorControl();
};

#endif

