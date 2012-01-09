#include "Deployment2415.h"

Deployment2415::Deployment2415(void) {
	global = Global::GetInstance();

	swingArmA = new Solenoid(8,5);
	swingArmB = new Solenoid(8,6);
	shootMinibotA = new Solenoid(8,7);
	shootMinibotB = new Solenoid(8,8);

	stickFB = global->GetFakeBJoystick();
	
	Start("deployment2415");
}

int Deployment2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main", taskName);

	bool order = false;

	swingArmA->Set(true);
	swingArmB->Set(false);
	shootMinibotA->Set(true);
	shootMinibotB->Set(false);	

	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP) {
			if(stickFB->GetRawButton(1)) {
				swingArmA->Set(false);
				swingArmB->Set(true);
				order = true;
			}
			if(stickFB->GetRawButton(2) && order) {
				shootMinibotA->Set(false);
				shootMinibotB->Set(true);
			}
			if (stickFB->GetRawButton(4)) {
				swingArmA->Set(true);
				swingArmB->Set(false);
				shootMinibotA->Set(true);
				shootMinibotB->Set(false);	
					
			}
			SwapAndWait();
		}
	}

	return 0;
}

