#include "Global.h"

Global *Global::myself = 0;

Global::Global(void) {
	static bool alreadyRun = false;
	
	if (!alreadyRun) {
		jLeft  = new Joystick(GLOBAL_JLEFT_PORT);
		jRight = new Joystick(GLOBAL_JRIGHT_PORT);
		jFakeA = new Joystick(GLOBAL_JFAKEA_PORT);
		jFakeB = new Joystick(GLOBAL_JFAKEB_PORT);

		myself = this;
	
		alreadyRun = true;
	}

	printf("instantiated global\n"); 
}

Joystick* Global::GetLeftJoystick()  { return jLeft;  }
Joystick* Global::GetRightJoystick() { return jRight; }
Joystick* Global::GetFakeAJoystick() { return jFakeA; }
Joystick* Global::GetFakeBJoystick() { return jFakeB; }	

Global* Global::GetInstance() {
	return myself;
}

