#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "WPILib.h"
#include "Defines.h"

#define GLOBAL_JLEFT_PORT	 (1)
#define GLOBAL_JRIGHT_PORT	 (2)
#define GLOBAL_JFAKEA_PORT	 (3)
#define GLOBAL_JFAKEB_PORT	 (4)

/* Global
 * ======
 * 
 * Variables that will be used across tasks are held here!
 * Global is in itself a task so that it constantly is fed the new values
 * This eliminates the need to constantly be passing copies of objects
 * around, thus quickening code!
 * 
 * Stuff located here:
 * 		- Joysticks
 * 		- Robot Status (disabled, operator, etc)
 * 		- Sensor Values (eventually)
 * 
 */

class Global {
private:
	// the instance
	static Global *myself;
	
	Joystick *jLeft, *jRight, *jFakeA, *jFakeB;

	DriverStationEnhancedIO *ds;

public:
	Global(void);
	
	Joystick* GetLeftJoystick();
	Joystick* GetRightJoystick();
	Joystick* GetFakeAJoystick();
	Joystick* GetFakeBJoystick();	

	// this is how tasks get access to the variables
	static Global *GetInstance();
};

#endif

