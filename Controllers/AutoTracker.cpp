#include "AutoTracker.h"

AutoTracker2415::AutoTracker2415(void) {
	global = Global::GetInstance();
	
	printf("stalling to allow tasks to be initialized\n");
	Wait(2.0);
	
	turret = Task2415::SearchForTask("turret2415");

	Start("autotracker2415");
}

int AutoTracker2415::Main(int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10) {
	printf("entering %s main", taskName);
	
	while (keepTaskAlive) {
		if (taskStatus == STATUS_TELEOP || taskStatus == STATUS_AUTO) {
			
			AxisCamera &camera = AxisCamera::GetInstance();
			printf("Setting camera parameters\n");
			camera.WriteResolution(AxisCamera::kResolution_320x240);
			camera.WriteCompression(20);
			camera.WriteBrightness(0);
				
			HSLImage *image = camera.GetImage();
			
			sendIOPortData();
			sendVisionData();
			
			delete image;

		}
		SwapAndWait();
	}

	return 0;
}

