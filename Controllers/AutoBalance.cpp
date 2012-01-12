#include "AutoBalance.h"

AutoBalance2415::AutoBalance2415(void) {
	global = Global::GetInstance();

	printf("stalling to allow tasks to be initialized\n");
	Wait(2.0);

	drive = Task2415::SearchForTask("drive2415");
	
	gyro = new Gyro(1,1);

	stickL = global->GetLeftJoystick();
	stickR = global->GetRightJoystick();
	stickFB = global->GetFakeBJoystick();
	
	taskState = WAIT_FOR_INPUT;

	Start("autobalance2415");
}

int AutoBalance2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	gyro->Reset();
	printf("entering %s main\n", taskName);
	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || taskStatus == STATUS_AUTO) {
			printf("%g\n", gyro->GetAngle());
			float angle = gyro->GetAngle();			
			switch (taskState) {
				case WAIT_FOR_INPUT:
					drive->SetState(NORMAL_JOYSTICK);
					if( angle > MARGIN_OF_ERROR){
						taskState = TILTED_TOWARDS_FRONT;
					}
					if (angle < -MARGIN_OF_ERROR){
						taskState = TILTED_TOWARDS_BACK;					
					}
					break;
				case TILTED_TOWARDS_FRONT:
					drive->SetState(MOVE_BACK);
					if( CheckIfBalanced(angle) ){
						taskState = WAIT_FOR_INPUT;
					}
					if ( angle < -MARGIN_OF_ERROR) {
						taskState = TILTED_TOWARDS_BACK;
					}
					break;
				case TILTED_TOWARDS_BACK:
					drive->SetState(GO_STRAIGHT);
					if( CheckIfBalanced(angle) ){
						taskState = WAIT_FOR_INPUT;
					}
					if ( angle > MARGIN_OF_ERROR) {
						taskState = TILTED_TOWARDS_FRONT;
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

bool AutoBalance2415::CheckIfBalanced(float angle) {
	return ( -MARGIN_OF_ERROR <= angle && angle <= MARGIN_OF_ERROR);
}
