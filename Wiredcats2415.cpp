#include "Wiredcats2415.h"
#include <math.h>

Task2415 *Task2415::TaskList[TASK2415_MAX_TASKS + 1] = {NULL};
int Task2415::TasksListed = 0;
int Task2415::TasksSwapped = 0;
bool Task2415::FirstConstructor = true;

Global global;

#include "Tasks.h"

Wiredcats2415::Wiredcats2415(void) {
	comp = new Compressor(4, 5);
	lightsA = new Relay(6);
}

void Wiredcats2415::Autonomous(void) {
	Task2415::SetTaskStatuses(STATUS_AUTO);	
	comp->Start();
}

void Wiredcats2415::OperatorControl(void) {
	Task2415::SetTaskStatuses(STATUS_TELEOP);
	comp->Start();	
}

START_ROBOT_CLASS(Wiredcats2415);

