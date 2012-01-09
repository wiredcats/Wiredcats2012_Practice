#include "Drive2415.h"

Drive2415::Drive2415(void) {
	global = Global::GetInstance();

	jagLeftU = new CANJaguar(3);
	jagLeftD = new CANJaguar(9);
	jagRightU = new CANJaguar(7);
	jagRightD = new CANJaguar(8);

	solA = new Solenoid(8, 1);
	solB = new Solenoid(8, 3);

	lightsA = new Relay(2);

	stickL = global->GetLeftJoystick();
	stickR = global->GetRightJoystick();

	gyro = new Gyro(1, 1);

	taskState = 100;

	Start("drive2415");
}

int Drive2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main\n", taskName);
	gyro->Reset();
	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP) {

			printf("%g\n", jagLeftU->Get());		
	
			lightsA->Set(Relay::kForward);

			jagLeftU->Set(-stickL->GetY());
			jagLeftD->Set(-stickL->GetY());
			jagRightU->Set(stickR->GetY());
			jagRightD->Set(stickR->GetY());

			if (stickL->GetTrigger()) {
				solA->Set(false);
				solB->Set(true);
			} else {
				solA->Set(true);
				solB->Set(false);
			}
		} else if (taskStatus == STATUS_AUTO) {
			solA->Set(true);
			solB->Set(false);

			switch (taskState) {
				case GO_STRAIGHT:
					jagLeftU->Set(AUTO_STRAIGHT_SPEED);
					jagLeftD->Set(AUTO_STRAIGHT_SPEED);
					jagRightU->Set(-AUTO_STRAIGHT_SPEED);
					jagRightD->Set(-AUTO_STRAIGHT_SPEED);
					
					break;
				
				case MOVE_BACK:
					jagLeftU->Set(-AUTO_STRAIGHT_SPEED);
					jagLeftD->Set(-AUTO_STRAIGHT_SPEED);
					jagRightU->Set(AUTO_STRAIGHT_SPEED);
					jagRightD->Set(AUTO_STRAIGHT_SPEED);

					break;
					

				case TURN_SOFT_RIGHT_TO_LINE:
					jagLeftU->Set(AUTO_TURN_SPEED);
					jagLeftD->Set(AUTO_TURN_SPEED);
					jagRightU->Set(-AUTO_TURN_SPEED - 0.15);
					jagRightD->Set(-AUTO_TURN_SPEED - 0.15);

					break;

				case TURN_SOFT_LEFT_TO_LINE:
					jagLeftU->Set(AUTO_TURN_SPEED + 0.15);
					jagLeftD->Set(AUTO_TURN_SPEED + 0.15);
					jagRightU->Set(-AUTO_TURN_SPEED);
					jagRightD->Set(-AUTO_TURN_SPEED);

					break;
				
				case TURN_HARD_LEFT_TO_LINE:
					jagLeftU->Set(AUTO_TURN_SPEED);
					jagLeftD->Set(AUTO_TURN_SPEED);
					jagRightU->Set(AUTO_TURN_SPEED);
					jagRightD->Set(AUTO_TURN_SPEED);
					break;

				case TURN_HARD_RIGHT_TO_LINE:
					jagLeftU->Set(-AUTO_TURN_SPEED);
					jagLeftD->Set(-AUTO_TURN_SPEED);
					jagRightU->Set(-AUTO_TURN_SPEED);
					jagRightD->Set(-AUTO_TURN_SPEED);

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

