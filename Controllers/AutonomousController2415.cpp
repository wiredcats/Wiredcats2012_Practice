#include "AutonomousController2415.h"

AutonomousController2415::AutonomousController2415(void) {
	global = Global::GetInstance();

	drive = Task2415::SearchForTask("drive2415");
	lift = Task2415::SearchForTask("lift2415");
	gripper = Task2415::SearchForTask("gripper2415");
	arm = Task2415::SearchForTask("arm2415");

	psLeft = new DigitalInput(7);
	psMid = new DigitalInput(8);
	psRight = new DigitalInput(9);

	turnTimer = new Timer();
	stopTimer = new Timer();
	backTimer = new Timer();
	gripTimer = new Timer();
	hardTimer = new Timer();

	printf("stalling to allow tasks to be initialized\n");
	Wait(1.0); 
	
	taskState = FOLLOW_LINE;

	Start("autonomouscontroller2415");
}

int AutonomousController2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {

	int left, middle, right = 0;
	bool goRight = false;

	printf("entering %s main\n", taskName);
	drive->SetState(GO_STRAIGHT);

	while (keepTaskAlive) {
		if (taskStatus == STATUS_AUTO) {
			left = psLeft->Get() ? 1 : 0;
			middle = psMid->Get() ? 1 : 0;
			right = psRight->Get() ? 1 : 0;

			printf("left: [%d] mid: [%d] right: [%d]\n", left, middle, right);

			switch (taskState) {
				case FOLLOW_LINE:
					arm->SetState(BACKDRIVE);
					if (left && middle && right) {
						drive->SetState(STOP_BOT);
						taskState = STOP_BOT_AUTO;
						stopTimer->Start();
					} else {
						if (left || right) {
							printf("found left [%d]  or right [%d]\n", left, right);
							if (goRight) {
								if (right) drive->SetState(TURN_SOFT_RIGHT_TO_LINE);
								else	   drive->SetState(TURN_SOFT_LEFT_TO_LINE);
							} else {
								if (left) drive->SetState(TURN_SOFT_LEFT_TO_LINE);
								else	  drive->SetState(TURN_SOFT_RIGHT_TO_LINE);
							}

							turnTimer->Start();
							taskState = TURN_SOFT_TO_LINE;
						}	
					}


					break;
				case TURN_SOFT_TO_LINE:
					if (middle) {
						printf("found middle\n");
						drive->SetState(GO_STRAIGHT);
						printf("found middle [%d]\n", middle); 

						turnTimer->Stop();
						turnTimer->Reset();

						taskState = FOLLOW_LINE;
					}

					if (turnTimer->HasPeriodPassed(AUTO2415_SOFT_TURN_PERIOD)) {
						printf("turning hard left [%d] or right [%d]\n", left, right);
						if (goRight) {
							if (right) drive->SetState(TURN_HARD_RIGHT_TO_LINE);
							else	   drive->SetState(TURN_HARD_LEFT_TO_LINE);
						} else {
							if (left) drive->SetState(TURN_HARD_LEFT_TO_LINE);
							else	  drive->SetState(TURN_HARD_RIGHT_TO_LINE);
						}

						hardTimer->Start();

						taskState = TURN_HARD_TO_LINE;
					}
					break;
				case TURN_HARD_TO_LINE:
					if (middle) {
						printf("found middle\n");
						drive->SetState(GO_STRAIGHT);
						printf("found middle [%d]\n", middle); 

						turnTimer->Stop();
						turnTimer->Reset();
						
						hardTimer->Stop();
						hardTimer->Reset();

						taskState = FOLLOW_LINE;
					}

					if (hardTimer->HasPeriodPassed(1.5)) {
						drive->SetState(STOP_BOT);
						arm->SetState(WAIT_FOR_ARM_INPUT);
						lift->SetState(WAIT_FOR_INPUT);
						gripper->SetState(WAIT_FOR_GRIP_INPUT);
						KillTask();
					}
					break;
				case STOP_BOT_AUTO:
					if (stopTimer->HasPeriodPassed(0.5)) {
						taskState = MOVE_BACKWARDS;
						drive->SetState(MOVE_BACK);

						stopTimer->Stop();
						stopTimer->Reset();

						backTimer->Start();
					}
				case MOVE_BACKWARDS:
					if (backTimer->HasPeriodPassed(0.3)) {
						taskState = LIFT_ELEVATOR;
						lift->SetState(MOVE_TO_AUTO_POSITION);
						drive->SetState(STOP_BOT);

						backTimer->Stop();
						backTimer->Reset();
					}
					break;
				case LIFT_ELEVATOR:
					if (lift->StateComplete()) {
						forTimer->Start();
						taskState = FORWARD;
						drive->SetState(GO_STRAIGHT);
					}
					break;
				case FORWARD:
					if (forTimer->HasPeriodPassed(0.15)) {
						taskState = ARM_DOWN;
						forTimer->Stop();
						forTimer->Reset(); 
						drive->SetState(STOP_BOT);
						gripper->SetState(SCORE_RUN_BACK);
						gripTimer->Start();
						arm->SetState(SCORE_FALL_TO_NEUTRAL);
					}
					break;
				case ARM_DOWN:
					if (gripTimer->HasPeriodPassed(0.1)) {
						gripTimer->Stop();
						gripTimer->Reset();
						lift->SetState(SCORE_DROP_LIFT);	
						gripTimer->Start();
						taskState = RELEASE;
					}
					break;
				case RELEASE:
					if (gripTimer->HasPeriodPassed(0.25)) {
						gripTimer->Stop();
						gripTimer->Reset();
						taskState = MOVE_BACK_TWO;
						drive->SetState(MOVE_BACK);
						lift->SetState(WAIT_FOR_INPUT);
						arm->SetState(WAIT_FOR_ARM_INPUT);
						backTimer->Start();
					}
					break;
				case MOVE_BACK_TWO:
					if (backTimer->HasPeriodPassed(3.0)) {
						backTimer->Stop();
						backTimer->Reset();
						taskState = CHILL;
						drive->SetState(STOP_BOT);
						lift->SetState(MOVE_TO_GROUND_POSITION);
						gripper->SetState(WAIT_FOR_GRIP_INPUT);
					}	
					break;
				case CHILL:
					if (lift->StateComplete()) {
						lift->SetState(WAIT_FOR_INPUT);
					}
					break;
				default:
					break;	
			}
		}
		SwapAndWait();
	}
	
	return 0;
}

