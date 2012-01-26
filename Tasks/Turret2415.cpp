#include "Turret2415.h"

Turret2415::Turret2415(void) {
	global = Global::GetInstance();
	
	jagTurret = new CANJaguar(4);
	
	stickR = global->GetRightJoystick();
		
	taskState = WAIT_FOR_INPUT;

	Start("turret2415");
}

int Turret2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main", taskName);
	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || taskStatus == STATUS_AUTO) {
			switch (taskState) {
				case WAIT_FOR_INPUT:
					if(stickR->GetTrigger()) {
						jagTurret->Set(0.1);
					} else {
						jagTurret->Set(0.0);
					}
					break;
				default:
					taskState = WAIT_FOR_INPUT;
					break;
			}
		}
		SwapAndWait();
	}

	return 0;
}

