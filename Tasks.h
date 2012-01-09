#include "Tasks/Drive2415.h"
#include "Tasks/Lift2415.h"
#include "Tasks/Arm2415.h"
#include "Tasks/Gripper2415.h"
#include "Tasks/Deployment2415.h"

#include "Controllers/ScoreController.h"
//#include "Controllers/TwoTubeAutonomousController2415.h"
#include "Controllers/AutonomousController2415.h"

Drive2415 drive;
Lift2415 lift;
Arm2415 arm;
Gripper2415 gripper;
Deployment2415 deploy;

ScoreController2415 sc;
//TwoTubeAutonomousController2415 ac;
AutonomousController2415 ac;

