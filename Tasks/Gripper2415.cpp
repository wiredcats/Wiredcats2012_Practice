#include "Gripper2415.h"

Gripper2415::Gripper2415(void) {
	global = Global::GetInstance();
	jagGripper = new CANJaguar(10);

	stickL = global->GetLeftJoystick();
	stickR = global->GetRightJoystick();

	botLS = new DigitalInput(10);

	taskState = WAIT_FOR_GRIP_INPUT;

	Start("gripper2415");
}

int Gripper2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main\n", taskName);
	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || STATUS_AUTO) {
			switch (taskState) {
				case WAIT_FOR_GRIP_INPUT:
					if (stickL->GetRawButton(2)) SyncMotorGrip(1.0);
					else 			     SyncMotorGrip(-1.0);
					break;
				
				case DELAY_GRIP_MOTOR:
					SyncMotorGrip(0.0);
					break;

				case SCORE_RUN_BACK:
					SyncMotorGrip(0.5);
					break;
			}
		}
		SwapAndWait();
	}

	return 0;
}

void Gripper2415::SyncMotorGrip(float speed) {
	if (speed <= 0 && !botLS->Get()) speed = 0;

	jagGripper->Set(speed);
}
