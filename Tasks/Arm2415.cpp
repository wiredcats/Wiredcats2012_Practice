#include "Arm2415.h"
#include <math.h>

Arm2415::Arm2415(void) {
	global = Global::GetInstance();

	jagArm = new CANJaguar(4);

	pot = new AnalogChannel(1,1); 

	stickL = global->GetLeftJoystick();
	stickFB = global->GetFakeBJoystick();

	taskState = WAIT_FOR_ARM_INPUT;

	Start("arm2415");
}

int Arm2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main\n", taskName);

	float initialValue = 0.0;
	float potGoal = 0.0;
	int armSign = 0;

	float armSpeed = 0.0;
	bool inManualControl = true;

	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || taskStatus == STATUS_AUTO) {
			switch (taskState) {
				case WAIT_FOR_ARM_INPUT:
					// manual control
					if (stickFB->GetRawButton(6)) {  
						inManualControl = true;
						SyncMotorArm(-0.75);
					} else if (stickFB->GetRawButton(7)) { 
						inManualControl = true;
						SyncMotorArm(0.75);
					} else {
						if (stickFB->GetRawButton(5)) {
							inManualControl = false;
							SyncMotorArm(0.75);
						} else {
							if (inManualControl) {
								SyncMotorArm(0.0);
							} else {
								inManualControl = false;
								SyncMotorArm(-0.75);
							}
						}
					}

					break;
				case RUN_ARM_RAMP:
					if (((pot->GetVoltage() <= potGoal && armSign < 0)) || ((pot->GetVoltage() >= potGoal && armSign > 0))) {
						taskState = WAIT_FOR_ARM_INPUT;
					} else {
						armSpeed = armSign * RampMotor(pot->GetVoltage(), initialValue, potGoal, ARM2415_LOW_SPEED, ARM2415_MAX_SPEED, ARM2415_DELTARAMP);
						SyncMotorArm(armSpeed);
					}
					break;

				case SCORE_FALL_TO_NEUTRAL_ARM:
					SyncMotorArm(ARM2415_SCORE_FALL_SPEED);
					break;

				case BACKDRIVE:
					SyncMotorArm(-ARM2415_SCORE_FALL_SPEED);
					break;

				default:
					printf("reached default, moving to WAIT_FOR_ARM_INPUT\n");
					taskState = WAIT_FOR_ARM_INPUT;
					break;
			}
		}
		SwapAndWait();
	}

	return 0;
}

void Arm2415::SyncMotorArm(float speed) {
	jagArm->Set(speed);
}

float Arm2415::RampMotor(float x, float initial, float goal, float lowSpeed, float maxSpeed, float deltaValue) {
	float speed = (maxSpeed * (x - initial) * (goal - x)) / (deltaValue * (abs((int)(goal - initial)) - deltaValue)) + lowSpeed;

	if (speed <= lowSpeed) return lowSpeed;
	else if (speed >= maxSpeed) return maxSpeed;
	else return speed;
}

