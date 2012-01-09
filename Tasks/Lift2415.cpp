#include "Lift2415.h"
#include <math.h>

Lift2415::Lift2415(void) {
	global = Global::GetInstance();

	jagLiftA = new CANJaguar(LIFT2415_JAGLIFTA_PORT);
	jagLiftB = new CANJaguar(LIFT2415_JAGLIFTB_PORT);
	jagLiftC = new CANJaguar(LIFT2415_JAGLIFTC_PORT);

	stickL = global->GetLeftJoystick();
	stickR = global->GetRightJoystick();
	stickFA = global->GetFakeAJoystick();
	stickFB = global->GetFakeBJoystick();

	encoder = new Encoder(1, 3);

	taskState = WAIT_FOR_INPUT;

	Start("lift2415");
}

int Lift2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main\n", taskName);

	int encoderValue = 0;
	float initialValue = 0.0;
	float encoderGoal = 0.0;
	int liftSign = 0;

	float liftSpeed = 0.0;
	encoder->Start();


	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || STATUS_AUTO) {
			encoderValue = encoder->Get();
			if (encoderValue < 0) encoder->Reset();
			printf("enc: [%d]", encoder->Get());

			// three position control
			if (PositionButtonPressed()) {
				initialValue = encoderValue;
				if (initialValue < 0) encoderValue = 0;

				if (stickFA->GetRawButton(6)) { encoderGoal = LIFT2415_ENCODER_TOP_LOW_VALUE; } 
				if (stickFA->GetRawButton(9)) { encoderGoal = LIFT2415_ENCODER_MID_LOW_VALUE; } 
				if (stickFA->GetRawButton(5)) { encoderGoal = LIFT2415_ENCODER_BOT_LOW_VALUE; } 

				if (stickFA->GetRawButton(7)) { encoderGoal = LIFT2415_ENCODER_TOP_HGH_VALUE; } 
				if (stickFA->GetRawButton(8)) { encoderGoal = LIFT2415_ENCODER_MID_HGH_VALUE; } 
				if (stickFA->GetRawButton(3)) { encoderGoal = LIFT2415_ENCODER_BOT_HGH_VALUE; } 

				liftSign = (encoderGoal > initialValue) ? 1 : -1;

				taskState = RUN_RAMP;
			}

			switch (taskState) {
				case WAIT_FOR_INPUT:
					// manual control
					if (stickFB->GetRawButton(8)) { 
						SyncMotorLift(LIFT2415_MANUAL_SPEED_UP);
					} else if (stickFB->GetRawButton(9)) {
						SyncMotorLift(-LIFT2415_MANUAL_SPEED_DOWN);
					} else {
						SyncMotorLift(0.0); 
					} 
					
					if (stickFB->GetRawButton(5)) {
						taskState = MOVE_TO_GROUND_POSITION;
					}

					break;
				case RUN_RAMP:
					if ((encoderValue >= encoderGoal && liftSign > 0) || (encoderValue <= (encoderGoal + 20) && liftSign < 0)) {
						printf("reached goal, ending ramp\n");
						taskStateComplete = true;
						taskState = WAIT_FOR_INPUT;
					} else {
						if (liftSign > 0) {
							liftSpeed = liftSign * RampMotor(encoderValue, initialValue, encoderGoal, LIFT2415_LOW_LIFT_SPEED, LIFT2415_MAX_LIFT_SPEED_UP, LIFT2415_DELTARAMP);
						} else {
							liftSpeed = liftSign * RampMotor(encoderValue, initialValue, encoderGoal + 150, LIFT2415_LOW_LIFT_SPEED, LIFT2415_MAX_LIFT_SPEED_DOWN, LIFT2415_DELTARAMP + 300);
						}
							
						SyncMotorLift(liftSpeed);
					}
					
					if (stickFB->GetRawButton(8) || stickFB->GetRawButton(7)) {
						printf("getting out of ramp loop!\n");
						taskState = WAIT_FOR_INPUT;
					}

					break;

				case SCORE_DROP_LIFT:
					SyncMotorLift(-LIFT2415_SCORE_DROP_SPEED);
					break;

				case MOVE_TO_AUTO_POSITION:
					initialValue = encoderValue;
					encoderGoal = LIFT2415_ENCODER_TOP_HGH_VALUE; 

					liftSign = (encoderGoal > initialValue) ? 1 : -1;

					taskState = RUN_RAMP;
					break;

				case MOVE_TO_GROUND_POSITION:
					initialValue = encoderValue;
					encoderGoal = LIFT2415_ENCODER_BOT_HGH_VALUE;

					liftSign = (encoderGoal > initialValue) ? 1 : -1;

					taskState = RUN_RAMP;
					break;

				default:
					printf("reached default, moving to WAIT_FOR_INPUT\n");
					taskState = WAIT_FOR_INPUT;
					break;
			}
		}
		SwapAndWait();
	}

	return 0;
}

void Lift2415::SyncMotorLift(float speed) {
	jagLiftA->Set(-speed);
	jagLiftB->Set(-speed);
	jagLiftC->Set(-speed);
}

bool Lift2415::PositionButtonPressed() {
	return (stickFA->GetRawButton(6) || stickFA->GetRawButton(9) ||	stickFA->GetRawButton(5) ||	
		stickFA->GetRawButton(7) || stickFA->GetRawButton(8) ||	stickFA->GetRawButton(3));
}	

float Lift2415::RampMotor(float x, float initial, float goal, float lowSpeed, float maxSpeed, float deltaValue) {
	if (x < 0) x = 0;
	float speed = (maxSpeed * (x - initial) * (goal - x)) / (deltaValue * (abs((int)(goal - initial)) - deltaValue)) + lowSpeed;

	if (speed <= lowSpeed) return lowSpeed;
	else if (speed >= maxSpeed) return maxSpeed;
	else return speed;
}

