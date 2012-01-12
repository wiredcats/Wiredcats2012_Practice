#include "Drive2415.h"

Drive2415::Drive2415(void) {
	global = Global::GetInstance();

	jagLeftU = new CANJaguar(3);
	jagLeftD = new CANJaguar(9);
	jagRightU = new CANJaguar(7);
	jagRightD = new CANJaguar(8);

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
					jagLeftU->Set(-stickL->GetY());
					jagLeftD->Set(-stickL->GetY());
					jagRightU->Set(stickR->GetY());
					jagRightD->Set(stickR->GetY());
					break;
				case GO_STRAIGHT:
					jagLeftU->Set(STRAIGHT_SPEED);
					jagLeftD->Set(STRAIGHT_SPEED);
					jagRightU->Set(STRAIGHT_SPEED);
					jagRightD->Set(STRAIGHT_SPEED);
					break;
				case MOVE_BACK:
					jagLeftU->Set(STRAIGHT_SPEED);
					jagLeftD->Set(STRAIGHT_SPEED);
					jagRightU->Set(STRAIGHT_SPEED);
					jagRightD->Set(STRAIGHT_SPEED);
					break;
				default:
					jagLeftU->Set(0.0);
					jagRightU->Set(0.0);
					jagLeftD->Set(0.0);
					jagRightD->Set(0.0);
					break;
			}
		}

		SwapAndWait();
	}

	return 0;
}

