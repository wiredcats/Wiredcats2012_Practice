#include "ScoreController.h"

ScoreController2415::ScoreController2415(void) {
	global = Global::GetInstance();

	printf("stalling to allow tasks to be initialized\n");
	Wait(2.0);

	lift = Task2415::SearchForTask("lift2415");
	grip = Task2415::SearchForTask("gripper2415");
	arm = Task2415::SearchForTask("arm2415");

	armJumpstartTimer = new Timer();
	deployTimer = new Timer();
	gripDelayTimer = new Timer();

	stickL = global->GetLeftJoystick();
	stickR = global->GetRightJoystick();
	stickFB = global->GetFakeBJoystick();

	taskState = WAIT_FOR_SCORE_INPUT;

	Start("scorecontroller2415");
}

int ScoreController2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {

	if (arm == 0 || grip == 0 || lift == 0) { KillTask(); }

	printf("entering %s main\n", taskName);
	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || taskStatus == STATUS_AUTO) {
			switch (taskState) {
				case WAIT_FOR_SCORE_INPUT:
					if (stickFB->GetRawButton(11) || stickR->GetTrigger()) {
						armJumpstartTimer->Start();
						taskState = ARM_JUMPSTART;	
						arm->SetState(SCORE_FALL_TO_NEUTRAL);
						grip->SetState(SCORE_RUN_BACK);
					}

					if (stickL->GetRawButton(3)) {
						taskState = DEPLOY_TUBE;
						grip->SetState(SCORE_RUN_BACK);
						lift->SetState(SCORE_DROP_LIFT);
						
						deployTimer->Start();
					}
					break;
				case AUTO_SCORE:
					armJumpstartTimer->Start();
					taskState = ARM_JUMPSTART;	
					arm->SetState(SCORE_FALL_TO_NEUTRAL);
					grip->SetState(SCORE_RUN_BACK);
					break;
				case ARM_JUMPSTART:
					if (armJumpstartTimer->HasPeriodPassed(ARM_JUMPSTART_PERIOD)) {
						printf("switching into wait for input");
						armJumpstartTimer->Stop();
						armJumpstartTimer->Reset();
						
						lift->SetState(SCORE_DROP_LIFT);

						deployTimer->Start();

						taskState = DEPLOY_TUBE;
					}
					break;

				case DEPLOY_TUBE:
					if (deployTimer->HasPeriodPassed(DEPLOY_TUBE_PERIOD)) {
						deployTimer->Stop();
						deployTimer->Reset();

						arm->SetState(WAIT_FOR_ARM_INPUT);
						lift->SetState(WAIT_FOR_INPUT);
						grip->SetState(DELAY_GRIP_MOTOR);
						
						gripDelayTimer->Start();

						taskState = DELAY_GRIPPER;	
					}
					break;
				
				case DELAY_GRIPPER:
					if (gripDelayTimer->HasPeriodPassed(GRIP_DELAY_PERIOD)) {
						gripDelayTimer->Stop();
						gripDelayTimer->Reset();
						
						grip->SetState(WAIT_FOR_GRIP_INPUT);
						
						taskStateComplete = true;

						taskState = WAIT_FOR_SCORE_INPUT;
					}
					break;

				default:
					taskState = WAIT_FOR_SCORE_INPUT;
					break;
			}
		}
		SwapAndWait();
	}
	
	return 0;
}

