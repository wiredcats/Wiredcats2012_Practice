#include "Drive2415.h"

Drive2415::Drive2415(void) {
	global = Global::GetInstance();

	jagLeft = new Jaguar(1);
	jagRight = new Jaguar(2);

	stickL = global->GetLeftJoystick();
	stickR = global->GetRightJoystick();

	taskState = NORMAL_JOYSTICK;

	Start("drive2415");
}

int Drive2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main\n", taskName);
	while (keepTaskAlive) {
		if (taskStatus == STATUS_AUTO || taskStatus == STATUS_TELEOP) {
			switch (taskState) {
				case NORMAL_JOYSTICK:
					jagLeft->Set(stickL->GetY());
					jagRight->Set(stickR->GetY());
					break;
				case GO_STRAIGHT:
					jagLeft->Set(STRAIGHT_SPEED);
					jagRight->Set(STRAIGHT_SPEED);
					break;
				case MOVE_BACK:
					jagLeft->Set(STRAIGHT_SPEED);
					jagRight->Set(STRAIGHT_SPEED);
					break;
				case GO_BACKDRIVE_STRAIGHT:
					jagLeft->Set(BACKDRIVE_STRAIGHT_SPEED);
					jagRight->Set(BACKDRIVE_STRAIGHT_SPEED);
					break;
				case MOVE_BACKDRIVE_BACK:
					jagLeft->Set(BACKDRIVE_STRAIGHT_SPEED);
					jagRight->Set(BACKDRIVE_STRAIGHT_SPEED);
					break;
				default:
					jagLeft->Set(0.0);
					jagRight->Set(0.0);
					break;
			}
		}

		SwapAndWait();
	}

	return 0;
}

